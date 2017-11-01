#include "linearlist.h"
using namespace std;
template <class T>
class SeqList:public LinearList<T>
{ 
	public:
    SeqList(int mSize);
    ~SeqList() { delete [] elements; }
    bool IsEmpty() const;
    int Length() const;
    bool Find(int i,T& x) const;
    int Search(T x) const;
    bool Insert(int i,T x);
    bool Delete(int i);
    bool Update(int i,T x);
    void Output(ostream& out)const;
	void Reverse();
	bool DeleteX(const T& x); 
	int n;
  private:
    int maxLength;  	//顺序表的最大长度
    T *elements;   	 //动态一维数组的指针
};

template <class T>
SeqList<T>::SeqList(int mSize)
{ 
    maxLength=mSize;
    elements=new T[maxLength];                            //动态分配顺序表的存储空间
    n=0;
}
template <class T>
bool SeqList<T>::IsEmpty() const
{ 
return n==0;
}
template <class T>
int SeqList<T>::Length() const
{ 
return n;
}
template<class T>
bool SeqList<T>::Find(int i,T& x) const
{ 
if (i<0 || i>n-1){                               //对i进行越界检查
		   cout<<"Out of Bounds"<<endl; return false;
    }
    x=elements[i];                                     //通过引用参数x返回下标为i的元素
    return true;
}
template<class T>
int SeqList<T>::Search(T x) const
{ 
	     for(int j=0;j<n;j++)
         if (elements[j]==x) return j;                 //从头开始搜索值为x的元素
   return -1;
}
template<class T>
bool SeqList<T>::Insert(int i,T x)
{  
if (i<-1 || i>n-1) { 
		    cout<<"Out Of Bounds"<<endl; return false;
     }
     if (n== maxLength){                                 //上溢出检查
		    cout<<"OverFlow"<<endl; return false;
     }
     for (int j=n-1;j>i;j--) elements[j+1]=elements[j];  //从后往前逐个后移元素
	     elements[i+1]=x;                                 //将x插入下标为i的元素后面
     n++; return true;
}
template <class T>
bool SeqList<T>::Delete(int i)
{ 
    if (!n) {                                            //下溢出检查
		    cout<<"UnderFlow"<<endl; return false;
    }
    if (i<0 || i>n-1) {	
		    cout<<"Out Of Bounds"<<endl; return false;
    }
    for (int j=i+1;j<n;j++) elements[j-1]=elements[j];    //从前往后逐个前移元素
    n--; return true;
}
template <class T>
bool SeqList<T>::Update(int i,T x)
{ 
    if (i<0 || i>n-1) { 
        cout<<"Out Of Bounds"<<endl; return false;
    }
    elements[i]=x;                                        //将下标为i的元素值修改为x
    return true;
}
template <class T>
void SeqList<T>::Output(ostream& out)const
{
    for (int i=0; i<n; i++) out<<elements[i]<<" ";
	    out<<endl;
}

template<class T>
void SeqList<T>::Reverse()
{
	T e;			//申明变量e，用于存放临时变量
	for (int i=1;i<=n/2;i++)    //数组从下标为零到下标【n/2】遍历
		{
		e=elements[i-1];
		elements[i-1]=elements[n-i];
		elements[n-i]=e;	//借助临时变量e完成下标为i-1和n-i元素的互换
	}
}

template<class T>
bool SeqList<T>::DeleteX(const T& x)
{
	bool flag=false; 		//定义bool型元素用于记录是否删除元素x成功
	for(int i=0;i<n;i++)
	{                           //遍历数组
		if(x==elements[i])
		{         //如果数组某一个元素值与函数的输入参数值相等，则删除元素
			Delete(i);
			flag=true;
			i--;                  //不遗漏遍历，时间复杂度为O(n)
		}
	}
	return flag;
}
