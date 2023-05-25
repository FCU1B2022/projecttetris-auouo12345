#include "Tetris.h"

int main(void)
{
    srand(time(NULL));
    State state = 
    {
        WIDTH / 2,
        0,
        0,
        0,
        0
    };

    for (int i = 0; i < 4; i++)
    {
        state.queue[i] = rand() % 7;
    }

    Block canvas[HEIGHT][WIDTH];
    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            resetBlock(&canvas[i][j]);
        }
    }

    system("cls");
    printf("\e[?25l"); // hide cursor

    move(canvas, state.x, state.y, state.rotate, state.x, state.y, state.rotate, state.queue[0]);

    while (1)
    {
        logic(canvas, &state);
        printCanvas(canvas, &state);
        Sleep(100);
    }

    return 0;
}