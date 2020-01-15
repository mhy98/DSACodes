#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;
#define MAXN 10010
#define MAXM 400010
//position[i]:标号为i的点在堆里的下标
//idInHeap[i]:堆里下标为i的点的标号
//dat[i]:小根堆维护数值
//size:堆的大小
int used[MAXN], n, m, s, dis[MAXN];
//used 访问标记
//dis 最短路数组
struct Edge
{
    int endPoint;
    int cost;
    Edge *next;
};
struct Graph
{
    int verticeNum, edgeNum;
    Edge *firstedge[MAXN];
    Graph()
    {
        memset(firstedge, 0, sizeof(firstedge));
    }
    void addEdge(int from, int to, int val)
    {
        Edge *p = new Edge;
        p->endPoint = to;
        p->cost = val;
        p->next = firstedge[from];
        firstedge[from] = p;
    }
    void input()
    {
        scanf("%d %d", &verticeNum, &edgeNum);
        int a, b, v;
        for (int i = 1; i <= edgeNum; i++)
        {
            scanf("%d %d %d", &a, &b, &v);
            addEdge(a, b, v);
            addEdge(b, a, v);
        }
    }
};
void swapData(int &a, int &b)
{
    int t = a;
    a = b;
    b = t;
}
struct Heap
{
    int dat[MAXN], position[MAXN], idInHeap[MAXN],size;
    Heap(){
        size=0;
    }
    void up(int p)
    { //堆向上调整 只要比根小就和根交换
        while (p >> 1)
        {
            if (dat[p] < dat[p >> 1])
            { //注意交换的时候 三个值对应都要交换
                swapData(dat[p], dat[p >> 1]);
                swapData(position[idInHeap[p]], position[idInHeap[p >> 1]]);
                swapData(idInHeap[p], idInHeap[p >> 1]);
            }
            else
                break;
            p = p >> 1;
        }
    }
    void down(int p)
    {
        //堆向下调整 同课本讲的 由于元素是一个一个按顺序插入的所以不用额外建堆
        int flag;
        while ((p << 1) <= size)
        {
            if ((p << 1) == size)
                flag = p << 1;
            else
            {
                if (dat[p << 1] < dat[(p << 1) | 1])
                    flag = p << 1;
                else
                    flag = (p << 1) | 1;
            }
            if (dat[p] > dat[flag])
            {
                swapData(dat[p], dat[flag]);
                swapData(position[idInHeap[p]], position[idInHeap[flag]]);
                swapData(idInHeap[p], idInHeap[flag]);
            }
            else
                break;
            p = flag;
        }
    }
    void insert(int data, int p)
    {
        dat[++size] = data;
        idInHeap[size] = p;
        position[p] = size;
        up(size);
    }
    void pop()
    { //堆顶弹出
        dat[1] = dat[size];
        position[idInHeap[size]] = 1;
        idInHeap[1] = idInHeap[size];
        size--;
        down(1);
    }
};
Graph G;
Heap H;
int main()
{
    G.input();
    memset(dis, -1, sizeof(dis));
    dis[0] = 0;
    H.insert(0, 0);
    for (int i = 1; i <= G.verticeNum; i++)
    {
        if (!H.size)
            break;           //堆空 说明所有连通到的点处理完了
        int p = H.idInHeap[1]; //普通的dij算法遍历了一遍所有的点找最短路最小的点 其实可以用堆来进行这一步
        used[p] = 1;         //标记p用过
        H.pop();               //p弹出堆 之后不再使用
        for (Edge *j = G.firstedge[p]; j; j = j->next)
        {
            int t = j->endPoint; //遍历j连接出去点所有边
            if (used[t])
                continue;
            if (dis[t] == -1)
            {
                dis[t] = dis[p] + j->cost;
                H.insert(dis[t], t); //第一次到达了t点 那么更新p点最短路 插入堆中
            }
            else if (dis[t] > dis[p] + j->cost)
            {
                dis[t] = dis[p] + j->cost;
                H.dat[H.position[t]] = dis[t];
                H.up(H.position[t]); //如果t点的最短路更新了 变小了 那么找到t在堆里的位置 向上调整
            }
        }
    } //事实上就是找最小点的那一步换成了堆 其他都一样 复杂度从平均o(n)变成了堆上查找和维护的o(logn) 总复杂度o(nlogn)
    int maxAns = 0, maxID = 0;
    for (int i = 1; i < G.verticeNum; i++)
    {
        if (dis[i] != -1)
        {
            if (dis[i] > maxAns)
                maxAns = dis[i], maxID = i;
        }
    }
    printf("%d\n%d", maxID, maxAns);
    return 0;
}