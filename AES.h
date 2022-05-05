#pragma once
#include <iostream>
#include <bitset>
#include <boost/multiprecision/cpp_int.hpp>
#include "RSA.h"

using namespace std;
using namespace boost::multiprecision;

const int  a = 57;
const int  ai = 248;
const int  b = 5;
const int  p = 257;

const int  as = 57;
const int  ais = 3089362441;
const int  bs = 5;
const int  ps = 4294967296;

const bitset<8> rc[] = {0x6c,0xd8,0xab,0x4d,0x9a,0x2f,0x5e, 0xbc, 0x63, 0xc6, 0x97, 0x35, 0x6a, 0xd4, 0xb3};

//                               r  c rows = 4 col = 8 containg an 8-bit bitset
void AESEncrypt(bitset<8> cipher[8][4], char msg[32], bitset<256> key);
void AESDecrypt(bitset<8> cipher[8][4], bitset<256> key);

void subByte(bitset<8> cipher[8][4]);
void inverseSubByte(bitset<8> cipher[8][4]);
void shiftRow(bitset<8> cipher[8][4]);
void inverseShiftRow(bitset<8> cipher[8][4]);
void mixCol(bitset<8> cipher[8][4]);
void inverseMixCol(bitset<8> cipher[8][4]);
void keyAdd(bitset<8> cipher[8][4], bitset<8>k[15][8][4], int i);

void createKeys(bitset<256> key, bitset<8> set[15][8][4]);
bitset<32> g(bitset<32> word, int i);

int affineTransformation(int x);
int inverseAffineTransformation(int x);
int  affineTransformationS(int x);
int inverseAffineTransformationS(int x);

bitset<8> multiply3(bitset<8> a);
bitset<8> multiply2(bitset<8> a);

bitset<8> multiply9(bitset<8> a);
bitset<8> multiply11(bitset<8> a);
bitset<8> multiply13(bitset<8> a);
bitset<8> multiply14(bitset<8> a);

int convertToInt(char message);
char convertToString(int msg);

