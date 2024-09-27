#include "board.h"
#include"boardview.h"
#include "iostream"

BoardView::BoardView(Board &GameBoard)
{
	this->GameBoard = &GameBoard;
}

void BoardView::displayBoard()
{
	cout << "   ";
	for (int col = 0; col < GameBoard->getCols(); col++) {
		
		cout << col <<" ";
		
	}
	cout << endl;
	for (int row = 0; row < GameBoard->getRows(); row++) {
		cout << row << " ";
		for (int col = 0; col < GameBoard->getCols(); col++) {
			if (GameBoard->getColors(row, col) == Board::blue) {
				cout << " ";
				cout << "B";
			}
			if (GameBoard->getColors(row, col) == Board::green) {
				cout << " ";
				cout << "G";
			}	
			if (GameBoard->getColors(row, col) == Board::red) {
				cout << " ";
				cout << "R";
			}	
			if (GameBoard->getColors(row, col) == Board::white) {
				cout << " ";
				cout << "-";
			}
		}
		cout << endl;
	}
}

		