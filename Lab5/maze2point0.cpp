/*
Jeff Olson queue/shortest path BFS
*/

#include <cstdlib>
#include <iostream>
#include <deque>
#include <queue>
#include "EasyBMP.h"
#include "EasyBMP.cpp"

//const int MSIZE = 100000;

using namespace std;


/*
class Point {
private:
	int x;
	int y;
	int idx_num;
public:

	Point() {
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

	void setidxnum(int image_width) {
		idx_num = (x * image_width) + y;
	}

	int getidxnum() {
		return idx_num;
	}
};


void checkneighbors(Point * u, BMP * In, visited[],) {

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

}

void BFS (BMP & In, Point * & start, Point * & target, int count) {
	int picwidth = In.TellWidth();
	start->setidxnum(picwidth);
	queue <Point> Q;
	Q.push(*start);
	count++;
	Point * u = new Point();
	//RangedPixelToPixelCopy(In, 0, In.TellWidth(), In.TellHeight(), 0, Out, 0, 0);

	int parents[MSIZE];
	int distance[MSIZE];//hold distance 
	bool visited[MSIZE];//hold bool value for point

	for (int i = 0; i < MSIZE; ++i){//set visited false for all vertices
		visited[i] = false;
	}

	for (int i = 0; i < MSIZE; ++i){//set visited false for all vertices
		cout << visited[i] << endl;
	}

	int start_index = (start->getX() * In.TellWidth()) + start->getY();//start point in idx form
	cout << start_index << endl;
	visited[start_index] = true;//find start index in 1d array
	
	for (int i = 0; i < MSIZE; ++i){//sets d[u] to max for all others
		distance[i] = MSIZE;
	}
	distance[start_index] = 0;//setting d[s] = 0

	int target_index = (target->getX() * In.TellWidth()) + target->getY();//find targetpoint in index form
	cout << target_index << endl;
	while (Q.size() != 0 && !visited[target_index]) {
		*u = Q.front();//u = to front of queue
		u->setidxnum(picwidth);
		//checkneighbors(u, In, visited[])
		vector <Point> neighbors;//vector used for storing points
		Point * neighborN = new Point(u->getX(), u->getY()+1);//initialize neighbors with coordinates
		neighbors.push_back(*neighborN);
		Point * neighborS = new Point(u->getX(), u->getY()-1);
		neighbors.push_back(*neighborS);
		Point * neighborE = new Point(u->getX()+1, u->getY());
		neighbors.push_back(*neighborE);
		Point * neighborW = new Point(u->getX()-1, u->getY());
		neighbors.push_back(*neighborW);
		for (int i = 0; i < neighbors.size(); ++i) {
		//	cout << neighbors[i]->getX() << " , " << neighbors[i]->getY() << endl;
			neighbors[i].setidxnum(picwidth);
			if (!visited[neighbors[i].getidxnum()]) {
				visited[neighbors[i].getidxnum()] = true;
				distance[neighbors[i].getidxnum()] = distance[u->getidxnum()] + 1;
				parents[neighbors[i].getidxnum()] = u->getidxnum();
				Q.push(neighbors[i]);
				count++;
			}//endif
		}//endfor
		//cout << "still in WEILL" << endl;
		//cout << "size: " << Q.size() << "visited: " << visited[target_index] << endl;
	}//endwhile
	//


	if (visited[target_index]) {
		int foo_x = target_index/picwidth; 
		int foo_y = target_index%picwidth;
		Point * v = new Point(foo_x, foo_y);
		v->setidxnum(picwidth);
		while (v->getidxnum() != start->getidxnum()) {
			//set color of c to red
			RGBApixel temp = In.GetPixel(v->getX(), v->getY());
			temp.Red = 255; temp.Green = 0; temp.Blue = 0;
			In.SetPixel(v->getX(), v->getY(), temp);
			v->setidxnum(picwidth);
			cout << "still in WHILE" << endl;
		}
		In.WriteToFile("BFS.bmp");
		for (int i = 0; i < MSIZE; ++i)
		{
			cout << distance[target_index] << endl;
		}
		cout << "count: " << endl;
		//cout << count << endl;
	}

	else
		cout << "no path from s to t" << endl;
}//end BFS
*/	

