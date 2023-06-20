#include "RSA.h"
#include<iostream>
#include<sstream>
#include<ctime>
#include<cstdlib>
using namespace std;
Rsa::Rsa()
{
}

Rsa::~Rsa()
{
}
//��ʼ��������Կ˽Կ
void Rsa::init(unsigned int n)
{
	srand(time(NULL));
	//����������p��q
	_p = create_Prime(n, 10);
	_q = create_Prime(n, 10);
	//����N
	N = _p * _q;
	//�����ŷ����
	_ol = (_p - 1) * (_q - 1);
	//����ָ��e
	create_Exp(_ol);
	//d
}
//���ɳ���Ϊn������
Bigprime Rsa::create_Odd_Num(unsigned int n)
{
	n = n / 4;
	static unsigned char hex_table[] = { '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F' };
	if (n)
	{
		ostringstream oss;
		for (std::size_t i = 0; i < n - 1; ++i)
			oss << hex_table[rand() % 16];
		oss << hex_table[1];
		string str(oss.str());
		return Bigprime(str);
	}
	else
		return Bigprime::Zero;
}
//�ж�����
bool Rsa::isPrime(const Bigprime& n, const unsigned int k)
{
	assert(n != Bigprime::Zero);
	if (n == Bigprime::Two)
		return true;

	Bigprime n_1 = n - 1;
	Bigprime::bit b(n_1);//������λ
	if (b.at(0) == 1)
		return false;

	for (std::size_t t = 0; t < k; ++t)
	{
		Bigprime a = create_Random_Small_Than(n_1);
		Bigprime d(Bigprime::One);
		for (int i = b.size() - 1; i >= 0; --i)
		{
			Bigprime x = d;
			d = (d * d) % n;
			if (d == Bigprime::One && x != Bigprime::One && x != n_1)
				return false;

			if (b.at(i))
			{
				assert(d != Bigprime::Zero);
				d = (a * d) % n;
			}
		}
		if (d != Bigprime::One)
			return false;
	}
	return true;
}
//�������С��
Bigprime Rsa::create_Random_Small_Than(const Bigprime& a)
{
	unsigned long t = 0;
	do
	{
		t = rand();
	} while (t == 0);

	Bigprime mod(t);
	Bigprime r = mod % a;
	if (r == Bigprime::Zero)
		r = a - Bigprime::One;
	return r;
}
//���ɳ���Ϊn������
Bigprime Rsa::create_Prime(unsigned int n, int it_count)
{
	assert(it_count > 0);
	Bigprime res = create_Odd_Num(n);
	while (!isPrime(res, it_count))
	{
		res.add(Bigprime::Two);
	}
	return res;
}
//��һ��ŷ���������ɹ�Կ��˽Կָ��
void Rsa::create_Exp(const Bigprime& ou)
{
	e = 65537;
	_d = e.extend_Euclid(ou);
}
//��Կ����
Bigprime Rsa::encrypt_ByPu(const Bigprime& m)
{
	return m.Mod_big_int(e, N);
}
//˽Կ����
Bigprime Rsa::decode_ByPr(const Bigprime& c)
{
	return c.Mod_big_int(_d, N);
}
//˽Կ����
Bigprime Rsa::encrypt_ByPr(const Bigprime& m)
{
	return decode_ByPr(m);
}
//��Կ����
Bigprime Rsa::decode_ByPu(const Bigprime& c)
{
	return encrypt_ByPu(c);
}