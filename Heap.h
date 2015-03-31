#ifndef MY_HEAP_H
#define MY_HEAP_H

#include "Vector.h"

#define PARENT(i) (((i)-1)/2)
#define LEFT(i) (2*(i)+1)
#define RIGHT(i) (2*((i)+1))

template <typename T> class Heap : public Vector<T>
{
protected:
	int _heapsize;	//堆的大小
	int precolateDown(int i);	//下滤
	int precolateUp(int i);	//上滤
	
public:
	void heapify(int n);	//批量建堆
	void heapsort(int n);	//堆排序
	Heap(int c = DEFAULT_CAPACITY):Vector<T>(c)
	{
		_heapsize = 0;
	}
};



template <typename T>
int Heap<T>::precolateDown(int i)
{
	int l = LEFT(i);
	int r = RIGHT(i);
	int largest;

	while (l < _heapsize && r < _heapsize)
	{
		if (this->_elem[i] >= this->_elem[l] && this->_elem[i] >= this->_elem[r])
			return i;
		else if (this->_elem[l] >= this->_elem[i] && this->_elem[l] >= this->_elem[r])
			largest = l;
		else
			largest = r;

		this->swap(this->_elem[i], this->_elem[largest]);

		i = largest;
		l = LEFT(i);
		r = RIGHT(i);
	}

	return i;
}

template <typename T>
int Heap<T>::precolateUp(int i)
{
	int p = PARENT(i);

	while (p >= 0)
	{
		if (this->_elem[i] > this->_elem[p])
		{
			this->swap(this->_elem[i], this->_elem[p]);

			i = p;
			p = PARENT(i);
		}
		else
			return i;
	}
	return 0;
}

template <typename T>
void Heap<T>::heapify(int n)
{
	_heapsize = n;
	int i = n / 2;
	while (i >= 0)
	{
		precolateDown(i);
		--i;
	}
}

template <typename T>
void Heap<T>::heapsort(int n)
{
	heapify(n);
	for (int i = n-1; i > 0; --i)
	{
		this->swap(this->_elem[0], this->_elem[i]);
		--_heapsize;
		precolateDown(0);
	}
}

#endif