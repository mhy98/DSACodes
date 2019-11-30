#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/**
 *初始化多项式头结点
 *@param L:要初始化的多项式
 *@return 状态码
 */
Status init(PolynList &L)
{
	if (L == NULL)
	{
		L = (PolynList)malloc(sizeof(Polyn));
		if (!L) return OVERFLOW; //银行装不下更多的钱了
		L->next = NULL;
		return OK;
	}
	else
	{
		return clear(L);//本来我很富，只因为扶了个老奶奶
	}
}

/**
 *获取输入整型数据
 *@param input:输入流
 *@return 获取的值
 */
int inputInt(FILE *input)
{
	int a;
	while ((fscanf(input,"%d",&a)) <= 0) //此处fscanf输入成功时应有返回值1
	{
		printf("Input error!Please input an integer:\n");
		fscanf(input,"%*s"); //跳过非法输入
		
		if (feof(input))
		{
			printf("Failed to input!End of input.\n");
			break;
		}
	}
	
	return a;
}

/**
 *获取输入双精度浮点型
 *@param input:输入流
 *@return 获取的值
 */
double inputDouble(FILE *input)
{
	double a;
	while ((fscanf(input,"%lf",&a)) <= 0)
	{
		printf("Input error!Please input double:\n");
		fscanf(input,"%*s"); //跳过非法输入
		
		if (feof(input))
		{
			printf("Failed to input!End of input.\n");
			break;
		}
	}
	
	return a;
}

/**
 *将一个多项式项添加到一个多项式中
 *@param L:原多项式
 *@param polyn:要添加的项
 *@return 状态码
 */
Status addPolyn(PolynList L,Polyn* polyn)
{
	if (L == NULL)
		return ERROR;//请问您哪位？
	if (fabs(polyn->coeff) < 1e-8)
		return OK;
	
	Polyn *p = L;
	
	while (p->next && polyn->index < p->next->index)
		p = p->next; //这笔钱应该归在旅游花费里
	
	if (!p->next) //旅游花费是最后一位
	{
		p->next = polyn;
		polyn->next = NULL;
	}
	else if (p->next->index == polyn->index) //已经有了旅游花费项
	{
		p->next->coeff += polyn->coeff;
		free(polyn); //扔掉多余的钱包
		if (fabs(p->next->coeff) < 1e-8) //旅游花费为0了？
		{
			Polyn *q = p->next;
			p->next = q->next;
			free(q);
		}
	}
	else
	{
		polyn->next = p->next;
		p->next = polyn;
	}
	return OK;
}

/**
 *创建一个多项式项
 *@param index:多项式的指数
 *@param coeff:多项式系数
 *@return 创建的多项式项
 */
Polyn* newPolyn(int index,double coeff)
{
	Polyn* p = (Polyn*)malloc(sizeof(Polyn));
	p->index = index;
	p->coeff = coeff;
	p->next = NULL;
	return p;
}

//具体实现，清除
Status clear(PolynList &L)
{
	if (L == NULL)
		return ERROR;//我不认识你
	
	Polyn *p = L->next;
	Polyn *q;
	
	while (p)
	{
		q = p;
		p = p->next;
		free(q);
	}
	L->next = NULL;
	return OK;
}

//具体实现，创建
Status create(PolynList &L,FILE *input)
{
	Status status = init(L);//一切从0开始
	if (status != OK)
		return status;
	
	int index;
	double coeff;
	
	printf("Input coeff and index:\n");
	coeff = inputDouble(input);
	index = inputInt(input);
	
	while (index || fabs(coeff) > 1e-8) //只要你给我，我就一直要
	{
		if (fabs(coeff) > 1e-8) //我不是那么随便的人
		{
			status = addPolyn(L,newPolyn(index,coeff));
			if (status != OK)
				return status;
		}
		
		printf("Input coeff and index:\n");
		
		coeff = inputDouble(input);
		index = inputInt(input);
	}
	
	return OK;
}

