# AVL Tree

AVL tree is a type of BST in which for every node the difference between height of left and right subtrees is between -1 to 1.  Whenever this property is violated we have to balance the tree. There are 4 ways in which violation can occur:
1. Insertion into left subtree of left child
2. Insertion into right subtree of left child
3. Insertion into left subtree of right child
4. Insertion into right subtree of right child

For case 1 and 3, we can single rotation to balance the tree, whereas, for case 2 and 4 we use double rotation to balance the tree.


Whenever we insert or remove a node from tree we have to check if the balance is preserved. If not, then we have to use appropriate rotation to balance it.
