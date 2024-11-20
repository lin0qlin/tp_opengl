// GameController.h
#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include "ChessPiece.h"
#include "ChessBoard.h"
#include "Texture.h"
#include <vector>
#include <utility>

class GameController {
public:
    GameController();
    void initializeBoard();
    void updateBoardState();
    void drawBoard() const;
    void handleClick(int x, int y); // Handle user clicks for selecting and moving pieces
    void switchTurn();

private:
    std::vector<std::vector<ChessPiece*>> board;
    std::vector<ChessPiece> pieces;
    Team currentTurn;
    ChessPiece* selectedPiece; // Track selected piece
    Texture* boardTexture;     // Chessboard texture
    Texture* pieceTextures[2][6]; // Textures for black and white pieces (6 types each)
};

#endif // GAMECONTROLLER_H