void AESEncrypt(bitset<8> cipher[8][4], char msg[32], bitset<256> key)
{
	//converting message to 8x8 matrix
	int b = 0;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			cipher[i][j] = convertToInt(msg[b]);
			b++;	
		}
	}
	cout << endl << "text" << endl;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			cout << convertToString(cipher[i][j].to_ullong());
		}
	}

	//end conversion to matrix
	bitset<8> k[15][8][4];
	createKeys(key, k);
	//encrypt/decrypt test
	//cipher[3][1] = 33;
	//cout << endl << "txt\t\t" << cipher[0][0] << ":" << cipher[3][1].to_ullong() << endl;
	keyAdd(cipher, k, 1);
	//cout << "keyadd1\t\t" << cipher[1][0] << ":" << cipher[0][0].to_ullong() << endl;
	subByte(cipher);
	//cout << "sub\t\t" << cipher[1][0] << ":" << cipher[0][0].to_ullong() << endl;
	shiftRow(cipher);
	//cout << "shift\t\t" << cipher[1][0] << ":" << cipher[0][0].to_ullong() << endl;
	mixCol(cipher);
	//cout << "mixcol\t\t" << cipher[1][0] << ":" << cipher[0][0].to_ullong() << endl;
	keyAdd(cipher, k, 1);
	//cout << "keyadd2\t\t" << cipher[1][0] << ":" << cipher[0][0].to_ullong() << endl;
	//cout << "-------------------------------------------------------------------" << endl;

	shiftRow(cipher);
	//cout << "shift\t\t" << cipher[0][0] << ":" << cipher[0][0].to_ullong() << endl;
	mixCol(cipher);
	//cout << "mixcol\t\t" << cipher[0][0] << ":" << cipher[0][0].to_ullong() << endl;
	keyAdd(cipher, k, 1);
	//cout << "keyadd2\t\t" << cipher[0][0] << ":" << cipher[0][0].to_ullong() << endl << endl;
	//cout << "-------------------------------------------------------------------" << endl;

	shiftRow(cipher);
	//cout << "shift\t\t" << cipher[0][0] << ":" << cipher[0][0].to_ullong() << endl;
	mixCol(cipher);
	//cout << "mixcol\t\t" << cipher[0][0] << ":" << cipher[0][0].to_ullong() << endl;
	keyAdd(cipher, k, 1);
	//cout << "keyadd2\t\t" << cipher[0][0] << ":" << cipher[0][0].to_ullong() << endl << endl;
	//cout << "-------------------------------------------------------------------" << endl;

	shiftRow(cipher);
	//cout << "shift\t\t" << cipher[0][0] << ":" << cipher[0][0].to_ullong() << endl;
	mixCol(cipher);
	//cout << "mixcol\t\t" << cipher[0][0] << ":" << cipher[0][0].to_ullong() << endl;
	keyAdd(cipher, k, 2);
	//cout << "keyadd2\t\t" << cipher[0][0] << ":" << cipher[0][0].to_ullong() << endl << endl;
	//cout << "-------------------------------------------------------------------" << endl;

	shiftRow(cipher);
	//cout << "shift\t\t" << cipher[0][0] << ":" << cipher[0][0].to_ullong() << endl;
	mixCol(cipher);
	//cout << "mixcol\t\t" << cipher[0][0] << ":" << cipher[0][0].to_ullong() << endl;
	keyAdd(cipher, k, 3);
	//cout << "keyadd2\t\t" << cipher[0][0] << ":" << cipher[0][0].to_ullong() << endl << endl;
	//cout << "-------------------------------------------------------------------" << endl;

	shiftRow(cipher);
	//cout << "shift\t\t" << cipher[0][0] << ":" << cipher[0][0].to_ullong() << endl;
	mixCol(cipher);
	//cout << "mixcol\t\t" << cipher[0][0] << ":" << cipher[0][0].to_ullong() << endl;
	keyAdd(cipher, k, 4);
	//cout << "keyadd2\t\t" << cipher[0][0] << ":" << cipher[0][0].to_ullong() << endl << endl;
	//cout << "-------------------------------------------------------------------" << endl;

	shiftRow(cipher);
	//cout << "shift\t\t" << cipher[0][0] << ":" << cipher[0][0].to_ullong() << endl;
	mixCol(cipher);
	//cout << "mixcol\t\t" << cipher[0][0] << ":" << cipher[0][0].to_ullong() << endl;
	keyAdd(cipher, k, 5);
	//cout << "keyadd2\t\t" << cipher[0][0] << ":" << cipher[0][0].to_ullong() << endl << endl;
	//cout << "-------------------------------------------------------------------" << endl;

	shiftRow(cipher);
	//cout << "shift\t\t" << cipher[0][0] << ":" << cipher[0][0].to_ullong() << endl;
	mixCol(cipher);
	//cout << "mixcol\t\t" << cipher[0][0] << ":" << cipher[0][0].to_ullong() << endl;
	keyAdd(cipher, k, 6);
	//cout << "keyadd2\t\t" << cipher[0][0] << ":" << cipher[0][0].to_ullong() << endl << endl;
	//cout << "-------------------------------------------------------------------" << endl;
	shiftRow(cipher);
	//cout << "shift\t\t" << cipher[0][0] << ":" << cipher[0][0].to_ullong() << endl;
	mixCol(cipher);
	//cout << "mixcol\t\t" << cipher[0][0] << ":" << cipher[0][0].to_ullong() << endl;
	keyAdd(cipher, k, 7);
	//cout << "keyadd2\t\t" << cipher[0][0] << ":" << cipher[0][0].to_ullong() << endl << endl;
	//cout << "-------------------------------------------------------------------" << endl;
	shiftRow(cipher);
	//cout << "shift\t\t" << cipher[0][0] << ":" << cipher[0][0].to_ullong() << endl;
	mixCol(cipher);
	//cout << "mixcol\t\t" << cipher[0][0] << ":" << cipher[0][0].to_ullong() << endl;
	keyAdd(cipher, k, 8);
	//cout << "keyadd2\t\t" << cipher[0][0] << ":" << cipher[0][0].to_ullong() << endl << endl;
	//cout << "-------------------------------------------------------------------" << endl;

	shiftRow(cipher);
	//cout << "shift\t\t" << cipher[0][0] << ":" << cipher[0][0].to_ullong() << endl;
	mixCol(cipher);
	//cout << "mixcol\t\t" << cipher[0][0] << ":" << cipher[0][0].to_ullong() << endl;
	keyAdd(cipher, k, 9);
	//cout << "keyadd2\t\t" << cipher[0][0] << ":" << cipher[0][0].to_ullong() << endl << endl;
	//cout << "-------------------------------------------------------------------" << endl;

	shiftRow(cipher);
	//cout << "shift\t\t" << cipher[0][0] << ":" << cipher[0][0].to_ullong() << endl;
	mixCol(cipher);
	//cout << "mixcol\t\t" << cipher[0][0] << ":" << cipher[0][0].to_ullong() << endl;
	keyAdd(cipher, k, 10);
	//cout << "keyadd2\t\t" << cipher[0][0] << ":" << cipher[0][0].to_ullong() << endl << endl;
	//cout << "-------------------------------------------------------------------" << endl;

	shiftRow(cipher);
	//cout << "shift\t\t" << cipher[0][0] << ":" << cipher[0][0].to_ullong() << endl;
	mixCol(cipher);
	//cout << "mixcol\t\t" << cipher[0][0] << ":" << cipher[0][0].to_ullong() << endl;
	keyAdd(cipher, k, 11);
	//cout << "keyadd2\t\t" << cipher[0][0] << ":" << cipher[0][0].to_ullong() << endl << endl;
	//cout << "-------------------------------------------------------------------" << endl;

	shiftRow(cipher);
	//cout << "shift\t\t" << cipher[0][0] << ":" << cipher[0][0].to_ullong() << endl;
	mixCol(cipher);
	//cout << "mixcol\t\t" << cipher[0][0] << ":" << cipher[0][0].to_ullong() << endl;
	keyAdd(cipher, k, 12);
	//cout << "keyadd2\t\t" << cipher[0][0] << ":" << cipher[0][0].to_ullong() << endl << endl;
	//cout << "-------------------------------------------------------------------" << endl;
	cout << endl << endl << "encrypted" << endl;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			cout << cipher[i][j].to_ullong();
		}
	}
	cout << endl;
}


