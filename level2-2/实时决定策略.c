#include <stdio.h>
#include <math.h>
#define _CRT_SECURE_NO_WARNINGS

//设置结构体，
//start表示起始楼层，end表示目的楼层,time表示呼叫时间
//sta为零时表示未接上，为1时表示已接上，为2时表示已放下
//dir(direction)为1时表示向上，为2时表示向下
struct request {
	int A, B, T ;
	int dir, sta;
} req[1000];

//设置电梯运行的参数
//state表示运动方向，0表示空闲，1表示上行，2表示下行。
//num表示电梯上的人数，floor表示电梯所在的层数，time表示时间。
//goal用于标记当前在电梯上的人的目的地，
//ter(terminal)表示电梯当前行进方向将来目的层，用于辅助对state的判断。
//x用于辅助判断是否是关键楼层
int time = 0;

struct elevator {
	int state;
	int num;
	int floor;
	int ter;
	int goal[4];
	int x;

};

//电梯参数的初始化
struct elevator ele[2] = {{0,  0, 1, 1, {-1, -1, -1, -1}, 0},
	{0,  0, 7, 7, {-1, -1, -1, -1}, 0}
};
int j, k, m, n; //辅助参数，用于遍历

//定义一个运动的函数
int move(int *h, int state) {
	if (state == 2)
		*h = *h - 1;
	if (state == 1)
		*h = *h + 1;
	return 0;
}

//设置判定运动目的地的几个函数
//1：两电梯同时向上时的判定
int check1(int h1, int *ter1, int h2, int *ter2) {
	//先检查上方电梯上方的请求
	for (m = 0; m < k; m = m + 1) {
		if (req[m].sta == 0 && req[m].A > *ter1) {
			*ter1 = req[m].A;
		}
	}

	for (m = 0; m < k; m = m + 1) {
		if (req[m].sta == 0 && req[m].A > *ter2) {
			//这里使用了比较两电梯到某一楼层的时间长短的判据，下同
			if ((req[m].A < h1 && req[m].dir == 1) || (req[m].dir == 2 && (*ter1 - h1 + *ter1 - req[m].A) >= (req[m].A - h2)))
				*ter2 = req[m].A;
		}
	}
	return 0;
}

//2：两电梯同时向下时的判定
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

//检查某电梯上方是否有请求
int check3(int h, int *ter) {

	for (m = 0; m < k; m = m + 1) {
		if (req[m].sta == 0 && req[m].A > *ter) {
			*ter = req[m].A;
			break;
		}
	}
}

//检查某电梯下方是否有请求
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
	for (j = 0; j < 2; j = j + 1) {
		printf("请输入%d号电梯的起始楼层\n(请输入一个1到10之间的整数)\n", j);
		scanf("%d", &ele[j].floor);
		ele[j].ter = ele[j].floor;
	}
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
			if (req[i].A > req[i].B)
				req[i].dir = 2;
			else
				req[i].dir = 1;
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
//输出两部电梯的初始状态
	printf("电梯\t楼层\t时间\t人数\n初始状态\n");
	for (j = 0; j < 2; j = j + 1) {
		printf("电梯%d:\t%d\t%d\t%d\n", j, ele[j].floor, time, ele[j].num);
	}
	printf("开始运行\n");
