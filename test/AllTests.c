

/* This is auto-generated code. Edit at your own peril. */
#include <stdio.h>
#include <stdlib.h>

#include "CuTest.h"


extern void TestFftFlatSignal(CuTest*);
extern void TestFftRossetaCode(CuTest*);
extern void TestFftSineSignal(CuTest*);
extern void TestInverseFftSineSignal(CuTest*);


void RunAllTests(void) 
{
    CuString *output = CuStringNew();
    CuSuite* suite = CuSuiteNew();


    SUITE_ADD_TEST(suite, TestFftFlatSignal);
    SUITE_ADD_TEST(suite, TestFftRossetaCode);
    SUITE_ADD_TEST(suite, TestFftSineSignal);
    SUITE_ADD_TEST(suite, TestInverseFftSineSignal);

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

