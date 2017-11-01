#include "Polynominal.h"
#include"stdlib.h"
int main()
{
	system("color f0");
	Polynominal p,q;
	cin>>p;	cout<<p;
	cin>>q;	cout<<q;
	cout<<"乘法运算"<<endl; 
	q*p;
	cout<<"加法运算"<<endl;   
	q=q+p; cout<<q;
	return 0;
}