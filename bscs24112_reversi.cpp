#include <iostream>
#include <fstream>
using namespace std;

const int SIZE = 8;
void writeinBoard(const char* filename);
void readBoard(char board[SIZE][SIZE], const char* filename);
void displayBoard(char board[SIZE][SIZE]);
bool isValidMove(char board[SIZE][SIZE], int rows, int cols);
void flipPieces(char board[SIZE][SIZE], int rows, int cols, int drows, int dcols, char player, char opponent);
void makeMove(char board[SIZE][SIZE], int rows, int cols, char player, char opponent);
bool isBoardFull(char board[SIZE][SIZE]);
void Winner(char board[SIZE][SIZE]);
bool AIMove(char board[SIZE][SIZE], char AI, char player);


int main()
{
	char board[SIZE][SIZE];
	writeinBoard("board.txt");
	readBoard(board, "board.txt");

	char player = 'X';
	char opponent = 'O';
	char AI = 'O';
	cout << "=====|WELCOME TO REVERSI|=====" << endl;
	cout << "Enter the mode of game: " << endl;
	cout << "1 for Human vs Human" << endl << "2 for Human vs AI" << endl;
	int x;
	cin >> x;
	int rows, cols;
	switch (x)
	{
	case 1: //human vs human
	{
		while (!isBoardFull(board)) {
			displayBoard(board);

			cout << "Player " << player << ", enter your move (row and column): ";
			cin >> rows >> cols;

			if (isValidMove(board, rows, cols)) {
				makeMove(board, rows, cols, player, opponent);
				player = (player == 'X') ? 'O' : 'X';
				opponent = (opponent == 'X') ? 'O' : 'X';
			}
			else {
				cout << "Invalid move. Try again.\n";
			}
		}
		break;
	}
	case 2: //human vs ai
	{
		while (!isBoardFull(board)) {
			displayBoard(board);

			cout << "Player " << player << ", enter your move (row and column): ";
			cin >> rows >> cols;

			if (isValidMove(board, rows, cols)) {
				makeMove(board, rows, cols, player, AI);
				displayBoard(board);
				if (isBoardFull(board)) break;  
			}
			else {
				cout << "Invalid move. Try again.\n";
				continue; 
			}

			// AI turn
			if (!isBoardFull(board)) {
				cout << "AI's turn:\n";
				if (!AIMove(board, AI, player)) {
					cout << "No valid moves left!\n";
				}
				if (isBoardFull(board)) break;  
			}
		}
		break;
	}
	}

	
	displayBoard(board);
	Winner(board);

	return 0;
}
void writeinBoard(const char* filename)
{
	ofstream writer(filename);
	if (!writer)
	{
		cerr << "Error found while oppening file. " << endl;
		exit(1);
	}

	char initialBoard[SIZE][SIZE] = 
	{
	
		{ '.', '.', '.', '.', '.', '.', '.', '.'},
		{ '.', '.', '.', '.', '.', '.', '.', '.'},
		{ '.', '.', '.', '.', '.', '.', '.', '.'},
		{ '.', '.', '.', 'O', 'X', '.', '.', '.'},
		{ '.', '.', '.', 'X', 'O', '.', '.', '.'},
		{ '.', '.', '.', '.', '.', '.', '.', '.'},
		{ '.', '.', '.', '.', '.', '.', '.', '.'},
		{ '.', '.', '.', '.', '.', '.', '.', '.'}
	};

	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			writer << initialBoard[i][j];
			if (j < SIZE - 1) writer << " "; // Add space between columns
		}
		writer << '\n'; 
	}

	writer.close();
}
void readBoard(char board[SIZE][SIZE], const char* filename) 
{
	ifstream reader(filename);
	if (!reader) {
		cerr << "Error found while opening file." << endl;
		exit(1);
	}

	
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			reader >> board[i][j];
		}
	}

	reader.close();
}
void displayBoard(char board[SIZE][SIZE]) {
	cout << "   ";
	for (int i = 0; i < SIZE; i++) cout << i << " ";
	cout << "\n  *";
	for (int i = 0; i < SIZE; i++) cout << "--";
	cout << "*\n";

	for (int i = 0; i < SIZE; i++) {
		cout << i << " |";
		for (int j = 0; j < SIZE; j++) {
			if (board[i][j] == 'X') {
				cout << "\033[31mX\033[0m "; // Red for X
			}
			else if (board[i][j] == 'O') {
				cout << "\033[34mO\033[0m "; // Blue for O
			}
			else {
				cout << board[i][j] << " ";
			}
		}
		cout << "|\n";
	}

	cout << "  *";
	for (int i = 0; i < SIZE; i++) cout << "--";
	cout << "*\n";
}




bool isValidMove(char board[SIZE][SIZE], int rows, int cols) {
	if (rows < 0 || rows >= SIZE || cols < 0 || cols >= SIZE) {
		return false;
	}
	return board[rows][cols] == '.';
}
void flipPieces(char board[SIZE][SIZE], int rows, int cols, int drows, int dcols, char player, char opponent)
{
	int i = rows + drows, j = cols + dcols;
	bool validFlip = false;

	while (i >= 0 && i < SIZE && j >= 0 && j < SIZE && board[i][j] == opponent) {
		validFlip = true;
		i += drows;
		j += dcols;
	}

	if (validFlip && i >= 0 && i < SIZE && j >= 0 && j < SIZE && board[i][j] == player) {
		i = rows + drows;
		j = cols + dcols;
		while (board[i][j] == opponent) {
			board[i][j] = player;
			i += drows;
			j += dcols;
		}
	}
}

void makeMove(char board[SIZE][SIZE], int rows, int cols, char player,char opponent) {
	board[rows][cols] = player;

	for (int dRow = -1; dRow <= 1; dRow++) {
		for (int dCol = -1; dCol <= 1; dCol++) {
			if (dRow != 0 || dCol != 0) {
				flipPieces(board, rows, cols, dRow, dCol, player,opponent);
			}
		}
	}
}
bool isBoardFull(char board[SIZE][SIZE]) 
{
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			if (board[i][j] == '.') {
				return false;
			}
		}
	}
	return true;
}
void Winner(char board[SIZE][SIZE])
{
	int count_O = 0;
	int count_X = 0;

	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			if (board[i][j] == 'O')
				count_O++;
			if (board[i][j] == 'X') 
				count_X++;
		}
	}

	cout << "Player 0 has " << count_O << "pieces." << '\n' << "Player X has " << count_X << "pieces.\n" ;
	if (count_O > count_X) {
		cout << "Player O wins!\n";
	}
	else if (count_X > count_O) {
		cout << "Player X wins!\n";
	}
	else {
		cout << "It's a draw!\n";
	}
}
bool AIMove(char board[SIZE][SIZE], char AI, char player) 
{
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			if (isValidMove(board, i, j)) {
				board[i][j] = AI;
				for (int drows = -1; drows <= 1; drows++) {
					for (int dcols = -1; dcols <= 1; dcols++) {
						if (drows != 0 || dcols != 0) {
							flipPieces(board, i, j, drows, dcols, AI, player);
						}
					}
				}
				return true;
			}
		}
	}
	return false;  
}










