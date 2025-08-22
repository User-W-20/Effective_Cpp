//条款06：若不想使用编译器自动生成的函数，就该明确拒绝

#include<iostream>

class HomeForSale{};

HomeForSale h1;
HomeForSale h2;
HomeForSale h3(h1);//企图拷贝h1-不该通过编译
h1 = h2;//企图拷贝h2-也不该通过编译

//通常如果不希望class支持某一特定技能，只要不声明对应函数就行。
//但这个策略对copy构造函数和copy assignment操作符不起作用
//因为如果不声明它们，编译器会声明它们

//所有编译器产出的函数都是public

//将成员函数声明为private而且故意不实现它们

class HomeForSale {
public:

private:
	HomeForSale(const HomeForSale&);//只有声明
	HomeForSale& operator=(const HomeForSale&);
};

class Uncopyable {
protected:
	Uncopyable(){}//允许derived对象构造和析构
	~Uncopyable(){}

private:
	Uncopyable(const Uncopyable&);
	Uncopyable& operator=(const Uncopyable&);
};

class HomeForSale :private Uncopyable {//class不再声明
										//copy构造函数或
};									//copy assign操作符

//为驳回编译器自动（暗自）提供的机能，可将相应的成员函数声明为private并且不予实现。使用像Uncopyable这样的base class也是一种做法。