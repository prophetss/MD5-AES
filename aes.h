#ifndef _AES_H_
#define _AES_H_

/* key length */
#define AES_128	16
#define AES_192	24
#define AES_256	32

typedef unsigned char	uint8_t;

#ifdef __cplusplus
extern "C" {
#endif


/**
 * @param in - source data.
 * @param in_len - source data length.
 * @param out - ouput, because of padding, the length must be equal to ((in_len>>4)+1)<<4.
 * @param key - the length of the key must be equal to AES_128(16) or AES_192(24) or AES_256(32)
 * @param key_len - AES_128 or AES_192 or AES_256
 */
void aes_cipher_data(const uint8_t *in, size_t in_len, uint8_t *out, const uint8_t *key, size_t key_len);

/**
 * @param in - source data.
 * @param in_len - source data length, and it must be divisible by 16
 * @param out - ouput, the size must at least be equal to in_len.
 * @param out_len - it's a reference and less than in_len because of padding
 * @param key - the length of the key must be equal to AES_128(16) or AES_192(24) or AES_256(32)
 * @param key_len - AES_128 or AES_192 or AES_256
 */
void aes_decipher_data(const uint8_t *in, size_t in_len, uint8_t *out, size_t *out_len, const uint8_t *key, size_t key_len);

/**
 * cipher file, not remove source file.
 * @param in_filename - source filename.
 * @param out_filename - destination filename. because of padding , the file size will be divisible by 16.
 * @param key - the length of the key must be equal to AES_128(16) or AES_192(24) or AES_256(32)
 * @param key_len - AES_128 or AES_192 or AES_256
 * @return 0-sucessful,1-failed
 */
int aes_cipher_file(const char *in_filename, const char *out_filename, const uint8_t *key, size_t key_len);

/**
 * decipher file, not remove source file.
 * @param in_filename - source filename and file size must be divisible by 16.
 * @param out_filename - destination filename
 * @param key - the length of the key must be equal to AES_128(16) or AES_192(24) or AES_256(32)
 * @param key_len - AES_128 or AES_192 or AES_256
 * @return 0-sucessful,1-failed
 */
int aes_decipher_file(const char *in_filename, const char *out_filename, const uint8_t *key, size_t key_len);

#ifdef __cplusplus
}
#endif

#endif /* !_AES_H_ */

