#include "ChessBoard.h"
#include <GLFW/glfw3.h>

void ChessBoard::draw() const {
    bool white = true;
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (white)
                glColor3f(0.9f, 0.9f, 0.7f); // Light beige color
            else
                glColor3f(0.5f, 0.7f, 0.5f); // Light green color
            white = !white;

            glBegin(GL_QUADS);
            glVertex2f(j, i);
            glVertex2f(j + 1, i);
            glVertex2f(j + 1, i + 1);
            glVertex2f(j, i + 1);
            glEnd();
        }
        white = !white; // Alternate starting color for each row
    }
}

