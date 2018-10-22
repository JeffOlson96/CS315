/*
Jeff O
Lab4
Stack/Linked List/Nested List parser
 */

//#include "stack1.cpp"
#include <iostream>
#include <cctype>
#include <typeinfo>//checking type of element
#include <sstream>//for string stream
#include <cstdlib>
#include <stdlib.h>
#include <vector>//for vector storage
#include <string>//for string data structure


using namespace std;

class Stack;

class Node {
public:
	Node(int key1) {
		key = key1;
		tag = 0;
		down = NULL;
		next = NULL;
	}
	
	Node(Node * dptr, Node * nptr) {
		tag = 1;
		down = dptr;
		next = nptr;
	}

	void setTag(int tager) {
		tag = tager;
	}

	void setKey(int k) {
		key = k;
	}

	void setDown(Node * ptr) {
		down = ptr;
	}

	void setNext(Node * ptr) {
		next = ptr;
	}

	int getTag(){
		return tag;
	}

	int getKey(){
		return key;
	}

	Node * getDown() {
		return down;
	}

	Node * getNext() {
		return next;
	}

	int size() {
		if (this == NULL)
			return 0;
		else if (this->tag == 0) return 1;
		else
			return down->size() + next->size();
	}
	void update(Node * L, int j, int k) {
		// update j position with k value
		if (L->isEmpty()) {
			cout << "list is empty" << endl;
			return;
		}
		else if (L->getTag() == 0) {
			L->setKey(k);
			return;
		}
		else {
			int s = L->down->size();
			if(j <= s)
				update(L->down,j,k);
			else
				update(L->next,j-s,k);
		}
	}

	bool isEmpty() {
		return this == NULL;
	}

	void print(int depth) {
		if (this == NULL) return;
		if (tag == 0) {
			cout << "<" << key << ":" << depth << "> " << " ";
		}
		else {
			down->print(depth+1);
			next->print(depth);
		}//end else
	}//end print



private:
	int tag;
	int key;
	Node * down;
	Node * next;
};

class Stack {

private:
	int maxTop;// max stack size = size - 1
	int top;// current top of stack
	Node * values[1000];//element array

public:
	bool IsEmpty() { return top == -1; }
	bool IsFull() { return top == maxTop; }

	Stack(){
		top=-1;
		maxTop=999;
	}
	
	void Push(Node * x) {
		if (IsFull())
			cout << "Error: Stack is full" << endl;
		else {
			values[++top] = x;
		}
	}

	Node * Pop() {//decrements top everytime called, don't call until end
		if (IsEmpty()) {
			cout << " Error: the stack is empty" << endl;
			return NULL;
		}
		else {
			return values[top--];
		}
	}

	Node * Top() {//doesnt decrement top, so use in else case
		if (IsEmpty()) {
			cout << "Error: the stack is empty" << endl;
			return NULL;
		}
		else
			return values[top];
	}
};

int convert(string x){
	return atoi(x.c_str());
}


Node * buildList (vector<string> T) {
	//create new node each case
	
	Stack * S = new Stack();
	for (int i = 0; i < T.size(); ++i) {
		if (T[i] == "[") {
			Node * n = new Node(0);
			n->setTag(-1);
			S->Push(n);
		}
		else if (isdigit(T[i].at(0))) {//creates leaf node with digit
			Node * temp = new Node(convert(T[i]));
			S->Push(temp);
		}
		else { // key is == "]"

			Node * N1 = new Node(S->Pop(), NULL);
			//cout << typeid(S->Top()).name() << endl;
			//Node * check_tag = new Node(n, NULL);
			while (S->Top()->getTag() != -1)
			{
				Node * k1 = new Node(S->Pop(), NULL);
				k1->setNext(N1);
				N1 = k1;
			}
			S->Pop();
			S->Push(N1);
		}
	}
	return S->Top();	
}



vector <string> Tokenizer (string input) {
	vector <string> tokens;
	stringstream S;
	S << input;
	int j;
	char c;
	while (S >> c) {
		if (c == '[')
		{
			tokens.push_back("[");
		}
		else if (c == ']') {
			tokens.push_back("]");
		}
		else if (isdigit(c)) {
			S.putback(c);
			S >> j;
			tokens.push_back(to_string(j));
		}
	}
	return tokens;
}

/*
int main(int argc, char * argv[]) {
	//asks user for input string like "[2,[3,4],6]" and creates list from input
	//update the list: specified by (j,k) where j is position and k is new value
	//printlist from left to right, depth 0-n
	Node* temp = new Node(3);
    Node* temp1 = new Node(5);
    Node* temp2 = new Node(temp1, NULL);
    temp = new Node(temp, temp2);
    temp1 = new Node(new Node(2), NULL);
    temp = new Node(temp, temp1);
    cout << "The list before update: " << endl;
    temp->print(0);
    cout << "The size is " << temp->size() << endl;
    return 0;
}
*/

int main(int argc, char * argv[]) {
	vector <string> v;
	string input;
	//string poop = "poop";
	cout << "input a string that represents a nested list: " << endl;
	getline(cin, input);
	v = Tokenizer(input);//v is set to hold tokens
	//for (int i = 0; i < v.size(); ++i)
		//cout << typeid(v[i]).name() << endl;
	//cout << typeid(poop).name() << endl;
	Node * list = buildList(v);
	//buildList(v);	//
	cout << "\nThe list is:\n";
	list->print(0);
	cout << endl;
	string something_todo;
	while(something_todo != "q"){
		cout << "What would you like to do: " << endl << "'u' to update" << endl << "'q' to quit" << endl;
		getline(cin, something_todo);
		if (something_todo == "u"){
			int a;
			int b;
			cout << "give an element number to change: " << endl;
			cin >> a;
			cout << "give the value to update it to: " << endl;
			cin >> b;
			list->update(list, a, b);
			list->print(0);
			cout << endl;
			something_todo = " ";
		}
		
	}
	return 0;
}


