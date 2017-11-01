enum ResultCode { Underflow, Duplicate, Failure, Success, NotPresent };
#include<iostream>
#include"Seqqueue.h"
#include"MGraph.h"
#include"LGraph.h"
#include<stdlib.h>
using namespace std;
const int INFTY = 2147483640;
int main()      //主函数  
{
	system("color f0");
	int n, g;
	cout << "请输入元素的个数: ";
	cin >> n;
	MGraph<int>A(n, INFTY);
	LGraph<int>B(n);
	cout << "请输入边的条数: ";
	cin >> g;
	int *a = new int[g];
	int *b = new int[g];
	int *w = new int[g];
	for (int i = 0; i<g; i++)
	{
		cout << "请输入边及权值: ";
		cin >> a[i] >> b[i] >> w[i];
		while (A.Insert(a[i], b[i], w[i]) == Duplicate)
		{
			cout << "已存在该边！" << endl << "请输入边及权值:" ;
			cin >> a[i] >> b[i] >> w[i];
		}
			B.Insert(a[i], b[i], w[i]);
			cout << "插入成功！"<<endl;
	}
	cout << "该图的深度优先遍历为:" << endl;
	A.DFS();
	cout << endl;
	cout << "该图的广度优先遍历为:" << endl;
	A.BFS();
	cout << endl;
	cout << "请输入要搜索的边: ";
	int c, d;
	cin >> c >> d;
	if (A.Exist(c, d))
		cout << "邻接矩阵中该边存在!" << endl;
	else
		cout << "邻接矩阵中该边不存在!" << endl;
	if (B.Exist(c, d))
		cout << "邻接表中该边存在!" << endl;
	else
		cout << "邻接表中该边不存在!" << endl;
	cout << "请输入要删除的边: ";
	int e, f;
	cin >> e >> f;
	if (A.Remove(e, f) == Success)
		cout << "邻接矩阵中删除该边成功!" << endl;
	else if (A.Remove(e, f) == NotPresent)
		cout << "邻接矩阵中该边不存在!" << endl;
	else
		cout << "输入错误!" << endl;
	if (B.Remove(e, f) == Success)
		cout << "邻接表中删除该边成功!" << endl;
	else if (B.Remove(e, f) == NotPresent)
		cout << "邻接表中该边不存在!" << endl;
	else
		cout << "邻接表中输入错误!" << endl;
	cout << "删除该边后该图的深度优先遍历为:" << endl;
	A.DFS();
	cout << endl;
	cout << "删除该边后该图的广度优先遍历为:" << endl;
	A.BFS();
	cout << endl;
	return 0;
}
