from launch import LaunchDescription
from launch_ros.actions import Node
from launch.substitutions import LaunchConfiguration
from launch.actions import DeclareLaunchArgument

def generate_launch_description():
    return LaunchDescription([
        # 声明启动参数
        DeclareLaunchArgument(
            'image_topic',
            default_value='/camera/image_raw',
            description='Image topic to subscribe to'
        ),
        
        # 启动色块识别节点
        Node(
            package='color_block_detector',
            executable='color_block_detector_node',
            name='color_block_detector_node',
            output='screen',
            parameters=[
                {'image_topic': LaunchConfiguration('image_topic')}
            ]
        )
    ])

