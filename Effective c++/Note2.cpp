//����02��������const��enum��inline�滻#define
#include<iostream>
#define ASPECT_RATIO 1.653

/*ASPECT_RATIOҲ���δ��������������
Ҳ���ڱ�������ʼ����Դ��֮ǰ�ͱ�Ԥ������������*/

//�Գ����滻�����ĺ꣨#define��

const double AspectRatio = 1.653;//��д����ͨ�����ں꣬��˸ı�д��

//�Գ����滻#defineʱ���������������
//1�����峣��ָ��
//��ͷ�ļ��ڶ���һ��������char*base�ַ���������дconst����
const char* const authorName = "Scitt Meyers";

const std::string authorName("Scitt Meyers");

//2��classר������
class GamePlayer {
private:
	static const int NumTurns = 5;//��������ʽ
	int scores[NumTurns];//ʹ�øó���
};

/*��������Ǹ�classר����������static��Ϊ��������,�������⴦��
ֻҪ��ȡ���ǵĵ�ַ�������������ʹ�����Ƕ������ṩ����ʽ*/

//const int GamePlayer::NumTurns;

//#define����������������classר��������Ҳ�����ṩ�κη�װ��

class CostEstimate {
private:
	static const double FudgeFactor;//static class ��������
};//.h

const double CostEstimate::FudgeFactor = 1.35;//.cpp

//Ψһ���⣺��class�����ڼ���Ҫһ��class����ֵ������������ֱ����ڱ�������֪������Ĵ�С����
//��һ������������أ�������static������class��������ɡ�in class ��ֵ�趨��,�ɸ��á�the enum hack������������
//���ۻ�������һ������ö�����͵���ֵ��Ȩ��ints��ʹ��

class GamePlayer {
private:
	enum {NumTurns=5};//"the enum hack"-��NumTurns��Ϊ5��һ���Ǻŷ���
	int scores{ NumTurns };
};

//enum hack����Ϊĳ����Ƚ���#define������const��

//��������ñ��˻��һ��pointer��referenceָ��ĳ������������enum���԰���ʵ�����Լ��

//enum hack ��template mateprogramming��ģ��Ԫ��̣��Ļ�������

//��a��b�Ľϴ�ֵ����f
#define CALL_WITH_MAX (a,b) f((a)>(b)?(a):(b))

int a = 5, b = 0;
CALL_WITH_MAX(++a, b);//a���ۼӶ���
CALL_WITH_MAX(++a, b + 10);//a���ۼ�һ��

template<typename T>
inline void callWithMax(const T& a, const T& b)
{
	f(a > b ? a : b);//pass by reference-to-const
}

//���ڵ��������������const�����enums���#defines
//�������ƺ����ĺ꣨macros������ø���inline�����滻#defines

