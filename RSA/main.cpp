#include<iostream>
#include<ctime>
#include"Prime.h"
#include"RSA.h"
using namespace std;

bool islegal(const string& str)
{//�ж������Ƿ�Ϸ�
	for (string::const_iterator it = str.begin(); it != str.end(); ++it)
		if (!isalnum(*it))//������ĸ����
			return false;
	return true;
}

bool Decode(Rsa& rsa)
{//����
	string str;
	do
	{
		cout << "���������ģ�16���ƣ���";
		cin >> str;
	} while (cin && str.length() < 1);
	if (!cin || islegal(str) == false)
		return false;
	Bigprime c(str);
	Bigprime m = rsa.decode_ByPr(c);
	cout << "����������ģ�" << c << endl << "���ܺ�����ģ�" << m << endl;
	return true;
}
//����
bool Encry(Rsa& rsa, Bigprime& c)
{
	string str;
	do
	{
		cout << "���������ģ�16���ƣ���";
		cin >> str;
	} while (cin && str.length() < 1);
	if (!cin || islegal(str) == false)
		return false;
	Bigprime m(str);
	c = rsa.encrypt_ByPu(m);
	cout << "����������ģ�" << m << endl << "���ܺ�����ģ�" << c << endl;
	return true;
}

void init(Rsa& rsa, int n)
{
	cout << "������ѡȡ��" << endl;
	long t1 = clock();
	rsa.init(n);
	long t2 = clock();
	cout << "ѡȡ��ϣ�������Ĺ�Կ��˽Կ��" << endl;
	cout << rsa << endl;
	cout << "����ʱ" << (t2 - t1) / 1000 << "s��" << endl;
}

int main()
{
	Rsa rsa;
	Bigprime c;
	init(rsa, 256);//512λ
	cout << "************��ʼ����RSA�㷨����************" << endl;
	while (1)
	{
		cout << "��������Ҫѡ��Ĺ��ܱ�ţ�" << endl;
		cout << "1�����ܣ�2�����ܣ�3���˳�" << endl;
		int a;
		cin >> a;
		switch (a)
		{
		case 1:
			Encry(rsa, c);//����
			break;
		case 2:
			Decode(rsa);//����
			break;
		case 3:
			return 0;
		}
	}
}