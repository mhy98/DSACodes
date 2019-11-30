#include "polynomial.h"
#include <cmath>
#include <iostream>
polynomial::polynomial()
{
	header = new Node;
	header->next = nullptr;
	length = 0;
}

polynomial::polynomial(const polynomial& p) {
	this->copy(p);
}
void polynomial::operator=(const polynomial& p) {
	this->copy(p);
}
polynomial::~polynomial()
{
	if (header!=nullptr)
		destroy();
}
void polynomial::clear() {		//只保留头节点
	if (header == nullptr) return;
	Node *tmp,*tmp1= header->next;
	while (tmp1 != nullptr) {
		tmp = tmp1->next;
		delete tmp1;
		tmp1 = tmp;
	}
	header->next = nullptr;
	length = 0;
}
void polynomial::destroy() {
	clear();
	delete header;
	header = nullptr;
}
void polynomial::copy(const polynomial &dst) {			
	if (this->header == dst.header || dst.header==nullptr) return;	//复制自身
	Node *end,*newnode,*tmp= dst.header->next;
	if (header != nullptr) this->clear();						//释放原先内存
	header->next = nullptr;
	end = header;
	length = 0;
	while (tmp!= nullptr) {
		newnode = new Node(tmp->A, tmp->K);
		end->next = newnode;
		end = newnode;
		tmp = tmp->next;
		length++;
	}
	end->next = nullptr;
}
void polynomial::append(double a, int k) {			//要求维护从大到小的指数顺序,删除小于误差值的节点。为了操作的方便，此类不维护为零的常数结点，在需要特殊处理的时候会特殊考虑
	if (abs(a) < 1e-8) return;						//输入极小，直接返回
	Node *tmp1 = header->next,*tmp2=header, *newnode;
	newnode = new Node(a, k);
	while (tmp1 != nullptr && tmp1->K > newnode->K) {
		tmp1 = tmp1->next;
		tmp2 = tmp2->next;
	}
	if (tmp1 == nullptr) {		//比所有的都小
		tmp2->next = newnode;
		length++;
	}
	else if (tmp1->K == newnode->K) {			//有相同节点
		tmp1->A += newnode->A;
		if (abs(tmp1->A) <= 1e-8) {			//删除节点
			tmp2->next = tmp1->next;
			delete tmp1;
			length--;
		}
	}
	else {						//无相同节点
		tmp2->next = newnode;
		newnode->next = tmp1;
		length++;
	}
}

