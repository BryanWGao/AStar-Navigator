#ifndef PATH_H
#define PATH_H

#include "map.h"

#define ROW 10
#define COL 10
#define MAX_CHILDREN 4

typedef struct {
    int row, col;
    int f, g, h;
} MyPoint;

typedef struct Node {
    MyPoint pos;
    struct Node* child[MAX_CHILDREN];
    struct Node* pParent;
} Node;

void tracePath(Node* endNode);
void runAStar(MyPoint startPos, MyPoint endPos);
void runPathFindingWithStops(MyPoint stop1, MyPoint stop2);

#endif



