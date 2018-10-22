// code contains board class, and all basic functions related to board
// also has the function solve that applies DFS - but without hashing to save the failed boards.
#include <vector>
#include <stack>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include "time.h"
#include <iomanip>
#include <list>
#include "QuadraticProbing.h"
#include "QuadraticProbing.cpp"
#include "SeparateChaining.h"
//#include "DoubleHashing.h"

using namespace std;

const static int BWIDTH = 7;
const static int BHEIGHT = 7;
const static int CORNERMARGEN = 2;
static int move_counter = 0;

class BoardMove {
public:
    explicit BoardMove(int s, int m, int e)
        : start{ s }, middle{ m }, end{ e } {}

    int start, middle, end;


    friend ostream & operator << (ostream& os, const BoardMove& BM);
};

ostream & operator << (ostream& os, const BoardMove& BM) {
    os << " start: " << BM.start << " mid: " << BM.middle << " end: " << BM.end << endl;
    return os;
}

static vector<BoardMove> PossibleMoves;

class Board {
public:
    explicit Board() : PegsOnBoard{ 0L }, TotalPegs{ 0 } {
    }

    void findMovesFromPeg(const int loc, vector<BoardMove>& m) const
    {
        if (pegIsInHole(loc))
            for (auto apm : PossibleMoves)
                if (apm.start == loc)
                    if (pegIsInHole(apm.middle) && !pegIsInHole(apm.end))
                        m.push_back(apm);
    }

    void removePeg(const int loc) {
        TotalPegs--;
        PegsOnBoard &= ~(1LL << loc);
    }

    void insertPeg(const int loc) {
        TotalPegs++;
        //cout << "TotalPegs" << TotalPegs << endl;
        PegsOnBoard |= (1LL << loc);
    }

    int NumPegsOnBoard() const {
        cout << "TotalPegs" << TotalPegs << endl;
        return TotalPegs;
    }

    unsigned long long BoardBitMap() const {
        return(PegsOnBoard);
    }

    bool pegIsInHole(const int loc) const {
        return (((PegsOnBoard >> loc) & 1LL) == 1);
    }

    unsigned long long getPegs() {
        return PegsOnBoard;
    }

private:
    unsigned long long PegsOnBoard;     // Board is limited to no more than 64 peg spots
    int TotalPegs;

    void printPossibleMoves(vector<BoardMove>& m) {
        cout << m.size() << " possible moves found" << endl;
        for (auto i : m)
            cout << "(" << i.start << " " << i.middle << " " << i.end << ")" << endl;
    }
};

bool isValidHole(const int col, const int row) {
    if (row >= BHEIGHT || row < 0 || col >= BWIDTH || col < 0)
        return false;

    if (row < CORNERMARGEN || row >= BHEIGHT - CORNERMARGEN) {
        // we are at the top or the bottom.  Let's check sides
        if (col < CORNERMARGEN)           // left corner
            return false;
        if (col >= BWIDTH - CORNERMARGEN)  // right corner
            return false;
    }
    return true;
}

void printBoard(const Board& x, const BoardMove &m)
{
    cout << endl << "+----------------------+"
        << " (" << m.start << " " << m.middle << " " << m.end << ")"
        << endl;
    for (int row = 0; row < BHEIGHT; row++) {
        cout << "| ";
        for (int col = 0; col < BWIDTH; col++) {
            if (!isValidHole(col, row))
                cout << "-- ";
            else if (x.pegIsInHole((row*BHEIGHT) + col))
                cout << "** ";
            else
                cout << internal << setfill('0') << setw(2) << (row*BHEIGHT) + col << ' ';
        }
        cout << "|" << endl;
    }
    cout << "+----------------------+";
}

void printBoard(const Board& x)
{
    cout << endl << "+----------------------+" << endl;
    for (int row = 0; row < BHEIGHT; row++) {
        cout << "| ";
        for (int col = 0; col < BWIDTH; col++) {
            if (!isValidHole(col, row))
                cout << "-- ";
            else if (x.pegIsInHole((row*BHEIGHT) + col))
                cout << "** ";
            else
                cout << internal << setfill('0') << setw(2) << (row*BHEIGHT) + col << ' ';
        }
        cout << "|" << endl;
    }
    cout << "+----------------------+";
}