//具体实现，显示
Status print(PolynList L,FILE *output)
{
	if (L == NULL) //神秘人
	{
		fprintf(output,"NULL\n");
		return OK;
	}
	
	if (L->next == NULL) //穷光蛋
	{
		fprintf(output,"0.0000\n");
		return OK;
	}
	
	int num = 0; //数一数多少个钱包
	
	Polyn *p = L;
	while (p->next)
	{
		p = p->next;
		num++;
		
		if (num == 1) //第一项，次数最大的项，不输出+号
		{
			if (p->index == 0) //常数项，不加x
				fprintf(output,"%.4lf",p->coeff);
			else if (p->index == 1) //一次项，不加次方
				fprintf(output,"%.4lfx",p->coeff);
			else 
				fprintf(output,"%.4lfx^%d",p->coeff,p->index);
		}
		else
		{
			if (p->index == 0)
				fprintf(output,"%+.4lf",p->coeff);
			else if (p->index == 1)
				fprintf(output,"%+.4lfx",p->coeff);
			else
				fprintf(output,"%+.4lfx^%d",p->coeff,p->index);
		}
	}
	fprintf(output,"\n");
	return OK;
}

//具体实现，复制
Status copy(PolynList from,PolynList &to)
{
	if (from == NULL)
		return ERROR;//我又不认识你
	
	PolynList temp = NULL;
	Status status = init(temp); //不管你是谁，到了这里都是平等的
	if (status != OK)
		return status;
	
	Polyn *p = from->next;
	
	while (p) //中间人接货
	{
		status = addPolyn(temp,newPolyn(p->index,p->coeff));
		if (status != OK)
			return status;
		
		p = p->next;
	}
	
	if (to != NULL)
		destroy(to);
	
	to = temp; //交易成功
	return OK;
}

//具体实现，加法
Status add(PolynList polyn1,PolynList polyn2,PolynList &result)
{
	if (polyn1 == NULL || polyn2 == NULL)
		return ERROR;
	
	PolynList temp = NULL;
	Status status = init(temp);
	if (status != OK)
		return status;
	
	Polyn *p = polyn1->next;
	
	while (p) //中间人接货
	{
		status = addPolyn(temp,newPolyn(p->index,p->coeff));
		if (status != OK)
			return status;
		
		p = p->next;
	}
	
	p = polyn2->next;
	
	while (p) //中间人接货
	{
		status = addPolyn(temp,newPolyn(p->index,p->coeff));
		if (status != OK)
			return status;
		
		p = p->next;
	}
	
	if (result != NULL)
		destroy(result);
	
	result = temp; //交易成功
	return OK;
}

//具体实现，减法
Status substract(PolynList polyn1,PolynList polyn2,PolynList &result)
{
	if (polyn1 == NULL || polyn2 == NULL)
		return ERROR;
	
	PolynList temp = NULL;
	Status status = init(temp);
	if (status != OK)
		return status;
	
	Polyn *p = polyn1->next;
	
	while (p) //中间人接货
	{
		status = addPolyn(temp,newPolyn(p->index,p->coeff));
		if (status != OK)
			return status;
		
		p = p->next;
	}
	
	p = polyn2->next;
	
	while (p) //中间人接货
	{
		status = addPolyn(temp,newPolyn(p->index,-p->coeff));
		if (status != OK)
			return status;
		
		p = p->next;
	}
	
	if (result != NULL)
		destroy(result);
	
	result = temp; //交易成功
	return OK;
}

//具体实现，乘法
Status multiply(PolynList polyn1,PolynList polyn2,PolynList &result)
{
	if (polyn1 == NULL || polyn2 == NULL)
		return ERROR;
	
	PolynList temp = NULL;
	Status status = init(temp);
	if (status != OK)
		return status;
	
	Polyn *p = polyn1->next;
	Polyn *q;
	
	while (p) //中间人接货
	{
		q = polyn2->next;
		while (q)
		{
			status = addPolyn(temp,newPolyn(p->index + q->index,p->coeff * q->coeff));
			if (status != OK)
				return status;
			
			q = q->next;
		}
		p = p->next;
	}
	
	p = polyn2->next;
	
	if (result != NULL)
		destroy(result);
	
	result = temp; //交易成功
	return OK;
}

