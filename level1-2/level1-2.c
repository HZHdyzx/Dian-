#include <stdio.h>
#define _CRT_SECURE_NO_WARNINGS

int move( int *h, int end, int *t) {

	while (*h > end) {
		*h = *h - 1;
		*t = *t + 1;
	}
	while (*h < end) {
		*h = *h + 1;
		*t = *t + 1;
	}
	return 0;
}

int main() {
	//���ļ�
	FILE *fp = fopen("./input.txt", "r");
	if (fp == NULL) {
		printf("���ļ�ʧ��");
		return -1;
	}
	//����һЩ����������Ϣ
	int A, B, C;
	fscanf(fp, "elevator %d\n%d %d", &C, &A, &B);
	int time = 0;
	int num = 0;
	if (A < 1 || A > 10 || B < 1 || B > 10 || C < 1 || C > 10) {
		printf("¥�㳬����Χ");
		goto end;
	}
	int high = C;
	//�����ʼ״̬
	printf("¥��\tʱ��\t����\n");
	printf("��ʼ״̬��\n%d\t%d\t%d\n��ʼ���У�\n", high, time, num);
	//ģ�����ȥ�ӳ˿͵Ĺ���
	move(&high, A, &time);
	num = num + 1;
	printf("%d\t%d\t%d\n", high, time, num);
	//ģ���ͳ˿�ȥĿ�Ĳ�Ĺ���
	move(&high, B, &time);
	num = num - 1;
	printf("%d\t%d\t%d\n", high, time, num);

	printf("���н���");
end:
	return 0;
}