void AESDecrypt(bitset<8> cipher[8][4], bitset<256> key)
{
	bitset<8> k[15][8][4];
	createKeys(key, k);
	//cout << "-------------------------------------------------------------------" << endl;
	keyAdd(cipher, k, 12);
	//cout << "keyadd2i\t" << cipher[0][0] << ":" << cipher[0][0].to_ullong() << endl;
	inverseMixCol(cipher);
	//cout << "mixcoli\t\t" << cipher[0][0] << ":" << cipher[0][0].to_ullong() << endl;
	inverseShiftRow(cipher);
	//cout << "shifti\t\t" << cipher[0][0] << ":" << cipher[0][0].to_ullong() << endl;
	//cout << "-------------------------------------------------------------------" << endl;
	keyAdd(cipher, k, 11);
	//cout << "keyadd2i\t" << cipher[0][0] << ":" << cipher[0][0].to_ullong() << endl;
	inverseMixCol(cipher);
	//cout << "mixcoli\t\t" << cipher[0][0] << ":" << cipher[0][0].to_ullong() << endl;
	inverseShiftRow(cipher);
	//cout << "shifti\t\t" << cipher[0][0] << ":" << cipher[0][0].to_ullong() << endl;
	//cout << "-------------------------------------------------------------------" << endl;
	keyAdd(cipher, k, 10);
	//cout << "keyadd2i\t" << cipher[0][0] << ":" << cipher[0][0].to_ullong() << endl;
	inverseMixCol(cipher);
	//cout << "mixcoli\t\t" << cipher[0][0] << ":" << cipher[0][0].to_ullong() << endl;
	inverseShiftRow(cipher);
	//cout << "shifti\t\t" << cipher[0][0] << ":" << cipher[0][0].to_ullong() << endl;
	//cout << "-------------------------------------------------------------------" << endl;
	keyAdd(cipher, k, 9);
	//cout << "keyadd2i\t" << cipher[0][0] << ":" << cipher[0][0].to_ullong() << endl;
	inverseMixCol(cipher);
	//cout << "mixcoli\t\t" << cipher[0][0] << ":" << cipher[0][0].to_ullong() << endl;
	inverseShiftRow(cipher);
	//cout << "shifti\t\t" << cipher[0][0] << ":" << cipher[0][0].to_ullong() << endl;

	//cout << "-------------------------------------------------------------------" << endl;
	keyAdd(cipher, k, 8);
	//cout << "keyadd2i\t" << cipher[0][0] << ":" << cipher[0][0].to_ullong() << endl;
	inverseMixCol(cipher);
	//cout << "mixcoli\t\t" << cipher[0][0] << ":" << cipher[0][0].to_ullong() << endl;
	inverseShiftRow(cipher);
	//cout << "shifti\t\t" << cipher[0][0] << ":" << cipher[0][0].to_ullong() << endl;
	//cout << "-------------------------------------------------------------------" << endl;
	keyAdd(cipher, k, 7);
	//cout << "keyadd2i\t" << cipher[0][0] << ":" << cipher[0][0].to_ullong() << endl;
	inverseMixCol(cipher);
	//cout << "mixcoli\t\t" << cipher[0][0] << ":" << cipher[0][0].to_ullong() << endl;
	inverseShiftRow(cipher);
	//cout << "shifti\t\t" << cipher[0][0] << ":" << cipher[0][0].to_ullong() << endl;
	//cout << "-------------------------------------------------------------------" << endl;
	keyAdd(cipher, k, 6);
	//cout << "keyadd2i\t" << cipher[0][0] << ":" << cipher[0][0].to_ullong() << endl;
	inverseMixCol(cipher);
	//cout << "mixcoli\t\t" << cipher[0][0] << ":" << cipher[0][0].to_ullong() << endl;
	inverseShiftRow(cipher);
	//cout << "shifti\t\t" << cipher[0][0] << ":" << cipher[0][0].to_ullong() << endl;
	//cout << "-------------------------------------------------------------------" << endl;
	keyAdd(cipher, k, 5);
	//cout << "keyadd2i\t" << cipher[0][0] << ":" << cipher[0][0].to_ullong() << endl;
	inverseMixCol(cipher);
	//cout << "mixcoli\t\t" << cipher[0][0] << ":" << cipher[0][0].to_ullong() << endl;
	inverseShiftRow(cipher);
	//cout << "shifti\t\t" << cipher[0][0] << ":" << cipher[0][0].to_ullong() << endl;
	//cout << "-------------------------------------------------------------------" << endl;
	keyAdd(cipher, k, 4);
	//cout << "keyadd2i\t" << cipher[0][0] << ":" << cipher[0][0].to_ullong() << endl;
	inverseMixCol(cipher);
	//cout << "mixcoli\t\t" << cipher[0][0] << ":" << cipher[0][0].to_ullong() << endl;
	inverseShiftRow(cipher);
	//cout << "shifti\t\t" << cipher[0][0] << ":" << cipher[0][0].to_ullong() << endl;
	//cout << "-------------------------------------------------------------------" << endl;
	keyAdd(cipher, k, 3);
	//cout << "keyadd2i\t" << cipher[0][0] << ":" << cipher[0][0].to_ullong() << endl;
	inverseMixCol(cipher);
	//cout << "mixcoli\t\t" << cipher[0][0] << ":" << cipher[0][0].to_ullong() << endl;
	inverseShiftRow(cipher);
	//cout << "shifti\t\t" << cipher[0][0] << ":" << cipher[0][0].to_ullong() << endl;
	//cout << "-------------------------------------------------------------------" << endl;
	keyAdd(cipher, k, 2);
	//cout << "keyadd2i\t" << cipher[0][0] << ":" << cipher[0][0].to_ullong() << endl;
	inverseMixCol(cipher);
	//cout << "mixcoli\t\t" << cipher[0][0] << ":" << cipher[0][0].to_ullong() << endl;
	inverseShiftRow(cipher);
	//cout << "shifti\t\t" << cipher[0][0] << ":" << cipher[0][0].to_ullong() << endl;
	//cout << "-------------------------------------------------------------------" << endl;
	keyAdd(cipher, k, 1);
	//cout << "keyadd2i\t" << cipher[0][0] << ":" << cipher[0][0].to_ullong() << endl;
	inverseMixCol(cipher);
	//cout << "mixcoli\t\t" << cipher[0][0] << ":" << cipher[0][0].to_ullong() << endl;
	inverseShiftRow(cipher);
	//cout << "shifti\t\t" << cipher[0][0] << ":" << cipher[0][0].to_ullong() << endl;

	//cout << "-------------------------------------------------------------------" << endl;
	keyAdd(cipher, k, 1);
	//cout << "keyadd2i\t" << cipher[0][0] << ":" << cipher[0][0].to_ullong() << endl;
	inverseMixCol(cipher);
	//cout << "mixcoli\t\t" << cipher[0][0] << ":" << cipher[0][0].to_ullong() << endl;
	inverseShiftRow(cipher);
	//cout << "shifti\t\t" << cipher[0][0] << ":" << cipher[0][0].to_ullong() << endl;

	//cout << "-------------------------------------------------------------------" << endl;
	keyAdd(cipher, k, 1);
	//cout << "keyadd2i\t" << cipher[0][0] << ":" << cipher[0][0].to_ullong() << endl;
	inverseMixCol(cipher);
	//cout << "mixcoli\t\t" << cipher[0][0] << ":" << cipher[0][0].to_ullong() << endl;
	inverseShiftRow(cipher);
	//cout << "shifti\t\t" << cipher[0][0] << ":" << cipher[0][0].to_ullong() << endl;
	inverseSubByte(cipher);
	//cout << "subi\t\t" << cipher[0][0] << ":" << cipher[0][0].to_ullong() << endl;
	keyAdd(cipher, k, 1);
	//cout << "keyadd1i\t" << cipher[0][0] << ":" << cipher[3][1].to_ullong() << endl;
	cout << endl << "decrypted" << endl;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			cout << convertToString(cipher[i][j].to_ullong());
		}
	}
}

