#include<iostream>
using namespace std;
//��ʼ�û���
int IP[64] = { 58,50,42,34,26,18,10,2,60,52,44,36,28,20,12,4,62,54,46,38,30,22,14,6,64,56,48,40,32,24,16,8,
57,49,41,33,25,17,9,1,59,51,43,35,27,19,11,3,61,53,45,37,29,21,13,5,63,55,47,39,31,23,15,7 };
//���ʼ�û���
int Inverse_IP_table[64] = { 40,8,48,16,56,24,64,32,39,7,47,15,55,23,63,31,38,6,46,14,54,22,62,30,37,5,45,13,53,21,61,29,
36,4,44,12,52,20,60,28,35,3,43,11,51,19,59,27,34,2,42,10,50,18,58,26,33,1,41,9, 49,17,57,25 };
//��չ�û�
int E[48] = { 32,1,2,3,4,5,4,5,6,7,8,9,8,9,10,11,12,13,12,13,14,15,16,17,16,17,18,19,
20,21,20,21,22,23,24,25,24,25,26,27,28,29,28,29,30,31,32,1 };
//S��
int S[32][16] = {
	{ 14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7 },{ 0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8 },
{ 4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0 },{ 15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13 },
{ 15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10 },{ 3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5 },
{ 0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15 },{ 13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9 },
{ 10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8 },{ 13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1 },
{ 13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7 },{ 1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12 },
{ 7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15 },{ 13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9 },
{ 10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4 },{ 3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14 },
{ 2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9 },{ 14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6 },
{ 4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14 },{ 11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3 },
{ 12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11 },{ 10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8 },
{ 9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6 },{ 4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13 },
{ 4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1 },{ 13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6 },
{ 1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2 },{ 6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12 },
{ 13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7 },{ 1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2 },
{ 7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8 },{ 2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11 } };
//�û�P
int P[32] = { 16,7,20,21,29,12,28,17,1,15,23,26,5,18,31,10,2,8,24,14,32,27,3,9,19,13,30,6,22,11,4,25 };
//PC-1
int IP1[56] = { 57,49,41,33,25,17,9,1,58,50,42,34,26,18,10,2,59,51,43,35,27,19,11,3,60,52,44,36,
63,55,47,39,31,23,15,7,62,54,46,38,30,22,14,6,61,53,45,37,29,21,13,5,28,20,12,4 };
//PC-2
int IP2[48] = { 14,17,11,24,1,5,3,28,15,6,21,10,23,19,12,4,26,8,16,7,27,20,13,2,41,
52,31,37,47,55,30,40,51,45,33,48,44,49,39,56,34,53,46,42,50,36,29,32 };
//��Կ��λ��
int keyshift[16] = { 1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1 };
//��ʼ��������Կ
int key64[64];
//�û����������Կ
int key56[56];
//��Կ����������
int key_left[28], key_right[28];
//������Կ
int key_left_BU[28], key_right_BU[28];
//����Կ
int round_key[48];
//�洢ÿ������Կ���ڽ���
int subkey[16][48];
//��ʼ�û�ǰ����������
int notranplain[64];
//��ʼ�û������������
int tranplain[64];
//���ʼ�û�ǰ������
int notrancipher[64];
//���ʼ�û��������
int trancipher[64];
//�û��������������������
int plaintext_left[32], plaintext_right[32];
//����������
int plaintetx_BU[32];
//S����չ��������
int plaintext_S[48];

