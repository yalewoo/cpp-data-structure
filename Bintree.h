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

#define stature(p) ((p) ? (p)->height : -1)	//该结点的高度 空节点高度为-1

//左孩子的水平位置 用于display
#define posilchild(p) ((p)->lchild ? (p)->lchild->horizontal_position : (p)->horizontal_position)
#define posirchild(p) ((p)->rchild ? (p)->rchild->horizontal_position : (p)->horizontal_position)


enum RB_COLOR{
	RED, BLACK
};

//二叉树结点数据结构
template <typename T>
class BinNode
{
public:
	T data;	//该结点具体数据
	BinNodePosi(T) parent;	//父节点指针
	BinNodePosi(T) lchild;	//左孩子指针
	BinNodePosi(T) rchild;	//右孩子指针

	enum RB_COLOR color;	//颜色 在红黑树中使用

	int height;	//记录该结点高度

	int horizontal_position;	//记录中序遍历下该结点的序号，用于display显示
	int distance_to_root;	//记录到根节点的距离 用于display显示
	

	int size();	//计算以该结点为根的二叉树结点个数（递归算法）

	BinNodePosi(T) insertAsLC(T const &);	//插入左孩子
	BinNodePosi(T) insertAsRC(T const &);	//插入右孩子
	BinNodePosi(T) succ();	//返回中序遍历时该结点的后继指针

	//遍历算法
	template <typename VST> void travPre_R(VST &);	//先序遍历递归算法
	template <typename VST> void travPre_I(VST &);	//先序遍历基于栈的算法1
	template <typename VST> void travPre_II(VST &);	//先序遍历基于栈的算法2

	template <typename VST> void travIn_R(VST &);	//中序遍历递归算法
	template <typename VST> void travIn_I(VST &);	//中序遍历基于栈的算法

	template <typename VST> void travPost_R(VST &);	//后序遍历递归算法
	template <typename VST> void travPost_I(VST &);	//后序遍历基于栈的算法

	template <typename VST> void travLevel(VST &);	//层次遍历 基于队列

	
	BinNode(T e, BinNodePosi(T) p);	//构造二叉树，父节点p，节点内容e
	BinNode();
	virtual ~BinNode(){}
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

/*
返回该结点为根的子树的结点个数
递归求解 return lc->size() + rc->size() + 1
叶子节点 return 1
*/
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



//二叉树数据结构
template <typename T> class BinTree
{
protected:
	int _size;	//记录该二叉树结点个数
	BinNodePosi(T) _root;	//二叉树树根节点指针

	virtual int updateHeight(BinNodePosi(T) x); //更新结点x的高度
	void updateHeightAbove(BinNodePosi(T) x); //更新x以及x的所有祖先元素的高度
    void updateDistanceToRoot(BinNodePosi(T) x);	//更新x结点及其孩子距离根节点的距离
    void calculatePosition();   //计算结点位置 结果存放在每个结点的horizontal_position和distance_to_root中

    BinNodePosi(T) siblingOf(BinNodePosi(T) x);	//返回结点x的兄弟结点
public:
	BinTree(BinNodePosi(T) root);
	BinTree();
	virtual ~BinTree();

	int size() const { return _size; }	//返回树中结点个数
	int height() const { return _root ? _root->height : 0; }	//返回树的高度
	bool empty() const { return !_root; }	//判断树是否为空树
	BinNodePosi(T) root() const { return _root; }	//返回根节点指针

	//拓扑连接
	BinNodePosi(T) insertAsLC(BinNodePosi(T) x, T const & e);	//把e作为x的左孩子插入
	BinNodePosi(T) insertAsRC(BinNodePosi(T) x, T const & e);	//把e作为x的右孩子插入
	BinNodePosi(T) attachAsLC(BinNodePosi(T) x, BinTree<T>* & S);	//把S作为x的左子树插入
	BinNodePosi(T) attachAsRC(BinNodePosi(T) x, BinTree<T>* & S);	//把S作为x的右子树插入

	//删除x结点
	virtual int remove(BinNodePosi(T) x);

	//将以x为根的子树从树中删去
	BinNodePosi(T) secede(BinNodePosi(T) x);

	//树的遍历算法
	template <typename VST> void travPre(VST &v) { _root->travPre_I(v); }	//先序遍历 对每个节点执行v
	template <typename VST> void travIn(VST &v) { _root->travIn_I(v); }	//中序遍历
	template <typename VST> void travPost(VST &v) { _root->travPost_I(v); }	//后序遍历
	template <typename VST> void travLevel(VST &v) { _root->travLevel_I(v); }	//层次遍历

	//命令行直观显示二叉树
	void display();
};

template <typename T>
BinNodePosi(T) BinTree<T>::siblingOf(BinNodePosi(T) x)
{
	if (x->parent == 0)
		return 0;

	if (x->parent->lchild == x)
		return x->parent->rchild;
	else
		return x->parent->lchild;
}

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


//更新x结点的高度 
template <typename T>
int BinTree<T>::updateHeight(BinNodePosi(T) x)
{
	return x->height = 1 + max(stature(x->lchild), stature(x->rchild));
}
//更新x及其祖先结点高度
template <typename T>
void BinTree<T>::updateHeightAbove(BinNodePosi(T) x)
{
	while (x)
	{
		updateHeight(x);
		x = x->parent;
	}
}

//拓扑连接 步骤为更新size 插入 更新高度
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

//删除结点
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
//分离子树 返回子树的树根
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

//删除子树 释放空间
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

//返回中序遍历下的后继指针
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


//更新x到root的距离 用于display
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

template <typename T>
void BinTree<T>::calculatePosition()
{
    //计算垂直位置
    updateDistanceToRoot(_root);


    //计算水平位置
    int count = 0;
    BinNodePosi(T) x = _root;
    //找到中序遍历的第一个结点
    while (x && x->lchild != NULL)
        x = x->lchild;
    //按照中序遍历的次序记录结点访问次序
    while (x != NULL)
    {
        x->horizontal_position = ++count;
        x->horizontal_position *= 4;    //水平位置放缩4倍 命令行显示时结点之间的空隙4个字符
        x = x->succ();
    }


}

template <typename T>
void BinTree<T>::display()
{
    calculatePosition();

	Queue<BinNodePosi(T)> q;
    BinNodePosi(T) x = _root;
	
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

		if (x && x->lchild) q.enqueue(x->lchild);
		if (x && x->rchild) q.enqueue(x->rchild);
	}


	cout << endl << endl;
}

#endif
