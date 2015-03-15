#include <iostream>
#include "Vector.h"

using namespace std;

int main()
{
	Vector<int> a(10);
	a.insert(0, 2);
	a.insert(0, 3);
	a.insert(0, 7);
	a.insert(0, 4);
	a.insert(0, 4);
	a.insert(0, 5);
	a.insert(0, 9);
	a.insert(0, 9);
	a.print();
	a.sort();
	a.print();

	//cout << a.find(2, 0, 1);
	//cout << "uniquify " << a.uniquify() << endl;
	//cout << "deduplicate " << a.deduplicate() << endl;
	
	//cout << a.search(7, 0, a.size());
	//cout << a.search(8, 0, a.size());


	return 0;
}
