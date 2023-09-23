#include <stdio.h>
#include <math.h>
#define _CRT_SECURE_NO_WARNINGS

//���ýṹ�壬
//start��ʾ��ʼ¥�㣬end��ʾĿ��¥��,time��ʾ����ʱ��
//staΪ��ʱ��ʾδ���ϣ�Ϊ1ʱ��ʾ�ѽ��ϣ�Ϊ2ʱ��ʾ�ѷ���
//dir(direction)Ϊ1ʱ��ʾ���ϣ�Ϊ2ʱ��ʾ����
struct request {
	int A, B, T ;
	int dir, sta;
} req[1000];

//���õ������еĲ���
//state��ʾ�˶�����0��ʾ���У�1��ʾ���У�2��ʾ���С�
//num��ʾ�����ϵ�������floor��ʾ�������ڵĲ�����time��ʾʱ�䡣
//goal���ڱ�ǵ�ǰ�ڵ����ϵ��˵�Ŀ�ĵأ�
//ter(terminal)��ʾ���ݵ�ǰ�н�������Ŀ�Ĳ㣬���ڸ�����state���жϡ�
//x���ڸ����ж��Ƿ��ǹؼ�¥��
int time = 0;

struct elevator {
	int state;
	int num;
	int floor;
	int ter;
	int goal[4];
	int x;

};

//���ݲ����ĳ�ʼ��
struct elevator ele[2] = {{0,  0, 1, 1, {-1, -1, -1, -1}, 0},
	{0,  0, 7, 7, {-1, -1, -1, -1}, 0}
};
int j, k, m, n; //�������������ڱ���

//����һ���˶��ĺ���
int move(int *h, int state) {
	if (state == 2)
		*h = *h - 1;
	if (state == 1)
		*h = *h + 1;
	return 0;
}

//�����ж��˶�Ŀ�ĵصļ�������
//1��������ͬʱ����ʱ���ж�
int check1(int h1, int *ter1, int h2, int *ter2) {
	//�ȼ���Ϸ������Ϸ�������
	for (m = 0; m < k; m = m + 1) {
		if (req[m].sta == 0 && req[m].A > *ter1) {
			*ter1 = req[m].A;
		}
	}

	for (m = 0; m < k; m = m + 1) {
		if (req[m].sta == 0 && req[m].A > *ter2) {
			//����ʹ���˱Ƚ������ݵ�ĳһ¥���ʱ�䳤�̵��оݣ���ͬ
			if ((req[m].A < h1 && req[m].dir == 1) || (req[m].dir == 2 && (*ter1 - h1 + *ter1 - req[m].A) >= (req[m].A - h2)))
				*ter2 = req[m].A;
		}
	}
	return 0;
}

//2��������ͬʱ����ʱ���ж�
int check2(int h1, int *ter1, int h2, int *ter2) {

	for (m = 0; m < k; m = m + 1) {
		if (req[m].sta == 0 && req[m].A < *ter1) {
			*ter1 = req[m].A;
		}
	}

	for (m = 0; m < k; m = m + 1) {
		if (req[m].sta == 0 && req[m].A < *ter2 )
			if ((req[m].A > h1 && req[m].dir == 2) || (req[m].dir == 1 && (h1 - *ter1 + req[m].A - *ter1) >= (h2 - req[m].A)))
				*ter2 = req[m].A;
	}
	return 0;
}

//���ĳ�����Ϸ��Ƿ�������
int check3(int h, int *ter) {

	for (m = 0; m < k; m = m + 1) {
		if (req[m].sta == 0 && req[m].A > *ter) {
			*ter = req[m].A;
			break;
		}
	}
}

