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
	//����һЩ����������Ϣ
	int A, B, C;
	int time = 0;
	int num = 0;
	printf("����������¥���A B C(����1��10֮�䣩��\n"
	       "��ʾ��A����һ�˵Ⱥ���ݵ�B�㼰��ʱ�������ڵĲ���C��\n");
	scanf("%d %d %d", &A, &B, &C);
	if (A < 1 || A > 10 || B < 1 || B > 10 || C < 1 || C > 10) {
		printf("¥�㳬����Χ");
		goto end;
	}
	int high = C;
	//�����ʼ״̬
	printf("¥��\tʱ��\t����\n");
	printf("%d\t%d\t%d\n", high, time, num);
	//ģ�����ȥ�ӳ˿͵Ĺ���
	move(&high, A, &time);
	num = num + 1;
	printf("%d\t%d\t%d\n", high, time, num);
	//ģ���ͳ˿�ȥĿ�Ĳ�Ĺ���
	move(&high, B, &time);
	num = num - 1;
	printf("%d\t%d\t%d\n", high, time, num);
end:
	return 0;
}
