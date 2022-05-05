#pragma once
#include <iostream>
#include <bitset>
#include <math.h>
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/multiprecision/miller_rabin.hpp>
#include <boost/random/mersenne_twister.hpp>

using namespace std;
using namespace boost::multiprecision;
using namespace boost::random;

typedef number<cpp_int_backend<4194304, 4194304, signed_magnitude, checked, void> > int_t;

void RSAGen(int_t& n, int_t& e, int_t& d, bool limiter);
int_t RSAEncrypt(int_t& e, int_t& msg, int_t& n);
int_t RSADecrypt(int_t& d, int_t& enc, int_t& n);

int_t gcd(int_t a, int_t b);
int_t gcdExtended(int_t a, int_t b, int_t* x, int_t* y);
int_t modInverse(int_t a, int_t m);
int_t exp(int_t a, int_t m);

void split(int_t num, int_t a[64]);
bitset<1024> merge(int_t a[64]);
int topBit(bitset<1024> x);
bitset<1024> toBinary(int_t x);
int_t squareMultiply(int_t num, int_t exp);

int_t gcd(int_t a, int_t b) {
	if (b == 0)
		return a;
	return gcd(b, a % b);
}
bool mRabin(int_t p, int_t iterator = 25)
{
	if (p < 2)
		return false;
	if (p != 2 && p % 2 == 0)
		return false;
	int_t s = p - 1;
	while (s % 2 == 0)
	{
		s = s / 2;
	}
	for (int_t i = 0; i < iterator; i++)
	{
		int_t a = rand() % (p - 1) + 1,
			tmp = s,
			mod;
		mod = squareMultiply(a, tmp);
		mod = mod % p;

		while (tmp != p - 1 && mod != 1 && mod != p - 1)
		{
			mod = squareMultiply(a, tmp);
			mod = mod % p;
			tmp = tmp * 2;
		}
		if (mod != p - 1 && tmp % 2 == 0)
		{
			return false;
		}
	}
	return true;
}
int_t squareMultiply(int_t num, int_t exp)
{
	int_t total = 1, tmp = exp;
	bitset<4194304> x = 0;
	int z = 0, j;
	while (tmp > 0) {
		if(tmp % 2 == 0)
			x[z] = 0;
		if (tmp % 2 == 1)
			x[z] = 1;
		tmp = tmp / 2;
		z++;
	}
	for (int i = 255; i >= 0; i--)
	{
		if (x[i] == 1)
		{
			j = i;
			total = total * num;
			j--;
			break;
		}
	}
	for (j; j >= 0; j--)
	{
		if (x[j] == 0)
		{
			total = total * total;
		}
		if (x[j] == 1)
		{
			total = (total * total) * num;
		}
	}
	return total;
}

void RSAGen(int_t& n, int_t& e, int_t& d, bool limiter)
{
	
	int_t p = int_t("11"), q = int_t("107"), i1, i2, phi, tmp = 1, x, y;
	if (limiter == false)
	{
		mt11213b base_gen(clock());
		independent_bits_engine<mt11213b, 256, int_t> gen(base_gen);
		int_t b;
		b = gen();
		do{
			b = gen();
		} while (!mRabin(b));
		p = b;
		do
		{
			b = gen();
		} while (!mRabin(b));
		q = b;
	}

	n = p*q;
	i1 = p - 1;
	i2 = q - 1;
	phi = i1 * i2;
	e = 2;
	while (e < phi)
	{
		int_t count = gcd(e, phi);
		if (count == tmp)
		{
			break;
		}
		else
		{
			e = e + 1;
		}
	}
	d = modInverse(e, phi);

}

int_t RSAEncrypt(int_t& e, int_t& msg, int_t& n)
{
	int_t enc = squareMultiply(msg, e);
	enc = enc % n;
	msg = enc;
	return enc;
}

int_t RSADecrypt(int_t& d, int_t& enc, int_t& n)
{
	int_t dec = squareMultiply(enc, d);
	dec = dec % n;
	return dec;
}

int_t gcdExtended(int_t a, int_t b, int_t* x, int_t* y)
{
	if (a == 0)
	{
		*x = 0;
		*y = 1;
		return b;
	}

	int_t _x, _y;
	int_t gcd = gcdExtended(b % a, a, &_x, &_y);

	*x = _y - (b / a) * _x;
	*y = _x;

	return gcd;
}

int_t modInverse(int_t a, int_t m)
{
	int_t x, y;
	int_t g = gcdExtended(a, m, &x, &y);
	if (g != 1)
	{
		cout << "Inverse doesn't exist";
		return -1;
	}
	else
	{
		int_t res = (x % m + m) % m;
		return res;
	}
}

int_t exp(int_t a, int_t b) 
{
	int_t tmp = 1, out = a, x = 1;
	while (tmp != b)
	{
		out = a*out;
		tmp = tmp + x;
	}
	return out;
}

bitset<1024> toBinary(int_t x)
{
	bitset<1024> tmp = int(0);
	for (int i = 0; i < 1024; i++)
	{
		tmp[i] = int(x % 2);
		x = x/2;
	}
	return tmp;
}

void split(int_t num, int_t a[64])
{
	bitset<1024> x = toBinary(num);
	cout << endl;
	/*for (int i = 1023; i >= 0; i--)
	{
		cout << x[i];
		if (i % 4 == 0)
			cout << " ";
	}*/
	cout << endl;
	int_t total = 0;
	int j = 0, i = 0, top = topBit(x);
	while (i <= top)
	{
		int tmp = i;
	
		if (x[tmp] == 1)
			total = total + 1; 
		tmp = i + 1;
		if (x[tmp] == 1)
			total = total + 2; 
		tmp = i + 2;
		if (x[tmp] == 1)
			total = total + 4; 
		tmp = i + 3;
		if (x[tmp] == 1)
			total = total + 8; 
		
		a[j] = total;
		total = 0;
		j++;
		i += 4;
	}
}

int topBit(bitset<1024> x) 
{
	for (int i = 1023; i >= 0; i--)
	{
		if (x[i] == 1)
			return i;
	}
}

bitset<1024> merge(int_t a[64])
{
	bitset<1024> tmp1024, key;
	bitset<4> tmp[64];
	int x, z;
	for (int i = 0; i < 64; i++)
	{
		tmp1024 = toBinary(a[i]);
		tmp[i][0] = tmp1024[0];
		tmp[i][1] = tmp1024[1];
		tmp[i][2] = tmp1024[2];
		tmp[i][3] = tmp1024[3];
	}
	int iter = 0;
	for (int i = 0; i < 64; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			x = tmp[i][j];
			key[iter] = x;
			iter++;
		}
	}
	return key;
}