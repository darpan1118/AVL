#pragma once


#include <iostream>
#include <algorithm>



// Implementation for AVL tree
template <typename Obj>
class AVL
{
public:
	AVL() : rootNode{nullptr}
	{
	}

	AVL(const AVL &rhs) : rootNode{ nullptr }
	{
		rootNode = clone(rhs.rootNode);
	}

	AVL(AVL &&rhs) : rootNode{ rhs.rootNode }
	{
		rhs.rootNode = nullptr;
	}

	~AVL() { deleteTree(); }

	// copy 
	AVL & operator = (const AVL & rhs)
	{
		AVL copy = rhs;
		std::swap(*this, copy);
		return *this;
	}

	// move
	AVL & operator = (AVL && rhs)
	{
		std::swap(rootNode, rhs.rootNode);
		return *this;
	}

	// return smallest item in tree
	const Obj & findMin() const
	{
		ASSERT("Root is null", isEmpty());
		return findMin(rootNode)->Object;
	}


	// return biggest item in tree
	const Obj & findMax() const
	{
		ASSERT("Root is null", isEmpty());
		return findMax(rootNode)->Object;
	}
	
	// returns true if tree contains X
	bool contains(const Obj &x) const 
	{
		return contains(x, rootNode);
	}

	// returns true if tree is empty
	bool isEmpty() const { return (rootNode == nullptr); }

	// deletes the tree
	void deleteTree()
	{
		emptyTree(rootNode);
	}

	// insert in tree, ignoring duplicates
	void insert(const Obj& x)
	{
		insert(x, rootNode);
	}

	// insert in tree, ignoring duplicates
	void insert(Obj && x)
	{
		insert(std::move(x), rootNode);
	}

	// finds and removes X, if not found then do nothing
	void remove(const Obj& x)
	{
		remove(x, rootNode);
	}


	// print tree
	void printTree() const 
	{
		if (isEmpty())
			std::cout << "Tree is empty\n";
		else
			print(rootNode);
	}


private:

	struct Node_AVL
	{
		Obj			Object;
		Node_AVL	*left;
		Node_AVL	*right;
		int			height;


		Node_AVL(const Obj &element, Node_AVL *lt, Node_AVL *rt, int _height = 0) : 
			Object{ element }, left{ lt }, right{ rt }, height{ _height } {};

		Node_AVL(Obj &&element, Node_AVL *lt, Node_AVL *rt, int _height = 0) : 
			Object{ std::move(element) }, left{ lt }, right{ rt }, height{ _height } {};
	};

	static const int ALLOWED_IMBALANCE = 1;

	Node_AVL *rootNode;


	// Internal function to add t into tree
	void insert(const Obj &x, Node_AVL * & t)
	{
		if (t == nullptr)
			t = new Node_AVL{ x, nullptr, nullptr };
		else if (x < t->Object)
			insert(x, t->left);
		else if (t->Object < x)
			insert(x, t->right);

		balanceTree(t);

		/*if (root == nullptr)
			root = new Node_AVL{ t, nullptr, nullptr };
		else if (t < root->Object)
			insert(t, root->left);
		else if (t > root->Object)
			insert(t, root->right);

		balanceTree(root);*/
	}

	// Internal function to add t into tree

	void insert(Obj &&x, Node_AVL * & t)
	{

		if (t == nullptr)
			t = new Node_AVL{ std::move(x), nullptr, nullptr };
		else if (x < t->Object)
			insert(std::move(x), t->left);
		else if (t->Object < x)
			insert(std::move(x), t->right);

		balanceTree(t);
		/*if (root == nullptr)
			root = new Node_AVL{ std::move(t), nullptr, nullptr };
		else if (t < root->Object)
			insert(std::move(t), root->left);
		else if (t > root->Object)
			insert(std::move(t), root->right);

		balanceTree(root);*/
	}

