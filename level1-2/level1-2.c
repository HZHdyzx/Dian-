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
	//打开文件
	FILE *fp = fopen("./input.txt", "r");
	if (fp == NULL) {
		printf("打开文件失败");
		return -1;
	}
	//设置一些量及输入信息
	int A, B, C;
	fscanf(fp, "elevator %d\n%d %d", &C, &A, &B);
	int time = 0;
	int num = 0;
	if (A < 1 || A > 10 || B < 1 || B > 10 || C < 1 || C > 10) {
		printf("楼层超出范围");
		goto end;
	}
	int high = C;
	//输出初始状态
	printf("楼层\t时间\t人数\n");
	printf("初始状态：\n%d\t%d\t%d\n开始运行：\n", high, time, num);
	//模拟电梯去接乘客的过程
	move(&high, A, &time);
	num = num + 1;
	printf("%d\t%d\t%d\n", high, time, num);
	//模拟送乘客去目的层的过程
	move(&high, B, &time);
	num = num - 1;
	printf("%d\t%d\t%d\n", high, time, num);

	printf("运行结束");
end:
	return 0;
}