void polynomial::print() {
	if (header == nullptr) {
		printf("NULL\n"); return;
	}
	if (length == 0||header->next==nullptr) {					//只有一个常数项0
		printf( "0.0000\n");
		return;
	}
	Node* tmp = header->next;
	bool first = true;
	while (tmp != nullptr) {
		if (tmp->A > 0)					//处理系数，系数大于零
			if (first){
				printf("%.4f", tmp->A);
				first = false;
			}
			else {
				printf( "+%.4f", tmp->A);
			}
		else{							//系数小于零
			printf("%.4f", tmp->A);
			first = false;
		}
		if (tmp->K == 1) {				//处理指数，指数等于1
			printf( "x");
		}
		else if(tmp->K!=0){
			printf("x^%d",tmp->K);
		}
		tmp = tmp->next;
	}
	printf("\n");
}
void polynomial::add(polynomial& m1, polynomial& m2) {
	if (m1.header == nullptr || m2.header == nullptr) {				//两个加项至少有一个不存在的错误
		return;
	}
	if (m1.header == this->header) {		//如果某个加项与this一样，则转变为单目运算形式的add
		this->add(m2);
		return;
	}
	if (m2.header == this->header) {		//同上
		this->add(m1);
		return;
	}
	this->clear();							//清空内存
	this->add(m1);
	this->add(m2);
}
void polynomial::add(polynomial& m1) {
	if (m1.header == this->header) {		//自己加自己，等于乘二
		Node* tmp = header->next;
		while (tmp != nullptr) {
			tmp->A += tmp->A;
			tmp = tmp->next;
		}
		return;
	}
	polynomial tmp = polynomial();
	tmp.copy(m1);
	Node* tmp1 = this->header;
	Node* tmp2 = tmp.header->next;
	while (tmp2 != nullptr) {				//把m1的项往自己表上插
		while (tmp1->next!=nullptr && tmp1->next->K > tmp2->K)
			tmp1 = tmp1->next;
		if (tmp1->next == nullptr) {		//剩余的直接插表尾
			tmp1->next = tmp2;
			tmp.header->next = nullptr;
			length += tmp.length;
			return;
		}
		if (tmp1->next->K == tmp2->K) {			//相同次数的节点
			tmp1->next->A += tmp2->A;
			if (abs(tmp1->next->A) < 1e-8) {		//如果加后的节点为零，则删之
				Node* tmp = tmp1->next;
				tmp1->next = tmp->next;
				delete tmp;
				length--;
			}
			tmp.header->next = tmp2->next;
			delete tmp2;
		}
		else {									//不相同次数的节点
			tmp.header->next = tmp2->next;
			tmp2->next = tmp1->next;
			tmp1->next = tmp2;
			length++;
		}
		tmp2 = tmp.header->next;
	}
}
void polynomial::sub(polynomial& m1, polynomial& m2){
	if (m1.header == nullptr || m2.header == nullptr) {				//两个减项至少有一个不存在的错误
		return;
	}
	if (m1.header == this->header) {		//如果某个减项与this一样，则转变为单目运算形式的sub
		this->sub(m2);
		return;
	}
	if (m2.header == this->header) {		//同上
		this->sub(m1);
		Node *tmp = header->next;
		while (tmp != nullptr) {
			tmp->A = -tmp->A;
			tmp = tmp->next;
		}
		return;
	}
	this->clear();							//清空内存
	this->add(m1);
	this->sub(m2);
}
void polynomial::sub(polynomial& m1) {
	if (m1.header == this->header) {		//自己减自己
		m1.clear();
		return;
	}
	polynomial tmp = polynomial();
	tmp.copy(m1);
	Node* nod =tmp.header->next;				//乘以-1转为加法
	while (nod != nullptr) {
		nod->A = -nod->A;
		nod = nod->next;
	}
	this->add(tmp);
}
void polynomial::mult(polynomial& m1, polynomial& m2) {
	if (m1.header == nullptr || m2.header == nullptr) {				//两个乘项至少有一个不存在的错误
		std::cout << "error:the polynomial hasn't been initialized" << std::endl;
		return;
	}
	if (m1.header == this->header) {		//如果某个乘项与this一样，则转变为单目运算形式的mult
		this->mult(m2);
		return;
	}
	if (m2.header == this->header) {		//同上
		this->mult(m1);
		return;
	}
	this->clear();							//清空内存
	this->copy(m1);
	this->mult(m2);
}
void polynomial::mult(polynomial& m1) {
	if (m1.header == this->header) {		//自己乘自己
		polynomial tmp = polynomial();
		tmp.copy(m1);
		this->mult(tmp);
		return;
	}
	polynomial tmp_poly = polynomial();
	Node* tmpm1 = m1.header->next;
	while (tmpm1 != nullptr) {
		Node* tmpm2 = this->header->next;
		while (tmpm2 != nullptr) {
			tmp_poly.append(tmpm1->A*tmpm2->A, tmpm1->K + tmpm2->K);
			tmpm2 = tmpm2->next;
		}
		tmpm1 = tmpm1->next;
	}
	this->copy(tmp_poly);
}

double polynomial::calculate(double x) {
	double result = 0;
	Node* tmp = header->next;
	while (tmp != nullptr) {
		result += tmp->A*pow(x, tmp->K);
		tmp = tmp->next;
	}
	return result;
}

void polynomial::differential(polynomial& m) {
	polynomial tmp = polynomial();
	tmp.copy(m);
	this->clear();
	Node* nod = tmp.header->next;
	while (nod != nullptr) {
		this->append(nod->A*nod->K, nod->K - 1);
		nod = nod->next;
	}
}

void polynomial::integral(polynomial& m) {
	polynomial tmp = polynomial();
	tmp.copy(m);
	this->clear();
	Node* nod = tmp.header->next;
	while (nod != nullptr) {
		this->append(nod->A / (double)(nod->K+1), nod->K + 1);
		nod = nod->next;
	}
}

double polynomial::definite_integral(double x1, double x2) {
	polynomial tmp = polynomial();
	tmp.copy(*this);
	tmp.integral(tmp);
	return tmp.calculate(x2) - tmp.calculate(x1);
}

void polynomial::divide(polynomial& m1, polynomial& m2) {
	if (m1.header == nullptr || m2.header == nullptr) {				//两个项至少有一个不存在的错误
		std::cout << "error:the polynomial hasn't been initialized" << std::endl;
		return;
	}
	if (m1.header == this->header) {		//如果某个项与this一样，则转变为单目运算形式的divide
		this->divide(m2);
		return;
	}
	if (m2.header == this->header) {		//同上
		this->divide(m1);
		return;
	}
	this->clear();							//清空内存
	this->copy(m1);
	this->divide(m2);
}