//���ĳ�����·��Ƿ�������
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
	for (j = 0; j < 2; j = j + 1) {
		printf("������%d�ŵ��ݵ���ʼ¥��\n(������һ��1��10֮�������)\n", j);
		scanf("%d", &ele[j].floor);
		ele[j].ter = ele[j].floor;
	}
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
			if (req[i].A > req[i].B)
				req[i].dir = 2;
			else
				req[i].dir = 1;
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
//����������ݵĳ�ʼ״̬
	printf("����\t¥��\tʱ��\t����\n��ʼ״̬\n");
	for (j = 0; j < 2; j = j + 1) {
		printf("����%d:\t%d\t%d\t%d\n", j, ele[j].floor, time, ele[j].num);
	}
	printf("��ʼ����\n");
//��ʼÿһ����λʱ��Ĵ���
	for (time = tmin; time <= tmax || ele[0].state != 0 || ele[1].state != 0; time = time + 1) {
		//��鵱ǰʱ����û���µ�����
		while (time == req[k].T) {
			k = k + 1;
		}
		ele[0].x = 0;
		ele[1].x = 0;

		//��ÿ�����ݷֱ������޳˿����ϵ���
		for (j = 0; j < 2; j = j + 1) {

			if (ele[j].state != 0) {
				//�����ƶ�һ��¥��
				move (&ele[j].floor, ele[j].state);
				//�ȼ���Ƿ������µ���
				for (m = 0; m < 4; m = m + 1) {
					if (req[ele[j].goal[m]].B == ele[j].floor) {
						ele[j].num = ele[j].num - 1;
						req[ele[j].goal[m]].sta = 2;
						ele[j].goal[m] = -1;
						ele[j].x = 1;
					}
				}
				//�ټ���Ƿ������ϵ���
				for (m = 0; m < k; m = m + 1) {
					if (req[m].sta == 0 && req[m].dir == ele[j].state && ele[j].num < 4 && req[m].A == ele[j].floor) {
						ele[j].x = 1;
						for (n = 0; n < 4; n = n + 1) {
							if (ele[j].goal[n] == -1) {
								ele[j].goal[n] = m;
								break;
							}
						}
						ele[j].num = ele[j].num + 1;
						req[m].sta = 1;
					}
				}
				//������ֹͣʱ�ж��Ƿ�����ǡ���ڵ�ǰ¥�㰴����
			} else {
				for (m = 0; m < k; m = m + 1) {
					if (ele[j].floor == req[m].A && req[m].sta == 0) {
						ele[j].x = 1;

						for (n = 0; n < 4; n = n + 1) {
							if (ele[j].goal[n] == -1) {
								ele[j].goal[n] = m;
								break;
							}
						}
						ele[j].num = ele[j].num + 1;
						req[m].sta = 1;
						if (req[m].A > req[m].B)
							ele[j].state = 2;
						else
							ele[j].state = 1;
						ele[j].ter = req[m].A;
						break;
					}
				}
			}

		}

		//����ڵ����ϵ��˵�����
		ele[0].ter = ele[0].floor;
		ele[1].ter = ele[1].floor;

		for (j = 0; j < 2; j = j + 1) {
			if (ele[j].num != 0) {
				for (m = 0; m < 4; m = m + 1) {
					if (ele[j].state == 1 && ele[j].goal[m] >= 0 && req[ele[j].goal[m]].B > ele[j].ter)
						ele[j].ter = req[ele[j].goal[m]].B;
					if (ele[j].state == 2 && ele[j].goal[m] >= 0 && req[ele[j].goal[m]].B < ele[j].ter )
						ele[j].ter = req[ele[j].goal[m]].B;
				}
			}
		}
		//�����������¥���ƽ��ֵ�����ں������ж�
		float ave = (ele[0].floor + ele[1].floor) / 2;
		//����ʱ�е�����û�ˣ�������ж�,���½��з����Ŀ�ĵصĵ���
		if (ele[0].num == 0 || ele[1].num == 0) {
			//���ǵ��������˶�ʱ
			if (ele[0].state != 0 && ele[1].state != 0) {

				if (ele[0].state == ele[1].state) {

					//��ʱ��������ͬʱ����
					if (ele[0].state == 1) {
						if (ele[0].floor >= ele[1].floor)
							check1(ele[0].floor, &ele[0].ter, ele[1].floor, &ele[1].ter);
						else
							check1(ele[1].floor, &ele[1].ter, ele[0].floor, &ele[0].ter);
					}
					//����������ͬʱ����
					if (ele[0].state == 2) {
						if (ele[0].floor <= ele[1].floor)
							check2(ele[0].floor, &ele[0].ter, ele[1].floor, &ele[1].ter);
						else
							check2(ele[1].floor, &ele[1].ter, ele[0].floor, &ele[0].ter);
					}

				} //���������ݷ���ͬ
				else {
					int a, b;
					//a��ʾ���ϵĵ��ݣ�b��ʾ���µĵ���
					if (ele[0].state == 1) {
						a = 0;
						b = 1;
					} else {
						a = 1;
						b = 0;
					}
					if (ele[a].floor >= ele[b].floor) {
						for (m = 0; m < k; m = m + 1) {
							if (req[m].sta == 0) {
								if (req[m].A > ele[a].ter)
									ele[a].ter = req[m].A;
								if (req[m].A < ele[b].ter)
									ele[b].ter = req[m].A;
							}
						}
					} else {

						for (m = 0; m < k; m = m + 1) {
							if (req[m].sta == 0) {
								//������о�ֵ������ϸ����
								if (req[m].A < ave && req[m].A > ele[a].ter)
									ele[a].ter = req[m].A;
								else if (req[m].A >= ave && req[m].A < ele[b].ter)
									ele[b].ter = req[m].A;
							}
						}
					}

				}

				//����Ƿ���䵽������û���䵽�����ȼٶ��õ��ݿ���
				for (j = 0; j < 2; j = j + 1) {
					if (ele[j].floor == ele[j].ter) {

						ele[j].state = 0;

					}
				}

			}
			//�������ݶ����ڿ���״̬ʱ

re1:
			if (ele[0].state == 0 && ele[1].state == 0) {
				int a, b;
				//a��ʾ�ϸߵ��Ǹ����ݣ�b��ʾ�ϵ͵��Ǹ�����
				if (ele[0].floor > ele[1].floor) {
					a = 0;
					b = 1;
				} else {
					a = 1;
					b = 0;
				}

				//�ȼ�������Ƿ�������
				for (m = 0; m < k; m = m + 1) {
					if (req[m].A > ele[a].floor && req[m].sta == 0) {
						ele[a].ter = req[m].A;
						break;
					}
				}
				for (m = 0; m < k; m = m + 1) {
					if (req[m].A < ele[b].floor && req[m].sta == 0) {
						ele[b].ter = req[m].A;
						break;
					}
				}
				//������඼û�У������м������
				if (ele[a].floor == ele[a].ter && ele[b].floor == ele[b].ter) {
					for (m = 0; m < k; m = m + 1) {
						if (req[m].A < ave && req[m].sta == 0 && req[m].A > ele[b].ter)
							ele[b].ter = req[m].A;
						else if (req[m].A >= ave && req[m].sta == 0 && req[m].A < ele[a].ter)
							ele[a].ter = req[m].A;
					}
				}
				//�����ж������ݵ�״̬
				for (j = 0; j < 2; j = j + 1) {
					if (ele[j].floor > ele[j].ter) {
						ele[j].state = 2;
					} else if (ele[j].floor < ele[j].ter)
						ele[j].state = 1;
				}
			}
re2:
			//����������һ������һ��������ʱ
			if ((ele[0].state != 0 && ele[1].state == 0) || (ele[0].state == 0 && ele[1].state != 0)) {
				//a��ʾ�����еĵ��ݣ�b��ʾ���еĵ���
				int a, b;
				if (ele[0].state != 0 && ele[1].state == 0) {
					a = 0;
					b = 1;
				} else {
					a = 1;
					b = 0;
				}
				//�ȿ��ǲ����е����Ѿ�ȷ������һ��λʱ��Ҫ���е����
				if (ele[a].floor != ele[a].ter) {
					//��a��������
					if (ele[a].state == 1) {
						//��b������a�����·�
						if (ele[a].floor >= ele[b].floor) {
							check4(ele[b].floor, &ele[b].ter); //���b�����·���û������
							if (ele[b].floor == ele[b].ter)    //���û����������������
								check1(ele[a].floor, &ele[a].ter, ele[b].floor, &ele[b].ter);
						}
						//��b������a�����Ϸ�
						else {
							check3(ele[b].floor, &ele[b].ter); //���b�����Ϸ���û������
							if (ele[b].floor == ele[b].ter) {  //���û����������������
								for (m = 0; m < k; m = m + 1) {
									if (req[m].sta == 0) {
										if ((req[m].A < ele[b].floor && req[m].dir == 2)
										        || (req[m].A < ele[a].floor) || req[m].A > ave)
											ele[b].ter = req[m].A;
									}
								}
							}
						}
					}
					//��a��������
					else {
						//��a������b�����·�
						if (ele[a].floor <= ele[b].floor) {
							check3(ele[b].floor, &ele[b].ter);//���b�����Ϸ���û������
							if (ele[b].floor == ele[b].ter)   //���û����������������
								check2(ele[a].floor, &ele[a].ter, ele[b].floor, &ele[b].ter);
						}//��a������b�����Ϸ�
						else {
							check4(ele[b].floor, &ele[b].ter); //���b�����·���û������
							if (ele[b].floor == ele[b].ter) {  //���û����������������
								for (m = 0; m < k; m = m + 1) {
									if (req[m].sta == 0) {
										if ((req[m].A < ele[a].floor && req[m].dir == 1)
										        || (req[m].A > ele[a].floor) || req[m].A < ave)
											ele[b].ter = req[m].A;
									}
								}

							}
						}
					}
				}
				//���жϲ����е���ûȷ����һ��λʱ���Ƿ����е����
				else {
					if (ele[a].state == 1 && ele[a].floor < ele[b].floor) {
						for (m = 0; m < k; m = m + 1) {
							if (req[m].sta == 0) {
								if (req[m].A < ave && req[m].A > ele[a].ter)
									ele[a].ter = req[m].A;
							}
						}
					} else if (ele[a].state == 2 && ele[a].floor > ele[b].floor) {
						for (m = 0; m < k; m = m + 1) {
							if (req[m].sta == 0 && req[m].A >= ave && req[m].A < ele[a].ter)
								ele[a].ter = req[m].A;
						}

					}
					if (ele[a].floor == ele[a].ter) {
						ele[a].state = 0;
						goto re1;
					} else
						goto re2;
				}
			}
		}
		//��һ�ν��е�������״̬���ж���
		for (j = 0; j < 2; j = j + 1) {
			if (ele[j].floor == ele[j].ter) {

				ele[j].state = 0;
			} else if (ele[j].floor > ele[j].ter)
				ele[j].state = 2;
			else
				ele[j].state = 1;
			//�������Ĺ����У��ҷ����Լ�һֱû��ȫ�濼�ǵ��ݵ�ǰ¥��ĳ˿�����
			//�����������в���
			for (m = 0; m < k; m = m + 1) {
				if (req[m].sta == 0 && ele[j].num < 4 && req[m].A == ele[j].floor) {
					if (req[m].dir == ele[j].state || ele[j].state == 0) {
						ele[j].x = 1;
						for (n = 0; n < 4; n = n + 1) {
							if (ele[j].goal[n] == -1) {
								ele[j].goal[n] = m;
								break;
							}
						}
						ele[j].num = ele[j].num + 1;
						req[m].sta = 1;
						ele[j].state = req[m].dir;
					}
				}
			}
			//���йؼ�¥����Ϣ�����
			if (ele[j].x == 1)
				printf("����%d:\t%d\t%d\t%d\n", j, ele[j].floor, time, ele[j].num);
		}

	}
	printf("���н���");
	return 0;
}

