//条款02：尽量以const、enum、inline替换#define
#include<iostream>
#define ASPECT_RATIO 1.653

/*ASPECT_RATIO也许从未被编译器看见；
也许在编译器开始处理源码之前就被预处理器移走了*/

//以常量替换上述的宏（#define）

const double AspectRatio = 1.653;//大写名称通常用于宏，因此改变写法

//以常量替换#define时有两种特殊情况：
//1、定义常量指针
//在头文件内定义一个常量的char*base字符串，必须写const两次
const char* const authorName = "Scitt Meyers";

const std::string authorName("Scitt Meyers");

//2、class专属常量
class GamePlayer {
private:
	static const int NumTurns = 5;//常量声明式
	int scores[NumTurns];//使用该常量
};

/*但如果它是个class专属常量又是static且为整数类型,则需特殊处理。
只要不取它们的地址，则可以声明并使用它们而无须提供定义式*/

//const int GamePlayer::NumTurns;

//#define不仅不能用来定义class专属常量，也不能提供任何封装性

class CostEstimate {
private:
	static const double FudgeFactor;//static class 常量声明
};//.h

const double CostEstimate::FudgeFactor = 1.35;//.cpp

//唯一例外：在class编译期间需要一个class常量值，（编译器坚持必须在编译器间知道数组的大小）。
//万一编译器（错误地）不允许“static整数型class常量“完成”in class 初值设定”,可改用“the enum hack”补偿做法。
//理论基础：“一个属于枚举类型的数值可权充ints被使用

class GamePlayer {
private:
	enum {NumTurns=5};//"the enum hack"-令NumTurns成为5的一个记号符号
	int scores{ NumTurns };
};

//enum hack的行为某方面比较像#define而不像const。

//如果不想让别人获得一个pointer或reference指向某个整数常量，enum可以帮助实现这个约束

//enum hack 是template mateprogramming（模板元编程）的基础技术

//以a和b的较大值调用f
#define CALL_WITH_MAX (a,b) f((a)>(b)?(a):(b))

int a = 5, b = 0;
CALL_WITH_MAX(++a, b);//a被累加二次
CALL_WITH_MAX(++a, b + 10);//a被累加一次

template<typename T>
inline void callWithMax(const T& a, const T& b)
{
	f(a > b ? a : b);//pass by reference-to-const
}

//对于单纯常量，最好以const对象或enums替代#defines
//对于形似函数的宏（macros），最好改用inline函数替换#defines

