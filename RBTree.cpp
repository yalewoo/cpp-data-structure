#include <iostream>

#include "RBTree.h"

int main()
{
	RBT<int> rb;

	rb.insert(12);
	rb.insert(1);
	rb.insert(9);
	rb.insert(2);
	rb.insert(0);
	rb.insert(11);
	rb.insert(7);
	rb.insert(19);
	rb.insert(4);

	rb.display();

	rb.remove(4);
	rb.display();
	

	return 0;
}