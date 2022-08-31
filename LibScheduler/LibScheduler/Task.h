#pragma once

#include "Definitions.h"
#include "TaskPriority.h"

struct Task {
	int id;
	int priority;
	double size;
};

typedef struct Task Task;

/// <summary>
/// Dynamic allocate of a task
/// </summary>
/// <returns>Pointer to task</returns>
Task* dynamicAllocationTask();

/// <summary>
/// Freeing dynamically allocated memory
/// </summary>
/// <param name="task">- Pointer to task</param>
void freeTask(Task* task);


/// <summary>
/// Create task with values
/// </summary>
/// <param name="priority"></param>
/// <param name="size"></param>
/// <returns>Pointer to task</returns>
Task* createTask(int priority, double size);

/// <summary>
/// Create task with random values
/// </summary>
/// <returns>Pointer to task</returns>
Task* createRandomTask();


/// <summary>
/// Print all values of task
/// </summary>
/// <param name="task">- Pointer to task</param>
void printTask(const Task* task);


/// <summary>
/// Calculate the run time of a task
/// </summary>
/// <param name="task"></param>
/// <returns>time</returns>
double calculateRunTimeOfTask(const Task* task);

/// <summary>
/// Calculation of how much of a task has been completed over a period of time
/// </summary>
/// <param name="task">Pointer to task</param>
/// <param name="time">Time to execute</param>
/// <returns>part of task that execute</returns>
double calculationPartTaskExecuteInPeriodTime(const Task* task, double time);


int getId(const Task* task);

int getPriority(const Task* task);

double getSize(const Task* task);

Task* copyTask(Task* task);


void decreaseSizeTask(Task* task, double decreaseSize);

double getPortionOfTaskCompletedOnTime(Task* task, double time);