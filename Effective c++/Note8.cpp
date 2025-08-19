//条款08：别让异常逃离析构函数

#include<iostream>
#include<string>
#include<vector>
using namespace std;

//C++并不禁止析构函数吐出异常，但并不鼓励这样做。

class Widget {
public:
	~Widget(){}//假设这个可能吐出一个异常
};

void doSomething() {
	std::vector<Widget>v;
}	//v在这里被自动销毁

//容器或array并非遇上麻烦的必要条件,只要析构函数吐出异常，即使并非使用容器或arrays，程序也可能过早结束或出现不明确行为。

class DBConnetion {
public:
	static DBConnetion create();//这个函数返回
								//DBConnetion对象
	void close();				//关闭联机，失败则抛出异常
};

class DBConn {//这个class用来管理DBConnetion对象
public:
	~DBConn() {//确保数据库连接总是会被关闭
		db.close();
	}
private:
	DBConnetion db;
};

{										//开启一个区块（block）
	DBConn dbc(DBConnetion::create());	//创建DBConnetion对象并
										//交给DBConn对象以便于管理
										//通过DBConn的接口
										//使用DBConnetion对象
}										//在区块结束点，DBConn对											象被销毁，因而自动
										//为DBConnetion对象调用close

//如果close抛出异常就结束程序，通常通过调用abort完成
DBConn::~DBConn() {
	try { db.close(); }
	catch (...) {
		//制作运转记录，记下对close的调用失败
		std::abort();
	}
}

//如果程序遭遇一个“于析构期间发生的错误”后无法继续执行，“强迫结束程序”是个合理选项。
//调用abort可以抢先制“不明确行为”于死地。

//吞下因调用close而发生的异常
DBConn::~DBConn() {
	try { db.close(); }
	catch (...) {
		//制作运转记录，记下对close的调用失败
	}
}

//一般而言，将异常吞掉是个坏主意，因为它压制了“某些动作失败”的重要信息！然而有些时候吞下异常也比负担“草率结束程序”或“不明确行为带来的风险”好。

class DBConn {
public:
	void close() {	//供客户使用的新函数
		db.close();
		closed = true;
	}

	~DBConn() {
		if (!close) {
			try {	//关闭连接（如果客户不那么做的话）
				db.close();
			}
			catch (...) {					//如果关闭动作失败，
				//制作运转记录，记下对close的调用失败	
								//记录下来并结束程序或吞下异常
			}
		}
	}
private:
	DBConnetion db;
	bool closed;
};

//如果某个操作可能在失败时抛出异常，而又存在某种需要必须处理该异常，那么这个异常必须来自析构函数以外的某个函数。

//析构函数绝对不要吐出异常。如果一个被析构函数调用的函数可能抛出异常，析构函数应该捕捉任何异常，然后吞下它们（不传播）或结束程序。

//如果客户需要对某个操作函数运行期间抛出的异常做出反应，那么class应该提供一个普通函数（而非在析构函数中）执行该操作。