#include <stdio.h>
#define _CRT_SECURE_NO_WARNINGS

//���ýṹ�壬
//A��ʾ��ʼ¥�㣬B��ʾĿ��¥��
//CΪ��ʱ��ʾδ���ϣ�CΪ1ʱ��ʾ�ѽ��ϣ�CΪ2ʱ��ʾ�ѷ���
struct request {
	int A, B;
	int C;
} req[100];

//����һ�������ƶ��ĺ���
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
	int floor = 1;
	int time = 0;
	int full = 4;
	int num = 0;//��ʾ�����ϵ�����
	int state = 1; //1�������ϣ�0��������

	//���ݵ�����
	printf ("�������������ʼ¥��A��Ŀ��¥��B\n"
	        "AB֮���õ����ո���м����"
	        "�����������ݺ��ԡ�0 0������\n");
	int i = 0;
	int a = 1; //���ڸ����ж�ѭ������
	while (a == 1) {
		scanf("%d %d", &req[i].A, &req[i].B);
		if (req[i].A == 0 && req[i].B == 0)
			break;
		if (req[i].A > 10 || req[i].A < 1 || req[i].B > 10 || req[i].B < 1 || req[i].A == req[i].B)
			printf("�����¥�㲻����Ҫ��������������������\n");
		else {
			req[i].C = 0;
			i = i + 1;
		}
	}
	//�����ʼ״̬
	printf("¥��\tʱ��\t����\n");
	printf("%d\t%d\t%d\n", floor, time, num);
	//��������
	int m = 0, n = 0;
	int x, y;
	int des = 0;
	int j, k;
	int p = 1;
	//x��ʾ����Ŀ�Ĳ㣬y��ʾ����Ŀ�Ĳ�
	//mnΪ�������ڱ����Ĳ���,des��ʾ����ȷ������һ��ͣ����
	//jkΪ��������,p�����ж��Ƿ�ﵽ���н���������
//�ڵ���û������ʱ
	while (a == 1) {
		if (num != full) {
			//��������ʱ��ȷ����һͣ����
state1:
			if (state == 1) {
				x = 11;
				m = 0;
				j = 0;
				for (m = 0; m <= i; m++) {
					if (req[m].C == 0 && req[m].A >= floor && req[m].A < x) {
						x = req[m].A;
						j = m;
					}
				}
				y = 11;
				n = 0;
				k = 0;
				for (n = 0; n <= i; n++) {
					if (req[n].C == 1 && req[n].B >= floor && req[n].B < y) {
						y = req[n].B;
						k = n;
					}
				}
				//�ж��Ƿ�������л����
				if (x == 11 && y == 11) {
					if (p == 1) {
						state = 0;
						p = 0;
						goto state0;
					} else
						goto end;
				} else {
					p = 1;
					if (x <= y)
						des = x;
					else
						des = y;
				}
			}
			//��������ʱ��ȷ����һͣ����
state0:
			if (state == 0) {
				x = 0 ;
				m = 0;
				j = 0;
				for (m = 0; m <= i; m++) {
					if (req[m].C == 0 && req[m].A <= floor && req[m].A > x) {
						x = req[m].A;
						j = m;
					}
				}
				y = 0;
				n = 0;
				k = 0;
				for (n = 0; n <= i; n++) {
					if (req[n].C == 1 && req[n].B <= floor && req[n].B > y) {
						y = req[n].B;
						k = n;
					}
				}
				//�ж��Ƿ�������л����
				if (x == 0 && y == 0) {
					if (p == 1) {
						state = 1;
						p = 0;
						goto state1;
					} else
						goto end;
				} else {
					p = 1;
					if (x >= y)
						des = x;
					else
						des = y;
				}
			}
		}
//�ڵ�������ʱ
		if (num == full) {
			x = 12;
			//x=12���ڷ����������ʱ���ж�
			//����������ʱ
fulstate1:
			if (state == 1) {
				y = 11;
				n = 0;
				k = 0;
				for (n = 0; n <= i; n++) {
					if (req[n].C == 1 && req[n].B >= floor && req[n].B < y) {
						y = req[n].B;
						k = n;
					}
				}
				//�ж��Ƿ��������
				if (y == 11)
					state = 0;
				else
					des = y;
			}
			//����������ʱ
			if (state == 0) {
				y = 0;
				n = 0;
				k = 0;
				for (n = 0; n <= i; n++) {
					if (req[n].C == 1 && req[n].B <= floor && req[n].B > y) {
						y = req[n].B;
						k = n;
					}
				}
				//�ж��Ƿ��������
				if (y == 0) {
					state = 1;
					goto fulstate1;
				} else
					des = y;
			}

		}
		//���ݽ���һ�����в����״̬

		if (x != 12 && x != y) {
			move(&floor, des, &time);
			if ((state == 1 && x < y) || (state == 0 && x > y)) {
				num = num + 1;
				req[j].C = req[j].C + 1;
			}
			if ((state == 1 && x > y) || (state == 0 && x < y)) {
				num = num - 1;
				req[k].C = req[k].C + 1;
			}
		}

		if (x != 12 && x == y) {
			move(&floor, des, &time);
			num = num - 1 + 1;
			req[j].C = req[j].C + 1;
			req[k].C = req[k].C + 1;
		}
		if (x == 12) {
			move(&floor, des, &time);
			num = num - 1;
			req[k].C = req[k].C + 1;
		}
		printf("%d\t%d\t%d\n", floor, time, num);
	}
end:
	printf("���н���");
	return 0;
}
