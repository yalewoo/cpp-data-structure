#ifndef RBTREE_H
#define RBTREE_H

#include "BST.h"





#define COLOR(x) (x==0 ? BLACK : x->color)

template <typename T>
class RBT : public BST<T>{
public:
	RBT();
	virtual BinNodePosi(T) insert(const T &);
	virtual bool remove(const T &);


protected:
	using BST<T>::_root;
	using BST<T>::_size;
	using BST<T>::_hot;
	using BST<T>::search;

	using BST<T>::siblingOf;
	using BST<T>::connect34;

	void solveDoubleRed(BinNodePosi(T) x);

	
};
template <typename T>
RBT<T>::RBT()
{
	_hot = 0;
	_size = 0;
}

template <typename T>
BinNodePosi(T) RBT<T>::insert(const T & e)
{
	BinNodePosi(T) x = BST<T>::insert(e);
	BinNodePosi(T) p = x->parent;

	//新插入结点是根节点时
	if (p == 0)
	{
		x->color = BLACK;
		return x;
	}

	x->color = RED;

	//若p结点是黑色 红黑树的性质没有破坏
	if (p->color == BLACK)
	{
		return x;
	}

	//若p是红色 出现双红缺陷
	solveDoubleRed(x);
	return x;


}

template <typename T>
void RBT<T>::solveDoubleRed(BinNodePosi(T) x)
{
	BinNodePosi(T) p = x->parent;
	BinNodePosi(T) g = p->parent;

	BinNodePosi(T) u = siblingOf(p);
	
	if (COLOR(u) == BLACK)
	{
		BinNodePosi(T) t1;
		BinNodePosi(T) t2;
		BinNodePosi(T) t3;
		BinNodePosi(T) st1;
		BinNodePosi(T) st2;
		BinNodePosi(T) st3;
		BinNodePosi(T) st4;

		if (x == g->lchild->lchild)
		{
			t1 = x;
			t2 = p;
			t3 = g;
			st1 = x->lchild;
			st2 = x->rchild;
			st3 = p->rchild;
			st4 = g->rchild;
		}
		else if (x == g->lchild->rchild)
		{
			t1 = p;
			t2 = x;
			t3 = g;
			st1 = p->lchild;
			st2 = x->lchild;
			st3 = x->rchild;
			st4 = g->rchild;
		}
		else if (x == g->rchild->lchild)
		{
			t1 = g;
			t2 = x;
			t3 = p;
			st1 = g->lchild;
			st2 = x->lchild;
			st3 = x->rchild;
			st4 = p->rchild;
		}
		else
		{
			t1 = g;
			t2 = p;
			t3 = x;
			st1 = g->lchild;
			st2 = p->lchild;
			st3 = x->lchild;
			st4 = x->rchild;
		}

		connect34(t1, t2, t3, st1, st2, st3, st4);

		t2->color = BLACK;
		t1->color = RED;
		t3->color = RED;
	}
	else
	{
		p->color = BLACK;
		u->color = BLACK;
		g->color = RED;

		if (COLOR(g->parent) == RED)
			solveDoubleRed(g);
	}

}

template <typename T>
bool RBT<T>::remove(const T & e)
{
	return true;
}

#endif