#pragma once
#include "polynomial.h"
class Poly_List
{
private:
	polynomial* List[10];
public:
	Poly_List();
	void Run();
	void Calculate();
	~Poly_List();
};
/*
#include "pch.h"
#include <iostream>
#define N 100
template<typename T>
class stack {
public:
	int top;
	int capacity;
	T* elem;
	stack();
	~stack();
	void push(T x);
	bool pop(T&);
	bool gettop(T&);
	bool stackempty();
};
template<typename T>
bool stack<T>::stackempty() {
	return (top == -1);
}
template<typename T>
stack<T>::stack() {
	top = -1;
	capacity = N;
	elem = new T[capacity];
}
template<typename T>
stack<T>::~stack() {
	delete[] elem;
}
template<typename T>
void stack<T>::push(T x) {
	if (top == capacity - 1) {
		std::cout << "stack is full" << std::endl;
		return;
	}
	elem[++top] = x;
}
template<typename T>
bool stack<T>::pop(T& c) {
	if (top == -1) {
		std::cout << "no element for poping" << std::endl;
		return false;
	}
	c = elem[top];
	top--;
	return true;
}
template<typename T>
bool stack<T>::gettop(T& c) {
	if (top == -1) {
		std::cout << "no element for poping" << std::endl;
		return false;
	}
	c = elem[top];
	return true;
}
bool isoperator(char c) {
	return (c == '#' || c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')');
}
int operate(int a, char c, int b) {
	switch (c) {
	case '+':return a + b;
	case '-':return a - b;
	case '*':return a * b;
	case '/':return a / b;
	}
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
using namespace std;
int main()
{
	stack<char> sop = stack<char>();
	stack<int> sval = stack<int>();
	sop.push('#');
	char s[100];
	char c, ch;
	int length = 0;
	while ((c = getchar()) != '#')
		s[length++] = c;
	s[length] = '#';
	char*p = s;
	while (!sop.stackempty()) {
		ch = *p++;
		if (!isoperator(ch)) {
			int t = ch - 48;
			while (!isoperator(*p)) {
				t = t * 10 + *p - 48;
				p++;
			}
			sval.push(t);
			continue;
		}
		switch (ch) {
		case '(':sop.push(ch); break;
		case ')':
			while ((sop.pop(c)) && c != '(') {
				int a, b;
				sval.pop(b);
				sval.pop(a);
				sval.push(operate(a, c, b));
			}
			break;
		case '#':
			while (sop.gettop(c) && preop(c, ch)) {
				int a, b;
				sval.pop(b);
				sval.pop(a);
				sop.pop(c);
				sval.push(operate(a, c, b));
			}
			sop.pop(c);
			break;
		default:
			while (sop.gettop(c) && preop(c, ch)) {
				int a, b;
				sval.pop(b);
				sval.pop(a);
				sop.pop(c);
				sval.push(operate(a, c, b));
			}
			if (ch != '#') sop.push(ch);
			break;
		}
	}
	int result;
	sval.gettop(result);
	cout << result;
	return 0;
}


*/