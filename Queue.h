#ifndef MY_QUEUE_H
#define MY_QUEUE_H

#include "List.h"

template <typename T>
class Queue : public List<T>
{
public:
	void enqueue(T const & e) { this->insertAsLast(e); }
	T rear() { return this->last()->data; }

	T dequeue() { return this->remove(this->first()); }
	T front() { return this->first->data; }
};

#endif