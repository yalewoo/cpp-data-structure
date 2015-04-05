#include <iostream>

using namespace std;

#include "BTree.h"


int main()
{
	BTree<int> bt(4);

	bt.insert(21);
	bt.insert(48);
	bt.insert(72);
	bt.insert(12);
	bt.insert(22);
	bt.insert(50);
	bt.insert(34);
	bt.insert(42);
	bt.insert(60);
	bt.insert(67);
	bt.insert(89);
	bt.insert(13);
	bt.display();

	cout << "delete 50\n\n";
	bt.remove(50);
	bt.display();
	cout << "delete 72\n\n";
	bt.remove(72);
	bt.display();
	cout << "delete 89\n\n";
	bt.remove(89);
	bt.display();
	cout << "delete 67\n\n";
	bt.remove(67);
	bt.display();

	cout << "delete 48\n\n";
	bt.remove(48);
	bt.display();
	cout << "delete 60\n\n";
	bt.remove(60);
	bt.display();
	cout << "delete 42\n\n";
	bt.remove(42);
	bt.display();
	cout << "delete 22\n\n";
	bt.remove(22);
	bt.display();
	cout << "delete 34\n\n";
	bt.remove(34);
	bt.display();

	cout << "delete 21\n\n";
	bt.remove(21);
	bt.display();



	// int i;
	// for (i = 0; i < 30; ++i)
	// 	bt.insert(i);

	

	printf("233");

	return 0;
}