void subByte(bitset<8> cipher[8][4])
{
	int count = 0;
	long long tmp;
	bitset<8> byte;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			tmp = cipher[i][j].to_ullong();
			tmp = affineTransformation(int(tmp));
			byte = int(tmp);
			cipher[i][j] = byte;
		}
	}
}

void inverseSubByte(bitset<8> cipher[8][4])
{
	int count = 0;
	long long tmp;
	bitset<8> byte;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			tmp = cipher[i][j].to_ullong();
			tmp = inverseAffineTransformation(int(tmp));
			byte = int(tmp);
			cipher[i][j] = byte;
		}
	}
}

void shiftRow(bitset<8> cipher[8][4])
{
	bitset<8> tmp[8][4];
	//1st row
	for (int i = 0; i < 4; i++)
	{
		tmp[0][i] = cipher[0][i];
	}
	//2nd row
	tmp[1][0] = cipher[1][1];
	tmp[1][1] = cipher[1][2];
	tmp[1][2] = cipher[1][3];
	tmp[1][3] = cipher[1][0];
	//3rd row
	tmp[2][0] = cipher[2][2];
	tmp[2][1] = cipher[2][3];
	tmp[2][2] = cipher[2][0];
	tmp[2][3] = cipher[2][1];
	//4th row
	tmp[3][0] = cipher[3][3];
	tmp[3][1] = cipher[3][0];
	tmp[3][2] = cipher[3][1];
	tmp[3][3] = cipher[3][2];
	//5st row
	for (int i = 0; i < 4; i++)
	{
		tmp[4][i] = cipher[4][i];
	}
	//6nd row
	tmp[5][0] = cipher[5][1];
	tmp[5][1] = cipher[5][2];
	tmp[5][2] = cipher[5][3];
	tmp[5][3] = cipher[5][0];
	//7rd row
	tmp[6][0] = cipher[6][2];
	tmp[6][1] = cipher[6][3];
	tmp[6][2] = cipher[6][0];
	tmp[6][3] = cipher[6][1];
	//8th row
	tmp[7][0] = cipher[7][3];
	tmp[7][1] = cipher[7][0];
	tmp[7][2] = cipher[7][1];
	tmp[7][3] = cipher[7][2];
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			cipher[i][j] = tmp[i][j];
		}
	}
}

