class AES
{
public:
	AES(unsigned char* key);
	virtual ~AES();
	unsigned char* Encrypt(unsigned char* input);//����
	unsigned char* Decrypt(unsigned char* input);//����
	void* Encrypt(void* input, int length = 0);
	void* Decrypt(void* input, int length);
private:
	unsigned char Sbox[256];//S��
	unsigned char InvSbox[256];//S����
	unsigned char w[11][4][4];

	void KeyExpansion(unsigned char* key, unsigned char w[][4][4]);//��Կ����
	unsigned char FFmul(unsigned char a, unsigned char b);

	void SubBytes(unsigned char state[][4]);//�ֽ��滻
	void ShiftRows(unsigned char state[][4]);//����λ�任
	void MixColumns(unsigned char state[][4]);//�л�ϱ任
	void AddRoundKey(unsigned char state[][4], unsigned char k[][4]);//��Կ��

	void InvSubBytes(unsigned char state[][4]);//�ֽ���任
	void InvShiftRows(unsigned char state[][4]);//����λ��任
	void InvMixColumns(unsigned char state[][4]);//�л����任
};
#pragma once
