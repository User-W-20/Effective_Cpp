//����03��������ʹ��const
#include<iostream>
#include<vector>

char greeting[] = "Hello";
char* p = greeting;
const char* p = greeting;//const data
char* const p = greeting;//const pointer
const char* const p = greeting;//const pointer ,const data

//const�������Ǻ���ߣ���ʾ��ָ���ǳ���
//const�������Ǻ��ұߣ���ʾָ�������ǳ���

void f1(const Widget* pw);//f1���һ��ָ�룬ָ��һ��������Widget����
void f2(Widget const* pw);

//����һ��T* constָ�룬��ʾ�������������ָ��ͬ�Ķ�����������ָ��ֵ�ǿ��ԸĶ���
//���ϣ����������ָ�Ķ������ɱ��Ķ�����ϣ��STLģ��һ��const T*ָ�룩����Ҫconst_iterator

std::vector<int >vec;
const std::vector<int>::iterator iter = vec.begin();//iter��������T* const
*iter = 10;//û���⣬�ı�iter��ָ��
++iter;//����iter��const

std::vector<int>::const_iterator CIter = vec.begin();//CIter���������const T*
*CIter = 10;//����*CIter��const
++CIter;//û���⣺�ı�CIter

class Rational{};

const Rational operator*(const Rational& lhs, const Rational& rhs);

Rational a, b, c;
(a* b) = c;//��a*b�ĳɹ��ϵ���operator=

//const ��Ա����
//��constʵʩ�ڳ�Ա������Ŀ�ģ���Ϊ��ȷ�ϸó�Ա������������const��������

//1������ʹclass�ӿڱȽ����ױ���⡣
//2������ʹ������const���󡱳�Ϊ���ܡ�

//������Ա�������ֻ�ǳ����ԣ�constness����ͬ�����Ա�����

class TextBlock {
public:
	const char& operator[](std::size_t position)const { return text[position]; }//operator[]for const ����

	char& operator[](std::size_t position) { return text[position]; }////operator[]for non-const ����

private:
	std::string text;
};

TextBlock tb("Hello");
std::cout << tb[0];//non-const

const TextBlock ctb("World");
std::cout << ctb[0];//const

void print(const TextBlock& ctb) {//const
	std::cout << ctb[0];//const
}

std::cout << tb[0];//��non-const
tb[0] = 'x';//дnon-const
std::cout << ctb[0];//��const
ctb[0] = 'x';//����дconst

//non_const operator[]�ķ��������Ǹ�reference to char������char

//��������ķ��������Ǹ��������ͣ���ô�Ķ���������ֵ�����Ͳ��Ϸ�.

//bitwise constness(physical constness)��logical constness

//bitwise constness:��Ա����ֻ���ڲ��ı����֮�κγ�Ա������static���⣩ʱ�ſ���˵��const

class CTextBlock {
public:
	char& operator[](std::size_t position)const { return pText[position]; }//bitwise const����������ʵ���ʵ�

private:
	char* pText;
};

const CTextBlock cctb("Hello");//����һ����������
char* pc = &cctb[0];//����const operator[]ȡ��һ��ָ�룬ָ��cctb������
*pc = 'J';//cctb�������ˡ�Jello��

//logical constness:һ��const��Ա���������޸���������Ķ����ڵ�ĳЩbits����ֻ���ڿͻ�����ⲻ��������²ŵ���ˡ�

class CTextBlock {
public:
	std::size_t length()const;

private:
	char* pText;
	std::size_t textLength();//���һ�μ�����ı�����ĳ���
	bool lengthIsVaild;//Ŀǰ�ĳ����Ƿ���Ч
};

std::size_t CTextBlock::length()const {
	if (!lengthIsVaild) {
		textLength = std::strlen(pText);//������const��Ա�����ڲ��ܸ�ֵ��textLength��lengthIsValid
		lengthIsVaild = true;
	}
	return textLength;
}

//����취������C++��һ����const��صİڶ�����mutable��

class CTextBlock {
public:
	std::size_t length()const;
private:
	char* pText;
	mutable std::size_t textLength;//��Щ��Ա�����������ǻᱻ�޸ģ���ʹ��const��Ա������
	mutable bool lengthIsVaild;
};

std::size_t CTextBlock::length()const {
	if (!lengthIsVaild) {
		textLength = std::strlen(pText);
		lengthIsVaild = true;
	}
	return textLength;
}

//��const��non-const��Ա�����б����ظ�
class TextBlock {
public:
	const char& operator[](std::size_t position)const {
		//�߽����
		//�ռ����ݷ���
		//��������������
		return text[position];
	}

	 char& operator[](std::size_t position) {
		//�߽����
		//�ռ����ݷ���
		//��������������
		return text[position];
	}

private:
	std::string text;
};


//������ת��:��һ��������Ϊconst�Ķ���ͨ���ֶΡ�ǿ�ơ���Ϊ��const���Ӷ����������޸�

class TextBlock {
public:
	const char& operator[](std::size_t position)const {
		return text[position];
	}

	char& operator[](std::size_t postition) {//����ֻ����const op[]
		return
			const_cast<char&>(//��op[]����ֵ��constת��
static_cast<const TextBlock&>(*this)//Ϊ*this����const
				[postition]//����const op[]
);
	}
};

//��ĳЩ��������Ϊconst�ɰ������������������÷���const�ɱ�ʩ�������κ��������ڵĶ��󡢺��������������������͡���Ա������
//������ǿ��ʵʩbitwise constness�����ڱ�д����ʱӦʹ�á������ϵĳ����ԡ�(conceptual constness)
//��const��non-const��Ա��������ʵ�ʵȼ۵�ʵ��ʱ����non-const�汾����const�汾���Ա�������ظ���