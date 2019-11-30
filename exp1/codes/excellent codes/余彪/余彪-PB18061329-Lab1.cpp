#include <stdio.h>
#include <stdlib.h>
#include "Polyn.h"
#define MAX 10
int inputNum(FILE* input);//输入多项式序号

int main()
{
	PolynList L[MAX];
	for (int i = 0; i < MAX; i++)
		L[i] = NULL;

	//FILE* input = fopen("/storage/emulated/0/AppProjects/MyNativeExecutable5/jni/polyn.in","r");
	FILE* input = fopen("polyn.in","r");
	//FILE* input = stdin;
	if (input == NULL)
	{
		printf("can't find file \"polyn.in\"\n");
		return -1;
	}

	//FILE* output = fopen("/storage/emulated/0/AppProjects/MyNativeExecutable5/jni/polyn.out","w");
	FILE* output = fopen("polyn.out","w");
	//FILE* output = stdout;
	
	if (output == NULL)
	{
		printf("can't create file \"polyn.out\"\n");
		return -1;
	}
		
	
	char* menu = 
		"==========================\n"
		"===========Menu===========\n"
		"==========0.Quit==========\n"
		"=========1.create=========\n"
		"==========2.show==========\n"
		"==========3.copy==========\n"
		"==========4.add===========\n"
		"=======5.substract========\n"
		"=======6.multiply=========\n"
		"=======7.calculate========\n"
		"========8.destroy=========\n"
		"=========9.clear==========\n"
		"==========10.dx===========\n"
		"===11.indefiniteIntegral==\n"
		"====12.definiteIntegral===\n"
		"==========13.gcd==========\n"
		"==========14.lcm==========\n"
		"========15.divide=========\n"
		"==========16.mod==========\n"
		"=========17.power=========\n"
		"========18.showAll========\n"
		"==========================\n";
	printf("%s",menu);
	
	int command;
	Status status;
	int m1,m2,m3,m4;
	double x,y;
	
	while ((command = inputInt(input)) != 0)
	{
		if (feof(input))
			break;
		
		switch (command)
		{
			case -1:
				printf("%s",menu);
				continue;
			case 1://创建
				printf("Input the number of polyn to create:\n");
				status = create(L[inputNum(input)],input);
				if (status != OK)
				{
					printf("Failed to create!Status:%d\n",status);
				}
				else
				{
					printf("Succeed.\n");
				}
				break;
			case 2://显示
				printf("Input the number of polyn to show:\n");
				status = print(L[inputNum(input)],output);
				if (status != OK)
				{
					printf("Failed to show!Status:%d\n",status);
				}
				break;
			case 3://复制
				printf("Input two numbers:\n");
				m1 = inputNum(input);
				m2 = inputNum(input);
				status = copy(L[m1],L[m2]);
				if (status != OK)
				{
					printf("Failed to copy!Status:%d\n",status);
				}
				else
				{
					printf("Succeed.\n");
				}
				break;
			case 4://求和
				printf("Input three numbers:\n");
				m1 = inputNum(input);
				m2 = inputNum(input);
				m3 = inputNum(input);
				status = add(L[m1], L[m2], L[m3]);
				if (status != OK)
				{
					printf("Failed to add!Status:%d\n",status);
				}
				else
				{
					printf("Succeed.\n");
				}
				break;
			case 5://求差
				printf("Input three numbers:\n");
				m1 = inputNum(input);
				m2 = inputNum(input);
				m3 = inputNum(input);
				status = substract(L[m1], L[m2], L[m3]);
				if (status != OK)
				{
					printf("Failed to substract!Status:%d\n",status);
				}
				else
				{
					printf("Succeed.\n");
				}
				break;
			case 6://求积
				printf("Input three numbers:\n");
				m1 = inputNum(input);
				m2 = inputNum(input);
				m3 = inputNum(input);
				status = multiply(L[m1], L[m2], L[m3]);
				if (status != OK)
				{
					printf("Failed to multiply!Status:%d\n",status);
				}
				else
				{
					printf("Succeed.\n");
				}
				break;
			case 7://求值
				printf("Input a number and a double:\n");
				m1 = inputNum(input);
				x = inputDouble(input);
				status = result(L[m1],x,output);
				if (status != OK)
				{
					printf("Failed to calculate!Status:%d\n",status);
				}
				break;
			case 8://销毁
				printf("Input a number:\n");
				status = destroy(L[inputNum(input)]);
				if (status != OK)
				{
					printf("Failed to destroy!Status:%d\n",status);
				}
				else
				{
					printf("Succeed.\n");
				}
				break;
			case 9://清空
				printf("Input a number:\n");
				status = clear(L[inputNum(input)]);
				if (status != OK)
				{
					printf("Failed to clear!Status:%d\n",status);
				}
				else
				{
					printf("Succeed.\n");
				}
				break;
			case 10://微分
				printf("Input two numbers:\n");
				m1 = inputNum(input);
				m2 = inputNum(input);
				status = dx(L[m1],L[m2]);
				if (status != OK)
				{
					printf("Failed to dx!Status:%d\n",status);
				}
				else
				{
					printf("Succeed.\n");
				}
				break;
			case 11://不定积分
				printf("Input two numbers:\n");
				m1 = inputNum(input);
				m2 = inputNum(input);
				status = indefiniteIntegral(L[m1],L[m2]);
				if (status != OK)
				{
					printf("Failed to calculate indefinite integral!Status:%d\n",status);
				}
				else
				{
					printf("Succeed.\n");
				}
				break;
			case 12://定积分
				printf("Input a number and two doubles:\n");
				m1 = inputNum(input);
				x = inputDouble(input);
				y = inputDouble(input);
				status = definiteIntegral(L[m1],x,y,output);
				if (status != OK)
				{
					printf("Failed to calculate definite integral!Status:%d\n",status);
				}
				break;
			case 13://最大公约式
				printf("Input three numbers:\n");
				m1 = inputNum(input);
				m2 = inputNum(input);
				m3 = inputNum(input);
				status = gcd(L[m1], L[m2], L[m3]);
				if (status != OK)
				{
					printf("Failed to gcd!Status:%d\n",status);
				}
				else
				{
					printf("Succeed.\n");
				}
				break;
			case 14://最小公倍式
				printf("Input three numbers:\n");
				m1 = inputNum(input);
				m2 = inputNum(input);
				m3 = inputNum(input);
				status = lcm(L[m1], L[m2], L[m3]);
				if (status != OK)
				{
					printf("Failed to lcm!Status:%d\n",status);
				}
				else
				{
					printf("Succeed.\n");
				}
				break;
			case 15://除法
				printf("Input three numbers:\n");
				m1 = inputNum(input);
				m2 = inputNum(input);
				m3 = inputNum(input);
				status = divide(L[m1], L[m2], L[m3]);
				if (status != OK)
				{
					printf("Failed to divide!Status:%d\n",status);
				}
				else
				{
					printf("Succeed.\n");
				}
				break;
			case 16://取余
				printf("Input three numbers:\n");
				m1 = inputNum(input);
				m2 = inputNum(input);
				m3 = inputNum(input);
				status = mod(L[m1], L[m2], L[m3]);
				if (status != OK)
				{
					printf("Failed to mod!Status:%d\n",status);
				}
				else
				{
					printf("Succeed.\n");
				}
				break;
			case 17://乘方
				printf("Input two numbers and an integer:\n");
				m1 = inputNum(input);
				m2 = inputNum(input);
				m3 = inputInt(input);
				status = fastPow(L[m1], L[m2], m3);
				if (status != OK)
				{
					printf("Failed to calculate power!Status:%d\n",status);
				}
				else
				{
					printf("Succeed.\n");
				}
				break;
			case 18://显示全部，测试
				for (int i = 0; i < MAX; i++)
				{
					printf("L[%d]:",i);
					print(L[i],stdout);
				}
				break;
			default:
				printf("Wrong command!Try again:\n");
				break;
		}
		
		printf(
			"==========================\n"
			"===========Menu===========\n"
			"========-1.showMenu=======\n"
			"==========================\n");
	}
	
	printf("==========finish==========\n");
	for (int i = 0; i < 10; i++)
		destroy(L[i]);
	if (input != stdin)
		fclose(input);
	if (output != stdout)
		fclose(output);
	
	return 0;
}

int inputNum(FILE* input) //返回输入的多项式序号，整数且在0到MAX-1之间(含)
{
	int a;
	while ((a = inputInt(input)) < 0 || a >= MAX)
	{
		printf("Invalid polyn number!Try again:\n");
		if (feof(input))
		{
			printf("Failed to input number!End of input.\n");
			return -1;
		}
	}
	return a;
}
