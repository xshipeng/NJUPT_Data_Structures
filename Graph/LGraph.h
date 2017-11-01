#pragma once
template<class T>   //结点类  
class ENode
{
public:
	ENode() { nextArc = NULL; }
	ENode(int vertex, T weight, ENode *next)
	{
		adjVex = vertex;
		w = weight;
		nextArc = next;
	}
	int adjVex;
	T w;
	ENode * nextArc;
};
template <class T>
class LGraph:public Graph<T>    //邻接表类  
{
public:
	LGraph(int mSize);
	~LGraph();
	ResultCode Insert(int u, int v, T&w);
	ResultCode Remove(int u, int v);
	ResultCode DFS();
	void DFS(int v, bool * visited);
	void BFS();
	void BFS(int v, bool * visited);
	void CalInDegree(int * InDegree);
	bool Exist(int u, int v)const;
protected:
	ENode<T> **a;
};
template <class T>
LGraph<T>::LGraph(int mSize)   //构造函数  
{
	n = mSize;
	e = 0;
	a = new ENode<T> *[n];
	for (int i = 0; i<n; i++)
		a[i] = NULL;
}
template <class T>
LGraph<T>::~LGraph()   //析构  
{
	ENode<T> *p, *q;
	for (int i = 0; i<n; i++)
	{
		p = a[i];
		q = p;
		while (p)
		{
			p = p->nextArc;
			delete q;
			q = p;
		}
	}
	delete[]a;
}
template <class T>
bool LGraph<T>::Exist(int u, int v)const   //判断边是否存在  
{
	if (u<0 || v<0 || u>n - 1 || v>n - 1 || u == v)
		return false;
	ENode<T>*p = a[u];
	while (p&&p->adjVex != v)
		p = p->nextArc;
	if (!p)
		return false;
	else return true;
}
template <class T>
ResultCode LGraph<T>::Insert(int u, int v, T&w)   //插入  
{
	if (u<0 || v<0 || u>n - 1 || v>n - 1 || u == v)
		return Failure;
	if (Exist(u, v))
		return Duplicate;
	ENode<T>*p = new ENode<T>(v, w, a[u]);
	a[u] = p;
	e++;
	return Success;
}
template <class T>
ResultCode LGraph<T>::Remove(int u, int v)   //删除  
{
	if (u<0 || v<0 || u>n - 1 || v>n - 1 || u == v)
		return Failure;
	ENode<T> *p = a[u], *q;
	q = NULL;
	while (p&&p->adjVex != v)
	{
		q = p;
		p = p->nextArc;
	}
	if (!p)
		return NotPresent;
	if (q)
		q->nextArc = p->nextArc;
	else
		a[u] = p->nextArc;
	delete p;
	e--;
	return Success;
}
template<class T>
void LGraph<T>::DFS()
{
	bool *visited = new bool[Graph<T>::n];
	for (int i = 0; i<Graph<T>::n; i++)
		visited[i] = false;
	for (int i = 0; i<Graph<T>::n; i++)
		//zzq
		if (!visited[i]) DFS(i, visited);
	delete[]visited;
}

template<class T>
void LGraph<T>::DFS(int v, bool *visited)
{
	visited[v] = true;
	cout << " " << v;
	//zzq
	for (ENode<T>*w = LGraph<T>::a[v]; w; w = w->nextArc)
		if (!visited[w->adjVex]) DFS(w->adjVex, visited);
}

template<class T>
void LGraph<T>::BFS()
{
	bool *visited = new bool[Graph<T>::n];
	for (int i = 0; i<LGraph<T>::n; i++)
		visited[i] = false;
	for (int i = 0; i<LGraph<T>::n; i++)
		//zzq
		if (!visited[i]) BFS(i, visited);
	delete[]visited;
}

template<class T>
void LGraph<T>::BFS(int v, bool *visited)
{
	SeqQueue<int>q(Graph<T>::Vertices());
	visited[v] = true;
	cout << " " << v;
	q.EnQueue(v);
	while (!q.IsEmpty())
	{
		//zzq
		q.Front(v); q.DeQueue();
		for (ENode<T>*w = LGraph<T>::a[v]; w; w = w->nextArc)
			if (!visited[w->adjVex]) {
				visited[w->adjVex] = true; cout << " " << w->adjVex;
				q.EnQueue(w->adjVex);
			}
	}
}

template<class T>
void LGraph<T>::CalInDegree(int *InDegree)  //计算所有顶点的入度
{
	for (int i = 0; i<Graph<T>::n; i++)
		InDegree[i] = 0;
	//zzq
	for (int i = 0; i<Graph<T>::n; i++)
		for (ENode<T>*p = LGraph<T>::a[i]; p; p = p->nextArc)
			InDegree[p->adjVex]++;
}
