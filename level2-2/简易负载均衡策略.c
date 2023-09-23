#include <stdio.h>

//设置结构体，
//A表示起始楼层，B表示目的楼层,T表示呼叫时间
//sta(state)为零时表示未接上，为1时表示已接上，为2时表示已放下
//dir(direction)为0时表示向下，为1时表示向上
struct request {
	int A, B, T, dir;
	int sta;
} req[1000];

//定义一个电梯移动的函数
int move( int *h, int *end, int *t, int i) {
	int m = 0;
	while (*h != *end) {
		if (*h > *end)
			*h = *h - 1;
		else*h = *h + 1;
		*t = *t + 1;
		//检查在运行过程中有没有新的请求
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
	//设置一个数组用于记录两部电梯的起始楼层
	int ele[2] = {};
	//数据的输入
	for (int j = 0; j < 2; j = j + 1) {
		printf("请输入%d号电梯的起始楼层\n(请输入一个1到10之间的整数)\n", j);
		scanf("%d", &ele[j]);

	}
	printf ("请分行输入多个起始楼层A和目的楼层B及呼叫时间D\n"
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
			if (req[i].A > req[i].B)
				req[i].dir = 0;
			else
				req[i].dir = 1;
			req[i].sta = 0;
			i = i + 1;
		}
	}
	int elevator = 0; //0表示0号电梯，1表示1号电梯
	int sign[9] = {0};
	int m = 0;//用于遍历结构体数组
//给0号电梯分配下标为偶数的任务req
//给1号电梯分配下标为奇数的任务req
//先处理0号电梯的运行过程，再处理1号电梯的运行过程
	for (elevator = 0; elevator < 2; elevator++) {
		int time = 0;
		int floor = ele[elevator];
		int state = 1;//1表示上行，0表示下行
		int num = 0;//表示电梯上的人数
//输出初始状态
		printf("\n%d号电梯\n楼层\t时间\t人数\n", elevator);
		printf("初始状态：\n%d\t%d\t%d\n开始运行：\n", floor, time, num);

		//找出最大的呼叫时间tmax，便于后续的判断
		int tmax = 0;
		for (m = elevator; m < i; m = m + 2) {
			if (req[m].T > tmax)
				tmax = req[m].T;
		}
		//while中进行下一停靠层的选择并计算停靠后电梯人数的变化
re:
		while (1) {

			int j = 0, n = 0;//j用于记录数组下标，n为电梯上人数的变化量
			int x = 0; //x用于表示下一停靠层

			int p = 1;//用于辅助判断是否运行结束
rejudge:
			//考虑上行的情况
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
						//考虑多人同时下电梯的情况
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
						if (req[m].A < x && num < 4) { //电梯没满载时还可以上人
							x = req[m].A;
							j = 0;
							sign[j] = m;
							n = 1;
						}
						//考虑下电梯的同时有人上电梯的情况

					}

				}

				if (x != 11) {
					p = 1;
				} else {
					//在当前上行任务结束时判断上方是否有人要下楼
					x = floor;
					for (m = elevator; m < i; m = m + 2) {
						if (req[m].sta == 0 && req[m].T <= time && req[m].A > x) {
							x = req[m].A;
							j = 0;
							sign[j] = m;
							n = 1;
							p = 1;
						}
					}//如果没有则改变运行方向或静止
					if (x == floor ) {
						if (p == 1) {
							p = 0;
							state = 0;
						} else
							goto decide;//跳出循环
					}

				}
			}
			//考虑下行的情况
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
						//考虑多人同时下电梯的情况
						else {
							n = n - 1;
							j = j + 1;
							sign[j] = m;
						}
					}
				}//&& req[m].A >= x
				for (m == elevator; m < i; m = m + 2) {

					if (req[m].sta == 0 && req[m].T <= time && req[m].A <= floor && req[m].dir == 0) {
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
				if (x != 0) {
					p = 1;
				} else {
					//在当前下行任务结束时判断下方是否有人要上楼
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
					//如果没有则改变运行方向或静止
					if (x == floor ) {
						if (p == 1) {
							p = 0;
							state = 1;
							goto rejudge;
						}//改变运行方向后重新判定
						else
							goto decide;//跳出循环
					}

				}
			}
//电梯开始运动
			move(&floor, &x, &time, i);
			//判断运动有没有被打断
			if (x != -1) {
				//若没被打断则输出
				num = num + n;
				for (m = 0; m <= j; m++) {
					//停靠后一些请求已经完成
					req[sign[m]].sta = req[sign[m]].sta + 1;
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
				for (m = elevator; m < i; m = m + 2) {
					if (req[m].T == time) {
						printf ("%d\t空闲静止\n", time);
						goto re;
					}
				}
			}
		} else//如果之后没有请求
			printf("电梯%d运行结束\n", elevator);
	}
	return 0;
}















