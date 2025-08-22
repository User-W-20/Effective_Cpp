//条款11：在operator=中处理“自我赋值”

class Widget{};
Widget w;
w = w;//赋值给自己

a[i] = a[j];//潜在的自我赋值

*px = *py;//潜在的自我赋值

//“别名”：“有一个以上的方法指称（指涉）某对象”。

//一般而言如果某段代码操作pointer或references而它们被用来“指向多个相同类型的对象”，就需要考虑这些对象是否为同一个。

class Base{};
class Derived:public Base{};
void doSomething(const Base& rb, Derived* pd);//rb和*pd有可能其实是同一对象

//如果尝试自行管理资源，可能会掉进“在停止使用资源之前意外释放了它”的陷阱。

class Bitmap{};
class Widget {
private:
	Bitmap* pb;//指针，指向一个从heap分配而得的对象
};

Widget & 
Widget::operator=(const Widget& rhs) {//一份不安全的operator实现版本
	delete pb;//停止使用当前的bitmap
	pb = new Bitmap(*rhs.pb);//使用rhs's bitmap的副本
	return *this;
}

//这里的自我赋值问题是，operator=函数内的*this（赋值的目的端）和rhs有可能是同一个对象。

//欲阻止这种错误，传统做法是由operator=最前面的一个“证同测试（identity test）”达到“自我赋值”的检验目的。

Widget& Widget::operator=(const Widget& rhs) {
	if (this == &rhs)return *this;//证同测试（identity test）
								//如果是自我赋值，就不做任何事
	delete pb;
	pb = new Bitmap(*rhs.pb);
	return *this;
}

//让operator=具备“异常安全性”往往自动获得“自我赋值安全”的回报

Widget& Widget::operator=(const Widget& rhs) {
	Bitmap* pOrig = pb;//记住原先的pb
	pb = new Bitmap(*rhs.pb);//令pb指向*pb的一个副本
	delete pOrig;//删除原先的pb
	return *this;
}

//copy and swap 技术

class Widget {
	void swap(Widget& rhs);//交换*this和rhs的数据
};

Widget& Widget::operator=(const Widget& rhs) {
	Widget temp(rhs);//为rhs数据制作一份副本
	swap(temp);//将*this数据和上述副本的数据交换
	return *this;
}

//1.某class的copy assignment操作符可能被声明为“以by value方式接受实参”
//2.以by value方式传递东西会造成一份副本


//rhs是被传递对象的一份副本
Widget& Widget::operator=(Widget rhs) {//这里是pass by value
	swap(rhs);	//将*this数据和上述副本的数据交换。
	return *this;
}

//确保当前对象自我赋值时operator=有良好行为。其中技术包括比较“来源对象”和“目标对象”的地址、精心周到的语句顺序、以及copy-and-swap。

//确定任何函数如果操作一个以上的对象，而其中多个对象是同一个对象时，其行为仍然正确。