	// Internal function to remove t from tree
	void remove(const Obj &t, Node_AVL * & root)
	{
		if (root == nullptr)
			return;

		if (t < root->Object)
			remove(t, root->left);
		else if (t > root->Object)
			remove(t, root->right);
		else if (root->left != nullptr && root->right != nullptr)
		{
			root->Object = findMin(root->right)->Object;
			remove(root->Object, root->right);
		}
		else
		{
			root = (root->left != nullptr) ? root->left : root->right;
		}

		balanceTree(root);
	}
	
	// balanced the tree to preserve with AVL property
	void balanceTree(Node_AVL * & root)
	{
		if (root == nullptr)
			return;

		if (GetHeight(root->left) - GetHeight(root->right) > ALLOWED_IMBALANCE)
		{
			if (GetHeight(root->left->left) >= GetHeight(root->left->right))
				rotateWithLeftChild(root);
			else
				doubleRotateWithLeftChild(root);
		}
		else if (GetHeight(root->right) - GetHeight(root->left) > ALLOWED_IMBALANCE)
		{
			if (GetHeight(root->right->right) >= GetHeight(root->right->left))
				rotateWithRightChild(root);
			else
				doubleRotateWithRightChild(root);
		}


		root->height = max(GetHeight(root->left), GetHeight(root->right)) + 1;

	}

	// find and returns smallest value, null if element is not found
	Node_AVL* findMin(Node_AVL * root) const
	{
		if (root == nullptr)
			return nullptr;
		if (root->left == nullptr)
			return root;
		
		return findMin(root->left);

	}

	// find and returns biggest value, null if element is not found
	Node_AVL* findMax(Node_AVL * root) const
	{
		if (root != nullptr)
		{
			while (root->right != nullptr)
				root = root->right;
		}

		return root;
	}


	// returns true if tree contains X else false
	bool contains(const Obj &x, Node_AVL * root)  
	{
		if (root == nullptr)
		{
			return false;
		}
		else if (x < root->Object)
			return contains(x, root->left);
		else if (x > root->Object)
			return contains(x, root->right);
		else
			return true;
	}

	// deletes tree
	void emptyTree(Node_AVL * & root)
	{
		if (root != nullptr)
		{
			emptyTree(root->left);
			emptyTree(root->right);
			delete root;
		}
		root = nullptr;
	}

	// Printing in sorted order
	void print(Node_AVL * root) const
	{
		if (root != nullptr)
		{
			print(root->left);
			std::cout << root->Object << std::endl;
			print(root->right);
		}
	}

	// clone sub-Trees
	Node_AVL* clone(Node_AVL * root) const
	{
		if (root == nullptr)
			return nullptr;
		return new Node_AVL{ root->Object, clone(root->left), clone(root->right), root->height};
	}

	// Height node and -1 if null
	int GetHeight(Node_AVL * root) const
	{
		return ((root == nullptr) ? -1 : root->height);
	}

	int max(int lhs, int rhs) const
	{
		return (lhs > rhs) ? lhs : rhs;
	}


	void rotateWithRightChild(Node_AVL * & k1)
	{
		Node_AVL *k2 = k1->right;
		k1->right = k2->left;
		k2->left = k1;
		k1->height = max(GetHeight(k1->left), GetHeight(k1->right)) + 1;
		k2->height = max(GetHeight(k2->right), k1->height) + 1;
		k1 = k2;
	}

	void rotateWithLeftChild(Node_AVL * & k2)
	{
		Node_AVL *k1 = k2->left;
		k2->left = k1->right;
		k1->right = k2;
		k2->height = max(GetHeight(k2->left), GetHeight(k2->right)) + 1;
		k1->height = max(GetHeight(k1->left), k2->height) + 1;
		k2 = k1;
	}


	void doubleRotateWithLeftChild(Node_AVL * & k3)
	{
		rotateWithRightChild(k3->left);
		rotateWithLeftChild(k3);
	}

	void doubleRotateWithRightChild(Node_AVL * & k4)
	{
		rotateWithLeftChild(k4->right);
		rotateWithRightChild(k4);
	}
};