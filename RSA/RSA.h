#pragma once
#include"Prime.h"
//
class Rsa
{
public:
	Rsa();
	~Rsa();
	void init(unsigned int n);//初始化，产生公私钥对
public:
	Bigprime encrypt_ByPu(const Bigprime& m);//私钥加密
	Bigprime decode_ByPr(const Bigprime& c);//公钥解密
	Bigprime encrypt_ByPr(const Bigprime& m);//公钥加密
	Bigprime decode_ByPu(const Bigprime& m);//私钥解密
private:
	Bigprime create_Odd_Num(unsigned int n);//生成长度为n的奇数
	bool isPrime(const Bigprime& a, const unsigned int k);//判断素数
	Bigprime create_Prime(unsigned int n, int it_cout);//生成长度为n的素数
	void create_Exp(const Bigprime& ou);//从一个欧拉数中生成公钥、私钥指数
	Bigprime create_Random_Small_Than(const Bigprime& a);//创建随机小数
	friend ostream& operator <<(ostream& out, const Rsa& rsa)//输出
	{
		out << "公钥N：" << rsa.N << "\n";
		out << "公钥e：" << rsa.e << "\n";
		out << "私钥p：" << rsa._p << "\n";
		out << "私钥q：" << rsa._q << "\n";
		out << "私钥d：" << rsa._d;
		return out;
	}
public:
	Bigprime e, N;//公钥
private:
	Bigprime _d;//私钥
	Bigprime _p, _q;//参数p、q
	Bigprime _ol;//欧拉数
};