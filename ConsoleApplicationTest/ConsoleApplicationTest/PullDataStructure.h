#pragma once
#include <LibScheduler/Task.h>
#include <LibScheduler/Definitions.h>

#define NUM_TASKS_IN_PULL_TO_TEST_TO_QUEUE3 17
#define MAX_SIZE_TASK_PRIORITY3 66.6
#define MAX_SIZE_TASK_PRIORITY2 100
#define MAX_SIZE_TASK_PRIORITY1 200

struct Pull
{
	Task** tasks;
	int numTasks;
	int currentNumTasks;
	int iterator;
};

typedef struct Pull Pull;

Pull* pull;

void initPull(int numTasks);

void addTaskToPull(Task* task);

void fillPullToTestTOQueue3();

Task* getTaskFromPull();

void fillPullToTestTOQueue2();
void fillDataStructureToTestTOQueue3();

void fillDataStructureToTestTOQueue2();
void printPull();


