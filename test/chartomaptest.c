#include<stdio.h>

#define D_IMPLEMENTATION
#include"../d.h"

/* This tests D_CharToMap() in d.h. It does not
 *  test every character but if some work they
 *  should all work, especially the first and
 *  last.
 */

int test(char c, int eX, int eY){
    int x = -1;
    int y = -1;

    int ret = D_CharToMap(c, &x, &y);

    printf("Char %c,   x: %d y: %d\nShould be x: %d y: %d\n", c, x, y, eX, eY);

    printf("returned %d\n\n", ret);

    return 0;
};

int main(){

    printf("Test capital letters\n");
    test('A', 0, 0);
    test('B', 1, 0);
    test('F', 5, 0);
    test('Z', 7, 2);

    printf("\nTest lower case letters\n");
    test('a', 0, 3);
    test('b', 1, 3);
    test('n', 4, 4);
    test('u', 2, 5);
    test('z', 7, 5);

    printf("\nTest numbers\n");
    test('0', 0, 6);
    test('1', 1, 6);
    test('2', 2, 6);
    test('7', 7, 6);
    test('9', 0, 7);

    printf("Test some symbols\n");
    test('.', 1, 7);
    test(',', 2, 7);
    test('!', 8, 7);
    test('"', 0, 8);
    test('@', 7, 8);
};
