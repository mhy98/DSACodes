/*
 * Author: MHY-Silence
 * Date: 2019-12-16
 * Content: Expected solution of experiment 4.1
 */ 

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const int MAX_SIZE = 1510;

class Graph
{
protected:
	int nodeNum;
	bool graph[MAX_SIZE][MAX_SIZE];

public:
	void input()
	{
		scanf("%d", &nodeNum);
		for (int i = 0; i < nodeNum; i++)
			for (int j = 0; j < nodeNum; j++)
				scanf("%d", &graph[i][j]);
	}
};

// 最近Java代码看得太多了，不继承一下总是不舒服
class MisakaNetwork : public Graph
{
private:
	bool isInfectSrc[MAX_SIZE];
	int infectTimes[MAX_SIZE], infectedBy[MAX_SIZE];

	void DFS(int infectSrc, int thisNode, bool* visited)
	{
		for (int i = 0; i < nodeNum; i++)
			if (graph[thisNode][i] && !visited[i] && i != thisNode)
			{
				// if the node is infected by many nodes, DFS is unnecessary.
				if (infectTimes[i] > 1||isInfectSrc[i])
					continue;
				visited[i] = true;
				infectTimes[i]++;
				infectedBy[i] = infectSrc;
				DFS(infectSrc, i, visited);
			}
	}

public:
	MisakaNetwork()
	{
		memset(isInfectSrc, 0, MAX_SIZE * sizeof(bool));
		memset(infectTimes, 0, MAX_SIZE * sizeof(int));
		memset(infectedBy, 0, MAX_SIZE * sizeof(int));
	}

	void input()
	{
		Graph::input();
		int infectNum;
		scanf("%d", &infectNum);
		for (int i = 0; i < infectNum; i++)
		{
			int tmp;
			scanf("%d", &tmp);
			isInfectSrc[tmp] = true;
		}
	}

	int calculate()
	{
		for (int i = 0; i < nodeNum; i++)
			if (isInfectSrc[i])
			{
				bool visited[MAX_SIZE];
				memset(visited, 0, MAX_SIZE * sizeof(bool));
				visited[i] = true;
				DFS(i, i, visited);
			}

		int maxSaved = 0, result = -1;
		int savedSisterNum[MAX_SIZE];
		memset(savedSisterNum, 0, MAX_SIZE * sizeof(int));

		for (int i = 0; i < nodeNum; i++)
			if (infectTimes[i] == 1)
				savedSisterNum[infectedBy[i]]++;

		for (int i = 0; i < nodeNum; i++)
			if (savedSisterNum[i] > maxSaved)
			{
				maxSaved = savedSisterNum[i];
				result = i;
			}

		return result;
	}
} network;

int main()
{
	network.input();
	printf("%d", network.calculate());
}
