#include "BST.h"
template <typename T>
class SplayBinTree : public BST<T>
{
protected:
	using BST<T>::updateHeightAbove;
	using BST<T>::_root;
	using BST<T>::_hot;
	BinNodePosi(T) splay(BinNodePosi(T) v);

	void rotateLL(BinNodePosi(T) p, BinNodePosi(T) q);
	void rotateRR(BinNodePosi(T) p, BinNodePosi(T) q);
	void connect34(BinNodePosi(T) t1, BinNodePosi(T) t2, BinNodePosi(T) t3, BinNodePosi(T) st1, BinNodePosi(T) st2, BinNodePosi(T) st3, BinNodePosi(T) st4);
public:
	BinNodePosi(T) search(const T & e);
	BinNodePosi(T) insert(const T & e);
	bool remove(const T & e);
};

template <typename T>
BinNodePosi(T) SplayBinTree<T>::splay(BinNodePosi(T) v)
{
	BinNodePosi(T) p;
	BinNodePosi(T) mid;
	BinNodePosi(T) q;

	BinNodePosi(T) t1;	
	BinNodePosi(T) t2;	
	BinNodePosi(T) t3;	
	BinNodePosi(T) st1;	
	BinNodePosi(T) st2;	
	BinNodePosi(T) st3;	
	BinNodePosi(T) st4;	

	BinNodePosi(T) par;
	enum {ROOT, LEFT, RIGHT} ptoc;

	while ((q = v) && (mid = v->parent) && (p = v->parent->parent))
	{
		par = p->parent;

		if (par)
		{
			if (p == par->lchild)
				ptoc = LEFT;
			else
				ptoc = RIGHT;
		}
		else
			ptoc = ROOT;

		if (p->lchild && q == p->lchild->lchild)
		{
			t1 = q;
			t2 = q->parent;
			t3 = p;
			st1 = q->lchild;
			st2 = q->rchild;
			st3 = mid->rchild;
			st4 = p->rchild;

			t1->rchild = t2; t2->parent = t1;
			t2->lchild = st2; if (st2) st2->parent = t2;
			t2->rchild = t3; t3->parent = t2;
			t3->lchild = st3; if (st3) st3->parent = t3;

			switch (ptoc)
			{
				case ROOT : _root = t1; break;
				case LEFT : par->lchild = t1; break;
				case RIGHT : par->rchild = t1; break;
			}
			t1->parent = par;

			updateHeightAbove(t3);
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

			t1->rchild = st2; if (st2) st2->parent = t1;
			t2->lchild = t1; t1->parent = t2;
			t2->rchild = st3; if (st3) st3->parent = t2;
			t3->lchild = t2; t2->parent = t3;

			switch (ptoc)
			{
				case ROOT : _root = t3; break;
				case LEFT : par->lchild = t3; break;
				case RIGHT : par->rchild = t3; break;
			}
			t3->parent = par;

			updateHeightAbove(t1);
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
			
			switch (ptoc)
			{
				case ROOT : _root = t2; break;
				case LEFT : par->lchild = t2; break;
				case RIGHT : par->rchild = t2; break;
			}
			t2->parent = par;

			this->connect34(t1, t2, t3, st1, st2, st3, st4);
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
			
			switch (ptoc)
			{
				case ROOT : _root = t2; break;
				case LEFT : par->lchild = t2; break;
				case RIGHT : par->rchild = t2; break;
			}
			t2->parent = par;

			this->connect34(t1, t2, t3, st1, st2, st3, st4);
		}

	}
	if ((q = v) && (mid = v->parent) && !(p = v->parent->parent))
	{
		if (q == mid->lchild)
			this->rotateLL(q, mid);
		else
			this->rotateRR(q, mid);

		updateHeightAbove(mid);
	}

	return v;
}
template <typename T>
BinNodePosi(T) SplayBinTree<T>::search(const T & e)
{
	BinNodePosi(T) x = searchIn(_root, e, _hot);
	if (!x)
		splay(_hot);
	else
		splay(x);
	return x;
}
template <typename T>
BinNodePosi(T) SplayBinTree<T>::insert(const T & e)
{
	BinNodePosi(T) x = search(e);
	if (x)
		return x;

	BinNodePosi(T) v = new BinNode<T>(e, NULL);
	BinNodePosi(T) p = _root;
	_root = v;
	if (p && p->data < e)
	{
		p->parent = v;
		v->lchild = p;
		v->rchild = p->rchild;
		if (p->rchild) p->rchild->parent = v;
		p->rchild = 0;
	}
	else if (p)
	{
		p->parent = v;
		v->rchild = p;
		v->lchild = p->lchild;
		if (p->lchild) p->lchild->parent = v;
		p->lchild = 0;
	}
	updateHeightAbove(p);
	updateHeightAbove(v);

	return v;
}
template <typename T>
bool SplayBinTree<T>::remove(const T & e)
{
	BinNodePosi(T) v = search(e);
	if (!v)
		return false;

	BinNodePosi(T) p = v->succ();
	BinNodePosi(T) oldleft = v->lchild;

	if (v->lchild) v->lchild->parent = 0;
	if (v->rchild) v->rchild->parent = 0;
	delete v;

	if (!p)
	{
		_root = oldleft;
		return true;
	}

	splay(p);

	_root = p;
	p->parent = 0;
	p->lchild = oldleft;
	if (p->lchild) p->lchild->parent = p;

	return true;
}
template <typename T>
void SplayBinTree<T>::rotateLL(BinNodePosi(T) p, BinNodePosi(T) q)
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
void SplayBinTree<T>::rotateRR(BinNodePosi(T) p, BinNodePosi(T) q)
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
void SplayBinTree<T>::connect34(BinNodePosi(T) t1, BinNodePosi(T) t2, BinNodePosi(T) t3, BinNodePosi(T) st1, BinNodePosi(T) st2, BinNodePosi(T) st3, BinNodePosi(T) st4)
{
	t1->lchild = st1; if (st1) st1->parent = t1;
	t1->rchild = st2; if (st2) st2->parent = t1;
	t3->lchild = st3; if (st3) st3->parent = t3;
	t3->rchild = st4; if (st4) st4->parent = t3;
	t2->lchild = t1; t1->parent = t2;
	t2->rchild = t3; t3->parent = t2;

	updateHeightAbove(t1);
	updateHeightAbove(t3);
}
