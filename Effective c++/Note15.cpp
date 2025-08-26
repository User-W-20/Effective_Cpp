//条款15：在资源管理类中提供对原始资源的访问
#include<iostream>
#include<memory>
#include<string>
using namespace std;
//资源管理类（resource-managing classes）是对抗资源泄露的堡垒。排除此等泄露是良好设计系统的根本性质。

//许多APIs直接指涉资源，除非永远不用这样的APIs，否则只能绕过资源管理对象（resource managing objects）直接访问原始资源（raw resources）。
class Investment {
};

shared_ptr<Investment>pInv(createInvestment());

int daysHeld(const Investment* pi);//返回投资天数

int days = daysHeld(pInv);//错误！

//daysHeld需要的是Investment*指针，而这样传递的是类型为shared_ptr<Investment>的对象。

//这时候需要一个函数可将RAII class 对象转换为其所内含的原始资源.

//两个做法：显式转换和隐式转换

//shared_ptr和auto_ptr都提供一个get成员函数，用来执行显式转换，它会返回智能指针内部的原始指针（的副本）。

int days = daysHeld(pInv.get());//将pInv内的原始指针传给daysheld

//shared_ptr和auto_ptr也重载了指针取值（pointer dereferencing）操作符（operator->和operator*），允许隐式转换至底部原始指针

class Investment {//Investment继承体系的根类
public:
	bool isTaxFree()const;
};

Investment* createrInvestment();//factory函数

//令shared_ptr管理一笔资源
shared_ptr<Investment> pi1(createrInvestment());

bool taxable1 = !(pi1->isTaxFree());//由operator->访问资源

//令auto_ptr*管理一笔资源
auto_ptr<Investment> pi2(createrInvestment());

bool taxable2 = !((*pi2).isTaxFree());//由operator*访问资源

//由于有时候还是必须去的RAII对象内的原始资源，做法是提供一个隐式转换函数
class FontHandle{};

FontHandle getFront();//C API

void releaseFont(FontHandle fh);//来自同一组C API

class Font {//RAII class
public:
	explicit Font(FontHandle fh)//获得资源
		:f(fh){}//采用pass-by-value

	~Font() { releaseFont(f); }//释放资源
private:
	FontHandle f;//原始（raw）字体资源
};

//Font class提供一个显式转换函数，像get那样

class Font {
public:
	FontHandle get()const { return f; }//显式转换函数
};

void changeFontSize(FontHandle f, int newSize);//C API

Font f(getFront());
int newFontSize;

changeFontSize(f.get(), newFontSize);//明确的将Font转换为FontHandle

//另一个方法是令Font提供隐式转换函数，转型为FontHandle

class Font {
public:
	operator FontHandle()const//隐式转换函数
	{
		return f;
	}
};

Font f(getFront());
int newFontSize;

changeFontSize(f, newFontSize);//将Font隐式转换为FontHandle

Font f1(getFront());

//原意是要拷贝一个Font对象，却反而将f1隐式转换为其底部的FontHandle。然后才复制它
FontHandle f2 = f1;

//是否提供一个显式转换函数将RAII class转换为其底部资源，或是应该提供隐式转换，主要取决于RAII class被设计执行的特定工作，以及它被使用的情况。

//通常显式转换函数如get是比较受欢迎的方法，因为它将“非故意的类型转换”的可能性最小化了。

//RAII classes并不是为了封装某物而存在；它们存在是为了确保一个特殊行为--资源释放--会发生。
//如果一定要，当然也可以在这基本功能上再加一层资源封装，以此获得真正的封装实现。

//APIs往往要求访问原始资源（raw resource），所以每一个RAII class应该提供一个“取得其所管理的资源”的方法。

//为原始资源的访问可能是经由显式转换或隐式转换。一般而言显式转换比较安全，但是隐式转换对客户比较方便。