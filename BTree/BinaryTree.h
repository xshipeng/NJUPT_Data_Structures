//binarytree.h
#include"btnode.h"
#include"seqqueue.h"
template<class T>
class BinaryTree
{
	public:
		BinaryTree(){root=NULL;}
		~BinaryTree(){Clear();}
		void MakeTree(const T &x,BinaryTree<T> &left,BinaryTree<T> &right);
		void BreakTree(		T &x,BinaryTree<T> &left,BinaryTree<T> &right);
		void PreOrder(void (*Visit)(T &x));
		int Size();
		void Copy(BinaryTree &temp);
		int Height();
		void Exchange();
		int LeafNum();
		void Clear();
		void LevelOrder(void (*Visit)(T &x));

	protected:

		BTNode<T> *root;
	private:
		void PreOrder(void (*Visit)(T &x),BTNode<T> *t);
		int Size(BTNode *t);
		BTNode<T> * Copy(BTNode<T> * t);
		int Height(BTNode<T>* t);
		void Exchange(BTNode<T> *t);	
		int Size(BTNode<T> *t);
		int LeafNum(BTNode<T> *t);
		void Clear(BTNode<T> *x);
		//void LevelOrder (void (*Visit)(T& x),BTNode<T>* &t);
		void LevelOrder (BTNode<T>* t);
	
};
/*MakeTree*/
template<class T>
void BinaryTree<T>::MakeTree(const T &x,BinaryTree<T> &left,BinaryTree<T> &right)
{
	if(root||&left==&right) return;
	root=new BTNode<T>(x,left.root,right.root);
	left.root=right.root=NULL;
}
/*BreakTree*/
template<class T>
void BinaryTree<T>::BreakTree(T &x,BinaryTree<T> &left,BinaryTree<T> &right)
{
	if(!root||&left==&right||left.root||right.root) return;
	x=root->element;
	left.root=root->lChild;right.root=root->rChild;
	delete root;root=NULL;
}


/*PreOrder*/
template<class T>
void Visit(T &x)
{
	cout<<x<<" ";
}
template<class T>
void BinaryTree<T>::PreOrder(void (*Visit)(T &x))
{
	PreOrder(Visit,root);
}
template<class T>
void BinaryTree<T>::PreOrder(void (*Visit)(T &x),BTNode<T> *t)
{
	if(t)
	{
		Visit(t->element);
		PreOrder(Visit,t->lChild);
		PreOrder(Visit,t->rChild);
	}
}
/*Size*/
template<class T>
int BinaryTree<T>::Size()
{	
	return Size(root);
}

template<class T>
int BinaryTree<T>::Size(BTNode<T> *t)
{
	if(!t) return 0;
	
	static int num=0;
	if(t->lChild) num++;
	if(t->rChild) num++;
	Size(t->lChild);
	Size(t->rChild) ;
	return num+1;    
	
	//return Size(t->lChild)+Size(t->rChild)+1;
}

/*Copy*/
template<class T>
void  BinaryTree<T>::Copy(BinaryTree<T> &temp)
{
	 root=Copy(temp.root);
}
template
<class T>
BTNode<T> * BinaryTree<T>::Copy(BTNode<T> * t)
{
	if(!t) return NULL;
	BTNode<T> *q= new BTNode<T>(t->element);
	q->lChild=Copy(t->lChild);q->rChild=Copy(t->rChild);
	return q;
}



/*Height*/
template<class T>
int BinaryTree<T>::Height()
{
	return Height(root);
}

template<class T>
int BinaryTree<T>::Height(BTNode<T>* t)
{
	int ltemp=0;
	int rtemp=0;
	if(!t)
		return 0;
	ltemp=Height(t->lChild);
	rtemp=Height(t->rChild);
	if(ltemp++ > rtemp++)
		return ltemp;
	else
		return rtemp;
}

/*LeafNum*/
template<class T>
int BinaryTree<T>::LeafNum()
{
	return LeafNum(root);
}
template<class T>
int BinaryTree<T>::LeafNum(BTNode<T> *t)
{
	static int num=0;
	if(!t) return 0;
	if((!(t->lChild))&&(!(t->rChild))) num++;
	LeafNum(t->lChild);
	LeafNum(t->rChild);
	return num;
}

/*Exchange*/
template <class T>
void BinaryTree<T>::Exchange()
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


/*Clear*/
template<class T>
void BinaryTree<T>::Clear()
{
	Clear(root);
}
template <class T>
void BinaryTree<T>::Clear(BTNode<T> *x)

{
	if (!x) return; 
	BinaryTree<T> a,b;
	BTNode<T> *l=x->lChild,*r=x->rChild;       //指向root指向的结点的左右孩子
	BreakTree(x->element,a,b);
	Clear(l);
	Clear(r);
}

/*LevelOrder*/
template <class T>//存在小bug
void BinaryTree<T>::LevelOrder(void (*Visit)(T &x))
{
	LevelOrder(root);
}
template <class T>
void BinaryTree<T>::LevelOrder(BTNode<T> *t)
{
	SeqQueue<BTNode<T>*> Q(Size());
	if (!t)
	{
		cout<<"空树！"<<endl;
		return;
	}
	BTNode<T> * p;
	p = root;
	Q.EnQueue(p);
	Visit(p->element);
	if (p->lChild)
		Q.EnQueue(p->lChild);
	if (p->rChild)
		Q.EnQueue(p->rChild);
	while (!Q.IsEmpty())
	{
		Q.DeQueue();
		Q.Front(p);
		if (Q.GetFront() == 0)
			break;
		Visit(p->element);
		if (p->lChild)
			Q.EnQueue(p->lChild);
		if (p->rChild)
			Q.EnQueue(p->rChild);
	}
	Q.DeQueue();
	return;
}