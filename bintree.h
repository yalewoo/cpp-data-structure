#include "Stack.h"
#include "Queue.h"

#include <algorithm>
using std::max;

#define BinNodePosi(T) BinNode<T>*

#define stature(p) ((p) ? (p)->height : -1)	//height, empty tree has height -1

template <typename T>
class BinNode
{
public:
	T data;
	BinNodePosi(T) parent;
	int height;
	BinNodePosi(T) lchild;
	BinNodePosi(T) rchild;
	
	int size();	//how many sub tree node(include this)

	BinNodePosi(T) insertAsLC(T const &);
	BinNodePosi(T) insertAsRC(T const &);
	BinNodePosi(T) succ();

	
	template <typename VST> void travPre_R(VST &);
	template <typename VST> void travPre_I(VST &);
	template <typename VST> void travPre_II(VST &);
	template <typename VST> void travIn_R(VST &);
	template <typename VST> void travIn_I(VST &);
	template <typename VST> void travPost_R(VST &);
	template <typename VST> void travPost_I(VST &);
	template <typename VST> void travLevel(VST &);
	BinNode(T e, BinNodePosi(T) p);
};
template <typename T>
int BinNode<T>::size()
{
	int s = 1;
	if (lchild) s += lchild->size();
	if (rchild) s += rchild->size();
	return s;
}

template <typename T>
BinNode<T>::BinNode(T e, BinNodePosi(T) p) : data(e), parent(p)
{
	height = 0;
	lchild = 0;
	rchild = 0;
	
}
template <typename T>
BinNodePosi(T) BinNode<T>::insertAsLC(T const & e)
{
	return lchild = new BinNode(e, this);
}
template <typename T>
BinNodePosi(T) BinNode<T>::insertAsRC(T const & e)
{
	return rchild = new BinNode(e, this);
}




template <typename T> class BinTree
{
protected:
	int _size;
	BinNodePosi(T) _root;

	int updateHeight(BinNodePosi(T) x); //update height of x
	void updateHeightAbove(BinNodePosi(T) x); //update height of x and x's parents
public:
	BinTree(BinNodePosi(T) root);
	int size() const { return _size; }	//how many binnodes
	bool empty() const { return !_root; }
	BinNodePosi(T) root() const { return _root; }
	BinNodePosi(T) insertAsLC(BinNodePosi(T) x, T const & e);
	BinNodePosi(T) insertAsRC(BinNodePosi(T) x, T const & e);
	BinNodePosi(T) attachAsLC(BinNodePosi(T) x, BinTree<T>* & S);
	BinNodePosi(T) attachAsRC(BinNodePosi(T) x, BinTree<T>* & S);
	int remove(BinNodePosi(T) x);
	BinNodePosi(T) secede(BinNodePosi(T) x);

};
template <typename T>
BinTree<T>::BinTree(BinNodePosi(T) root) : _root(root)
{
	_size = root->size();
	root->parent = NULL;
}
template <typename T>
int BinTree<T>::updateHeight(BinNodePosi(T) x)
{
	return x->height = 1 + max(stature(x->lchild), stature(x->rchild));
}
template <typename T>
void BinTree<T>::updateHeightAbove(BinNodePosi(T) x)
{
	while (x)
	{
		updateHeight(x);
		x = x->parent;
	}
}

template <typename T>
BinNodePosi(T) BinTree<T>::insertAsLC(BinNodePosi(T) x, T const & e)
{
	++_size;
	x->insertAsLC(e);
	updateHeightAbove(x);
	return x->lchild;
}
template <typename T>
BinNodePosi(T) BinTree<T>::insertAsRC(BinNodePosi(T) x, T const & e)
{
	++_size;
	x->insertAsRC(e);
	updateHeightAbove(x);
	return x->rchild;
}

template <typename T>
BinNodePosi(T) BinTree<T>::attachAsLC(BinNodePosi(T) x, BinTree<T>* & S)
{
	x->lchild = S->_root;
	if (x->lchild) x->lchild->parent = x;

	_size += S->_size;
	updateHeightAbove(x);

	S->_root = NULL;
	S->_size = 0;
	delete S;
	S = NULL;

	return x;
}

template <typename T>
BinNodePosi(T) BinTree<T>::attachAsRC(BinNodePosi(T) x, BinTree<T>* & S)
{
	x->rchild = S->_root;
	if (x->rchild) x->rchild->parent = x;

	_size += S->_size;
	updateHeightAbove(x);

	S->_root = NULL;
	S->_size = 0;
	delete S;
	S = NULL;

	return x;
}

