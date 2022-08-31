#include "TestDataStructure.h"

TestDataStructure* testDataStructure;


/* initialization and allocted of TestDataStructure */
void initTestDataStructure() {
	testDataStructure = calloc(1, sizeof(TestDataStructure*));
	assert(testDataStructure);
	testDataStructure->numTasksPush = 0;
	initTaskRunMetaData();
}

/* initialization and allocted of TaskRunMetaData */
void initTaskRunMetaData() {
	assert(testDataStructure);
	testDataStructure->tasksRunMetaData = calloc(MAX_PUSH_TASK, sizeof(TaskRunMetaData**));
	assert(testDataStructure->tasksRunMetaData);
	for (size_t i = 0; i < MAX_PUSH_TASK; i++) {
		testDataStructure->tasksRunMetaData[i] = calloc(1, sizeof(TaskRunMetaData*));
		assert(testDataStructure->tasksRunMetaData[i]);
		testDataStructure->tasksRunMetaData[i]->numTimesInCpu = 0;
		testDataStructure->tasksRunMetaData[i]->totalRunningTimeInCpu = 0;
		testDataStructure->tasksRunMetaData[i]->orginalTask = dynamicAllocationTask();
		testDataStructure->tasksRunMetaData[i]->updateTask = dynamicAllocationTask();
	}
}

/* Entering the task details into the task information array - tasksRunMetaData */
void enterTaskValuesInTasksRunMetaData(Task* t) {
	int id = getId(t);
	TaskRunMetaData* currentTaskRunMetaData = testDataStructure->tasksRunMetaData[id];
	assert(currentTaskRunMetaData);
	currentTaskRunMetaData->beginTimeInQueues = clock();
	currentTaskRunMetaData->orginalTask = copyTask(t);
	currentTaskRunMetaData->updateTask = copyTask(t);
}

/* Update of the task details in the task information array - tasksRunMetaData */
void updateTaskDataInTasksRunMetaData(Task* t) {
	int id = getId(getTaskInCPU());
	TaskRunMetaData* currentTaskRunMetaData = testDataStructure->tasksRunMetaData[id];
	assert(currentTaskRunMetaData);
	currentTaskRunMetaData->numTimesInCpu++;
	currentTaskRunMetaData->totalRunningTimeInCpu += reastartTimerAndGetTime();
	currentTaskRunMetaData->endTimeInQueues = clock();
	currentTaskRunMetaData->updateTask = copyTask(t);
}

/* Adding a random task to the system */
void addRandomTask() {
	Task* t = createRandomTask();
	pushTask(t);
	enterTaskValuesInTasksRunMetaData(t);
	increaseNumTasksPush();
}

/* increase num tasks in the system */
void increaseNumTasksPush() {
	testDataStructure->numTasksPush++;
}


/* get number of tasks pushed to the queue by the test */
int getNumTasksPush() {
	return testDataStructure->numTasksPush;
}

/* Lottery between 0 and 1 to check whether to push values or not */
bool isPushTask() {
	return  rand() % 2 + 1;
}

/* Going through all the tasks in the system and checking their timeout that does not pass */
void testTasksTO() {
	for (size_t i = 0; getNumTasksPush() > i && MAX_PUSH_TASK > i; i++)
	{
		double start = testDataStructure->tasksRunMetaData[i]->beginTimeInQueues;
		double end = testDataStructure->tasksRunMetaData[i]->endTimeInQueues;
		double timeOut = getTimeOut(getPriority(testDataStructure->tasksRunMetaData[i]->orginalTask));
		double currentTimeOut = (end - start) / CLOCKS_PER_SEC;
		double timeToRunTask = calculateRunTimeOfTask(testDataStructure->tasksRunMetaData[i]->updateTask);
		assert(currentTimeOut + timeToRunTask <= timeOut);
	}
}

#pragma region Timer
clock_t start;

void stratTimer() {
	start = clock();
}

clock_t getStartTimer() {
	return start;
}

clock_t reastartTimerAndGetTime() {
	clock_t time = clock() - getStartTimer();
	stratTimer();
	return time / CLOCKS_PER_SEC;
}
#pragma endregion


