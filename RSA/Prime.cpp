#include"Prime.h"
#include<cassert>
int Bigprime::base_char = 8;
int Bigprime::base = 0xFFFFFFFF;
int Bigprime::basebit = 5;
int Bigprime::basebitchar = 0x1F;
int Bigprime::basebitnum = 32;
Bigprime Bigprime::Zero(0);
Bigprime Bigprime::One(1);
Bigprime Bigprime::Two(2);

Bigprime operator + (const Bigprime& a, const Bigprime& b)
{
	Bigprime ca(a);
	return ca.add(b);
}

Bigprime operator - (const Bigprime& a, const Bigprime& b)
{
	Bigprime ca(a);
	return ca.sub(b);
}

Bigprime operator * (const Bigprime& a, const Bigprime& b)
{
	if (a == (Bigprime::Zero) || b == (Bigprime::Zero))
		return Bigprime::Zero;

	const Bigprime& big = a._data.size() > b._data.size() ? a : b;
	const Bigprime& small = (&big) == (&a) ? b : a;

	Bigprime result(0);

	Bigprime::bit bt(small);
	for (int i = bt.size() - 1; i >= 0; --i)
	{
		if (bt.at(i))
		{
			Bigprime temp(big, false);
			temp.leftShift(i);
			result.add(temp);
		}
	}
	result._isnegative = !(a._isnegative == b._isnegative);
	return result;
}

Bigprime operator / (const Bigprime& a, const Bigprime& b)
{
	assert(b != (Bigprime::Zero));
	if (a.equals(b))//绝对值相等
		return (a._isnegative == b._isnegative) ? Bigprime(1) : Bigprime(-1);
	else if (a.small_Than(b))//绝对值小于
		return Bigprime::Zero;
	else
	{
		Bigprime result, ca;
		Bigprime::div(a, b, result, ca);
		return result;
	}
}

Bigprime operator % (const Bigprime& a, const Bigprime& b)
{
	assert(b != (Bigprime::Zero));
	if (a.equals(b))
		return Bigprime::Zero;
	else if (a.small_Than(b))
		return a;
	else
	{
		Bigprime result, ca;
		Bigprime::div(a, b, result, ca);
		return ca;
	}
}

void Bigprime::div(const Bigprime& a, const Bigprime& b, Bigprime& result, Bigprime& ca)
{
	//1.复制a,b
	Bigprime cb(b, false);
	ca._isnegative = false;
	ca._data = a._data;

	Bigprime::bit bit_b(cb);
	//位数对齐
	while (true)//绝对值小于
	{
		Bigprime::bit bit_a(ca);
		int len = bit_a.size() - bit_b.size();
		Bigprime temp;
		//找到移位的
		while (len >= 0)
		{
			temp = cb << len;
			if (temp.small_Or_Equals(ca))
				break;
			--len;
		}
		if (len < 0)
			break;
		Bigprime::base_t n = 0;
		while (temp.small_Or_Equals(ca))
		{
			ca.sub(temp);
			++n;
		}
		Bigprime kk(n);
		if (len)
			kk.leftShift(len);
		result.add(kk);
	}
	result.trim();
}

bool operator < (const Bigprime& a, const Bigprime& b)
{
	if (a._isnegative == b._isnegative)
	{
		if (a._isnegative == false)
			return a.small_Than(b);
		else
			return !(a.small_Or_Equals(b));
	}
	else
	{
		if (a._isnegative == false)
			return true;
		else
			return false;
	}
}

bool operator <= (const Bigprime& a, const Bigprime& b)
{
	if (a._isnegative == b._isnegative)
	{//同号
		if (a._isnegative == false)
			return a.small_Or_Equals(b);
		else
			return !(a.small_Than(b));
	}
	else//异号
	{
		if (a._isnegative == false)
			return true;
		else
			return false;
	}
}

bool operator == (const Bigprime& a, const Bigprime& b)
{
	return a._data == b._data && a._isnegative == b._isnegative;
}

