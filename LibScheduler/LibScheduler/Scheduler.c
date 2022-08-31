#include "pch.h"
#include "Scheduler.h"


#pragma region Defination

void initMetaData();
void initTaskInCpuMetaData();

void freeMetaData();
void freeTaskMetaData();

Queue** getQueues();
Queue* getQueueByPriority(int priority);
void setQueues(Queue* queues);
int getNumTasks();
void setNumTasks(int numTasks);
SchedulerMetaData* getSchedulerMetaData();
void setSchedulerMetaData(SchedulerMetaData* schedulerMetaData);

int getCurrentQueue();
void setCurrentQueue(int currentQueue);
clock_t getStartTimeInCurrentQueue();
void setStartTimeInCurrentQueue(clock_t startTimeInCurrentQueue);
TaskInCpuMetaData* getTaskInCPUMetaData();
void setTaskInCPUMetaData(TaskInCpuMetaData* taskInCPUMetaData);

Task* getTaskInCPU();
void setTaskInCPU(Task* taskInCPU);
clock_t getStartTimeOfTaskInCPU();
void setStartTimeOfTaskInCPU(clock_t startTimeOfTaskInCPU);
double getTimeToRunInCPU();
void setTimeToRunInCPU(double timeToRunInCPU);
void setTaskInCpuMetaData(Task* taskInCPU, clock_t startTimeOfTaskInCPU, clock_t lastUpdateTime, double timeToRunInCPU);

int getQuantumToQueue(int numQueue);
double quantityRemainingForCurrentQueue();
void nextQueue();
int findQueueNotEmpty();

void decreaseNumTask();
void increaseNumTask();

bool isLeftTimeToRunTaskInCpu();
bool isValidNumQueue(int numQueue);
//bool isLeftTimeToCurrentQueue();

#pragma endregion



static SchedulerDataStructure* DataStructure;


#pragma region InitDataStructure
/* Dynamic initialization and allocation for the DataStructure */
void initDataStructure() {
	DataStructure = calloc(1, sizeof(SchedulerDataStructure));
	assert(DataStructure);
	DataStructure->queues = calloc(NUM_PRIORITIES, sizeof(Queue*));
	assert(DataStructure->queues);
	for (size_t i = 0; i < NUM_PRIORITIES; i++)
		DataStructure->queues[i] = queue_init();
	DataStructure->numTasks = 0;
	initMetaData();
	assert(DataStructure->metaData);
	return DataStructure;
}

/* Dynamic initialization and allocation for SchedulerMetaData */
void initMetaData() {
	assert(DataStructure);
	DataStructure->metaData = calloc(1, sizeof(SchedulerMetaData));
	assert(DataStructure->metaData);
	DataStructure->metaData->currentQueue = 0;
	initTaskInCpuMetaData();
	assert(DataStructure->metaData->taskInCPUMetaData);
	DataStructure->metaData->startTimeInCurrentQueue = NULL;
}

/* Dynamic initialization and allocation for TaskMetaData */
void initTaskInCpuMetaData() {
	assert(DataStructure);
	assert(DataStructure->metaData);
	DataStructure->metaData->taskInCPUMetaData = calloc(1, sizeof(TaskInCpuMetaData*));
	assert(DataStructure->metaData->taskInCPUMetaData);
	DataStructure->metaData->taskInCPUMetaData->startTimeOfTaskInCPU = NULL;
	DataStructure->metaData->taskInCPUMetaData->lastUpdateTime = NULL;
	DataStructure->metaData->taskInCPUMetaData->timeToRunInCPU = 0;
}
#pragma endregion

#pragma region FreeDataStructure
/* Freeing dynamically allocated memory of SchedulerDataStructure */
void freeDataStructure() {
	assert(DataStructure);
	assert(DataStructure->queues);
	for (size_t i = 0; i < NUM_PRIORITIES; i++)
		queue_free(DataStructure->queues[i]);
	freeMetaData();
	free(DataStructure);
}

