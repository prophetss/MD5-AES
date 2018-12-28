#include <stdio.h>
#include "md5.h"
#include "aes.h"

void print_bytes(const unsigned char *buf, size_t len)
{
	int i;
	for (i = 0; i < len; i++)
		printf("%x ", buf[i]);
	printf("\n");
}

int main(int argc, char *argv[])
{
	const char *filename = "test.c";

	uint8_t in[31] = {
		0x00, 0x11, 0x22, 0x33,
		0x44, 0x55, 0x66, 0x77,
		0x88, 0x99, 0xaa, 0xbb,
		0xcc, 0xdd, 0xee, 0xff,
		0x11, 0x22, 0x33, 0xff,
		0x44, 0x55, 0x66, 0x77,
		0x88, 0x99, 0xaa, 0xbb,
		0xcc, 0xdd, 0xee };

	/* aes test */
	uint8_t key[] = {		// 256 bit key
		0x00, 0x01, 0x02, 0x03,
		0x04, 0x05, 0x06, 0x07,
		0x08, 0x09, 0x0a, 0x0b,
		0x0c, 0x0d, 0x0e, 0x0f,
		0x10, 0x11, 0x12, 0x13,
		0x14, 0x15, 0x16, 0x17,
		0x18, 0x19, 0x1a, 0x1b,
		0x1c, 0x1d, 0x1e, 0x1f };
	
	uint8_t out[32]; // ((31>>4)+1)<<4
	printf("data in:\n");
	print_bytes(in, 31);

	aes_cipher_data(in, 31, out, key, AES_256);
	printf("cipher in:\n");
	print_bytes(out, 32);

	size_t out_len;
	aes_decipher_data(out, 32, out, &out_len, key, AES_256);
	printf("decipher in:\n");
	print_bytes(out, out_len);

	const char* cipher_file = "ciphertext.txt";
	const char* decipher_file = "original.txt";
	aes_cipher_file(filename, cipher_file, key, AES_256);
	aes_decipher_file(cipher_file, decipher_file, key, AES_256);
	printf("\n");

	/* md5 test */
	unsigned char buf[MD5_HASHBYTES];	//128/8
	MD5File(filename, buf);
	printf("md5 %s:\n", filename);
	print_bytes(buf, MD5_HASHBYTES);

	MD5File(decipher_file, buf);
	printf("md5 %s:\n", decipher_file);
	print_bytes(buf, MD5_HASHBYTES);

	MD5Data(in, MD5_HASHBYTES, buf);
	printf("md5 in:\n");
	print_bytes(buf, MD5_HASHBYTES);
	printf("\n");
}
