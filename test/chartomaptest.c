
/* This tests D_CharToMap() in d.h. It does not
 *  test every character but if some work they
 *  should all work, especially the first and
 *  last.
 *
 * This test is part of autotest.c.
 */

int D_CharToMapSubTest(char c, int eX, int eY, int eRet){
    int x = -2;
    int y = -2;

    int ret = D_CharToMap(c, &x, &y);

    TEST_PRINTF_V0("Char %c,   x: %d y: %d\nShould be x: %d y: %d\n", c, x, y, eX, eY);

    TEST_PRINTF_V0("returned %d\n", ret);

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

    TEST_PRINTF_V0("Test capital letters\n");
    failedTests += D_CharToMapSubTest('A', 0, 0, 0);
    failedTests += D_CharToMapSubTest('B', 1, 0, 0);
    failedTests += D_CharToMapSubTest('F', 5, 0, 0);
    failedTests += D_CharToMapSubTest('Z', 7, 2, 0);

    TEST_PRINTF_V0("\nTest lower case letters\n");
    failedTests += D_CharToMapSubTest('a', 0, 3, 0);
    failedTests += D_CharToMapSubTest('b', 1, 3, 0);
    failedTests += D_CharToMapSubTest('n', 4, 4, 0);
    failedTests += D_CharToMapSubTest('u', 2, 5, 0);
    failedTests += D_CharToMapSubTest('z', 7, 5, 0);

    TEST_PRINTF_V0("\nTest numbers\n");
    failedTests += D_CharToMapSubTest('0', 0, 6, 0);
    failedTests += D_CharToMapSubTest('1', 1, 6, 0);
    failedTests += D_CharToMapSubTest('2', 2, 6, 0);
    failedTests += D_CharToMapSubTest('7', 7, 6, 0);
    failedTests += D_CharToMapSubTest('9', 0, 7, 0);

    TEST_PRINTF_V0("\nTest some symbols\n");
    failedTests += D_CharToMapSubTest('.', 1, 7, 0);
    failedTests += D_CharToMapSubTest(',', 2, 7, 0);
    failedTests += D_CharToMapSubTest('!', 8, 7, 0);
    failedTests += D_CharToMapSubTest('"', 0, 8, 0);
    failedTests += D_CharToMapSubTest('@', 7, 8, 0);

    TEST_PRINTF_V0("\nTest some more symbols\n");
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
