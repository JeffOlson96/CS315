/*
Jeff Olson BinarySearchTree Class Number 2
*/


//Lab8 BST updated with findMin, remove, RankofKey and KeyOfRank
//insert, search and inorderTrav are borrowed from Lab6
//
//

#ifndef LAB_6_BINARYSEARCHTREE_H
#define LAB_6_BINARYSEARCHTREE_H

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;


class BinaryNode
{
public:
	BinaryNode() {
		left = nullptr;
		right = nullptr;
		data = 0;
		word_val = "";
		rank = 0;
	}

	BinaryNode(string s) {
		left = nullptr;
		right = nullptr;
		data = 0;
		word_val = s;
		rank = 0;
	}

	
	BinaryNode(int x_data, int nu_rank) {
		left = nullptr;
		right = nullptr;
		data = x_data;
		word_val = "";
		rank = nu_rank;

	}

	BinaryNode * leftTree() { return left; }
	BinaryNode * rightTree() { return right; }

	BinaryNode * setLeftTree (BinaryNode * t ) { this->left = t; }
	BinaryNode * setRightTree (BinaryNode * t) {this->right = t; }

	
	int getRank () {return rank;}

	void setRank(int nu_rank) {
		rank = nu_rank;
	}

	int getdata() { return data;}
	string word() { return word_val; }
	//int& rowNum() { return row; }
private:
	BinaryNode * left; BinaryNode * right;
	int data;
	string word_val;
	int rank;
};


class BinarySearchTree
{
public:
	BinarySearchTree () {
		root = nullptr;
	}

	~BinarySearchTree()
	{
		makeEmpty();
	}

	void makeEmpty()
	{
		makeEmpty( root );
	}

	void insert (string s) {
		if ( ! search_for_string(root, s))
			root = node_insert(root, s);
	}

	void insert_int (int s) {
		if ( ! search_for_int(root, s)) {
			int prev_rank = tree_size(root);
			root = node_insert_int(root, s, prev_rank);
		}
	}

	bool search_string (string s) {
		return search_for_string(root, s);
	}

	bool search_int (int s) {
		if(search_for_int(root, s)) {
			return true;
		}
		else
			return false;
	}

	void trav_to_val (int s) {
		if (!search_for_int(root, s))
			cout << "empty tree" << endl;
		else
			root = trav_to_value(root, s);
	}

	int size() {
		return tree_size(root);
	}

	void setTreeRanks(int treesize) {
		if (isEmpty())
			cout << "empty tree" << endl;
		else
		{
			int rank = 0;
			setTreeRanks(root, treesize, rank);
		}
	}


	void printTree(ostream & out = cout) const {
		if (isEmpty() )
			cout << "Empty Tree" << endl;
		else
			printTree(root, out);
	}

	string saveTree(ostream & out = cout) const {
		if (isEmpty() )
			cout << "Empty Tree" << endl;
		else
			return saveTree(root, out);
	}

	bool isEmpty() const
	{
		return root == nullptr;
	}

	int RankOfKey(int s) {
		//takes input as a key x, returns rank;
		if (isEmpty())
			cout << "Empty Tree" << endl;
		else
			root = trav_to_value(root, s);
			return RankOfKey(root);
	}
	void KeyOfRank(int k) {
		if (KeyOfRank(root, k))
			return;
	}

	void delete_min() {
		if (isEmpty()) {cout << "Empty Tree" << endl;}
		else
			delete_min(root);
	}

	void remove (int key_remove) {
		if (isEmpty()) {cout << "Empty Tree" << endl;}
		else
			int_remove(root, key_remove);
	}

private:

	BinaryNode * root;

	bool search_for_string(BinaryNode * root, string s) {
		//searches for string saved in binarynodes
		if (root == nullptr)
			return false;
		else if (root->word() == s)
			return true;
		else if (root->word() < s)
			return search_for_string(root->rightTree(), s);
		else
			return search_for_string(root->leftTree(), s);
	}

	bool search_for_int(BinaryNode * root, int s) {
		//searches for int data saved in nodes
		if (root == nullptr)
			return false;
		else if (root->getdata() == s)
			return true;
		else if (root->getdata() < s)
			return search_for_int(root->rightTree(), s);
		else
			return search_for_int(root->leftTree(), s);
	}
	

