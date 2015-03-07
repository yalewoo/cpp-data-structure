#include <iostream>

using namespace std;

#define DEFAULT_CAPACITY 5

template <typename T> class Vector{	
protected:
	int _size;	//当前元素个数
	int _capacity;	//最大容量
	T* _elem;	//存放向量元素
	void copyFrom(T a[], int lo, int hi);	//把a数组[lo,hi)部分复制到_elem
	void bubbleSort();	//冒泡排序
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
	void print(void);	//打印
	int size(void);	//返回当前元素总数
	T get(int r);	//返回秩为r的元素
	bool put(int r, T e);	//将位置r处元素替换为e
	bool insert(int r, T e);	//在位置r处插入e 后面的后移
	T remove(int r);	//删除秩为r的元素，并返回
	bool disordered();	//是否非降序排列（true乱序 false有序）
	void sort();	//按照非降排序
};




int main()
{
	Vector<int> a(10);
	a.insert(0, 2);
	a.insert(0, 7);
	a.insert(0, 4);
	a.insert(0, 1);
	a.sort();
	a.print();
	return 0;
}

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
void Vector<T>::print(void)
{
	for (int i = 0; i < _size; ++i)
	{
		cout << _elem[i] << " ";
	}
	cout << endl;
}

template <typename T>
bool Vector<T>::insert(int r, T e)
{
	if (r > _size)
		return false;

	int i = _size++;
	while (i > r)
	{
		_elem[i] = _elem[i-1];
		--i;
	}
	_elem[i] = e;
	return true;
}

template <typename T>
int Vector<T>::size(void)
{
	return _size;
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
	int flag;
	for (i = _size; i > 0; --i)
	{
		flag = 0;
		for (j = 0; j < i; ++j)
		{
			if (_elem[j] > _elem[j+1])
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
void Vector<T>::sort()
{
	bubbleSort();
}