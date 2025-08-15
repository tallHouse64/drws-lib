#include"../devents.h"

/* The purpose of this test is to find where the
 *  devents.h file does not meet the C89 standard
 *  (when D_IMPLEMENTATION is not defined).
 *
 * Run this test with "gcc stdc89testdeventsh.c ../d.h --std=c89".
 */

int main(int argc, char ** argv){
    return 0;
};
