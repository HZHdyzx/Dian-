#include <stdio.h>

int main() {
	//����һЩ����������Ϣ
	int A, B, C;
	int time = 0;
	int num = 0;
	printf("����������¥���A B C(����0��10֮�䣩��\n"
	       "��ʾ��A����һ�˵Ⱥ���ݵ�B�㼰��ʱ�������ڵĲ���C��\n");
	scanf("%d %d %d", &A, &B, &C);
	//�����ʼ״̬
	printf("%d %d %d\n", C, time, num);
	//���㲢����ӵ���ʱ��״̬
	if (C > A)
		time = time + C - A;
	else
		time = time + A - C;
	num = num + 1;
	printf("%d %d %d\n", A, time, num);
	//���㲢�������Ŀ��¥��ʱ��״̬
	if (A > B)
		time = time + A - B;
	else
		time = time + B - A;
	num = num - 1;
	printf("%d %d %d\n", B, time, num);
	return 0;
}
