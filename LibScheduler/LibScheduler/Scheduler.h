#pragma once

#include <time.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "Task.h"
#include "Queue.h"
#include "Definitions.h"

/// <summary>
/// Data about the task on the processor
///		taskInCPU - A task that runs on the CPU.
///		startTimeOfTaskInCPU - Time when the task started in the CPU.
///		lastUpdateTime - to update size of task
///		timeToRunInCPU - Quntum of the task to be run on the CPU
/// </summary>
struct TaskInCpuMetaData
{
	Task* taskInCPU;
	clock_t startTimeOfTaskInCPU;
	clock_t lastUpdateTime;
	double timeToRunInCPU;
};

typedef struct TaskInCpuMetaData TaskInCpuMetaData;


/// <summary>
/// Saves the timing state between queues:
///   currentQueue - The queue number from which to schedule.
///   startTimeInCurrentQueue - Start time for this queue.
/// </summary>
struct SchedulerMetaData {
	int currentQueue;
	clock_t startTimeInCurrentQueue;
	TaskInCpuMetaData* taskInCPUMetaData;
};

typedef struct SchedulerMetaData SchedulerMetaData;


/// <summary>
/// Saving all task to scheduler:
///    queues - An array of queues, a queue for each priority
///    numTasks - Number of task that exist in all queues together
///    mtaData - Managing the scheduler between queues as explained above
/// </summary>
struct SchedulerDataStructure
{
	Queue** queues;
	int numTasks;
	struct SchedulerMetaData* metaData;
};

typedef struct SchedulerDataStructure SchedulerDataStructure;

//мозеч!!!!!!
Task* getTaskInCPU();
int getNumTasks();


/// <summary>
/// Dynamic initialization and allocation for the DataStructure
/// </summary>
/// <returns>Pointer to SchedulerDataStructure</returns>
void initDataStructure();


/// <summary>
/// Freeing dynamically allocated memory of SchedulerDataStructure
/// </summary>
void freeDataStructure();


/// <summary>
/// find next task to run in CPU
/// </summary>
/// <returns>Time the task is in the CPU</returns>
void nextTask();


/// <summary>
/// Print all task in DataStructure
/// </summary>
void printDataStructure();


/// <summary>
/// Insert new task to DataStructure
/// </summary>
/// <param name="task">Pointer to task</param>
void pushTask(const Task* task);


/// <summary>
/// Checking whether the task has time left to run on the processor
/// </summary>
/// <returns>true or false remain or not reain</returns>
bool isLeftTimeToRunTaskInCpu();

/// <summary>
/// is scheduler queues full
/// </summary>
/// <returns>true if full false if not full</returns>
bool isSchedulerQueuesFull();

/// <summary>
/// Change the size of the task running on the processor 
/// according to the time that has passed since the last update
/// </summary>
void changeSizeOfTaskInCPU();


/// <summary>
/// Removing the task from the cpu and saving or deleting the task
///  if the task is finished - delete, otherwise - save back to the scheduler queues.
/// </summary>
void saveOrDelteTaskInCPU();