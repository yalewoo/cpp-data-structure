#include <iostream>
#include "Stack.h"

using namespace std;

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
	Stack<int> s;
	s.push(4);
	s.push(5);
	s.push(7);
	s.push(8);
	s.push(9);
	s.push(11);

	MyPrint<int> visit;

	s.travser(visit);

	s.empty();

	return 0;
}