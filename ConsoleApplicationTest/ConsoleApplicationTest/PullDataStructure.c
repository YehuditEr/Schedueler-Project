#include "PullDataStructure.h"

/* init data structure of pull*/
void initPull(int numTasks) {
	pull = calloc(1, sizeof(Pull*));
	assert(pull);
	pull->tasks = calloc(numTasks, sizeof(Task*));
	assert(pull->tasks);
	pull->numTasks = numTasks;
	pull->currentNumTasks = 0;
	pull->iterator = 0;
}

/* add task to array of pull in last place that empty */
void addTaskToPull(Task* task) {
	assert(pull->currentNumTasks < pull->numTasks);
	pull->tasks[pull->currentNumTasks++] = task;
}

/* remove last task from pull and return it */
Task* getTaskFromPull() {
	assert(pull->currentNumTasks > pull->iterator);
	return pull->tasks[(pull->iterator)++];
}


void fillPullToTestTOQueue3() {
	fillDataStructureToTestTOQueue3();
	initPull(NUM_TASKS_IN_PULL_TO_TEST_TO_QUEUE3);
	addTaskToPull(createTask(1, MAX_SIZE_TASK_PRIORITY1));
	addTaskToPull(createTask(1, MAX_SIZE_TASK_PRIORITY1));
	for (size_t i = 0; i < 5; i++)
	{
		addTaskToPull(createTask(2, MAX_SIZE_TASK_PRIORITY2));
		addTaskToPull(createTask(1, MAX_SIZE_TASK_PRIORITY1));
		addTaskToPull(createTask(1, MAX_SIZE_TASK_PRIORITY1));
		addTaskToPull(createTask(1, MAX_SIZE_TASK_PRIORITY1));
		addTaskToPull(createTask(1, MAX_SIZE_TASK_PRIORITY1));
	}
	addTaskToPull(createTask(2, MAX_SIZE_TASK_PRIORITY2));

}
void fillDataStructureToTestTOQueue3() {
	for (size_t i = 0; i < 6; i++) {
		Task* t = createTask(3, MAX_SIZE_TASK_PRIORITY3);
		pushTask(t);
		enterTaskValuesInTasksRunMetaData(t);
		increaseNumTasksPush();
	}
	for (size_t i = 0; i < 2; i++) {
		Task* t = createTask(1, MAX_SIZE_TASK_PRIORITY1);
		pushTask(t);
		enterTaskValuesInTasksRunMetaData(t);
		increaseNumTasksPush();
	}
}


void fillPullToTestTOQueue2() {
	fillDataStructureToTestTOQueue2();
	initPull(NUM_TASKS_IN_PULL_TO_TEST_TO_QUEUE3);
	addTaskToPull(createTask(1, MAX_SIZE_TASK_PRIORITY1));
	addTaskToPull(createTask(1, MAX_SIZE_TASK_PRIORITY1));
	for (size_t i = 0; i < 3; i++)
	{
		addTaskToPull(createTask(3, MAX_SIZE_TASK_PRIORITY3));
		addTaskToPull(createTask(1, MAX_SIZE_TASK_PRIORITY1));
		addTaskToPull(createTask(1, MAX_SIZE_TASK_PRIORITY1));
		addTaskToPull(createTask(1, MAX_SIZE_TASK_PRIORITY1));
		addTaskToPull(createTask(1, MAX_SIZE_TASK_PRIORITY1));
	}

}
void fillDataStructureToTestTOQueue2() {
	for (size_t i = 0; i < 6; i++) {
		Task* t = createTask(2, MAX_SIZE_TASK_PRIORITY2);
		pushTask(t);
		enterTaskValuesInTasksRunMetaData(t);
		increaseNumTasksPush();
	}
	for (size_t i = 0; i < 2; i++) {
		Task* t = createTask(1, MAX_SIZE_TASK_PRIORITY1);
		pushTask(t);
		enterTaskValuesInTasksRunMetaData(t);
		increaseNumTasksPush();
	}
}


void printPull() {
	printf("\n-----------------------pull--------------------------------");
	for (size_t i = 0; i < pull->currentNumTasks; i++)
	{
		printTask(pull->tasks[i]);
	}
}