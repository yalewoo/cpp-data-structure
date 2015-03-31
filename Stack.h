#ifndef MY_STACK_H
#define MY_STACK_H


#include "Vector.h"
template <typename T>
class Stack : public Vector<T>
{
public:

	using Vector<T>::size;

	void push(T const & e) { this->insert(size(), e); }
	T pop() { return this->remove(size()-1); }
	T top() {return this->get(size()-1); }

};

#endif