//具体实现，求值
Status result(PolynList L,double x,FILE *output)
{
	if (L == NULL) return ERROR;
	if (L->next == NULL)
	{
		fprintf(output,"0.0000\n");
		return OK;
	}
	
	double result = 0;
	Polyn* p = L->next;
	while (p)
	{
		result += p->coeff * pow(x,p->index);
		p = p->next;
	}
	
	fprintf(output,"%.4lf\n",result);
	return OK;
}

//具体实现，销毁
Status destroy(PolynList &L)
{
	if (L == NULL)
		return OK; //收钱不办事
	
	Polyn *p = L;
	Polyn *q;
	
	while (p)
	{
		q = p;
		p = p->next;
		free(q);
	}
	
	L = NULL;
	return OK;
}

//具体实现，求导
Status dx(PolynList from,PolynList &to)
{
	if (from == NULL)
		return ERROR;//我又不认识你
	
	PolynList temp = NULL;
	Status status = init(temp); //不管你是谁，到了这里都是平等的
	if (status != OK)
		return status;
	
	Polyn *p = from->next;
	
	while (p && p->index > 0) //中间人接货
	{
		status = addPolyn(temp,newPolyn(p->index - 1,p->coeff * p->index));
		if (status != OK)
			return status;
		
		p = p->next;
	}
	
	if (to != NULL)
		destroy(to);
	
	to = temp; //交易成功
	return OK;
}

//具体实现，不定积分
Status indefiniteIntegral(PolynList from,PolynList &to)
{
	if (from == NULL)
		return ERROR;//我又不认识你
	
	PolynList temp = NULL;
	Status status = init(temp); //不管你是谁，到了这里都是平等的
	if (status != OK)
		return status;
	
	Polyn *p = from->next;
	
	while (p) //中间人接货
	{
		status = addPolyn(temp,newPolyn(p->index + 1,p->coeff / (p->index + 1)));
		if (status != OK)
			return status;
		
		p = p->next;
	}
	
	if (to != NULL)
		destroy(to);
	
	to = temp; //交易成功
	return OK;
}

//具体实现，定积分
Status definiteIntegral(PolynList L,double lower,double upper,FILE *output)
{
	if (L == NULL)
		return ERROR;
	
	PolynList temp = NULL;
	Status status = indefiniteIntegral(L,temp);

	if (status != OK)
		return status;
	
	double result = 0;
	Polyn* p = temp->next;
	
	while (p)
	{
		result += p->coeff * (pow(upper,p->index) - pow(lower,p->index));
		p = p->next;
	}
	
	fprintf(output,"%.4lf\n",result);
	destroy(temp);
	return OK;
}

//具体实现，最大公约式
Status gcd(PolynList polyn1,PolynList polyn2,PolynList &result)
{
	if (polyn1 == NULL || polyn2 == NULL)
		return ERROR;
		
	Status status;
	if (polyn1->next == NULL || polyn2->next == NULL)
	{
		status = init(result);
		if (status != OK)
			return status;
		status = addPolyn(result,newPolyn(0,1));
		
		return status;
	}

	PolynList temp1 = NULL,temp2 = NULL,temp = NULL;
	
	status = copy(polyn1,temp1);
	if (status != OK) return status;
	status = copy(polyn2,temp2);
	if (status != OK) return status;
	
	if (temp1->next->index < temp2->next->index) //让temp1的最高次数不低于temp2的最高次数
	{
		temp = temp1;
		temp1 =temp2;
		temp2 = temp;
	}

	while (temp2->next != NULL) //辗转相除
	{
		status = mod(temp1,temp2,temp1);
		if (status != OK) return status;
		temp = temp1;
		temp1 = temp2;
		temp2 = temp;
	}
	
	if (result != NULL)
	{
		status = destroy(result);
		if (status != OK) return status;
	}
	
	result = temp1;
	
	double coeff = result->next->coeff;
	
	if (fabs(coeff - 1) > 1e-8) //归一化
	{
		Polyn *p = result->next;
		while (p)
		{
			p->coeff /= coeff;
			p = p->next;
		}
	}
	status = destroy(temp2);
	return status;
}

