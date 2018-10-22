/*
Jeff Olson BinarySearchTree Class Number 2
*/


//figure out way to save duplicates data in binarynode, maybe before inserting, searching and then in search
//
//
//

#ifndef LAB_6_BINARYSEARCHTREE_H
#define LAB_6_BINARYSEARCHTREE_H

#include <algorithm>
#include <iostream>
#include <vector>
//#include <fstream>

using namespace std;


class BinaryNode
{
public:
	BinaryNode() {
		left = nullptr;
		right = nullptr;
		word_val = "";
		rowNum[0] = 0;
	}

	BinaryNode(string s, int n) {
		left = nullptr;
		right = nullptr;
		word_val = s;
		rowNum.push_back(n);
	}

	BinaryNode(string s, int n, vector<int> v) {
		left = nullptr;
		right = nullptr;
		word_val = s;
		rowNum = v;
	}

	BinaryNode * leftTree() { return left; }
	BinaryNode * rightTree() { return right; }

	BinaryNode * setLeftTree (BinaryNode * t ) { this->left = t; }
	BinaryNode * setRightTree (BinaryNode * t) {this->right = t; }

	void handle_dup (int n) {
		rowNum.push_back(n);
		//cout << rowNum.size() << endl;
	}
	
	void print_linenumber() {
		for (int i = 0; i < rowNum.size(); ++i) {
			//cout << rowNum.size() << endl;
			cout << rowNum[i] << endl;
		}
	}
	vector<int> rows() {
		return rowNum;
	}
	

	string word() { return word_val; }
	//int& rowNum() { return row; }
private:
	BinaryNode * left; BinaryNode * right;
	string word_val;
	vector <int> rowNum;
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

	void insert (string s, int row) {
		if ( ! search(s))
			root = node_insert(root, s, row);
	}

	bool search (string s) {
		return search_for(root, s);
	}

	int size() {
		return tree_size(root);
	}

	void print_line_num() {
		if (isEmpty())
			cout << "empty tree" << endl;
		else
			print_line_num(root);
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


private:

	BinaryNode * root;

	bool search_for(BinaryNode * root, string s) {
		if (root == nullptr)
			return false;
		else if (root->word() == s)
			return true;
		else if (root->word() < s)
			return search_for(root->rightTree(), s);
		else
			return search_for(root->leftTree(), s);
	}
	
	void print_line_num(BinaryNode * root) {
		for (int i = 0; i < root->rows().size(); ++i) {
			cout << root->rows()[i] << endl;
		}
	}


	BinaryNode * node_insert(BinaryNode * root, string s, int row) {
		if (root == nullptr) {
			//cout << "in if\n";
			vector <int> v;
			v.push_back(row);
			return new BinaryNode(s, row, v);
		}
		else if (root->word() < s) {
			//cout << "root is smaller than s" << endl;
			return root->setRightTree( node_insert(root->rightTree(), s, row ));
		}
		else if (root->word() > s) {
			//cout << "root is bigger than s" << endl;
			return root->setLeftTree( node_insert(root->leftTree(), s, row ));
		}
		else {
			//cout << "duplicate" << endl;
			//duplicate handle case
			root->handle_dup(row);
		}
	}
	
	int tree_size(BinaryNode * root) {
		if (root == nullptr)
			return 0;
		return 1 + tree_size(root->leftTree()) + tree_size(root->rightTree());
	}

	void makeEmpty( BinaryNode *  root )
	{
	  if( root != nullptr )
	    {
	      makeEmpty( root->leftTree() );
	      makeEmpty( root->rightTree() );
	      delete root;
	    }
	  root = nullptr;
	}

	void printTree(BinaryNode * root, ostream & out) const
	{
		if (root != nullptr)
		{
			printTree(root->leftTree(), out);
			cout << "word: "<< root->word() << "  | " << " LineNumbers: ";
			root->print_linenumber();
			printTree(root->rightTree(), out);
		}
	}

	string saveTree(BinaryNode * root, ostream & out) const
	{
		string save_index;
		if (root != nullptr)
		{
			save_index.append(root->word());
			saveTree(root->leftTree(), out);
			saveTree(root->rightTree(), out);
		}
		return save_index;
	}
};

#endif