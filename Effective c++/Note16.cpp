//条款16：成对使用new和delete时要采取相同形式

#include<iostream>
#include<string>
using namespace std;

string* stringArray = new string[100];
delete stringArray;

//程序行为不明确（未有定义）。
//最低限度，stringArray所含的100个string对象中的99个不太可能被适当删除，因为它们的析构函数很可能没被调用。

//当使用new（通过new动态生成一个对象），有两件事发生
//1、内存被分配出来（通过operator new的函数）
//2、针对此内存会有一个（或更多）构造函数被调用。

//当使用delete，也有两件事发生
// 针对此内存会有一个（或更多）析构函数被调用。，然后内存才被释放（通过operator delete的函数）

//单一对象的内存布局一般而言不同于数组的内存布局

//数组所用的内存通常还包括“数组大小”，以便delete知道需要调用多少次析构函数
//单一对象的内存则没有这笔记录

string* stringPtr1 = new string;
string* stringPtr2 = new string[100];

delete stringPtr1;//删除一个对象
delete stringPtr2[];//删除一个对象组成的数组

//如果调用new时使用[],必须在对应调用delete时也使用[]，如果在调用new时没有使用[]，那么也不应该在对应调用delete时使用[]

//每个人的地址有4行，每行是一个string
typedef string AddressLines[4];

//“new AddressLines”返回一个string*，就像new string[4]一样
string *pa1 = new AddressLines;

delete pa1;//行为未有定义
delete[] pa1;//很好

//尽量不要对数组形式做typedefs动作

//如果在new表达式中使用[]，必须在对应的delete表达式中也使用[]。如果在new表达式中不适用[]，一定不要在相应的delete表达式中使用[]。