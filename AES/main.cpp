#include "AES.h"
#include<iostream>
using namespace std;
void AsciiToHex(unsigned char* pAscii, unsigned char* pHex, int nLen);//��ASCII���ʾ��ʮ�������ַ���ת��Ϊʮ�������ֽڴ�
//void HexToAscii(unsigned char * pHex, unsigned char * pAscii, int nLen);//��ʮ�������ֽڴ�ת��ΪASCII���ʾ��ʮ�������ַ���
void print(unsigned char* state);//���ASCII���ʾ��ʮ�������ַ���
void Avalanche_effect(unsigned char key[16], unsigned char input[16], unsigned char cipher[16]);//ѩ��ЧӦ
int main()
{
	while (1)
	{
		cout << "��������Ҫʵ�ֵĹ��ܵı�ţ�1��AES���ܣ�2��AES���ܣ�3������ѩ��ЧӦ��4���˳�" << endl;
		int a;
		cin >> a;
		if (a == 1)
		{
			cout << "�����������Կ��";
			unsigned char  key16[33];
			cin >> key16;
			cout << "������������ģ�";
			unsigned char  input16[33];
			cin >> input16;
			unsigned char key[16];//ʮ�������ֽڴ���Կ
			AsciiToHex(key16, key, 32);//ת��Ϊʮ�������ֽڴ�
			cout << "���������Կ��";
			print(key);
			unsigned char  input[16];//ʮ�������ֽڴ�����
			AsciiToHex(input16, input, 32);
			cout << "����������ģ�";
			print(input);
			AES aes(key);
			aes.Encrypt(input);
			cout << "���ܺ�����ģ�";
			print(input);
		}
		else if (a == 2)
		{
			cout << "�����������Կ��";
			unsigned char  key16[33];
			cin >> key16;
			cout << "������������ģ�";
			unsigned char  cipher16[33];
			cin >> cipher16;
			unsigned char key[16];
			AsciiToHex(key16, key, 32);
			cout << "���������Կ��";
			print(key);
			unsigned char  cipher[16];//ʮ�������ֽڴ�����
			AsciiToHex(cipher16, cipher, 32);
			cout << "����������ģ�";
			print(cipher);
			AES aes(key);
			aes.Decrypt(cipher);
			cout << "���ܺ�Ľ����";
			print(cipher);
		}
		else if (a == 3)
		{
			cout << "�����������Կ��";
			unsigned char  key16[33];
			cin >> key16;
			unsigned char key[16];
			AsciiToHex(key16, key, 32);
			cout << "������������ģ�";
			unsigned char  input16[33];
			cin >> input16;
			unsigned char input[16];
			unsigned char cipher[16];
			AsciiToHex(input16, input, 32);
			for (int i = 0; i < 16; i++)
				cipher[i] = input[i];
			cout << "���������Կ��";
			print(key);
			cout << "����������ģ�";
			print(input);
			AES aes(key);
			aes.Encrypt(cipher);
			cout << "���ܺ�����ģ�";
			print(cipher);
			cout << "----------------------------ѩ������----------------------------" << endl;
			Avalanche_effect(key, input, cipher);
		}
		else
		{
			return 0;
		}
	}
	return 0;
}
//��ASCII���ʾ��ʮ�������ַ���ת��Ϊʮ�������ֽڴ�
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

//ѩ��ЧӦ����
void Avalanche_effect(unsigned char key[16], unsigned char input[16], unsigned char cipher[16])
{

	cout << "ѩ��ЧӦ֮�ı�һλ����:" << endl;
	int num1 = 0;
	int num2 = 0;
	for (int j = 5; j < 13; j++)
	{
		//�ı��λ����
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
		aes.Encrypt(plain);//����
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
		cout << "���ı����ĵ�" << j << "λʱ�����ĸı�λ��Ϊ��" << sum << endl;
		num1 += sum;
	}
	cout << "���ı�һλ����ʱ�����ĸı�λ����ƽ��ֵΪ��" << num1 / 8 << endl;
	cout << endl << "ѩ��ЧӦ֮�ı�һλ��Կ:" << endl;
	for (int j = 2; j < 10; j++)
	{
		//�ı��λ��Կ
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
		aes.Encrypt(input);//����
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
		cout << "���ı���Կ��" << j << "λʱ�����ĸı�λ��Ϊ��" << sum << endl;
		num2 += sum;
	}
	cout << "���ı�һλ��Կʱ�����ĸı�λ����ƽ��ֵΪ��" << num2 / 8 << endl;
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
