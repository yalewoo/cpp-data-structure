#include <iostream>
#include "Vector.h"

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
	Vector<int> a(5);
	a.insert(0, 2);
	a.insert(0, 6);
	a.insert(0, 7);
	// cout << a.capacity() << endl;
	a.insert(0, 4);
	a.insert(0, 4);
	a.insert(0, 5);
	a.insert(0, 9);
	a.insert(0, 9);
	a.insert(0, 5);
	a.insert(0, 5);
	a.insert(0, 9);
	a.insert(0, 9);
	a.insert(0, 5);
	// cout << a.capacity() << endl;

	MyPrint<int> visit;

	// a.travser(visit);
	a.sort();
	a.travser(visit);

	cout << endl;
	cout << a.search(1) << endl;
	cout << a.search(2) << endl;
	cout << a.search(3) << endl;
	//cout << "uniquify " << a.uniquify() << endl;
	//cout << "deduplicate " << a.deduplicate() << endl;
	
	//cout << a.search(7, 0, a.size());
	//cout << a.search(8, 0, a.size());


	return 0;
}
