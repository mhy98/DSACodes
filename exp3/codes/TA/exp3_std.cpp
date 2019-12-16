/*
 * Author: MHY-Silence
 * Date: 2019-12-16
 * Content: Expected solution of experiment 3
 */

#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <cctype>
#include <cstdlib>

struct node
{
	int data;
	node* lchild, *rchild;
};

template<class T> class queue
{
private:
	T data[50000];
	int head, tail;
public:
	queue(): head(0), tail(0){}
	void init()
	{
		head = 0;
		tail = 0;
	}
	void push(T input)
	{
		data[tail++] = input;
	}
	T front()
	{
		return data[head];
	}
	void pop()
	{
		head++;
	}
	int size()
	{
		return tail - head;
	}
};

node* Construct(char* inputStr, int &scanPos)
{
	// inputStr[scanPos] is '{'
	scanPos++;	//skip the '{'
	if (inputStr[scanPos] == '}')
	{
		scanPos++;
		return NULL;
	}
	auto subTree = new node;

	// lchild
	subTree->lchild = Construct(inputStr, scanPos);
	scanPos++;	//skip the comma
	
	// number
	subTree->data = atoi(inputStr + scanPos);
	while (isdigit(inputStr[scanPos]))
		scanPos++;
	scanPos++;	//skip the comma

	//rchild
	subTree->rchild = Construct(inputStr, scanPos);
	return subTree;
}

void PreOrder(bool comma, node* root)
{
	if (!root)
		return;
	if(comma)
		printf(",");
	printf("%d", root->data);
	PreOrder(true, root->lchild);
	PreOrder(true, root->rchild);
}

queue<node*> layer[2];
void BFS(node* root, int &maxWidth, int &maxWidthDepth, int &depth)
{
	layer[0].push(root);
	for (depth =  maxWidth = 0; layer[depth % 2].size(); depth++)
	{
		int thisLayer = depth % 2;
		int nextLayer = (depth + 1) % 2;
		if (layer[thisLayer].size() >= maxWidth)
		{
			maxWidth = layer[thisLayer].size();
			maxWidthDepth = depth;
		}
		layer[nextLayer].init();
		while (layer[thisLayer].size())
		{
			auto thisnode = layer[thisLayer].front();
			if (depth)
				printf(",");
			printf("%d", thisnode->data);
			if(thisnode->lchild)
				layer[nextLayer].push(thisnode->lchild);
			if(thisnode->rchild)
				layer[nextLayer].push(thisnode->rchild);
			layer[thisLayer].pop();
		}
	}
}

int main()
{
	auto inputStr = new char[300310];
	scanf("%s", inputStr);
	
	int scanPos = 0;
	node *biTree = Construct(inputStr, scanPos);
	
	PreOrder(false, biTree);
	printf("\n");

	int maxWidth, maxWidthDepth, depth;
	BFS(biTree, maxWidth, maxWidthDepth, depth);
	printf("\n%d\n%d\n%d", maxWidthDepth + 1, maxWidth, depth);
}