template <typename T>
int BinTree<T>::remove(BinNodePosi(T) x)
{
	if (x->parent->lchild == x) x->parent->lchild = NULL;
	if (x->parent->rchild == x) x->parent->rchild = NULL;

	updateHeightAbove(x->parent);

	int n = removeAt(x);
	_size -= n;
	return n;
}
template <typename T>
BinNodePosi(T) BinTree<T>::secede(BinNodePosi(T) x)
{
	if (x->parent->lchild == x) x->parent->lchild = NULL;
	if (x->parent->rchild == x) x->parent->rchild = NULL;

	updateHeightAbove(x->parent);

	BinTree<T> * S = new BinTree<T>;
	S->_root = x;
	x->parent = NULL;
	S->_size = x->size();

	_size -= S->size;

	return S;
}

template <typename T>
static int removeAt(BinNodePosi(T) x)
{
	if (x == NULL) return 0;
	int n = 1 + removeAt(x->lchild) + removeAt(x->rchild);

	delete x;
	return n;
}

template <typename T>
template <typename VST>
void BinNode<T>::travPre_R(VST & visit)
{
	if (this == NULL) return;

	visit(this->data);
	this->lchild->travPre_R(visit);
	this->rchild->travPre_R(visit);
}
template <typename T>
template <typename VST>
void BinNode<T>::travPre_I(VST & visit)
{
	Stack<BinNodePosi(T)> stk;
	BinNodePosi(T) x;

	stk.push(this);
	while (!stk.empty())
	{
		x = stk.pop();
		while (x != NULL)
		{
			visit(x->data);
			stk.push(x->rchild);
			x = x->lchild;
		}
	}
}
template <typename T>
template <typename VST>
void BinNode<T>::travPre_II(VST & visit)
{
	Stack<BinNodePosi(T)> stk;
	BinNodePosi(T) x;

	stk.push(this);
	while (!stk.empty())
	{
		x = stk.pop();
		if (x != NULL) visit(x->data);
		if (x->rchild) stk.push(x->rchild);
		if (x->lchild) stk.push(x->lchild);
	}
}

template <typename T>
template <typename VST>
void BinNode<T>::travIn_R(VST & visit)
{
	if (this == NULL) return;

	this->lchild->travIn_R(visit);
	visit(this->data);
	this->rchild->travIn_R(visit);
}
template <typename T>
template <typename VST>
void BinNode<T>::travIn_I(VST & visit)
{
	Stack<BinNodePosi(T)> stk;
	BinNodePosi(T) x = this;

	stk.push(x);
	x = x->lchild;

	while (true)
	{
		while (x != NULL)
		{
			stk.push(x);
			x = x->lchild;
		}

		if (stk.empty()) break;

		x = stk.pop();
		visit(x->data);
		x = x->rchild;
	}
}

template <typename T>
template <typename VST>
void BinNode<T>::travPost_R(VST & visit)
{
	if (this == NULL) return;

	this->lchild->travPost_R(visit);
	this->rchild->travPost_R(visit);
	visit(this->data);
}

template <typename T>
template <typename VST>
void BinNode<T>::travPost_I(VST & visit)
{
	Stack<BinNodePosi(T)> stk;
	
	BinNodePosi(T) x = this;
	if (x) stk.push(this);

	while (!stk.empty())
	{
		if (x->parent != stk.top())
		{
			while ((x = stk.top()) != NULL)
			{
				if (x->lchild)
				{
					if (x->rchild)
						stk.push(x->rchild);
					stk.push(x->lchild);
				}
				else
				{
					stk.push(x->rchild);
				}
			}
			stk.pop();
		}
		x = stk.pop();
		visit(x->data);
	}
}
template <typename T>
template <typename VST>
void BinNode<T>::travLevel(VST & visit)
{
	Queue<BinNodePosi(T)> q;
	BinNodePosi(T) x = this;
	
	q.enqueue(x);
	while (!q.empty())
	{
		x = q.dequeue();
		if (x) visit(x->data);
		if (x->lchild) q.enqueue(x->lchild);
		if (x->rchild) q.enqueue(x->rchild);
	}
}

template <typename T>
BinNodePosi(T) BinNode<T>::succ()
{
	BinNodePosi(T) x;
	if (rchild != NULL)
	{
		x = rchild;
		while (x->lchild != NULL)
			x = x->lchild;
	}
	else
	{
		x = this;
		while (x->parent != NULL && x->parent->lchild != x)
			x = x->parent;
		x = x->parent;
	}
	return x;
}