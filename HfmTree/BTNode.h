using namespace std;
template<class T>
struct BTNode
{
	BTNode() { lChild = rChild = NULL; }
	BTNode(const T& x)
	{
		element = x;
		lChild = rChild = NULL;
	}
	BTNode(const T& x, BTNode<T>* l, BTNode<T>* r)
	{
		element = x; lChild = l; rChild = r;
	}
	T element;
	BTNode<T>* lChild, *rChild, *parent;
};
