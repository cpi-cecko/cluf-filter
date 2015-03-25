#include <iostream>
#include <stdint.h>
#include <limits>

void bytes_to_hex(const unsigned char* data, size_t length, std::string& str)
{
	// Sanity check
	//static_assert<8 == CHAR_BIT>::valid_expression();

	str.clear();

	if (0 == length)
		return;

	// Output is twice the length of input length
	str.resize(length * 2, ' ');

	// Working with 4-bit nybbles, we can use the value as
	// index to character
	static const std::string hex_char = "0123456789abcdef";

	for (size_t i = 0; i < length; ++i)
	{
		// High nybble
		str[i<<1] = hex_char[(data[i] >> 4) & 0x0f];
		// Low nybble
		str[(i<<1) + 1] = hex_char[data[i] & 0x0f];
	}
}

void OutHex(char *str, size_t size)
{
	std::string toStr;
	bytes_to_hex((unsigned char *)str, size, toStr);

	std::cout << toStr.c_str() << '\n';
}

#define DELTA 0x9e3779b9
#define MX (((z>>5^y<<2) + (y>>3^z<<4)) ^ ((sum^y) + (key[(p&3)^e] ^ z)))
 
void XXTEA_FullCycle(uint32_t *msg, size_t msgSize, uint32_t key[4], size_t cycle)
{
	uint32_t sum = cycle * DELTA;
	uint32_t e = sum >> 2;
	for (size_t r = 0; r < msgSize; ++r)
	{
		uint32_t z = msg[(r + msgSize - 1) % msgSize]; // left neighbour
		uint32_t y = msg[(r + 1) % msgSize];		   // right neighbour
		msg[r] += ((z>>5 ^ y<<2) + (y>>3 ^ z<<4)) ^ ((sum ^ y) + (key[(r ^ e) % 4] ^ z));
	}
}

void XXTEA_Encode(uint32_t *msg, size_t msgSize, uint32_t key[4])
{
	size_t cycles = 6 + 52 / msgSize; // min 6 Feistell Network iterations
	for (size_t i = 1; i <= cycles; ++i)
	{
		XXTEA_FullCycle(msg, msgSize, key, i);
	}
}

void btea(uint32_t *v, int n, uint32_t const key[4]) 
{
	uint32_t y, z, sum;
	unsigned p, rounds, e;
	if (n > 1) 
	{   /* Coding Part */
		rounds = 6 + 52/n;
		sum = 0;
		z = v[n-1];
		do 
		{
			sum += DELTA;
			e = (sum >> 2) & 3;
			for (p=0; p<n-1; p++) 
			{
				y = v[p+1]; 
				z = v[p] += MX;
			}
			y = v[0];
			z = v[n-1] += MX;
		} 
		while (--rounds);
	} 
	else if (n < -1) 
	{  /* Decoding Part */
		n = -n;
		rounds = 6 + 52/n;
		sum = rounds*DELTA;
		y = v[0];
		do 
		{
			e = (sum >> 2) & 3;
			for (p=n-1; p>0; p--) 
			{
				z = v[p-1];
				y = v[p] -= MX;
			}
			z = v[n-1];
			y = v[0] -= MX;
			sum -= DELTA;
		}
		while (--rounds);
	}
}

char* replace(const char *msg, const char *msgOne, const char *msgTwo, size_t size)
{
	char *newMessage = new char[size + 1];
	for (size_t i = 0; i < size; ++i)
	{
		newMessage[i] = msg[i] ^ msgOne[i] ^ msgTwo[i];
	}

	newMessage[size] = 0;
	return newMessage;
}

void xor(char *msgOne, const char *msgTwo, size_t msgSize)
{
	for (size_t i = 0; i < msgSize; ++i)
	{
		msgOne[i] ^= msgTwo[i];
	}
}

#define SIZE(arr) sizeof(arr) / sizeof(char)

int main()
{
	uint32_t key[] = { 2541362587, 1453987125, 4236974159, 2541698555 };

	char msg[] = "The quick brown fox jumps over the lazy dog.";
	//char attack[] = "F\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0";
	size_t msgSize = SIZE(msg);
	size_t msgBlockCount = msgSize / sizeof(uint32_t);
	//xor(msg, attack, msgSize);

	XXTEA_Encode((uint32_t*)msg, msgBlockCount, key);
	//XXTEA_Encode((uint32_t*)attack, msgBlockCount, key);
	//xor(msg, attack, msgSize);

	btea((uint32_t*)msg, -msgBlockCount, key);

	OutHex(msg, msgSize);
	//std::cout << msg << '\n\n';
}