//条款18：让接口容易被正确使用，不易被误用

//欲开发一个“容易被正确使用，不容易被误用”的接口，首先必须考虑客户可能做出什么错误
#include<iostream>
#include<memory>
class Date {
public:
	Date(int month, int day, int year);
};

//它的客户很容易犯下至少两个错误
//1、他们也许会以错误的次序传递参数
Date d(30, 3, 1995);//应该是3.30

//2、他们可能传递一个无效的月份或天数
Date d(2, 30, 1995);//应该是3.30

//许多客户端错误可以因为导入新类型而获得预防

struct Day
{
	explicit Day(int d) :val(d){}
	int val;
};

struct Month
{
	explicit Month(int m) :val(m) {}
	int val;
};

struct Year
{
	explicit Year(int y) :val(y) {}
	int val;
};

class Date {
public:
	Date(const Month& m, const Day& d, const Year& y);
};

Date d(30, 3, 1995);//错误。不正确的类型
Date d(Day(30), Month(3), Year(1995));//错误。不正确的类型
Date d(Month(30), Day(3), Year(1995));//正确

//明智而谨慎地导入新类型对预防“接口被误用”有神奇疗效

//一旦正确的类型就定位，限制其值有时候是通情达理的

class Month {
public:
	//函数，返回有效月份，这些是函数而非对象
	static Month Jan() { return Month(1); }
	//...
	static Month Dec() { return Month(12); }
private:
	//阻止生成新月份，月份的专属数据
	explicit Month(int m);
};

Date d(Month::Dec(), Day(30), Year(1995));

//预防客户错误的另一个方法是，限制类型内什么事可做，什么事不能做
//常见 加上const

//除非有好理由，否则应该尽量令types的行为与内置的types一致

//避免无端与内置类型不兼容，真正的理由是为了提供行为一致的接口

//任何接口如果要求客户必须记得做某件事，就是有着“不正确使用”的倾向，因为客户可能会忘记做那件事
class Investment{};

Investment* createInvestment();

//为避免资源泄露，createInvestment返回的指针最终必须被删除，但那至少开启了两个客户错误机会：没有删除指针，或删除同一个指针超过一次

//许多时候，较佳接口的设计原则是先发制人，就令factory函数返回一个智能指针

std::shared_ptr<Investment> createInvestment();

//企图创建一个null shared_ptr 并携带一个自定的删除器，此式无法通过编译
std::shared_ptr<Investment>
pInv(0, getRidOfInvestment);

//shared_ptr构造函数坚持其第一参数必须是个指针，而0不是指针，是个int

//建立一个null shared_ptr并以getRidOfInvestment为删除器
std::shared_ptr<Investment>
pInv(static_cast<Investment*>(0), getRidOfInvestment);

std::shared_ptr<Investment> createInvestment() {
	std::shared_ptr<Investment>
		retVal(static_cast<Investment*>(0), getRidOfInvestment);

	retVal = ...;//令retVal指向正确对象
	return retVal;
}

//如果被pInv管理的原始指针（raw pointer）可以在建立pInv之前先确定下来，那么“将原始指针传给pInv构造函数”会比“先将pInv初始化为null再对它做一次赋值操作”为佳

//shared_ptr会自动使用它的“每个指针专属的删除器”，因而消除另一个潜在的客户错误：所谓的“cross-DLL problem”

std::shared_ptr<Investment> createInvestment() {
	return std::shared_ptr<Investment>(new Stock);
}

//返回的那个shared_ptr可被传递给任何DLLs，无需在意“cross-DLL problem”

//好的接口很容易被正确使用，不容易被误用。应该在所有接口中努力达成这些性质

//“促进正确使用”的方法包括接口的一致性，以及与内置类型的行为兼容

//shared_ptr支持定制型删除器（custom deleter）。这可防范DLL问题，可被用来自动解除互斥锁（mutexes）等等