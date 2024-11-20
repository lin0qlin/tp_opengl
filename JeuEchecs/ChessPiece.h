#ifndef CHESSPIECE_H
#define CHESSPIECE_H

#include <vector>
#include <utility> // for std::pair

enum Team { BLACK, WHITE };
enum PieceType { PAWN, ROOK, KNIGHT, BISHOP, QUEEN, KING };

struct ChessPiece {
    float x, y; // Position on the board (0-7 range)
    PieceType type;  // Type of piece
    Team team;  // Team of the piece (BLACK or WHITE)

    ChessPiece(float x, float y, PieceType type, Team team);
    void draw() const; // Draw the chess piece
    std::vector<std::pair<int, int>> getPossibleMoves(const std::vector<std::vector<ChessPiece*>>& board) const; // Get possible moves
    void move(int newX, int newY); // Move the piece to a new position
};

#endif // CHESSPIECE_H
