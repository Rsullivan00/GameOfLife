#include <iostream>
#include <string>
#include <time.h>
#define SIZE 50
using namespace std;

bool** newBoard(){
	bool** board = new bool*[SIZE + 2];
	for(int i = 0; i < (SIZE + 2); i++){
		board[i] = new bool[SIZE + 2];
	}
	return board;
}

void print(bool ** board){
	cout << "Next generation:" << endl;
	for(int i = 1; i < SIZE + 1; i++){
		for(int j = 1; j < SIZE + 1; j++)
			if(board[i][j])
				cout << 'x';
			else
				cout << '.';
		cout << endl;
	}
	cout << endl;
}

int neighbors(bool** board, int x, int y){
	int count = 0;
	if(board[x+1][y] == true)
		count++;
	if(board[x-1][y] == true)
		count++;
	if(board[x][y+1] == true)
		count++;
	if(board[x][y-1] == true)
		count++;
	if(board[x-1][y-1] == true)
		count++;
	if(board[x+1][y-1] == true)
		count++;
	if(board[x+1][y+1] == true)
		count++;
	if(board[x-1][y+1] == true)
		count++;
	return count;
}

void initBoard(bool** board){
	for(int i = 0; i < (SIZE + 2); i++){
		for(int j = 0; j < (SIZE + 2); j++)
			board[i][j] = false;
	}
}

void clearBoard(bool** board){
	for(int i = 0; i < (SIZE + 2); i++){
		delete[] board[i];
	}
	delete[] board;
}

void randomSeed(bool** board){
	srand(time(NULL));
	for(int i = 1; i < SIZE + 1; i++){
		for(int j = 1; j < SIZE + 1; j++){
			if(rand()% 100 < 50)
				board[i][j] = true;
		}
	}
}

void play(bool** board){
	int xin = -1; int yin = -1;
	/*
	while(true){
		cout << "Enter pairs of x and y coordinates or '-1' to start." << endl;
		cin >> xin >> yin;
		if(xin == -1)
			break;
		board[xin+1][yin+1] = true;
	}
	*/
	randomSeed(board);
	bool ** temp = newBoard();
	cout << "Press Enter to move to the next generation,"
		<< " or enter 'q' to quit." << endl;
	char go;
	while(1){
		cin >> go;
		if(go == 'q' || go == 'Q')
			break;
		print(board);
		initBoard(temp);
		for(int i = 1; i < SIZE + 1; i++){
			for(int j = 1; j < SIZE + 1; j++){
				if(neighbors(board, i, j) < 2 || neighbors(board, i, j) > 3)
					temp[i][j] = false;
				else if(neighbors(board, i, j) == 3)
					temp[i][j] = true;
			}
		}
		for(int i = 0; i < SIZE + 2; i++){
			for(int j = 0; j < SIZE + 2; j++)
				board[i][j] = temp[i][j];
		}
	}
}

int main(){
	bool replay = true;
	bool ** board;
	board = newBoard();
	while(replay){
		initBoard(board);
		play(board);
		cout << "Play again? Y/N" << endl;
		char input;
		cin >> input;
		if(input == 'n' || input == 'N')
			replay = false;
	}
	clearBoard(board);
	return 0;
}
