#include "raylib.h"
#include "rectangle.h"
#include "board.h"
#include "iostream"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

using namespace std;
int main(void)
{
    const int screenWidth = 1000;
    const int screenHeight =1000;

    InitWindow(screenWidth, screenHeight, "Color Matching Game");
    SetTargetFPS(60);

    Board gameBoard;
    
    int moveCounter = 0;
    bool gameOver = false;

    for (int row = 0; row < gameBoard.getRows(); row++) {
        for (int col = 0; col < gameBoard.getCols(); col++) {
            gameBoard.setGBoardElement(row, col, static_cast<Board::boardColors>(GetRandomValue(0, 2)));
        }
    }

    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_Q)) {
            break; // Quits the game when Q is pressed
        }
        Vector2 mousePos = GetMousePosition();
        BeginDrawing();
        ClearBackground(RAYWHITE);

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && !gameOver) {
            int col = (mousePos.x - gameBoard.OFFSET_X - 300) / gameBoard.SQUARE_SIZE;
            int row = (mousePos.y - gameBoard.OFFSET_Y - 50) / gameBoard.SQUARE_SIZE;

            if (col >= 0 && col < gameBoard.getCols() && row >= 0 && row < gameBoard.getRows()) {
                Board::boardColors clickedColor = gameBoard.getColors(row, col);
                gameBoard.removeConnectedBlocks(clickedColor, row, col);

                gameBoard.dropAllBlocks();
                moveCounter++;
            }
        }

        if (!gameOver && gameBoard.isBoardEmpty(gameBoard.getRows(),gameBoard.getCols())) {
            gameOver = true;
        }


        // Update falling blocks
        for (int i = 0; i < gameBoard.fallingBlocks.size(); ) {
            Board::FallingBlock& block = gameBoard.fallingBlocks[i];
            
            block.currentY += gameBoard.FALL_SPEED;
          
            // Check if it has reached its target position
            if (block.currentY >= block.targetY) {
               /* cout << block.currentY << endl;
                cout << "target Y" << block.targetY << endl;*/
                block.currentY = block.targetY; 
                // Remove the block from fallingBlocks if it reaches the target
                gameBoard.fallingBlocks.erase(gameBoard.fallingBlocks.begin() + i);
            }
            else {
                ++i; // Move to the next block
            }
        }
        BeginDrawing();
        ClearBackground(RAYWHITE);

        for (int row = 0; row < gameBoard.getRows(); row++) {
            for (int col = 0; col < gameBoard.getCols(); col++) {
                Board::boardColors color = gameBoard.getColors(row, col);
                Color squareColor;

                switch (color) {
                case Board::blue: squareColor = BLUE; break;
                case Board::green: squareColor = GREEN; break;
                case Board::red: squareColor = RED; break;
                case Board::white: squareColor = WHITE; break;
                }
                int blockX = gameBoard.OFFSET_X + 300 + col * gameBoard.SQUARE_SIZE;
                int blockY = gameBoard.OFFSET_Y + 50 + row * gameBoard.SQUARE_SIZE;
                // Check if there's a falling block in this position
                bool isFalling = false;
                for ( Board::FallingBlock& block : gameBoard.fallingBlocks) {
                    if (block.row == row && block.col == col) {
                        /*cout << "falling starting at " << block.currentY << endl;*/
                        DrawRectangle(gameBoard.OFFSET_X + 300 + col * gameBoard.SQUARE_SIZE, block.currentY,
                            gameBoard.SQUARE_SIZE, gameBoard.SQUARE_SIZE, squareColor);
                        if (color != Board::white) {
                            DrawRectangleLines(blockX, block.currentY, gameBoard.SQUARE_SIZE, gameBoard.SQUARE_SIZE, DARKGRAY);
                        }
                        isFalling = true;
                        break;
                    }
                }

                // Draw normally if no block is falling
                if (!isFalling) {
                    DrawRectangle(gameBoard.OFFSET_X + 300 + col * gameBoard.SQUARE_SIZE, gameBoard.OFFSET_Y + 50 + row * gameBoard.SQUARE_SIZE,
                        gameBoard.SQUARE_SIZE, gameBoard.SQUARE_SIZE, squareColor);

                }
                
                if (color != Board::white && !isFalling) {
                    DrawRectangleLines(blockX, blockY, gameBoard.SQUARE_SIZE, gameBoard.SQUARE_SIZE, DARKGRAY);
                }
            }
        }

        if (gameOver) {
            DrawText(TextFormat("Game Over! Moves: %d", moveCounter), 10, 10, 20, DARKGRAY);
        }
        else {
            DrawText(TextFormat("Moves: %d", moveCounter), 10, 10, 20, DARKGRAY);
        }
        DrawFPS(10, 40);
        EndDrawing();
    }


    CloseWindow();
    return 0;
}