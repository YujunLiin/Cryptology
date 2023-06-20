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
//初始化产生公钥私钥
void Rsa::init(unsigned int n)
{
	srand(time(NULL));
	//产生大素数p、q
	_p = create_Prime(n, 10);
	_q = create_Prime(n, 10);
	//计算N
	N = _p * _q;
	//计算出欧拉数
	_ol = (_p - 1) * (_q - 1);
	//加密指数e
	create_Exp(_ol);
	//d
}
//生成长度为n的奇数
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
//判断素数
bool Rsa::isPrime(const Bigprime& n, const unsigned int k)
{
	assert(n != Bigprime::Zero);
	if (n == Bigprime::Two)
		return true;

	Bigprime n_1 = n - 1;
	Bigprime::bit b(n_1);//二进制位
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
//创建随机小数
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
//生成长度为n的素数
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
//从一个欧拉数中生成公钥、私钥指数
void Rsa::create_Exp(const Bigprime& ou)
{
	e = 65537;
	_d = e.extend_Euclid(ou);
}
//公钥加密
Bigprime Rsa::encrypt_ByPu(const Bigprime& m)
{
	return m.Mod_big_int(e, N);
}
//私钥解密
Bigprime Rsa::decode_ByPr(const Bigprime& c)
{
	return c.Mod_big_int(_d, N);
}
//私钥加密
Bigprime Rsa::encrypt_ByPr(const Bigprime& m)
{
	return decode_ByPr(m);
}
//公钥解密
Bigprime Rsa::decode_ByPu(const Bigprime& c)
{
	return encrypt_ByPu(c);
}