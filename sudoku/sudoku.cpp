// sudoku.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <chrono>
#include <random>
#include <algorithm> 
#include <functional>
#include <cstdlib>
#include <cstdio>
#include <fstream>
#include <time.h>
#include <string>


using namespace std;

//随机生成一行1~9  第一个数为固定
auto init = [](int* list)
{
	int jj = 0;
	for (jj = 0; jj < 9; jj++)
	{
		*(list + jj) = jj + 1;
	}
	*list = (4 + 0) % 9 + 1;                                        //学号031502404尾数为4 0
	*(list + *list - 1) = 1;
	unsigned seed = chrono::system_clock::now().time_since_epoch().count();//以时间设置随机种子
	shuffle(list + 1, list + 9, default_random_engine(seed));//随机排列函数
															 /*for (jj = 0; jj < 9; jj++)
															 cout << *(list + jj) << " ";
															 cout << endl;*/
};

bool is_number(string str)

{
	for (auto i = 0; i < str.size(); i++)
	{
		if (str[i]<'0' || str[i]>'9')
		{
			return false;
		}
	}
	return true;
}

int main(int argc, char *argv[])
{
	ofstream ocout;
	ocout.open("test.txt");

	int scene[9][9] = { 0 };
	int num1, ii;
	//cin >> num1;
	if (argc == 3)

	{

		if (strcmp(argv[1], "-c") == 0)

		{

			if (is_number(argv[2]))
			{
				num1 = stoi(argv[2]);
				for (ii = 0; ii < num1; ii++)
				{

					init(scene[0]);  //初始化第一行  第一个数字固定
					int trylist[9] = { 1 ,2 ,3 ,4 ,5 ,6 ,7 ,8 ,9 };
					unsigned seed = chrono::system_clock::now().time_since_epoch().count();//以时间设置随机种子
					shuffle(&trylist[0], &trylist[9], default_random_engine(seed));//随机排列函数
																				   //用于数字的尝试顺序

																				   /*for (int jj(0); jj < 9; jj++)
																				   cout << trylist[jj]<< " ";
																				   cout << endl;*/


																				   //判断填入的数字是否合法
					auto judge_tf = [&scene](int i, int j, int num) -> bool
					{
						int k = 0;
						//判断区域相同
						int count = j % 3 + i % 3 * 3;
						while (count--)
							if (!(scene[i - i % 3 + count / 3][j - j % 3 + count % 3] - num))
								return false;
						//判断列相同
						for (k = 0; k < i; k++)
							if (scene[k][j] == num)
								return false;
						//判断行相同
						for (k = 0; k < j; k++)
							if (scene[i][k] == num)
								return false;
						return true;
					};



					//简单回溯方法填入数字
					function<bool(int, int, int*)> fill = [&trylist, &fill, &scene, judge_tf](int y, int x, int* numloc) -> bool
					{
						if (y > 8)
							return true;
						if (judge_tf(y, x, *numloc))
						{
							scene[y][x] = *numloc;
							/*for (int i(0); i < 9; i++)
							{
							for (int j : scene[i])
							cout << j << " ";
							cout << endl;
							}
							cout << endl << endl;*/
							if (fill(y + (x + 1) / 9, (x + 1) % 9, trylist))
								return true;
						}
						scene[y][x] = 0;
						if (numloc - trylist >= 8)
							return false;
						if (fill(y, x, numloc + 1))
							return true;
					};


					fill(1, 0, trylist);//调用函数求解
										//输出
										//cout << "   " << ii + 1 << endl;
					for (int i(0); i < 9; i++)
					{
						for (int j : scene[i])
							ocout << j << " ";
						ocout << endl;
					}
					ocout << endl << endl;
				}
				return 0;

			}

		}

	}

	ocout << ("err") << endl;

	ocout.close();
	return 0;
}
