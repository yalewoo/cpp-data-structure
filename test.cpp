#include <iostream>

using namespace std;

template <typename T>
class A
{
public:
	T a;

	template <typename VST> void func(VST &visit);
};

template <typename T, typename VST> 
void func(A<T>* x, VST &visit)
{
	visit(x->a);
}

template <typename T>
class B
{
public:
	 void operator()(T e)
	{
		cout << e;
	}
};

int main()
{
	B<int> visit;
	A<int> a;
	a.a = 6;
	cout << a.a;
	a.func(visit);

	return 0;
}