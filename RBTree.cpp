#include <iostream>

#include "RBTree.h"

int main()
{
	RBT<int> rb;

	rb.insert(12);	rb.display();
	rb.insert(1);	rb.display();
	rb.insert(9);	rb.display();
	rb.insert(2);	rb.display();
	rb.insert(0);	rb.display();
	rb.insert(11);	rb.display();
	rb.insert(7);	rb.display();
	rb.insert(5);	rb.display();
	rb.insert(4);	rb.display();

	rb.display();

	rb.remove(12);	rb.display();
	rb.remove(1);	rb.display();
	rb.remove(9);	rb.display();
	rb.remove(2);	rb.display();
	rb.remove(0);	rb.display();
	rb.remove(11);	rb.display();
	rb.remove(7);	rb.display();
	rb.remove(5);	rb.display();
	rb.remove(4);	rb.display();

	rb.display();
	

	return 0;
}