//具体实现，最小公倍式
Status lcm(PolynList polyn1,PolynList polyn2,PolynList &result)
{
	if (polyn1 == NULL || polyn2 == NULL)
		return ERROR;
	PolynList temp = NULL;
	Status status = gcd(polyn1,polyn2,temp);//求最大公约式
	if (status != OK) return status;
	status = divide(polyn1,temp,temp);//ab = (a,b)[a,b]
	if (status != OK) return status;
	status = multiply(temp,polyn2,result);
	if (status != OK) return status;

	double coeff = result->next->coeff;
	if (fabs(coeff - 1) > 1e-8) //归一化
	{
		Polyn *p = result->next;
		while (p)
		{
			p->coeff /= coeff;
			p = p->next;
		}
	}
	status = destroy(temp);
	return status;
}

//具体实现，除法
Status divide(PolynList polyn1,PolynList polyn2,PolynList &result)
{
	if (polyn1 == NULL || polyn2 == NULL || polyn2->next == NULL)
		return ERROR;
	if (polyn1->next == NULL)
		return init(result);
	
	Status status;
	PolynList temp1 = NULL,temp2 = NULL,answer = NULL,onePolyn = NULL;
	status = init(answer);
	if (status != OK) return status;
	status = copy(polyn1,temp1);
	if (status != OK) return status;
	int index1 = temp1->next->index;
	int index2 = polyn2->next->index;
	while (index1 >= index2)//每次的运算都使得temp1的最高次数减少
	{
		status = init(onePolyn);
		if (status != OK) return status;
		
		double mul = temp1->next->coeff / polyn2->next->coeff; //两个最高次数项系数的倍数
		int deltaIndex = index1 - index2; //次数差
		status = addPolyn(onePolyn,newPolyn(deltaIndex,mul)); //temp1 - polyn2 * onePolyn使得temp1最高次数项可以消去
		if (status != OK) return status;
		status = multiply(onePolyn,polyn2,temp2);
		if (status != OK) return status;
		status = substract(temp1,temp2,temp1);
		if (status != OK) return status;
		status = add(answer,onePolyn,answer); //最终结果要加上每个循环里的onePolyn
		if (status != OK) return status;
		if (temp1->next == NULL) index1 = -1;
		else index1 = temp1->next->index;
	}
	
	status = destroy(temp1);
	if (status != OK) return status;
	status = destroy(temp2);
	if (status != OK) return status;
	status = destroy(onePolyn);
	if (status != OK) return status;
	if (result != NULL)
	{
		status = destroy(result);
		if(status != OK) return status;
	}
	
	result = answer;
	return OK;
}

//具体实现，取余
Status mod(PolynList polyn1,PolynList polyn2,PolynList &result)
{
	PolynList temp = NULL;
	Status status = divide(polyn1,polyn2,temp);//result = polyn1 - polyn1 / polyn2 * polyn2
	if (status != OK) return status;
	status = multiply(temp,polyn2,temp);
	if (status != OK) return status;
	status = substract(polyn1,temp,result);
	if (status != OK) return status;
	status = destroy(temp);
	return status;
}

//具体实现，快速幂算法求乘方
Status fastPow(PolynList base,PolynList &result,int pow)
{
	if (base == NULL)
		return ERROR;

	Status status;
	if (base->next == NULL)
	{
		if (pow == 0) return ERROR;
		status = init(result);
		return status;
	}
	
	if (pow == 0)
	{
		status = init(result);
		if (status != OK) return status;
		status = addPolyn(result,newPolyn(0,1));
		return status;
	}
	
	PolynList temp = NULL,answer = NULL;
	status = copy(base,temp);
	if (status != OK) return status;
	status = init(answer);
	if (status != OK) return status;
	status = addPolyn(answer,newPolyn(0,1));
	if (status != OK) return status;
	
	while (pow)
	{
		if (pow % 2)
		{
			status = multiply(answer,temp,answer);
			if (status != OK) return status;
		}
		pow /= 2;
		status = multiply(temp,temp,temp);
		if (status != OK) return status;
	}
	
	if (result != NULL)
	{
		status = destroy(result);
		if (status != OK) return status;
	}
	
	result = answer;
	status = destroy(temp);
	return status;
}
