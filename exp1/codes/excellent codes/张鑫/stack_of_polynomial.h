#pragma once
#include "polynomial.h"
#include<iostream>
class stack_of_polynomial
{
public:
	int top;
	int capacity;
	polynomial* elem;
	void push(polynomial& x);
	bool pop(polynomial&);
	bool gettop(polynomial&);
	bool stackempty();
	stack_of_polynomial();
	~stack_of_polynomial();
};

stack_of_polynomial::stack_of_polynomial() {
	top = -1;
	capacity = 10;
	elem = new polynomial[capacity];
}
bool stack_of_polynomial::stackempty() {
	return (top == -1);
}
stack_of_polynomial::~stack_of_polynomial() {
	delete[] elem;
}
void stack_of_polynomial::push(polynomial& x) {
	if (top == capacity - 1) {
		std::cout << "stack is full" << std::endl;
		return;
	}
	elem[++top].copy(x);
}
bool stack_of_polynomial::pop(polynomial& c) {
	if (top == -1) {
		std::cout << "no element for poping" << std::endl;
		return false;
	}
	c.copy(elem[top]);
	top--;
	return true;
}
bool stack_of_polynomial::gettop(polynomial& c) {
	if (top == -1) {
		std::cout << "no element for poping" << std::endl;
		return false;
	}
	c.copy(elem[top]);
	return true;
}