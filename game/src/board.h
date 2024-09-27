#ifndef BOARD_H
#define BOARD_H
#include <vector>
#include <string>
using namespace std;
class Board{
public:
	static const int SQUARE_SIZE = 50;
	static const int OFFSET_X = 50;
	static const int OFFSET_Y = 50;
	static const float FALL_SPEED;
enum boardColors{	
	blue,
	green,
	red,		
	white,

};
struct FallingBlock {
	int row;
	int col;
	float targetY;
	float currentY;
	boardColors color;
};
vector<FallingBlock> fallingBlocks;


private:
	int static const rows = 5;
	int static const cols = 5;
	boardColors GBoard[rows][cols];
public:
	
	Board();
	boardColors getColors(int row, int col);
	int getRows();
	int getCols();
	void setBoard(int rows, int cols);
	bool isBoardEmpty(int rows, int cols);
	void removeConnectedBlocks(boardColors color,int row, int col);
	void dropBlocks(int row, int col);
	void dropAllBlocks();
	void setGBoardElement(int row, int col, boardColors color);
};
#endif