//DES���ܹ���
void Encrypt(int plaintext[64])
{
	int i, j, m;
	for (m = 0; m < 56; m++)//�����Կ�û�ѡ��1
	{
		key56[m] = key64[IP1[m] - 1];
	}
	for (m = 0; m < 56; m++)//����Կ��Ϊ��������
	{
		if (m < 28)
			key_left[m] = key56[m];
		else
			key_right[m - 28] = key56[m];
	}
	for (i = 0; i < 1; i++)
	{
		for (j = 0; j < 64; j++)//ȡǰ64λ���м���
		{
			notranplain[j] = plaintext[j + 64 * i];
		}
		for (j = 0; j < 64; j++)//��ɳ�ʼ�û�
		{
			tranplain[j] = notranplain[IP[j] - 1];
		}
		for (m = 0; m < 64; m++)//�����ķ�Ϊ��������
		{
			if (m < 32)
				plaintext_left[m] = tranplain[m];
			else
				plaintext_right[m - 32] = tranplain[m];
		}
		for (j = 0; j < 16; j++)//16���ֽṹ
		{
			for (m = 0; m < 28; m++)//��Կ����λ
			{
				key_left_BU[m] = key_left[(m + keyshift[j]) % 28];
				key_right_BU[m] = key_right[(m + keyshift[j]) % 28];
			}
			for (m = 0; m < 28; m++)//����������Կ����֤�´�ѭ��ʹ��
			{
				key_left[m] = key_left_BU[m];
				key_right[m] = key_right_BU[m];
			}
			for (int m = 0; m < 48; m++)//����û�ѡ��2
			{
				if (IP2[m] < 29)
				{
					round_key[m] = key_left_BU[IP2[m] - 1];
					subkey[j][m] = round_key[m];
				}
				else
				{
					round_key[m] = key_right_BU[IP2[m] - 29];
					subkey[j][m] = round_key[m];
				}
			}
			for (m = 0; m < 32; m++)//�������ı���
			{
				plaintetx_BU[m] = plaintext_right[m];
			}
			for (m = 0; m < 48; m++)//��չ����
			{
				plaintext_S[m] = plaintext_right[E[m] - 1];
			}
			for (m = 0; m < 48; m++)//��չ���Ki�����
			{
				plaintext_S[m] = plaintext_S[m] ^ round_key[m];
			}
			for (m = 0; m < 8; m++)//S�д���
			{
				int s;
				s = S[(plaintext_S[m * 6] * 2 + plaintext_S[5 + m * 6]) + m * 4][plaintext_S[1 + m * 6] * 8 + plaintext_S[2 + m * 6] * 4 + plaintext_S[3 + m * 6] * 2 + plaintext_S[4 + m * 6]];
				//������λ�õ�����ʾ��Ϊ������
				for (int n = 0; n < 4; n++)
				{
					plaintext_S[(3 - n) + 4 * m] = s % 2;
					s = s / 2;
				}
			}
			for (m = 0; m < 32; m++)//���P�û�,�������������,�����ݵ������Ĵ�������������һ��ѭ��
			{
				plaintext_right[m] = plaintext_S[P[m] - 1] ^ plaintext_left[m];
				plaintext_left[m] = plaintetx_BU[m];
			}
		}
		for (m = 0; m < 64; m++)//16�ֺ����ҽ���
		{
			if (m < 32)
				notrancipher[m] = plaintext_right[m];
			else
				notrancipher[m] = plaintext_left[m - 32];
		}
		for (m = 0; m < 64; m++)//������ʼ�û�
		{
			trancipher[m] = notrancipher[Inverse_IP_table[m] - 1];
		}
	}
}

