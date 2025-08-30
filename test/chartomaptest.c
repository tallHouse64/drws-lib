
/* This tests D_CharToMap() in d.h. It tests each
 *  recognised character.
 *
 * This test is part of autotest.c.
 */

int D_CharToMapSubTest(char c, int eX, int eY, int eRet){
    int x = -2;
    int y = -2;

    int ret = D_CharToMap(c, &x, &y);

    TEST_PRINTF_V0("Char %c,   x: %d y: %d return: %d\nShould be x: %d y: %d return: %d ", c, x, y, ret, eX, eY, eRet);


    if(x == eX && y == eY && ret == eRet){
        TEST_PRINTF_V0("Success\n\n");
        return 0;
    }else{
        TEST_PRINTF_V0("Failed\n\n");
        return 1;
    };

    return 1;
};

int D_CharToMapTest(){

    int failedTests = 0;

    TEST_PRINTF_V0("Test the capital letters\n");
    failedTests += D_CharToMapSubTest('A', 0, 0, 0);
    failedTests += D_CharToMapSubTest('B', 1, 0, 0);
    failedTests += D_CharToMapSubTest('C', 2, 0, 0);
    failedTests += D_CharToMapSubTest('D', 3, 0, 0);
    failedTests += D_CharToMapSubTest('E', 4, 0, 0);
    failedTests += D_CharToMapSubTest('F', 5, 0, 0);
    failedTests += D_CharToMapSubTest('G', 6, 0, 0);
    failedTests += D_CharToMapSubTest('H', 7, 0, 0);
    failedTests += D_CharToMapSubTest('I', 8, 0, 0);
    failedTests += D_CharToMapSubTest('J', 0, 1, 0);
    failedTests += D_CharToMapSubTest('K', 1, 1, 0);
    failedTests += D_CharToMapSubTest('L', 2, 1, 0);
    failedTests += D_CharToMapSubTest('M', 3, 1, 0);
    failedTests += D_CharToMapSubTest('N', 4, 1, 0);
    failedTests += D_CharToMapSubTest('O', 5, 1, 0);
    failedTests += D_CharToMapSubTest('P', 6, 1, 0);
    failedTests += D_CharToMapSubTest('Q', 7, 1, 0);
    failedTests += D_CharToMapSubTest('R', 8, 1, 0);
    failedTests += D_CharToMapSubTest('S', 0, 2, 0);
    failedTests += D_CharToMapSubTest('T', 1, 2, 0);
    failedTests += D_CharToMapSubTest('U', 2, 2, 0);
    failedTests += D_CharToMapSubTest('V', 3, 2, 0);
    failedTests += D_CharToMapSubTest('W', 4, 2, 0);
    failedTests += D_CharToMapSubTest('X', 5, 2, 0);
    failedTests += D_CharToMapSubTest('Y', 6, 2, 0);
    failedTests += D_CharToMapSubTest('Z', 7, 2, 0);

    TEST_PRINTF_V0("\nTest the lower case letters\n");
    failedTests += D_CharToMapSubTest('a', 0, 3, 0);
    failedTests += D_CharToMapSubTest('b', 1, 3, 0);
    failedTests += D_CharToMapSubTest('c', 2, 3, 0);
    failedTests += D_CharToMapSubTest('d', 3, 3, 0);
    failedTests += D_CharToMapSubTest('e', 4, 3, 0);
    failedTests += D_CharToMapSubTest('f', 5, 3, 0);
    failedTests += D_CharToMapSubTest('g', 6, 3, 0);
    failedTests += D_CharToMapSubTest('h', 7, 3, 0);
    failedTests += D_CharToMapSubTest('i', 8, 3, 0);
    failedTests += D_CharToMapSubTest('j', 0, 4, 0);
    failedTests += D_CharToMapSubTest('k', 1, 4, 0);
    failedTests += D_CharToMapSubTest('l', 2, 4, 0);
    failedTests += D_CharToMapSubTest('m', 3, 4, 0);
    failedTests += D_CharToMapSubTest('n', 4, 4, 0);
    failedTests += D_CharToMapSubTest('o', 5, 4, 0);
    failedTests += D_CharToMapSubTest('p', 6, 4, 0);
    failedTests += D_CharToMapSubTest('q', 7, 4, 0);
    failedTests += D_CharToMapSubTest('r', 8, 4, 0);
    failedTests += D_CharToMapSubTest('s', 0, 5, 0);
    failedTests += D_CharToMapSubTest('t', 1, 5, 0);
    failedTests += D_CharToMapSubTest('u', 2, 5, 0);
    failedTests += D_CharToMapSubTest('v', 3, 5, 0);
    failedTests += D_CharToMapSubTest('w', 4, 5, 0);
    failedTests += D_CharToMapSubTest('x', 5, 5, 0);
    failedTests += D_CharToMapSubTest('y', 6, 5, 0);
    failedTests += D_CharToMapSubTest('z', 7, 5, 0);

    TEST_PRINTF_V0("\nTest the numbers\n");
    failedTests += D_CharToMapSubTest('0', 0, 6, 0);
    failedTests += D_CharToMapSubTest('1', 1, 6, 0);
    failedTests += D_CharToMapSubTest('2', 2, 6, 0);
    failedTests += D_CharToMapSubTest('3', 3, 6, 0);
    failedTests += D_CharToMapSubTest('4', 4, 6, 0);
    failedTests += D_CharToMapSubTest('5', 5, 6, 0);
    failedTests += D_CharToMapSubTest('6', 6, 6, 0);
    failedTests += D_CharToMapSubTest('7', 7, 6, 0);
    failedTests += D_CharToMapSubTest('8', 8, 6, 0);
    failedTests += D_CharToMapSubTest('9', 0, 7, 0);

    TEST_PRINTF_V0("\nTest the first symbols\n");
    failedTests += D_CharToMapSubTest('.', 1, 7, 0);
    failedTests += D_CharToMapSubTest(',', 2, 7, 0);
    failedTests += D_CharToMapSubTest(';', 3, 7, 0);
    failedTests += D_CharToMapSubTest(':', 4, 7, 0);
    failedTests += D_CharToMapSubTest('$', 5, 7, 0);
    failedTests += D_CharToMapSubTest('#', 6, 7, 0);
    failedTests += D_CharToMapSubTest('\'', 7, 7, 0);
    failedTests += D_CharToMapSubTest('!', 8, 7, 0);

    failedTests += D_CharToMapSubTest('"', 0, 8, 0);
    failedTests += D_CharToMapSubTest('/', 1, 8, 0);
    failedTests += D_CharToMapSubTest('?', 2, 8, 0);
    failedTests += D_CharToMapSubTest('%', 3, 8, 0);
    failedTests += D_CharToMapSubTest('&', 4, 8, 0);
    failedTests += D_CharToMapSubTest('(', 5, 8, 0);
    failedTests += D_CharToMapSubTest(')', 6, 8, 0);
    failedTests += D_CharToMapSubTest('@', 7, 8, 0);

    TEST_PRINTF_V0("\nTest the extra symbols\n");
    failedTests += D_CharToMapSubTest('^', 0, 9, 0);
    failedTests += D_CharToMapSubTest('*', 1, 9, 0);
    failedTests += D_CharToMapSubTest('-', 2, 9, 0);
    failedTests += D_CharToMapSubTest('_', 3, 9, 0);
    failedTests += D_CharToMapSubTest('+', 4, 9, 0);
    failedTests += D_CharToMapSubTest('=', 5, 9, 0);
    failedTests += D_CharToMapSubTest('|', 6, 9, 0);
    failedTests += D_CharToMapSubTest('\\', 7, 9, 0);
    failedTests += D_CharToMapSubTest('{', 8, 9, 0);

    failedTests += D_CharToMapSubTest('}', 0, 10, 0);
    failedTests += D_CharToMapSubTest('[', 1, 10, 0);
    failedTests += D_CharToMapSubTest(']', 2, 10, 0);
    failedTests += D_CharToMapSubTest('<', 3, 10, 0);
    failedTests += D_CharToMapSubTest('>', 4, 10, 0);
    failedTests += D_CharToMapSubTest('~', 5, 10, 0);
    failedTests += D_CharToMapSubTest('`', 6, 10, 0);

    TEST_PRINTF_V0("\nNull character test\n");
    failedTests += D_CharToMapSubTest(D_NULL, -2, -2, -1);

    TEST_PRINTF_V1("\nD_CharToMapTest overall ");
    if(failedTests == 0){
        TEST_PRINTF_V1("Success\n\n");
        return 0;
    }else{
        TEST_PRINTF_V1("Failed (%d subtests failed)\n\n", failedTests);
        return 1;
    };

    return 1;
};
