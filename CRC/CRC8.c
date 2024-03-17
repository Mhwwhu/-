#include <stdio.h>

#define POLYNOMIAL 0x07 // CRC-8 的生成多项式
#define WIDTH  (8 * sizeof(unsigned char))
#define TOPBIT (1 << (WIDTH - 1))

unsigned char CRC8(const unsigned char* data, unsigned int size) {
	unsigned char remainder = 0; // 初始化余数

	// 对每个字节进行处理
	for (unsigned int byte = 0; byte < size; ++byte) {
		remainder ^= data[byte]; // 将当前数据字节与余数异或

		// 对当前字节的每一位进行处理
		for (unsigned char bit = 8; bit > 0; --bit) {
			// 余数最高位为1，按生成多项式进行异或
			if (remainder & TOPBIT) {
				remainder = (remainder << 1) ^ POLYNOMIAL;
			}
			else {
				remainder = (remainder << 1);
			}
		}
	}

	// 返回最终的余数，即CRC校验码
	return remainder;
}

int main() {
	const unsigned char message[] = "Hello, World!";
	unsigned int size = sizeof(message) - 1;
	unsigned char crc = CRC8(message, size);

	printf("CRC-8 for \"%s\" is 0x%X\n", message, crc);
	return 0;
}
