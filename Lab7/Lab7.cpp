//jeff cpp for peg solitaire
//
//
//

#include "time.h"
#include <sstream>
#include "SeparateChaining.h"
#include "SeparateChaining.cpp"
#include <iostream>
#include <algorithm>
#include <string>
#include <cstdlib>
#include <list>

using namespace std;


bool solved(string s);
bool solve(string board, list<vector<int>> mseq);
bool hard_solve(string board, list<vector<int>> mseq);
vector <vector<int>> next_moves(string board);
vector <vector<int>> hard_moves(string board);
string makeMove(string board, vector<int> move);
bool hsolve(string board, list<vector<int>> mseq, HashTable<long long> & H);


vector <vector<int>> hard_moves();
vector <int> tokenizer(string input);
bool isvalidboard(int x, string board);
bool isvalidmove(int x, string board);
bool isvalidplacement(int x, int side);
string initialize_board(string board, vector <int> pegs);
int count_pegs (string board);
bool isvaliddownmove(int x);
bool isvalidupmove(int x);
bool isvalidrightmove(int x);
bool isvalidleftmove(int x);
long long convert_to_long(string board);
bool check_board(string board, int x);
//bool check_h (string board, Hashtable<long long> & H);




int main(int argc, char  * argv[]) {
	string board;
	string board88;
	for (int i = 0; i < 49; i++) {
		board.append("0");
    //board88.append("0");
	}
	
	int x;
  string first_test = "9 18 19 29 30 38";
  string second_test = "2 3 4 9 10 14 15 16 17 19";
  string third_test = "3 4 9 15 16 17 19 20 22 23 25 26 27 30 31 33 34 38 45 46";
  string fourth_test = "2 3 4 9 10 14 15 16 17 19 20 21";
	string first_pegs = "2 3 4 8 9 10 11 14 15 16 17 18 19 20 21 22 23 25 26 27 28 29 30 31 32 33 34 37 38 39 44 45 46";
	string test_wing = " 4 ";
	vector <int> v = tokenizer(first_pegs);
	vector <int> b = tokenizer(test_wing);
  vector <int> ft = tokenizer(first_test);
  vector <int> st = tokenizer(second_test);
  vector <int> tht = tokenizer(third_test);
  vector <int> ftht = tokenizer(fourth_test);
  string test_case;
  cout << "enter a test case to start: 1 for simple, 4 for difficult: "<< endl;
  cout << " 1 - 2 - 3 - 4 " << endl;
  cin >> test_case;
  if (test_case == "1") {board = initialize_board(board, ft);}
  else if (test_case == "2") {board = initialize_board(board, st);}
  else if (test_case == "3") {board = initialize_board(board, tht);}
  else if (test_case == "4") {board = initialize_board(board, ftht);}


  HashTable<long long> H;
  list <vector<int>> mseq;
  string instruct;
  while (instruct != "3") {
    cout << "run DFS without hashing: 1, run DFS with openhashing: 2, to quit: 3" << endl;
    cin >> instruct;
    if (instruct == "1") {
      double finish_time;
      double start_time = clock();
      if (solve(board, mseq)) {
        cout << " you did it! " << endl;
        finish_time = clock();
        double time = (double) (finish_time - start_time)/CLOCKS_PER_SEC;
        cout << "solving took: " << time << " seconds" << endl;
      }
      else {
        cout << "couldn't solve"<< endl;
      }
    }
    if (instruct == "2") {
      double finish_time;
      double start_time = clock();
      if (hsolve(board, mseq, H)) {
        cout << "board solved!" << endl;
        finish_time = clock();
        double time = (double) (finish_time - start_time)/CLOCKS_PER_SEC;
        cout << "solving took: " << time << " seconds" << endl;
      }
      
      else {
        cout << "couldn't solve" << endl;
      }
    }
  }
  return 0;
}


bool check_board(string board, int x) {
  if (board[x] == '1') {return true;}
  else {return false;}
}


long long convert_to_long(string board) {
  long long int x = 0;
  for (int j = 0; j < 64; j++) {
    int s = 0;
    if (check_board(board, j))
      s = 1;
    x = 2*x + s;
  }
  return x;
}

int count_pegs (string board) {
  int counter = 0;
  for (int i = 0; i < board.size(); ++i) {
    if(board[i] == '1') {
      counter++;
      //cout << counter;
    }
  }
  return counter;
}


