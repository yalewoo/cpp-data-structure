#include <iostream>

using namespace std;

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

	BTNode() : parent(NULL) { }
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
	int n;
	while (p)
	{
		n = p->key.search(e);
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
		lc->child.push_back(pn->child[i]);
	}
	lc->child.push_back(pn->child[i]);
	for (i = 0; i < lc->child.size(); ++i)
		if (lc->child[i]) lc->child[i]->parent = lc;

	BTNodePosi(T) rc = new BTNode<T>;
	for (i = n+1; i < pn->key.size(); ++i)
	{
		rc->key.push_back(pn->key[i]);
		rc->child.push_back(pn->child[i]);
	}
	rc->child.push_back(pn->child[i]);
	for (i = 0; i < rc->child.size(); ++i)
		if (rc->child[i]) rc->child[i]->parent = rc;
	

	if (!p)
	{
		p = new BTNode<T>;
		p->child.push_back(NULL);
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
void BTree<T>::solveUnderflow(BTNodePosi(T) pn)
{
	
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




int main()
{
	BTree<int> bt(4);

	// bt.insert(21);
	// bt.insert(48);
	// bt.insert(72);
	// bt.insert(12);
	// bt.insert(22);
	// bt.insert(50);
	// bt.insert(34);
	// bt.insert(42);
	// bt.insert(60);
	// bt.insert(67);
	// bt.insert(89);
	// bt.insert(13);

	int i;
	for (i = 0; i < 30; ++i)
		bt.insert(i);

	bt.display();

	printf("233");

	return 0;
}