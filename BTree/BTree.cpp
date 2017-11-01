#include"BTree.h"
#include "stdlib.h"
int main() {
	system("color f0");
	BinaryTree<char> a, b, x, y, z, A;
	y.MakeTree('E', a, b);
	z.MakeTree('F', a, b);
	x.MakeTree('C', y, z);
	y.MakeTree('D', a, b);
	z.MakeTree('B', y, x);
	cout << "z的先序遍历：";
	z.PreOrder(Visit);
	cout << endl;
	cout << "z的中序遍历：";
	z.InOrder(Visit);
	cout << endl;
	cout << "将z复制给A" << endl;
	A.Copy(z);												//复制二叉树
	cout << "A的先序遍历：";
	A.PreOrder(Visit);
	cout << endl;
	cout << "A的中序遍历：";
	A.InOrder(Visit);
	cout << endl;
	cout << "A的层次遍历：";
	A.LevelOrder(Visit);
	cout << endl;
	cout << "A的叶子结点数为" << A.LeafNum() << endl;
	cout << "A的高度为" << A.Height() << endl;
	cout << "交换A及其所有结点的左右子树" << endl;
	A.Exchange();
	cout << "A的先序遍历：";
	A.PreOrder(Visit);
	cout << endl;
	cout << "A的中序遍历：";
	A.InOrder(Visit);
	cout << endl;
	cout << "A的层次遍历：";
	A.LevelOrder(Visit);
	cout << endl;
	return 0;
}