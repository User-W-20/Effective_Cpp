//条款03：尽可能使用const
#include<iostream>
#include<vector>

char greeting[] = "Hello";
char* p = greeting;
const char* p = greeting;//const data
char* const p = greeting;//const pointer
const char* const p = greeting;//const pointer ,const data

//const出现在星号左边，表示被指物是常量
//const出现在星号右边，表示指针自身是常量

void f1(const Widget* pw);//f1获得一个指针，指向一个常量的Widget对象
void f2(Widget const* pw);

//声明一个T* const指针，表示这个迭代器不得指向不同的东西，但它所指的值是可以改动的
//如果希望迭代器所指的东西不可被改动（即希望STL模拟一个const T*指针），需要const_iterator

std::vector<int >vec;
const std::vector<int>::iterator iter = vec.begin();//iter的作用像T* const
*iter = 10;//没问题，改变iter所指物
++iter;//错误：iter是const

std::vector<int>::const_iterator CIter = vec.begin();//CIter的作用像个const T*
*CIter = 10;//错误：*CIter是const
++CIter;//没问题：改变CIter

class Rational{};

const Rational operator*(const Rational& lhs, const Rational& rhs);

Rational a, b, c;
(a* b) = c;//在a*b的成果上调用operator=

//const 成员函数
//将const实施于成员函数的目的，是为了确认该成员函数可作用于const对象身上

//1、它们使class接口比较容易被理解。
//2、它们使“操作const对象”成为可能。

//两个成员函数如果只是常量性（constness）不同，可以被重载

class TextBlock {
public:
	const char& operator[](std::size_t position)const { return text[position]; }//operator[]for const 对象

	char& operator[](std::size_t position) { return text[position]; }////operator[]for non-const 对象

private:
	std::string text;
};

TextBlock tb("Hello");
std::cout << tb[0];//non-const

const TextBlock ctb("World");
std::cout << ctb[0];//const

void print(const TextBlock& ctb) {//const
	std::cout << ctb[0];//const
}

std::cout << tb[0];//读non-const
tb[0] = 'x';//写non-const
std::cout << ctb[0];//读const
ctb[0] = 'x';//错误：写const

//non_const operator[]的返回类型是个reference to char，不是char

//如果函数的返回类型是个内置类型，那么改动函数返回值从来就不合法.

//bitwise constness(physical constness)和logical constness

//bitwise constness:成员函数只有在不改变对象之任何成员变量（static除外）时才可以说是const

class CTextBlock {
public:
	char& operator[](std::size_t position)const { return pText[position]; }//bitwise const声明，但其实不适当

private:
	char* pText;
};

const CTextBlock cctb("Hello");//声明一个常量对象
char* pc = &cctb[0];//调用const operator[]取得一个指针，指向cctb的数据
*pc = 'J';//cctb现在有了“Jello”

//logical constness:一个const成员函数可以修改它所处理的对象内的某些bits，但只有在客户端侦测不出的情况下才得如此。

class CTextBlock {
public:
	std::size_t length()const;

private:
	char* pText;
	std::size_t textLength();//最近一次计算的文本区块的长度
	bool lengthIsVaild;//目前的长度是否有效
};

std::size_t CTextBlock::length()const {
	if (!lengthIsVaild) {
		textLength = std::strlen(pText);//错误，在const成员函数内不能赋值给textLength和lengthIsValid
		lengthIsVaild = true;
	}
	return textLength;
}

//解决办法：利用C++的一个与const相关的摆动场：mutable。

class CTextBlock {
public:
	std::size_t length()const;
private:
	char* pText;
	mutable std::size_t textLength;//这些成员变量可能总是会被修改，即使在const成员函数内
	mutable bool lengthIsVaild;
};

std::size_t CTextBlock::length()const {
	if (!lengthIsVaild) {
		textLength = std::strlen(pText);
		lengthIsVaild = true;
	}
	return textLength;
}

//在const和non-const成员函数中避免重复
class TextBlock {
public:
	const char& operator[](std::size_t position)const {
		//边界检验
		//日记数据访问
		//检验数据完整性
		return text[position];
	}

	 char& operator[](std::size_t position) {
		//边界检验
		//日记数据访问
		//检验数据完整性
		return text[position];
	}

private:
	std::string text;
};


//常量性转除:把一个被声明为const的对象，通过手段“强制”变为非const，从而对它进行修改

class TextBlock {
public:
	const char& operator[](std::size_t position)const {
		return text[position];
	}

	char& operator[](std::size_t postition) {//现在只调用const op[]
		return
			const_cast<char&>(//将op[]返回值的const转除
static_cast<const TextBlock&>(*this)//为*this加上const
				[postition]//调用const op[]
);
	}
};

//将某些东西声明为const可帮助编译器侦测出错误用法。const可被施加在于任何作用域内的对象、函数参数、函数返回类型、成员函数体
//编译器强制实施bitwise constness，但在编写程序时应使用“概念上的常量性”(conceptual constness)
//当const和non-const成员函数有着实质等价的实现时，令non-const版本调用const版本可以避免代码重复。