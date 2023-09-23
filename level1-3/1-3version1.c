#include <stdio.h>
#define _CRT_SECURE_NO_WARNINGS

//设置结构体，
//A表示起始楼层，B表示目的楼层
//C为零时表示未接上，C为1时表示已接上，C为2时表示已放下
struct request {
	int A, B;
	int C;
} req[100];

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
	int floor = 1;
	int time = 0;
	int full = 4;
	int num = 0;//表示电梯上的人数
	int state = 1; //1代表向上，0代表向下

	//数据的输入
	printf ("请分行输入多个起始楼层A和目的楼层B\n"
	        "AB之间用单个空格进行间隔，"
	        "输入所有数据后以“0 0”结束\n");
	int i = 0;
	int a = 1; //用于辅助判断循环条件
	while (a == 1) {
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
	printf("%d\t%d\t%d\n", floor, time, num);
	//电梯运行
	int m = 0, n = 0;
	int x, y;
	int des = 0;
	int j, k;
	int p = 1;
	//x表示接人目的层，y表示放人目的层
	//mn为辅助用于遍历的参数,des表示最终确定的下一个停靠层
	//jk为辅助参数,p用于判断是否达到运行结束的条件
//在电梯没有满载时
	while (a == 1) {
		if (num != full) {
			//电梯上行时的确定下一停靠层
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
				//判断是否继续上行或结束
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
			//电梯下行时的确定下一停靠层
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
				//判断是否继续下行或结束
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
//在电梯满载时
		if (num == full) {
			x = 12;
			//x=12用于方便后续运行时的判断
			//当电梯上行时
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
				//判断是否继续上行
				if (y == 11)
					state = 0;
				else
					des = y;
			}
			//当电梯下行时
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
				//判断是否继续下行
				if (y == 0) {
					state = 1;
					goto fulstate1;
				} else
					des = y;
			}

		}
		//电梯进行一次运行并输出状态

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
	printf("运行结束");
	return 0;
}
