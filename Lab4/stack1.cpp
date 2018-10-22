
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
//#include "scan.cpp"

using namespace std;

class Stack;

class Node {

public:
Node(int key1){
	key = key1;
	tag = 0;
	down = NULL;
	next = NULL;
}

Node(Node* dptr, Node* nptr) {
	tag = 1;
	down = dptr;
	next = nptr;
}

void setKey(int k) {
	key = k;
}

void setDown(Node* ptr) {
	down = ptr;
}

void setNext(Node* ptr) {
	next = ptr;
}

int getKey() {
	return key;
}

Node* getDown() {
	return down;
}

Node* getNext() {
	return next;
}

int size() {
	if (this == NULL)
	   return 0;
	else if (this->tag == 0) return 1;
	else
	   return down->size() + next->size();
}

void update(int j, int k) {
  // to be completed


  } 

bool isEmpty() {
	  return this == NULL;
  }

void print(int depth) {
	  if (this == NULL) return;
	  if (tag == 0) {
	      cout << "<" << key << ":" << depth << ">  " ;
	      }
	  else {
	     down->print(depth+1);
	     next->print(depth);
	    } // end else
	 } // end print

private:
   int tag;
   int key;
   Node* down;
   Node* next;
};

class Stack {

private:
  int maxTop;// max stack size = size - 1
  int top;// current top of stack
  Node* values[1000];// element array

public:

  bool IsEmpty() { return top == -1; }
  bool IsFull() { return top == maxTop; }

 Stack() {
    top=-1;
    maxTop= 999;
  }

  void Push(Node* x) {
    if (IsFull())  // if stack is full, print error
      cout << "Error: the stack is full." << endl;
    else {
        values[++top]= x;
        }
  }

  Node*  Pop() {
    if (IsEmpty()) { //if stack is empty, print error
      cout << "Error: the stack is empty." << endl;
      return NULL;
    }
    else {
      return values[top--];
    }
  }

  Node* Top() {
    if (IsEmpty()) {
      cout << "Error: the stack is empty." << endl;
      return NULL;
    }
    else
      return values[top];
  }
};

int convert(string x) {
 // converts a string rep of decimal integer to an int
  return atoi(x.c_str());
}

Node* create (vector<string> T) {
return NULL; // to be completed. Takes as input a vector of strings and builds a generalized list
} 

int main(int argc, char* argv[]) {
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

