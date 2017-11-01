#pragma once
#include"Graph.h"
template <class T>
class Graph    //³éÏóÀà  
{
public:
	virtual ResultCode Insert(int u, int v, T&w) = 0;
	virtual ResultCode Remove(int u, int v) = 0;
	virtual bool Exist(int u, int v)const = 0;
protected:
	int n, e;
};
