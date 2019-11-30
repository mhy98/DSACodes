#pragma once
#include<fstream>
struct Node {
	double A;
	int K;
	struct Node* next;
	Node(double a, int k) {
		this->A = a;
		this->K = k;
		this->next = nullptr;
	}
	Node() {
		this->A = 0;
		this->K = 0;
		this->next = nullptr;
	}
};

class polynomial
{
public:
	Node* header;
	int length;
public:
	polynomial();
	~polynomial();
	void operator=(const polynomial&);
	polynomial(const polynomial&);
	void copy(const polynomial&);						//拷贝
	void append(double, int);					//将（系数，次数）节点插入多项式链表
	void print();								//打印输出
	void add(polynomial&, polynomial&);			//二目加法
	void add(polynomial&);						//一目加法
	void sub(polynomial&, polynomial&);			//二目减法
	void sub(polynomial&);						//一目减法
	void mult(polynomial&, polynomial&);		//二目乘法
	void mult(polynomial&);						//一目乘法
	double calculate(double);					//将X代入求值
	void destroy();								//主动的析构操作
	void clear();								//清空
	void differential(polynomial&);				//微分
	void integral(polynomial&);					//不定积分
	double definite_integral(double,double);	//定积分				
	void divide(polynomial&, polynomial&);		//二目除法
	void divide(polynomial&);					//一目除法
	void mod(polynomial&, polynomial&);			//二目取模
	void mod(polynomial&);						//一目取模
	void GCD(polynomial&, polynomial&);			//最大公约式
	void LCM(polynomial&, polynomial&);			//最小公倍式
	void exponentiation(polynomial&, int);		//多项式求幂，利用快速幂算法
};

