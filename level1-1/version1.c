#include <stdio.h>

int main() {
	//设置一些量及输入信息
	int A, B, C;
	int time = 0;
	int num = 0;
	printf("请输入三个楼层号A B C(均在0到10之间），\n"
	       "表示第A层有一人等候电梯到B层及此时电梯所在的层数C。\n");
	scanf("%d %d %d", &A, &B, &C);
	//输出初始状态
	printf("%d %d %d\n", C, time, num);
	//计算并输出接到人时的状态
	if (C > A)
		time = time + C - A;
	else
		time = time + A - C;
	num = num + 1;
	printf("%d %d %d\n", A, time, num);
	//计算并输出到达目的楼层时的状态
	if (A > B)
		time = time + A - B;
	else
		time = time + B - A;
	num = num - 1;
	printf("%d %d %d\n", B, time, num);
	return 0;
}
