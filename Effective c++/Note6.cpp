//����06��������ʹ�ñ������Զ����ɵĺ������͸���ȷ�ܾ�

#include<iostream>

class HomeForSale{};

HomeForSale h1;
HomeForSale h2;
HomeForSale h3(h1);//��ͼ����h1-����ͨ������
h1 = h2;//��ͼ����h2-Ҳ����ͨ������

//ͨ�������ϣ��class֧��ĳһ�ض����ܣ�ֻҪ��������Ӧ�������С�
//��������Զ�copy���캯����copy assignment��������������
//��Ϊ������������ǣ�����������������

//���б����������ĺ�������public

//����Ա��������Ϊprivate���ҹ��ⲻʵ������

class HomeForSale {
public:

private:
	HomeForSale(const HomeForSale&);//ֻ������
	HomeForSale& operator=(const HomeForSale&);
};

class Uncopyable {
protected:
	Uncopyable(){}//����derived�����������
	~Uncopyable(){}

private:
	Uncopyable(const Uncopyable&);
	Uncopyable& operator=(const Uncopyable&);
};

class HomeForSale :private Uncopyable {//class��������
										//copy���캯����
};									//copy assign������

//Ϊ���ر������Զ������ԣ��ṩ�Ļ��ܣ��ɽ���Ӧ�ĳ�Ա��������Ϊprivate���Ҳ���ʵ�֡�ʹ����Uncopyable������base classҲ��һ��������