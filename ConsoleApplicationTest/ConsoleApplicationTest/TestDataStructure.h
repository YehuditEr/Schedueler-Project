#pragma once

#include <time.h>
#include <stdbool.h>

#include "LibScheduler/Task.h"
#include "LibScheduler/Scheduler.h"

#define MAX_PUSH_TASK 1000

/// <summary>
/// Information about a task running on the processor:
///		beginTimeInQueues - begin time in queues
///		endTimeInQueues = end time in queues
///		numTimesInCpu - several times in the cpu
///		totalRunningTimeInCpu - Total CPU runtime
///		orginalTask - Original task as entered into the system
///		updateTask - A task as it exits the system
/// </summary>
struct TaskRunMetaData
{
	clock_t beginTimeInQueues;
	clock_t endTimeInQueues;
	int numTimesInCpu;
	double totalRunningTimeInCpu;
	Task* orginalTask;
	Task* updateTask;
};

typedef struct TaskRunMetaData TaskRunMetaData;


/// <summary>
/// Information about the status of the test:
///		numTasksPush - Number of tasks pushed to the queue by the test
///		tasksRunMetaData - An array with extensive information on all tasks pushed to the system
/// </summary>
struct TestDataStructure
{
	int numTasksPush;
	TaskRunMetaData** tasksRunMetaData;
};

typedef struct TestDataStructure TestDataStructure;

TestDataStructure* testDataStructure;



/* initialization and allocted of TestDataStructure */
void initTestDataStructure();

/* initialization and allocted of TaskRunMetaData */
void initTaskRunMetaData();

/* Entering the task details into the task information array - tasksRunMetaData */
void enterTaskValuesInTasksRunMetaData(Task* t);

/* Update of the task details in the task information array - tasksRunMetaData */
void updateTaskDataInTasksRunMetaData(Task* t);

/* Adding a random task to the system */
void addRandomTask();

/* increase num tasks in the system */
void increaseNumTasksPush();

/* get number of tasks pushed to the queue by the test */
int getNumTasksPush();

/* Lottery between 0 and 1 to check whether to push values or not */
bool isPushTask();

/* Going through all the tasks in the system and checking their timeout that does not pass */
void testTasksTO();

void checkResultTest();

void printTest();

void tst_random();


