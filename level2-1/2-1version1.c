#include <stdio.h>

//设置结构体，
//A表示起始楼层，B表示目的楼层,D表示呼叫时间
//C为零时表示未接上，C为1时表示已接上，C为2时表示已放下
struct request {
	int A, B, T;
	int C;
} req[1000];

//定义一个电梯移动的函数
int move( int *h, int *end, int *t, int i) {
	int m = 0;
	while (*h != *end) {
		if (*h > *end)
			*h = *h - 1;
		else*h = *h + 1;
		*t = *t + 1;
		for (m = 0; m < i; m++) {
			if (req[m].T == *t) {
				*end = -1; //*end=-1表示没有到达目的地，便于后续判断
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
	//表示电梯上的人数
	int sign[5] = {0};
	int m = 0;//用于遍历结构体数组
	//数据的输入
	printf("请输入'elevator a'，a表示电梯的起始位置\n");
	scanf("elevator %d", &floor);
	printf ("请分行输入多个起始楼层A和目的楼层B及呼叫时间T\n"
	        "A、B、D之间用单个空格进行间隔，"
	        "输入所有数据后以“0 0 0”结束\n");
	int i = 0;
	while (1) {
		scanf("%d %d %d", &req[i].A, &req[i].B, &req[i].T);
		if (req[i].A == 0 && req[i].B == 0)
			break;
		if (req[i].A > 10 || req[i].A < 1 || req[i].B > 10 || req[i].B < 1 || req[i].A == req[i].B)
			printf("输入的楼层不符合要求，请重新输入这组数据\n");
		else {
			req[i].C = 0;
			i = i + 1;
		}
	}
	//输出初始状态
	printf("楼层\t时间\t人数\n");
	printf("初始状态：\n%d\t%d\t%d\n开始运行：\n", floor, time, num);
	//找出最大的呼叫时间tmax，便于后续的判断
	int b = 0;
	int tmax = 0;
	for (b = 0; b < i; b++) {
		if (req[b].T > tmax)
			tmax = req[b].T;
	}
//while中进行下一停靠层的选择并计算停靠后电梯人数的变化
re:
	while (1) {

		int j = 0, n = 0;//j为辅助参数，n为电梯上人数的变化量
		int x ;//x用于表示下一停靠层

		int p = 1;//用于辅助判断是否运行结束
		//考虑上行的情况
sta1:
		if (state == 1) {
			x = 11;
			//先考虑下电梯的请求
			for (m = 0; m < i; m++) {
				if (req[m].C == 1 && req[m].B >= floor && req[m].B <= x) {
					if (req[m].B < x) {
						x = req[m].B;
						n = -1;
						j = 0;
						sign[j] = m;
					}
					//考虑多人同时下电梯的情况
					else {
						n = n - 1;
						j = j + 1;
						sign[j] = m;
					}
				}
			}
			//再考虑上电梯的请求
			for (m = 0; m <= i - 1; m++) {
				if (req[m].C == 0 && req[m].A >= floor && req[m].T <= time  ) {
					//考虑下电梯的同时有人上电梯的情况
					if (req[m].A == x) {
						n = n + 1;
						j = j + 1;
						sign[j] = m;
					}
					//考虑上电梯的请求
					if (req[m].A < x && num < 4) {
						x = req[m].A;
						j = 0;
						sign[j] = m;
						n = 1;
					}


				}

			}

			//进行结果判断
			if (x != 11) {
				p = 1;
			}
			if ( x == 11 && p == 1 ) {
				p = 0;
				state = 0;
				goto sta0;
			}
			if (x == 11 && p == 0  ) {
				goto decide;//即当前时刻电梯空闲
			}
		}
		//考虑下行的情况
sta0:
		if (state == 0) {
			x = 0;
			//先考虑下电梯的请求
			for (m = 0; m < i; m++) {
				if (req[m].C == 1 && req[m].B <= floor && req[m].B >= x) {
					if (req[m].B > x) {
						x = req[m].B;
						n = -1;
						j = 0;
						sign[j] = m;
					}
					//考虑多人同时下电梯的情况
					else {
						n = n - 1;
						j = j + 1;
						sign[j] = m;
					}
				}
			}
			//再考虑上电梯的请求
			for (m = 0; m <= i - 1; m++) {
				if (req[m].C == 0 && req[m].A <= floor  && req[m].T <= time ) {
					//考虑下电梯的同时有人上电梯
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
			//进行结果判断
			if (x != 0) {
				p = 1;
			}
			if ( x == 0 && p == 1 ) {
				p = 0;
				state = 1;
				goto sta1;
			}
			if ( x == 0 && p == 0 ) {
				goto decide;//即当前时刻电梯空闲
			}
		}
//电梯开始运动
		move(&floor, &x, &time, i);
		//判断运动有没有被打断
		if (x != -1) {
			//若没被打断则输出
			num = num + n;
			int q = 0;
			for (q = 0; q <= j; q++) {
				//停靠后标记已经完成的请求
				req[sign[q]].C = req[sign[q]].C + 1;
			}
			printf("%d\t%d\t%d\n", floor, time, num);
		}

	}
//判断空闲之后是否仍有请求
decide:
	if (time < tmax)
		//如果之后的时间仍有请求
	{
		printf("%d\t%d-", floor, time);
		while (1) {
			time = time + 1;
			for (m = 0; m < i; m++) {
				if (req[m].T == time) {
					printf ("%d\t空闲静止\n", time);
					goto re;
				}
			}
		}
	} else
		printf("运行结束");
	return 0;
}
