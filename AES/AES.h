class AES
{
public:
	AES(unsigned char* key);
	virtual ~AES();
	unsigned char* Encrypt(unsigned char* input);//加密
	unsigned char* Decrypt(unsigned char* input);//解密
	void* Encrypt(void* input, int length = 0);
	void* Decrypt(void* input, int length);
private:
	unsigned char Sbox[256];//S盒
	unsigned char InvSbox[256];//S盒逆
	unsigned char w[11][4][4];

	void KeyExpansion(unsigned char* key, unsigned char w[][4][4]);//密钥编排
	unsigned char FFmul(unsigned char a, unsigned char b);

	void SubBytes(unsigned char state[][4]);//字节替换
	void ShiftRows(unsigned char state[][4]);//行移位变换
	void MixColumns(unsigned char state[][4]);//列混合变换
	void AddRoundKey(unsigned char state[][4], unsigned char k[][4]);//密钥加

	void InvSubBytes(unsigned char state[][4]);//字节逆变换
	void InvShiftRows(unsigned char state[][4]);//行移位逆变换
	void InvMixColumns(unsigned char state[][4]);//列混合逆变换
};
#pragma once
