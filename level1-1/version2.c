#include <stdio.h>

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
	//设置一些量及输入信息
	int A, B, C;
	int time = 0;
	int num = 0;
	printf("请输入三个楼层号A B C(均在1到10之间），\n"
	       "表示第A层有一人等候电梯到B层及此时电梯所在的层数C。\n");
	scanf("%d %d %d", &A, &B, &C);
	if (A < 1 || A > 10 || B < 1 || B > 10 || C < 1 || C > 10) {
		printf("楼层超出范围");
		goto end;
	}
	int high = C;
	//输出初始状态
	printf("楼层\t时间\t人数\n");
	printf("%d\t%d\t%d\n", high, time, num);
	//模拟电梯去接乘客的过程
	move(&high, A, &time);
	num = num + 1;
	printf("%d\t%d\t%d\n", high, time, num);
	//模拟送乘客去目的层的过程
	move(&high, B, &time);
	num = num - 1;
	printf("%d\t%d\t%d\n", high, time, num);
end:
	return 0;
}
