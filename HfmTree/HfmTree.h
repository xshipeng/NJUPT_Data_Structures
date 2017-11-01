#include"Stack.h"
#include"BTree.h" 
#include"Prioqueue.h"
using namespace std;
template <class T>
class HfmTree :public BinaryTree<T>
{
public:
	operator T()const { return weight; }                //重载类型转换运算符 
	T getW() { return weight; }
	void putW(const T& x) { weight = x; }
	void SetNull() { root = NULL; }
	void CreateCode();
	void Decode();      //解码
private:
	T weight;
};

template <class T>
HfmTree<T> CreateHfmTree(T w[], int n)
{
	PrioQueue < HfmTree<T> > pq(n);        //定义一个元素类型为HfmTree<T>的优先权队列
	HfmTree<T> x, y, z, zero;
	for (int i = 0; i<n; i++) {
		z.MakeTree(w[i], x, y);
		z.putW(w[i]); //构造树中只有一个结点的哈夫曼树对象
		pq.Append(z);                      //将哈夫曼树对象进优先权队列
		z.SetNull();                       //将z置成空树
	}
	for (int i = 1; i<n; i++) {
		pq.Serve(x);
		pq.Serve(y);           //取出最小和次小权值哈夫曼树对象x和y
		z.MakeTree(x.getW() + y.getW(), x, y); //构造一个新哈夫曼树对象
		z.putW(x.getW() + y.getW());
		pq.Append(z);                      //新哈夫曼树对象进优先权队列
		z.SetNull();                       //将z置成空树
	}
	pq.Serve(z);                           //从队列中取出构造完毕的哈夫曼树对象
	return z;                              //返回构造完成的哈夫曼树对象
}
template<class T>
void HfmTree<T>::CreateCode()
{
	SeqStack<int> A(Size() + 1);
	BTNode<int>* t = root;
	int n = 1;
	int i = 1;
	while (n <= Size())
	{
		if (t->lChild != NULL)							//判断左孩子是否为空
		{
			A.Push(0);									//0进栈
			t = t->lChild;
			n++;
		}
		else if (t->rChild != NULL)						//判断右孩子是否为空
		{
			A.Push(1);									//1进栈
			t = t->rChild;
			n++;
		}
		else											//左右孩子都为空为叶子结点
		{
			A.Output(codeArray[Findchar(t->element)]); //输出叶子结点对应元素的二叉树编码
			i++;
			if (i>s.length()) break;
			while (t->parent->rChild == t)				//判断叶子结点是否为双亲结点的右孩子
			{
				t = t->parent;
				A.Pop();								//指针指向双亲结点，顶层元素出栈
			}
			t = t->parent->rChild;						//指针指向双亲结点的右孩子，1进栈
			A.Pop();
			A.Push(1);
			n++;
		}
	}
	for (int j = 0; j < s.length(); j++)
	{
		cout << s[j] << "的编码为" << codeArray[j] << endl;
	}
}
template <class T>
void HfmTree<T>::Decode() {
	if (codeArray == NULL) {
		cout << "尚未编码！" << endl;
		return;
	}
	ofstream foutr("D://result.txt");
	if (!foutr)
	{
		cout << "不能打开 result.txt!" << endl;
		return;
	}
	ifstream foutc("D://codefile.txt");
	if (!foutc)
	{
		cout << "不能打开 codefile.txt!" << endl;
		return;
	}
	BTNode<T>* searchNode = root;
	char c, ch;
	while (!foutc.eof())
	{
		foutc.get(ch);
		if (ch == '0')
			searchNode = searchNode->lChild;
		else if (ch == '1')
			searchNode = searchNode->rChild;
		if (searchNode->lChild == NULL && searchNode->rChild == NULL)
		{
			c = s[Findchar(searchNode->element)];
			cout << c;
			foutr << c;
			foutr.flush();
			searchNode = root;
		}
	}
	cout << endl << endl;
	foutr.close();
	foutc.close();
}