void inverseShiftRow(bitset<8> cipher[8][4])
{
	bitset<8> tmp[8][4];
	//1st row
	for (int i = 0; i < 4; i++)
	{
		tmp[0][i] = cipher[0][i];
	}
	//2nd row
	tmp[1][0] = cipher[1][3];
	tmp[1][1] = cipher[1][0];
	tmp[1][2] = cipher[1][1];
	tmp[1][3] = cipher[1][2];
	//3rd row
	tmp[2][0] = cipher[2][2];
	tmp[2][1] = cipher[2][3];
	tmp[2][2] = cipher[2][0];
	tmp[2][3] = cipher[2][1];
	//4th row
	tmp[3][0] = cipher[3][1];
	tmp[3][1] = cipher[3][2];
	tmp[3][2] = cipher[3][3];
	tmp[3][3] = cipher[3][0];
	//5st row
	for (int i = 0; i < 4; i++)
	{
		tmp[4][i] = cipher[4][i];
	}
	//6nd row
	tmp[5][0] = cipher[5][3];
	tmp[5][1] = cipher[5][0];
	tmp[5][2] = cipher[5][1];
	tmp[5][3] = cipher[5][2];
	//7rd row
	tmp[6][0] = cipher[6][2];
	tmp[6][1] = cipher[6][3];
	tmp[6][2] = cipher[6][0];
	tmp[6][3] = cipher[6][1];
	//8th row
	tmp[7][0] = cipher[7][1];
	tmp[7][1] = cipher[7][2];
	tmp[7][2] = cipher[7][3];
	tmp[7][3] = cipher[7][0];
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			cipher[i][j] = tmp[i][j];
		}
	}
}