void initAllPossibleMoves() {
    for (int row = 0; row < BHEIGHT; row++) {
        for (int col = 0; col < BWIDTH; col++) {
            int idx = (row*BHEIGHT) + col;

            if (isValidHole(col, row)) {
                if (isValidHole(col + 2, row))   // Valid right move?
                    PossibleMoves.push_back(BoardMove(idx, idx + 1, idx + 2));
                if (isValidHole(col - 2, row))   // Valid left move?
                    PossibleMoves.push_back(BoardMove(idx, idx - 1, idx - 2));
                if (isValidHole(col, row + 2))   // Valid down move?
                    PossibleMoves.push_back(BoardMove(idx, idx + BWIDTH, idx + (BWIDTH * 2)));
                if (isValidHole(col, row - 2))   // Valid up move?
                    PossibleMoves.push_back(BoardMove(idx, idx - BWIDTH, idx - (BWIDTH * 2)));
            }
        }
    }
}


bool solved(const Board& x) {
    int pegInc = 0;
    for (int row = 0; row < BHEIGHT; row++) {
        //cout << "| ";
        for (int col = 0; col < BWIDTH; col++) {
            if (x.pegIsInHole((row*BHEIGHT) + col)) {
                //cout << "counting peg: " << pegInc << endl;
                pegInc++;
            }
        }
    }
    if (pegInc == 1) {
        printBoard(x);
        return true;
    }
    else
        return false;
}



/*
bool solved(const Board& x)
{
    
    if (x.NumPegsOnBoard() == 1) {
        cout << "you win" << endl;
        return true;
    }
    else
        return false;
}
*/

vector<BoardMove> currentMoves(const Board& x)
{
    vector<BoardMove> rval;
    for (int i = 0; i < BHEIGHT*BWIDTH; i++){
        x.findMovesFromPeg(i, rval);
    }
    return rval;
}

Board makeMove(const Board& x, const BoardMove& m)
{
    Board y = x;

    y.removePeg(m.start);
    y.removePeg(m.middle);
    y.insertPeg(m.end);

    return y;
}


bool solve(const Board& x, stack<BoardMove> & mseq)
{
    vector<BoardMove> curMoves;

    if (solved(x)) {
        return true;
    }

    curMoves = currentMoves(x); // set of possible moves that can be made on board x
    for (auto m : curMoves) {
        Board y = makeMove(x, m);
        move_counter++;
        if (solve(y, mseq)) {
            mseq.push(m);
            return true;
        }
    }
    return false;
}

//going to have 2 hsolves, one for separate chaining and one for the other closed hashing methods

bool hsolve(const Board& board, vector<BoardMove> mseq, HashTable<long long> & H, int chose) {
    if (solved(board)) {
        return true;
    }
    vector <BoardMove> curMoves = currentMoves(board);
    for (auto m : curMoves) {
        Board board2 = makeMove(board, m);
        if (!H.contains(board2.getPegs(), chose)) {
            if (hsolve(board2, mseq, H, chose)) {
                mseq.push_back(m);
                return true;
            }
            else {
                H.insert(board2.getPegs(), chose);
            }
        }
    }
    return false;
}



bool hsolve(const Board& board, vector<BoardMove> mseq, SeparateChainHashTable<long long> & SH, int chose) {
    if (solved(board)) {
        return true;
    }
    vector <BoardMove> curMoves = currentMoves(board);
    for (auto m : curMoves) {
        Board board2 = makeMove(board, m);
        if (!SH.contains(board2.getPegs())) {
            if (hsolve(board2, mseq, SH, chose)) {
                mseq.push_back(m);
                return true;
            }
            else {
                SH.insert(board2.getPegs());
            }
        }
    }
    return false;
}

