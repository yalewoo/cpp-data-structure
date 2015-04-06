#ifndef MY_VECTOR_H
#define MY_VECTOR_H

#include <cstdlib>
using std::rand;

#define DEFAULT_CAPACITY 20

enum sort_method{
	BUBBLE, INSERT, QUICK, MERGE
};

template <typename T> class Vector{	
	
protected:
	int _size;	//当前元素个数
	int _capacity;	//最大容量
	T* _elem;	//存放向量元素

	void expand();	//扩容为原来的2倍
	void decrease();	//收缩容量为二分之一
	void copyFrom(T a[], int lo, int hi);	//把a数组[lo,hi)部分复制到_elem

	void bubbleSort();	//冒泡排序
	int partition(int lo, int hi);	//快速排序的划分
	void quicksort(int lo, int hi);	//快速排序
	void merge(int lo, int mid, int hi);
	void mergesort(int lo, int hi);

	void swap(T &a, T &b){T tmp = a; a = b; b = tmp;}
	
public:
	Vector(int c = DEFAULT_CAPACITY)
	{
		_size = 0;
		_capacity = c;
		_elem = new T[c];
	}
	Vector(Vector &s)
	{
		copyFrom(s._elem, 0, s._size);
	}
	~Vector() { if (_elem) delete[] _elem; }
	template <typename VST> void travser(VST &visit);	//遍历
	int size() {return _size;}	//返回当前元素总数
	int capacity() {return _capacity;}
	bool empty() {return !_size;}
	T get(int r);	//返回秩为r的元素
	T & operator[](int n) { return _elem[n]; }
	T last() { return _elem[_size-1]; }

	bool put(int r, T e);	//将位置r处元素替换为e
	bool insert(int r, T e);	//在位置r处插入e 后面的后移
	bool push_back(T e) { return insert(_size, e); }
	T remove(int r);	//删除秩为r的元素，并返回
	bool disordered();	//是否非降序排列（true乱序 false有序）

	void sort(enum sort_method method = QUICK);	//按照非降排序

	int find(T e);	//查找e 返回下标
	int search(T e);	//有序查找 返回不大于e的最大元素的位置
	int findInRange(T e, int lo, int hi);	//查找e 返回下标
	int searchInRange(T e, int lo, int hi);	//有序查找 返回不大于e的最大元素的位置

	int deduplicate();	//无序向量去重
	int uniquify();	//有序向量去重
};


//把a[]的[lo, hi)复制到类中
template <typename T>
void Vector<T>::copyFrom(T a[], int lo, int hi)
{
	_capacity = 2 * (lo - hi);
	_elem = new T[_capacity];
	_size = 0;
	while (lo < hi)
	{
		_elem[_size++] = a[lo++];
	}
}

template <typename T>
template <typename VST>
void Vector<T>::travser(VST &visit)
{
	for (int i = 0; i < _size; ++i)
		visit(_elem[i]);
}

template <typename T>
bool Vector<T>::insert(int r, T e)
{
	if (r > _size || r < 0)
		return false;
	if (_size == _capacity)
		expand();

	int i = _size++;
	while (i > r)
	{
		_elem[i] = _elem[i-1];
		--i;
	}
	_elem[i] = e;
	return true;
}

//返回秩为r的元素
template <typename T>
T Vector<T>::get(int r)
{
	if (r >= 0 && r < _size)
		return _elem[r];
	else
		return 0;
}

//将位置r处元素替换为e
template <typename T>
bool Vector<T>::put(int r, T e)
{
	if (r < 0 || r >= _size)
		return false;
	
	_elem[r] = e;
	return true;
}


//删除秩为r的元素，并返回
template <typename T>
T Vector<T>::remove(int r)
{
	if (r < 0 || r >= _size)
		return 0;
	T tmp = _elem[r];
	int i;
	for (i = r; i < _size-1; ++i)
	{
		_elem[i] = _elem[i+1];
	}
	--_size;
	return tmp;
}

//是否非降序排列（true乱序 false有序）
template <typename T>
bool Vector<T>::disordered()
{
	for (int i = 0; i < _size-1; ++i)
	{
		if (_elem[i+1] < _elem[i])
			return true;
	}
	return false;
}

