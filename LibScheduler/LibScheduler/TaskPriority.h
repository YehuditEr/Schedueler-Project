#pragma once
#pragma once
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>

/// <summary>
/// Allocating the array and initializing it with constant values
/// </summary>
void initPriorities();

char* getName(int priority);

double getTimeToByte(int priority);

int getTimeOut(int priority);

bool isValidPriority(int priority);

