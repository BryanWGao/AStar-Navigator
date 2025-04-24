#include <stdio.h>
#include "map.h"
#include "path.h"

int main() {
    
    loadMap("map.txt");
    printf("Initial Map State：\n");
    printMap();

    
    printf("Starting Position: (%d, %d)\n", startX, startY);
    printf("Ending Position: (%d, %d)\n", endX, endY);

    
    MyPoint stop1 = {3, 4};  
    MyPoint stop2 = {5, 1};  
 
    runPathFindingWithStops(stop1, stop2);

    printf("\nMap with Path Labeled：\n");
    printMap();

    return 0;
}

