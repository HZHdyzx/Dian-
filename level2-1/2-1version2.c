#include <stdio.h>
#include <math.h>
#define _CRT_SECURE_NO_WARNINGS

//设置结构体，
//A表示起始楼层，B表示目的楼层,T表示呼叫时间
//sta为零时表示未接上，为1时表示已接上，为2时表示已放下

struct request {
	int A, B, T ;
	int sta;
} req[1000];

//设置电梯运行的参数
//state表示运动方向，0表示空闲，1表示上行，2表示下行。
//num表示电梯上的人数，flo表示电梯所在的层数，time表示时间。
//goal用于标记当前在电梯上的人的目的地，
//ter(terminal)表示电梯当前行进方向将来目的层，用于辅助对state的判断。
//x用于辅助判断是否是关键楼层
int time = 0;
int state = 0;
int num = 0;
int flo = 1;
int ter;

int goal[4] = {-1, -1, -1, -1};
int x = 0;

int j, k, m, n; //辅助参数，用于遍历

//定义一个运动的函数
int move(int *h, int state) {
	if (state == 2)
		*h = *h - 1;
	if (state == 1)
		*h = *h + 1;
	return 0;
}

//检查某电梯上方是否有请求的函数
int check3(int h, int *ter) {

	for (m = 0; m < k; m = m + 1) {
		if (req[m].sta == 0 && req[m].A > *ter) {
			*ter = req[m].A;
			break;
		}
	}
}

//检查某电梯下方是否有请求的函数
int check4(int h, int *ter) {

	for (m = 0; m < k; m = m + 1) {
		if (req[m].sta == 0 && req[m].A < *ter) {
			*ter = req[m].A;
			break;
		}
	}

}

int main() {
	//数据的输入
	printf("请输入'elevator a'，a表示电梯的起始位置\n");
	scanf("elevator %d", &flo);
	printf ("请分行输入多个起始楼层A和目的楼层B及呼叫时间T\n"
	        "A、B、T之间用单个空格进行间隔，"
	        "输入所有数据后以“0 0 0”结束\n");
	int i = 0;

	while (1) {
		scanf("%d %d %d", &req[i].A, &req[i].B, &req[i].T);
		if (req[i].A == 0 && req[i].B == 0)
			break;
		if (req[i].A > 10 || req[i].A < 1 || req[i].B > 10 || req[i].B < 1 || req[i].A == req[i].B)
			printf("输入的楼层不符合要求，请重新输入这组数据\n");
		else {
			req[i].sta = 0;
			i = i + 1;
		}
	}

	req[i].T = -1;


//按照时间顺序对请求进行重新排序
	for (j = 0; j < i - 1; j = j + 1) {
		for (k = 0; k < i - 1 - j; k = k + 1) {
			if (req[k].T > req[k + 1].T) {
				req[i] = req[k + 1];
				req[k + 1] = req[k];
				req[k] = req[i];
			}
		}
	}
//记录的呼叫时间tmax和tmix，便于后续的判断
	int tmax = req[i - 1].T;
	int tmin = req[0].T;
	k = 0;
//输出电梯的初始状态
	printf("楼层\t时间\t人数\n初始状态\n");
	printf("%d\t%d\t%d\n", flo, time, num);
	printf("开始运行\n");
//开始每一个单位时间的处理
	for (time = tmin; time <= tmax || state != 0; time = time + 1) {
		//检查当前时间有没有新的请求
		while (time == req[k].T) {
			k = k + 1;
		}
		x = 0;

		if (state != 0) {
			//电梯移动一个楼层
			move (&flo, state);
			//先检查是否有人下电梯
			for (m = 0; m < 4; m = m + 1) {
				if (req[goal[m]].B == flo) {
					num = num - 1;
					req[goal[m]].sta = 2;
					goal[m] = -1;
					x = 1;
				}
			}
			//再检查是否有人上电梯
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
		} else {//当电梯停止时判断是否有人恰好在当前楼层按电梯
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
		//先检查电梯上的人的同方向的请求
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
		//进行关键楼层信息的输出
		if (x == 1)
			printf("%d\t%d\t%d\n", flo, time, num);
	}
	printf("运行结束");
	return 0;
}


