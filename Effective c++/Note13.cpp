//条款13：以对象管理资源
#include<iostream>
#include<string>
#include<memory>
using namespace std;

class Investment{};//“投资类型”继承体系中的root class

//返回指针，指向Investment继承体系内的动态分配对象，调用者有责任删除它
Investment* createrInvestment();

void f() {
	Investment* pInv = createrInvestment();//调用factory函数
	//...
	delete pInv;//释放pInv所指对象

}
//在某些情况下f可能无法删除它来自createrInvestment的投资对象
//如...区域中过早的return语句、...区域中的语句抛出异常

//把资源放进对象内，便可以依赖c++的“析构函数自动调用机制”确保资源被释放。

//auto_ptr 析构函数自动对其所指对象调用delete

void f() {
	//调用factory函数，一如既往地使用pInv，经由auto_ptr的析构函数自动删除pInv
	std::auto_ptr<Investment>pInv(createrInvestment());
}

/*获得资源后立即放进管理对象（managing object）内
"以对象管理资源"的观念常被称为“资源取得时机便是初始化时机（Resource Acquisition Is Initialization；RAII）”
几乎总是在获得一笔资源后于同一语句内以初始化某个管理对象，有时候获得的资源被拿来赋值（而非初始化）某个管理对象*/

/*管理对象（managing object）运用析构函数确保资源被释放 */

//别让多个auto_ptr同时指向同一对象

//auto_ptr不寻常的性质：若通过copy构造函数或copy assignment 操作符复制它们，它们会变成null，而复制所得的指针将取得资源的唯一拥有权！

//pInv1指向createInvestment返回物
std::auto_ptr<Investment>pInv1(createrInvestment());

//现在pInv2指向对象，pInv1被设为null
std::auto_ptr<Investment>pInv2(pInv1);

//现在pInv1指向对象，pInv2被设为null
pInv1 = pInv2;

//“受auto_ptrs管理的资源必须绝对没有一个以上的auto_ptr同时指向它”，意味auto_ptrs并非管理动态分配资源的神兵利器。

/*替代方案：引用计数型智能指针（reference-counting smart pointer；RCSP）
持续追踪共有多少对象指向某笔资源，并在无人指向它时自动删除该资源*/

void f() {
	//调用factory函数，使用pInv一如既往
	std::tr1::shared_ptr<Investment>pInv(createrInvestment());

	//经由shared_ptr析构函数自动删除pInv
}

void f() {
	//pInv1指向createrInvestment返回物
	std::shared_ptr<Investment>pInv1(createrInvestment());

	//pInv1和pInv2指向同一个对象
	std::shared_ptr<Investment>pInv2(pInv1);

	//同上
	pInv1 = pInv2;
}//pInv1和pInv2被销毁，它们所指的对象也就被自动销毁

//坏主意！会用上错误的delete形式
std::auto_ptr<string>aps(new string[10]);
//相同问题
std::shared_ptr<int>sp1(new int[1024]);

//为防止资源泄露，使用RAII对象，它们在构造函数中获得并在析构函数中释放资源。

//两个常被使用的RAII classes分别是tr1::shared_ptr和auto_ptr。前者通常是较佳选择，因为其copy行为比较直观。若选择auto_ptr，复制动作会使它（被复制物）指向null。