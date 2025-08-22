//条款09：绝不在构造和析构过程中调用virtual函数

#include<iostream>
#include<string>
using namespace std;

class Transaction {//所有交易的base class
public:
	Transaction();
	//做出一份因类型不同而不同的日志记录（log entry）
	virtual void logTransaction()const = 0;
};

Transaction::Transaction() {//base class构造函数实现
	logTransaction();//最后动作是记录这笔交易
}

class BuyTransaction :public Transaction {//derived class
public:
	virtual void logTransaction()const;//日志（log）此类型交易
};

class SellTransaction :public Transaction {//derived class
public:
	virtual void logTransaction()const;//日志（log）此类型交易
};

BuyTransaction b;
//有一个BuyTransaction构造函数被调用，但是，首先Transaction构造函数一定会更早被调用。
//Transaction最后一行调用virtual函数logTransaction 才是引发问题的起点，这时被调用的logTransaction是Transaction内的版本而非BuyTransaction。

//base class构造期间virtual函数绝不会下降到derived class阶层。

//在base class 构造期间，virtual函数不是virtual函数

//在derived class对象的构造期间，对象的类型是base class 而不是derived class，不只virtual 函数会被编译器解析至（resolve to）base class，若使用运行期类型信息（runtime type information，例如dynamic_cast和typeid），也会把对象视为base class类型。

//也适用于析构函数

//一旦derived class析构函数开始执行，对象内的derived class成员变量便呈现未定义值，所以C++视它们仿佛不存在。

class Transaction {
public:
	Transaction()
	{
		init();//调用non-virtual
	}
	virtual void logTransaction()const = 0;
private:
	void init() {
		logTransaction();//调用virtual
	}
};

//和上个版本一样，但是比较潜藏并且暗中危害，因为它通常不会引发任何编译器和连接器的抱怨。

//确定构造和析构函数都没有（在对象被创建和被销毁期间）调用virtual函数，而它们的所有函数也都服从同一约束。

//在class Transaction内将logTransaction函数改为non-virtual，然后要求derived class构造函数传递必要信息给Transaction构造函数，而后那个构造函数便可安全地调用non-virtual logTransaction

class Transaction {
public:
	explicit Transaction(const string& logInfo);
	//如今是个non-virtual函数
	void logTransaction(const string& logInfo)const;
};

Transaction::Transaction(const string& logInfo) {
	//如今是个non-virtual函数
	logTransaction(logInfo);
}

class BuyTransaction :public Transaction {
public:
	//将log信息传给base class构造函数
	BuyTransaction(...):
		Transaction(createLogString(...)){... }

private:
	static string createLogString(...);
};

//由于无法使用virtual函数从base classes向下调用，在构造期间，可以借由“令derived classes将必要的构造信息向上传递至base class构造函数”替换之而加以弥补。

//在构造和析构期间不要调用virtual函数，因为这类调用从不下降至derived class（比起当前执行构造函数和析构函数的那层）。

