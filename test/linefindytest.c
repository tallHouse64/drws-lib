#define D_IMPLEMENTATION
#include"../d.h"

#include<stdio.h>

D_Point a = {10, 40};
D_Point b = {21, 3};

int y = -99;


int test(int x, int expectedY){
    printf("a x: %d y: %d\n", a.x, a.y);
    printf("b x: %d y: %d\n", b.x, b.y);
    printf("          x: %d\n", x);

    int ret = D_LineFindY(&a, &b, x, &y);
    printf("          y: %d\n", y);
    printf("y should be: %d\n", expectedY);
    printf("returned: %d\n\n", ret);
};

int main(){
    printf("D_LineFindY() test\n\n");

    printf("Normal tests, valid data. Should all return 0.\n\n");
    test(10, 40);
    test(21, 3);
    test(11, 36);
    test(-2, 80); //close enough
    test(24, -7);

    printf("Error tests, infinate y result. Should all return -2.\n\n");
    a.x = 21;
    test(1, -7);
    test(21, -7);
    test(22, -7);

    printf("Error tests, null pointers. Should all return -1.\n\n");
    a.x = 10;
    printf("a null, returned: %d\n", D_LineFindY(D_NULL, &b, 1, &y));
    printf("b null, returned: %d\n", D_LineFindY(&a, D_NULL, 2, &y));
    printf("y null, returned: %d\n", D_LineFindY(&a, &b, 3, D_NULL));
};