	BinaryNode * trav_to_value(BinaryNode * root, int s) {
		//traverses to specific node
		if (root != nullptr) {
			if (root->getdata() == s) {
				return root;
			}
			else {
				trav_to_value(root->leftTree(), s);
				trav_to_value(root->rightTree(), s);
			}
		}
	}


	BinaryNode * node_insert(BinaryNode * root, string s) {
		//insert a node
		if (root == nullptr) {
			//cout << "in if\n";
			return new BinaryNode(s);
		}
		else if (root->word() < s) {
			//cout << "root is smaller than s" << endl;
			return root->setRightTree( node_insert(root->rightTree(), s));
		}
		else if (root->word() > s) {
			//cout << "root is bigger than s" << endl;
			return root->setLeftTree( node_insert(root->leftTree(), s));
		}
		else {
			//cout << "duplicate" << endl;
			//duplicate handle case
			//root->handle_dup(row);
		}
	}

	BinaryNode * node_insert_int(BinaryNode * root, int s, int prev_rank) {
		//insert a node
		if (root == nullptr) {
			return new BinaryNode(s, prev_rank);
		}
		else if (root->getdata() < s) {
			//cout << "root is smaller than s" << endl;
			return root->setRightTree( node_insert_int(root->rightTree(), s, --prev_rank));
		}
		else if (root->getdata() > s) {
			//cout << "root is bigger than s" << endl;
			return root->setLeftTree( node_insert_int(root->leftTree(), s, ++prev_rank));
		}
		else {
			//do nothing
		}
	}
	
	int tree_size(BinaryNode * root) {
		//recursively find treesize
		if (root == nullptr)
			return 0;
		return 1 + tree_size(root->leftTree()) + tree_size(root->rightTree());
	}

	void makeEmpty( BinaryNode *  root )
	{//make tree empty
	  if( root != nullptr )
	    {
	      makeEmpty( root->leftTree() );
	      makeEmpty( root->rightTree() );
	      delete root;
	    }
	  root = nullptr;
	}

	void printTree(BinaryNode * root, ostream & out) const
	{//does in order print of tree
		if (root != nullptr)
		{
			printTree(root->leftTree(), out);
			cout << "data: "<< root->getdata() << "  | " << " ThisNode'sRank: " << root->getRank() << endl;
			//root->print_linenumber();
			printTree(root->rightTree(), out);
		}
	}

	
	void setTreeRanks(BinaryNode * root, int treesize, int &prev_rank)
	{//setranks
		if (root != nullptr)
		{
			int leftsize = tree_size(root->leftTree());
			root->setRank(leftsize+prev_rank);
			prev_rank = root->getRank();
			setTreeRanks(root->leftTree(), treesize, prev_rank);
			setTreeRanks(root->rightTree(), treesize, prev_rank);
		}
	}
	

	string saveTree(BinaryNode * root, ostream & out) const
	{//save tree to string, but should be changed to ostream object
		string save_index;
		if (root != nullptr)
		{
			save_index.append(root->word());
			saveTree(root->leftTree(), out);
			saveTree(root->rightTree(), out);
		}
		return save_index;
	}

	int RankOfKey(BinaryNode * & root) const
	{//returns the rank of a certain key in the BST
		if (root != nullptr) {
			return root->getRank();
		}
		return 0;
	}

	bool KeyOfRank(BinaryNode * root, int k) {
		//returns key of a certain rank
		if (root != nullptr && root->getRank() != k) {
			KeyOfRank(root->leftTree(), k);
			KeyOfRank(root->rightTree(), k);
		}
		else if (root != nullptr && root->getRank() == k) {
			cout << "the rank you searched for is this key: " << root->getdata() << endl;
			return true;
		}
		else
			return false;			
	}

	void delete_min(BinaryNode * root) {
		if (root != nullptr) {
			delete_min(root->leftTree());
			//delete root;
		}
		else
			delete root;
	}

	
	void int_remove (BinaryNode * root, int key_remove) {
		if (search_for_int(root, key_remove)) {
			root = trav_to_value(root, key_remove);
			if (root != nullptr) {
				if (root->leftTree() == nullptr && root->rightTree() == nullptr) {
					delete root;
				}
				else if (root->leftTree() != nullptr && root->rightTree() != nullptr) {

				}

			}
				
		}
	}	
};

#endif