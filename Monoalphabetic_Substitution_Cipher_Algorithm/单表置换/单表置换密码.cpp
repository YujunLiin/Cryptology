#include<iostream>
#include<string>
using namespace std;
string getcipher(string key)   //获得置换表
{
	string alphabet = "abcdefghijklmnopqrstuvwxyz";
	string getc;
	getc = key + alphabet;
	int sign[26];    //用于标记字母是否出现过
	for (int i = 0; i < getc.length(); i++)
	{
		if (getc[i] >= 'A' && getc[i] <= 'Z')
			getc[i] += 32;
		if (getc[i] >= 'a' && getc[i] <= 'z')
		{
			if (sign[getc[i] - 'a'] != 1)   //该字母第一次出现
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
			cout << "输入错误！！！" << endl;
			continue;
		}
	}
	return getc;
}
string encrypt(string getc, string plaintext)    //加密
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
string decrypt(string getc, string ciphertext)   //解密
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
int frequency(string ciphertext)   //统计各个字母的频率
{
	string result = "abcdefghijklmnopqrstuvwxyz";
	double sum = 0.0;  //统计密文中的字母个数
	int count[26];
	for (int i = 0; i < 26; i++)
		count[i] = 0;
	for (int i = 0; i < ciphertext.length(); i++)
	{
		if (ciphertext[i] >= 'A' && ciphertext[i] <= 'Z')  //不区分大小写，均统一转换成小写
			ciphertext[i] += 32;
		if (ciphertext[i] >= 'a' && ciphertext[i] <= 'z')
		{
			count[ciphertext[i] - 'a']++;
			sum++;
		}
		else
			continue;
	}
	for (int i = 0; i < 26; i++)//排序
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
	cout << "频率统计结果为：" << endl;
	for (int i = 0; i < 26; i++)
		cout << result[i] << "  " << count[i] * 100 / sum << endl;
	return 0;
}
int main()
{
	string alphabet = "abcdefghijklmnopqrstuvwxyz";
	while (1)
	{
		cout << "请输入你要是实现的功能：1：加密；2：解密；3：频率统计；4：退出：" << endl;
		int choice;
		cin >> choice;
		cin.get();
		if (choice == 1)
		{
			cout << "请输入你的加密密钥短语或句子：" << endl;
			string key;
			getline(cin, key);
			string getc = getcipher(key);
			cout << "置换表如下：" << endl;
			cout << alphabet << endl;
			cout << getc << endl;
			cout << "请输入你的明文：" << endl;
			string plaintext;
			getline(cin, plaintext);
			cout << "加密结果为：" << endl << encrypt(getc, plaintext) << endl;
		}
		else if (choice == 2)
		{
			cout << "请输入你的解密密钥短语或句子：" << endl;
			string key;
			getline(cin, key);
			string getc = getcipher(key);
			cout << "置换表如下:" << endl << alphabet << endl << getc << endl;
			cout << "请输入你的密文：" << endl;
			string ciphertext;
			getline(cin, ciphertext);
			cout << "解密结果为：" << endl << decrypt(getc, ciphertext) << endl;
		}
		else if (choice == 3)
		{
			cout << "请输入你的密文：" << endl;
			string ciphertext;
			getline(cin, ciphertext);
			frequency(ciphertext);
		}
		else
			return 0;
	}
}