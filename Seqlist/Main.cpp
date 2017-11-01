#include "seqlist.h"
#include "stdlib.h"
const int SIZE=10;
int  main()
{
	system("color f0");
	SeqList<int> Seq(SIZE);
	for(int i=0;i<10;i++)
		Seq.Insert(i-1,i/3);
	cout<<"逆置前的顺序表:"<<endl;
	Seq.Output(cout);
 	Seq.Reverse(); 
	cout<<"逆置后的顺序表:"<<endl;
	Seq.Output(cout);
	cout<<"输入需要删除的数:"<<endl;
	int x;
	cin>>x;
	if(Seq.DeleteX(x)==true)
	{
		cout<<"删除后的结果："<<endl;
		Seq.Output(cout);
	} 
	else
	cout<<"所删除的元素不存在"<<endl; 
    return 0;
}

