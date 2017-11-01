#pragma once
#include"Graph.h"
template <class T>  
class MGraph:public Graph<T>    //邻接矩阵类  
{  
public:  
    MGraph(int mSize,const T& noedg);  
    ~MGraph();  
    ResultCode Insert(int u,int v,T&w);  
    ResultCode Remove(int u,int v);  
    bool Exist(int u,int v)const;  
    void DFS();  
    void BFS();  
protected:  
    T **a;  
    T noEdge;  
    void DFS(int v,bool *visited);  
    void BFS(int v,bool *visited);  
};  
template <class T>  
MGraph<T>::MGraph(int mSize,const T&noedg)  //构造函数  
{  
    n=mSize;  
    e=0;  
    noEdge=noedg;  
    a=new T*[n];  
    for(int i=0;i<n;i++)  
    {  
        a[i]=new T[n];  
        for(int j=0;j<n;j++)  
            a[i][j]=noEdge;  
        a[i][i]=0;  
    }  
}  
template <class T>  
MGraph<T>::~MGraph()   //析构函数  
{  
    for(int i=0;i<n;i++)  
        delete []a[i];  
    delete []a;  
}  
template <class T>  
ResultCode MGraph<T>::Insert(int u,int v,T&w)    //插入函数  
{  
    if(u<0||v<0||u>n-1||v>n-1||u==v)  
        return Failure;  
    if(a[u][v]!=noEdge)  
        return Duplicate;  
    a[u][v]=w;  
    e++;  
    return Success;  
}  
template <class T>  
ResultCode MGraph<T>::Remove(int u,int v)    //删除函数  
{  
    if(u<0||v<0||u>n-1||v>n-1||u==v)  
        return Failure;  
    if(a[u][v]==noEdge)  
        return NotPresent;  
    a[u][v]=noEdge;  
    e--;  
    return Success;  
}  
template<class T>  
bool MGraph<T>::Exist(int u,int v)const    //判断边是否存在  
{  
    if(u<0||v<0||u>n-1||v>n-1||u==v||a[u][v]==noEdge)  
        return false;  
    return true;  
}  
template <class T>  
void MGraph<T>::DFS()   //深度遍历  
{  
    bool *visited=new bool[n];  
    for (int i=0;i<n;i++)  
        visited[i]=false;  
    for(i=0;i<n;i++)  
        if(!visited[i])  
            DFS(i,visited);  
    delete[]visited;  
}   
template <class T>  
void MGraph<T>::DFS(int v,bool *visited)  
{  
    visited[v]=true;  
    cout<<" "<<v;  
    for(int i=0;i<n;i++)  
        if(a[v][i]!=noEdge&&a[v][i]!=0&&!visited[i])  
            DFS(i,visited);  
}  
template <class T>  
void MGraph<T>::BFS()   //广度遍历  
{  
    bool *visited=new bool[n];  
    for (int i=0;i<n;i++)  
        visited[i]=false;  
    for(i=0;i<n;i++)  
        if(!visited[i])  
            BFS(i,visited);  
    delete[]visited;  
}  
template <class T>  
void MGraph<T>::BFS(int v,bool *visited)  
{  
    SeqQueue<int> q(n);  
    visited[v]=true;  
    cout<<" "<<v;  
    q.EnQueue(v);  
    while(!q.IsEmpty())  
    {  
        q.Front(v);  
        q.DeQueue();  
        for(int i=0;i<n;i++)  
            if(a[v][i]!=noEdge&&a[v][i]!=0&&!visited[i])  
            {  
                visited[i]=true;  
                cout<<" "<<i;  
               q.EnQueue(i);  
            }  
    }  
}  
