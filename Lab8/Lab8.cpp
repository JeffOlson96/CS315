
#include "time.h"
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <vector>
//#include "BinarySearchTree.h"
#include "Lab8.h"

using namespace std;



vector <int> tokenizer(string input);

int main(int argc, char * argv[])
{	
	string numbers;
	string input_str;
	cout << "Please enter a series of numbers followed by a q to stop\n";
	while (numbers != "q") {
		cin >> numbers;
		input_str.append(numbers + " ");
	}
	//cout << input_str << endl;
	vector <int> input = tokenizer(input_str);

	BinarySearchTree *T = new BinarySearchTree();
	double finish_time;
	double start_time = clock();
	for (int i = 0; i < input.size(); ++i) {
		T->insert_int(input[i]);
		//cout << input[i] << endl;
	}
	int size = T->size();
	T->setTreeRanks(size);
	finish_time = clock();
	double time = (double) (finish_time - start_time)/CLOCKS_PER_SEC;
	
	cout << "inserting took: " << time << " seconds" << endl;
	cout << "number of keys: " << T->size() << endl;
	string c;
	int k;
	
	while (c != "q") {

		cout << "what would you like to do: " << endl;
		cout << "q: to quit, s: to search, d: display the entire index, r: remove a key, k: to search for the Rank, k1: to search for key of a certain rank" << endl;
		cin >> c;
		if (c == "s") {
			cout << "which key would you like to search for?" << endl;
			cin >> k;
			if (T->search_int(k)) {
				cout << k << " is found ! " << endl;
			}

		}
		else if (c == "d") {
			T->printTree();
		}
		else if (c == "r") {
			//tree to string using print function
			int key_remove;
			cout << "what key would you like to remove" << endl;
			cin >> key_remove;
			T->remove(key_remove);
		}
		else if (c == "k") {
			cout << "what Rank would you like to search for" << endl;
			int x;
			cin >> x;
			T->KeyOfRank(x);
		}
		else if (c == "k1") {
			cout << "what Key would you like to search for" << endl;
			int x;
			cin >> x;
			int rank = T->RankOfKey(x);
			cout << "key's rank is: " << rank << endl;
		}
	}
	return 0;
}


vector <int> tokenizer (string input) {
  vector <int> tokens;
  stringstream S;
  S << input;
  int j;
  char c;
  while (S >> c) {
    if (isdigit(c)) {
      S.putback(c);
      S >> j;
      tokens.push_back(j);
    }
  }
  return tokens;
}

