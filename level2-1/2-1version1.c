#include <stdio.h>

//���ýṹ�壬
//A��ʾ��ʼ¥�㣬B��ʾĿ��¥��,D��ʾ����ʱ��
//CΪ��ʱ��ʾδ���ϣ�CΪ1ʱ��ʾ�ѽ��ϣ�CΪ2ʱ��ʾ�ѷ���
struct request {
	int A, B, T;
	int C;
} req[1000];

//����һ�������ƶ��ĺ���
int move( int *h, int *end, int *t, int i) {
	int m = 0;
	while (*h != *end) {
		if (*h > *end)
			*h = *h - 1;
		else*h = *h + 1;
		*t = *t + 1;
		for (m = 0; m < i; m++) {
			if (req[m].T == *t) {
				*end = -1; //*end=-1��ʾû�е���Ŀ�ĵأ����ں����ж�
				goto out;
			}
		}
	}
out:
	return 0;

}

int main() {
	int floor = 1, state = 1;
	int time = 0;
	int num = 0;
	//��ʾ�����ϵ�����
	int sign[5] = {0};
	int m = 0;//���ڱ����ṹ������
	//���ݵ�����
	printf("������'elevator a'��a��ʾ���ݵ���ʼλ��\n");
	scanf("elevator %d", &floor);
	printf ("�������������ʼ¥��A��Ŀ��¥��B������ʱ��T\n"
	        "A��B��D֮���õ����ո���м����"
	        "�����������ݺ��ԡ�0 0 0������\n");
	int i = 0;
	while (1) {
		scanf("%d %d %d", &req[i].A, &req[i].B, &req[i].T);
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
	printf("��ʼ״̬��\n%d\t%d\t%d\n��ʼ���У�\n", floor, time, num);
	//�ҳ����ĺ���ʱ��tmax�����ں������ж�
	int b = 0;
	int tmax = 0;
	for (b = 0; b < i; b++) {
		if (req[b].T > tmax)
			tmax = req[b].T;
	}
//while�н�����һͣ�����ѡ�񲢼���ͣ������������ı仯
re:
	while (1) {

		int j = 0, n = 0;//jΪ����������nΪ�����������ı仯��
		int x ;//x���ڱ�ʾ��һͣ����

		int p = 1;//���ڸ����ж��Ƿ����н���
		//�������е����
sta1:
		if (state == 1) {
			x = 11;
			//�ȿ����µ��ݵ�����
			for (m = 0; m < i; m++) {
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
				if (req[m].C == 0 && req[m].A >= floor && req[m].T <= time  ) {
					//�����µ��ݵ�ͬʱ�����ϵ��ݵ����
					if (req[m].A == x) {
						n = n + 1;
						j = j + 1;
						sign[j] = m;
					}
					//�����ϵ��ݵ�����
					if (req[m].A < x && num < 4) {
						x = req[m].A;
						j = 0;
						sign[j] = m;
						n = 1;
					}


				}

			}

			//���н���ж�
			if (x != 11) {
				p = 1;
			}
			if ( x == 11 && p == 1 ) {
				p = 0;
				state = 0;
				goto sta0;
			}
			if (x == 11 && p == 0  ) {
				goto decide;//����ǰʱ�̵��ݿ���
			}
		}
		//�������е����
sta0:
		if (state == 0) {
			x = 0;
			//�ȿ����µ��ݵ�����
			for (m = 0; m < i; m++) {
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
				if (req[m].C == 0 && req[m].A <= floor  && req[m].T <= time ) {
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
			//���н���ж�
			if (x != 0) {
				p = 1;
			}
			if ( x == 0 && p == 1 ) {
				p = 0;
				state = 1;
				goto sta1;
			}
			if ( x == 0 && p == 0 ) {
				goto decide;//����ǰʱ�̵��ݿ���
			}
		}
//���ݿ�ʼ�˶�
		move(&floor, &x, &time, i);
		//�ж��˶���û�б����
		if (x != -1) {
			//��û����������
			num = num + n;
			int q = 0;
			for (q = 0; q <= j; q++) {
				//ͣ�������Ѿ���ɵ�����
				req[sign[q]].C = req[sign[q]].C + 1;
			}
			printf("%d\t%d\t%d\n", floor, time, num);
		}

	}
//�жϿ���֮���Ƿ���������
decide:
	if (time < tmax)
		//���֮���ʱ����������
	{
		printf("%d\t%d-", floor, time);
		while (1) {
			time = time + 1;
			for (m = 0; m < i; m++) {
				if (req[m].T == time) {
					printf ("%d\t���о�ֹ\n", time);
					goto re;
				}
			}
		}
	} else
		printf("���н���");
	return 0;
}
