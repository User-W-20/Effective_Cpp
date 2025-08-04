//����05���˽�C++ĬĬ��д��������Щ����
#include<iostream>
//���û�������������ͻ�Ϊ���������������汾�ģ�copy���캯����copy assignment ������������������
//���û�������κι��캯����Ҳ������һ��default���캯��������public��inline��

class Empty{};

class Empty {
public:
	Empty(){}//default���캯��
	Empty(const Empty&rhs){}//copy
	~Empty(){}//����

	Empty operator=(const Empty& rhs){}//copy assignment
};

Empty e1;//default���캯��
		//����
Empty e2(e1);//copy

e2 = e1;//copy assignment

//���������������������Ǹ�non-virtual���������class��base class����������virtual���������������������������������ԣ�virtualness����Ҫ����base class��

//copy��copy assignment�������������İ汾ֻ�ǵ�������Դ�����ÿһ��non_static��Ա����������Ŀ�����

template<typename T>
class NamedObject {
public:
	NamedObject(const char* name, const T& value);
	NamedObject(const std::string& name, const T& value);

private:
	std::string nameValue;
	T objectValue;
};

NamedObject<int>nol("Smallest Prime Number", 2);
NamedObject<int >nol2(nol);//����copy���캯��

template<typename T>
class NamedObject {
public:
	/*���¹��캯������ٽ���һ��const���ƣ���ΪnameValue����Ǹ�reference-to-non-const string����ǰ�Ǹ�char*���캯���Ѿ���ȥ�ˣ���Ϊ�����и�string�ɹ�ָʾ*/

	NamedObject(std::string& name, const T& value);
					//���貢δ����operator=

private:
	std::string newDog("p");
	std::string oldDog("s");
	NamedObject<int>p(newDog, 2);
	NamedObject<int>s(oldDog, 36);

	p = s;
};

//c++����������reference��ָ��ͬ����

//���������һ�����ں�reference��Ա����class��֧�ָ�ֵ������assignment�������붨��copy assignment������

//���ĳ��base classes��copy assignment����������Ϊprivate�����������ܾ�Ϊ��derived classes����һ��copy assignment������

//�������ް���Ϊclass����default���캯����copy���캯����copy assignment���������Լ���������