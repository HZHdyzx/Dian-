#include <stdio.h>
#define _CRT_SECURE_NO_WARNINGS

//���ýṹ�壬
//A��ʾ��ʼ¥�㣬B��ʾĿ��¥��
//CΪ��ʱ��ʾδ���ϣ�CΪ1ʱ��ʾ�ѽ��ϣ�CΪ2ʱ��ʾ�ѷ���
struct request {
	int A, B;
	int C;
} req[1000];

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
	int floor = 1, state = 1;
	int time = 0;
	int num = 0;
	//��ʾ�����ϵ�����
	int sign[9] = {0};//�������ڼ�¼��ͬ¥�����µ�����
	//���ݵ�����
	printf ("�������������ʼ¥��A��Ŀ��¥��B\n"
	        "AB֮���õ����ո���м����"
	        "�����������ݺ��ԡ�0 0������\n");
	int i = 0;
	while (1) {
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
	printf("��ʼ״̬��\n%d\t%d\t%d\n��ʼ����\n", floor, time, num);
	//��������
	while (1) {
		int j = 0;//jΪ�������������ڼ�¼������±�

//ȷ����һͣ����
		int x, n = 0; //x���ڱ�ʾ��һͣ���㣬nΪ�����������ı仯��
		int m = 0;//���ڱ����ṹ������
		int p = 1;//���ڸ����ж��Ƿ����к����ж�û������
		//�������е����
sta1:
		if (state == 1) {
			x = 11;
			//�����º��ϵ�ԭ���ȿ����µ��ݵ�����
			for (m = 0; m <= i - 1; m++) {
				if (req[m].C == 1 && req[m].B >= floor && req[m].B <= x) {
					if (req[m].B < x) {
						x = req[m].B;
						n = -1;
						j = 0;
						sign[j] = m;
					}
					//���Ƕ���ͬʱ�µ��ݵ����
					else {
						n = n - 1;
						j = j + 1;
						sign[j] = m;
					}
				}
			}
			//�ٿ����ϵ��ݵ�����
			for (m = 0; m <= i - 1; m++) {
				if (req[m].C == 0 && req[m].A >= floor ) {
					//�����µ��ݵ�ͬʱ�����ϵ��ݵ����
					if (req[m].A == x) {
						n = n + 1;
						j = j + 1;
						sign[j] = m;
					}
					if (req[m].A < x && num < 4) {
						x = req[m].A;
						j = 0;
						sign[j] = m;
						n = 1;
					}


				}

			}
			//����ж�
			if (x != 11) {
				p = 1;
			}
			if ( x == 11 && p == 1 ) {
				p = 0;
				state = 0;
				goto sta0;
			}
			if ( x == 11 && p == 0 )
				goto end;

		}
		//�������е����
sta0:
		if (state == 0) {
			x = 0;
			//�ȿ����µ��ݵ�����
			for (m = 0; m <= i - 1; m++) {
				if (req[m].C == 1 && req[m].B <= floor && req[m].B >= x) {
					if (req[m].B > x) {
						x = req[m].B;
						n = -1;
						j = 0;
						sign[j] = m;
					}
					//���Ƕ���ͬʱ�µ��ݵ����
					else {
						n = n - 1;
						j = j + 1;
						sign[j] = m;
					}
				}
			}
			//�ٿ����ϵ��ݵ�����
			for (m = 0; m <= i - 1; m++) {
				if (req[m].C == 0 && req[m].A <= floor ) {
					//�����µ��ݵ�ͬʱ�����ϵ���
					if (req[m].A == x) {
						n = n + 1;
						j = j + 1;
						sign[j] = m;
					}
					if (req[m].A > x && num < 4) {
						x = req[m].A;
						j = 0;
						sign[j] = m;
						n = 1;
					}

				}
			}
			//����ж�
			if (x != 0) {
				p = 1;
			}
			if ( x == 0 && p == 1 ) {
				p = 0;
				state = 1;
				goto sta1;
			}
			if ( x == 0 && p == 0 )
				goto end;

		}
//���ݿ�ʼ�˶�
		move(&floor, x, &time);
		num = num + n;
		int q = 0;
		for (q = 0; q <= j; q++) {
			//ͣ����һЩ�����Ѿ����
			req[sign[q]].C = req[sign[q]].C + 1;
		}
		printf("%d\t%d\t%d\n", floor, time, num);
	}

end:
	printf("���н���");
	return 0;
}
