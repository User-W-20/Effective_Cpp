//条款10：令operator=返回一个reference to *this
#include<iostream>
#include<string>
using namespace std;

int x, y, z;
x = y = z = 15;//赋值连锁形式

//右结合律
x = (y = (z = 15));

//为了实现“连锁赋值”，赋值操作符必须返回一个reference指向操作符的左侧实参。

class Widget {
public:
	//返回类型是个reference指向当前对象
	Widget& operator=(const Widget& rhs) {
		return *this;//返回左侧对象
	}
};

class Widget {
public:
	//这个协议适用于+=，-=，*=，等等
	Widget& operator+=(const Widget& rhs) {
		return *this;
	}

	//此函数也适用，即使此-操作符的参数类型不符协定。
	Widget& operator=(int rhs) {
		return *this;
	}
};

//令赋值（assignment）操作符返回一个reference to *this。