/*
Binary Search Tree
Jeff Olson
Lab6
*/

#include "time.h"
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <vector>
//#include "BinarySearchTree.h"
#include "BSTree.h"

using namespace std;



//builds tree
void buildTree (ifstream & in)
{//gets ifstream object in, reads from it into stringstream and then appends SS to regular string.
	BinarySearchTree *T = new BinarySearchTree();
	int row = 1;
	stringstream S;
	S << in.rdbuf();
	string x;
	double finish_time;
	double start_time = clock();
	while (S >> x) {
		//row = findrownum(in, x);
		T->insert(x, row);
	}
	finish_time = clock();
	double time = (double) (finish_time - start_time)/CLOCKS_PER_SEC;
	
	cout << "inserting took: " << time << " seconds" << endl;
	cout << "number of words: " << T->size() << endl;
	string c;
	while (c != "q") {

		cout << "what would you like to do: " << endl;
		cout << "q: to quit, s: to search, d: display the entire index, r: save index to file" << endl;
		cin >> c;
		if (c == "s") {
			cout << "which word would you like to search for?" << endl;
			cin >> c;
			if (T->search(c)) {
				cout << c << " is found in the text at line: " << endl;
				T->print_line_num();
			}

		}
		else if (c == "d") {
			T->printTree();
		}
		else if (c == "r") {
			//tree to string using print function
			cout << "index saved to txt file 'output.txt'" << endl;
			string index = T->saveTree();
			ofstream out("output.txt");
			out << index;
			out.close();
		}	
	}
}



int main(int argc, char * argv[])
{	
	string file;
	ifstream inFile;
	cout << "Please enter a file name\n";
	cin >> file;
	inFile.open(file.c_str());
	buildTree(inFile);
	return 0;
	
}
