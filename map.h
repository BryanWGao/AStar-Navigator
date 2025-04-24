#ifndef MAP_H
#define MAP_H

#define ROW 10
#define COL 10

extern int getCost(char n);
extern void loadMap(const char* filename);
extern void printMap();
extern char map[ROW][COL];
extern int costMap[ROW][COL];

extern int startX, startY, endX, endY;

#endif