void tst_random() {

	init();

	/* Adding a random task to the system */
	addRandomTask();

	/* Scheduling a new task to run on the processor */
	nextTask();

	/* start timer to keep time start of task in cpu */
	stratTimer();


	/* A loop that works as long as:
		-there is a task in the processor
		-there are tasks in the system
		-the number of tasks pushed is less than the number of tasks scheduled for pushing */
	while (getTaskInCPU() || getNumTasks() > 0 || getNumTasksPush() < MAX_PUSH_TASK) {

		/* Checking whether there is time left for the task to run on the processor -
		   if so, pushing the task based on random values for the task and random on pushing the task */
		if (isLeftTimeToRunTaskInCpu()) {
			if (MAX_PUSH_TASK > getNumTasksPush() && !isSchedulerQueuesFull()) {
				if (isPushTask()) {
					addRandomTask();
				}
			}
		}

		/* Saving and updating the task on the cpu and scheduling a new task to run on the cpu */
		else {
			changeSizeOfTaskInCPU();
			updateTaskDataInTasksRunMetaData(getTaskInCPU());
			saveOrDelteTaskInCPU();
			nextTask();
		}
		/* Check all tasks in system and check that timeOut valids  */
		testTasksTO();
		printf("\n-------------------------------------------------------\n");
	}
}

void printTest() {
	for (size_t i = 0; i < MAX_PUSH_TASK; i++)
	{
		TaskRunMetaData* currentTaskRunMetaData = testDataStructure->tasksRunMetaData[i];
		assert(currentTaskRunMetaData);
		printTask(currentTaskRunMetaData->orginalTask);
		printTask(currentTaskRunMetaData->updateTask);
		printf("task run in cpu: %f\n\n\n", currentTaskRunMetaData->totalRunningTimeInCpu);
	}
}


void checkResultTest() {
	printf("\n---------------checkResultTest:---------------");
	if (getNumTasks() != 0) {
		printf("\nError, exist task in dataStructure of scheduler!!!");
	}
	for (size_t i = 0; i < MAX_PUSH_TASK; i++)
	{
		assert(testDataStructure->tasksRunMetaData[i]);
		Task* orginalTask = testDataStructure->tasksRunMetaData[i]->orginalTask;
		Task* updateTask = testDataStructure->tasksRunMetaData[i]->updateTask;
		if (updateTask->size > 0) {
			printf("\nError, exist task not finish!!!");
		}

		double timeOut = getTimeOut(getPriority(testDataStructure->tasksRunMetaData[i]->orginalTask));
		double currentTimeOut = ((double)testDataStructure->tasksRunMetaData[i]->endTimeInQueues - (double)testDataStructure->tasksRunMetaData[i]->beginTimeInQueues) / CLOCKS_PER_SEC;
		if (timeOut < currentTimeOut) {
			printf("\nError, timeOut over!");
		}
	}
}

//assert(testDataStructure->tasksRunMetaData[i]);
//printTask(testDataStructure->tasksRunMetaData[i]->orginalTask);
//printTask(testDataStructure->tasksRunMetaData[i]->updateTask);
//printf("\nTask %d was in cpu %d times during %f", (int)i, testDataStructure->tasksRunMetaData[i]->numTimesInCpu, testDataStructure->tasksRunMetaData[i]->totalRunningTimeInCpu);
//printf("check time out:");
//printf(", beginTimeInQueues=%d", (int)testDataStructure->tasksRunMetaData[i]->beginTimeInQueues);
//printf(", endTimeInQueues=%d", (int)testDataStructure->tasksRunMetaData[i]->endTimeInQueues);
//printf(", timeOut-of-task=%d", getTimeOut(getPriority(testDataStructure->tasksRunMetaData[i]->orginalTask)));
//printf(", current-timeOut=%f\n\n", ((double)testDataStructure->tasksRunMetaData[i]->endTimeInQueues - (double)testDataStructure->tasksRunMetaData[i]->beginTimeInQueues) / CLOCKS_PER_SEC);