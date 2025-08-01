//条款04：确定对象被使用前已先被初始化
#include<iostream>
#include<string>
#include<list>

int x;
//在某些语境下x被保证被初始化（为0），但在其他语境下却不保证

class Point {
	int x, y;
};

Point x;
//p的成员变量有时候被初始化（为0），有时候不会。

//读取未初始化的值会导致不明确的行为。

//最佳处理办法：永远在使用对象之前先将它初始化。

int x = 0;//对int进行手工初始化
const char* text = "A C-style string";//对指针进行手工初始化
double d;
std::cin >> d;//以读取input stream的方式完成初始化

//内置类型意外的任何其他东西，初始化责任落在构造函数上
//确保每一个构造函数都将对象的每一个成员初始化

//别混淆赋值和初始化
class PhoneNumber{};
class ABEntry {
public:
	ABEntry(const std::string& name, const std::string& address, const std::list<PhoneNumber>& phones);

private:
	std::string theName;
	std::string theAddress;
	std::list<PhoneNumber> thePhones;
	int numTimesConsuted;
};

ABEntry::ABEntry(const std::string& name, const std::string& address, const std::list<PhoneNumber>& phones) {
	theName = name;//这些都是赋值
	theAddress = address;//而非初始化
	thePhones = phones;
	numTimesConsuted = 0;
}

//使用member initialization list 替换赋值操作

ABEntry::ABEntry(const std::string& name, const std::string& address, const std::list<PhoneNumber>& phones):theName(name),theAddress(address),thePhones(phones),numTimesConsuted(0){}

ABEntry::ABEntry()
	:theName(),//调用theName的default构造函数
	theAddress(),//为theAddess做类似动作
	thePhones(),//为thePhones做类似动作
	numTimesConsuted(0)//numTimesConsuted显式初始化为0
{}

//即使面对的成员变量属于内置类型（其初始化与赋值的成本相同），也一定得使用初值列

//成员变量是const或reference，就一定需要初值，不能被赋值

//总是使用成员初值列

//比起由赋值操作完成得伪初始化，通过成员初值列完成的真正初始化通常更加可取

//c++有着十分固定的“成员初始化次序”

//non-local static对象：指的是在函数外部或命名空间作用域中定义的static对象，它在程序启动时构造、结束时析构，具有整个程序生命周期的静态存储期。

//local static对象：定义在函数内部的static对象

//C++对“定义于不同编译单元内的non-local static对象”的初始化次序并无明确定义。

class FileSystem {
public:
	std::size_t numDisks()const;
};

extern FileSystem tfs;//预备给客户使用的对象；
					//tfs代表"the file system"

class Directory {
public:
	Directory(params);
};
Directory::Directory(params) {
	std::size_t disks = tfs.numDisks();//使用tfs对象
}

Directory tempDir(params);//为临时文件而做出的目录

//决定它们的初始化次序相当困难

//多个编译单元内的non-local static对象经由“模板隐式具现化，implicit template instantiations”形成

//将每个non-local static对象搬到自己的专属函数内（该对象在此函数内被声明为static）。这些函数返回一个reference指向它所含的对象

//non-local static对象被local static对象替换了

//C++保证，函数内的local static对象堆在“该函数被调用期间”“首次遇上该对象的定义式”时被初始化

//如果从未调用non-local static对象的“仿真函数”，就绝不会引发构造和析构成本

class FileSystem{};
FileSystem tfs()//用来替换tfs对象
{					//在FileSystem class中可能是个static
	static FileSystem fs;//定义并初始化一个local static对象
	return fs;//返回一个reference指向上述对象
}

class Directory{};
Directory::Directory(params) {//原来的reference to tfs
	std::size_t disks = tfs().numDisks();//现在改为tfs（）
}

Directory& tempDir() {//用来替换tempDir对象
				//在Directory class中可能是个static
	static Directory td; //定义并初始化local static对象
	return td;//返回一个reference指向上述对象
}

//在程序的单线程启动阶段手工调用所有reference-returning函数，这可消除与初始化有关的“竞速形势”

//运用reference-returning函数防止“初始化次序问题”，前提是其中有着一个对对象而言合理的初始化次序。

//避免在对象初始化之前过早地使用它们
//1、手工初始化内置型non-member对象
//2、使用成员初值列对付对象所有成分
//3、在“初始化次序不确定性”氛围下加强设计

//为内置对象进行手工初始化，因为C++不保证初始化他们
//构造函数最好使用成员初值列，而不要在构造函数本体内使用赋值操作。初值列列出的成员变量，其排序次序应该和它们在class中的声明次序相同。
//为免除“跨编译单元的初始化次序”问题，请以local static对象替换non-local static 对象。