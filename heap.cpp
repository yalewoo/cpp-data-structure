#include <iostream>
#include "Heap.h"

using namespace std;



int main()
{
	Heap<int> a(10);
	a.insert(0, 2);
	a.insert(0, 3);
	a.insert(0, 7);
	a.insert(0, 4);
	a.insert(0, 4);
	a.insert(0, 5);
	a.insert(0, 9);
	a.insert(0, 3);
	a.print();
	// a.sort();
	// a.print();
	//a.heapify(a.size());
	a.heapsort(a.size());
	a.print();
	

	return 0;
}
