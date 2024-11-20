// GameController.cpp
#include "GameController.h"
#include <GLFW/glfw3.h>
#include <ctime>
#include <cstdlib>

GameController::GameController() : currentTurn(WHITE), selectedPiece(nullptr) {
    boardTexture = new Texture("textures/chessboard.png");
    pieceTextures[WHITE][PAWN] = new Texture("textures/white_pawn.png");
    pieceTextures[WHITE][ROOK] = new Texture("textures/white_rook.png");
    pieceTextures[WHITE][KNIGHT] = new Texture("textures/white_knight.png");
    pieceTextures[WHITE][BISHOP] = new Texture("textures/white_bishop.png");
    pieceTextures[WHITE][QUEEN] = new Texture("textures/white_queen.png");
    pieceTextures[WHITE][KING] = new Texture("textures/white_king.png");
    pieceTextures[BLACK][PAWN] = new Texture("textures/black_pawn.png");
    pieceTextures[BLACK][ROOK] = new Texture("textures/black_rook.png");
    pieceTextures[BLACK][KNIGHT] = new Texture("textures/black_knight.png");
    pieceTextures[BLACK][BISHOP] = new Texture("textures/black_bishop.png");
    pieceTextures[BLACK][QUEEN] = new Texture("textures/black_queen.png");
    pieceTextures[BLACK][KING] = new Texture("textures/black_king.png");
    initializeBoard();
    std::srand(std::time(nullptr));
}

void GameController::initializeBoard() {
    board.resize(8, std::vector<ChessPiece*>(8, nullptr));

    // Initialize pieces for both teams
    // Black pieces
    pieces = {
        {0, 0, ROOK, BLACK}, {1, 0, KNIGHT, BLACK}, {2, 0, BISHOP, BLACK}, {3, 0, QUEEN, BLACK},
        {4, 0, KING, BLACK}, {5, 0, BISHOP, BLACK}, {6, 0, KNIGHT, BLACK}, {7, 0, ROOK, BLACK},
        {0, 1, PAWN, BLACK}, {1, 1, PAWN, BLACK}, {2, 1, PAWN, BLACK}, {3, 1, PAWN, BLACK},
        {4, 1, PAWN, BLACK}, {5, 1, PAWN, BLACK}, {6, 1, PAWN, BLACK}, {7, 1, PAWN, BLACK},
        // White pieces
        {0, 6, PAWN, WHITE}, {1, 6, PAWN, WHITE}, {2, 6, PAWN, WHITE}, {3, 6, PAWN, WHITE},
        {4, 6, PAWN, WHITE}, {5, 6, PAWN, WHITE}, {6, 6, PAWN, WHITE}, {7, 6, PAWN, WHITE},
        {0, 7, ROOK, WHITE}, {1, 7, KNIGHT, WHITE}, {2, 7, BISHOP, WHITE}, {3, 7, QUEEN, WHITE},
        {4, 7, KING, WHITE}, {5, 7, BISHOP, WHITE}, {6, 7, KNIGHT, WHITE}, {7, 7, ROOK, WHITE}
    };

    // Place pieces on the board
    for (auto& piece : pieces) {
        board[piece.y][piece.x] = &piece;
    }
}

void GameController::updateBoardState() {
    for (auto& piece : pieces) {
        if (board[piece.y][piece.x] != &piece) {
            board[piece.y][piece.x] = &piece;
        }
    }
}

void GameController::drawBoard() const {
    // Draw the chessboard texture
    boardTexture->bind();
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex2f(0.0f, 0.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex2f(8.0f, 0.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex2f(8.0f, 8.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex2f(0.0f, 8.0f);
    glEnd();
    boardTexture->unbind();

    // Draw the chess pieces with appropriate textures
    for (const auto& piece : pieces) {
        pieceTextures[piece.team][piece.type]->bind();
        float size = 0.8f; // Size of the piece relative to the square
        glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f); glVertex2f(piece.x + 0.1f, piece.y + 0.1f);
        glTexCoord2f(1.0f, 0.0f); glVertex2f(piece.x + 0.9f, piece.y + 0.1f);
        glTexCoord2f(1.0f, 1.0f); glVertex2f(piece.x + 0.9f, piece.y + 0.9f);
        glTexCoord2f(0.0f, 1.0f); glVertex2f(piece.x + 0.1f, piece.y + 0.9f);
        glEnd();
        pieceTextures[piece.team][piece.type]->unbind();
    }
}

void GameController::handleClick(int x, int y) {
    if (selectedPiece == nullptr) {
        // Select a piece if it belongs to the current player
        if (board[y][x] != nullptr && board[y][x]->team == currentTurn) {
            selectedPiece = board[y][x];
        }
    } else {
        // Try to move the selected piece
        if (board[y][x] == nullptr) {
            // Check if the move is valid
            auto possibleMoves = selectedPiece->getPossibleMoves(board);
            for (const auto& move : possibleMoves) {
                if (move.first == x && move.second == y) {
                    // Move the piece
                    board[selectedPiece->y][selectedPiece->x] = nullptr; // Clear old position
                    selectedPiece->move(x, y);
                    board[y][x] = selectedPiece; // Update new position
                    selectedPiece = nullptr; // Deselect piece
                    switchTurn(); // Switch turns after a successful move
                    return;
                }
            }
        }
        // If move is invalid, deselect the piece
        selectedPiece = nullptr;
    }
}

void GameController::switchTurn() {
    currentTurn = (currentTurn == WHITE) ? BLACK : WHITE;
}