int main() {
    //essential pieces
    Board _board;
    vector <BoardMove> mseq;
    HashTable<long long> H;
    SeparateChainHashTable<long long> SH;
    vector <int> Search;
    //Search.resize(4);
    vector <int> Insert;
    //Insert.resize(4);
    //vector<int>::iterator it = Search.begin();
    //vector<int>::iterator bit = Insert.begin();

    //open file pieces
    string x;
    ifstream in;
    string file;
    cout << "Please enter a file name\n";
    cin >> file;
    in.open(file.c_str());
    vector <int> i;
    while (in >> x) {
        i.push_back(stoi(x));
    }
    
    //set up the board, print initial board
    for (auto j: i) {
        _board.insertPeg(j);
    }
    cout << "----Initial Board----" << endl;
    printBoard(_board);
    cout << endl;

    Board _board2 = _board;
    Board _board3 = _board;
    Board _board4 = _board;

    //find all possible moves in board
    initAllPossibleMoves();

    //begin solving board

    //Quadratic Probing
    cout << "___Quadratic Probing___" << endl;
    double finish_time;
    double start_time = clock();
    hsolve(_board, mseq, H, 1);
    cout << endl;
    finish_time = clock();
    double time = (double) (finish_time - start_time)/CLOCKS_PER_SEC;
    cout << "solving took: " << time << " seconds" << endl;
    Search.push_back(H.GetNumberSearchProbes());
    cout << "Number of Search Probes " << Search[0] << endl;
    Insert.push_back(H.GetNumberInsertProbes());
    cout << "Number of Insert Probes " << Insert[0] << endl;
    H.ResetProbeCounters();
    cout << endl;

    //Double Hashing
    cout << "___Double Hashing___" << endl;
    double finish_time1;
    double start_time1 = clock();
    hsolve(_board2, mseq, H, 2);
    cout << endl;
    finish_time1 = clock();
    double time1 = (double) (finish_time1 - start_time1)/CLOCKS_PER_SEC;
    cout << "solving took: " << time1 << " seconds" << endl;
    Search.push_back(H.GetNumberSearchProbes());
    cout << "Number of Search Probes "<< Search[1] << endl;
    Insert.push_back(H.GetNumberInsertProbes());
    cout << "Number of Insert Probes " << Insert[1] << endl;
    H.ResetProbeCounters();
    cout << endl;

    //Linear Hashing
    cout << "___Linear Hashing___" << endl;
    double finish_time2;
    double start_time2 = clock();
    hsolve(_board3, mseq, H, 3);
    cout << endl;
    finish_time2 = clock();
    double time2 = (double) (finish_time2 - start_time2)/CLOCKS_PER_SEC;
    cout << "solving took: " << time2 << " seconds" << endl;
    Search.push_back(H.GetNumberSearchProbes());
    cout << "Number of Search Probes "<< Search[2] << endl;
    Insert.push_back(H.GetNumberInsertProbes());
    cout << "Number of Insert Probes " << Insert[2] << endl;
    H.ResetProbeCounters();
    cout << endl;

    //Separate Chaining
    cout << "___Separate Chaining___" << endl;
    double finish_time3;
    double start_time3 = clock();
    hsolve(_board4, mseq, SH, 4);
    cout << endl;
    finish_time3 = clock();
    double time3 = (double) (finish_time3 - start_time3)/CLOCKS_PER_SEC;
    cout << "solving took: " << time3 << " seconds" << endl;
    Search.push_back(SH.GetNumberSearchProbes());
    cout << "Number of Search Probes: " << Search[3] << endl;
    Insert.push_back(SH.GetNumberInsertProbes());
    cout << "Number of Insert Probes " << Insert[3] << endl;
    H.ResetProbeCounters();
    cout << endl;

    /*
    for (auto m : Search) {
        cout << "Search[i]: "<< m << endl;
    }

    for (auto m : Insert) {
        cout << "Insert[i]: "<< m << endl;
    }
    */
    return 0;
}

