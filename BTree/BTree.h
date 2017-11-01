#include"BTNode.h"
#include"Seqqueue.h"
template<class T>
class BinaryTree
{
public:
	BinaryTree() { root = NULL; }
	~BinaryTree() { Clear(); }
	bool IsEmpty()const;
	void Clear();					//删除二叉树
	void Copy(BinaryTree &temp);	//复制二叉树
	int Height();//求二叉树的高度
	void Exchange();//交换二叉树的左右子树
	int Size(); //求树的所有节点数
	int LeafNum();//求叶子结点的数目
	void MakeTree(const T &e, BinaryTree<T>&left, BinaryTree<T>& right);
	void LevelOrder(void(*Visit)(T&x)); //层次遍历
	void PreOrder(void(*Visit)(T &x));
	void InOrder(void(*Visit)(T& x));
protected:
	BTNode<T>* root;
private:
	void Clear(BTNode<T>* t);
	BTNode<T>* Copy(BTNode<T> * t);
	int Height(BTNode<T>* t);
	void Exchange(BTNode<T> *t);
	int LeafNum(BTNode<T> *t);
	int Size(BTNode<T>* t);
	void NumOfOne(BTNode<T>* t, int & k);
	int GetHeight();
	int GetHeight(BTNode<T>* t);
	void LevelOrder(void(*Visit)(T &x), BTNode<T>* &t);
	void PreOrder(void(*Visit)(T &x), BTNode<T> *t);
	void InOrder(void(*Visit)(T& x), BTNode<T>*t);
};
template<class T>
void Visit(T &x)
{
	cout << x << " ";
}
template <class T>
void BinaryTree<T>::MakeTree(const T &x, BinaryTree<T>&left, BinaryTree<T>& right)
{
	if (root || &left == &right) return;
	root = new BTNode<T>(x, left.root, right.root);
	left.root = right.root = NULL;
}
template<class T>
void BinaryTree<T>::Clear()   //删除二叉树
{
	Clear(root);
}
template <class T>
void BinaryTree<T>::Clear(BTNode<T> *x)
{
	if (x) 
	{
		Clear(x->lChild);
		Clear(x->rChild);
		delete x;
	}
}
template<class T>
int BinaryTree<T>::Height()   //求二叉树的高度
{
	return Height(root);
}
template<class T>
int BinaryTree<T>::Height(BTNode<T>* x)
{
	int ltemp = 0;
	int rtemp = 0;
	if (!x)
		return 0;
	ltemp = Height(x->lChild);
	rtemp = Height(x->rChild);
	if (ltemp++>rtemp++)
		return ltemp;
	else
		return rtemp;
}
template <class T>
void BinaryTree<T>::Copy(BinaryTree &temp)  //复制二叉树
{
	root = Copy(temp.root);
}
template <class T>
BTNode<T>* BinaryTree<T>::Copy(BTNode<T>* t)
{
	if (!t) return NULL;
	BTNode<T>* q = new BTNode<T>(t->element);
	q->lChild = Copy(t->lChild);
	q->rChild = Copy(t->rChild);
	return q;
}
template <class T>
void BinaryTree<T>::Exchange()  //交换二叉树的左右子树
{
	Exchange(root);
}
template <class T>
void BinaryTree<T>::Exchange(BTNode<T> *t)
{
	if (!t) return;
	BTNode<T> *temp;
	temp = t->lChild;
	t->lChild = t->rChild;
	t->rChild = temp;
	Exchange(t->lChild);
	Exchange(t->rChild);
}
template<class T>
void BinaryTree<T>::LevelOrder(void(*Visit)(T &x))   //层次遍历二叉树
{
	LevelOrder(Visit, root);
}
template<class T>
void BinaryTree<T>::LevelOrder(void(*Visit)(T &x), BTNode<T>* &t)
{
	if (!t)
	{
		cout << "Empty tree!" << endl;
		return;
	}
	SeqQueue<BTNode<T>*> Q(Size() + 1);
	Q.EnQueue(t);
	while (!Q.IsEmpty())
	{
		BTNode<T>* temp;
		Q.Front(temp);
		if (temp->lChild)
			Q.EnQueue(temp->lChild);
		if (temp->rChild)
			Q.EnQueue(temp->rChild);
		Q.DeQueue();
		Visit(temp->element);
	}
}
template<class T>
void BinaryTree<T>::PreOrder(void(*Visit)(T &x))
{
	PreOrder(Visit, root);
}
template<class T>
void BinaryTree<T>::PreOrder(void(*Visit)(T &x), BTNode<T> *t)
{
	if (t)
	{
		Visit(t->element);
		PreOrder(Visit, t->lChild);
		PreOrder(Visit, t->rChild);
	}
}
template <class T>
void BinaryTree<T>::InOrder(void(*Visit)(T& x))
{
	InOrder(Visit, root);
}

template<class T>
void BinaryTree<T>::InOrder(void(*Visit)(T& x), BTNode<T>* t)
{
	if (t)
	{
		InOrder(Visit, t->lChild);
		Visit(t->element);
		InOrder(Visit, t->rChild);
	}
}
template<class T>
int BinaryTree<T>::Size()    //求二叉树所有结点的个数
{
	return Size(root);
}
template<class T>
int BinaryTree<T>::Size(BTNode<T> *t)
{
	if (!t) return 0;
	else  return Size(t->lChild) + Size(t->rChild) + 1;
}
template<class T>
int BinaryTree<T>::LeafNum()  //求二叉树的叶子结点数
{
	return LeafNum(root);
}
template<class T>
int BinaryTree<T>::LeafNum(BTNode<T> *t)
{
	if (!t) return 0;
	if (t->lChild == NULL&&t->rChild == NULL) return 1;
	else return LeafNum(t->lChild) + LeafNum(t->rChild);
}

template<class T>
void BinaryTree<T>::NumOfOne(BTNode<T>*t, int &k)    //求度为1结点的个数 (可以更改为求叶子结点或者度为2的结点个数)
{
	if (t)
	{
		if (t->lChild && !t->rChild || !t->rChild && !t->lChild) k++;
		NumOfOne(t->lChild,k);
		NumOfOne(t->rChild,k);
	}
}
template<class T>
int BinaryTree<T>::GetHeight()
{
	return GetHeight(root);
}

template<class T>
int BinaryTree<T>::GetHeight(BTNode<T> *t)  //求二叉树的高度
{
	if (!t)return 0;               //若为空节点，则返回0
	if ((!t->lChild) && (!t->rChild)) return 1; //若为叶子节点，则返回1
	int lHeight = GetHeight(t->lChild);        //获得左子树高度
	int rHeight = GetHeight(t->rChild);        //获得右子树高度
	return (lHeight>rHeight ? lHeight : rHeight) + 1; //若不是叶子节点，则返回左右子树中高度最大的高度+1
}
