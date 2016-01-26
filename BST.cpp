#include <iostream>

using namespace std;

#include "BST.h"


template <typename T>
class MyPrint
{
public:
	void operator()(T const &e)
	{
		cout << e << " ";
	}
};
int main()
{
	MyPrint<int> visit;

	BST<int> b;
	b.insert(8);
	b.insert(3);
	b.insert(7);
	b.insert(9);
	b.insert(11);
	b.insert(5);
	b.insert(51);
	b.insert(2);
	b.insert(1);
	b.insert(88);
	b.insert(64);
	b.insert(67);


	b.travIn(visit);
	cout << endl << b.height() << endl;

	b.remove(51);
	b.travIn(visit);
	cout << endl << b.height() << endl;
	cout << endl;

	b.remove(67);

	b.insert(7);
	b.insert(6);
	b.insert(5);
	b.insert(4);
	b.insert(3);
	b.insert(2);
	b.insert(1);
	b.insert(3);

	b.display();
	cout << endl << endl;

	b.remove(2);
	b.display();
	return 0;
}