void mixCol(bitset<8> cipher[8][4])
{
	bitset<8> tmp[8][4], x1, x2, x3, x4,
		t = 27 ;

	for (int i = 0; i < 4; i++) 
	{
		x1 = multiply2(cipher[0][i]);
		x2 = multiply3(cipher[1][i]);
		x3 = cipher[2][i];
		x4 = cipher[3][i];
		tmp[0][i] = x1 ^ x2 ^ x3 ^ x4;
		x1 = cipher[0][i];
		x2 = multiply2(cipher[1][i]);
		x3 = multiply3(cipher[2][i]);
		x4 = cipher[3][i];
		tmp[1][i] = x1 ^ x2 ^ x3 ^ x4;
		x1 = cipher[0][i];
		x2 = cipher[1][i];
		x3 = multiply2(cipher[2][i]);
		x4 = multiply3(cipher[3][i]);
		tmp[2][i] = x1 ^ x2 ^ x3 ^ x4;
		x1 = multiply3(cipher[0][i]);
		x2 = cipher[1][i];
		x3 = cipher[2][i];
		x4 = multiply2(cipher[3][i]);
		tmp[3][i] = x1 ^ x2 ^ x3 ^ x4;
		x1 = multiply2(cipher[4][i]);
		x2 = multiply3(cipher[5][i]);
		x3 = cipher[6][i];
		x4 = cipher[7][i];
		tmp[4][i] = x1 ^ x2 ^ x3 ^ x4;
		x1 = cipher[4][i];
		x2 = multiply2(cipher[5][i]);
		x3 = multiply3(cipher[6][i]);
		x4 = cipher[7][i];
		tmp[5][i] = x1 ^ x2 ^ x3 ^ x4;
		x1 = cipher[4][i];
		x2 = cipher[5][i];
		x3 = multiply2(cipher[6][i]);
		x4 = multiply3(cipher[7][i]);
		tmp[6][i] = x1 ^ x2 ^ x3 ^ x4;
		x1 = multiply3(cipher[4][i]);
		x2 = cipher[5][i];
		x3 = cipher[6][i];
		x4 = multiply2(cipher[7][i]);
		tmp[7][i] = x1 ^ x2 ^ x3 ^ x4;
	}
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			cipher[i][j] = tmp[i][j];
		}
	}
}

void inverseMixCol(bitset<8> cipher[8][4])
{
	bitset<8> tmp[8][4], x1, x2, x3, x4,
		t = 27;

	for (int i = 0; i < 4; i++)
	{
		x1 = multiply14(cipher[0][i]);
		x2 = multiply11(cipher[1][i]);
		x3 = multiply13(cipher[2][i]);
		x4 = multiply9(cipher[3][i]);
		tmp[0][i] = x1 ^ x2 ^ x3 ^ x4;
		x1 = multiply9(cipher[0][i]);
		x2 = multiply14(cipher[1][i]);
		x3 = multiply11(cipher[2][i]);
		x4 = multiply13(cipher[3][i]);
		tmp[1][i] = x1 ^ x2 ^ x3 ^ x4;
		x1 = multiply13(cipher[0][i]);
		x2 = multiply9(cipher[1][i]);
		x3 = multiply14(cipher[2][i]);
		x4 = multiply11(cipher[3][i]);
		tmp[2][i] = x1 ^ x2 ^ x3 ^ x4;
		x1 = multiply11(cipher[0][i]);
		x2 = multiply13(cipher[1][i]);
		x3 = multiply9(cipher[2][i]);
		x4 = multiply14(cipher[3][i]);
		tmp[3][i] = x1 ^ x2 ^ x3 ^ x4;
		//
		x1 = multiply14(cipher[4][i]);
		x2 = multiply11(cipher[5][i]);
		x3 = multiply13(cipher[6][i]);
		x4 = multiply9(cipher[7][i]);
		tmp[4][i] = x1 ^ x2 ^ x3 ^ x4;
		x1 = multiply9(cipher[4][i]);
		x2 = multiply14(cipher[5][i]);
		x3 = multiply11(cipher[6][i]);
		x4 = multiply13(cipher[7][i]);
		tmp[5][i] = x1 ^ x2 ^ x3 ^ x4;
		x1 = multiply13(cipher[4][i]);
		x2 = multiply9(cipher[5][i]);
		x3 = multiply14(cipher[6][i]);
		x4 = multiply11(cipher[7][i]);
		tmp[6][i] = x1 ^ x2 ^ x3 ^ x4;
		x1 = multiply11(cipher[4][i]);
		x2 = multiply13(cipher[5][i]);
		x3 = multiply9(cipher[6][i]);
		x4 = multiply14(cipher[7][i]);
		tmp[7][i] = x1 ^ x2 ^ x3 ^ x4;
	}
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			cipher[i][j] = tmp[i][j];
		}
	}
}

