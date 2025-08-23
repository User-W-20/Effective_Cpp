//条款12：复制对象时勿忘其每一个成分

#include<iostream>
#include<string>
using namespace std;

//设计良好的面对对象系统（OO-systems）会将对象的内部封装起来，只留两个函数负责对象拷贝（复制）。

//编译器在必要的时候会为我们的classes创建copying函数，将被拷对象的所有成员变量都做一份拷贝。

void logCall(const string& funcName);//制造一个log entry

class Customer {
public:
	Customer(const Customer& rhs);
	Customer& operator=(const Customer& rhs);
private:
	string name;
};

Customer::Customer(const Customer& rhs) :name(rhs.name) {
	logCall("Customer copy constructor");//复制rhs的数据
}

Customer& Customer::operator=(const Customer& rhs) {
	logCall("Customer copy assignment operator");
	name = rhs.name;//复制rhs的数据
	return *this;
}

class Date{};
class Customer {
public:
	Customer(const Customer& rhs);
	Customer& operator=(const Customer& rhs);
private:
	string name;
	Date lastTransaction;
};

//这时候即有的copying函数执行的是局部拷贝（partial copy）：它们的确复制了顾客的name，但没有复制新添加的lastTransaction。

//如果为class添加一个成员变量，必须同时修改copying函数。

class PriorityCustomer :public Customer {//derived class
public:
	PriorityCustomer(const PriorityCustomer& rhs);
	PriorityCustomer& operator=(const PriorityCustomer& rhs);
private:
	int priority;
};

PriorityCustomer::PriorityCustomer(const PriorityCustomer& rhs)
	:priority(rhs.priority) {
	logCall("PriorityCustomer copy constructor");
}

PriorityCustomer&
PriorityCustomer::operator=(const PriorityCustomer& rhs) {
	logCall("PriorityCustomer copy assignment operator");
	priority = rhs.priority;
	return *this;
}

//任何时候只要承担起“为derived class撰写copying函数”的责任，必须很小心地也复制其base class成分。

PriorityCustomer::PriorityCustomer(const PriorityCustomer& rhs)
	:Customer(rhs), priority(rhs.priority) {
	logCall("PriorityCustomer copy constructor");
}

PriorityCustomer&
PriorityCustomer::operator=(const PriorityCustomer& rhs) {
	logCall("PriorityCustomer copy assignment operator");
	Customer::operator=(rhs);//对base class成分进行赋值动作
	priority = rhs.priority;
	return *this;
}

//1.复制所有local成员变量。
//2.调用所有base classes内的适当的copying函数。

//令copy assignment操作符调用copy构造函数是不合理的，因为这就像试图构造一个已经存在的对象。

//如果发现copy 构造函数和copy assignment操作符有相近的代码，消除重复代码的做法是，建立一个新的成员函数给两者调用。

//private，常被命名为init

//Copying函数应该确保复制“对象内的所有成员变量”及“所有base class成分”。

//不要尝试以某个copying函数实现另一个copying函数。应该将共同功能放进第三个函数中，并由两个copying函数共同调用。