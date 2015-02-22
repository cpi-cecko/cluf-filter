#include <iostream>
#include <stdint.h>
#include <limits>

void bytes_to_hex(const unsigned char* data, size_t length,
  std::string& str)
{
  // Sanity check
  //static_assert<8 == CHAR_BIT>::valid_expression();

  // Clear output
  str.clear();

  // No data? Then we're done
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
 
void btea(uint32_t *v, int n, uint32_t const key[4]) {
	uint32_t y, z, sum;
	unsigned p, rounds, e;
	if (n > 1) {          /* Coding Part */
		  rounds = 6 + 52/n;
		  sum = 0;
		  z = v[n-1];
		  do {
				sum += DELTA;
				e = (sum >> 2) & 3;
				for (p=0; p<n-1; p++) {
					  y = v[p+1]; 
					  z = v[p] += MX;
				}
				y = v[0];
				z = v[n-1] += MX;
		  } while (--rounds);
	} else if (n < -1) {  /* Decoding Part */
		  n = -n;
		  rounds = 6 + 52/n;
		  sum = rounds*DELTA;
		  y = v[0];
		  do {
				e = (sum >> 2) & 3;
				for (p=n-1; p>0; p--) {
					  z = v[p-1];
					  y = v[p] -= MX;
				}
				z = v[n-1];
				y = v[0] -= MX;
				sum -= DELTA;
		  } while (--rounds);
	}
}

#define SIZE(arr) sizeof(arr) / sizeof(char)

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

int main()
{
	char msg[] = "from:Zoe The quick brown fox jumps over the lazy dog. Attack at dawn!!!!\0";
	int rawN = SIZE(msg);
	int n = rawN / 4;
	std::cout << msg << " " << n << '\n';

	uint32_t key[4];
	key[0] = 2586310455;
	key[1] = 443325601;
	key[2] = 1124863153;
	key[3] = 2896345105;

	btea((uint32_t*)msg, n, key);

	char attack[] = "\0\0\0\0\0Amy\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0";
	btea((uint32_t*)attack, n, key);
	char known[] =  "\0\0\0\0\0Zoe\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0";
	btea((uint32_t*)known, n, key);

	std::cout << "attack: "; OutHex(attack, rawN);
	std::cout << "known:  "; OutHex(known, rawN);

	//char xored[SIZE(msg) + 1];
	//for (size_t i = 0; i < SIZE(msg); ++i)
	//{
	//	xored[i] = attack[i] ^ known[i];
	//}
	//xored[SIZE(msg)] = 0;


	//std::cout << '\n';
	//std::cout << "Message: " << msg << '\n';
	//std::cout << '\n';
	//std::cout << "Attack: " << xored << '\n';

	char *newMsg = replace(msg, attack, known, rawN);

	btea((uint32_t*)msg, -n, key);

	std::cout << "decr xor: "; OutHex(newMsg, rawN);

	delete [] newMsg;
	return 0;
}