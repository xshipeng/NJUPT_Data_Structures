#pragma once
template <class T>
class Graph    //抽象类  
{
public:
	virtual ResultCode Insert(int u, int v, T w) = 0;
	virtual ResultCode Remove(int u, int v) = 0;
	virtual bool Exist(int u, int v)const = 0;
protected:
	int n, e;
};
template <class T>
class MGraph :public Graph<T>    //邻接矩阵类  
{
public:
	MGraph(int mSize, const T noedg);
	~MGraph();
	ResultCode Insert(int u, int v, T w);
	ResultCode Remove(int u, int v);
	bool Exist(int u, int v)const;
	int Choose(int *d, bool *s);
	void Dijkstra(int v, T *d, int *path);
protected:
	T **a;
	T noEdge;
};
template <class T>
MGraph<T>::MGraph(int mSize, const T noedg)
{
	n = mSize;
	e = 0;
	noEdge = noedg;
	a = new T*[n];
	for (int i = 0; i<n; i++)
	{
		a[i] = new T[n];
		for (int j = 0; j<n; j++)
			a[i][j] = noEdge;
		a[i][i] = 0;
	}
}
template <class T>
MGraph<T>::~MGraph()
{
	for (int i = 0; i<n; i++)
		delete[]a[i];
	delete[]a;
}
template <class T>
ResultCode MGraph<T>::Insert(int u, int v, T w)
{
	if (u<0 || v<0 || u>n - 1 || v>n - 1 || u == v)
		return Failure;
	if (a[u][v] != noEdge)
		return Duplicate;
	a[u][v] = w;
	e++;
	return Success;
}
template <class T>
ResultCode MGraph<T>::Remove(int u, int v)
{
	if (u<0 || v<0 || u>n - 1 || v>n - 1 || u == v)
		return Failure;
	if (a[u][v] == noEdge)
		return NotPresent;
	a[u][v] = noEdge;
	e--;
	return Success;
}
template<class T>
bool MGraph<T>::Exist(int u, int v)const
{
	if (u<0 || v<0 || u>n - 1 || v>n - 1 || u == v || a[u][v] == noEdge)
		return false;
	return true;
}
template <class T>
int MGraph<T>::Choose(int *d, bool *s)      //求最小d[i]  
{
	int i, minpos;
	T min;
	min = INF;
	minpos = -1;
	for (i = 0; i<n; i++)
		if (d[i] <= min && !s[i])
		{
			min = d[i];
			minpos = i;
		}
	return minpos;
}
template <class T>
void MGraph<T>::Dijkstra(int v, T *d, int *path)    //迪杰斯特拉算法  
{
	int i, k, w;
	if (v<0 || v>n - 1)
		throw OutOfBounds;
	bool *s = new bool[n];
	for (i = 0; i<n; i++)
	{
		s[i] = false;
		d[i] = a[v][i];
		if (i != v&&d[i]<INF)
			path[i] = v;
		else
			path[i] = -1;
	}
	s[v] = true;
	d[v] = 0;
	for (i = 1; i<n; i++)
	{
		k = Choose(d, s);
		s[k] = true;
		for (w = 0; w<n; w++)
			if (!s[w] && (d[k] + a[k][w])<d[w])
			{
				d[w] = d[k] + a[k][w];
				path[w] = k;
			}
	}
}
