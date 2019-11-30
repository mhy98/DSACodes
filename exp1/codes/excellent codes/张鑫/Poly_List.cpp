#include "Poly_List.h"
#include<iostream>
#include<fstream>
#include "stack_of_char.h"
#include "stack_of_polynomial.h"
using namespace std;
Poly_List::Poly_List()
{
	for (int i = 0; i < 10; i++)
		List[i] = nullptr;
}


Poly_List::~Poly_List()
{
	for (int i = 0; i < 10; i++)
		if (List[i] != nullptr)
			delete List[i];
}
void Poly_List::Run() {
	int w,m1,m2,m3,m,k;
	double a,x, x1, x2;
	scanf("%d",&w);
	while (w != 0) {
		switch (w) {
		case 1: 
			scanf("%d", &m);
			if (List[m] != nullptr) delete List[m];
			List[m] = new polynomial();
			scanf("%lf %d", &a,&k);
			while (abs(a) >= 1e-8 || k != 0) {
				List[m]->append(a, k);
				scanf("%lf %d", &a, &k);
			}
			break;
		case 2:
			scanf("%d", &m);
			if (List[m] == nullptr) printf("NULL\n");
			else List[m]->print();
			break;
		case 3:
			scanf("%d %d", &m1,&m2);
			if (List[m1] == nullptr) {
				printf("You cannot copy a polynomial which not exist!");
				return;
			}
			if (List[m2] == nullptr) List[m2] = new polynomial();
			List[m2]->copy(*List[m1]);
			break;
		case 4:
			scanf( "%d %d %d", &m1, &m2,&m3);
			if (List[m3] == nullptr) List[m3] = new polynomial();
			List[m3]->add(*List[m1], *List[m2]);
			break;
		case 5:
			scanf("%d %d %d", &m1, &m2, &m3);
			if (List[m3] == nullptr) List[m3] = new polynomial();
			List[m3]->sub(*List[m1], *List[m2]);
			break;
		case 6:
			scanf("%d %d %d", &m1, &m2, &m3);
			if (List[m3] == nullptr) List[m3] = new polynomial();
			List[m3]->mult(*List[m1], *List[m2]);
			break;
		case 7:
			scanf( "%d %lf", &m, &x);
			printf("%.4f\n",List[m]->calculate(x));
			break;
		case 8:
			scanf( "%d", &m);
			if (List[m] != nullptr) {
				delete List[m];
				List[m] = nullptr;
			}
			break;
		case 9:
			scanf( "%d", &m);
			List[m]->clear();
			break;
		case 10:
			scanf( "%d %d", &m1, &m2);
			if (List[m2] == nullptr) List[m2] = new polynomial();
			List[m2]->differential(*List[m1]);
			break;
		case 11:
			scanf( "%d %d", &m1, &m2);
			if (List[m2] == nullptr) List[m2] = new polynomial();
			List[m2]->integral(*List[m1]);
			break;
		case 12:
			scanf( "%d %lf %lf",&m, &x1, &x2);
			printf("%.4f\n", List[m]->definite_integral(x1, x2));
			break;
		case 13:
			scanf( "%d %d %d", &m1, &m2, &m3);
			if (List[m3] == nullptr) List[m3] = new polynomial();
			List[m3]->GCD(*List[m1], *List[m2]);
			break;
		case 14:
			scanf( "%d %d %d", &m1, &m2, &m3);
			if (List[m3] == nullptr) List[m3] = new polynomial();
			List[m3]->LCM(*List[m1], *List[m2]);
			break;
		case 15:
			scanf("%d %d %d", &m1, &m2, &m3);
			if (List[m3] == nullptr) List[m3] = new polynomial();
			List[m3]->divide(*List[m1], *List[m2]);
			break;
		case 16:
			scanf("%d %d %d", &m1, &m2, &m3);
			if (List[m3] == nullptr)List[m3] = new polynomial();
			List[m3]->mod(*List[m1], *List[m2]);
			break;
		case 17:
			scanf( "%d %d %d", &m1, &m2, &k);
			if (List[m2] == nullptr) List[m2] = new polynomial();
			List[m2]->exponentiation(*List[m1], k);
			break;
		case 18:
			Calculate();
			break;
		}
		scanf("%d", &w);
	}
}
bool isoperator(char c) {
	return (c == '#' || c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')'|| c=='%');
}
bool isdigit(char c) {
	return (c >= '0' && c <= '9');
}
bool preop(char c, char ch) {
	int a1, b1;
	if (c == '#' && ch == '#')return false;
	switch (c) {
	case '#':a1 = -1; break;
	case '(':a1 = 0; break;
	case '+':
	case '-':a1 = 1; break;
	case '*':
	case '/':a1 = 2; break;
	}
	switch (ch) {
	case '#':b1 = -1; break;
	case '(':b1 = 0; break;
	case '+':
	case '-':b1 = 1; break;
	case '*':
	case '/':b1 = 2; break;
	}
	return (a1 >= b1);
}
void Poly_List::Calculate() {	//四则运算，输入运算式，以#号结束，输出结果
	stack_of_char sop = stack_of_char();
	stack_of_polynomial sval = stack_of_polynomial();
	sop.push('#');
	char s[100];
	char c, ch;
	int length = 0;
	scanf("%s", s);
	length = strlen(s);
	s[length] = '#';
	char* p = s;
	while (!sop.stackempty()) {
		ch = *p++;
		if (isdigit(ch)) {
			int t = ch - '0';
			if (List[t]!=nullptr) sval.push(*List[t]);
			else {
				cout << "List error!" << endl;
				return;
			}
			continue;
		}
		switch (ch) {
		case '(':sop.push(ch); break;
		case ')':
			while ((sop.pop(c)) && c != '(') {
				polynomial a = polynomial(); 
				polynomial b = polynomial();
				sval.pop(b);
				sval.pop(a);
				switch (c) {
				case '+': { a.add(b); break; }
				case '-': { a.sub(b); break; }
				case '*': {a.mult(b); break; }
				case '/': {a.divide(b); break; }
				case '%': {a.mod(b); break; }
				}
				sval.push(a);
			}
			break;
		case '#':
			while (sop.gettop(c) && preop(c, ch)) {
				polynomial a = polynomial();
				polynomial b = polynomial();
				sval.pop(b);
				sval.pop(a);
				sop.pop(c);
				switch (c) {
				case '+': { a.add(b); break; }
				case '-': { a.sub(b); break; }
				case '*': {a.mult(b); break; }
				case '/': {a.divide(b); break; }
				case '%': {a.mod(b); break; }
				}
				sval.push(a);
			}
			sop.pop(c);
			break;
		case '+':
		case '-':
		case '*':
		case '/':
		case '%':
			while (sop.gettop(c) && preop(c, ch)) {
				polynomial a = polynomial();
				polynomial b = polynomial();
				sval.pop(b);
				sval.pop(a);
				sop.pop(c);
				switch (c) {
				case '+': { a.add(b); break; }
				case '-': { a.sub(b); break; }
				case '*': {a.mult(b); break; }
				case '/': {a.divide(b); break; }
				case '%': {a.mod(b); break; }
				}
				sval.push(a);
			}
			if (ch != '#') sop.push(ch);
			break;
		}
	}
	polynomial result = polynomial();
	sval.gettop(result);
	result.print();
}