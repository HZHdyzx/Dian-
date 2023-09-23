#include <stdio.h>
#include <math.h>
#define _CRT_SECURE_NO_WARNINGS

//���ýṹ�壬
//A��ʾ��ʼ¥�㣬B��ʾĿ��¥��,T��ʾ����ʱ��
//staΪ��ʱ��ʾδ���ϣ�Ϊ1ʱ��ʾ�ѽ��ϣ�Ϊ2ʱ��ʾ�ѷ���

struct request {
	int A, B, T ;
	int sta;
} req[1000];

//���õ������еĲ���
//state��ʾ�˶�����0��ʾ���У�1��ʾ���У�2��ʾ���С�
//num��ʾ�����ϵ�������flo��ʾ�������ڵĲ�����time��ʾʱ�䡣
//goal���ڱ�ǵ�ǰ�ڵ����ϵ��˵�Ŀ�ĵأ�
//ter(terminal)��ʾ���ݵ�ǰ�н�������Ŀ�Ĳ㣬���ڸ�����state���жϡ�
//x���ڸ����ж��Ƿ��ǹؼ�¥��
int time = 0;
int state = 0;
int num = 0;
int flo = 1;
int ter;

int goal[4] = {-1, -1, -1, -1};
int x = 0;

int j, k, m, n; //�������������ڱ���

//����һ���˶��ĺ���
int move(int *h, int state) {
	if (state == 2)
		*h = *h - 1;
	if (state == 1)
		*h = *h + 1;
	return 0;
}

//���ĳ�����Ϸ��Ƿ�������ĺ���
int check3(int h, int *ter) {

	for (m = 0; m < k; m = m + 1) {
		if (req[m].sta == 0 && req[m].A > *ter) {
			*ter = req[m].A;
			break;
		}
	}
}

//���ĳ�����·��Ƿ�������ĺ���
int check4(int h, int *ter) {

	for (m = 0; m < k; m = m + 1) {
		if (req[m].sta == 0 && req[m].A < *ter) {
			*ter = req[m].A;
			break;
		}
	}

}

int main() {
	//���ݵ�����
	printf("������'elevator a'��a��ʾ���ݵ���ʼλ��\n");
	scanf("elevator %d", &flo);
	printf ("�������������ʼ¥��A��Ŀ��¥��B������ʱ��T\n"
	        "A��B��T֮���õ����ո���м����"
	        "�����������ݺ��ԡ�0 0 0������\n");
	int i = 0;

	while (1) {
		scanf("%d %d %d", &req[i].A, &req[i].B, &req[i].T);
		if (req[i].A == 0 && req[i].B == 0)
			break;
		if (req[i].A > 10 || req[i].A < 1 || req[i].B > 10 || req[i].B < 1 || req[i].A == req[i].B)
			printf("�����¥�㲻����Ҫ��������������������\n");
		else {
			req[i].sta = 0;
			i = i + 1;
		}
	}

	req[i].T = -1;


//����ʱ��˳������������������
	for (j = 0; j < i - 1; j = j + 1) {
		for (k = 0; k < i - 1 - j; k = k + 1) {
			if (req[k].T > req[k + 1].T) {
				req[i] = req[k + 1];
				req[k + 1] = req[k];
				req[k] = req[i];
			}
		}
	}
//��¼�ĺ���ʱ��tmax��tmix�����ں������ж�
	int tmax = req[i - 1].T;
	int tmin = req[0].T;
	k = 0;
//������ݵĳ�ʼ״̬
	printf("¥��\tʱ��\t����\n��ʼ״̬\n");
	printf("%d\t%d\t%d\n", flo, time, num);
	printf("��ʼ����\n");
//��ʼÿһ����λʱ��Ĵ���
	for (time = tmin; time <= tmax || state != 0; time = time + 1) {
		//��鵱ǰʱ����û���µ�����
		while (time == req[k].T) {
			k = k + 1;
		}
		x = 0;

		if (state != 0) {
			//�����ƶ�һ��¥��
			move (&flo, state);
			//�ȼ���Ƿ������µ���
			for (m = 0; m < 4; m = m + 1) {
				if (req[goal[m]].B == flo) {
					num = num - 1;
					req[goal[m]].sta = 2;
					goal[m] = -1;
					x = 1;
				}
			}
			//�ټ���Ƿ������ϵ���
			for (m = 0; m < k; m = m + 1) {
				if (req[m].sta == 0 && num < 4 && req[m].A == flo) {
					x = 1;
					for (n = 0; n < 4; n = n + 1) {
						if (goal[n] == -1) {
							goal[n] = m;
							break;
						}
					}
					num = num + 1;
					req[m].sta = 1;
				}
			}
		} else {//������ֹͣʱ�ж��Ƿ�����ǡ���ڵ�ǰ¥�㰴����
			for (m = 0; m < k; m = m + 1) {
				if (flo == req[m].A && req[m].sta == 0) {
					x = 1;
					for (n = 0; n < 4; n = n + 1) {
						if (goal[n] == -1) {
							goal[n] = m;
							break;
						}
					}
					num = num + 1;
					req[m].sta = 1;
					if (req[m].A > req[m].B)
						state = 2;
					else
						state = 1;
					ter = req[m].A;
					break;
				}
			}
		}
		ter = flo;
		//�ȼ������ϵ��˵�ͬ���������
		if (num != 0) {
			for (m = 0; m < 4; m = m + 1) {
				if (state == 1 && goal[m] >= 0 && req[goal[m]].B > ter)
					ter = req[goal[m]].B;
				if (state == 2 && goal[m] >= 0 && req[goal[m]].B < ter )
					ter = req[goal[m]].B;
			}
		}

		if (ter == flo) {
			if (state == 1)
				check3(flo, &ter);
			else if (state == 2)
				check4(flo, &ter);
			if (flo == ter) {
				int y = 11;
				for (m = 0; m < k; m = m + 1) {
					if (req[m].sta == 0 && abs(req[m].A - flo) < y)
						ter = req[m].A;
					else if (req[m].sta == 1 && abs(req[m].B - flo) < y)
						ter = req[m].B;
				}

			}
			if (ter > flo)
				state = 1;
			else if (ter < flo)
				state = 2;
			else if (ter == flo)
				state = 0;
		}
		//���йؼ�¥����Ϣ�����
		if (x == 1)
			printf("%d\t%d\t%d\n", flo, time, num);
	}
	printf("���н���");
	return 0;
}


