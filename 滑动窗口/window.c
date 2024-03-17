#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WINDOW_SIZE 4
#define TOTAL_PACKETS 10

// 模拟发送的数据包
typedef struct Packet {
	int id;
	char data[20];
} Packet;

// 模拟接收方确认
typedef struct Acknowledgement {
	int ackId;
} Acknowledgement;

void sendData(Packet packets[], int totalPackets) {
	int windowStart = 0;
	int windowEnd = WINDOW_SIZE - 1;
	Acknowledgement ack;

	while (windowStart < totalPackets) {
		// 发送窗口内的所有数据包
		for (int i = windowStart; i <= windowEnd && i < totalPackets; i++) {
			printf("Sending packet with ID: %d\n", packets[i].id);
			// 假设接收方总是成功接收并发送确认
			ack.ackId = packets[i].id;
		}

		// 模拟接收确认
		if (ack.ackId >= windowStart) {
			printf("Acknowledgement received for packet ID: %d\n", ack.ackId);
			// 移动窗口
			windowStart = ack.ackId + 1;
			windowEnd = windowStart + WINDOW_SIZE - 1;
		}
	}
}

int main() {
	Packet packets[TOTAL_PACKETS];
	// 初始化数据包
	for (int i = 0; i < TOTAL_PACKETS; i++) {
		packets[i].id = i;
		snprintf(packets[i].data, sizeof(packets[i].data), "Packet %d data", i);
	}

	// 发送数据
	sendData(packets, TOTAL_PACKETS);
	return 0;
}
