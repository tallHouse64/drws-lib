#include<stdio.h>

#define D_IMPLEMENTATION
#include"../d.h"

int test(char c, int eX, int eY){
    int x = -1;
    int y = -1;

    int ret = D_CharToMap(c, &x, &y);

    printf("Char %c,   x: %d y: %d\nShould be x: %d y: %d\n", c, x, y, eX, eY);

    printf("returned %d\n\n", ret);

    return 0;
};

int main(){
    test('A', 0, 0);
    test('B', 1, 0);
    test('F', 5, 0);
    test('Z', 7, 2);
};
