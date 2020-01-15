#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAXSIZE 4096
#define TOMB 123456 //墓碑
typedef struct
{
	unsigned int *table;
} hashtable;
int success = 0, successSearchTimes = 0, fail = 0, failSearchTimes = 0;
void init(hashtable &HT)
{
	HT.table = (unsigned int *)malloc(sizeof(unsigned int) * MAXSIZE);
}
int Hash(unsigned int elem)
{
	return (((unsigned long long int)pow(elem, 2) << 26) >> 52);
}
void insert(hashtable &HT, unsigned int x)
{
	int hashCode = Hash(x), searchTime = 0;
	while (1)
	{
		searchTime++;
		if (HT.table[hashCode] == 0 || HT.table[hashCode] == TOMB)
		{
			HT.table[hashCode] = x;
			break;
		}
		else if (x % 2 == 0)
				hashCode = (hashCode + (x + 1) % maxsize) % maxsize;
		else if (x % 2 != 0)
				hashCode = (hashCode + x % maxsize) % maxsize;
	}
	printf("%d %d\n", searchTime, hashCode);
}
void search(hashtable &HT, unsigned int x)
{
	int hashCode, searchTime = 0;
	hashCode = Hash(x);
	while (1)
	{
		searchTime++;
		if (HT.table[hashCode] == 0)
		{
			printf("%d %d\n", searchTime, -1);
			fail++;
			failSearchTimes += searchTime;
			break;
		}
		if (HT.table[hashCode] == x)
		{
			printf("%d %d\n", searchTime, hashCode);
			success++;
			successSearchTimes += searchTime;
			HT.table[hashCode] = TOMB;
			break;
		}
		if (HT.table[hashCode] != 0 && HT.table[hashCode] != x)
		{
			if (x % 2 == 0)
				hashCode = (hashCode + (x + 1) % maxsize) % maxsize;
			if (x % 2 != 0)
				hashCode = (hashCode + x % maxsize) % maxsize;
		}
	}
}

int main()
{
	hashtable HT;
	init(HT);
	int operation;
	unsigned int key;
	for (int k = 0; k < maxsize; k++)
		HT.table[k] = 0;
	for (int k = 0; k < 10000; k++)
	{
		scanf("%u %d", &key, &operation);
		if (operation)
			insert(HT, key);
		else
			search(HT, key);
	}
	printf("%d/%d\n", successSearchTimes, success);
	printf("%d/%d", failSearchTimes, fail);
}