#include "AES.h"
#include<iostream>
using namespace std;
void AsciiToHex(unsigned char* pAscii, unsigned char* pHex, int nLen);//将ASCII码表示的十六进制字符串转换为十六进制字节串
//void HexToAscii(unsigned char * pHex, unsigned char * pAscii, int nLen);//将十六进制字节串转换为ASCII码表示的十六进制字符串
void print(unsigned char* state);//输出ASCII码表示的十六进制字符串
void Avalanche_effect(unsigned char key[16], unsigned char input[16], unsigned char cipher[16]);//雪崩效应
int main()
{
	while (1)
	{
		cout << "请输入你要实现的功能的编号：1：AES加密；2：AES解密；3：测试雪崩效应；4：退出" << endl;
		int a;
		cin >> a;
		if (a == 1)
		{
			cout << "请输入你的密钥：";
			unsigned char  key16[33];
			cin >> key16;
			cout << "请输入你的明文：";
			unsigned char  input16[33];
			cin >> input16;
			unsigned char key[16];//十六进制字节串密钥
			AsciiToHex(key16, key, 32);//转换为十六进制字节串
			cout << "所输入的密钥：";
			print(key);
			unsigned char  input[16];//十六进制字节串明文
			AsciiToHex(input16, input, 32);
			cout << "所输入的明文：";
			print(input);
			AES aes(key);
			aes.Encrypt(input);
			cout << "加密后的密文：";
			print(input);
		}
		else if (a == 2)
		{
			cout << "请输入你的密钥：";
			unsigned char  key16[33];
			cin >> key16;
			cout << "请输入你的密文：";
			unsigned char  cipher16[33];
			cin >> cipher16;
			unsigned char key[16];
			AsciiToHex(key16, key, 32);
			cout << "所输入的密钥：";
			print(key);
			unsigned char  cipher[16];//十六进制字节串密文
			AsciiToHex(cipher16, cipher, 32);
			cout << "所输入的密文：";
			print(cipher);
			AES aes(key);
			aes.Decrypt(cipher);
			cout << "解密后的结果：";
			print(cipher);
		}
		else if (a == 3)
		{
			cout << "请输入你的密钥：";
			unsigned char  key16[33];
			cin >> key16;
			unsigned char key[16];
			AsciiToHex(key16, key, 32);
			cout << "请输入你的明文：";
			unsigned char  input16[33];
			cin >> input16;
			unsigned char input[16];
			unsigned char cipher[16];
			AsciiToHex(input16, input, 32);
			for (int i = 0; i < 16; i++)
				cipher[i] = input[i];
			cout << "所输入的密钥：";
			print(key);
			cout << "所输入的明文：";
			print(input);
			AES aes(key);
			aes.Encrypt(cipher);
			cout << "加密后的密文：";
			print(cipher);
			cout << "----------------------------雪崩测试----------------------------" << endl;
			Avalanche_effect(key, input, cipher);
		}
		else
		{
			return 0;
		}
	}
	return 0;
}
//将ASCII码表示的十六进制字符串转换为十六进制字节串
void AsciiToHex(unsigned char* pAscii, unsigned char* pHex, int nLen)
{
	if (nLen % 2)
		return;
	int nHexLen = nLen / 2;

	for (int i = 0; i < nHexLen; i++)
	{
		unsigned char Nibble[2];
		Nibble[0] = *pAscii++;
		Nibble[1] = *pAscii++;
		for (int j = 0; j < 2; j++)
		{
			if (Nibble[j] <= 'F' && Nibble[j] >= 'A')
				Nibble[j] = Nibble[j] - 'A' + 10;
			else if (Nibble[j] <= 'f' && Nibble[j] >= 'a')
				Nibble[j] = Nibble[j] - 'a' + 10;
			else if (Nibble[j] >= '0' && Nibble[j] <= '9')
				Nibble[j] = Nibble[j] - '0';
			else
				return;
		}   // for (int j = ...)
		pHex[i] = Nibble[0] << 4;
		pHex[i] |= Nibble[1];
	}   // for (int i = ...)
}

//雪崩效应检验
void Avalanche_effect(unsigned char key[16], unsigned char input[16], unsigned char cipher[16])
{

	cout << "雪崩效应之改变一位明文:" << endl;
	int num1 = 0;
	int num2 = 0;
	for (int j = 5; j < 13; j++)
	{
		//改变此位明文
		unsigned char tmp1;
		unsigned char tmp2;
		unsigned char plain[16];
		for (int i = 0; i < 16; i++)
			plain[i] = input[i];
		tmp1 = plain[j] & 0xfe;
		tmp2 = plain[j] & 0x01;
		if (tmp2 == 0x01)
			tmp1 = 0x00;
		else
			tmp1 = 0x01;
		plain[j] = tmp1 + tmp2;
		AES aes(key);
		aes.Encrypt(plain);//加密
		int sum = 0;
		for (int j = 0; j < 16; j++)
		{
			unsigned char comp = plain[j] ^ cipher[j];
			for (int k = 0; k < 8; k++)
			{
				unsigned char tmp = comp & 0x01;
				if (tmp == 0x00)
					sum++;
				comp >>= 1;
			}
		}
		cout << "当改变明文第" << j << "位时，密文改变位数为：" << sum << endl;
		num1 += sum;
	}
	cout << "当改变一位明文时，密文改变位数的平均值为：" << num1 / 8 << endl;
	cout << endl << "雪崩效应之改变一位密钥:" << endl;
	for (int j = 2; j < 10; j++)
	{
		//改变此位密钥
		unsigned char tmp1;
		unsigned char tmp2;
		unsigned char newkey[16];
		for (int i = 0; i < 16; i++)
			newkey[i] = key[i];
		tmp1 = newkey[j] & 0xfe;
		tmp2 = newkey[j] & 0x01;
		if (tmp2 == 0x01)
			tmp1 = 0x00;
		else
			tmp1 = 0x01;
		newkey[j] = tmp1 + tmp2;
		AES aes(newkey);
		aes.Encrypt(input);//加密
		int sum = 0;
		for (int j = 0; j < 16; j++)
		{
			unsigned char comp = input[j] ^ cipher[j];
			for (int k = 0; k < 8; k++)
			{
				unsigned char tmp = comp & 0x01;
				if (tmp == 0x00)
					sum++;
				comp >>= 1;
			}
		}
		cout << "当改变密钥第" << j << "位时，密文改变位数为：" << sum << endl;
		num2 += sum;
	}
	cout << "当改变一位密钥时，密文改变位数的平均值为：" << num2 / 8 << endl;
}
void print(unsigned char* state)
{
	int i;
	for (i = 0; i < 16; i++)
	{
		printf("%s%X ", state[i] > 15 ? "" : "0", state[i]);
	}
	printf("\n");
}
