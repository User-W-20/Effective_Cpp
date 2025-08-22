//条款07：为多态基类声明virtual析构函数
#include<iostream>
#include<vector>
using namespace std;

class TimerKeeper {
public:
	TimerKeeper();
	~TimerKeeper();
};

class AtomicClock:public TimerKeeper{};//原子钟
class WaterClock :public TimerKeeper{};//水钟
class WristWatch :public TimerKeeper{};//腕表

//只想在程序中使用时间，不关心时间如何计算等细节
//可以设计factory（工厂）函数，返回指针指向一个计时函数

TimerKeeper* getTimeKeeper();//返回一个指针，指向一个
							//TimerKeeper派生类的动态分配对象

//被getTimeKeeper（）返回的对象必须位于heap
//未来避免泄露内存和其他资源，将factory函数返回的每一个对象适当地delete掉很重要

TimerKeeper* ptk = getTimeKeeper();/*从TimerKeeper继承体系	                              获得一个动态分配对象
									运用它*/
delete ptk;//释放，避免资源泄露

//当derived class 对象由一个base class 指针被删除，而该base class带着一个non-virtual析构函数，其结果未有定义——实际执行时通常发生的是对象的derived成分没被销毁。

//解决方法：给base class一个virtual析构函数

class TimeKeeper {
public:
	TimerKeeper( );
	virtual ~TimerKeeper();
};

TimerKeeper* ptk = getTimeKeeper();

delete ptk;//行为正确

//如果class不含virtual函数，通常表示它并不意图被用做一个base class

class Point {//一个二维空间点（2D point）
public:
	Point(int xCoord, int yCoord);
	~Point();
private:
	int x, y;
};

//每个虚函数都有一个虚函数表，用来存放虚函数地址
//对应的对象有一个指向虚函数表的指针，vptr
//使用虚函数的时候，vptr通过虚表，实现动态绑定
//因此如果Point class 内含 virtual函数，其对象的体积会增加

//只有当class 内含至少一个virtual函数，才为它声明virtual析构函数

class SpecialString:public std::string{};//馊主意！std::string有一个non-virtual析构函数

//如果在某处无意的将pointer-to-SpecialString转换为一个pointer-to-String，然后将转换所得的那个string指针delete掉，立刻会处于“行为不明确”。

class AWOV {
public:
	virtual ~AWOV() = 0;//声明pure virtual析构函数
};

AWOV::~AWOV(){}//pure virtual析构函数的定义

//析构函数的运作方式：最深层派生（most derived）的那个class其析构函数最先被调用，然后是其每一个base class的析构函数被调用。

//给base classes一个virtual析构函数，这个规则只适用于polymorphic（带多态性质的）base classes身上
//这种base classes的设计目的是为了用来通过base class接口处理derived class对象。

//polymorphic（带多态性质的）base class 应该声明一个virtual析构函数。如果class带有任何virtual函数，它就应该拥有一个virtual析构函数

//Classes的设计目的如果不是作为base classes使用，或不是为了具备多态性（polymorphic），就不该声明virtual析构函数

//禁止继承的类（例如final，或不打算被继承的工具类）->不用虚析构