#include <iostream>
#include "bintree.h"

using namespace std;


template <typename T> 
class Printint
{
public:
	void operator()(T e) { cout << e << " "; }
};



int main()
{
	BinTree<int> * bt1 = new BinTree<int>(new BinNode<int>(5, NULL));

	bt1->insertAsLC(bt1->root(), 2);
	bt1->insertAsRC(bt1->root(), 3);

	BinTree<int> * bt = new BinTree<int>(new BinNode<int>(9, NULL));

	bt->insertAsLC(bt->root(), 7);
	bt->insertAsRC(bt->root(), 8);

	bt->attachAsLC(bt->root()->lchild, bt1);

	Printint<int> visit;
	(bt->root())->travPre_I(visit);
	cout << endl;
	(bt->root())->travPre_II(visit);
	cout << endl;
	(bt->root())->travPre_R(visit);
	cout << endl << endl;
	(bt->root())->travIn_R(visit);
	cout << endl;
	(bt->root())->travIn_I(visit);
	cout << endl;
	
	auto x = bt->root();
	while (x->lchild != NULL)
		x = x->lchild;

	while (x != NULL)
	{
		cout << x->data << " ";
		x = x->succ();
	}
	cout << endl << endl;
	(bt->root())->travPost_R(visit);
	cout << endl;
	(bt->root())->travPost_I(visit);
	cout << endl << endl;

	(bt->root())->travLevel(visit);
	cout << endl;

	bt->display();

	return 0;
}