void keyAdd(bitset<8> cipher[8][4], bitset<8>k[15][8][4], int i)
{
	for (int x = 0; x < 8; x++)
	{
		for (int j = 0; j < 4; j++)
		{
			cipher[x][j] = cipher[x][j]^k[i][x][j];	
		}
	}
}

void createKeys(bitset<256> key, bitset<8> set[15][8][4])
{
	bitset<32> set1[4], set2[4];
	int z = 255;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 32; j++)
		{
			set1[i][j] = key[z];
			z--;
		}
	}
	z = 127;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 32; j++)
		{
			set2[i][j] = key[z];
			z--;
		}
	}
	int b = 31, x = 0; bool first = false;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			for (int z = 0; z < 8; z++)
			{
				if(first)
					set[0][i][j][z] = set1[x][b];
				else
					set[0][i][j][z] = set2[x][b];
				if (b == 0)
				{
					b = 31;
					x++;
				}
				if (x == 4)
				{
					x = 0;
					first = false;
				}
				b--;
			}
		}
	}
	for (int i = 1; i < 15; i++)
	{
		set1[0] = set1[0] ^ g(set1[3], i);
		set1[1] = set1[1] ^ set1[0];
		set1[2] = set1[2] ^ set1[1];
		set1[3] = set1[3] ^ set1[2];

		set2[0] = set2[0] ^ g(set2[3], i);
		set2[1] = set2[1] ^ set2[0];
		set2[2] = set2[2] ^ set2[1];
		set2[3] = set2[3] ^ set2[2];
		for (int o= 0; o < 8;o++)
		{
			for (int j = 0; j < 4; j++)
			{
				for (int z = 0; z < 8; z++)
				{
					if (first)
						set[i][o][j][z] = set1[x][b];
					else
						set[i][o][j][z] = set2[x][b];
					if (b == 0)
					{
						b = 31;
						x++;
					}
					if (x == 4)
					{
						x = 0;
						first = false;
					}
					b--;
				}
			}
		}
	}
}

bitset<32> g(bitset<32> word, int i)
{
	bitset<8> tmp[4], tmp2[4];
	bitset<32> out;
	int z = 31;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			tmp2[i][j] = word[z];
			z--;
		}
	}
	tmp[0] = tmp2[1];
	tmp[1] = tmp2[2];
	tmp[2] = tmp2[3];
	tmp[3] = tmp2[0];
	int arr[4];
	arr[0] = tmp[0].to_ullong();
	arr[1] = tmp[1].to_ullong();
	arr[2] = tmp[2].to_ullong();
	arr[3] = tmp[3].to_ullong();

	arr[0] = affineTransformationS(arr[0]);
	arr[1] = affineTransformationS(arr[1]);
	arr[2] = affineTransformationS(arr[2]);
	arr[3] = affineTransformationS(arr[3]);

	tmp[0] = arr[0];
	tmp[1] = arr[1];
	tmp[2] = arr[2];
	tmp[3] = arr[3];
	
	tmp[0] = tmp[0]^rc[i];

	z = 31;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			out[z] = tmp2[i][j];
			z--;
		}
	}
	return out;
}

bitset<8> multiply3(bitset<8> a)
{
	bitset<8> x2 = a << 1, t = 27; //x3
	if (a[7] == 1)
	{
		x2 = x2 ^ t; // xor
	}
	x2 = x2 ^ a;
	return x2;
}

bitset<8> multiply2(bitset<8> a)
{
	bitset<8> x2 = a << 1, t = 27; //x3
	if (a[7] == 1)
	{
		x2 = x2 ^ t; // xor
	}
	return x2;
}

bitset<8> multiply9(bitset<8> a)
{
	bitset<8> x = a, t = a;
	x = multiply2(x);
	x = multiply2(x);
	x = multiply2(x);
	x = x ^ t;
	return x;
}

