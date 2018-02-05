
#include <stdio.h>
#include "md5.h"
#include "aes.h"

int main(int argc, char *argv[])
{
	/* md5 test */
	char buf[128];
	MD5File("test.c", buf);
	printf("%s\n", buf);
	char data[] = "hello world!";
	MD5Data(data, sizeof data, buf);
	printf("%s\n", buf);

	/* aes test */
	int i;
	/* 256 bit key */
	uint8_t key[] = {
		0x00, 0x01, 0x02, 0x03,
		0x04, 0x05, 0x06, 0x07,
		0x08, 0x09, 0x0a, 0x0b,
		0x0c, 0x0d, 0x0e, 0x0f,
		0x10, 0x11, 0x12, 0x13,
		0x14, 0x15, 0x16, 0x17,
		0x18, 0x19, 0x1a, 0x1b,
		0x1c, 0x1d, 0x1e, 0x1f};

	uint8_t in[32] = {
		0x00, 0x11, 0x22, 0x33,
		0x44, 0x55, 0x66, 0x77,
		0x88, 0x99, 0xaa, 0xbb,
		0xcc, 0xdd, 0xee, 0xff,
		0x11, 0x22, 0x33, 0xff,
		0x44, 0x55, 0x66, 0x77,
		0x88, 0x99, 0xaa, 0xbb,
		0xcc, 0xdd, 0xee};
	
	uint8_t out[32]; // 128

	for (i = 0; i < 31; i++) {
		printf("%x ", in[i]);
	}
	
	printf("\n");

	aes_cipher_data(in,31, out, key, AES_256);

	printf("out:\n");
	
	for (i = 0; i < 8; i++) {
		printf("%x %x %x %x ", out[4*i+0], out[4*i+1], out[4*i+2], out[4*i+3]);
	}

	printf("\n");

	int in_len;
	aes_decipher_data(out, 32, in, &in_len, key, AES_256);

	printf("msg:\n");
	for (i = 0; i < in_len; i++) {
		printf("%x ", in[i]);
	}

	printf("\n");

	char* in_file = "test.c";
	char* cipher_file = "cipher.txt";
	char* decipher_file = "decipher.txt";
	aes_cipher_file(in_file, cipher_file, key, AES_256);
	aes_decipher_file(cipher_file, decipher_file, key, AES_256);
}