//super hardcoded logic to make sure peg is playable, 
//all values are outside the scope of the board
bool isvalidboard (int x, string board) {
  if (x < 0) {return false;}
  if (x == 0) {return false;}
  if (x == 1) {return false;}
  if (x == 5) {return false;}
  if (x == 6) {return false;}
  if (x == 7) {return false;}
  if (x == 8) {return false;}
  if (x == 12) {return false;}
  if (x == 13) {return false;}
  if (x == 35) {return false;}
  if (x == 36) {return false;}
  if (x == 40) {return false;}
  if (x == 41) {return false;}
  if (x == 42) {return false;}
  if (x == 43) {return false;}
  if (x == 47) {return false;}
  if (x == 48) {return false;}
  if (x > 49) {return false;}
  else {
    return true;
  }
}

bool isvalidmove (int x, string board) {
  if (!isvalidboard(x, board)) {return false;}
  else if (board[x] == '1') {return true;}
  return false; 
}

//initializes the values of board, with pegs and empty spots
//calls isvalid to keep in playable board area
string initialize_board (string board, vector<int> pegs) {
  //string::iterator it;
  //cout << pegs << endl;
  for (int i = 0; i < pegs.size(); ++i) {
    int temp = pegs[i];
    if (isvalidboard(temp, board)) {
      board.insert(board.begin()+temp,'1');
      board.resize(49);
    }
  }
  return board;
}


//boolean to return true if the game is done
bool solved (string s) {
  if (count_pegs(s) == 1) {
    return true;
  }
  else {
    return false;
  }
}

bool isvalidplacement (int x, int side) {
  if (side == 1) { //right side
    if (x == 19) { return false;}
    if (x == 20) { return false;}
    if (x == 26) { return false;}
    if (x == 27) { return false;}
  }
  else if (side == 0) { //left side
    if (x == 21) { return false;}
    if (x == 22) { return false;}
    if (x == 28) { return false;}
    if (x == 29) { return false;}
  }
  return true;
}



bool isvalidrightmove(int x) {
  if (x == 2) {return true;}
  if (x == 9) {return true;}
  if (x == 14) {return true;}
  if (x == 15) {return true;}
  if (x == 16) {return true;}
  if (x == 17) {return true;}
  if (x == 18) {return true;}
  if (x == 21) {return true;}
  if (x == 22) {return true;}
  if (x == 23) {return true;}
  if (x == 24) {return true;}
  if (x == 25) {return true;}
  if (x == 28) {return true;}
  if (x == 29) {return true;}
  if (x == 30) {return true;}
  if (x == 31) {return true;}
  if (x == 32) {return true;}
  if (x == 37) {return true;}
  if (x == 44) {return true;}
  else {return false;}
}

bool isvalidleftmove(int x) {
  if (x == 4) {return true;}
  if (x == 11) {return true;}
  if (x == 16) {return true;}
  if (x == 17) {return true;}
  if (x == 18) {return true;}
  if (x == 19) {return true;}
  if (x == 20) {return true;}
  if (x == 23) {return true;}
  if (x == 24) {return true;}
  if (x == 25) {return true;}
  if (x == 26) {return true;}
  if (x == 27) {return true;}
  if (x == 30) {return true;}
  if (x == 31) {return true;}
  if (x == 32) {return true;}
  if (x == 33) {return true;}
  if (x == 34) {return true;}
  if (x == 39) {return true;}
  if (x == 46) {return true;}
  else {return false;}

}

vector <vector<int>> hard_moves () {
  vector <vector<int>> n_moves = {{29, 30, 31}, {38, 31, 24}, {19, 18, 17}, {24, 17, 10}, {9, 10, 11}};
  return n_moves;
}