//DES���ܹ���
void Decrypt(int ciphertext[64])
{
	int i, j, m;
	for (i = 0; i < 64; i++)//�����ķ���һ��������
	{
		ciphertext[i] = trancipher[i];
	}

	for (i = 0; i < 1; i++)
	{
		for (j = 0; j < 64; j++)//ȡǰ64λ���н���
		{
			notranplain[j] = ciphertext[j + 64 * i];
		}
		for (j = 0; j < 64; j++)//��ɳ�ʼ�û�
		{
			tranplain[j] = notranplain[IP[j] - 1];
		}
		for (int m = 0; m < 64; m++)//�����ķ�Ϊ��������
		{
			if (m < 32)
				plaintext_left[m] = tranplain[m];
			else
				plaintext_right[m - 32] = tranplain[m];
		}
		for (j = 0; j < 16; j++)//16���ֽṹ
		{
			for (int m = 0; m < 32; m++)//�������ı���
			{
				plaintetx_BU[m] = plaintext_right[m];
			}
			for (m = 0; m < 48; m++)//��չ����
			{
				plaintext_S[m] = plaintext_right[E[m] - 1];
			}
			for (m = 0; m < 48; m++)//F(R,subkey)
			{
				plaintext_S[m] = plaintext_S[m] ^ subkey[15 - j][m];
			}
			for (m = 0; m < 8; m++)//S�д���
			{
				int s;
				s = S[(plaintext_S[m * 6] * 2 + plaintext_S[5 + m * 6]) + m * 4][plaintext_S[1 + m * 6] * 8 + plaintext_S[2 + m * 6] * 4 + plaintext_S[3 + m * 6] * 2 + plaintext_S[4 + m * 6]];
				for (int n = 0; n < 4; n++)
				{
					plaintext_S[(3 - n) + 4 * m] = s % 2;
					s = s / 2;
				}
			}
			for (m = 0; m < 32; m++)//���P�û�,�������������,�����ݵ������Ĵ�������������һ��ѭ��
			{
				plaintext_right[m] = plaintext_S[P[m] - 1] ^ plaintext_left[m];
				plaintext_left[m] = plaintetx_BU[m];
			}
		}
		for (m = 0; m < 64; m++)//16�ֺ����ҽ���
		{
			if (m < 32)
				notrancipher[m] = plaintext_right[m];
			else
				notrancipher[m] = plaintext_left[m - 32];
		}
		for (m = 0; m < 64; m++)//������ʼ�û�
		{
			trancipher[m] = notrancipher[Inverse_IP_table[m] - 1];
		}
	}
}

//ѩ��ЧӦ����
void Avalanche_effect(int plaintext[64])
{
	cout << "ѩ��ЧӦ֮�ı�һλ����:" << endl;
	int first_ciphertext[64];
	Encrypt(plaintext);
	for (int i = 0; i < 64; i++)
	{
		first_ciphertext[i] = trancipher[i];
	}
	int num1 = 0;
	int num2 = 0;
	for (int i = 0; i < 8; i++)
	{
		cout << "������Ҫ�ı����ĵĵڼ�λ����";
		int j;
		cin >> j;
		//�ı��λ����
		if (plaintext[j] == 0)
		{
			plaintext[j] = 1;
		}
		else
		{
			plaintext[j] = 0;
		}
		Encrypt(plaintext);
		int second_ciphertext[64];
		int count = 0;
		for (int i = 0; i < 64; i++)
		{
			second_ciphertext[i] = trancipher[i];
			if (second_ciphertext[i] ^ first_ciphertext[i] == 1)
			{
				count++;
			}
		}
		//���ԭ������
		if (plaintext[j] == 0)
		{
			plaintext[j] = 1;
		}
		else
		{
			plaintext[j] = 0;
		}
		cout << "���ı����ĵ�" << j << "λʱ�����ĸı�λ��Ϊ��" << count << endl;
		num1 += count;
	}
	cout << "���ı�һλ����ʱ�����ĸı�λ����ƽ��ֵΪ��" << num1 / 8 << endl;
	cout << endl << "ѩ��ЧӦ֮�ı�һλ��Կ:" << endl;
	for (int i = 0; i < 8; i++)
	{
		cout << "������Ҫ�ı���Կ�ĵڼ�λ����";
		int j;
		cin >> j;
		//�ı��λ��Կ
		if (key64[j] == 1)
		{
			key64[j] = 0;
		}
		else
		{
			key64[j] = 1;
		}
		Encrypt(plaintext);
		int second_ciphertext[64];
		int count = 0;
		for (int i = 0; i < 64; i++)
		{
			second_ciphertext[i] = trancipher[i];
			if (second_ciphertext[i] ^ first_ciphertext[i] == 1)
			{
				count++;
			}
		}
		//���ԭ����Կ
		if (key64[j] == 1)
		{
			key64[j] = 0;
		}
		else
		{
			key64[j] = 1;
		}
		cout << "���ı���Կ��" << j << "λʱ�����ĸı�λ��Ϊ��" << count << endl;
		num2 += count;
	}
	cout << "���ı�һλ��Կʱ�����ĸı�λ����ƽ��ֵΪ��" << num2 / 8 << endl;
}

