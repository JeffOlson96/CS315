/*
Jeff Queue class/maze BFS
*/

#include "EasyBMP.h"
#include "EasyBMP.cpp"
#include <cstdlib>
#include <iostream>


const int MSIZE = 10000;

using namespace std;


class Point {
private:
	int x;
	int y;

public:

	Point(){
		x = 0;
		y = 0;
	}

	Point(int x_cor, int y_cor) {
		x = x_cor;
		y = y_cor;
	}
	void setX(int x2) {
		x = x2;
	}

	int getX() {
		return x;
	}

	void setY(int y2) {
		y = y2;
	}

	int getY() {
		return y;
	}
};



class queue {
private:
	Point * Q[MSIZE];
	int front;
	int rear;
	int size;
	

public:
	queue() {
		front = 0;
		rear = 0;
		size = 0;
		for (int i = 0; i < MSIZE; ++i)
			Q[i] = 0;
	}
	/*
	void setMSIZE (int ms){
		MSIZE = ms;
	}

	int getMSIZE () {
		return MSIZE;
	} 
	*/
	void setFront (int f) {
		front = f;
	}

	int getFront () {
		return front;
	}

	void setRear (int r) {
		rear = r;
	}

	int getRear () {
		return rear;
	}

	int getSize() {
		return size;
	}

	bool isEmpty() {
		return (size == 0);
	}

	bool isFull() {
		return (size == MSIZE);
	}

	void insert(Point * x) {
		if (!isFull()) {
			size++;
			if (rear == MSIZE) {
				rear = 0;
			}
			Q[rear++] = x;
		}
	}

	Point * Delete() {
		if (!isEmpty()) {
			front++;
			if (front == MSIZE) {
				front = 0;
			}
			size--;
			return Q[front];
		}
	}
};


void checkneighbor(vector<Point> p, queue * Q, visited[MSIZE]){
	//takes vector of points and checks each point to visited
}


/*

void BFS (BMP & In, Point * start, Point * target, int count) {
	queue * Q = new queue();
	
	Q->insert(start);
	count++;
	Point * u = new Point();
	Point * temp = new Point();//"v", temp for holding all vertices

	int parent[MSIZE];
	int distance[MSIZE];//hold distance 
	bool visited[MSIZE];//hold bool value for point
	for (int i = 0; i < MSIZE; ++i){
		visited[i] = false;
	}

	int start_index = (start->getX() * In.TellWidth()) + start->getY();
	visited[start_index] = true;
	
	for (int i = 0; i < MSIZE; ++i){
		distance[i] = MSIZE;
	}
	distance[start_index] = 0;
	
	int target_index = (target->getX() * In.TellWidth()) + target->getY();
	while (!Q->isEmpty() && !visited[target_index]) {
		u = Q->Delete();//make u equal to front of queue
		if (!visited[((u->getX() * In.TellWidth()) + u->getY()) + 1])//check v to right
		{
			visited[((u->getX() * In.TellWidth()) + u->getY()) + 1] = true;
			distance[((u->getX() * In.TellWidth()) + u->getY()) + 1] = distance[((u->getX() * In.TellWidth()) + u->getY())];
			parent[((u->getX() * In.TellWidth()) + u->getY()) + 1] = u;
			Q->insert(temp);
			count++;
		}

		if (!visited[((u->getX() * In.TellWidth()) + u->getY()) - 1])//check v to left
		{
			visited[((u->getX() * In.TellWidth()) + u->getY()) - 1] = true;
			distance[((u->getX() * In.TellWidth()) + u->getY()) - 1] = distance[((u->getX() * In.TellWidth()) + u->getY())];
			parent[((u->getX() * In.TellWidth()) + u->getY()) - 1] = u;
			Q->insert(temp);
			count++;
		}

		if (!visited[((u->getX() * In.TellWidth()) + u->getY()) + In.TellWidth()])//check v to down
		{
			visited[((u->getX() * In.TellWidth()) + u->getY()) + In.TellWidth()] = true;
			distance[((u->getX() * In.TellWidth()) + u->getY()) + In.TellWidth()] = distance[((u->getX() * In.TellWidth()) + u->getY())];
			parent[((u->getX() * In.TellWidth()) + u->getY()) + In.TellWidth()] = u;
			Q->insert(temp);
			count++;
		}

		if (!visited[((u->getX() * In.TellWidth()) + u->getY()) - In.TellWidth()])//check v to up
		{
			visited[((u->getX() * In.TellWidth()) + u->getY()) - In.TellWidth()] = true;
			distance[((u->getX() * In.TellWidth()) + u->getY()) - In.TellWidth()] = distance[((u->getX() * In.TellWidth()) + u->getY())];
			parent[((u->getX() * In.TellWidth()) + u->getY()) - In.TellWidth()] = u;
			Q->insert(temp);
			count++;
		}

	}//end while
	if visited[target_index] {
		for (int i = 0; i < MSIZE; ++i) {
			v = target;
		}
		while (v->getZ() != s->getZ()) {
			//set color of c to red
			RGBApixel temp = In.GetPixel(v->getX(), v->getY());
			temp.Red = 255; temp.Green = 0; temp.Blue = 0;
			In.SetPixel(v->getX(), v->getY(), temp)
			v = p[v];
		}
		In.WriteToFile("BFS.bmp");
		for (int i = 0; i < MSIZE; ++i)
		{
			cout << d[t] << endl;
		}
		cout << "count: " << endl;
		cout << count << endl;
	}

	else
		cout << "no path from s to t" << endl;
}//end BFS

*/

void BW(BMP & Output) {
	int picWidth = Output.TellWidth();
	int picHeight = Output.TellHeight();
	Output.SetBitDepth(1); //compression happens here
	for (int i = 0; i < picWidth-1; ++i)
	 	for (int j = 0; j < picHeight-1; ++j) {
	 		int col = 0.1* Output(i, j)->Blue + 0.6*Output(i,j)->Green +0.3* Output(i,j)->Red;
	 		if (col > 127) {
	 			Output(i,j)->Red = 255;
	 			Output(i,j)->Blue = 255;
	 			Output(i,j)->Green = 255;
	 		}
	 	}
 }

int main (int argc, char * argv[]) {

	BMP & In;
	In.ReadFromFile(argv[2])
	Point * start = new point(3, 3);
	Point * target = new point(38, 74);
	int count = 0;
	BW(In);
	BFS(In, start, target, count);
}



