/*
Jeff Olson
CS315
Lab1
*/

#include <iostream>

using namespace std;

long long int exp_rec(long long int x, long long int n);

int main()
{
  int temp;
  int exp;
  cout << "hit me with a numba" << endl;
  cin >> temp;
  cout << "hit me with an exponent" << endl;
  cin >> exp;
  cout << exp_rec(temp, exp) << endl;
  
}

long long int exp_rec(long long int x, long long int n)
{
  if (n == 0) return 1;
  else if (n == 1) return x;
  else if (n%2 == 0)
    return exp_rec(x*x, n/2);
  else return x * exp_rec(x*x, (n-1)/2);
}
