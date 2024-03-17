#include <stdio.h>

#define POLYNOMIAL 0x07 // CRC-8 �����ɶ���ʽ
#define WIDTH  (8 * sizeof(unsigned char))
#define TOPBIT (1 << (WIDTH - 1))

unsigned char CRC8(const unsigned char* data, unsigned int size) {
	unsigned char remainder = 0; // ��ʼ������

	// ��ÿ���ֽڽ��д���
	for (unsigned int byte = 0; byte < size; ++byte) {
		remainder ^= data[byte]; // ����ǰ�����ֽ����������

		// �Ե�ǰ�ֽڵ�ÿһλ���д���
		for (unsigned char bit = 8; bit > 0; --bit) {
			// �������λΪ1�������ɶ���ʽ�������
			if (remainder & TOPBIT) {
				remainder = (remainder << 1) ^ POLYNOMIAL;
			}
			else {
				remainder = (remainder << 1);
			}
		}
	}

	// �������յ���������CRCУ����
	return remainder;
}

int main() {
	const unsigned char message[] = "Hello, World!";
	unsigned int size = sizeof(message) - 1;
	unsigned char crc = CRC8(message, size);

	printf("CRC-8 for \"%s\" is 0x%X\n", message, crc);
	return 0;
}