//冒泡排序
template <typename T>
void Vector<T>::bubbleSort()
{
	int i, j, temp;
	
	for (i = _size-1; i > 0; --i)
	{
		int flag = 0;
		for (j = 0; j < i; ++j)
		{
			if (_elem[j+1] < _elem[j])
			{
				temp = _elem[j];
				_elem[j] = _elem[j+1];
				_elem[j+1] = temp;
				flag = 1;
			}
		}
		if (flag == 0)
			return;
	}
}


//按照非降排序
template <typename T>
void Vector<T>::sort(enum sort_method method)
{
	switch (method)
	{
	case BUBBLE:
		bubbleSort();
		break;
	case INSERT:
		break;
	case QUICK:
		quicksort(0, _size);
		break;
	case MERGE:
		mergesort(0, _size);
		break;
	default:
		break;
	}
}

//无序时查找
template <typename T>
int Vector<T>::findInRange(T e, int lo, int hi)
{
	for (int i = lo; i < hi; ++i)
	{
		if (_elem[i] == e)
			return i;
	}
	return -1;
}

//有序查找 返回不大于e的最大元素的位置
template <typename T>
int Vector<T>::searchInRange(T e, int lo, int hi)
{
	while (lo < hi)
	{
		int mid = lo + (hi - lo) / 2;
		if (e < _elem[mid])
		{
			hi = mid;
		}
		else
		{
			lo = mid + 1;
		}
	}

	return lo-1;
}

template <typename T>
int Vector<T>::search(T e)
{
	return searchInRange(e, 0, _size);
}

template <typename T>
int Vector<T>::find(T e)
{
	return findInRange(e, 0, _size);
}

//无序向量去重 返回重复个数
template <typename T>
int Vector<T>::deduplicate()
{
	int oldsize = _size;
	for (int i = 0; i < _size; ++i)
	{
		if (findInRange(_elem[i], 0, i) >= 0)
			remove(i);
	}
	return oldsize - _size;
}

//有序向量去重
template <typename T>
int Vector<T>::uniquify()
{
	int oldsize = _size;
	int i = _size - 2;
	while (i >= 0)
	{
		if (_elem[i] == _elem[i+1])
			remove(i+1);

		--i;
	}
	return oldsize - _size;
}

//快速排序的划分
template <typename T>
int Vector<T>::partition(int lo, int hi)
{
	int r = rand() % (hi - lo + 1) + lo;
	int x = _elem[r];
	_elem[r] = _elem[lo];

	while (lo < hi)
	{
		while (hi > lo && !(_elem[hi] < x))
			--hi;
		_elem[lo] = _elem[hi];


		while (lo < hi && !(x < _elem[lo]))
			++lo;
		_elem[hi] = _elem[lo];

	}
	_elem[lo] = x;
	return lo;
}
//快速排序
template <typename T>
void Vector<T>::quicksort(int lo, int hi)
{
	if (hi - lo < 2) return;
	int mid = partition(lo, hi - 1);
	quicksort(lo, mid);
	quicksort(mid+1, hi);
}

template <typename T>
void Vector<T>::merge(int lo, int mid, int hi)
{
	T * L = new int[mid-lo];

	int i;
	int lenL = mid - lo;

	for (i = lo; i < mid; ++i)
		L[i-lo] = _elem[i];

	i = 0;
	int j = mid;
	int k = lo;
	while (i < lenL && j < hi)
	{
		if (!(_elem[j] < L[i]))
			_elem[k++] = L[i++];
		else
			_elem[k++] = _elem[j++];
	}
	while (i < lenL)
		_elem[k++] = L[i++];

	delete[] L;
}
template <typename T>
void Vector<T>::mergesort(int lo, int hi)
{
	if (hi - lo < 2) return;
	int mid = lo + (hi - lo) / 2;
	mergesort(lo, mid);
	mergesort(mid, hi);
	merge(lo, mid, hi);
}

template <typename T>
void Vector<T>::expand()
{
	_capacity *= 2;
	T *old = _elem;
	_elem = new T[_capacity];
	for (int i = 0; i < _size; ++i)
	{
		_elem[i] = old[i];
	}
	delete[] old;
}
template <typename T>
void Vector<T>::decrease()
{
	_capacity /= 2;
	T *old = _elem;
	_elem = new T[_capacity];
	for (int i = 0; i < _size; ++i)
	{
		_elem[i] = old[i];
	}
	delete[] old;
}

#endif