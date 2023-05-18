#include <iostream>
#include <Windows.h>

#define HEIGHT 20
#define WIDTH 10

#define RED  41
#define GREEN 42
#define YELLOW 43
#define BLUE 44
#define PURPLE 45
#define CYAN 46
#define WHITE 47
#define BLACK  0


#define EMPTY -1
#define I 0
#define J 1
#define L 2
#define O 3
#define S 4
#define T 5
#define Z 6

typedef struct 
{
    int shape;
    int color;
    int size;
    char rotates[4][4][4];
} Shape;

typedef struct
{
    int x;
    int y;
    int score;
    int rotate;
    int fallTime;
    int queue[4];
}State;

typedef struct {
    int color;
    int shape;
    bool current;
}Block;

Shape shapes[];

void setBlock(Block*, int color, int shape, bool);
void resetBlock(Block*);
bool move(Block canvas[HEIGHT][WIDTH], int, int, int, int, int, int, int);
void printCanvas(Block canvas[HEIGHT][WIDTH], State*);
void logic(Block canvas[HEIGHT][WIDTH], State*);