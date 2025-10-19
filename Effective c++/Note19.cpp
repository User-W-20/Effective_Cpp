//条款19：设计class犹如设计type

//当定义一个新class，也就定义了一个新type
//应该带着和“语言设计者当初设计语言内置类型时”一样的谨慎来研讨class的设计

//新type的对象应该如何被创建和销毁？
//会影响到class的构造函数和析构函数以及内存分配函数和释放函数的设计

//对象的初始化和对象的赋值该有什么样的区别？
//决定构造函数和赋值操作符的行为，以及其间的差异

//新type的对象如果被passed by value，意味着什么?
//copy构造函数用来定义一个type的pass-by-value该如何实现

//什么是新type的“合法值”？
//对class的成员变量而言，通常只有某些数值集是有效的。
//那些数值集决定了class必须维护的约束条件（invariants），也就决定了成员函数（特别是构造函数、赋值操作符、和所谓“setter”函数）必须进行的错误检查工作
//也影响函数抛出的异常、以及（极少被使用的）函数异常明确细列（exception specifications）

//你的新type需要配合某个继承图系（inheritance graph）吗？
//如果继承来自某些既有classes，就受到那些classes的设计的束缚，特别是受到“它们的函数是virtual或non-virtual”的影响
//如果允许其他classes继承你的class，那会影响你所声明的函数-尤其是析构函数-是否为virtual

//你的新type需要什么样的转换？
//如果希望允许类型T1被隐式转换成类型T2，就必须在class T1内写一个类型转换函数（operator T2）或在class T2内写一个non-explicit-one-argument（可被单一实参调用）的构造函数
//如果只允许explicit构造函数存在，就得写出专门负责执行转换的函数，且不得为类型转换操作符（type conversion operators）或non-explicit-one-argumnet构造函数

//什么样的操作符和函数对此新type而言是合理的？
//决定将为class声明哪些函数，其中某些该是member函数，某些则否

//什么样的标准函数应该驳回？
//必须声明为private的

//谁该采用新type的成员？
//决定哪个成员为public，哪个为protected，哪个为private。
//也帮助决定哪一个classes和/或functions应该是friends，以及将它们嵌套于另一个之内是否合理

//什么是新type的“未声明接口”（undeclared interface）？
//对效率、异常安全性以及资源运用提供何种保证？
//在这些方面提供的保证将为class实现代码加上相应的约束条件

//你的新type有多么一般化？
//或许其实并非定义一个新type，而是定义一整个types家族
//如果是这样，就不该定义一个新class，而是定义一个新的class template

//你真的需要一个新type吗？
//如果只是定义新的derived class以便为既有的class添加功能，那么说不定单纯定义一个或多个non-member函数或templates，更能够到达目的

//Class的设计就是type的设计。在定义一个新type之前，请确定已经考虑过上述的所有问题