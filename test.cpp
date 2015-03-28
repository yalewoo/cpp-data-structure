#include <iostream>

using namespace std;

template <typename T> 
void func(T * & x)
{
	x += 1;
}

template <typename T>
class A
{	
protected:
	T *a;
public:

	void func1();
};
template <typename T>
void A<T>::func1()
{
	func(a);
}



int main()
{
	A<int> aa;

	aa.func1();

	return 0;
}