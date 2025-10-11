#include <cstdlib>
#include <iostream>
using namespace std;
int strlen(const char * s) 
{	int i = 0;
	for(; s[i]; ++i);
	return i;
}
void strcpy(char * d,const char * s)
{
	int i = 0;
	for( i = 0; s[i]; ++i)
		d[i] = s[i];
	d[i] = 0;
		
}
int strcmp(const char * s1,const char * s2)
{
	for(int i = 0; s1[i] && s2[i] ; ++i) {
		if( s1[i] < s2[i] )
			return -1;
		else if( s1[i] > s2[i])
			return 1;
	}
	return 0;
}
void strcat(char * d,const char * s)
{
	int len = strlen(d);
	strcpy(d+len,s);
}
class MyString
{
private:
    char* data;
    int length;

    void copy(const char* s) {
        if (s == nullptr) {
            length = 0;
            data = new char[1];
            data[0] = '\0';
        } else {
            length = strlen(s);
            data = new char[length + 1];
            strcpy(data, s);
        }
    }

public:
    MyString() : data(nullptr), length(0) {
        data = new char[1];
        data[0] = '\0';
    }

    MyString(const char* s) {
        copy(s);
    }

    // 拷贝构造函数
    MyString(const MyString& other) {
        copy(other.data);
    }

    // 析构函数
    ~MyString() {
        delete[] data;
    }

    // 赋值运算符重载
    MyString& operator=(const char* s) {
        if (data != nullptr) {
            delete[] data;
        }
        copy(s);
        return *this;
    }

    MyString& operator=(const MyString& other) {
        if (this != &other) {
            if (data != nullptr) {
                delete[] data;
            }
            copy(other.data);
        }
        return *this;
    }

    // 连接运算符重载
    MyString operator+(const MyString& other) const {
        char* temp = new char[length + other.length + 1];
        strcpy(temp, data);
        strcat(temp, other.data);
        MyString result(temp);
        delete[] temp;
        return result;
    }

    MyString operator+(const char* s) const {
        char* temp = new char[length + strlen(s) + 1];
        strcpy(temp, data);
        strcat(temp, s);
        MyString result(temp);
        delete[] temp;
        return result;
    }

    friend MyString operator+(const char* s, const MyString& other) {
        char* temp = new char[strlen(s) + other.length + 1];
        strcpy(temp, s);
        strcat(temp, other.data);
        MyString result(temp);
        delete[] temp;
        return result;
    }

    // += 运算符重载
    MyString& operator+=(const char* s) {
        char* temp = new char[length + strlen(s) + 1];
        strcpy(temp, data);
        strcat(temp, s);
        delete[] data;
        data = temp;
        length = strlen(temp);
        return *this;
    }

    MyString& operator+=(const MyString& other) {
        char* temp = new char[length + other.length + 1];
        strcpy(temp, data);
        strcat(temp, other.data);
        delete[] data;
        data = temp;
        length = strlen(temp);
        return *this;
    }

    // 下标运算符重载
    char& operator[](int index) {
        return data[index];
    }

    // 比较运算符重载
    bool operator<(const MyString& other) const {
        return strcmp(data, other.data) < 0;
    }

    bool operator>(const MyString& other) const {
        return strcmp(data, other.data) > 0;
    }

    bool operator==(const MyString& other) const {
        return strcmp(data, other.data) == 0;
    }

    // 输出运算符重载
    friend ostream& operator<<(ostream& os, const MyString& s) {
        os << s.data;
        return os;
    }

    // 子串函数
    MyString operator()(int start, int len) const {
        char* temp = new char[len + 1];
        for (int i = 0; i < len; i++) {
            temp[i] = data[start + i];
        }
        temp[len] = '\0';
        MyString result(temp);
        delete[] temp;
        return result;
    }
};


int CompareString( const void * e1, const void * e2)
{
	MyString * s1 = (MyString * ) e1;
	MyString * s2 = (MyString * ) e2;
	if( * s1 < *s2 )
	return -1;
	else if( *s1 == *s2)
	return 0;
	else if( *s1 > *s2 )
	return 1;
}
int main()
{
	MyString s1("abcd-"),s2,s3("efgh-"),s4(s1);
	MyString SArray[4] = {"big","me","about","take"};
	cout << "1. " << s1 << s2 << s3<< s4<< endl;
	s4 = s3;
	s3 = s1 + s3;
	cout << "2. " << s1 << endl;
	cout << "3. " << s2 << endl;
	cout << "4. " << s3 << endl;
	cout << "5. " << s4 << endl;
	cout << "6. " << s1[2] << endl;
	s2 = s1;
	s1 = "ijkl-";
	s1[2] = 'A' ;
	cout << "7. " << s2 << endl;
	cout << "8. " << s1 << endl;
	s1 += "mnop";
	cout << "9. " << s1 << endl;
	s4 = "qrst-" + s2;
	cout << "10. " << s4 << endl;
	s1 = s2 + s4 + " uvw " + "xyz";
	cout << "11. " << s1 << endl;
	qsort(SArray,4,sizeof(MyString),CompareString);
	for( int i = 0;i < 4;i ++ )
	cout << SArray[i] << endl;
	//s1的从下标0开始长度为4的子串
	cout << s1(0,4) << endl;
	//s1的从下标5开始长度为10的子串
	cout << s1(5,10) << endl;
	return 0;
}