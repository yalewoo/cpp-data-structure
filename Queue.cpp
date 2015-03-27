#include "List.h"
#include <iostream>

using namespace std;

template <typename T>
class Queue : public List<T>
{
public:
	void enqueue(T const & e) { this->insertAsLast(e); }
	T rear() { return this->last()->data; }

	T dequeue() { return this->remove(this->first()); }
	T front() { return this->first->data; }
};

template <typename T>
class MyPrint
{
public:
	void operator()(T e)
	{
		cout << e << " ";
	}
};

int main()
{
	Queue<int> q;
	q.enqueue(4);
	q.enqueue(5);
	q.enqueue(6);
	q.enqueue(7);
	q.enqueue(8);
	q.enqueue(9);

	MyPrint<int> visit;

	q.travser(visit);

	cout << endl << q.dequeue() << endl;


	q.travser(visit);


	return 0;
}