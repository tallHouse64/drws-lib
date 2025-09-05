
/* This is different to rawformattorgbatest.c
 *
 * Some of this was copied from that file though but
 *  changed to test D_FormatTorgba().
 *
 * This test is part of autotest.c.
 */
int D_FormatTorgbaTest(){
    TEST_PRINTF_V0("D_FormatTorgba() Test.\n\n");

    int failedTests = 0;


    D_PixFormat f = D_FindPixFormat(0xFF, 0xFF00, 0xFF0000, 0xFF000000, 32);
    D_uint32 p = 0xFFE0C052; /* This is just #52C0E0 */
    int r = 0, g = 0, b = 0, a = 0;
    int eR = 0, eG = 0, eB = 0, eA = 0; /*Expected red, green, blue, alpha */

    D_FormatTorgba(p, f, &r, &g, &b, &a);
    /*Should be 82, 192, 224, 255 */
    eR = 82; eG = 192; eB = 224; eA = 255;
    TEST_PRINTF_V0("Test 1 Colour:  r: %d, g: %d, b: %d, a: %d.\n", r, g, b, a);
    TEST_PRINTF_V0("Should be:      r: %d, g: %d, b: %d, a: %d. ", eR, eG, eB, eA);
    if(r == eR && g == eG && b == eB && a == eA){
        TEST_PRINTF_V0("Success\n\n");
    }else{
        TEST_PRINTF_V0("Failed\n\n");
        failedTests++;
    };


    p = 0;
    D_FormatTorgba(p, f, &r, &g, &b, &a);
    /*Should be 0, 0, 0, 0 */
    eR = 0; eG = 0; eB = 0; eA = 0;
    TEST_PRINTF_V0("Test 2 Colour:  r: %d, g: %d, b: %d, a: %d.\n", r, g, b, a);
    TEST_PRINTF_V0("Should be:      r: %d, g: %d, b: %d, a: %d. ", eR, eG, eB, eA);
    if(r == eR && g == eG && b == eB && a == eA){
        TEST_PRINTF_V0("Success\n\n");
    }else{
        TEST_PRINTF_V0("Failed\n\n");
        failedTests++;
    };


    p = 0xC60085FF; /*#ff8500 */
    D_FormatTorgba(p, f, &r, &g, &b, &a);
    /*Should be 255, 133, 0, 198 */
    eR = 255; eG = 133; eB = 0; eA = 198;
    TEST_PRINTF_V0("Test 3 Colour:  r: %d, g: %d, b: %d, a: %d.\n", r, g, b, a);
    TEST_PRINTF_V0("Should be:      r: %d, g: %d, b: %d, a: %d. ", eR, eG, eB, eA);
    if(r == eR && g == eG && b == eB && a == eA){
        TEST_PRINTF_V0("Success\n\n");
    }else{
        TEST_PRINTF_V0("Failed\n\n");
        failedTests++;
    };


    p = 0xFFFFFFFF; /*#ffffff */
    D_FormatTorgba(p, f, &r, &g, &b, &a);
    /*Should be 255, 255, 255, 255 */
    eR = 255; eG = 255; eB = 255; eA = 255;
    TEST_PRINTF_V0("Test 4 Colour:  r: %d, g: %d, b: %d, a: %d.\n", r, g, b, a);
    TEST_PRINTF_V0("Should be:      r: %d, g: %d, b: %d, a: %d. ", eR, eG, eB, eA);
    if(r == eR && g == eG && b == eB && a == eA){
        TEST_PRINTF_V0("Success\n\n");
    }else{
        TEST_PRINTF_V0("Failed\n\n");
        failedTests++;
    };


    p = 0xFFFFFFFF; /*#ffffff */
    r = 0;
    D_FormatTorgba(p, f, D_NULL, &g, &b, &a);
    /*Should be 0, 255, 255, 255 */
    eR = 0; eG = 255; eB = 255; eA = 255;
    TEST_PRINTF_V0("Test 5 Colour:  r: %d, g: %d, b: %d, a: %d. (null r pointer test)\n", r, g, b, a);
    TEST_PRINTF_V0("Should be:      r: %d, g: %d, b: %d, a: %d. ", eR, eG, eB, eA);
    if(r == eR && g == eG && b == eB && a == eA){
        TEST_PRINTF_V0("Success\n\n");
    }else{
        TEST_PRINTF_V0("Failed\n\n");
        failedTests++;
    };



    //NDS Colour tests
    TEST_PRINTF_V0("\nNDS Format tests.\n");
    f = D_FindPixFormat(0x1F, 0x3E0, 0x7C00, 0x8000, 16);

    p = 0xFF18;
    /*    F    F    1    8
       1111 1111 0001 1000
       ABBB BBGG GGGR RRRR
       1B:31  G: 24   R: 24 */
    D_FormatTorgba(p, f, &r, &g, &b, &a);
    /*Should be 197, 197, 255, 255
         approx 200, 200, 255, 255 */
    eR = 197; eG = 197; eB = 255; eA = 255;
    TEST_PRINTF_V0("Test 6 Colour: r: %d, g: %d, b: %d, a: %d.\n", r, g, b, a);
    TEST_PRINTF_V0("Should be:      r: %d, g: %d, b: %d, a: %d. ", eR, eG, eB, eA);
    if(r == eR && g == eG && b == eB && a == eA){
        TEST_PRINTF_V0("Success\n\n");
    }else{
        TEST_PRINTF_V0("Failed\n\n");
        failedTests++;
    };


    p = 0x7678;
    /*    7    6    7    8
       0111 0110 0111 1000
       ABBB BBGG GGGR RRRR
       0B:29  G: 19   R: 24 */
    D_FormatTorgba(p, f, &r, &g, &b, &a);
    /*Should be 197, 156, 238, 0
         approx 203, 159, 240, 126 */
    eR = 197; eG = 156; eB = 238; eA = 0;
    TEST_PRINTF_V0("Test 7 Colour: r: %d, g: %d, b: %d, a: %d.\n", r, g, b, a);
    TEST_PRINTF_V0("Should be:      r: %d, g: %d, b: %d, a: %d. ", eR, eG, eB, eA);
    if(r == eR && g == eG && b == eB && a == eA){
        TEST_PRINTF_V0("Success\n\n");
    }else{
        TEST_PRINTF_V0("Failed\n\n");
        failedTests++;
    };


    p = 0xFFFF;
    D_FormatTorgba(p, f, &r, &g, &b, &a);
    /*Should be 255, 255, 255, 255 */
    eR = 255; eG = 255; eB = 255; eA = 255;
    TEST_PRINTF_V0("Test 8 Colour: r: %d, g: %d, b: %d, a: %d.\n", r, g, b, a);
    TEST_PRINTF_V0("Should be:      r: %d, g: %d, b: %d, a: %d. ", eR, eG, eB, eA);
    if(r == eR && g == eG && b == eB && a == eA){
        TEST_PRINTF_V0("Success\n\n");
    }else{
        TEST_PRINTF_V0("Failed\n\n");
        failedTests++;
    };


    p = 0;
    D_FormatTorgba(p, f, &r, &g, &b, &a);
    /*Should be 0, 0, 0, 0 */
    TEST_PRINTF_V0("Test 9 Colour: r: %d, g: %d, b: %d, a: %d.\n", r, g, b, a);
    TEST_PRINTF_V0("Should be:     r: 0, g: 0, b: 0, a: 0. ");
    if(0 == r && 0 == g && 0 == b && 0 == a){
        TEST_PRINTF_V0("Success\n\n");
    }else{
        TEST_PRINTF_V0("Failed\n\n");
        failedTests++;
    };



    TEST_PRINTF_V0("\nB&W format tests.\n");
    f = D_FindPixFormat(0xFF, 0xFF, 0xFF, 0, 8);
    p = 170;
    D_FormatTorgba(p, f, &r, &g, &b, &a);
    /*Should be 170, 170, 170, 255*/
    TEST_PRINTF_V0("Test 10 Colour: r: %d, g: %d, b: %d, a: %d.\n", r, g, b, a);
    TEST_PRINTF_V0("Should be:      r: 170, g: 170, b: 170, a: 255. ");
    if(170 == r && 170 == g && 170 == b && 255 == a){
        TEST_PRINTF_V0("Success\n\n");
    }else{
        TEST_PRINTF_V0("Failed\n\n");
        failedTests++;
    };


    p = 255;
    D_FormatTorgba(p, f, &r, &g, &b, &a);
    /*Should be 255, 255, 255, 255 */
    TEST_PRINTF_V0("Test 11 Colour: r: %d, g: %d, b: %d, a: %d.\n", r, g, b, a);
    TEST_PRINTF_V0("Should be:      r: 255, g: 255, b: 255, a: 255. ");
    if(255 == r && 255 == g && 255 == b && 255 == a){
        TEST_PRINTF_V0("Success\n\n");
    }else{
        TEST_PRINTF_V0("Failed\n\n");
        failedTests++;
    };


    /* Look into this test below another time */

    /*TEST_PRINTF_V0("\nSpecial alpha format test.\n");
    f = D_FindPixFormat(0xFF, 0xFF, 0xFF, 0xF0, 8);
    p = 181;
    D_FormatTorgba(p, f, &r, &g, &b, &a);
    //Should be 181, 181, 181, 187
    TEST_PRINTF_V0("Test 12 Colour: r: %d, g: %d, b: %d, a: %d.\n", r, g, b, a);
    TEST_PRINTF_V0("Should be:      r: 181, g: 181, b: 181, a: 197. ");
    if(181 == r && 181 == g && 181 == b && 187 == a){
        TEST_PRINTF_V0("Success\n\n");
    }else{
        TEST_PRINTF_V0("Failed\n\n");
        failedTests++;
    };*/

    TEST_PRINTF_V1("\nD_FormatTorgbaTest overall ");
    if(failedTests == 0){
        TEST_PRINTF_V1("Success\n\n");
        return 0;
    }else{
        TEST_PRINTF_V1("Failed (%d subtests failed)\n\n", failedTests);
        return 1;
    };

    return 1;
};
