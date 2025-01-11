#define D_IMPLEMENTATION
#include"../d.h"

#include<stdio.h>

int main(){
    D_Point points[8] = {{1, 5}, {-4, 19}, {15, 20}, {2, 4}, {5, 7}, {-1, -4}, {5, -19}, {3, 2}};

    printf("D_FindHighestPoint() test\n\n");

    printf("Should find 6\nFound       %d\n\n", D_FindHighestPoint(points, 8));

    printf("Should error with -1\nFound             %d\n\n", D_FindHighestPoint(points, 0));

    printf("Should find 0\nFound       %d\n\n", D_FindHighestPoint(points, 1));


    return 0;
};
