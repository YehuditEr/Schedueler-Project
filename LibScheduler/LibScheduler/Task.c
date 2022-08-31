#include "pch.h"
#include "Task.h"

#pragma region Declarations of functions
void setId(Task* task, int id);
void setPriority(Task* task, int priority);
void setSize(Task* task, double size);
double getRandomSizeByPriority(int priority);
int getRandomPriority();
#pragma endregion


/* A global variable to create a different id for each task */
static int id = 0;


/* Dynamic allocate of a task */
Task* dynamicAllocationTask() {
	Task* task = calloc(1, sizeof(Task));
	return task;
}

/* Freeing dynamically allocated memory */
void freeTask(Task* task) {
	if (task != NULL)
		free(task);
}


/* Create task with values */
Task* createTask(int priority, double size) {
	Task* task = calloc(1, sizeof(Task));
	assert(task);
	setId(task, id++);
	setPriority(task, priority);
	setSize(task, size);
	return task;
}

/* Create task with random values */
Task* createRandomTask() {
	int priority = getRandomPriority();
	double size = getRandomSizeByPriority(priority);
	return createTask(priority, size);
}

/* get random priority 1/2/3 */
int getRandomPriority() {
	return (rand() % NUM_PRIORITIES) + 1;
}

/* get random size by priority */
double getRandomSizeByPriority(int priority) {
	assert(isValidPriority(priority));
	switch (priority)
	{
	case 1:
		return (rand() % 200) + 1;
	case 2:
		return (rand() % 100) + 1;
	case 3:
		return (rand() % 66) + 1;
	default:
		printf("priority %d not exist...", priority);
		exit(-1);
	}
}


/* Print all values of task */
void printTask(const Task* task) {
	assert(task);
	printf("\nTask: { id: %d, priority: %d, size : %f }\n", getId(task), getPriority(task), getSize(task));
}


Task* copyTask(Task* task) {
	assert(task);
	Task* copy = dynamicAllocationTask();
	assert(copy);
	copy->id = task->id;
	copy->priority = task->priority;
	copy->size = task->size;
	return copy;
}


/* Calculate the run time of a task */
double calculateRunTimeOfTask(const Task* task) {
	assert(task);
	double taskSize = task->size;
	double timeToByte = getTimeToByte(getPriority(task));
	return taskSize * timeToByte;
}

/* Calculation of how much of a task has been completed over a period of time */
double calculationPartTaskExecuteInPeriodTime(const Task* task, double time) {
	assert(task);
	return time / getTimeToByte(getPriority(task));
}


int getPriority(Task* task) {
	assert(task);
	return task->priority;
}
void setPriority(Task* task, int priority) {
	assert(task);
	assert(isValidPriority(priority));
	task->priority = priority;
}

int getId(Task* task) {
	assert(task);
	return task->id;
}
void setId(Task* task, int id) {
	assert(task);
	task->id = id;
}

double getSize(Task* task) {
	assert(task);
	return task->size;
}

void setSize(Task* task, double size) {
	assert(task);
	task->size = size;
}


void decreaseSizeTask(Task* task, double decreaseSize) {
	task->size -= decreaseSize;
}

double getPortionOfTaskCompletedOnTime(Task* task, double time) {
	assert(task);
	return time / getTimeToByte(getPriority(task));
}