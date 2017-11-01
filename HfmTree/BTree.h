#include"BTNode.h"
using namespace std;
template<class T>
class BinaryTree
{
public:
	BinaryTree() { root = NULL; }
	~BinaryTree() { }
	bool IsEmpty()const;
	void Clear();
	int Size();
	bool Root(T &x)const;
	void MakeTree(const T &e, BinaryTree<T>&left, BinaryTree<T>& right);
	void PreOrder(void(*Visit)(T& x));
	void InOrder(void(*Visit)(T& x));
protected:
	BTNode<T>* root;
private:
	void Clear(BTNode<T>* t);
	int Size(BTNode<T>* t);
	void PreOrder(void(*Visit)(T& x), BTNode<T>*t);
	void InOrder(void(*Visit)(T& x), BTNode<T>*t);
};
template<class T>
int BinaryTree<T>::Size()
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
void Visit(T& x)
{
	cout << x << "  ";
}

template <class T>
bool BinaryTree<T>::Root(T &x)const
{
	if (root) {
		x = root->element; return true;
	}
	else return false;
}
template <class T>
void BinaryTree<T>::MakeTree(const T &x, BinaryTree<T>&left, BinaryTree<T>& right)
{
	if (root || &left == &right) return;
	root = new BTNode<T>(x, left.root, right.root);
	if ((left.root != NULL) && (right.root != NULL))
		left.root->parent = right.root->parent = root;
	left.root = right.root = NULL;
}
template <class T>
void BinaryTree<T>::PreOrder(void(*Visit)(T& x))
{
	PreOrder(Visit, root);
}

template<class T>
void BinaryTree<T>::PreOrder(void(*Visit)(T& x), BTNode<T>* t)
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
void BinaryTree<T>::Clear()
{
	Clear(root);
}
template <class T>
void BinaryTree<T>::Clear(BTNode<T> *x)
{
	if (!x) return;
	if (!(x->lChild) && !(x->rChild))
	{
		delete x;
		x = NULL;
		return;
	}
	else
	{
		Clear(x->lChild);
		Clear(x->rChild);
		delete x;
		x = NULL;
		return;
	}
}