/* Freeing dynamically allocated memory of SchedulerMetaData */
void freeMetaData() {
	assert(DataStructure);
	assert(DataStructure->metaData);
	free(DataStructure->metaData->startTimeInCurrentQueue);
	freeTaskMetaData();
	free(DataStructure->metaData);
}

/* Freeing dynamically allocated memory of TaskMetaData */
void freeTaskMetaData() {
	assert(DataStructure);
	assert(DataStructure->metaData);
	assert(DataStructure->metaData->taskInCPUMetaData);
	free(DataStructure->metaData->taskInCPUMetaData->startTimeOfTaskInCPU);
	free(DataStructure->metaData->taskInCPUMetaData->lastUpdateTime);
	freeTask(DataStructure->metaData->taskInCPUMetaData->taskInCPU);
	free(DataStructure->metaData);
}

#pragma endregion

#pragma region Getters & Setters of SchedulerDataSructure

/* return queues of DataStructure */
Queue** getQueues() {
	Queue** queues = DataStructure->queues;
	return DataStructure->queues;
}

/* return queue of priority from DataStructure */
Queue* getQueueByPriority(int priority) {
	return getQueues()[priority - 1];
}

/* return num tasks that exist in DataStructure */
int getNumTasks() {
	int numTasks = DataStructure->numTasks;
	return DataStructure->numTasks;
}

/* return scheduler metaData of DataStructure*/
SchedulerMetaData* getSchedulerMetaData() {
	return DataStructure->metaData;
}

void setQueues(Queue* queues) {
	DataStructure->queues = queues;
}

void setNumTasks(int numTasks) {
	DataStructure->numTasks = numTasks;
}

void setSchedulerMetaData(SchedulerMetaData* schedulerMetaData) {
	DataStructure->metaData = schedulerMetaData;
}
#pragma endregion

#pragma region Getters & Setters of SchedulerMetaData
int getCurrentQueue() {
	return getSchedulerMetaData()->currentQueue;
}

clock_t getStartTimeInCurrentQueue() {
	return getSchedulerMetaData()->startTimeInCurrentQueue;
}

TaskInCpuMetaData* getTaskInCPUMetaData() {
	return getSchedulerMetaData()->taskInCPUMetaData;
}

void setCurrentQueue(int currentQueue) {
	getSchedulerMetaData()->currentQueue = currentQueue;
}

void setStartTimeInCurrentQueue(clock_t startTimeInCurrentQueue) {
	getSchedulerMetaData()->startTimeInCurrentQueue = startTimeInCurrentQueue;
}

void setTaskInCPUMetaData(TaskInCpuMetaData* taskInCPUMetaData) {
	getSchedulerMetaData()->taskInCPUMetaData = taskInCPUMetaData;
}
#pragma endregion

#pragma region Getters & Setters of TaskInCpuMetaData
Task* getTaskInCPU() {
	return getTaskInCPUMetaData()->taskInCPU;
}

clock_t getStartTimeOfTaskInCPU() {
	return getTaskInCPUMetaData()->startTimeOfTaskInCPU;
}

clock_t getLastUpdateSize() {
	return getTaskInCPUMetaData()->lastUpdateTime;
}

double getTimeToRunInCPU() {
	double timeToRunInCPU = getTaskInCPUMetaData()->timeToRunInCPU;
	return getTaskInCPUMetaData()->timeToRunInCPU;
}

void setTaskInCPU(Task* taskInCPU) {
	getTaskInCPUMetaData()->taskInCPU = taskInCPU;
}

void setStartTimeOfTaskInCPU(clock_t startTimeOfTaskInCPU) {
	getTaskInCPUMetaData()->startTimeOfTaskInCPU = startTimeOfTaskInCPU;
}

void setLastUpdateSize(clock_t lastUpdateTime) {
	getTaskInCPUMetaData()->lastUpdateTime = lastUpdateTime;
}

void setTimeToRunInCPU(double timeToRunInCPU) {
	getTaskInCPUMetaData()->timeToRunInCPU = timeToRunInCPU;
}

