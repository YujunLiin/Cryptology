#include<iostream>
#include<ctime>
#include"Prime.h"
#include"RSA.h"
using namespace std;

bool islegal(const string& str)
{//判断输入是否合法
	for (string::const_iterator it = str.begin(); it != str.end(); ++it)
		if (!isalnum(*it))//不是字母数字
			return false;
	return true;
}

bool Decode(Rsa& rsa)
{//解密
	string str;
	do
	{
		cout << "请输入密文（16进制）：";
		cin >> str;
	} while (cin && str.length() < 1);
	if (!cin || islegal(str) == false)
		return false;
	Bigprime c(str);
	Bigprime m = rsa.decode_ByPr(c);
	cout << "所输入的密文：" << c << endl << "解密后的明文：" << m << endl;
	return true;
}
//加密
bool Encry(Rsa& rsa, Bigprime& c)
{
	string str;
	do
	{
		cout << "请输入明文（16进制）：";
		cin >> str;
	} while (cin && str.length() < 1);
	if (!cin || islegal(str) == false)
		return false;
	Bigprime m(str);
	c = rsa.encrypt_ByPu(m);
	cout << "所输入的明文：" << m << endl << "加密后的密文：" << c << endl;
	return true;
}

void init(Rsa& rsa, int n)
{
	cout << "大素数选取中" << endl;
	long t1 = clock();
	rsa.init(n);
	long t2 = clock();
	cout << "选取完毕，计算出的公钥、私钥：" << endl;
	cout << rsa << endl;
	cout << "总用时" << (t2 - t1) / 1000 << "s。" << endl;
}

int main()
{
	Rsa rsa;
	Bigprime c;
	init(rsa, 256);//512位
	cout << "************开始进行RSA算法测试************" << endl;
	while (1)
	{
		cout << "请输入你要选择的功能编号：" << endl;
		cout << "1：加密，2：解密，3：退出" << endl;
		int a;
		cin >> a;
		switch (a)
		{
		case 1:
			Encry(rsa, c);//加密
			break;
		case 2:
			Decode(rsa);//解密
			break;
		case 3:
			return 0;
		}
	}
}