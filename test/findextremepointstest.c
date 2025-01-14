#include<stdio.h>

#define D_IMPLEMENTATION
#include"../d.h"

D_Point p[7] = {{13, 5}, {78, 21}, {-3, -1}, {0, -7}, {9, 1}, {-1, -24}, {4, 4}};

int main(){

    //remember highest and lowest are indexes
    int highest = -99;
    int lowest = -99;
    int ret = -99;

    printf("Testing D_FindExtremePoints()\nRemember highest and lowest are indexes.\n\n");

    printf("Normal test, valid data.\n");
    ret = D_FindExtremePoints(p, 7, &highest, &lowest);


    printf("          Highest %d, lowest %d, return %d\n", highest, lowest, ret);
    printf("should be Highest 5, lowest 1, return 0\n\n");



    highest = -99;
    lowest = -99;
    ret = -99;

    printf("Normal test, valid data, null for highest.\n");
    ret = D_FindExtremePoints(p, 7, D_NULL, &lowest);


    printf("          Highest %d, lowest %d, return %d\n", highest, lowest, ret);
    printf("should be Highest -99, lowest 1, return 0\n\n");



    highest = -99;
    lowest = -99;
    ret = -99;

    printf("Normal test, valid data, null for lowest.\n");
    ret = D_FindExtremePoints(p, 7, &highest, D_NULL);


    printf("          Highest %d, lowest %d, return %d\n", highest, lowest, ret);
    printf("should be Highest 5, lowest -99, return 0\n\n");



    highest = -99;
    lowest = -99;
    ret = -99;

    printf("Normal test, valid data, null for highest and lowest.\n");
    ret = D_FindExtremePoints(p, 7, D_NULL, D_NULL);


    printf("          Highest %d, lowest %d, return %d\n", highest, lowest, ret);
    printf("should be Highest -99, lowest -99, return 0\n\n");



    highest = -99;
    lowest = -99;
    ret = -99;

    printf("Error test, null for p.\n");
    ret = D_FindExtremePoints(D_NULL, 7, &highest, &lowest);


    printf("          Highest %d, lowest %d, return %d\n", highest, lowest, ret);
    printf("should be Highest -99, lowest -99, return -2\n\n");



    printf("Error test, numPoints is 0.\n");
    highest = -99;
    lowest = -99;
    ret = -99;

    ret = D_FindExtremePoints(p, 0, &highest, &lowest);

    printf("          Highest %d, lowest %d, return %d\n", highest, lowest, ret);
    printf("should be Highest -99, lowest -99, return -1\n\n");

};
