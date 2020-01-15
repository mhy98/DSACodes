#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAX_EDGE_NUM 1510
using namespace std;
int index1 = 0, index2 = 0, dfsTime[MAX_EDGE_NUM], lowestTime[MAX_EDGE_NUM], n, maxans = 0, maxid = -1, tmp, upIndex1, upIndex2, root;
int save[MAX_EDGE_NUM], father[MAX_EDGE_NUM], kid[MAX_EDGE_NUM], infectedKid[MAX_EDGE_NUM];
//dfsTime[i] i号点dfs的时间序号
//index1 计时器1 dfs每遇到一个新的点就+1
//index2 计时器2 dfs每遇到一个新的感染点才+1
//lowestTime[i] i号点沿dfs搜索树能够到的最早的点的dfs时间序号
//kid[i] i号点为根的搜索树里一共有多少个点
//infectedKid[i] i号点为根点搜索树里有多少个被感染点
//save[i] 割掉i号点以后可以拯救多少个节点 不算自己
//father[i] i号点的搜索树根
struct Edge
{
	int endPoint;
	int nextEdge;
};

struct Graph
{
	// 图的大小
	int edgeNum, verticeNum, infectNum;

	// 使用静态邻接表存储图。firstedge是每个点连接的第一条边。
	int firstEdge[MAX_EDGE_NUM];

	// 边数组
	Edge edges[MAX_EDGE_NUM * 200];

	// 感染信息
	int tag[MAX_EDGE_NUM];

	Graph()
	{
		edgeNum = 0;
		verticeNum = 0;
		memset(tag, 0, sizeof(tag));
	}

	/**
	 * @brief 增加一条边
	 * @param startPoint: 边的起点
	 * @param endPoint: 边的终点
	 */
	void addEdge(int from, int to)
	{
		edgeNum++;
		edges[edgeNum].endPoint = to;
		edges[edgeNum].nextEdge = firstEdge[from];
		firstEdge[from] = edgeNum;
	}

	/**
	 * @brief 输入图
	 */
	void input()
	{
		scanf("%d", &verticeNum);
		getchar();
		for (int i = 0; i < verticeNum; i++)
		{
			char inputStr[MAX_EDGE_NUM * 2];
			char *scanPos = inputStr;

			fgets(inputStr, MAX_EDGE_NUM * 2, stdin);
			for (int j = 0; j < verticeNum; j++)
			{
				if (*scanPos == '1' && i != j)
					addEdge(i, j);
				scanPos += 2;
			}
		} //输入
	}

	void input_infect(void)
	{
		scanf("%d", &infectNum);
		for (int i = 0; i < infectNum; i++)
		{
			int infectedPoint;
			scanf("%d", &infectedPoint);
			tag[infectedPoint] = 1;
		} //tag[i]=1 表示i号点感染
	}
} G;

void tarjan(int p, Graph &G)
{
	int v, tempIndex1, tempIndex2; //用来暂存
	father[p] = root;			   //记录根节点
	kid[p] = 1;
	infectedKid[p] = G.tag[p];
	dfsTime[p] = lowestTime[p] = ++index1;
	index2 += G.tag[p];
	for (int i = G.firstEdge[p]; i; i = G.edges[i].nextEdge)
	{
		v = G.edges[i].endPoint; //遍历p点连出去的边
		if (!dfsTime[v])
		{
			tempIndex1 = index1;
			tempIndex2 = index2;
			tarjan(v, G);
			if (lowestTime[v] < lowestTime[p])
				lowestTime[p] = lowestTime[v];
			if (lowestTime[v] >= dfsTime[p])
			{ //说明v在的这一块是独立的

				if (tempIndex2 == index2)
					save[p] += index1 - tempIndex1;
				//如果搜索完这一块以后没有增加被感染的点 那么这一块会被p拯救
				kid[p] += index1 - tempIndex1;
				infectedKid[p] += index2 - tempIndex2;
				//统计p点的两个kid数量 留待后面算父块
			}
		}
		else if (dfsTime[v] < lowestTime[p])
			lowestTime[p] = dfsTime[v];
	}
}
int main()
{
	G.input();
	G.input_infect();

	for (int i = 0; i < G.verticeNum; i++)
		if (!dfsTime[i])
		{
			root = i;
			upIndex1 = index1;
			upIndex2 = index2; //用于暂存 计算搜索树根节点的两个kid数量
			tarjan(i, G);
			kid[i] = index1 - upIndex1;
			infectedKid[i] = index2 - upIndex2;
		}
	for (int i = 0; i < G.verticeNum; i++)
	{
		if (infectedKid[father[i]] == infectedKid[i])
			save[i] += kid[father[i]] - kid[i]; //计算父块的拯救节点数
		if (G.tag[i] && save[i])
		{
			if (save[i] > maxans)
				maxans = save[i], maxid = i;
			else if (save[i] == maxans && i < maxid)
				maxid = i;
		} //更新答案
	}
	printf("%d\n", maxid);
	return 0;
}