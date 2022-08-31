
#include <stdlib.h>
#include <stdio.h>

#include "TestDataStructure.h"


void init() {
	initTestDataStructure();
	initDataStructure();
	initPriorities();
}

void makeTestToRun(void (*fn)()) {
	fn();
	checkResultTest();
	printTest();
}


int main()
{
	init();

	makeTestToRun(tst_random);
}