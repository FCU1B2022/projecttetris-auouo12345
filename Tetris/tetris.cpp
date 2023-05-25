#include "Tetris.h"

Shape shapes[7] =
{
    {
        I,
        CYAN,
        4,
        {
            {
                {0, 0, 0, 0},
                {1, 1, 1, 1},
                {0, 0, 0, 0},
                {0, 0, 0, 0}
            },
            {
                {0, 0, 1, 0},
                {0, 0, 1, 0},
                {0, 0, 1, 0},
                {0, 0, 1, 0}
            },
            {
                {0, 0, 0, 0},
                {0, 0, 0, 0},
                {1, 1, 1, 1},
                {0, 0, 0, 0}
            },
            {
                {0, 1, 0, 0},
                {0, 1, 0, 0},
                {0, 1, 0, 0},
                {0, 1, 0, 0}
            }
        }
    },
    {
        J,
        BLUE,
        3,
        {
            {
                {1, 0, 0},
                {1, 1, 1},
                {0, 0, 0}
            },
            {
                {0, 1, 1},
                {0, 1, 0},
                {0, 1, 0}
            },
            {
                {0, 0, 0},
                {1, 1, 1},
                {0, 0, 1}
            },
            {
                {0, 1, 0},
                {0, 1, 0},
                {1, 1, 0}
            }
        }
    },
    {
        L,
        YELLOW,
        3,
        {
            {
                {0, 0, 1},
                {1, 1, 1},
                {0, 0, 0}
            },
            {
                {0, 1, 0},
                {0, 1, 0},
                {0, 1, 1}
            },
            {
                {0, 0, 0},
                {1, 1, 1},
                {1, 0, 0}
            },
            {
                {1, 1, 0},
                {0, 1, 0},
                {0, 1, 0}
            }
        }
    },
    {
        O,
        WHITE,
        2,
        {
            {
                {1, 1},
                {1, 1}
            },
            {
                {1, 1},
                {1, 1}
            },
            {
                {1, 1},
                {1, 1}
            },
            {
                {1, 1},
                {1, 1}
            }
        }
    },
    {
        S,
        GREEN,
        3,
        {
            {
                {0, 1, 1},
                {1, 1, 0},
                {0, 0, 0}
            },
            {
                {0, 1, 0},
                {0, 1, 1},
                {0, 0, 1}
            },
            {
                {0, 0, 0},
                {0, 1, 1},
                {1, 1, 0}
            },
            {
                {1, 0, 0},
                {1, 1, 0},
                {0, 1, 0}
            }
        }
    },
    {
        T,
        PURPLE,
        3,
        {
            {
                {0, 1, 0},
                {1, 1, 1},
                {0, 0, 0}
            },
            {
                {0, 1, 0},
                {0, 1, 1},
                {0, 1, 0}
            },
            {
                {0, 0, 0},
                {1, 1, 1},
                {0, 1, 0}
            },
            {
                {0, 1, 0},
                {1, 1, 0},
                {0, 1, 0}
            }
        }
    },
    {
        Z,
        RED,
        3,
        {
            {
                {1, 1, 0},
                {0, 1, 1},
                {0, 0, 0}
            },
            {
                {0, 0, 1},
                {0, 1, 1},
                {0, 1, 0}
            },
            {
                {0, 0, 0},
                {1, 1, 0},
                {0, 1, 1}
            },
            {
                {0, 1, 0},
                {1, 1, 0},
                {1, 0, 0}
            }
        }
    },
};

void setBlock(Block* block, int color, int shape, bool current)
{
    block->color = color;
    block->shape = shape;
    block->current = current;
}

void resetBlock(Block* block)
{
    block->color = BLACK;
    block->shape = EMPTY;
    block->current = false;
}

bool move(Block canvas[HEIGHT][WIDTH], int originalX, int originalY, int originalRotate, int newX, int newY, int newRotate, int shapeId) {
    Shape shapeData = shapes[shapeId];
    int size = shapeData.size;

    // check if the new position is valid to place the block
    for (int i = 0; i < size; i++) 
    {
        for (int j = 0; j < size; j++) 
        {
            if (shapeData.rotates[newRotate][i][j]) 
            {
                if (newX + j < 0 || newX + j >= WIDTH || newY + i < 0 || newY + i >= HEIGHT) return false;
                if (!canvas[newY + i][newX + j].current && canvas[newY + i][newX + j].shape != EMPTY) return false;
            }
        }
    }

    // remove the old position
    for (int i = 0; i < size; i++) 
    {
        for (int j = 0; j < size; j++) 
        {
            if (shapeData.rotates[originalRotate][i][j]) resetBlock(&canvas[originalY + i][originalX + j]);
        }
    }

    // move the block
    for (int i = 0; i < size; i++) 
    {
        for (int j = 0; j < size; j++) {
            if (shapeData.rotates[newRotate][i][j]) setBlock(&canvas[newY + i][newX + j], shapeData.color, shapeId, true);
        }
    }

    return true;
}

void printCanvas(Block canvas[HEIGHT][WIDTH], State* state)
{
    printf("\033[0;0H\n");
    for (int i = 0; i < HEIGHT; i++) 
    {
        printf("|");
        for (int j = 0; j < WIDTH; j++) printf("\033[%dm\u3000", canvas[i][j].color);
        printf("\033[0m|\n");
    }
    return;
}

void logic(Block canvas[HEIGHT][WIDTH], State* state)
{
    if (move(canvas, state->x, state->y, state->rotate, state->x, state->y + 1, state->rotate, state->queue[0])) state->y++;
    return;
}