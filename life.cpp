#include <iostream>
#include <string>
#include <time.h>
using namespace std;

class Board{
private:
    int s;      //Size of the square (s x s)
    bool** b;   //Contains the current status of each node
    int** n;    //Contains the number of neihbors of each node

    void init(int = 11);
    void clear();

public:
    Board(int = 11);
    ~Board();
    Board(const Board&);
    const Board& operator=(const Board&);
    void print();
    void printN();
    void randomize();
    void updateN();
    void updateB();
    int countNeighbors(int, int);
    bool evalN(int, int);
};

Board::Board(int _s){
    init(_s);
}

void Board::init(int _s){
    s = _s;
    b = new bool*[s];
    n = new int*[s];
    for(int i = 0; i < s; i++){
        b[i] = new bool[s];
        n[i] = new int[s];
    }
}

Board::~Board(){
    clear();
}

void Board::clear(){
    for(int i = 0; i < s; i++){
        delete b[i];
        delete n[i];
    }
    delete b;
    delete n;
}

Board::Board(const Board& other){
    init();
    *this = other;
}

const Board& Board::operator=(const Board& other){
    if(this == &other)
        return *this;
    clear();
    init(other.s);
    for(int i = 0; i < other.s; i++){
        for(int j = 0; j < other.s; j++){
            b[i][j] = other.b[i][j];
            n[i][j] = other.n[i][j];
        }
    }

    return *this;
}

void Board::print(){
    cout << endl << "Game of Life" << endl;
    for(int i = 0; i < s; i++){
        for(int j = 0; j < s; j++)
            cout << b[i][j] << ' ';
        cout << endl;
    }
}

void Board::printN(){
    cout << endl;
    for(int i = 0; i < s; i++){
        for(int j = 0; j < s; j++)
            cout << n[i][j] << ' ';
        cout << endl;
    }
}

void Board::randomize(){
    for(int i = 1; i < s-1; i++)
        for(int j = 1; j < s-1; j++)
            b[i][j] = rand() % 2;
}

void Board::updateN(){
    for(int i = 1; i < s-1; i++)
        for(int j = 1; j < s-1; j++)
            n[i][j] = countNeighbors(i, j);
}

void Board::updateB(){
    for(int i = 1; i < s-1; i++)
        for(int j = 1; j < s-1; j++)
            b[i][j] = evalN(i, j);
}

//Returns what the state of b[x][y] should become
//depending on the state of n[x][y].
bool Board::evalN(int x, int y){
    if(n[x][y] < 2 || n[x][y] > 4) 
        return false;
    if(n[x][y] == 3) 
        return true;
    return b[x][y];
}

int Board::countNeighbors(int x, int y){
    int count = 0;

    if(b[x-1][y-1]) count++;
    if(b[x-1][y])   count++;
    if(b[x-1][y+1]) count++;
    if(b[x][y-1])   count++;
    if(b[x][y+1])   count++;
    if(b[x+1][y+1]) count++;
    if(b[x+1][y])   count++;
    if(b[x+1][y-1]) count++;

    return count;
}

int main(){
    srand(time(NULL));
    Board B(25);
    B.randomize();
    B.print();
    while(true){
        cin.ignore();
        B.updateN();
        B.updateB();
        B.print();
    }
    return 0;
}
