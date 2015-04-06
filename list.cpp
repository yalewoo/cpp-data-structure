#include <iostream>
#include "List.h"

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
	List<int> l;
	l.insertAsFirst(5);
	Posi(int) p = l.insertAsFirst(4);
	l.insertAsFirst(3);
	l.insertAsFirst(8);
	l.insertAsFirst(22);
	l.insertBefore(l.insertAsFirst(2), 9);

	MyPrint<int> visit;
	l.travser(visit);
	l.remove(p);
	cout << endl;
	l.travser(visit);
	cout << endl;

	//cout << l.disordered();
	l.sort();
	l.insertAfter(l.search(7), 7);
	l.travser(visit);


	return 0;
}

