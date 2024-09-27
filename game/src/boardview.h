#ifndef BOARDVIEW_H
#define BOARDVIEW_H
#include "board.h"
class BoardView {
private:
	Board *GameBoard; 
public:
	BoardView(Board &GameBoard);
	void displayBoard();

};

#endif