//�������ʮ������ת��Ϊ������
void binary_tran(char input[16], int output[64])
{
	int k = 0;
	for (int i = 0; i < 16; i++)
	{
		if (input[i] <= '9')
		{
			for (int j = 0; j < 4; j++)
			{
				output[k + 3 - j] = int(input[i]) % 2;
				input[i] = int(input[i]) / 2;
			}
			k = k + 4;
		}
		else
		{
			if (input[i] == 'A')
			{
				output[k++] = 1;
				output[k++] = 0;
				output[k++] = 1;
				output[k++] = 0;
			}
			if (input[i] == 'B')
			{
				output[k++] = 1;
				output[k++] = 0;
				output[k++] = 1;
				output[k++] = 1;
			}
			if (input[i] == 'C')
			{
				output[k++] = 1;
				output[k++] = 1;
				output[k++] = 0;
				output[k++] = 0;
			}
			if (input[i] == 'D')
			{
				output[k++] = 1;
				output[k++] = 1;
				output[k++] = 0;
				output[k++] = 1;
			}
			if (input[i] == 'E')
			{
				output[k++] = 1;
				output[k++] = 1;
				output[k++] = 1;
				output[k++] = 0;
			}
			if (input[i] == 'F')
			{
				output[k++] = 1;
				output[k++] = 1;
				output[k++] = 1;
				output[k++] = 1;
			}
		}
	}
}

//��������ת��Ϊʮ�����Ʋ����
void tran_binary(int output[64])
{
	for (int i = 0; i < 16; i++)
	{
		if (output[4 * i] == 0 && output[4 * i + 1] == 0 && output[4 * i + 2] == 0 && output[4 * i + 3] == 0)
		{
			cout << "0";
			continue;
		}
		if (output[4 * i] == 0 && output[4 * i + 1] == 0 && output[4 * i + 2] == 0 && output[4 * i + 3] == 1)
		{
			cout << "1";
			continue;
		}
		if (output[4 * i] == 0 && output[4 * i + 1] == 0 && output[4 * i + 2] == 1 && output[4 * i + 3] == 0)
		{
			cout << "2";
			continue;
		}
		if (output[4 * i] == 0 && output[4 * i + 1] == 0 && output[4 * i + 2] == 1 && output[4 * i + 3] == 1)
		{
			cout << "3";
			continue;
		}
		if (output[4 * i] == 0 && output[4 * i + 1] == 1 && output[4 * i + 2] == 0 && output[4 * i + 3] == 0)
		{
			cout << "4";
			continue;
		}
		if (output[4 * i] == 0 && output[4 * i + 1] == 1 && output[4 * i + 2] == 0 && output[4 * i + 3] == 1)
		{
			cout << "5";
			continue;
		}
		if (output[4 * i] == 0 && output[4 * i + 1] == 1 && output[4 * i + 2] == 1 && output[4 * i + 3] == 0)
		{
			cout << "6";
			continue;
		}
		if (output[4 * i] == 0 && output[4 * i + 1] == 1 && output[4 * i + 2] == 1 && output[4 * i + 3] == 1)
		{
			cout << "7";
			continue;
		}
		if (output[4 * i] == 1 && output[4 * i + 1] == 0 && output[4 * i + 2] == 0 && output[4 * i + 3] == 0)
		{
			cout << "8";
			continue;
		}
		if (output[4 * i] == 1 && output[4 * i + 1] == 0 && output[4 * i + 2] == 0 && output[4 * i + 3] == 1)
		{
			cout << "9";
			continue;
		}
		if (output[4 * i] == 1 && output[4 * i + 1] == 0 && output[4 * i + 2] == 1 && output[4 * i + 3] == 0)
		{
			cout << "A";
			continue;
		}
		if (output[4 * i] == 1 && output[4 * i + 1] == 0 && output[4 * i + 2] == 1 && output[4 * i + 3] == 1)
		{
			cout << "B";
			continue;
		}
		if (output[4 * i] == 1 && output[4 * i + 1] == 1 && output[4 * i + 2] == 0 && output[4 * i + 3] == 0)
		{
			cout << "C";
			continue;
		}
		if (output[4 * i] == 1 && output[4 * i + 1] == 1 && output[4 * i + 2] == 0 && output[4 * i + 3] == 1)
		{
			cout << "D";
			continue;
		}
		if (output[4 * i] == 1 && output[4 * i + 1] == 1 && output[4 * i + 2] == 1 && output[4 * i + 3] == 0)
		{
			cout << "E";
			continue;
		}
		if (output[4 * i] == 1 && output[4 * i + 1] == 1 && output[4 * i + 2] == 1 && output[4 * i + 3] == 1)
		{
			cout << "F";
			continue;
		}
	}
}

