#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/image.hpp>
#include <std_msgs/msg/string.hpp>
#include <geometry_msgs/msg/point.hpp>
#include <cv_bridge/cv_bridge.h>
#include <image_transport/image_transport.hpp>
#include <opencv2/opencv.hpp>
#include <vector>

class ColorBlockDetectorNode : public rclcpp::Node
{
public:
  ColorBlockDetectorNode() : Node("color_block_detector_node")
  {
    // 声明参数
    this->declare_parameter<std::string>("image_topic", "/camera/image_raw");
    this->declare_parameter<int>("blue_hue_low", 100);
    this->declare_parameter<int>("blue_hue_high", 130);
    this->declare_parameter<int>("blue_saturation_low", 50);
    this->declare_parameter<int>("blue_saturation_high", 255);
    this->declare_parameter<int>("blue_value_low", 50);
    this->declare_parameter<int>("blue_value_high", 255);
    this->declare_parameter<int>("red_hue_low1", 0);
    this->declare_parameter<int>("red_hue_high1", 10);
    this->declare_parameter<int>("red_hue_low2", 160);
    this->declare_parameter<int>("red_hue_high2", 180);
    this->declare_parameter<int>("red_saturation_low", 50);
    this->declare_parameter<int>("red_saturation_high", 255);
    this->declare_parameter<int>("red_value_low", 50);
    this->declare_parameter<int>("red_value_high", 255);
    this->declare_parameter<int>("min_contour_area", 1000);
    
    // 获取参数
    this->get_parameter("image_topic", image_topic_);
    
    // 创建图像订阅者
    image_sub_ = image_transport::create_subscription(
      this, image_topic_, 
      std::bind(&ColorBlockDetectorNode::image_callback, this, std::placeholders::_1),
      "raw");
    
    // 创建原始结果图
    image_pub_ = image_transport::create_publisher(this, "color_detection_result");
    
    // 创建色块位置发布者
    blue_block_pub_ = this->create_publisher<geometry_msgs::msg::Point>("blue_block_position", 10);
    red_block_pub_ = this->create_publisher<geometry_msgs::msg::Point>("red_block_position", 10);
    
    // 创建新窗口
    cv::namedWindow("Red Mask", cv::WINDOW_NORMAL);  // 红色区域窗口
    cv::namedWindow("Blue Mask", cv::WINDOW_NORMAL); // 蓝色区域窗口
    cv::resizeWindow("Red Mask", 640, 480);          // 设置窗口大小
    cv::resizeWindow("Blue Mask", 640, 480);
    
    RCLCPP_INFO(this->get_logger(), "Color Block Detector Node started");
  }

  ~ColorBlockDetectorNode()
  {
    // 关闭窗口
    cv::destroyWindow("Red Mask");
    cv::destroyWindow("Blue Mask");
  }

private:
  void image_callback(const sensor_msgs::msg::Image::ConstSharedPtr& msg)
  {
    try
    {
      // 将ROS图像消息转换为OpenCV图像
      cv_bridge::CvImagePtr cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
      cv::Mat frame = cv_ptr->image;
      
      // 创建图像用于显示结果
      cv::Mat result_frame = frame.clone();
      
      // 转换为HSV颜色空间
      cv::Mat hsv_frame;
      cv::cvtColor(frame, hsv_frame, cv::COLOR_BGR2HSV);
      
      // 检测蓝色方块并获取掩码
      cv::Mat blue_mask = detect_color_block(hsv_frame, result_frame, "blue");
      // 检测红色方块并获取掩码
      cv::Mat red_mask = detect_color_block(hsv_frame, result_frame, "red");
      
      // 发布结果图像
      std::shared_ptr<sensor_msgs::msg::Image> out_msg = cv_bridge::CvImage(
        msg->header, sensor_msgs::image_encodings::BGR8, result_frame).toImageMsg();
      image_pub_.publish(out_msg);
      
      // 在新窗口中显示红色和蓝色掩码（实时更新）
      // 确保窗口始终显示（即使掩码为空也显示黑色窗口）
      cv::imshow("Red Mask", red_mask.empty() ? cv::Mat::zeros(hsv_frame.size(), CV_8UC1) : red_mask);
      cv::imshow("Blue Mask", blue_mask.empty() ? cv::Mat::zeros(hsv_frame.size(), CV_8UC1) : blue_mask);
      
      
      // 等待按键事件（必须添加，否则窗口会无响应）
      cv::waitKey(30);
      
    }
    catch (cv_bridge::Exception& e)
    {
      RCLCPP_ERROR(this->get_logger(), "cv_bridge exception: %s", e.what());
    }
  }
  