ostream& operator << (ostream& out, const Bigprime& a)
{
	static char hex[] = { '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F' };
	if (a._isnegative)
		out << "-";
	Bigprime::base_t T = 0x0F;
	std::string str;
	for (Bigprime::data_t::const_iterator it = a._data.begin(); it != a._data.end(); ++it)
	{
		Bigprime::base_t ch = (*it);
		for (int j = 0; j < Bigprime::base_char; ++j)
		{
			str.push_back(hex[ch & (T)]);
			ch = ch >> 4;
		}
	}
	reverse(str.begin(), str.end());
	out << str;
	return out;
}

Bigprime operator <<(const Bigprime& a, unsigned int n)
{
	Bigprime ca(a);
	return ca.leftShift(n);
}

Bigprime& Bigprime::leftShift(const unsigned int n)
{
	int k = n >> (Bigprime::basebit);//5
	int off = n & (Bigprime::basebitchar);//0xFF

	int inc = (off == 0) ? k : 1 + k;
	for (int i = 0; i < inc; ++i)
		_data.push_back(0);

	if (k)
	{
		inc = (off == 0) ? 1 : 2;
		for (int i = _data.size() - inc; i >= k; --i)
			_data[i] = _data[i - k];
		for (int i = 0; i < k; ++i)
			_data[i] = 0;
	}

	if (off)
	{
		Bigprime::base_t T = Bigprime::base;//0xffffffff
		T = T << (Bigprime::basebitnum - off);//32
											//左移
		Bigprime::base_t ch = 0;
		for (std::size_t i = 0; i < _data.size(); ++i)
		{
			Bigprime::base_t t = _data[i];
			_data[i] = (t << off) | ch;
			ch = (t & T) >> (Bigprime::basebitnum - off);//32,最高位
		}
	}
	trim();
	return *this;
}

Bigprime& Bigprime::rightShift(const unsigned int n)
{
	int k = n >> (Bigprime::basebit);//5
	int off = n & (Bigprime::basebitchar);//0xFF

	if (k)
	{
		for (int i = 0; i > k; ++i)
			_data[i] = _data[i + k];
		for (int i = 0; i < k; ++i)
			_data.pop_back();
		if (_data.size() == 0)
			_data.push_back(0);
	}

	if (off)
	{
		Bigprime::base_t T = Bigprime::base;//0xFFFFFFFF
		T = T >> (Bigprime::basebitnum - off);//32
											//左移
		Bigprime::base_t ch = 0;
		for (int i = _data.size() - 1; i >= 0; --i)
		{
			Bigprime::base_t t = _data[i];
			_data[i] = (t >> off) | ch;
			ch = (t & T) << (Bigprime::basebitnum - off);//32,最高位
		}
	}
	trim();
	return *this;
}

Bigprime& Bigprime::sub(const Bigprime& b)
{
	if (b._isnegative == _isnegative)
	{//同号

		Bigprime::data_t& res = _data;
		if (!(small_Than(b)))//绝对值大于b
		{
			int cn = 0;//借位
					   //大数减小数
			for (std::size_t i = 0; i < b._data.size(); ++i)
			{
				Bigprime::base_t temp = res[i];
				res[i] = (res[i] - b._data[i] - cn);
				cn = temp < res[i] ? 1 : temp < b._data[i] ? 1 : 0;
			}

			for (std::size_t i = b._data.size(); i < _data.size() && cn != 0; ++i)
			{
				Bigprime::base_t temp = res[i];
				res[i] = res[i] - cn;
				cn = temp < cn;
			}
			trim();
		}
		else//绝对值小于b
		{
			_data = (b - (*this))._data;
			_isnegative = !_isnegative;
		}
	}
	else
	{//异号的情况
		bool isnegative = _isnegative;
		_isnegative = b._isnegative;
		add(b);
		_isnegative = isnegative;
	}
	return *this;
}

