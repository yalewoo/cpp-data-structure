#ifndef MY_BST_H
#define MY_BST_H

#include "Bintree.h"

template <typename T>
class BST : public BinTree<T>
{
public:
	BST();
	virtual BinNodePosi(T) search(const T &);
	virtual BinNodePosi(T) insert(const T &);
	virtual bool remove(const T &);
	BinNodePosi(T) removeAt(BinNodePosi(T) x);
protected:
	using BinTree<T>::_root;
	using BinTree<T>::_size;

	BinNodePosi(T) _hot;	//parent of (x returned by search)
	void transplant(BinNodePosi(T) p, BinNodePosi(T) c);	//move single node c to p

	void connect34(BinNodePosi(T) t1, BinNodePosi(T) t2, BinNodePosi(T) t3, BinNodePosi(T) st1, BinNodePosi(T) st2, BinNodePosi(T) st3, BinNodePosi(T) st4);

};

template <typename T>
BST<T>::BST()
{
	_hot = NULL;
}
template <typename T>
BinNodePosi(T) searchIn(BinNodePosi(T) root, const T & e, BinNodePosi(T) & hot)
{
	BinNodePosi(T) x = root;
	hot = 0;
	while (x != NULL)
	{
		if (e == x->data)
			return x;

		hot = x;
		if (e < x->data)
			x = x->lchild;
		else
			x = x->rchild;
	}
	return x;
}
template <typename T>
BinNodePosi(T) BST<T>::search(const T & e)
{
	return searchIn(_root, e, _hot);
}

template <typename T>
BinNodePosi(T) BST<T>::insert(const T & e)
{
	BinNodePosi(T) p = BST<T>::search(e);
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
	return x;
}


//the called function should modify the lchild and rchild of c
//meanwhile, children node of p not changed
template <typename T>
void BST<T>::transplant(BinNodePosi(T) p, BinNodePosi(T) c)
{
	if (p == _root)
	{
		_root = c;
		if (c)
			c->parent = 0;
		return;
	}

	if (p->parent->lchild == p)
		p->parent->lchild = c;
	else
		p->parent->rchild = c;

	if (c) c->parent = p->parent;
}

//删除结点x 若有左右孩子，与中序后继交换再删 
//返回实际删除的结点的替代者指针  _hot指向删除后实际删除节点替代者的父节点
template <typename T>
BinNodePosi(T) BST<T>::removeAt(BinNodePosi(T) x)
{
	BinNodePosi(T) suc;
	if (!x->lchild)	//x has no lchild, just use rchild to replace x,including rchild==NULL
	{
		suc = x->rchild;
		_hot = x->parent;
		transplant(x, x->rchild);
	}
	//has lchild
	else if (!x->rchild)	//no rchild ,move lchild to x
	{
		suc = x->lchild;
		_hot = x->parent;
		transplant(x, x->lchild);
	}
	else	//two children
	{
		BinNodePosi(T) p = x->succ();

		
		//p has no lchild
		
		suc = p->rchild;
		_hot = p->parent;


		T tmp = x->data;
		x->data = p->data;
		p->data = tmp;

		transplant(p, p->rchild);
		
	}
	--_size;
	this->updateHeightAbove(_hot);
	return suc;
}
template <typename T>
bool BST<T>::remove(const T & e)
{
	BinNodePosi(T) x = search(e);
	if (!x) return false;

	removeAt(x);
	delete x;

	return true;
}

template <typename T>
void BST<T>::connect34(BinNodePosi(T) t1, BinNodePosi(T) t2, BinNodePosi(T) t3, BinNodePosi(T) st1, BinNodePosi(T) st2, BinNodePosi(T) st3, BinNodePosi(T) st4)
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

#endif