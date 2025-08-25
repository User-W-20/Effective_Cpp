//条款14：在资源管理类中小心copying行为

#include<iostream>
#include<mutex>
#include<string>
using namespace std;

void lock(mutex* pm);//锁定pm所指的互斥器
void unlock(mutex* pm);//将互斥器解除锁定

//为确保绝不会忘记将一个被锁住的Mutex解锁，希望建立一个class用来管理机锁
//基本结构由RAII守则支配，“资源在构造期间获得，在析构期间释放”

class Lock {
public:
	explicit Lock(mutex* pm) :mutexPtr(pm) 
	{ lock(mutexPtr); }//获得资源

	~Lock() { unlock(mutexPtr); }//释放资源

private:
	mutex* mutexPtr;
};

mutex m;//定义需要的互斥锁
{
				//建立一个区块用来定义critical section
	Lock m1(&m);//锁定互斥锁
				//执行critical section内的操作
}				//在区块最末尾，自动解除互斥器锁定

Lock m11(&m);//锁定m
Lock m12(m11);//将m11复制到m12上。会发生什么？

//两种可能
//禁止复制。 很少能够合理拥有“同步化基础器物（synchronization primitives）的副本”  将copying操作声明为private

class Lock :private Uncopyable {//禁止复制
public:
	//...
};

//对底层资源祭出“引用计数法（reference-count）” 
/*通常只需内含一个shared_ptr成员变量，RAII classes便可实现出reference-counting copying行为。  但是shared_ptr的默认行为是“当引用次数为0时删除其所指物”。 当用mutex时，想要做的操作是解除锁定而非删除。*/

/*shared_ptr允许指定的“删除器（deleter），那是一个函数或函数对象（function object），当引用计数为0时便被调用（此机能不存在于auto_ptr-它总是将其指针删除）。”*/

class Lock {
public:
	//以某个mutex初始化shared_ptr并以unlock函数为删除器
	explicit Lock(mutex *pm):mutexPtr(pm,unlock){
		lock(mutexPtr.get());
	}
private:
	shared_ptr<mutex> mutexPtr;//使用shared_ptr替换raw pointer
};

/*复制底部资源
需要“资源管理类”的唯一理由是，当不需要某个副本时确保它被释放
复制资源管理对象时，进行的时“深度拷贝”
某些标准字符串类型是由“指向heap内存”的指针构成（那块被用来存放字符串的组成字符）。
当这样的字符串对象被复制，不论指针或其所指内存都会被制作出一个副本。*/

/*转移底部资源的拥有权
某些罕见场合下可能希望确保永远只有一个RAII对象指向一个未加工资源（raw resource），即使RAII对象被复制依然如此。
此时资源的拥有权会从被复制物转移到目标物。 auto_ptr
Copying函数（包括copy构造函数和copy assignment操作符）有可能被编译器自动构造出来，因此除非编译器所生成的版本做了想要做的事，否则得自己编写它们*/

//复制RAII对象必须一并复制它所管理的资源，所以资源的copying行为决定RAII对象的copying行为。

//普遍而常见的RAII class copying行为是：抑制copying、施行引用计数法（reference counting）。不过其他行为也可能被实现。