void setTaskInCpuMetaData(Task* taskInCPU, clock_t startTimeOfTaskInCPU, clock_t lastUpdateTime, double timeToRunInCPU) {
	setTaskInCPU(taskInCPU);
	setStartTimeOfTaskInCPU(startTimeOfTaskInCPU);
	setLastUpdateSize(lastUpdateTime);
	setTimeToRunInCPU(timeToRunInCPU);
}
#pragma endregion

#pragma region Queues functions

/* return quantum of queue */
int getQuantumToQueue(int numQueue) {
	assert(isValidNumQueue(numQueue));
	switch (numQueue)
	{
	case 0:
		return QUANTUM_QUEUE1;
	case 1:
		return QUANTUM_QUEUE2;
	case 2:
		return QUANTUM_QUEUE3;
	default:
		exit(-1);
	}
}

/* Finding a queue that is not empty by going through all the queues until finding a queue with tasks.
   If all the queues are empty - 1- is returned. */
int findQueueNotEmpty() {
	int i = 1;
	while (i <= NUM_PRIORITIES && isQueueEmpty(getQueueByPriority(getCurrentQueue() + 1)))
	{
		nextQueue();
		i++;
	}
	int currentQueue = getCurrentQueue();
	if (isQueueEmpty(getQueueByPriority(currentQueue + 1)))
		return -1;
	return currentQueue;
}

/* set current queue to be next queue */
void nextQueue() {
	printf("\n*************current queue %d use to run task during %f", getCurrentQueue(), (((double)clock() - (double)getStartTimeInCurrentQueue()) / CLOCKS_PER_SEC));
	////Kמחוק!!!!!!!!!
	//printDataStructure();
	setCurrentQueue((getCurrentQueue() + 1) % 3);
	setStartTimeInCurrentQueue(clock());
}

/* Quantity remaining for the current queue */
double quantityRemainingForCurrentQueue() {
	int currentQueue = getCurrentQueue();
	double maxTimeInQueue = getQuantumToQueue(currentQueue);
	double timeInCurrentQueueu = (clock() - getStartTimeInCurrentQueue()) / CLOCKS_PER_SEC;
	return maxTimeInQueue - timeInCurrentQueueu;
}

#pragma endregion

#pragma region Task In CPU
/* check if the task have time left to run on the cpu */
bool isLeftTimeToRunTaskInCpu() {
	if (getTaskInCPU() == NULL) {
		printf("task in cpu == NULL");
		return;
	}
	clock_t start = getStartTimeOfTaskInCPU();
	double timeToRun = getTimeToRunInCPU();
	clock_t cl = clock();
	double overTime = ((double)clock() - (double)start) / CLOCKS_PER_SEC;
	double leftTime = timeToRun - overTime;
	printf("\nTo task in CPU with id %d left time to run %f when time to run in cpu is %f, over time = %f",
		getId(getTaskInCPU()), leftTime, timeToRun, overTime);
	return overTime < timeToRun;
}
#pragma endregion

#pragma region Scheduer
void increaseNumTask() {
	DataStructure->numTasks++;
}

void decreaseNumTask() {
	DataStructure->numTasks--;
}

/* Print all task in scheduer */
void printDataStructure() {
	assert(DataStructure);
	printf("\n********SchedulerDataStructure********\n");
	for (size_t i = 0; i < NUM_PRIORITIES; i++) {
		printf("\nQueue %d: \n", (int)i);
		print_queue(DataStructure->queues[i], printTask);
	}
}

#pragma endregion

#pragma region Validation
bool isValidQuantumTask(double time) {
	return  QUANTUM_TASK >= time;
}

bool isValidNumQueue(int numQueue) {
	return 0 <= numQueue && NUM_PRIORITIES > numQueue;
}

bool isValidSizeTask(Task* task) {
	return  MAX_SIZE_OF_TASK > getSize(task) * getTimeToByte(getPriority(task));
}

bool isRemainingTimeToCurrentQueue() {
	return quantityRemainingForCurrentQueue() > 0;
}

bool isEmptyScheduler() {
	return  0 >= getNumTasks();
}

bool isSchedulerQueuesFull() {
	printf("\nisSchedulerFull: numTasks = %d", getNumTasks());
	return MAX_TASKS <= getNumTasks();
}
#pragma endregion


