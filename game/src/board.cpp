#include "board.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;
//falling added a into dropBlocks()
#include <raylib.h>

Board::Board() {

	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			GBoard[i][j] = white; // default color
		}
	}
}


void Board::setBoard(int rows, int cols) {
	srand(time(NULL));
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			int boardColorsIndex = rand() % static_cast<int>(boardColors::white);
			boardColors color = static_cast<boardColors>(boardColorsIndex);
			GBoard[i][j] = color;
		}
	}
}
void Board::setGBoardElement(int row, int col, boardColors color) {
	if (row >= 0 && row < rows && col >= 0 && col < cols) {
		GBoard[row][col] = color;
	}
}


bool Board::isBoardEmpty(int rows, int cols) {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (GBoard[i][j] != white) {
				return false;
			}
		}
	}
	return true;
}
Board:: boardColors Board::getColors(int row, int col) {
	if (row >= 0 && row <rows && col >= 0 && col < cols) {
		return GBoard[row][col];
	}
	else {
		throw out_of_range("Row or column out of bounds");
	}
}

int Board::getRows() {
	return rows;
}
int Board::getCols() {
	return cols;
}
void Board::removeConnectedBlocks(boardColors color, int row, int col) {
	if (row < 0 || row >= rows || col < 0 || col >= cols || Board::getColors(row, col) != color) {
		return;
	}
	Board::setGBoardElement(row, col, Board::boardColors::white);
	int r = row;
	// Add a falling block to the fallingBlocks vector
	while (r > 0) {
		FallingBlock block = { r, col, static_cast<float>(OFFSET_Y + 50 + (r)*SQUARE_SIZE),
			static_cast<float>(OFFSET_Y + 50 + (r- 1) * SQUARE_SIZE) ,Board::getColors(r- 1,col) };
		fallingBlocks.push_back(block);
		r = r - 1;
	}

	Board::removeConnectedBlocks(color, row + 1, col); // down
	Board::removeConnectedBlocks(color, row - 1, col); // up
	Board::removeConnectedBlocks(color, row, col + 1); // right
	Board::removeConnectedBlocks(color, row, col - 1); // left
	//std::cout << "Block removed: (" << row << ", " << col << ")" << std::endl;

}

//void Board::removeConnectedBlocks(boardColors color, int row, int col) {
//	if (row < 0 || row >= rows || col < 0 || col >= cols || Board::getColors(row, col) != color) {
//		return;
//	}
//	Board::setGBoardElement( row, col,Board::boardColors::white);
//	Board::removeConnectedBlocks(color, row + 1, col); //down
//	Board::removeConnectedBlocks(color, row - 1, col);//up
//	Board::removeConnectedBlocks(color, row, col +1);//right
//	Board::removeConnectedBlocks(color, row, col -1);//left
//	dropAllBlocks();
//
//}

void Board::dropBlocks(int row, int col) {
	if (row < 0 || row >= rows) {
		return;
	}
	if (Board::getColors(row, col) == white && row > 0) {
		Board::setGBoardElement(row, col, Board::getColors(row -1, col));
		Board::setGBoardElement(row - 1, col, white);
		dropBlocks(row - 1, col);
	}
}

void Board::dropAllBlocks() {
	for (int col = 0; col < cols; col++) {
		for (int row = 0; row < rows; row++) {
			dropBlocks(row, col);
		}
	}
}
const float Board::FALL_SPEED = 1.0f;