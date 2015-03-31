#include "BST.h"
#include <iostream>

using namespace std;

#define BalFac(x) (stature((x)->lchild) - stature((x)->rchild))
#define AvlBalanced(x) ((-2 < BalFac(x)) && BalFac(x) < 2)

template <typename T>
class AVL : public BST<T>
{
protected:
	using BST<T>::_hot;
	using BST<T>::_root;
	using BST<T>::_size;
	void rotateLL(BinNodePosi(T) p, BinNodePosi(T) q);
	void rotateRR(BinNodePosi(T) p, BinNodePosi(T) q);
public:
	using BST<T>::search;
	virtual BinNodePosi(T) insert(const T &);
	//virtual bool remove(const T &);
	
};

template <typename T>
BinNodePosi(T) tallerChild(BinNodePosi(T) x)
{
	return (stature(x->lchild) > stature(x->rchild) ? x->lchild : x->rchild);
}

template <typename T>
void AVL<T>::rotateLL(BinNodePosi(T) p, BinNodePosi(T) q)
{
	
	q->lchild = p->rchild;
	if (p->rchild)
		p->rchild->parent = q;

	p->rchild = q;
	

	if (q->parent == NULL)
	{
		p->parent = NULL;
		this->_root = p;

		q->parent = p;
		return;
	}

	p->parent = q->parent;
	if (q->parent->lchild == q)
		q->parent->lchild = p;
	else
		q->parent->rchild = p;

	q->parent = p;
}
template <typename T>
void AVL<T>::rotateRR(BinNodePosi(T) p, BinNodePosi(T) q)
{
	
	q->rchild = p->lchild;
	if (p->lchild)
		p->lchild->parent = q;

	p->lchild = q;
	if (q->parent == NULL)
	{
		this->_root = p;
		p->parent = NULL;
		q->parent = p;
		return;
	}
	

	p->parent = q->parent;

	if (q->parent->lchild == q)
		q->parent->lchild = p;
	else
		q->parent->rchild = p;

	q->parent = p;
}

template <typename T>
BinNodePosi(T) AVL<T>::insert(const T &e)
{
	BinNodePosi(T) p = search(e);
	if (p != NULL && p->data == e)	//already exist
	{
		return p;
	}

	BinNodePosi(T) x = new BinNode<T>(e, _hot);
	if (_hot == NULL)	//empty tree
	{
		_root = x;
	}
	else	//insert as a leaf
	{
		if (e < _hot->data)
			_hot->lchild = x;
		else
			_hot->rchild = x;
	}
	++_size;
	this->updateHeightAbove(x);

	p = x;
	while (p != NULL && AvlBalanced(p))
	{
		p = p->parent;
	}
	if (p == NULL)
		return x;

	//p is unbanlced node
	BinNodePosi(T) q;
	q = tallerChild(p);
	q = tallerChild(q);

	if (p->lchild && q == p->lchild->lchild)
	{
		rotateLL(q->parent, p);
	}
	else if (p->rchild && q == p->rchild->rchild)
	{
		rotateRR(q->parent, p);
	}
	else if (p->lchild && q == p->lchild->rchild)
	{
		rotateRR(q, q->parent);
		this->updateHeightAbove(q->lchild);
		rotateLL(p->lchild, p);
	}
	else
	{
		rotateLL(q, q->parent);
		this->updateHeightAbove(q->rchild);
		rotateRR(p->rchild, p);
	}

	this->updateHeightAbove(p);

	return x;
}


int main()
{
	AVL<int> b;
	b.insert(3);
	b.insert(2);
	b.insert(1);
	b.insert(4);
	b.insert(5);
	b.insert(6);
	b.insert(7);

	b.insert(16);
	b.insert(15);
	b.insert(14);
	b.insert(13);
	b.insert(12);
	b.insert(11);
	b.insert(10);
	b.insert(9);
	b.insert(8);


	b.display();
	cout << endl << endl;

	return 0;
}