bitset<8> multiply11(bitset<8> a)
{
	bitset<8> x = a, t = a;
	x = multiply2(x);
	x = multiply2(x);
	x = x ^ t;
	x = multiply2(x);
	x = x ^ t;
	return x;
}

bitset<8> multiply13(bitset<8> a)
{
	bitset<8> x = a, t = a;
	x = multiply2(x);
	x = x ^ t;
	x = multiply2(x);
	x = multiply2(x);
	x = x ^ t;
	return x;
}

bitset<8> multiply14(bitset<8> a)
{
	bitset<8> x = a, t = a;
	x = multiply2(x);
	x = x ^ t;
	x = multiply2(x);
	x = x ^ t;
	x = multiply2(x);
	return x;
}
/*
const int  a = 57;
const int  ai = 85;
const int  b = 5;
const int  p = 173;
*/
int  affineTransformation(int x)
{
	int tmp = ((x * a) + b);
	tmp = tmp % p;
	return tmp;
}

int inverseAffineTransformation(int x)
{
	int tmp = (ai * (x - b));
	tmp = tmp % p;
	return tmp;
}

int  affineTransformationS(int x)
{
	long long tmp = long long(((x * as) + bs));
	tmp = tmp % ps;
	return int(tmp);
}

int inverseAffineTransformationS(int x)
{
	long long tmp = (long long(ais) * (x - bs));
	tmp = tmp % ps;
	return int(tmp);
}

int convertToInt(char message)
{
	switch (message)
	{
	case 'q':
	case 'Q':
		return 1;
		break;
	case 'w':
	case 'W':
		return 2;
		break;
	case 'e':
	case 'E':
		return 3;
		break;
	case 'r':
	case 'R':
		return 4;
		break;
	case 't':
	case 'T':
		return 5;
		break;
	case 'y':
	case 'Y':
		return 6;
		break;
	case 'u':
	case 'U':
		return 7;
		break;
	case 'i':
	case 'I':
		return 8;
		break;
	case 'o':
	case 'O':
		return 9;
		break;
	case 'p':
	case 'P':
		return 10;
		break;
	case 'a':
	case 'A':
		return 11;
		break;
	case 's':
	case 'S':
		return 12;
		break;
	case 'd':
	case 'D':
		return 13;
		break;
	case 'f':
	case 'F':
		return 14;
		break;
	case 'g':
	case 'G':
		return 15;
		break;
	case 'h':
	case 'H':
		return 16;
		break;
	case 'j':
	case 'J':
		return 17;
		break;
	case 'k':
	case 'K':
		return 18;
		break;
	case 'l':
	case 'L':
		return 19;
		break;
	case 'z':
	case 'Z':
		return 20;
		break;
	case 'x':
	case 'X':
		return 21;
		break;
	case 'c':
	case 'C':
		return 22;
		break;
	case 'v':
	case 'V':
		return 23;
		break;
	case 'b':
	case 'B':
		return 24;
		break;
	case 'n':
	case 'N':
		return 25;
		break;
	case 'm':
	case 'M':
		return 26;
		break;
	case '_':
	case ' ':
		return 27;
		break;
	}
}
char convertToString(int msg)
{
	switch (msg)
	{
	case 1:
		return 'Q';
		break;
	case 2:
		return 'W';
		break;
	case 3:
		return 'E';
		break;
	case 4:
		return 'R';
		break;
	case 5:
		return 'T';
		break;
	case 6:
		return 'Y';
		break;
	case 7:
		return 'U';
		break;
	case 8:
		return 'I';
		break;
	case 9:
		return 'O';
		break;
	case 10:
		return 'P';
		break;
	case 11:
		return 'A';
		break;
	case 12:
		return 'S';
		break;
	case 13:
		return 'D';
		break;
	case 14:
		return 'F';
		break;
	case 15:
		return 'G';
		break;
	case 16:
		return 'H';
		break;
	case 17:
		return 'J';
		break;
	case 18:
		return 'K';
		break;
	case 19:
		return 'L';
		break;
	case 20:
		return 'Z';
		break;
	case 21:
		return 'X';
		break;
	case 22:
		return 'C';
		break;
	case 23:
		return 'V';
		break;
	case 24:
		return 'B';
		break;
	case 25:
		return 'N';
		break;
	case 26:
		return 'M';
		break;
	case 27:
		return '_';
		break;
	}
}