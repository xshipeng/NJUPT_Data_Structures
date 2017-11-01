#include<iostream.h> 
class Term
{  
public:
     Term(int c,int e);
     Term(int c,int e,Term* nxt);
     Term* InsertAfter(int c,int e);            //在this指针指示的结点后插入新结点
 private:
     int coef;
     int exp;
     Term *link;
	  friend ostream & operator<<(ostream &,const Term &); //重载"<<"，输出多项式的一项
     friend class Polynominal;
};    
class Polynominal
{
public:
	Polynominal();
	~Polynominal();
	void AddTerms(istream& in);
	void OutPut(ostream& out) const;
	void PolyAdd(Polynominal& r);
	void PolyMul(Polynominal& r);
private:
	Term* theList;
	friend ostream& operator<<(ostream& out,const Polynominal& r);
	friend istream& operator>>(istream& in,Polynominal& r);
	friend Polynominal& operator+(Polynominal& a,Polynominal& b);
	friend Polynominal& operator*(Polynominal& a,Polynominal& b);
};
Term::Term(int c,int e):coef(c),exp(e)
{
link=0;
}
Term::Term(int c,int e,Term *nxt):coef(c),exp(e)
{
link=nxt;
}
Term* Term::InsertAfter(int c,int e)
{	                                     //为新项申请结点的存储单元，并用Term函数将
link=new Term(c,e,link);              //c,e和this->link的值填入新结点的相应域 
return link;
}
ostream &operator <<(ostream & out, const Term& val)   
{ //重载"<<"，输出多项式的一项，用coef X^exp表示coef Xexp
      if(val.coef==0) return out;  
	   out<<val.coef;
      switch(val.exp){  
case 0:break;
          case 1:out<<"X"; break;
          default:out<<"X^"<<val.exp; break;
	   }
	   return out;
}


Polynominal::Polynominal()                           //创建多项式的空的单循环链表
{  
	theList=new Term(0,-1);	                     //分配表头结点的存储单元
	theList->link=theList;                           //构成循环链表
}
Polynominal::~Polynominal()                           //撤消多项式的单循环链表
{
	Term* p=theList->link;
	while(p!=theList){
	theList->link=p->link;                        //删除p结点
 	 delete p;                                     //释放p之存储空间
 	 p=theList->link;                              //p指向下1个待删除结点
	}
	delete theList;                                    //释放表头结点的存储单元
}

void Polynominal:: AddTerms(istream & in)         //按降幂输入各项，构造单循环链表
{
  Term* q=theList;
  int c,e;
  for(;;){ 	  
	   cout<<"Input a term(coef,exp):\n"<<endl;
      cin>>c>>e;
	     if (e<0) break;                          //当输入的指数小于0时，构造过程结束
      q=q->InsertAfter(c,e);                   //将c,e插入表尾结点q之后
  }
}
void Polynominal:: OutPut(ostream& out)const
{
   int first=1;  Term *p=theList->link;
   cout<<"The polynominal is:\n"<<endl;
   for ( ; p!=theList ; p=p->link){
      if (!first && (p->coef>0)) out<<"+";      //在非第一项的正系数前输出+号
first=0;                                       
      out<<*p;                                  //调用Term类上重载的"<<"操作
   }
   cout<<"\n"<<endl;
}

void Polynominal::PolyAdd(Polynominal& r)     
{											//将多项式r加到多项式this上
     Term* q,*q1=theList,*p;                 //q1指向表头结点
	p=r.theList->link;                       //p指向第一个要处理的结点
     q=q1->link;                           //q1是q的前驱，p和q就指向两个当前进行比较的项
     while (p->exp>=0){                       //对r的单循环链表遍历,直到全部结点都处理完  
        while (p->exp<q->exp){                //跳过q->exp大的项
         q1=q;  q=q->link;	           
}
	   if (p->exp==q->exp) {                    //当指数相等时，系数相加
		  q->coef=q->coef+p->coef;
		  if (q->coef==0){                   //若相加后系数为0，则删除q
                q1->link=q->link; delete(q);
                q=q1->link;                    //重置q指针
		  }
		  else {
			   q1=q; q=q->link;             //若相加后系数不为0，则移动q1和q
		  }
	   }
	   else{                                   //p->exp>q->exp的情况 
          q1=q1->InsertAfter(p->coef,p->exp);   //以p的系数和指数生成新结点，插入q1
        }
        p=p->link;
    }
}

void Polynominal::PolyMul(Polynominal& r)
{											//将多项式r与多项式this相乘 
	Polynominal result;						//声明result的多项式类用于存储相乘后的结果 
	Term *p=theList,*q;						//p指向表头节点 
    p=p->link;								//p指向this的第一个节点 
    for(;p->exp>=0;p=p->link)				//用p指针对this进行遍历	
    {
        q=r.theList;						//q指向待相乘的r多项式的表头节点 
        q=q->link;							//q指向r的第一个节点 
        Polynominal temp;					//声明temp多项式类用于储存中间多项式 
        Term* t=temp.theList;
        for(;q->exp>=0;q=q->link)			//对r多项式进行遍历 
        {
            t=t->InsertAfter(p->coef*q->coef,p->exp+q->exp);//将r和this的某一项相乘存入temp 
        }
        result.PolyAdd(temp);				//将temp加到result结果多项式中 
    }
    cout<<result;							//打印结果多项式 
}
ostream& operator<<(ostream &out,const Polynominal &r)
{
	r.OutPut(out);
	return out;
}

istream& operator>>(istream &in,Polynominal &r)
{
	r.AddTerms(in);
	return in;
}

Polynominal& operator+(Polynominal &a,Polynominal &b)
{
	a.PolyAdd(b);
	return a;
}

Polynominal& operator*(Polynominal &a,Polynominal &b)
{
	a.PolyMul(b);
	return a;
}
