#include <stdio.h>
#define _CRT_SECURE_NO_WARNINGS

//设置结构体，
//A表示起始楼层，B表示目的楼层
//C为零时表示未接上，C为1时表示已接上，C为2时表示已放下
struct request {
	int A, B;
	int C;
} req[1000];

//定义一个电梯移动的函数
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
	//表示电梯上的人数
	int sign[9] = {0};//数组用于记录相同楼层上下的请求
	//数据的输入
	printf ("请分行输入多个起始楼层A和目的楼层B\n"
	        "AB之间用单个空格进行间隔，"
	        "输入所有数据后以“0 0”结束\n");
	int i = 0;
	while (1) {
		scanf("%d %d", &req[i].A, &req[i].B);
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
	printf("初始状态：\n%d\t%d\t%d\n开始运行\n", floor, time, num);
	//电梯运行
	while (1) {
		int j = 0;//j为辅助参数，用于记录数组的下标

//确定下一停靠层
		int x, n = 0; //x用于表示下一停靠层，n为电梯上人数的变化量
		int m = 0;//用于遍历结构体数组
		int p = 1;//用于辅助判断是否上行和下行都没有任务，
		//考虑上行的情况
sta1:
		if (state == 1) {
			x = 11;
			//由先下后上的原则，先考虑下电梯的请求
			for (m = 0; m <= i - 1; m++) {
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
				if (req[m].C == 0 && req[m].A >= floor ) {
					//考虑下电梯的同时有人上电梯的情况
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
			//结果判断
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
		//考虑下行的情况
sta0:
		if (state == 0) {
			x = 0;
			//先考虑下电梯的请求
			for (m = 0; m <= i - 1; m++) {
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
				if (req[m].C == 0 && req[m].A <= floor ) {
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
			//结果判断
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
//电梯开始运动
		move(&floor, x, &time);
		num = num + n;
		int q = 0;
		for (q = 0; q <= j; q++) {
			//停靠后一些请求已经完成
			req[sign[q]].C = req[sign[q]].C + 1;
		}
		printf("%d\t%d\t%d\n", floor, time, num);
	}

end:
	printf("运行结束");
	return 0;
}