/* Scheduling a new task to run on the processor */
void nextTask() {
	assert(DataStructure);
	/* Checking that the task in the processor ran the time allocated to it */
	if (!getTaskInCPU() || !isLeftTimeToRunTaskInCpu()) {//switch

		/* Finding a queue in which tasks exist.
		   If there are tasks in the current queue,
		   the current queue will be returned */
		int currentQueue = findQueueNotEmpty();

		/* Checking whether there is a queue that has tasks */
		if (-1 != currentQueue) {//define ERROR_NOT_TASK

			/* Finding the time to remove tasks from the current queue */
			double remaimigTimeToQueue = quantityRemainingForCurrentQueue();

			/* Checking whether there is no time left - you need to move to the next queue */
			if (0 >= remaimigTimeToQueue) {
				nextQueue();
				currentQueue = findQueueNotEmpty();
				remaimigTimeToQueue = quantityRemainingForCurrentQueue();
			}
			printf("\n--next-task-- use queue: %d:", currentQueue);

			/* Removing a task from the queue and updating the TaskInCpuMetaData*/
			Task* task = queue_dequeue(getQueueByPriority(currentQueue + 1));
			//decreaseNumTask();
			double timeToRunTask = calculateRunTimeOfTask(task);//remainingTimeToRun
			double timeToRunInCpu = MIN(remaimigTimeToQueue, timeToRunTask);
			timeToRunInCpu = MIN(QUANTUM_TASK, timeToRunInCpu);
			setTaskInCpuMetaData(task, clock(), clock(), timeToRunInCpu);
			printf("schedule task to cpu:");
			printTask(task);
		}
		else {
			printf("\nnextTask: All queues is empty, num tasks in data structure is %d", getNumTasks());
			setTaskInCPU(NULL);
		}
	}
	else
	{
		printf("\nnextTask: A task exists in the cpu");
	}
}

/* Adding a new task to the schedule */
void pushTask(const Task* task) {
	assert(DataStructure);
	assert(task);

	if (isSchedulerQueuesFull()) {
		printf("\n\tScheduler is full");
		return;
	}

	if (!isValidSizeTask(task)) {
		printf("\n\tSize of task not valid");
		printTask(task);
		return;
	}

	Queue* queue = getQueueByPriority(getPriority(task));
	assert(queue);
	queue_enqueue(queue, task);
	printf("\nPush task: ");
	printTask(task);
	increaseNumTask();
}

void changeSizeOfTaskInCPU() {
	if (!getTaskInCPU()) {
		printf("task in cpu == null");
		return;
	}
	printf("\nchangeSizeOfTaskInCPU:taskId: %d, sizeTask=%f, ", getId(getTaskInCPU()), getSize(getTaskInCPU()));
	clock_t start = getLastUpdateSize();//getStartInCPU()
	//rename taskTimePassed
	double timeTaskRun = ((double)clock() - (double)start) / CLOCKS_PER_SEC;
	setLastUpdateSize(clock());//מיותר
	double prtitionComplete = getPortionOfTaskCompletedOnTime(getTaskInCPU(), timeTaskRun);//rename dataSizeComplete
	printf("taskRunInCPU=%f, ", timeTaskRun);
	printf("=>PartitionCompleted=%f", prtitionComplete);
	decreaseSizeTask(getTaskInCPU(), prtitionComplete);
	printTask(getTaskInCPU());
}

void saveOrDelteTaskInCPU() {
	//int currentTaskI 
	if (!getTaskInCPU()) {
		printf("\ntask in cpu == NULL");
		return;
	}

	double sizeTask = getSize(getTaskInCPU());
	printf("\nsaveOrDelteTaskInCPU: taskId = %d, sizeTask = %f ", getId(getTaskInCPU()), sizeTask);
	decreaseNumTask();
	if (sizeTask > 0) {
		pushTask(getTaskInCPU());
		printf("- push back task to queues!");//add task id
	}
	else {
		freeTask(getTaskInCPU());
		printf("- delete task!");
	}
}