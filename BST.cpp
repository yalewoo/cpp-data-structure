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
	b.insert(2);
	b.insert(1);
	b.insert(3);
	

	b.display();
	cout << endl << endl;

	b.remove(2);

	b.display();

	b.insert(6);
	b.display();


	return 0;
}