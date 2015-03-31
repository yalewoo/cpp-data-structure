#ifndef MY_AVL_H
#define MY_AVL_H

#include "BST.h"

#define BalFac(x) (stature((x)->lchild) - stature((x)->rchild))
#define AvlBalanced(x) ((-2 < BalFac(x)) && BalFac(x) < 2)

template <typename T>
class AVL : public BST<T>
{
protected:
	using BST<T>::removeAt;
	using BST<T>::_hot;
	using BST<T>::_root;
	using BST<T>::_size;
	void rotateLL(BinNodePosi(T) p, BinNodePosi(T) q);
	void rotateRR(BinNodePosi(T) p, BinNodePosi(T) q);
	void insertFixUp(BinNodePosi(T) p);	//By rotate
	void insertFixUp2(BinNodePosi(T) p);	//By connect34
	void connect34(BinNodePosi(T) t1, BinNodePosi(T) t2, BinNodePosi(T) t3, BinNodePosi(T) st1, BinNodePosi(T) st2, BinNodePosi(T) st3, BinNodePosi(T) st4);
public:
	using BST<T>::search;
	virtual BinNodePosi(T) insert(const T &);
	virtual bool remove(const T &);

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
	insertFixUp2(p);

	return x;
}

template <typename T>
void AVL<T>::insertFixUp(BinNodePosi(T) p)
{
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
}

template <typename T>
void AVL<T>::insertFixUp2(BinNodePosi(T) p)
{
	BinNodePosi(T) q;
	BinNodePosi(T) mid;
	mid = tallerChild(p);
	q = tallerChild(mid);

	BinNodePosi(T) par = p->parent;

	
		
	BinNodePosi(T) t1;	
	BinNodePosi(T) t2;	
	BinNodePosi(T) t3;	
	BinNodePosi(T) st1;	
	BinNodePosi(T) st2;	
	BinNodePosi(T) st3;	
	BinNodePosi(T) st4;	

	if (p->lchild && q == p->lchild->lchild)
	{
		t1 = q;
		t2 = q->parent;
		t3 = p;
		st1 = q->lchild;
		st2 = q->rchild;
		st3 = mid->rchild;
		st4 = p->rchild;
	}
	else if (p->rchild && q == p->rchild->rchild)
	{
		t1 = p;
		t2 = mid;
		t3 = q;
		st1 = p->lchild;
		st2 = mid->lchild;
		st3 = q->lchild;
		st4 = q->rchild;
	}
	else if (p->lchild && q == p->lchild->rchild)
	{
		t1 = mid;
		t2 = q;
		t3 = p;
		st1 = mid->lchild;
		st2 = q->lchild;
		st3 = q->rchild;
		st4 = p->rchild;
	}
	else
	{
		t1 = p;
		t2 = q;
		t3 = mid;
		st1 = p->lchild;
		st2 = q->lchild;
		st3 = q->rchild;
		st4 = mid->rchild;
	}

	if (p->parent)
	{
		if (p == p->parent->lchild)
			p->parent->lchild = t2;
		else
			p->parent->rchild = t2;
	}
	else
		_root = t2;
	t2->parent = par;

	connect34(t1, t2, t3, st1, st2, st3, st4);
}
template <typename T>
void AVL<T>::connect34(BinNodePosi(T) t1, BinNodePosi(T) t2, BinNodePosi(T) t3, BinNodePosi(T) st1, BinNodePosi(T) st2, BinNodePosi(T) st3, BinNodePosi(T) st4)
{
	t1->lchild = st1; if (st1) st1->parent = t1;
	t1->rchild = st2; if (st2) st2->parent = t1;
	t3->lchild = st3; if (st3) st3->parent = t3;
	t3->rchild = st4; if (st4) st4->parent = t3;
	t2->lchild = t1; t1->parent = t2;
	t2->rchild = t3; t3->parent = t2;

	this->updateHeightAbove(t1);
	this->updateHeightAbove(t3);
}


template <typename T>
bool AVL<T>::remove(const T & e)
{
	BinNodePosi(T) x = search(e);
	if (!x) return false;

	removeAt(x);

	BinNodePosi(T) p = _hot;
	BinNodePosi(T) q;
	while (p != NULL)
	{
		q = p;
		p = p->parent;
		if (!AvlBalanced(q))
		{
			insertFixUp2(q);
		}
	}

	return true;
}


#endif