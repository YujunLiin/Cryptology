#include<iostream>
#include<string>
using namespace std;
string getcipher(string key)   //����û���
{
	string alphabet = "abcdefghijklmnopqrstuvwxyz";
	string getc;
	getc = key + alphabet;
	int sign[26];    //���ڱ����ĸ�Ƿ���ֹ�
	for (int i = 0; i < getc.length(); i++)
	{
		if (getc[i] >= 'A' && getc[i] <= 'Z')
			getc[i] += 32;
		if (getc[i] >= 'a' && getc[i] <= 'z')
		{
			if (sign[getc[i] - 'a'] != 1)   //����ĸ��һ�γ���
				sign[getc[i] - 'a'] = 1;
			else
			{
				getc.erase(i, 1);
				i--;
			}
		}
		else if (getc[i] == ' ')
		{
			getc.erase(i, 1);
			i--;
		}
		else
		{
			cout << "������󣡣���" << endl;
			continue;
		}
	}
	return getc;
}
string encrypt(string getc, string plaintext)    //����
{
	string alphabet = "abcdefghijklmnopqrstuvwxyz";
	string ciphertext = plaintext;
	for (int i = 0; i < plaintext.length(); i++)
	{
		if (plaintext[i] >= 'A' && plaintext[i] <= 'Z')
			plaintext[i] += 32;
		if (plaintext[i] >= 'a' && plaintext[i] <= 'z')
		{
			for (int j = 0; j < 26; j++)
			{
				if (plaintext[i] == alphabet[j])
					ciphertext[i] = getc[j];
			}
		}
		else
			continue;
	}
	return ciphertext;
}
string decrypt(string getc, string ciphertext)   //����
{
	string alphabet = "abcdefghijklmnopqrstuvwxyz";
	string plaintext = ciphertext;
	for (int i = 0; i < ciphertext.length(); i++)
	{
		if (ciphertext[i] >= 'A' && ciphertext[i] <= 'Z')
			ciphertext[i] += 32;
		if (ciphertext[i] >= 'a' && ciphertext[i] <= 'z')
		{
			for (int j = 0; j < 26; j++)
			{
				if (ciphertext[i] == getc[j])
					plaintext[i] = alphabet[j];
			}
		}
		else
			continue;
	}
	return plaintext;
}
int frequency(string ciphertext)   //ͳ�Ƹ�����ĸ��Ƶ��
{
	string result = "abcdefghijklmnopqrstuvwxyz";
	double sum = 0.0;  //ͳ�������е���ĸ����
	int count[26];
	for (int i = 0; i < 26; i++)
		count[i] = 0;
	for (int i = 0; i < ciphertext.length(); i++)
	{
		if (ciphertext[i] >= 'A' && ciphertext[i] <= 'Z')  //�����ִ�Сд����ͳһת����Сд
			ciphertext[i] += 32;
		if (ciphertext[i] >= 'a' && ciphertext[i] <= 'z')
		{
			count[ciphertext[i] - 'a']++;
			sum++;
		}
		else
			continue;
	}
	for (int i = 0; i < 26; i++)//����
	{
		for (int j = i + 1; j < 26; j++)
		{
			if (count[i] < count[j])
			{
				swap(count[i], count[j]);
				swap(result[i], result[j]);
			}
		}
	}
	cout << "Ƶ��ͳ�ƽ��Ϊ��" << endl;
	for (int i = 0; i < 26; i++)
		cout << result[i] << "  " << count[i] * 100 / sum << endl;
	return 0;
}
int main()
{
	string alphabet = "abcdefghijklmnopqrstuvwxyz";
	while (1)
	{
		cout << "��������Ҫ��ʵ�ֵĹ��ܣ�1�����ܣ�2�����ܣ�3��Ƶ��ͳ�ƣ�4���˳���" << endl;
		int choice;
		cin >> choice;
		cin.get();
		if (choice == 1)
		{
			cout << "��������ļ�����Կ�������ӣ�" << endl;
			string key;
			getline(cin, key);
			string getc = getcipher(key);
			cout << "�û������£�" << endl;
			cout << alphabet << endl;
			cout << getc << endl;
			cout << "������������ģ�" << endl;
			string plaintext;
			getline(cin, plaintext);
			cout << "���ܽ��Ϊ��" << endl << encrypt(getc, plaintext) << endl;
		}
		else if (choice == 2)
		{
			cout << "��������Ľ�����Կ�������ӣ�" << endl;
			string key;
			getline(cin, key);
			string getc = getcipher(key);
			cout << "�û�������:" << endl << alphabet << endl << getc << endl;
			cout << "������������ģ�" << endl;
			string ciphertext;
			getline(cin, ciphertext);
			cout << "���ܽ��Ϊ��" << endl << decrypt(getc, ciphertext) << endl;
		}
		else if (choice == 3)
		{
			cout << "������������ģ�" << endl;
			string ciphertext;
			getline(cin, ciphertext);
			frequency(ciphertext);
		}
		else
			return 0;
	}
}