#include <iostream>
#include <cstdlib>

#include "SplayBinTree.h"

using namespace std;

int main()
{
	SplayBinTree<int> b;

	for (int i = 32; i >=1; --i)
	{
		b.insert(i);
	}
	
	// b.remove(32);
	// b.remove(4);

	char c;
	for (int i = 32; i >=1; --i)
	{
		b.display();

		cout << "Press Enter to Search " << i;
		while ((c = getchar()) != '\n')
			;
		b.search(i);
		system("cls");
	}
	b.search(1);

	b.display();

	return 0;
}