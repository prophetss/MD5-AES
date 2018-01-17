
#include <stdio.h>
#include "md5.h"
#include "aes.h"

int main(int argc, char *argv[])
{
	/* md5 test */
	char buf[128];
	MD5File("C:\\test.txt", buf);
	printf("%s\n", buf);
	char data[] = "hello world!";
	MD5Data(data, sizeof data, buf);
	printf("%s\n", buf);

	/* aes test */
	/* 256 bit key */
	uint8_t key[] = {
		0x00, 0x01, 0x02, 0x03,
		0x04, 0x05, 0x06, 0x07,
		0x08, 0x09, 0x0a, 0x0b,
		0x0c, 0x0d, 0x0e, 0x0f,
		0x10, 0x11, 0x12, 0x13,
		0x14, 0x15, 0x16, 0x17,
		0x18, 0x19, 0x1a, 0x1b,
		0x1c, 0x1d, 0x1e, 0x1f };
	char* f = "C:\\test.txt";
	char* o = "C:\\cipher.txt";
	char* o1 = "C:\\decipher.txt";
	aes_file(f, o, key, sizeof key, AES_CIPHER);
	aes_file(o, o1, key, sizeof key, AES_DECIPHER);

	uint8_t in[] = "hello world";

	printf("in:  ");
	for (int i = 0; i < 4; i++)
		printf("%02x %02x %02x %02x ", in[4 * i + 0], in[4 * i + 1], in[4 * i + 2], in[4 * i + 3]);
	printf("\n");

	uint8_t out[AES_BUFSIZ];
	/* cipher */
	aes_data(in, AES_BUFSIZ, out, key, AES_256, AES_CIPHER);
	printf("out: ");
	for (int i = 0; i < 4; i++) 
		printf("%02x %02x %02x %02x ", out[4 * i + 0], out[4 * i + 1], out[4 * i + 2], out[4 * i + 3]);
	printf("\n");

	/* decipher */
	aes_data(out, AES_BUFSIZ, in, key, AES_256, AES_DECIPHER);
	printf("msg: ");
	for (int i = 0; i < 4; i++) 
		printf("%02x %02x %02x %02x ", in[4 * i + 0], in[4 * i + 1], in[4 * i + 2], in[4 * i + 3]);
	printf("\n");
	system("pause");
}