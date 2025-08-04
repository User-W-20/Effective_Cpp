//条款05：了解C++默默编写并调用哪些函数
#include<iostream>
//如果没声明，编译器就会为它声明（编译器版本的）copy构造函数、copy assignment 操作符和析构函数。
//如果没有声明任何构造函数，也会声明一个default构造函数，都是public且inline。

class Empty{};

class Empty {
public:
	Empty(){}//default构造函数
	Empty(const Empty&rhs){}//copy
	~Empty(){}//析构

	Empty operator=(const Empty& rhs){}//copy assignment
};

Empty e1;//default构造函数
		//析构
Empty e2(e1);//copy

e2 = e1;//copy assignment

//编译器产出的析构函数是个non-virtual，除非这个class的base class自身声明有virtual析构函数（这种情况下这个函数的虚属性；virtualness；主要来自base class）

//copy和copy assignment，编译器创建的版本只是单纯地来源对象的每一个non_static成员变量拷贝到目标对象

template<typename T>
class NamedObject {
public:
	NamedObject(const char* name, const T& value);
	NamedObject(const std::string& name, const T& value);

private:
	std::string nameValue;
	T objectValue;
};

NamedObject<int>nol("Smallest Prime Number", 2);
NamedObject<int >nol2(nol);//调用copy构造函数

template<typename T>
class NamedObject {
public:
	/*以下构造函数如今不再接受一个const名称，因为nameValue如今是个reference-to-non-const string，先前那个char*构造函数已经过去了，因为必须有个string可供指示*/

	NamedObject(std::string& name, const T& value);
					//假设并未声明operator=

private:
	std::string newDog("p");
	std::string oldDog("s");
	NamedObject<int>p(newDog, 2);
	NamedObject<int>s(oldDog, 36);

	p = s;
};

//c++并不允许“让reference改指向不同对象”

//如果打算在一个“内含reference成员”的class内支持赋值操作（assignment），必须定义copy assignment操作符

//如果某个base classes将copy assignment操作符声明为private，编译器将拒绝为其derived classes生成一个copy assignment操作符

//编译器哭暗自为class创建default构造函数、copy构造函数、copy assignment操作符，以及析构函数