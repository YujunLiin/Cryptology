#pragma once
#include"Prime.h"
//
class Rsa
{
public:
	Rsa();
	~Rsa();
	void init(unsigned int n);//��ʼ����������˽Կ��
public:
	Bigprime encrypt_ByPu(const Bigprime& m);//˽Կ����
	Bigprime decode_ByPr(const Bigprime& c);//��Կ����
	Bigprime encrypt_ByPr(const Bigprime& m);//��Կ����
	Bigprime decode_ByPu(const Bigprime& m);//˽Կ����
private:
	Bigprime create_Odd_Num(unsigned int n);//���ɳ���Ϊn������
	bool isPrime(const Bigprime& a, const unsigned int k);//�ж�����
	Bigprime create_Prime(unsigned int n, int it_cout);//���ɳ���Ϊn������
	void create_Exp(const Bigprime& ou);//��һ��ŷ���������ɹ�Կ��˽Կָ��
	Bigprime create_Random_Small_Than(const Bigprime& a);//�������С��
	friend ostream& operator <<(ostream& out, const Rsa& rsa)//���
	{
		out << "��ԿN��" << rsa.N << "\n";
		out << "��Կe��" << rsa.e << "\n";
		out << "˽Կp��" << rsa._p << "\n";
		out << "˽Կq��" << rsa._q << "\n";
		out << "˽Կd��" << rsa._d;
		return out;
	}
public:
	Bigprime e, N;//��Կ
private:
	Bigprime _d;//˽Կ
	Bigprime _p, _q;//����p��q
	Bigprime _ol;//ŷ����
};