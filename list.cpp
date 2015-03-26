#include <iostream>

using namespace std;

#define Posi(T) ListNode<T>*

template <typename T> struct ListNode
{
	T data;
	Posi(T) pred;
	Posi(T) next;
	ListNode() = default;
	ListNode(T e, Posi(T) p = NULL, Posi(T) n = NULL) : data(e), pred(p), next(n) { }
	Posi(T) insertPred(T e);
	Posi(T) insertNext(T e);
};
template <typename T> class List
{
protected:
	int _size;
	ListNode<T> head;
	ListNode<T> tail;
public:
	List();
	int size() {return _size;}
	Posi(T) first() {return head.next;}
	Posi(T) last() {return tail.pred;}
	Posi(T) insertAsFirst(T e);
	Posi(T) insertAsLast(T e);
	void print();
	Posi(T) insertAfter(Posi(T) p, T e);
	Posi(T) insertBefore(Posi(T) p, T e);
	T remove(Posi(T) p);
	bool disordered();
	void sort();
};

int main()
{
	List<int> l;
	l.insertAsFirst(5);
	Posi(int) p = l.insertAsFirst(4);
	l.insertAsFirst(3);
	l.insertAsFirst(8);
	l.insertAsFirst(22);
	l.insertBefore(l.insertAsFirst(2), 9);

	l.print();
	l.remove(p);
	cout << endl;
	l.print();
	cout << endl;

	//cout << l.disordered();
	l.sort();
	l.print();
	return 0;
}

template <typename T>
Posi(T) ListNode<T>::insertPred(T e)
{
	Posi(T) x = new ListNode(e, this->pred, this);
	this->pred->next = x;
	this->pred = x;
	return x;
}
template <typename T>
Posi(T) ListNode<T>::insertNext(T e)
{
	Posi(T) x = new ListNode(e, this, this->next);
	this->next->pred = x;
	this->next = x;
	return x;
}


template <typename T>
List<T>::List()
{
	_size = 0;

	head.next = &tail;
	tail.pred = &head;

	head.pred = NULL;
	tail.next = NULL;
}

template <typename T>
Posi(T) List<T>::insertAsFirst(T e)
{
	Posi(T) x = new ListNode<T> (e, &head, head.next);
	head.next->pred = x;
	head.next = x;
	return x;
}
template <typename T>
Posi(T) List<T>::insertAsLast(T e)
{
	Posi(T) x = new ListNode<T> (e, tail.pred, &tail);
	tail.pred->next = x;
	tail.pred = x;
	return x;
}

template <typename T>
void List<T>::print()
{
	Posi(T) x = head.next;
	while (x != &tail)
	{
		cout << x->data << " ";
		x = x->next;
	}
}

template <typename T>
Posi(T) List<T>::insertAfter(Posi(T) p, T e)
{
	Posi(T) x = new ListNode<T> (e, p, p->next);
	p->next = x;
	x->next->pred = x;
	return x;
}
template <typename T>
Posi(T) List<T>::insertBefore(Posi(T) p, T e)
{
	Posi(T) x = new ListNode<T> (e, p->pred, p);
	p->pred = x;
	x->pred->next = x;
	return x;
}

template <typename T>
T List<T>::remove(Posi(T) p)
{
	T tmp = p->data;
	p->pred->next = p->next;
	p->next->pred = p->pred;
	delete p;
	return tmp;
}

template <typename T>
bool List<T>::disordered()
{
	Posi(T) p = head.next;
	T e = p->data;
	while (p != &tail)
	{
		if (p->data < e)
			return true;
		e = p->data;
		p = p->next;
	}
	return false;
}

template <typename T>
void List<T>::sort()
{
	Posi(T) i = head.next;
	Posi(T) j = i;
	while (i != &tail)
	{
		for (j = head.next; j != i && j->data <= i->data; j = j->next)
			;
		Posi(T) newi = i->next;
		j->insertPred(i->data);
		remove(i);
		i = newi;
	}
}