void polynomial::divide(polynomial& m) {	
	if (m.header->next == nullptr) {
		std::cout << "error:divide zero!" << std::endl;  //除数为零
		return;
	}
	if (m.header == this->header) {		//自己除自己
		this->clear();
		this->append(1, 0);
		return;
	}
	polynomial quotient = polynomial();		//quotient保存商数
	polynomial tmp_poly = polynomial();		//用于中间计算过程
	Node* tmp = header->next;
	double a1 = tmp->A;
	double a2 = m.header->next->A;
	while (tmp != nullptr && tmp->K >= m.header->next->K) {		//若被除项的系数不小于除项，则可以继续除
		double A = a1 / a2;
		int K = tmp->K - m.header->next->K;						//得到系数为A，指数为K的项
		quotient.append(A,K);
		Node* tp = m.header->next;									
		while (tp != nullptr) {									//将得到的项与除项相乘，得到中间结果
			tmp_poly.append(A*tp->A,K+tp->K);
			tp = tp->next;
		}
		this->sub(tmp_poly);									//减去中间结果
		tmp = header->next;										//更新
		if (tmp!=nullptr) a1 = tmp->A;							//更新
		tmp_poly.clear();										//更新
	}
	this->copy(quotient);
}


void polynomial::mod(polynomial& m1, polynomial& m2) {
	if (m1.header == nullptr || m2.header == nullptr) {				//两个项至少有一个不存在的错误
		std::cout << "error:the polynomial hasn't been initialized" << std::endl;
		return;
	}
	if (m1.header == this->header) {		//如果某个项与this一样，则转变为单目运算形式的mod
		this->mod(m2);
		return;
	}
	if (m2.header == this->header) {		//同上
		this->mod(m1);
		return;
	}
	this->clear();							//清空内存
	this->copy(m1);
	this->mod(m2);
}


void polynomial::mod(polynomial& m) {
	if (m.header->next == nullptr) {
		std::cout << "divide zero!" << std::endl;  //除数为零
		return;
	}
	if (m.header == this->header) {		//自己模自己
		this->clear();
		return;
	}
	polynomial tmp_poly = polynomial();		//用于中间计算过程
	Node* tmp = header->next;
	double a1 = tmp->A;
	double a2 = m.header->next->A;
	while (tmp != nullptr && tmp->K >= m.header->next->K) {		//若被除项的系数不小于除项，则可以继续除
		double A = a1 / a2;
		int K = tmp->K - m.header->next->K;						//得到系数为A，指数为K的项
		Node* tp = m.header->next;
		while (tp != nullptr) {									//将得到的项与除项相乘，得到中间结果
			tmp_poly.append(A*tp->A, K + tp->K);
			tp = tp->next;
		}
		this->sub(tmp_poly);									//减去中间结果
		tmp = header->next;										//更新
		if (tmp != nullptr) a1 = tmp->A;						//更新
		tmp_poly.clear();										//更新
	}
	//留下的this就是余项
}

void polynomial::GCD(polynomial& m1, polynomial& m2) {			//利用辗转相除法求最大公约式
	if (m1.header == nullptr || m2.header == nullptr) {				//两个项至少有一个不存在的错误
		std::cout << "error:the polynomial hasn't been initialized" << std::endl;
		return;
	}
	polynomial p1 = polynomial();
	polynomial p2 = polynomial();
	polynomial p = polynomial();
	p1.copy(m1);
	p2.copy(m2);
	p.mod(p1, p2);
	while (p.length != 0) {						//直到多项式为常数零
		p1.copy(p2);
		p2.copy(p);
		p.mod(p1, p2);
	}
	double A;									//接下来对p2进行归一化处理
	Node* tmp = p2.header->next;
	if (tmp != nullptr)
		A = tmp->A;
	while (tmp != nullptr) {
		tmp->A /= A;
		tmp = tmp->next;
	}
	this->copy(p2);
}

void polynomial::LCM(polynomial& m1, polynomial& m2) {
	if (m1.header == nullptr || m2.header == nullptr) {				//两个项至少有一个不存在的错误
		std::cout << "error:the polynomial hasn't been initialized" << std::endl;
		return;
	}
	polynomial p1 = polynomial();
	polynomial p2 = polynomial();
	polynomial p = polynomial();
	p1.copy(m1);
	p2.copy(m2);
	p.GCD(m1, m2);
	this->mult(p1, p2);
	this->divide(p);							//最小公倍式乘最大公约式等于p1*p2
	double A;									//接下来对this进行归一化处理
	Node* tmp = this->header->next;
	if (tmp != nullptr)
		A = tmp->A;
	while (tmp != nullptr) {
		tmp->A /= A;
		tmp = tmp->next;
	}
}

void polynomial::exponentiation(polynomial& m, int x) {
	polynomial tmp = polynomial();
	tmp.copy(m);
	this->clear();
	while (x > 0) {
		if (x % 2 == 1) {
			if (this->header->next == nullptr)
				this->copy(tmp);
			else this->mult(tmp);
		}
		tmp.mult(tmp);
		x = x / 2;
	}
}