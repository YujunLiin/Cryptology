#pragma once
#include<vector>
#include<string>
#include<cassert>
#include<iostream>
#include <algorithm>
using namespace std;
class Bigprime {

public:
	typedef unsigned long base_t;
	static int base_char;
	static int base;
	static int basebitnum;
	static int basebitchar;
	static int basebit;
private:
	friend class Rsa;
public:
	friend Bigprime operator + (const Bigprime& a, const Bigprime& b);
	friend Bigprime operator - (const Bigprime& a, const Bigprime& b);
	friend Bigprime operator * (const Bigprime& a, const Bigprime& b);
	friend Bigprime operator / (const Bigprime& a, const Bigprime& b);
	friend Bigprime operator % (const Bigprime& a, const Bigprime& b);
	friend bool operator < (const Bigprime& a, const Bigprime& b);
	friend bool operator <= (const Bigprime& a, const Bigprime& b);
	friend bool operator == (const Bigprime& a, const Bigprime& b);
	friend bool operator != (const Bigprime& a, const Bigprime& b) { return !(a == b); }
	//重载版本	
	friend Bigprime operator + (const Bigprime& a, const long b) { Bigprime t(b); return a + t; }
	friend Bigprime operator - (const Bigprime& a, const long b) { Bigprime t(b); return a - t; }
	friend Bigprime operator * (const Bigprime& a, const long b) { Bigprime t(b); return a * t; }
	friend Bigprime operator / (const Bigprime& a, const long b) { Bigprime t(b); return a / t; }
	friend Bigprime operator % (const Bigprime& a, const long b) { Bigprime t(b); return a % t; }
	friend bool operator < (const Bigprime& a, const long b) { Bigprime t(b); return a < t; }
	friend bool operator <= (const Bigprime& a, const  long b) { Bigprime t(b); return a <= t; }
	friend bool operator == (const Bigprime& a, const long b) { Bigprime t(b); return a == t; }
	friend bool operator != (const Bigprime& a, const long b) { Bigprime t(b); return !(a == t); };
	//	
	friend ostream& operator << (ostream& out, const Bigprime& a);
	friend Bigprime operator <<(const Bigprime& a, unsigned int n);
public:
	typedef vector<base_t> data_t;
	typedef const vector<base_t> const_data_t;
	Bigprime& trim()
	{
		int count = 0;
		//检查不为0的元素的数量		
		for (data_t::reverse_iterator it = _data.rbegin(); it != _data.rend(); ++it)
			if ((*it) == 0)
				++count;
			else
				break;
		if (count == _data.size())//只有零的情况保留			
			--count;
		for (int i = 0; i < count; ++i)
			_data.pop_back();
		return *this;
	}
	friend class bit;
	class bit
	{
	public:
		std::size_t size();
		bool at(std::size_t i);
		bit(const Bigprime& a);
	private:
		vector<base_t> _bitvec;
		std::size_t _size;
	};
	//大数幂模运算	
	Bigprime Mod_big_int(const Bigprime& exp, const Bigprime& p)const;
	//用扩展的欧几里得算法求乘法逆元
	Bigprime extend_Euclid(const Bigprime& m);
public:
	Bigprime() :_isnegative(false) { _data.push_back(0); }
	Bigprime(const string& num) :_data(), _isnegative(false) { copy_From_Hex_String(num); trim(); }
	Bigprime(int n) :_isnegative(false) { copy_From_Long(n); }
	Bigprime& operator =(string s)
	{
		_data.clear();
		_isnegative = false;
		copy_From_Hex_String(s);
		trim();
		return *this;
	}
	Bigprime(const Bigprime& a, bool isnegative) :_data(a._data), _isnegative(isnegative) {}
	Bigprime& operator =(int n)
	{
		_data.clear();
		copy_From_Long(n);
		return *this;
	}
public:
	static Bigprime Zero;
	static Bigprime One;
	static Bigprime Two;
private:
	bool small_Than(const Bigprime& a)const;//判断绝对值是否小于
	bool small_Or_Equals(const Bigprime& a)const;//判断绝对值是否小于相等
	bool equals(const Bigprime& a)const;//判断绝对值是否相等

	Bigprime& leftShift(const unsigned int n);
	Bigprime& rightShift(const unsigned int n);
	Bigprime& add(const Bigprime& b);
	Bigprime& sub(const Bigprime& b);

	void copy_From_Hex_String(const string& s)
	{
		string str(s);
		if (str.length() && str.at(0) == '-')
		{
			if (str.length() > 1)
				_isnegative = true;
			str = str.substr(1);
		}
		int count = (8 - (str.length() % 8)) % 8;
		std::string temp;

		for (int i = 0; i < count; ++i)
			temp.push_back(0);

		str = temp + str;

		for (int i = 0; i < str.length(); i += Bigprime::base_char)
		{
			base_t sum = 0;
			for (int j = 0; j < base_char; ++j)
			{
				char ch = str[i + j];

				ch = hex_2Uchar(ch);
				sum = ((sum << 4) | (ch));
			}
			_data.push_back(sum);
		}
		reverse(_data.begin(), _data.end());
	}
	char hex_2Uchar(char ch)
	{
		static char table[] = { 0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0a,0x0b,0x0c,0x0d,0x0e,0x0f };
		if (isdigit(ch))
			ch -= '0';
		else if (islower(ch))
			ch -= 'a' - 10;
		else if (isupper(ch))
			ch -= 'A' - 10;

		return table[ch];
	}

	void copy_From_Long(int n)
	{
		long a = n;
		if (a < 0)
		{
			_isnegative = true;
			a = -a;
		}
		do
		{
			Bigprime::base_t ch = (a & (Bigprime::base));
			_data.push_back(ch);
			a = a >> (Bigprime::basebitnum);
		} while (a);
	}
	static void div(const Bigprime& a, const Bigprime& b, Bigprime& result, Bigprime& ca);
private:
	vector<base_t> _data;
	//数据存储	
	bool _isnegative;
};
