#include <iostream>
#include "AVL.h"

using namespace std;

int main()
{

	AVL<int> b;
	b.insert(3);
	b.insert(2);
	b.insert(1);
	b.insert(4);
	b.insert(5);
	b.insert(6);
	b.insert(7);

	b.insert(16);
	b.insert(15);
	b.insert(14);
	b.insert(13);
	b.insert(12);
	b.insert(11);
	b.insert(10);
	b.insert(9);
	b.insert(8);

	b.display();
	cout << endl << endl;

	b.remove(11);
	b.remove(12);






	b.display();
	cout << endl << endl;

	b.remove(7);

	b.display();
	cout << endl << endl;


	return 0;
}