  // 检测颜色块并返回掩码
  cv::Mat detect_color_block(const cv::Mat& hsv_frame, cv::Mat& result_frame, const std::string& color)
  {
    cv::Mat mask;
    cv::Scalar lower_bound, upper_bound;
    cv::Scalar draw_color;
    rclcpp::Publisher<geometry_msgs::msg::Point>::SharedPtr* publisher;
    
    // 设置颜色阈值
    if (color == "blue")
    {
      int h_low, h_high, s_low, s_high, v_low, v_high;
      this->get_parameter("blue_hue_low", h_low);
      this->get_parameter("blue_hue_high", h_high);
      this->get_parameter("blue_saturation_low", s_low);
      this->get_parameter("blue_saturation_high", s_high);
      this->get_parameter("blue_value_low", v_low);
      this->get_parameter("blue_value_high", v_high);
      
      lower_bound = cv::Scalar(h_low, s_low, v_low);
      upper_bound = cv::Scalar(h_high, s_high, v_high);
      draw_color = cv::Scalar(255, 0, 0); // BGR
      publisher = &blue_block_pub_;
      
      // 创建蓝色掩码
      cv::inRange(hsv_frame, lower_bound, upper_bound, mask);
    }
    else if (color == "red")
    {
      int h_low1, h_high1, h_low2, h_high2, s_low, s_high, v_low, v_high;
      this->get_parameter("red_hue_low1", h_low1);
      this->get_parameter("red_hue_high1", h_high1);
      this->get_parameter("red_hue_low2", h_low2);
      this->get_parameter("red_hue_high2", h_high2);
      this->get_parameter("red_saturation_low", s_low);
      this->get_parameter("red_saturation_high", s_high);
      this->get_parameter("red_value_low", v_low);
      this->get_parameter("red_value_high", v_high);
      
      // 红色在HSV空间中有两个范围
      cv::Mat mask1, mask2;
      cv::inRange(hsv_frame, cv::Scalar(h_low1, s_low, v_low), cv::Scalar(h_high1, s_high, v_high), mask1);
      cv::inRange(hsv_frame, cv::Scalar(h_low2, s_low, v_low), cv::Scalar(h_high2, s_high, v_high), mask2);
      mask = mask1 | mask2;
      
      draw_color = cv::Scalar(0, 0, 255); 
      publisher = &red_block_pub_;
    }
    else
    {
      return cv::Mat();
    }
    
    // 形态学操作去除噪声
    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(5, 5));
    cv::morphologyEx(mask, mask, cv::MORPH_OPEN, kernel);
    cv::morphologyEx(mask, mask, cv::MORPH_CLOSE, kernel);
    
    // 查找轮廓
    std::vector<std::vector<cv::Point>> contours;
    cv::findContours(mask, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
    
    // 过滤轮廓并找到最大的方块
    int min_area;
    this->get_parameter("min_contour_area", min_area);
    double max_area = 0;
    std::vector<cv::Point> largest_contour;
    
    for (const auto& contour : contours)
    {
      double area = cv::contourArea(contour);
      if (area > min_area && area > max_area)
      {
        max_area = area;
        largest_contour = contour;
      }
    }
    
    // 如果找到有效轮廓，绘制并发布位置
    if (!largest_contour.empty())
    {
      // 计算最小外接矩形
      cv::RotatedRect rect = cv::minAreaRect(largest_contour);
      cv::Point2f vertices[4];
      rect.points(vertices);
      
      // 绘制矩形
      for (int i = 0; i < 4; ++i)
      {
        cv::line(result_frame, vertices[i], vertices[(i+1)%4], draw_color, 2);
      }
      
      // 计算中心点
      cv::Point2f center = rect.center;
      cv::circle(result_frame, center, 5, draw_color, -1);
      
      // 发布位置信息
      geometry_msgs::msg::Point point_msg;
      point_msg.x = center.x;
      point_msg.y = center.y;
      point_msg.z = 0.0; // 2D图像，z坐标为0
      (*publisher)->publish(point_msg);
      
      // 在图像上显示坐标
      std::string text = color + ": (" + std::to_string((int)center.x) + "," + std::to_string((int)center.y) + ")";
      cv::putText(result_frame, text, cv::Point(center.x + 10, center.y), 
                  cv::FONT_HERSHEY_SIMPLEX, 0.5, draw_color, 2);
    }
    
    // 返回处理后的掩码
    return mask;
  }
  
  std::string image_topic_;
  image_transport::Subscriber image_sub_;
  image_transport::Publisher image_pub_;
  rclcpp::Publisher<geometry_msgs::msg::Point>::SharedPtr blue_block_pub_;
  rclcpp::Publisher<geometry_msgs::msg::Point>::SharedPtr red_block_pub_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<ColorBlockDetectorNode>());
  rclcpp::shutdown();
  return 0;
}


