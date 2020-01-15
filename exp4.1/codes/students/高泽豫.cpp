#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <string.h>
using std::cin;
using std::cout;
using std::endl;

#define NODE_NUM (1500 + 10)

struct Edge {
	int from;
	int to;
	Edge* next;
} edge[NODE_NUM * NODE_NUM * 2], *pt = edge, *edge_head[NODE_NUM];

void add_edge(int from, int to) {
	pt->from = from;
	pt->to = to;
	pt->next = edge_head[from];
	edge_head[from] = pt++;
}

int source[NODE_NUM];
int n, m;

char line[100000];
char* p;
int read2() {
	int x = 0, w = 1;
	char ch = 0;
	while (ch < '0' || ch > '9') {
		if (ch == '-')
			w = -1;
		ch = *p++;
	}
	while (ch >= '0' && ch <= '9') {
		x = (x << 3) + (x << 1) + (ch - '0');
		ch = *p++;
	}
	return x * w;
}
int read() {
	int x = 0, w = 1;
	char ch = 0;
	while (ch < '0' || ch > '9') {
		if (ch == '-')
			w = -1;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9') {
		x = (x << 3) + (x << 1) + (ch - '0');
		ch = getchar();
	}
	while (ch == ' ') {
		ch = getchar();
	}
	return x * w;
}
int count = 0;
bool visited[NODE_NUM];
int deleted = -1;
void dye(int x) {
	visited[x] = 1;
	count++;
	for (auto t = edge_head[x]; t; t = t->next) {
		if (t->to == deleted || visited[t->to])
			continue;
		dye(t->to);
	}
}

int main() {
	//freopen("data.in", "r", stdin);
	n = read();
	for (register int i = 0; i < n; i++) {
		fgets(line, 100000, stdin);
		p = line;
		for (register int j = 0; j < n; j++)
			if (read2() && i != j)
				add_edge(i, j);
	}
	m = read();
	fgets(line, 100000, stdin);
	p = line;
	for (register int i = 0; i < m; i++) {
		source[i] = read2();
	}
	std::sort(source, source + m);
	count = 0;
	for (int j = 0; j < m; j++) {
		if (!visited[source[j]])
			dye(source[j]);
	}
	int pre_count = count;
	int ans = pre_count;
	int loc = -1;
	for (int i = 0; i < m; i++) {
		memset(visited, 0, sizeof(visited));
		deleted = source[i];
		count = 1;
		for (int j = 0; j < m; j++) {
			int t = source[j];
			if (t == deleted || visited[t])
				continue;
			dye(t);
		}
		if (count < ans) {
			ans = count;
			loc = source[i];
		}
	}
	cout << loc;
	return 0;
}