Bigprime& Bigprime::add(const Bigprime& b)
{
	if (_isnegative == b._isnegative)
	{//同号
	 //引用
		Bigprime::data_t& res = _data;
		int len = b._data.size() - _data.size();

		while ((len--) > 0)//高位补0
			res.push_back(0);

		int cn = 0;//进位
		for (std::size_t i = 0; i < b._data.size(); ++i)
		{
			Bigprime::base_t temp = res[i];
			res[i] = res[i] + b._data[i] + cn;
			cn = temp > res[i] ? 1 : temp > (temp + b._data[i]) ? 1 : 0;//0xFFFFFFFF
		}

		for (std::size_t i = b._data.size(); i < _data.size() && cn != 0; ++i)
		{
			Bigprime::base_t temp = res[i];
			res[i] = (res[i] + cn);
			cn = temp > res[i];
		}

		if (cn != 0)
			res.push_back(cn);

		trim();
	}
	else
	{//异号的情况
		bool isnegative;
		if (small_Than(b))//绝对值小于b
			isnegative = b._isnegative;
		else if (equals(b))//绝对值等于b
			isnegative = false;
		else//绝对值大于b
			isnegative = _isnegative;

		_isnegative = b._isnegative;
		sub(b);
		_isnegative = isnegative;
	}
	return *this;
}
//模幂运算
Bigprime Bigprime::Mod_big_int(const Bigprime& exp, const Bigprime& p)const
{
	Bigprime::bit t(exp);

	Bigprime d(1);
	for (int i = t.size() - 1; i >= 0; --i)
	{
		d = (d * d) % p;
		if (t.at(i))
			d = (d * (*this)) % p;
	}
	return d;
}
//扩展欧几里得算法求乘法逆元
Bigprime Bigprime::extend_Euclid(const Bigprime& m)
{
	assert(m._isnegative == false);//m为正数
	Bigprime a[3], b[3], t[3];
	a[0] = 1; a[1] = 0; a[2] = m;
	b[0] = 0; b[1] = 1; b[2] = *this;
	if (b[2] == Bigprime::Zero || b[2] == Bigprime::One)
		return b[2];

	while (true)
	{
		if (b[2] == Bigprime::One)
		{
			if (b[1]._isnegative == true)//负数
				b[1] = (b[1] % m + m) % m;
			return b[1];
		}

		Bigprime q = a[2] / b[2];
		for (int i = 0; i < 3; ++i)
		{
			t[i] = a[i] - q * b[i];
			a[i] = b[i];
			b[i] = t[i];
		}
	}
}

std::size_t Bigprime::bit::size()
{
	return _size;
}

bool Bigprime::bit::at(std::size_t i)
{
	std::size_t index = i >> (Bigprime::basebit);
	std::size_t off = i & (Bigprime::basebitchar);
	Bigprime::base_t t = _bitvec[index];
	return (t & (1 << off));
}

Bigprime::bit::bit(const Bigprime& ba)
{
	_bitvec = ba._data;
	Bigprime::base_t a = _bitvec[_bitvec.size() - 1];//最高位
	_size = _bitvec.size() << (Bigprime::basebit);
	Bigprime::base_t t = 1 << (Bigprime::basebitnum - 1);

	if (a == 0)
		_size -= (Bigprime::basebitnum);
	else
	{
		while (!(a & t))
		{
			--_size;
			t = t >> 1;
		}
	}
}

bool Bigprime::small_Than(const Bigprime& b)const
{
	if (_data.size() == b._data.size())
	{
		for (Bigprime::data_t::const_reverse_iterator it = _data.rbegin(), it_b = b._data.rbegin();
			it != _data.rend(); ++it, ++it_b)
			if ((*it) != (*it_b))
				return (*it) < (*it_b);
		return false;//相等
	}
	else
		return _data.size() < b._data.size();
}

bool Bigprime::small_Or_Equals(const Bigprime& b)const
{
	if (_data.size() == b._data.size())
	{
		for (Bigprime::data_t::const_reverse_iterator it = _data.rbegin(), it_b = b._data.rbegin();
			it != _data.rend(); ++it, ++it_b)
			if ((*it) != (*it_b))
				return (*it) < (*it_b);
		return true;//相等
	}
	else
		return _data.size() < b._data.size();
}

bool Bigprime::equals(const Bigprime& a)const
{
	return _data == a._data;
}