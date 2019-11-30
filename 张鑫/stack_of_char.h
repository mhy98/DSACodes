#pragma once
#include<iostream>
class stack_of_char {
public:
	int top;
	int capacity;
	char* elem;
	stack_of_char();
	~stack_of_char();
	void push(char x);
	bool pop(char&);
	bool gettop(char&);
	bool stackempty();
};
bool stack_of_char::stackempty() {
	return (top == -1);
}
stack_of_char::stack_of_char() {
	top = -1;
	capacity = 100;
	elem = new char[capacity];
}
stack_of_char::~stack_of_char() {
	delete[] elem;
}
void stack_of_char::push(char x) {
	if (top == capacity - 1) {
		std::cout << "stack is full" << std::endl;
		return;
	}
	elem[++top] = x;
}
bool stack_of_char::pop(char& c) {
	if (top == -1) {
		std::cout << "no element for poping" << std::endl;
		return false;
	}
	c = elem[top];
	top--;
	return true;
}
bool stack_of_char::gettop(char& c) {
	if (top == -1) {
		std::cout << "no element for poping" << std::endl;
		return false;
	}
	c = elem[top];
	return true;
}