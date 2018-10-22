#include "time.h"
#include <string>
#include <stdio.h>
#include <ctype.h>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include "AvlTree.h"
//#include "MyAVLTree.h"

using namespace std;

bool buildTree(ifstream & in, AvlTree<string> & T);
vector <string> tokenizer(string input);
string clean (string n, int & word_count);


int main (int argc , char * argv[]) {
	//building file
	AvlTree<string> T;
	string file;
	ifstream inFile;
	cout << "Please enter a file name\n";
	cin >> file;
	inFile.open(file.c_str());
	cout << "file: " << file << endl;
	if (!inFile.is_open()) {
		cout << "file doesn't exist please try again" << endl;
		return 0;
	}

	//user interface
	string treesave;
	buildTree(inFile, T);
	int _do;
	long long int search_count = 0;//use long long cause it was huge but now could probably use a 32-int, but okay
	while (_do != 4) {
		cout << "Options: (1) display index, (2) search, (3) save index, (4) quit" << endl;
		cin >> _do;
		if (_do == 1) {
			T.printTree();
			cout << "Size of Tree: " << T.size() << endl;
		}
		else if (_do == 2) {
			string _searching;
			cout << "what would you like to search for: " << endl;
			cin >> _searching;
			if (T.contains(_searching, search_count)) {
				cout << "Word found at: " << endl;
				cout << "Number of key comparisons for Search: " << search_count << endl; 
			}
			else
				cout << "unable to find word, please try again" << endl;
		}
		else if (_do == 3) {
			cout << "index saved to txt file 'output.txt'" << endl;
			treesave = T.saveTree(cout, treesave);
			ofstream out ("output.txt");
			out << treesave;
			out.close();
		}
		else
			break;
	}
	return 0;
}

string clean (string n, int & word_count) {
	//clean gets rid of the punctuation and spaces in the words 
	string give_back;
	for (int i = 0; i <n.length(); i++) {
		char c = n[i];
		if (isalpha(c)) {
			give_back.push_back(c);
		}
		else if (c == '-') {
			if (give_back.back() == '-') {
				give_back.pop_back();
				break;
			}
			else
				give_back.push_back(c);
		}
		else if (c == '`') {
			give_back.push_back(c);
		}
		else if (c == ' ') {
			return give_back;
		}
		else
			break;
	}
	word_count++;
	return give_back;
}

bool buildTree(ifstream & in, AvlTree<string> & T) {
	stringstream S;
	int count = 0;
	int comp_count = 0;
	S << in.rdbuf();
	string x;
	string give;
	double finish_time;
	double start_time = clock();
	while (S >> x) {
		give = clean(x, count);// adds extra time to clock but need clean before each word
		comp_count = T.insert(give, comp_count);
	}
	finish_time = clock();
	double time = (double) (finish_time - start_time)/CLOCKS_PER_SEC;
	cout << "Number of Words: " << count << endl;
	cout << "Building the AVL tree index took: " << time << " seconds to build the tree" << endl;
	cout << "Number of distinct words: " << T.size() << endl;
	cout << "Number of key comparisons: " << comp_count << endl;
	cout << "Height of the Tree: " << T.height() << endl;
	return true;
}