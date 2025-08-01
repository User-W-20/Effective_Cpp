//����04��ȷ������ʹ��ǰ���ȱ���ʼ��
#include<iostream>
#include<string>
#include<list>

int x;
//��ĳЩ�ﾳ��x����֤����ʼ����Ϊ0�������������ﾳ��ȴ����֤

class Point {
	int x, y;
};

Point x;
//p�ĳ�Ա������ʱ�򱻳�ʼ����Ϊ0������ʱ�򲻻ᡣ

//��ȡδ��ʼ����ֵ�ᵼ�²���ȷ����Ϊ��

//��Ѵ���취����Զ��ʹ�ö���֮ǰ�Ƚ�����ʼ����

int x = 0;//��int�����ֹ���ʼ��
const char* text = "A C-style string";//��ָ������ֹ���ʼ��
double d;
std::cin >> d;//�Զ�ȡinput stream�ķ�ʽ��ɳ�ʼ��

//��������������κ�������������ʼ���������ڹ��캯����
//ȷ��ÿһ�����캯�����������ÿһ����Ա��ʼ��

//�������ֵ�ͳ�ʼ��
class PhoneNumber{};
class ABEntry {
public:
	ABEntry(const std::string& name, const std::string& address, const std::list<PhoneNumber>& phones);

private:
	std::string theName;
	std::string theAddress;
	std::list<PhoneNumber> thePhones;
	int numTimesConsuted;
};

ABEntry::ABEntry(const std::string& name, const std::string& address, const std::list<PhoneNumber>& phones) {
	theName = name;//��Щ���Ǹ�ֵ
	theAddress = address;//���ǳ�ʼ��
	thePhones = phones;
	numTimesConsuted = 0;
}

//ʹ��member initialization list �滻��ֵ����

ABEntry::ABEntry(const std::string& name, const std::string& address, const std::list<PhoneNumber>& phones):theName(name),theAddress(address),thePhones(phones),numTimesConsuted(0){}

ABEntry::ABEntry()
	:theName(),//����theName��default���캯��
	theAddress(),//ΪtheAddess�����ƶ���
	thePhones(),//ΪthePhones�����ƶ���
	numTimesConsuted(0)//numTimesConsuted��ʽ��ʼ��Ϊ0
{}

//��ʹ��Եĳ�Ա���������������ͣ����ʼ���븳ֵ�ĳɱ���ͬ����Ҳһ����ʹ�ó�ֵ��

//��Ա������const��reference����һ����Ҫ��ֵ�����ܱ���ֵ

//����ʹ�ó�Ա��ֵ��

//�����ɸ�ֵ������ɵ�α��ʼ����ͨ����Ա��ֵ����ɵ�������ʼ��ͨ�����ӿ�ȡ

//c++����ʮ�̶ֹ��ġ���Ա��ʼ������

//non-local static����ָ�����ں����ⲿ�������ռ��������ж����static�������ڳ�������ʱ���졢����ʱ�������������������������ڵľ�̬�洢�ڡ�

//local static���󣺶����ں����ڲ���static����

//C++�ԡ������ڲ�ͬ���뵥Ԫ�ڵ�non-local static���󡱵ĳ�ʼ����������ȷ���塣

class FileSystem {
public:
	std::size_t numDisks()const;
};

extern FileSystem tfs;//Ԥ�����ͻ�ʹ�õĶ���
					//tfs����"the file system"

class Directory {
public:
	Directory(params);
};
Directory::Directory(params) {
	std::size_t disks = tfs.numDisks();//ʹ��tfs����
}

Directory tempDir(params);//Ϊ��ʱ�ļ���������Ŀ¼

//�������ǵĳ�ʼ�������൱����

//������뵥Ԫ�ڵ�non-local static�����ɡ�ģ����ʽ���ֻ���implicit template instantiations���γ�

//��ÿ��non-local static����ᵽ�Լ���ר�������ڣ��ö����ڴ˺����ڱ�����Ϊstatic������Щ��������һ��referenceָ���������Ķ���

//non-local static����local static�����滻��

//C++��֤�������ڵ�local static������ڡ��ú����������ڼ䡱���״����ϸö���Ķ���ʽ��ʱ����ʼ��

//�����δ����non-local static����ġ����溯�������;�������������������ɱ�

class FileSystem{};
FileSystem tfs()//�����滻tfs����
{					//��FileSystem class�п����Ǹ�static
	static FileSystem fs;//���岢��ʼ��һ��local static����
	return fs;//����һ��referenceָ����������
}

class Directory{};
Directory::Directory(params) {//ԭ����reference to tfs
	std::size_t disks = tfs().numDisks();//���ڸ�Ϊtfs����
}

Directory& tempDir() {//�����滻tempDir����
				//��Directory class�п����Ǹ�static
	static Directory td; //���岢��ʼ��local static����
	return td;//����һ��referenceָ����������
}

//�ڳ���ĵ��߳������׶��ֹ���������reference-returning����������������ʼ���йصġ��������ơ�

//����reference-returning������ֹ����ʼ���������⡱��ǰ������������һ���Զ�����Ժ���ĳ�ʼ������

//�����ڶ����ʼ��֮ǰ�����ʹ������
//1���ֹ���ʼ��������non-member����
//2��ʹ�ó�Ա��ֵ�жԸ��������гɷ�
//3���ڡ���ʼ������ȷ���ԡ���Χ�¼�ǿ���

//Ϊ���ö�������ֹ���ʼ������ΪC++����֤��ʼ������
//���캯�����ʹ�ó�Ա��ֵ�У�����Ҫ�ڹ��캯��������ʹ�ø�ֵ��������ֵ���г��ĳ�Ա���������������Ӧ�ú�������class�е�����������ͬ��
//Ϊ���������뵥Ԫ�ĳ�ʼ���������⣬����local static�����滻non-local static ����