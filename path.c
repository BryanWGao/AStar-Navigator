#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "map.h"
#include "path.h"

#define MAX_CHILDREN 4
#define INF 999999

enum direct { 
    p_up, p_down, p_left, p_right 
};

Node* createTreeNode(int row, int col) {
    Node* pNew = (Node*)malloc(sizeof(Node));
    memset(pNew, 0, sizeof(Node));
    pNew->pos.row = row;
    pNew->pos.col = col;
    return pNew;
}

int getH(MyPoint pos, MyPoint endPos) {
    return abs(pos.row - endPos.row) + abs(pos.col - endPos.col);
}

void tracePath(Node* endNode) {
    Node* p = endNode;
    while (p->pParent != NULL) {
        map[p->pos.row][p->pos.col] = '*';
        p = p->pParent;
    }
    map[startX][startY] = 'S';
    map[endX][endY] = 'E';
}

typedef struct {
    MyPoint start;
    MyPoint end;
} PathTask;

void runAStar(MyPoint startPos, MyPoint endPos) {
    Node* pRoot = createTreeNode(startPos.row, startPos.col);
    pRoot->pos.g = 0;
    pRoot->pos.h = getH(startPos, endPos);
    pRoot->pos.f = pRoot->pos.h;

    int gMap[ROW][COL];
    for (int i = 0; i < ROW; i++)
        for (int j = 0; j < COL; j++)
            gMap[i][j] = INF;

    gMap[startPos.row][startPos.col] = 0;

    Node* buffer[1000];
    int bufferSize = 0;
    buffer[bufferSize++] = pRoot;

    while (bufferSize > 0) {
        int minIdx = 0;
        for (int i = 1; i < bufferSize; i++) {
            if (buffer[i]->pos.f < buffer[minIdx]->pos.f)
                minIdx = i;
        }

        Node* pCurrent = buffer[minIdx];
        buffer[minIdx] = buffer[--bufferSize];

        if (pCurrent->pos.row == endPos.row && pCurrent->pos.col == endPos.col) {
            tracePath(pCurrent);
            return;
        }

        for (int i = 0; i < 4; i++) {
            int newRow = pCurrent->pos.row;
            int newCol = pCurrent->pos.col;
            switch (i) {
                case p_up:    newRow--; break;
                case p_down:  newRow++; break;
                case p_left:  newCol--; break;
                case p_right: newCol++; break;
            }

            if (newRow < 0 || newRow >= ROW || newCol < 0 || newCol >= COL)
                continue;
            if (map[newRow][newCol] == '#')
                continue;

            int stepCost = getCost(map[newRow][newCol]);
            int newG = pCurrent->pos.g + stepCost;

            if (newG < gMap[newRow][newCol]) {
                gMap[newRow][newCol] = newG;

                Node* pChild = createTreeNode(newRow, newCol);
                pChild->pos.g = newG;
                pChild->pos.h = getH(pChild->pos, endPos);
                pChild->pos.f = pChild->pos.g + pChild->pos.h;
                pChild->pParent = pCurrent;
                pCurrent->child[i] = pChild;

                buffer[bufferSize++] = pChild;
            }
        }
    }
}

void runPathFindingWithStops(MyPoint stop1, MyPoint stop2) {
    runAStar((MyPoint){startX, startY}, stop1);
    runAStar(stop1, stop2);
    runAStar(stop2, (MyPoint){endX, endY});
}