int main()
{
	while (1)
	{
		cout << "��������Ҫʵ�ֵĹ��ܵı�ţ�1��DES���ܣ�2��DES���ܣ���ʹ�õ���һ�ֵ�����Կ�����ȼ��ܺ��ٽ��ܣ���3������ѩ��ЧӦ��4���˳�" << endl;
		int a;
		cin >> a;
		if (a == 1)
		{
			char key[16];
			int i = 0, j = 0;
			cout << "�����������Կ��";
			for (i = 0; i < 16; i++)
				cin >> key[i];
			binary_tran(key, key64);//��������Կת��Ϊ������
			char plaintext_input[16];
			cout << "������������ģ�";
			for (j = 0; j < 16; j++)
				cin >> plaintext_input[j];
			int plaintext[64];
			binary_tran(plaintext_input, plaintext);//����������ת��Ϊ������
			Encrypt(plaintext);//����
			cout << "���ܺ�Ľ��Ϊ��";
			tran_binary(trancipher);
			cout << endl;
		}
		else if (a == 2)
		{
			char key[16];
			int i = 0, k = 0;
			cout << "�����������Կ��";
			for (i = 0; i < 16; i++)
				cin >> key[i];
			binary_tran(key, key64);//��������Կת��Ϊ������
			char ciphertext_input[16];
			cout << "������������ģ�";
			for (k = 0; k < 16; k++)
				cin >> ciphertext_input[k];
			int ciphertext[64];
			binary_tran(ciphertext_input, ciphertext);//����������ת��Ϊ������
			Decrypt(ciphertext);//����
			cout << "���ܺ�Ľ��Ϊ��";
			tran_binary(trancipher);
			cout << endl;
		}
		else if (a == 3)
		{
			char key[16];
			int i = 0, j = 0;
			cout << "�����������Կ��";
			for (i = 0; i < 16; i++)
				cin >> key[i];
			binary_tran(key, key64);//��������Կת��Ϊ������
			char plaintext_input[16];
			cout << "������������ģ�";
			for (j = 0; j < 16; j++)
				cin >> plaintext_input[j];
			int plaintext[64];
			binary_tran(plaintext_input, plaintext);
			Encrypt(plaintext);
			cout << "���ܺ�Ľ��Ϊ��";
			tran_binary(trancipher);
			cout << endl;
			Avalanche_effect(plaintext);
		}
		else
		{
			return 0;
		}
	}
	system("pause");
}