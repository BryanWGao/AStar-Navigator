#include<stdio.h>
#include<stdlib.h>

#define ROW 10
#define COL 10

char map[ROW][COL];
int costMap[ROW][COL];
int startX, startY, endX, endY;

int getCost(char tile) {
    switch (tile) {
        case '.': return 1;   
        case 'R': return 2;   
        case 'T': return 3;   
        case '#': return -1;  
        case 'S': return 1;   
        case 'E': return 1;   
        case 'A': return 1;   
        case 'B': return 1;   
        default: return 1;   
    }
}


void loadMap(const char* filename){
    FILE *fp = NULL;
    fp = fopen(filename, "r"); 
    
    if (!fp) {
        printf("Failed to open file %s\n", filename);
        exit(1);
    }

    for (int i = 0; i < ROW; i++){
        for (int j = 0; j < COL; j++){
            fscanf(fp, " %c", &map[i][j]); 
        }
    }

    for(int i = 0; i < ROW; i++){
        for(int j = 0; j < COL; j++){
            costMap[i][j] = getCost(map[i][j]);
    }
}

    for (int i = 0; i < ROW; i++){
        for (int j = 0; j < COL; j++){
            if (map[i][j] == 'S'){
                startX = i;
                startY = j;
            }
            if (map[i][j] == 'E'){
                endX = i;
                endY = j;
            }


        }
    }   
}

void printMap(){
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            printf("%c ", map[i][j]);
        }
        printf("\n");
    }
}