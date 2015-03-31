#ifndef MY_BINTREE_H
#define MY_BINTREE_H

#include "Stack.h"
#include "Queue.h"

#include <algorithm>
#include <iostream>
#include <cstdio>
using std::max;
using std::cout;
using std::endl;

#define BinNodePosi(T) BinNode<T>*

#define stature(p) ((p) ? (p)->height : -1)	//height, empty tree has height -1
#define posilchild(p) ((p)->lchild ? (p)->lchild->horizontal_position : (p)->horizontal_position)
#define posirchild(p) ((p)->rchild ? (p)->rchild->horizontal_position : (p)->horizontal_position)



template <typename T>
class BinNode
{
public:
	T data;
	BinNodePosi(T) parent;
	int height;
	BinNodePosi(T) lchild;
	BinNodePosi(T) rchild;

	int horizontal_position;	//Inorder travser index used to display the tree. 
	int distance_to_root;
	

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
	BinNode();
};

template <typename T>
BinNode<T>::BinNode(T e, BinNodePosi(T) p) : data(e), parent(p)
{
	height = 0;
	lchild = 0;
	rchild = 0;
	horizontal_position = 0;
	distance_to_root = 0;
}
template <typename T>
BinNode<T>::BinNode() : data(0), parent(0)
{
	height = 0;
	lchild = 0;
	rchild = 0;
	horizontal_position = 0;
	distance_to_root = 0;

}

template <typename T>
int BinNode<T>::size()
{
	int s = 1;
	if (lchild) s += lchild->size();
	if (rchild) s += rchild->size();
	return s;
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
	void updateDistanceToRoot(BinNodePosi(T) x);
public:
	BinTree(BinNodePosi(T) root);
	BinTree();
	~BinTree();
	int size() const { return _size; }	//how many binnodes
	int height() const { return _root ? _root->height : 0; }
	bool empty() const { return !_root; }
	BinNodePosi(T) root() const { return _root; }
	BinNodePosi(T) insertAsLC(BinNodePosi(T) x, T const & e);
	BinNodePosi(T) insertAsRC(BinNodePosi(T) x, T const & e);
	BinNodePosi(T) attachAsLC(BinNodePosi(T) x, BinTree<T>* & S);
	BinNodePosi(T) attachAsRC(BinNodePosi(T) x, BinTree<T>* & S);
	int remove(BinNodePosi(T) x);
	BinNodePosi(T) secede(BinNodePosi(T) x);

	template <typename VST> void travPre(VST &v) { _root->travPre_I(v); }
	template <typename VST> void travIn(VST &v) { _root->travIn_I(v); }
	template <typename VST> void travPost(VST &v) { _root->travPost_I(v); }
	template <typename VST> void travLevel(VST &v) { _root->travLevel_I(v); }

	void display();

};
template <typename T>
BinTree<T>::BinTree()
{
	_size = 0;
	_root = NULL;
}

template <typename T>
BinTree<T>::BinTree(BinNodePosi(T) root) : _root(root)
{
	_size = root->size();
	root->parent = NULL;
}
template <typename T>
BinTree<T>::~BinTree()
{
	removeTreeByRootNode(_root);
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

	int n = removeTreeByRootNode(x);
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
int removeTreeByRootNode(BinNodePosi(T) x)
{
	if (x == NULL) return 0;
	int n = 1 + removeTreeByRootNode(x->lchild) + removeTreeByRootNode(x->rchild);

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



template <typename T>
void BinTree<T>::updateDistanceToRoot(BinNodePosi(T) x)
{
	if (!x) return;
	int i = 0;
	BinNodePosi(T) p = x;
	while (p != NULL)
	{
		p = p->parent;
		++i;
	}

	x->distance_to_root = i-1;

	Queue<BinNodePosi(T)> q;
	
	q.enqueue(x);
	while (!q.empty())
	{
		x = q.dequeue();
		if (x && x->parent) 
			x->distance_to_root = x->parent->distance_to_root + 1;
		if (x->lchild) q.enqueue(x->lchild);
		if (x->rchild) q.enqueue(x->rchild);
	}



}

// template <typename T>
// void BinTree<T>::display()
// {
// 	int count = 0;
// 	BinNodePosi(T) x = _root;
// 	while (x->lchild != NULL)
// 		x = x->lchild;

// 	while (x != NULL)
// 	{
// 		x->horizontal_position = ++count;
// 		x = x->succ();
// 	}

// 	updateDistanceToRoot(_root);


// 	Queue<BinNodePosi(T)> q;
// 	x = _root;
	
// 	q.enqueue(x);

// 	int nowheight = 0;
// 	int lastheight = 0;
// 	int levelcount = 0;
// 	int i = 0;
// 	while (!q.empty())
// 	{
// 		x = q.dequeue();

// 		if (x) 
// 		{
// 			nowheight = x->distance_to_root;

// 			if (nowheight != lastheight)
// 			{
// 				lastheight = nowheight;
// 				cout << endl;
// 				levelcount = 0;
// 			}

// 			for(i = levelcount; i < x->horizontal_position; ++i)
// 			{
// 				printf("\t");
// 			}
// 			cout << x->data;
// 			levelcount += x->horizontal_position - levelcount;

// 		}

// 		if (x->lchild) q.enqueue(x->lchild);
// 		if (x->rchild) q.enqueue(x->rchild);
// 	}
// 	cout << endl << endl;
// }


template <typename T>
void BinTree<T>::display()
{
	int count = 0;
	BinNodePosi(T) x = _root;
	while (x->lchild != NULL)
		x = x->lchild;

	while (x != NULL)
	{
		x->horizontal_position = ++count;
		x->horizontal_position *= 4;
		x = x->succ();
	}

	updateDistanceToRoot(_root);


	Queue<BinNodePosi(T)> q;
	x = _root;
	
	q.enqueue(x);

	int nowheight = 0;
	int lastheight = 0;
	int levelcount = 0;
	int i = 0;
	while (!q.empty())
	{
		x = q.dequeue();

		long long int tmpposi;
		if (x) 
		{
			nowheight = x->distance_to_root;

			if (nowheight != lastheight)
			{
				lastheight = nowheight;
				cout << endl;
				levelcount = 0;
			}



			for(i = levelcount; i < posilchild(x); ++i)
			{
				printf(" ");
			}
			
			int firstprint = 1;
			for (; i < x->horizontal_position; ++i)
			{
				if (firstprint)
				{
					printf("_");
					firstprint = 0;
				}
				else
					printf("_");
			}

			tmpposi = cout.tellp();
			cout << x->data;
			long long int tellpppp = cout.tellp() - tmpposi;
			levelcount += (int) (tellpppp);

			levelcount += x->horizontal_position - levelcount;

			for (i = levelcount; i < posirchild(x); ++i)
			{
				if (i == posirchild(x) - 1)
					printf("_");
				else
					printf("_");
			}
			levelcount = i;


		}

		if (x->lchild) q.enqueue(x->lchild);
		if (x->rchild) q.enqueue(x->rchild);
	}


	cout << endl << endl;
}

#endif