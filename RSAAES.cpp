#include <iostream>
#include <bitset>
#include <stdio.h>
#include <boost/multiprecision/cpp_int.hpp>
#include "RSA.h"
#include "AES.h"

using namespace std;
using namespace boost::multiprecision;


int main()
{
	char msg[32];
	bool limiter = true;
	string s;
	cout << "for RSA enter '1' to remove the limiter, if the limiter is off it will use 256 bit nums for p, and q but it will be significantly slower:\n>";
	cin >> s;
	if (s == "1")
		limiter = false;
	cout << "enter txt:\n>";
	cin >> s;
	int i = 0;
	

	bitset<8> cipher[8][4];


	int_t a = 7, b = 7, p = 23,key = int_t("11122855932768674222832270684772054760204077720273405144653729197153407177753"),
		n, 
		e, 
		d, 
		m[64];
	bitset<1024> bitKey;
	bitset<256> redKey;

	RSAGen(n, e, d, limiter);

	split(key, m);
	i = 63;
	while (i >= 0)
	{
		i--;
	}
	i = 63;

	//encrypting blocks
	while (i >= 0)
	{
		m[i] = RSAEncrypt(e, m[i], n);
		i--;
	}
	i = 63;

	//decrypting blocks
	while (i >= 0)
	{
		m[i] = RSADecrypt(d, m[i], n);
		i--;
	}

	//merging decrypted blocks into bitKey of macipher size 1024
	bitKey = merge(m);
	//reducing 1024 to 256
	for (int j = 0; j < 256; j++)
	{
		redKey[j] = bitKey[j];
	}

	cout << "\n\nblock 2\n\n";
	while (i < 32)
	{
		msg[i] = s[i];
		if (i >= s.length())
			msg[i] = '_';
		cout << msg[i];
		i++;
	}
	AESEncrypt(cipher, msg, redKey);
	AESDecrypt(cipher, redKey);
	if (s.length() > 32)
	{
		cout << "\n\nblock 2\n\n";
		i = 0;
		while (i < 32)
		{
			msg[i] = s[long(i+32)];
			if (long(i+32) >= s.length())
				msg[i] = '_';
			cout << msg[i];
			i++;
		}
		AESEncrypt(cipher, msg, redKey);
		AESDecrypt(cipher, redKey);
	}
	cin >> s;
}
