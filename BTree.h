#include "Vector.h"
#include "Queue.h"

#define BTNodePosi(T) BTNode<T>*

template <typename T>
class BTNode
{
public:
	BTNodePosi(T) parent;
	Vector<T> key;
	Vector<BTNodePosi(T)> child;

	BTNode() : parent(NULL) { child.push_back(NULL); }
	BTNode(T e, BTNodePosi(T) lchild = NULL, BTNodePosi(T) rchild = NULL);
};

template <typename T>
BTNode<T>::BTNode(T e, BTNodePosi(T) lchild, BTNodePosi(T) rchild)
{
	parent = NULL;
	key.insert(e);
	child.insert(0, lchild);
	child.insert(1, rchild);
	if (lchild) lchild->parent = this;
	if (rchild) rchild->parent = this;
}

template <typename T>
class BTree
{
protected:
	int _size;
	int _order;
	BTNodePosi(T) _root;
	BTNodePosi(T) _hot;
	void solveOverflow(BTNodePosi(T));
	void solveUnderflow(BTNodePosi(T));
public:
	BTNodePosi(T) search(const T & e);
	bool insert(const T & e);
	bool remove(const T & e);
	void display();
	BTree(int order) : _size(0), _order(order), _root(NULL), _hot(NULL) { }
};

template <typename T>
BTNodePosi(T) BTree<T>::search(const T & e)
{
	BTNodePosi(T) p = _root;
	_hot = NULL;

	while (p)
	{
		int n = p->key.search(e);
		if (p->key[n] == e)
			return p;

		_hot = p;
		p = p->child[n+1];
	}
	return NULL;
}
template <typename T>
bool BTree<T>::insert(const T & e)
{
	if (search(e)) return false;

	BTNodePosi(T) p = _hot;
	if (!p)
	{
		p = new BTNode<T>;
		_root = p;
		p->key.push_back(e);
		p->child.push_back(NULL);
		return true;
	}
	int n = p->key.search(e);
	p->key.insert(n+1, e);
	p->child.push_back(NULL);

	++_size;

	BTNodePosi(T) par;
	while (p && p->child.size() > _order)
	{
		par = p->parent;
		solveOverflow(p);
		p = par;
	}


	return true;
}
template <typename T>
bool BTree<T>::remove(const T & e)
{
	BTNodePosi(T) p = search(e);
	if (!p) return false;
	int n = p->key.search(e);

	if (p->child[0])
	{
		BTNodePosi(T) q = p->child[n+1];
		while (q->child[0])
		{
			q = q->child[0];
		}
		p->key.put(n, q->key[0]);
		n = 0;
		p = q;
	}
	
	p->key.remove(n);
	p->child.remove(n);
	--_size;
	

	if (p != _root && p->child.size() < (_order+1)/2)
	{
		solveUnderflow(p);
	}

	return true;
}

template <typename T>
void BTree<T>::solveOverflow(BTNodePosi(T) pn)
{
	BTNodePosi(T) p = pn->parent;
	int n = (_order-1)/2;

	int i;
	BTNodePosi(T) lc = new BTNode<T>;
	for (i = 0; i < n; ++i)
	{
		lc->key.push_back(pn->key[i]);
		if (i == 0)
			lc->child.put(0, pn->child[0]);
		else
			lc->child.push_back(pn->child[i]);
	}
	lc->child.push_back(pn->child[i]);
	for (i = 0; i < lc->child.size(); ++i)
		if (lc->child[i]) lc->child[i]->parent = lc;

	BTNodePosi(T) rc = new BTNode<T>;
	for (i = n+1; i < pn->key.size(); ++i)
	{
		rc->key.push_back(pn->key[i]);
		if (i == n+1)
			rc->child.put(0, pn->child[i]);
		else
			rc->child.push_back(pn->child[i]);	
	}
	rc->child.push_back(pn->child[i]);
	for (i = 0; i < rc->child.size(); ++i)
		if (rc->child[i]) rc->child[i]->parent = rc;
	

	if (!p)
	{
		p = new BTNode<T>;
		_root = p;
	}

	lc->parent = p;
	rc->parent = p;
	int n1 = p->key.search(pn->key[n]);
	p->key.insert(n1+1, pn->key[n]);
	p->child.put(n1+1, lc);
	p->child.insert(n1+2, rc);

	delete pn;

}
template <typename T>
void BTree<T>::solveUnderflow(BTNodePosi(T) q)
{
	if (q->child.size() >= (_order+1)/2) return;

	if (q == _root)
	{
		if (q->key.empty())
		{
			_root = q->child[0];
			delete q;
		}
		return;
	}


	BTNodePosi(T) p = q->parent;
	int n;
	for (n = 0; n < p->child.size(); ++n)
	{
		if (p->child[n] == q)
			break;
	}

	BTNodePosi(T) lc;
	BTNodePosi(T) rc;
	if (n > 0 && p->child[n-1]->child.size() > (_order+1)/2)
	{
		lc = p->child[n-1];
		q->key.insert(0, p->key[n-1]);
		q->child.insert(0, lc->child.last());
		if (q->child[0]) q->child[0]->parent = q;

		p->key.put(n-1, lc->key.last());

		lc->key.remove(lc->key.size() - 1);
		lc->child.remove(lc->child.size() - 1);
		return;
	}
	if (n < p->child.size()-1 && p->child[n+1]->child.size() > (_order+1)/2)
	{
		rc = p->child[n+1];
		q->key.push_back(p->key[n]);
		q->child.push_back(rc->child[0]);
		if (rc->child[0]) rc->child[0] = q;

		p->key.put(n, rc->key[0]);

		rc->key.remove(0);
		rc->child.remove(0);
		return;
	}

	if (n > 0)
	{
		lc = p->child[n-1];
		lc->key.push_back(p->key[n-1]);
		int i;
		for (i = 0; i < q->key.size(); ++i)
		{
			lc->key.push_back(q->key[i]);
			lc->child.push_back(q->child[i]);
		}
		lc->child.push_back(q->child[i]);

		p->key.remove(n-1);
		p->child.remove(n);
		delete q;
	}
	else
	{
		rc = p->child[n+1];

		q->key.push_back(p->key[n]);
		int i;
		for (i = 0; i < rc->key.size(); ++i)
		{
			q->key.push_back(rc->key[i]);
			q->child.push_back(rc->child[i]);
		}
		q->child.push_back(rc->child[i]);

		p->key.remove(n);
		p->child.remove(n+1);
		delete rc;
	}

	solveUnderflow(p);

}

template <typename T>
class MyPrint
{
public:
	void operator()(T e)
	{
		cout << e << " ";
	}
};


template <typename T>
void BTree<T>::display()
{
	if (!_root) return;

	MyPrint<T> visit;
	Queue<BTNodePosi(T)> q;
	BTNodePosi(T) x = _root;

	BTNode<T> endl1;
	
	q.enqueue(x);
	q.enqueue(&endl1);

	int i;
	while (!q.empty())
	{
		x = q.dequeue();

		if (!x) continue;
		if (x == &endl1)
		{
			if (q.size() > 0)
				q.enqueue(&endl1);
			printf("\n");
			continue;
		}
		printf("#");
		x->key.travser(visit);
		printf("#");


		for (i = 0; i < x->child.size(); ++i)
		{
			q.enqueue(x->child[i]);
		}
		
		printf("----");
	}
}

