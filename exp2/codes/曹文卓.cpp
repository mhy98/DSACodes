#include <iostream>
#include <string.h>
#include <cmath>
using namespace std;
void errorreport()
{
	cout << "NULL" << endl;
	exit(0);
}
void string_replace(std::string &strBig, const std::string &strsrc, const std::string &strdst)
{
	std::string::size_type pos = 0;
	std::string::size_type srclen = strsrc.size();
	std::string::size_type dstlen = strdst.size();

	while ((pos = strBig.find(strsrc, pos)) != std::string::npos)
	{
		strBig.replace(pos, srclen, strdst);
		pos += dstlen;
	}
}
template <class type>
class stacknode
{
public:
	stacknode() : next(NULL) {}
	type data;
	stacknode *next;
};
template <class type>
class stack
{
private:
	unsigned int stacklength;
	stacknode<type> *node;
	stacknode<type> *headnode;

public:
	stack();
	unsigned int length();
	void push(type x);
	bool isEmpty();
	void pop();
	type top();
	void clear();
};

template <class type>
stack<type>::stack()
{
	node = NULL;
	headnode = NULL;
	stacklength = 0;
}

template <class type>
inline unsigned int stack<type>::length()
{
	return stacklength;
}
template <class type>
void stack<type>::push(type x)
{
	node = new stacknode<type>();
	node->data = x;
	node->next = headnode;
	headnode = node;
	stacklength++;
}
template <class type>
void stack<type>::pop()
{
	if (isEmpty())
		return;
	node = headnode;
	headnode = headnode->next;
	delete node;
	stacklength--;
}

template <class type>
bool stack<type>::isEmpty()
{
	return stacklength == 0;
}

template <class type>
type stack<type>::top()
{
	if (!isEmpty())
		return headnode->data;
}

template <class type>
void stack<type>::clear()
{
	while (headnode != NULL)
	{
		node = headnode;
		headnode = headnode->next;
		delete node;
	}
	node = NULL;
	headnode = NULL;
	stacklength = 0;
}
void preManage(string &str)
{
	int i = 0, size = str.size();
	int numpre = 0;
	int numpost = 0;
	for (; i < size; i++)
	{
		if (str[i] == '(')
			numpre++;
		if (str[i] == ')')
			numpost++;
	}
	if (numpre != numpost)
		errorreport();
	else
	{

		string_replace(str, "(-", "(0-");
		string_replace(str, "abs(", "0|(");
	}
}
int getPriority(char ch)
{
	if (ch == '(')
		return 1;
	else if (ch == '+' || ch == '-')
		return 4;
	else if (ch == '*' || ch == '/')
		return 3;
	else if (ch == '^')
		return 2;
	else if (ch == '|')
		return 5;
	else
		return 6;
}

void calculate(stack<int> &mystack, char operation)
{
	int num1, num2, num3 = 0;
	num2 = mystack.top();
	mystack.pop();
	num1 = mystack.top();
	mystack.pop();
	if (operation == '+')
	{
		num3 = num1 + num2;
	}
	else if (operation == '-')
	{
		num3 = num1 - num2;
	}
	else if (operation == '*')
	{
		num3 = num1 * num2;
	}
	else if (operation == '/')
	{
		if (num2 == 0)
			errorreport();
		num3 = num1 / num2;
	}
	else if (operation == '^')
	{
		if (num1 == 0 && num2 <= 0)
			errorreport();
		num3 = pow(num1, num2);
	}
	else if (operation == '|')
	{
		num3 = abs(num2);
	}
	mystack.push(num3);
}

int calculator(string str)
{
	stack<int> mystack_number;
	stack<char> mystack_operation;
	int scanPtr = 0, size = str.size();
	char tmp_operation;
	string tmp_num;
	while (scanPtr < size)
	{
		if (str[scanPtr] >= '0' && str[scanPtr] <= '9')
		{
			int j = scanPtr;
			while (j < size && str[j] >= '0' && str[j] <= '9')
				j++;
			tmp_num = str.substr(scanPtr, j - scanPtr);
			mystack_number.push(atoi(tmp_num.c_str()));
			scanPtr = j;
		}
		else if (str[scanPtr] == '+' || str[scanPtr] == '-' || str[scanPtr] == '*' || str[scanPtr] == '/' || str[scanPtr] == '^' || str[scanPtr] == '|')
		{
			if (mystack_operation.isEmpty())
				mystack_operation.push(str[scanPtr]);
			else
			{
				while (!mystack_operation.isEmpty())
				{
					tmp_operation = mystack_operation.top();
					if (getPriority(tmp_operation) >= getPriority(str[scanPtr]))
					{
						calculate(mystack_number, tmp_operation);
						mystack_operation.pop();
					}
					else
						break;
				}
				mystack_operation.push(str[scanPtr]);
			}
			scanPtr++;
		}
		else
		{
			if (str[scanPtr] == '(')
				mystack_operation.push(str[scanPtr]);
			else
			{
				while (mystack_operation.top() != '(')
				{
					tmp_operation = mystack_operation.top();
					calculate(mystack_number, tmp_operation);
					mystack_operation.pop();
				}
				mystack_operation.pop();
			}
			scanPtr++;
		}
	}
	while (!mystack_operation.isEmpty())
	{
		tmp_operation = mystack_operation.top();
		calculate(mystack_number, tmp_operation);
		mystack_operation.pop();
	}
	return mystack_number.top();
}

int main()
{
	string str;
	cin >> str;
	preManage(str);
	int num_res = calculator(str);
	cout << num_res << endl;
}