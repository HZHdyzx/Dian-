#include <stdio.h>

//���ýṹ�壬
//A��ʾ��ʼ¥�㣬B��ʾĿ��¥��,T��ʾ����ʱ��
//sta(state)Ϊ��ʱ��ʾδ���ϣ�Ϊ1ʱ��ʾ�ѽ��ϣ�Ϊ2ʱ��ʾ�ѷ���
//dir(direction)Ϊ0ʱ��ʾ���£�Ϊ1ʱ��ʾ����
struct request {
	int A, B, T, dir;
	int sta;
} req[1000];

//����һ�������ƶ��ĺ���
int move( int *h, int *end, int *t, int i) {
	int m = 0;
	while (*h != *end) {
		if (*h > *end)
			*h = *h - 1;
		else*h = *h + 1;
		*t = *t + 1;
		//��������й�������û���µ�����
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
	//����һ���������ڼ�¼�������ݵ���ʼ¥��
	int ele[2] = {};
	//���ݵ�����
	for (int j = 0; j < 2; j = j + 1) {
		printf("������%d�ŵ��ݵ���ʼ¥��\n(������һ��1��10֮�������)\n", j);
		scanf("%d", &ele[j]);

	}
	printf ("�������������ʼ¥��A��Ŀ��¥��B������ʱ��D\n"
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
			if (req[i].A > req[i].B)
				req[i].dir = 0;
			else
				req[i].dir = 1;
			req[i].sta = 0;
			i = i + 1;
		}
	}
	int elevator = 0; //0��ʾ0�ŵ��ݣ�1��ʾ1�ŵ���
	int sign[9] = {0};
	int m = 0;//���ڱ����ṹ������
//��0�ŵ��ݷ����±�Ϊż��������req
//��1�ŵ��ݷ����±�Ϊ����������req
//�ȴ���0�ŵ��ݵ����й��̣��ٴ���1�ŵ��ݵ����й���
	for (elevator = 0; elevator < 2; elevator++) {
		int time = 0;
		int floor = ele[elevator];
		int state = 1;//1��ʾ���У�0��ʾ����
		int num = 0;//��ʾ�����ϵ�����
//�����ʼ״̬
		printf("\n%d�ŵ���\n¥��\tʱ��\t����\n", elevator);
		printf("��ʼ״̬��\n%d\t%d\t%d\n��ʼ���У�\n", floor, time, num);

		//�ҳ����ĺ���ʱ��tmax�����ں������ж�
		int tmax = 0;
		for (m = elevator; m < i; m = m + 2) {
			if (req[m].T > tmax)
				tmax = req[m].T;
		}
		//while�н�����һͣ�����ѡ�񲢼���ͣ������������ı仯
re:
		while (1) {

			int j = 0, n = 0;//j���ڼ�¼�����±꣬nΪ�����������ı仯��
			int x = 0; //x���ڱ�ʾ��һͣ����

			int p = 1;//���ڸ����ж��Ƿ����н���
rejudge:
			//�������е����
			if (state == 1) {
				x = 11;
				for (m = elevator; m < i; m = m + 2) { //&& req[m].B >= floor
					if (req[m].sta == 1 && req[m].B <= x) {
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
				for (m = elevator; m < i; m = m + 2) {
					if (req[m].sta == 0 && req[m].T <= time && req[m].A >= floor && req[m].dir == 1) {
						if (req[m].A == x) {
							n = n + 1;
							j = j + 1;
							sign[j] = m;
						}
						if (req[m].A < x && num < 4) { //����û����ʱ����������
							x = req[m].A;
							j = 0;
							sign[j] = m;
							n = 1;
						}
						//�����µ��ݵ�ͬʱ�����ϵ��ݵ����

					}

				}

				if (x != 11) {
					p = 1;
				} else {
					//�ڵ�ǰ�����������ʱ�ж��Ϸ��Ƿ�����Ҫ��¥
					x = floor;
					for (m = elevator; m < i; m = m + 2) {
						if (req[m].sta == 0 && req[m].T <= time && req[m].A > x) {
							x = req[m].A;
							j = 0;
							sign[j] = m;
							n = 1;
							p = 1;
						}
					}//���û����ı����з����ֹ
					if (x == floor ) {
						if (p == 1) {
							p = 0;
							state = 0;
						} else
							goto decide;//����ѭ��
					}

				}
			}
			//�������е����
			if (state == 0) {
				x = 0;
				for (m = elevator; m < i; m = m + 2) { //&& req[m].B <= floor
					if (req[m].sta == 1 && req[m].B >= x) {
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
				}//&& req[m].A >= x
				for (m == elevator; m < i; m = m + 2) {

					if (req[m].sta == 0 && req[m].T <= time && req[m].A <= floor && req[m].dir == 0) {
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
				if (x != 0) {
					p = 1;
				} else {
					//�ڵ�ǰ�����������ʱ�ж��·��Ƿ�����Ҫ��¥
					x = floor;
					for (m = elevator; m < i; m = m + 2) {
						if (req[m].sta == 0 && req[m].T <= time && req[m].A < x) {
							x = req[m].A;
							j = 0;
							sign[j] = m;
							n = 1;
							p = 1;
						}
					}
					//���û����ı����з����ֹ
					if (x == floor ) {
						if (p == 1) {
							p = 0;
							state = 1;
							goto rejudge;
						}//�ı����з���������ж�
						else
							goto decide;//����ѭ��
					}

				}
			}
//���ݿ�ʼ�˶�
			move(&floor, &x, &time, i);
			//�ж��˶���û�б����
			if (x != -1) {
				//��û����������
				num = num + n;
				for (m = 0; m <= j; m++) {
					//ͣ����һЩ�����Ѿ����
					req[sign[m]].sta = req[sign[m]].sta + 1;
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
				for (m = elevator; m < i; m = m + 2) {
					if (req[m].T == time) {
						printf ("%d\t���о�ֹ\n", time);
						goto re;
					}
				}
			}
		} else//���֮��û������
			printf("����%d���н���\n", elevator);
	}
	return 0;
}















