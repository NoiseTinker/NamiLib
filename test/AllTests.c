

/* This is auto-generated code. Edit at your own peril. */
#include <stdio.h>
#include <stdlib.h>

#include "CuTest.h"


extern void TestFftFlatSignal(CuTest*);
extern void TestFftRossetaCode(CuTest*);
extern void TestSine(CuTest*);
extern void TestSquare(CuTest*);
extern void TestTriangle(CuTest*);
extern void TestSawtooth(CuTest*);
extern void TestAddFunction(CuTest*);
extern void TestAddWayPoints(CuTest*);
extern void TestClear(CuTest*);


void RunAllTests(void) 
{
    CuString *output = CuStringNew();
    CuSuite* suite = CuSuiteNew();


    SUITE_ADD_TEST(suite, TestFftFlatSignal);
    SUITE_ADD_TEST(suite, TestFftRossetaCode);
    SUITE_ADD_TEST(suite, TestSine);
    SUITE_ADD_TEST(suite, TestSquare);
    SUITE_ADD_TEST(suite, TestTriangle);
    SUITE_ADD_TEST(suite, TestSawtooth);
    SUITE_ADD_TEST(suite, TestAddFunction);
    SUITE_ADD_TEST(suite, TestAddWayPoints);
    SUITE_ADD_TEST(suite, TestClear);

    CuSuiteRun(suite);
    CuSuiteSummary(suite, output);
    CuSuiteDetails(suite, output);
    printf("%s\n", output->buffer);
    CuStringDelete(output);
    CuSuiteDelete(suite);
}

int main(void)
{
    RunAllTests();
}

