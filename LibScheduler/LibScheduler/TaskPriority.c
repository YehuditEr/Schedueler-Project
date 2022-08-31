#include "pch.h"
#include "TaskPriority.h"

#pragma region Defines
#define READ "read"
#define WRITE "write"
#define DELETE "delete"

#define TIME_TO_BYTE_PRIORITY1 0.1
#define TIME_TO_BYTE_PRIORITY2 0.2
#define TIME_TO_BYTE_PRIORITY3 0.3

#define TIMEOUT_PRIORITY1 170
#define TIMEOUT_PRIORITY2 440
#define TIMEOUT_PRIORITY3 740

#define NUM_PRIORITIES 3
#pragma endregion


/*
* name - Name of priority: read/write/delete.
* timeToByte - Time to execute byte from task.
* timeOut - The latest time to finish the task.
*/
struct TaskPriority {
	char* name;
	double timeToByte;
	int timeOut;
};

typedef struct TaskPriority TaskPriority;


/* An array of all the priorities that are correct in the system */
static TaskPriority** priorities;



/* Create a PriorityTask with the received values */
TaskPriority* createTypeTask(char* name, double timeToByte, int timeOut) {
	TaskPriority* priority = calloc(1, sizeof(TaskPriority));
	assert(priority);
	priority->name = name;
	priority->timeOut = timeOut;
	priority->timeToByte = timeToByte;
	return priority;
}


/* Allocating the array and initializing it with constant values */
void initPriorities() {

	priorities = calloc(NUM_PRIORITIES, sizeof(TaskPriority*));
	assert(priorities);

	for (size_t i = 0; i < NUM_PRIORITIES; i++)
		priorities[i] = calloc(1, sizeof(TaskPriority));

	priorities[0] = createTypeTask(READ, TIME_TO_BYTE_PRIORITY1, TIMEOUT_PRIORITY1);
	priorities[1] = createTypeTask(WRITE, TIME_TO_BYTE_PRIORITY2, TIMEOUT_PRIORITY2);
	priorities[2] = createTypeTask(DELETE, TIME_TO_BYTE_PRIORITY3, TIMEOUT_PRIORITY3);

}


/* Checking that the received priority is correct */
bool isValidPriority(int priority) {
	return NUM_PRIORITIES >= priority && 0 <= priority;
}


char* getName(int priority) {
	assert(isValidPriority(priority));
	return priorities[priority - 1]->name;
}

double getTimeToByte(int priority) {
	assert(isValidPriority(priority));
	return priorities[priority - 1]->timeToByte;
}

int getTimeOut(int priority) {
	assert(isValidPriority(priority));
	return priorities[priority - 1]->timeOut;
}
