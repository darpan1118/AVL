#include "AVL.h"


int main()
{
	AVL<int> t;

	t.insert(2);
	t.insert(4);
	t.insert(1);
	t.insert(6);
	t.insert(2+14);
	t.insert(8);
	t.insert(18);

	



	AVL<int> t1{ t };
	t1.remove(1);
	t1.remove(6);
	t1.insert(1 + 6);

	std::cout << "\nprinting t\n";
	t.printTree();

	std::cout << "\nprinting t1\n";

	t1.printTree();



	getchar();
	return EXIT_SUCCESS;
}