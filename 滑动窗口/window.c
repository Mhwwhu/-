#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WINDOW_SIZE 4
#define TOTAL_PACKETS 10

// ģ�ⷢ�͵����ݰ�
typedef struct Packet {
	int id;
	char data[20];
} Packet;

// ģ����շ�ȷ��
typedef struct Acknowledgement {
	int ackId;
} Acknowledgement;

void sendData(Packet packets[], int totalPackets) {
	int windowStart = 0;
	int windowEnd = WINDOW_SIZE - 1;
	Acknowledgement ack;

	while (windowStart < totalPackets) {
		// ���ʹ����ڵ��������ݰ�
		for (int i = windowStart; i <= windowEnd && i < totalPackets; i++) {
			printf("Sending packet with ID: %d\n", packets[i].id);
			// ������շ����ǳɹ����ղ�����ȷ��
			ack.ackId = packets[i].id;
		}

		// ģ�����ȷ��
		if (ack.ackId >= windowStart) {
			printf("Acknowledgement received for packet ID: %d\n", ack.ackId);
			// �ƶ�����
			windowStart = ack.ackId + 1;
			windowEnd = windowStart + WINDOW_SIZE - 1;
		}
	}
}

int main() {
	Packet packets[TOTAL_PACKETS];
	// ��ʼ�����ݰ�
	for (int i = 0; i < TOTAL_PACKETS; i++) {
		packets[i].id = i;
		snprintf(packets[i].data, sizeof(packets[i].data), "Packet %d data", i);
	}

	// ��������
	sendData(packets, TOTAL_PACKETS);
	return 0;
}
