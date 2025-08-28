//条款17：以独立语句将newed对象置于智能指针

#include<iostream>
#include<memory>
using namespace std;

class Widget{};
int priority();
void processWidget(shared_ptr<Widget>pw, int priority());

processWidget(new Widget, priority());
//不能通过编译。 shared_ptr构造函数需要一个原始指针（raw pointer），但该构造函数是个explicit构造函数，无法进行隐式转换，将得自“newWidget”的原始指针转换为processWidget所要求的shared_ptr。

processWidget(shared_ptr<Widget>(new Widget), priority());
//上述调用可能泄露资源

//编译器产出调用码之前，必须首先核算即将被传递的各个实参
//上述第二实参只是一个单纯的对priority函数的调用
//但是第一实参shared_ptr<Widget>(new Widget)由两部分组成：
//执行“new Widget”表达式
//调用shared_ptr构造函数

//在调用之前，编译器必须创建代码，做三件事：
//调用priority
//执行“new Widget”表达式
//调用shared_ptr构造函数

//编译器执行的次序：“new Widget”一定执行于shared_ptr构造函数被调用之前，因为这个表达式的结果还要被传递做shared_ptr构造函数的一个实参，但对priority的调用则可以排在第一或第二或第三执行。

//如果对priority的调用导致异常
//在此情况下“new Widget”返回的指针将会丢失，因为它尚未被置入shared_tr内，后者是我们希望用来防止资源泄露的武器
//在对processWidget的调用过程中可能引发资源泄露，因为在“资源被创建（经由“new WIdget”）”和“资源被转换为资源管理对象”两个时间点之间有可能发生异常干扰。

//避免方法：使用分离语句
//在单独语句内以智能指针存储newed所得对象
shared_ptr<Widget>pw(new Widget);

//这个调用动作绝不至于造成资源泄露
processWidget(pw, priority());

//编译器对于“跨越语句的各项操作”没有重新排列的自由（只有在语句内它才拥有哪个自由度）。

//以独立语句将newed对象存储与（置入）智能指针内。如果不这样做，一旦异常被抛出，有可能导致难以察觉的资源泄露。