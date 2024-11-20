#include "ChessPiece.h"
#include <GLFW/glfw3.h>
#include <cmath>
#include <cstdlib>
#include <vector>

ChessPiece::ChessPiece(float x, float y, PieceType type, Team team)
    : x(x), y(y), type(type), team(team) {}

void ChessPiece::draw() const {
    switch (type) {
        case PAWN:
            glColor3f(team == BLACK ? 0.0f : 1.0f, 0.0f, 0.0f); // Black or white pawn
            break;
        case ROOK:
            glColor3f(0.8f, 0.5f, 0.0f); // Brown for rook
            break;
        case KNIGHT:
            glColor3f(0.5f, 0.2f, 0.8f); // Purple for knight
            break;
        case BISHOP:
            glColor3f(0.0f, 0.5f, 0.8f); // Blue for bishop
            break;
        case QUEEN:
            glColor3f(1.0f, 0.5f, 0.5f); // Pink for queen
            break;
        case KING:
            glColor3f(1.0f, 1.0f, 0.0f); // Yellow for king
            break;
    }

    float size = 0.4f; // Size of the piece
    if (type == ROOK || type == KNIGHT) {
        glBegin(GL_QUADS);
        glVertex2f(x + 0.5f - size, y + 0.5f - size);
        glVertex2f(x + 0.5f + size, y + 0.5f - size);
        glVertex2f(x + 0.5f + size, y + 0.5f + size);
        glVertex2f(x + 0.5f - size, y + 0.5f + size);
        glEnd();
    } else if (type == BISHOP) {
        glBegin(GL_TRIANGLES);
        glVertex2f(x + 0.5f, y + 0.5f + size);
        glVertex2f(x + 0.5f - size, y + 0.5f - size);
        glVertex2f(x + 0.5f + size, y + 0.5f - size);
        glEnd();
    } else {
        // Pawns, Queen, and King as circles
        int segments = 100;
        glBegin(GL_TRIANGLE_FAN);
        glVertex2f(x + 0.5f, y + 0.5f);
        for (int i = 0; i <= segments; ++i) {
            float angle = i * 2.0f * 3.14159f / segments;
            float dx = size * cos(angle);
            float dy = size * sin(angle);
            glVertex2f(x + 0.5f + dx, y + 0.5f + dy);
        }
        glEnd();
    }
}

std::vector<std::pair<int, int>> ChessPiece::getPossibleMoves(const std::vector<std::vector<ChessPiece*>>& board) const {
    std::vector<std::pair<int, int>> moves;

    switch (type) {
        case PAWN: {
            int direction = (team == WHITE) ? 1 : -1;
            if (y + direction >= 0 && y + direction < 8 && board[y + direction][x] == nullptr) {
                moves.push_back({x, y + direction});
            }
            break;
        }
        case ROOK: {
            for (int i = y + 1; i < 8; ++i) {
                if (board[i][x] == nullptr) {
                    moves.push_back({x, i});
                } else break;
            }
            for (int i = y - 1; i >= 0; --i) {
                if (board[i][x] == nullptr) {
                    moves.push_back({x, i});
                } else break;
            }
            for (int i = x + 1; i < 8; ++i) {
                if (board[y][i] == nullptr) {
                    moves.push_back({i, y});
                } else break;
            }
            for (int i = x - 1; i >= 0; --i) {
                if (board[y][i] == nullptr) {
                    moves.push_back({i, y});
                } else break;
            }
            break;
        }
        case BISHOP: {
            for (int i = 1; x + i < 8 && y + i < 8; ++i) {
                if (board[y + i][x + i] == nullptr) {
                    moves.push_back({x + i, y + i});
                } else break;
            }
            for (int i = 1; x - i >= 0 && y + i < 8; ++i) {
                if (board[y + i][x - i] == nullptr) {
                    moves.push_back({x - i, y + i});
                } else break;
            }
            for (int i = 1; x + i < 8 && y - i >= 0; ++i) {
                if (board[y - i][x + i] == nullptr) {
                    moves.push_back({x + i, y - i});
                } else break;
            }
            for (int i = 1; x - i >= 0 && y - i >= 0; ++i) {
                if (board[y - i][x - i] == nullptr) {
                    moves.push_back({x - i, y - i});
                } else break;
            }
            break;
        }
        case KNIGHT: {
            const std::vector<std::pair<int, int>> knightMoves = {
                {x + 1, y + 2}, {x + 1, y - 2}, {x - 1, y + 2}, {x - 1, y - 2},
                {x + 2, y + 1}, {x + 2, y - 1}, {x - 2, y + 1}, {x - 2, y - 1}
            };
            for (const auto& move : knightMoves) {
                if (move.first >= 0 && move.first < 8 && move.second >= 0 && move.second < 8 &&
                    (board[move.second][move.first] == nullptr || board[move.second][move.first]->team != team)) {
                    moves.push_back(move);
                }
            }
            break;
        }
        case QUEEN: {
            // Queen moves like both a rook and a bishop
            // Rook-like moves
            for (int i = y + 1; i < 8; ++i) {
                if (board[i][x] == nullptr) {
                    moves.push_back({x, i});
                } else break;
            }
            for (int i = y - 1; i >= 0; --i) {
                if (board[i][x] == nullptr) {
                    moves.push_back({x, i});
                } else break;
            }
            for (int i = x + 1; i < 8; ++i) {
                if (board[y][i] == nullptr) {
                    moves.push_back({i, y});
                } else break;
            }
            for (int i = x - 1; i >= 0; --i) {
                if (board[y][i] == nullptr) {
                    moves.push_back({i, y});
                } else break;
            }
            // Bishop-like moves
            for (int i = 1; x + i < 8 && y + i < 8; ++i) {
                if (board[y + i][x + i] == nullptr) {
                    moves.push_back({x + i, y + i});
                } else break;
            }
            for (int i = 1; x - i >= 0 && y + i < 8; ++i) {
                if (board[y + i][x - i] == nullptr) {
                    moves.push_back({x - i, y + i});
                } else break;
            }
            for (int i = 1; x + i < 8 && y - i >= 0; ++i) {
                if (board[y - i][x + i] == nullptr) {
                    moves.push_back({x + i, y - i});
                } else break;
            }
            for (int i = 1; x - i >= 0 && y - i >= 0; ++i) {
                if (board[y - i][x - i] == nullptr) {
                    moves.push_back({x - i, y - i});
                } else break;
            }
            break;
        }
        case KING: {
            const std::vector<std::pair<int, int>> kingMoves = {
                {x + 1, y}, {x - 1, y}, {x, y + 1}, {x, y - 1},
                {x + 1, y + 1}, {x - 1, y + 1}, {x + 1, y - 1}, {x - 1, y - 1}
            };
            for (const auto& move : kingMoves) {
                if (move.first >= 0 && move.first < 8 && move.second >= 0 && move.second < 8 &&
                    (board[move.second][move.first] == nullptr || board[move.second][move.first]->team != team)) {
                    moves.push_back(move);
                }
            }
            break;
        }
    }
    return moves;
}

void ChessPiece::move(int newX, int newY) {
    x = newX;
    y = newY;
}
