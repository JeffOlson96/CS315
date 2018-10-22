/*
Jeff Olson
CS315
Lab1
*/

#include <iostream>
#include <vector>
#include <cstdlib>
#include <string>

using namespace std;

vector<string> gray(int n);

int main()
{
  int temp;
  cout << "hit me with a numba" << endl;
  cin >> temp;
  vector <string> out = gray(temp);
  for (int i = 0; i < out.size(); i++ )
    cout << out[i] << endl;
  
}

vector<string> gray (int n)
{
  vector <string> v;
  vector <string> u;
  v.push_back("0");
  v.push_back("1");
  if (n == 1){
    //v.push_back("0");
    //v.push_back("1");
    return v;
  }
  else if (n > 1)
  {
    v = gray(n-1);//recursive call to get base case
    int size = v.size();
    for (int i = 0; i < size; ++i)//first for loop to add zeros
      {
	u.push_back(v[i] + "0");
	//cout << v[i] << endl;
      }
    for (int i = 0; i < size; ++i)//second to add ones
      {
	u.push_back(v[i] + "1");
	//cout << u[i] << endl;
      }
    return u;
   } 
  //return u;
}
