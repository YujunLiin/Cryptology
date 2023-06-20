#include<iostream>
#include<string>
using namespace std;
string encrypt(string plaintext, int key)       //加密算法，不区分大小写，均加密为大写
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
string decrypt(string ciphertext, int key)   //解密，无论大小写均解密为大写
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
		cout << "移位" << i << "位后的明文" <<endl<< decrypt(ciphertext, i) << endl;
	return 0;
}
int main()
{
	while (1)
	{
		cout << "输入相应数字表明要实现的功能：1：加密；2：解密；3：攻击；4：退出" << endl;
		int choice;
		cin >> choice; 
		cin.get();
		if (choice == 1)
		{
			cout << "请输入要加密的明文:" << endl;
			string plaintext;
			getline(cin, plaintext);
			int key;
			cout << "请输入相应的密钥：" << endl;
			cin >> key;
			cin.get();
			cout << "加密结果为：" << endl << encrypt(plaintext, key) << endl;
		}
		else if (choice == 2)
		{
			cout << "请输入要解密的密文:" << endl;
			string ciphertext;
			getline(cin, ciphertext);
			int key;
			cout << "请输入相应的密钥：" << endl;
			cin >> key;
			cin.get();
			cout << "解密结果为：" << endl << decrypt(ciphertext, key) << endl;
		}
		else if (choice == 3)
		{
			cout << "请输入你要破解的密文内容：" << endl;
			string ciphertext;
			getline(cin, ciphertext);
			cout << "破解后的所有可能的密钥以及相应的明文如下：" << endl << attack(ciphertext) << endl;
		}
		else 
			return 0;
	}
}
		
