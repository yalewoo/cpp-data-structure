#ifndef RBTREE_H
#define RBTREE_H

#include "BST.h"


#define IsBlack(x) ( (x) == 0 || (x)->color == BLACK )
#define IsRed(x) ( !IsBlack(x) )


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
	using BST<T>::removeAt;

	void solveDoubleRed(BinNodePosi(T) x);
	void solveDoubleBlack(BinNodePosi(T) r);

	void rotateLL(BinNodePosi(T) t1, BinNodePosi(T) t2);
	void rotateRR(BinNodePosi(T) t2, BinNodePosi(T) t1);

	virtual int updateHeight(BinNodePosi(T) x);
};


//更新某结点的黑高度
template <typename T>
int RBT<T>::updateHeight(BinNodePosi(T) x)
{
	if (!x)
		return -1;
	x->height = max(stature(x->lchild), stature(x->rchild));
	if (x->color == BLACK)
		++x->height;
	return x->height;
}

template <typename T>
RBT<T>::RBT()
{
	_hot = 0;
	_size = 0;
}

template <typename T>
BinNodePosi(T) RBT<T>::insert(const T & e)
{
	BinNodePosi(T) p = search(e);
	if (p != NULL && p->data == e)	//already exist
	{
		return p;
	}

	BinNodePosi(T) x = BST<T>::insert(e);
	p = x->parent;

	//新插入结点是根节点时
	if (p == 0)
	{
		x->color = BLACK;
		x->height = 1;
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

	//++_size;
	return x;


}

template <typename T>
void RBT<T>::solveDoubleRed(BinNodePosi(T) x)
{
	BinNodePosi(T) p = x->parent;
	BinNodePosi(T) g = p->parent;

	BinNodePosi(T) u = siblingOf(p);
	
	if (IsBlack(u))	//情况2.1 p红u黑
	{
		BinNodePosi(T) par = g->parent;
		enum {ROOT, LEFT, RIGHT} ptoc;
		if (g->parent)
		{
			if (g == g->parent->lchild)
				ptoc = LEFT;
			else
				ptoc = RIGHT;
		}
		else
			ptoc = ROOT;


		BinNodePosi(T) t1;
		BinNodePosi(T) t2;
		BinNodePosi(T) t3;
		BinNodePosi(T) st1;
		BinNodePosi(T) st2;
		BinNodePosi(T) st3;
		BinNodePosi(T) st4;

		if (g->lchild && x == g->lchild->lchild)
		{
			t1 = x;
			t2 = p;
			t3 = g;
			st1 = x->lchild;
			st2 = x->rchild;
			st3 = p->rchild;
			st4 = g->rchild;
		}
		else if (g->lchild && x == g->lchild->rchild)
		{
			t1 = p;
			t2 = x;
			t3 = g;
			st1 = p->lchild;
			st2 = x->lchild;
			st3 = x->rchild;
			st4 = g->rchild;
		}
		else if (g->rchild && x == g->rchild->lchild)
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

		t2->parent = par;
		switch (ptoc)
		{
			case ROOT : _root = t2; break;
			case LEFT : par->lchild = t2; break;
			case RIGHT : par->rchild = t2; break;
		}

		connect34(t1, t2, t3, st1, st2, st3, st4);

		

		t2->color = BLACK;
		t1->color = RED;
		t3->color = RED;

		t2->height++;
		t3->height--;

	}
	else	//情况2.2 p红u红
	{
		p->color = BLACK;
		u->color = BLACK;
		g->color = RED;

		p->height++;
		g->height--;

		if (g->parent == 0)
			g->color = BLACK;
		else if (IsRed(g->parent))
			solveDoubleRed(g);
	}

}

template <typename T>
bool RBT<T>::remove(const T & e)
{
	//如果已存在则返回false
	BinNodePosi(T) x = search(e);
	if (!x) return false;

	//左右孩子都存在时，与中序后继交换元素 保证删除时有一个孩子为空
	if (x->lchild && x->rchild)
	{
		BinNodePosi(T) p = x->succ();
		T tmp = x->data;
		x->data = p->data;
		p->data = tmp;

		x = p;
	}

	BinNodePosi(T) r = removeAt(x);

	//如果删除后变为空树 直接返回
	if ((_size) == 0)
		return true;
	//如果删除的是根节点重新将根节点染黑 并更新高度
	if (_hot == 0)
	{
		_root->color = BLACK;
		updateHeight(_root);
		return true;
	}

	//x和r有一个为红
	if (IsRed(x) || IsRed(r))
	{
		if (IsRed(r))
			r->color = BLACK;

		return true;
	}
	else
	{
		solveDoubleBlack(r);
	}


	delete x;

	return true;
}

template <typename T>
void RBT<T>::solveDoubleBlack(BinNodePosi(T) r)
{
	BinNodePosi(T) p = r ? r->parent : _hot;
	if (p == 0) return;
	BinNodePosi(T) s = ( r == p->lchild ? p->rchild : p->lchild );

	if (IsBlack(s))
	{
		if ( IsRed(s->lchild) || IsRed(s->rchild) )	//情况1 s为黑 t为红
		{	
			BinNodePosi(T) t;
			if (IsRed(s->rchild)) t = s->rchild;
			if (IsRed(s->lchild)) t = s->lchild;

			BinNodePosi(T) g = p;
			BinNodePosi(T) p1 = s;
			BinNodePosi(T) x = t;

			BinNodePosi(T) par = g->parent;
			enum {ROOT, LEFT, RIGHT} ptoc;
			if (g->parent)
			{
				if (g == g->parent->lchild)
					ptoc = LEFT;
				else
					ptoc = RIGHT;
			}
			else
				ptoc = ROOT;


			BinNodePosi(T) t1;
			BinNodePosi(T) t2;
			BinNodePosi(T) t3;
			BinNodePosi(T) st1;
			BinNodePosi(T) st2;
			BinNodePosi(T) st3;
			BinNodePosi(T) st4;

			if (g->lchild && x == g->lchild->lchild)
			{
				t1 = x;
				t2 = p1;
				t3 = g;
				st1 = x->lchild;
				st2 = x->rchild;
				st3 = p1->rchild;
				st4 = g->rchild;
			}
			else if (g->lchild && x == g->lchild->rchild)
			{
				t1 = p1;
				t2 = x;
				t3 = g;
				st1 = p1->lchild;
				st2 = x->lchild;
				st3 = x->rchild;
				st4 = g->rchild;
			}
			else if (g->rchild && x == g->rchild->lchild)
			{
				t1 = g;
				t2 = x;
				t3 = p1;
				st1 = g->lchild;
				st2 = x->lchild;
				st3 = x->rchild;
				st4 = p1->rchild;
			}
			else
			{
				t1 = g;
				t2 = p1;
				t3 = x;
				st1 = g->lchild;
				st2 = p1->lchild;
				st3 = x->lchild;
				st4 = x->rchild;
			}

			t2->parent = par;
			switch (ptoc)
			{
				case ROOT : _root = t2; break;
				case LEFT : par->lchild = t2; break;
				case RIGHT : par->rchild = t2; break;
			}

			connect34(t1, t2, t3, st1, st2, st3, st4);

			t2->color = g->color;
			t1->color = BLACK;
			t3->color = BLACK;

		}
		else	//情况2 s为黑 s的两个孩子为黑
		{
			s->color = RED;
			--s->height;

			if (IsRed(p))	//情况2.1 s为黑 s的两个孩子均为黑 p为红
			{
				p->color = BLACK;
			}
			else	//s为黑 s的两个孩子均为黑 p为黑
			{
				p->height--;
				solveDoubleBlack(p);
			}
		}
	}
	else	//情况3 s为红
	{
		if (s == p->lchild)
		{
			rotateLL(s, p);
		}
		else
		{
			rotateRR(s, p);
		}
		s->color = BLACK;
		p->color = RED;

		solveDoubleBlack(r);
	}
	


}


template <typename T>
void RBT<T>::rotateLL(BinNodePosi(T) t1, BinNodePosi(T) t2)
{
	//t2 --> st2
	t2->lchild = t1->rchild;

	//st2 --> t1
	if (t1->rchild)
		t1->rchild->parent = t2;

	//t1 --> t2
	t1->rchild = t2;

	//父节点 --> t1（树根情况）
	if (t2->parent == NULL)
	{
		t1->parent = NULL;
		this->_root = t1;

		t2->parent = t1;
		return;
	}

	//t1 --> 父节点
	t1->parent = t2->parent;

	//父节点 --> t1（非树根）
	if (t2->parent->lchild == t2)
		t2->parent->lchild = t1;
	else
		t2->parent->rchild = t1;

	//t2 --> t1
	t2->parent = t1;
}
template <typename T>
void RBT<T>::rotateRR(BinNodePosi(T) t2, BinNodePosi(T) t1)
{
	//t1 --> st2
	t1->rchild = t2->lchild;

	//st2 --> t1
	if (t2->lchild)
		t2->lchild->parent = t1;

	//t2 --> t1
	t2->lchild = t1;

	//父节点 --> t2（树根）
	if (t1->parent == NULL)
	{
		this->_root = t2;
		t2->parent = NULL;
		t1->parent = t2;
		return;
	}

	//t2 --> 父节点
	t2->parent = t1->parent;

	//父节点 --> t2（非树根）
	if (t1->parent->lchild == t1)
		t1->parent->lchild = t2;
	else
		t1->parent->rchild = t2;

	//t1 --> t2
	t1->parent = t2;
}


#endif