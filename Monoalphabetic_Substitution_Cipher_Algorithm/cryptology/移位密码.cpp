#include<iostream>
#include<string>
using namespace std;
string encrypt(string plaintext, int key)       //�����㷨�������ִ�Сд��������Ϊ��д
{
	int len = plaintext.length();
	for (int i = 0; i < len; i++)
	{
		if (plaintext[i] >= 'a' && plaintext[i] <= 'z')
			plaintext[i] = char((int(plaintext[i] - 'a') + key) % 26 + 'A');
		else if (plaintext[i] >= 'A' && plaintext[i] <= 'Z')
			plaintext[i] = char((int(plaintext[i] - 'A') + key) % 26 + 'A');
		else
			continue;
	}
	return plaintext;
}
string decrypt(string ciphertext, int key)   //���ܣ����۴�Сд������Ϊ��д
{
	int len = ciphertext.length();
	for (int i = 0; i < len; i++)
	{
		if (ciphertext[i] >= 'a' && ciphertext[i] <= 'z')
			ciphertext[i] = char((int(ciphertext[i] - 'a') - key+26) % 26 + 'A');
		else if (ciphertext[i] >= 'A' && ciphertext[i] <= 'Z')
			ciphertext[i] = char((int(ciphertext[i] - 'A') - key+26) % 26 + 'A');
		else
			continue;
	}
	return ciphertext;
}
int attack(string ciphertext)
{
	for (int i = 0; i < 26; i++)
		cout << "��λ" << i << "λ�������" <<endl<< decrypt(ciphertext, i) << endl;
	return 0;
}
int main()
{
	while (1)
	{
		cout << "������Ӧ���ֱ���Ҫʵ�ֵĹ��ܣ�1�����ܣ�2�����ܣ�3��������4���˳�" << endl;
		int choice;
		cin >> choice; 
		cin.get();
		if (choice == 1)
		{
			cout << "������Ҫ���ܵ�����:" << endl;
			string plaintext;
			getline(cin, plaintext);
			int key;
			cout << "��������Ӧ����Կ��" << endl;
			cin >> key;
			cin.get();
			cout << "���ܽ��Ϊ��" << endl << encrypt(plaintext, key) << endl;
		}
		else if (choice == 2)
		{
			cout << "������Ҫ���ܵ�����:" << endl;
			string ciphertext;
			getline(cin, ciphertext);
			int key;
			cout << "��������Ӧ����Կ��" << endl;
			cin >> key;
			cin.get();
			cout << "���ܽ��Ϊ��" << endl << decrypt(ciphertext, key) << endl;
		}
		else if (choice == 3)
		{
			cout << "��������Ҫ�ƽ���������ݣ�" << endl;
			string ciphertext;
			getline(cin, ciphertext);
			cout << "�ƽ������п��ܵ���Կ�Լ���Ӧ���������£�" << endl << attack(ciphertext) << endl;
		}
		else 
			return 0;
	}
}
		