//开始每一个单位时间的处理
	for (time = tmin; time <= tmax || ele[0].state != 0 || ele[1].state != 0; time = time + 1) {
		//检查当前时间有没有新的请求
		while (time == req[k].T) {
			k = k + 1;
		}
		ele[0].x = 0;
		ele[1].x = 0;

		//对每部电梯分别检查有无乘客下上电梯
		for (j = 0; j < 2; j = j + 1) {

			if (ele[j].state != 0) {
				//电梯移动一个楼层
				move (&ele[j].floor, ele[j].state);
				//先检查是否有人下电梯
				for (m = 0; m < 4; m = m + 1) {
					if (req[ele[j].goal[m]].B == ele[j].floor) {
						ele[j].num = ele[j].num - 1;
						req[ele[j].goal[m]].sta = 2;
						ele[j].goal[m] = -1;
						ele[j].x = 1;
					}
				}
				//再检查是否有人上电梯
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
				//当电梯停止时判断是否有人恰好在当前楼层按电梯
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

		//检查在电梯上的人的需求
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
		//计算出两电梯楼层的平均值，便于后续的判断
		float ave = (ele[0].floor + ele[1].floor) / 2;
		//若此时有电梯上没人，则进行判定,重新进行方向和目的地的调整
		if (ele[0].num == 0 || ele[1].num == 0) {
			//考虑电梯正在运动时
			if (ele[0].state != 0 && ele[1].state != 0) {

				if (ele[0].state == ele[1].state) {

					//此时若两电梯同时向上
					if (ele[0].state == 1) {
						if (ele[0].floor >= ele[1].floor)
							check1(ele[0].floor, &ele[0].ter, ele[1].floor, &ele[1].ter);
						else
							check1(ele[1].floor, &ele[1].ter, ele[0].floor, &ele[0].ter);
					}
					//若两部电梯同时向下
					if (ele[0].state == 2) {
						if (ele[0].floor <= ele[1].floor)
							check2(ele[0].floor, &ele[0].ter, ele[1].floor, &ele[1].ter);
						else
							check2(ele[1].floor, &ele[1].ter, ele[0].floor, &ele[0].ter);
					}

				} //若两部电梯方向不同
				else {
					int a, b;
					//a表示向上的电梯，b表示向下的电梯
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
								//这里的判据值得再仔细斟酌
								if (req[m].A < ave && req[m].A > ele[a].ter)
									ele[a].ter = req[m].A;
								else if (req[m].A >= ave && req[m].A < ele[b].ter)
									ele[b].ter = req[m].A;
							}
						}
					}

				}

				//检查是否分配到任务，若没分配到任务，先假定该电梯空闲
				for (j = 0; j < 2; j = j + 1) {
					if (ele[j].floor == ele[j].ter) {

						ele[j].state = 0;

					}
				}

			}
			//当两电梯都属于空闲状态时

re1:
			if (ele[0].state == 0 && ele[1].state == 0) {
				int a, b;
				//a表示较高的那个电梯，b表示较低的那个电梯
				if (ele[0].floor > ele[1].floor) {
					a = 0;
					b = 1;
				} else {
					a = 1;
					b = 0;
				}

				//先检查两侧是否有请求
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
				//如果两侧都没有，则考虑中间的请求
				if (ele[a].floor == ele[a].ter && ele[b].floor == ele[b].ter) {
					for (m = 0; m < k; m = m + 1) {
						if (req[m].A < ave && req[m].sta == 0 && req[m].A > ele[b].ter)
							ele[b].ter = req[m].A;
						else if (req[m].A >= ave && req[m].sta == 0 && req[m].A < ele[a].ter)
							ele[a].ter = req[m].A;
					}
				}
				//重新判定两电梯的状态
				for (j = 0; j < 2; j = j + 1) {
					if (ele[j].floor > ele[j].ter) {
						ele[j].state = 2;
					} else if (ele[j].floor < ele[j].ter)
						ele[j].state = 1;
				}
			}
re2:
			//当两部电梯一部空闲一部不空闲时
			if ((ele[0].state != 0 && ele[1].state == 0) || (ele[0].state == 0 && ele[1].state != 0)) {
				//a表示不空闲的电梯，b表示空闲的电梯
				int a, b;
				if (ele[0].state != 0 && ele[1].state == 0) {
					a = 0;
					b = 1;
				} else {
					a = 1;
					b = 0;
				}
				//先考虑不空闲电梯已经确定了下一单位时间要运行的情况
				if (ele[a].floor != ele[a].ter) {
					//当a电梯上行
					if (ele[a].state == 1) {
						//当b电梯在a电梯下方
						if (ele[a].floor >= ele[b].floor) {
							check4(ele[b].floor, &ele[b].ter); //检查b电梯下方有没有请求
							if (ele[b].floor == ele[b].ter)    //如果没有则检查其他的请求
								check1(ele[a].floor, &ele[a].ter, ele[b].floor, &ele[b].ter);
						}
						//当b电梯在a电梯上方
						else {
							check3(ele[b].floor, &ele[b].ter); //检查b电梯上方有没有请求
							if (ele[b].floor == ele[b].ter) {  //如果没有则检查其他的请求
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
					//当a电梯下行
					else {
						//当a电梯在b电梯下方
						if (ele[a].floor <= ele[b].floor) {
							check3(ele[b].floor, &ele[b].ter);//检查b电梯上方有没有请求
							if (ele[b].floor == ele[b].ter)   //如果没有则检查其他的请求
								check2(ele[a].floor, &ele[a].ter, ele[b].floor, &ele[b].ter);
						}//当a电梯在b电梯上方
						else {
							check4(ele[b].floor, &ele[b].ter); //检查b电梯下方有没有请求
							if (ele[b].floor == ele[b].ter) {  //如果没有则检查其他的请求
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
				//再判断不空闲电梯没确定下一单位时间是否运行的情况
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
		//再一次进行电梯运行状态的判定，
		for (j = 0; j < 2; j = j + 1) {
			if (ele[j].floor == ele[j].ter) {

				ele[j].state = 0;
			} else if (ele[j].floor > ele[j].ter)
				ele[j].state = 2;
			else
				ele[j].state = 1;
			//在最后检查的过程中，我发现自己一直没有全面考虑电梯当前楼层的乘客请求，
			//所以在最后进行补充
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
			//进行关键楼层信息的输出
			if (ele[j].x == 1)
				printf("电梯%d:\t%d\t%d\t%d\n", j, ele[j].floor, time, ele[j].num);
		}

	}
	printf("运行结束");
	return 0;
}

