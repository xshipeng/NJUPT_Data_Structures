#include<iostream> 
#include<string> 
#include<sstream>
#include<fstream>
#include"HfmTree.h"
#include "stdlib.h"
using namespace std;
int *weightArray;
string s;
string *codeArray;
HfmTree<int> p;
void Input(HfmTree<int>& p)
{
	cout << "请输入需要编码的字符组成的字符串: ";
	cin >> s;
	weightArray = new int[s.length()];
	codeArray = new string[s.length()];
	for (int i = 0; i < s.length(); i++) {
		cout << "请输入第" << (i + 1) << "个字符的权值：" << endl;
		cin >> weightArray[i];
	}
	p = CreateHfmTree(weightArray, s.length());
}
void Encode() {
	if (codeArray == NULL) {
		cout << "尚未编码！" << endl;
		return;
	}
	string encodeString;
	ofstream foutt("D://textfile.txt");
	if (!foutt)
	{
		cout << "不能打开 textfile.txt!" << endl;
		return;
	}
	ofstream foutc("D://codefile.txt");
	if (!foutc)
	{
		cout << "不能打开 codefile.txt!" << endl;
		return;
	}
	cout << "请输入需要编码的字符串: ";
	cin >> encodeString;
	foutt << encodeString;
	cout << "\n经过编码的码值为：";
	for (int i = 0; i < encodeString.length(); i++)
		for (int j = 0; j < s.length(); j++)
			if (s[j] == encodeString[i])						//查找字符所对应的哈夫曼编码并输出
			{
				cout << codeArray[j];
				foutc << codeArray[j];
				break;
			}
	foutt.close();
	foutc.close();
	cout << endl;
}
/*打印文件*/
void Print()
{
	char c;
	ifstream foutt("D://textfile.txt");
	if (!foutt)
	{
		cout << "不能打开 textfile.txt!" << endl;
		return;
	}
	cout << endl << "----------------------textfile.txt----------------------" << endl;
	while (!foutt.eof())
	{
		foutt >> c;
		cout << c;
		c = ' ';       //因为eof()函数在文件读取结束时还会多一次0，所以如果不把c置空会导致文件最后一个字符多输出一次
	}
	cout << endl << "--------------------------------------------------------" << endl;
	foutt.close();
	ifstream foutc("D://codefile.txt");
	if (!foutc)
	{
		cout << "不能打开 codefile.txt!" << endl;
		return;
	}
	cout << endl << "----------------------codefile.txt----------------------" << endl;
	while (!foutc.eof())
	{
		foutc >> c;
		cout << c;
		c = ' ';		 //因为eof()函数在文件读取结束时还会多一次0，所以如果不把c置空会导致文件最后一个字符多输出一次
	}
	cout << endl << "--------------------------------------------------------" << endl;
	foutc.close();
	ifstream foutr("D://result.txt");
	if (!foutr)
	{
		cout << "不能打开 result.txt!" << endl;
		return;
	}
	cout << endl << "----------------------result.txt------------------------" << endl;
	while (!foutr.eof())
	{
		foutr >> c;
		cout << c;
		c = ' ';		 //因为eof()函数在文件读取结束时还会多一次0，所以如果不把c置空会导致文件最后一个字符多输出一次
	}
	cout << endl << "--------------------------------------------------------" << endl;
	foutr.close();
}
int Findchar(int x)			//根据权值查找对应的字符
{
	for (int i = 0; i < s.length(); i++)
		if (x == weightArray[i])
			return i;
}
void main()
{
	system("color f0");
	bool flag = true;
	while (flag) {
		cout << "请输入命令所对应的字符：" << endl;
		cout << "---------------------B——建树--------------------------" << endl;
		cout << "---------------------T——遍历--------------------------" << endl;
		cout << "---------------------E——生成编码----------------------" << endl;
		cout << "---------------------C——编码--------------------------" << endl;
		cout << "---------------------D——译码--------------------------" << endl;
		cout << "---------------------P——打印--------------------------" << endl;
		cout << "---------------------X——退出--------------------------" << endl;
		char c;
		cin >> c;
		cout << endl;
		switch (c) {
		case 'B':
			Input(p);
			break;
		case 'T':
			if (p != NULL) {
				cout << "前序遍历：";
				p.PreOrder(Visit);
				cout << endl;
				cout << "中序遍历：";
				p.InOrder(Visit);
				cout << endl;
			}
			else cout << "尚未建树！" << endl;
			cout << endl;
			break;
		case 'E':
			p.CreateCode();
			cout << endl;
			break;
		case 'C':
			Encode();
			cout << endl;
			break;
		case 'D':
			p.Decode();
			cout << endl;
			break;
		case 'P':
			Print();
			cout << endl;
			break;
		case 'X':
			flag = false;
			break;
		}
	}
}