//BFS without point class using ints
void BFS (BMP & In, int start, int target, int count) {
	int MSIZE;
	queue <int> Q;//init queue
	Q.push(start);//insert start
	count++;
	//RangedPixelToPixelCopy(In, 0, In.TellWidth(), In.TellHeight(), 0, Out, 0, 0);
	int picwidth = In.TellWidth();//get wid
	int picheight = In.TellHeight();//get hei
	MSIZE = picwidth * picwidth;//set msize to max value
	int parents[MSIZE + picwidth];//hold parents
	int distance[MSIZE + picwidth];//hold distance 
	bool visited[MSIZE + picwidth];//hold bool value for point

	for (int i = 1; i < MSIZE; ++i) {//set visited false for all vertices
		visited[i] = false;
	}

	cout << start << endl;
	visited[start] = true;//find start index in 1d array
	
	for (int i = 1; i < MSIZE; ++i) {//sets d[u] to max for all others
		distance[i] = MSIZE * MSIZE;
	}
	distance[start] = 0;//setting d[s] = 0

	//Grid[MSIZE][MSIZE];
	//set black spaces as visited
	for (int i = 0; i < picwidth-1; ++i)
		for (int j = 0; j < picheight-1; ++j)
		{
			RGBApixel b_pixel = In.GetPixel(i,j);
			int color_num = b_pixel.Red + b_pixel.Green + b_pixel.Blue;
			if (color_num < 127) {
				int black_space = i + j;
				visited[black_space];
			}
		}


	cout << "Target: " << target << endl;
	while (Q.size() != 0 && !visited[target]) {
		int u = Q.front();//u = to front of queue
		Q.pop();
		cout << "u: " << u << endl;
		//checkneighbors(u, In, visited[])
		//make neighbors
		vector <int> neighbors;
		int neighborN = u - picwidth;
		neighbors.push_back(neighborN);
		int neighborS = u + picwidth;
		neighbors.push_back(neighborS);
		int neighborW = u - 1;
		neighbors.push_back(neighborW);
		int neighborE = u + 1;
		neighbors.push_back(neighborE);

		for (int i = 0; i < neighbors.size(); ++i) {
		//	cout << neighbors[i]->getX() << " , " << neighbors[i]->getY() << endl;
			//neighbors[i].setidxnum(picwidth);
			if (!visited[neighbors[i]]) {
				visited[neighbors[i]] = true;
				distance[neighbors[i]] = distance[u] + 1;
				parents[neighbors[i]] = u;
				Q.push(neighbors[i]);
				count++;
			}//endif
		}//endfor
		//cout << "still in WEILL" << endl;
		//cout << "size: " << Q.size() << "visited: " << visited[target_index] << endl;
	}//endwhile
	//


	if (visited[target]) {
		int temp1 = target;
		while (temp1 != start) {
			//set color of c to red
			int k = temp1/picwidth;
			int l = temp1%picwidth;
			RGBApixel temp = In.GetPixel(k, l);
			temp.Red = 255; temp.Green = 0; temp.Blue = 0;
			In.SetPixel(k, l, temp);
			temp1 = parents[temp1];
			cout << "still in WHILE" << endl;
		}
		In.WriteToFile("BFS.bmp");//write to file
		for (int i = 0; i < MSIZE; ++i)//cout d[t] & count
		{
			cout << distance[target] << endl;
		}
		cout << "count: " << endl;
		cout << count << endl;
	}

	else
		cout << "no path from s to t" << endl;
}//end BFS





	




void BW(BMP & Output) {
	int picWidth = Output.TellWidth();
	int picHeight = Output.TellHeight();
	Output.SetBitDepth(8); //compression happens here
	for (int i = 0; i < picWidth-1; ++i)
	 	for (int j = 0; j < picHeight-1; ++j) {
	 		RGBApixel temp = Output.GetPixel(i,j);
	 		temp.Red = 255; temp.Green = 0; temp.Blue = 0;
	 		int col = 0.1* temp.Blue + 0.6*temp.Green +0.3* temp.Red;
	 		if (col > 127) {
	 			temp.Red = 255;
	 			temp.Blue = 255;
	 			temp.Green = 255;
	 		}
	 	}
 }




int main (int argc, char * argv[]) {

	BMP In;
	In.ReadFromFile(argv[1]);
	//Point * start = new Point(3, 3);
	//Point * target = new Point(38, 74);
	int startx; 
	int targetx;
	int starty; 
	int targety;
	cout << "where would you like to start: \n";
	cout << "x: " << endl;
	cin >> startx;
	cout << "y: " << endl;
	cin >> starty;

	cout << "where would you like to go: \n";
	cout << "x: " << endl;
	cin >> targetx;
	cout << "y: " << endl;
	cin >> targety;
	int picwid = In.TellWidth();
	int start = (startx * picwid) + starty;
	int target = (targetx * picwid) + targety;


	int count = 0;
	BW(In);
	BFS(In, start, target, count);
	return 0;

}