vector <vector <int>> next_moves (string board) {
  vector <vector <int>> NMOVES;
  //bool move_made = false;
  for (int i = 0; i < board.size(); ++i) {
    if (board[i] == '0' && isvalidboard(i, board)){
      //i is 0 and its on the board
      vector <int> _moves (3, 0);
      //test for below open peg slot, can only go if i < 20, if it catches, passes a move into NMOVES
      //need more logic for figuring out where you are in board

      if (isvalidmove(i+14, board) && isvalidmove(i+7, board) && isvaliddownmove(i)) {
        //cout << "doing down move" << endl;
        _moves[0] = i+14;
        _moves[1] = i+7;
        _moves[2] = i;
        NMOVES.push_back(_moves);
        //move_made = true;
        //return NMOVES;
      }
      //test for above the open peg slot
      if (isvalidmove(i-14, board) && isvalidmove(i-7, board) && isvalidupmove(i) /*&& move_made == false*/) {
        //cout << "doing up move" << endl;
        _moves[0] = i-14;
        _moves[1] = i-7;
        _moves[2] = i;
        NMOVES.push_back(_moves);
        //move_made = true;
        //return NMOVES;
      }

      //test to right of slot
      if (isvalidmove(i+2, board) && isvalidmove(i+1, board) && isvalidrightmove(i) /*&& move_made == false*/) {
        //cout << "doing right slot" << endl;
        _moves[0] = i+2;
        _moves[1] = i+1;
        _moves[2] = i;
        NMOVES.push_back(_moves);
        //move_made = true;
        //return NMOVES;
      }
      //test to left of slot
      if (isvalidmove(i-2, board) && isvalidmove(i-1, board) && isvalidleftmove(i) /*&& move_made == false*/) {
        //cout << "doing left slot" << endl;
        _moves[0] = i-2;
        _moves[1] = i-1;
        _moves[2] = i;
        NMOVES.push_back(_moves);
        //move_made = true;
        //return NMOVES;
      }
    }
  }
  //move_made = false;
  return NMOVES;
}


bool isvaliddownmove(int x) {
  //checks down moves
  if (x == 2) {return true;}
  if (x == 3) {return true;}
  if (x == 4) {return true;}
  if (x == 9) {return true;}
  if (x == 10) {return true;}
  if (x == 11) {return true;}
  if (x == 14) {return true;}
  if (x == 15) {return true;}
  if (x == 16) {return true;}
  if (x == 17) {return true;}
  if (x == 18) {return true;}
  if (x == 19) {return true;}
  if (x == 20) {return true;}
  if (x == 23) {return true;}
  if (x == 24) {return true;}
  if (x == 25) {return true;}
  if (x == 30) {return true;}
  if (x == 31) {return true;}
  if (x == 32) {return true;}
  else {return false;}
}

bool isvalidupmove(int x) {
  //checks down moves
  if (x == 16) {return true;}
  if (x == 17) {return true;}
  if (x == 18) {return true;}
  if (x == 23) {return true;}
  if (x == 24) {return true;}
  if (x == 25) {return true;}
  if (x == 28) {return true;}
  if (x == 29) {return true;}
  if (x == 30) {return true;}
  if (x == 31) {return true;}
  if (x == 32) {return true;}
  if (x == 33) {return true;}
  if (x == 34) {return true;}
  if (x == 37) {return true;}
  if (x == 38) {return true;}
  if (x == 39) {return true;}
  if (x == 44) {return true;}
  if (x == 45) {return true;}
  if (x == 46) {return true;}
  else {return false;}
}


string makeMove(string board, vector<int> move) {
  //makethe move requested in the vector, assume move is valid, testing for validity when building the move vector
  string copy_board;
  int from = move[0];
  int mid = move[1];
  int to = move[2];
  board.replace(from, 1, "0");
  board.replace(mid, 1, "0");
  board.replace(to, 1, "1");
  return board;
}

//solve is main solving function, using DFS
bool solve (string board, list<vector<int>> mseq) {
  if (solved(board))
    return true;
  vector <vector <int>> current_moves = next_moves(board);
  for (int i = 0; i < current_moves.size(); ++i) {
      string board2 = makeMove(board, current_moves[i]);
      if (solve(board2, mseq)) {
        //cout << "coming into here? AHHHHHHHHHHHHH " << endl;
        //vector <int> c_move = current_moves[i]; 
        mseq.push_front(current_moves[i]);
        return true;
      } 
  }
  return false;
}

//solved using hard coded solutions
bool hard_solve (string board, list<vector<int>> mseq) {
  if (solved(board))
    return true;
  vector <vector <int>> current_moves = next_moves(board);
  for (int i = 0; i < current_moves.size(); ++i) {
      string board2 = makeMove(board, current_moves[i]);
      if (solve(board2, mseq)) { 
        mseq.push_front(current_moves[i]);
        return true;
      } 
  }
  return false;
}

bool hsolve(string board, list<vector<int>> mseq, HashTable<long long> & H) {
  if (solved(board))
    return true;
  vector <vector <int>> current_moves = next_moves(board);
  for (int i = 0; i < current_moves.size(); ++i) {
    string board2 = makeMove(board, current_moves[i]);
    long long board_int = convert_to_long(board2);
    if (!H.contains(board_int)); {
      if (hsolve(board2, mseq, H)) {
        mseq.push_front(current_moves[i]);
        return true;
      }
      else {
        H.insert(board_int);
      }
    }
  }
  return false;
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