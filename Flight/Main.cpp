enum ResultCode { Underflow, Duplicate, Failure, Success, NotPresent, OutOfBounds };
#include<iostream>
#include<string.h>  
#include<stdlib.h>
const int INF = 100000000;
#include"MGraph.h"
using namespace std;
int main()
{
	system("color f0");
	int n, m;
	cout << "请输入城市个数:";
	cin >> n;
	cout << "请输入航线条数:";
	cin >> m;
	MGraph<int>A(n, INF);
	int c, f;
	cout << "请输入每条航线的起点和终点: " << endl;
	for (int i = 0; i<m; i++)
	{
		cout << "航线" << i + 1 << ": ";
		cin >> c >> f;
		while (A.Insert(c, f, 1) == Duplicate)
		{
			cout << "重复航线！请重新输入其他航线：";
			cin >> c >> f;
		}
	}
	char s;
	do {
		int v, w;
		cout << "请输入你的起点和终点:";
		cin >> v >> w;
		while (v<0 || w<0 || w>n - 1 || v>n - 1||w==v)
		{
			cout << "输入错误!请重新输入:";
			cin >> v >> w;
		}
		int *b = new int[n];
		int *d = new int[n];
		int *path = new int[n];
		A.Dijkstra(v, d, path);
		int e = n - 1;
		for (int j = 0; j<n; j++)
			b[j] = -2;
		if (w != v)
		{
			int j = w;
			while (path[j] != -1)
			{
				b[e] = path[j];
				e--;
				j = path[j];
			}
			if (e == n - 1 || d[j] == INF)
				cout << "该路间无线路!" << endl;
			else
			{
				cout << "从" << v << "到" << w << "的换乘次数最小的线路方案为:";
				for (int k = 0; k<n; k++)
				{
					if (b[k] != -2)
						cout << b[k] << ",";
				}
				cout << w << endl;
			}
		}
		if (w == v)
			cout << "从" << v << "到" << w << "该路间无需乘飞机!" << endl;
		delete[]b;
		delete[]d;
		delete[]path;
		cout << "请问是否继续查询路线?请输入Y/N:";
		cin >> s;
		while (s != 'Y'&&s != 'y'&&s != 'n'&&s != 'N')
		{
			cout << "输入错误!请重新输入:";
			cin >> s;
		}
	} while (s == 'Y' || s == 'y');
	return 0;
}
