/*
*******************************************************************************
*                                               sample.c
*
* Description:	This sample program uses the ucos linux port to start 5 simple
* tasks.
*
* Author: Philip Mitchell
*
*******************************************************************************
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <ucos_ii.h>

#include "app_cfg.h"

#if OS_STK_GROWTH == 1u
#define STK_HEAD(size) (size - 1u)
#else
#define STK_HEAD(size) (0)
#endif

void hardware_init()
{
}

void writeToLog(const char* filename, int num) {
	FILE* file = fopen(filename, "a");
	if (file == NULL) {
		printf("Error opening file: %s\n", filename);
		return;
	}
	fprintf(file, "\n%d", num);
	fclose(file); // ensures data is flushed to file
}


/* Function common to all tasks */
void MyTask(void *p_arg)
{
	char *sTaskName = (char *)p_arg;
#if OS_CRITICAL_METHOD == 3
	OS_CPU_SR cpu_sr = 0;
#endif

    char filename[256];
    strcpy(filename, sTaskName);
    strcat(filename, ".log");

    FILE *f = fopen(filename, "w");
    if (f == NULL) {
        printf("Error opening file!\n");
    }
    fclose(f); 

	OS_ENTER_CRITICAL();
	printf("Name: %s status: RED\n", sTaskName);
	OS_EXIT_CRITICAL();
	writeToLog(filename, 4);

	while (1) {

		/*
		 * printf uses mutex to get terminal access, therefore
		 * must enter critical section
		 */

		OS_ENTER_CRITICAL();
		printf("Name: %s\n", sTaskName);
		OS_EXIT_CRITICAL();

		// only one traffic light for now
		if (strcmp(sTaskName, "Task1") == 0) {
			// TODO: take semaphore
			OSTimeDly(OS_TICKS_PER_SEC * 5); // safety margin

			printf("Name: %s status: RED+YELLOW\n", sTaskName);
			writeToLog(filename, 6);
			OSTimeDly(OS_TICKS_PER_SEC * 1);
			
			printf("Name: %s status: GREEN\n", sTaskName);
			writeToLog(filename, 1);
			OSTimeDly(OS_TICKS_PER_SEC * 15);
			
			printf("Name: %s status: GREEN+YELLOW\n", sTaskName);
			writeToLog(filename, 3);
			OSTimeDly(OS_TICKS_PER_SEC * 1);

			printf("Name: %s status: RED\n", sTaskName);
			writeToLog(filename, 4);
			// TODO: return semaphore

			OSTimeDly(OS_TICKS_PER_SEC * 3); // don't try to take semaphore too fast
		} else
			/* Delay so other tasks may execute. */
			OSTimeDly(OS_TICKS_PER_SEC * 60);
	} 
}

int main(void)
{
#if OS_CRITICAL_METHOD == 3
	OS_CPU_SR cpu_sr = 0;
#endif
	INT8U err;

	/*
	 * pthreads allocates its own memory for task stacks. This UCOS
	 * linux port needs a minimum stack size in order to pass the
	 * function information within the port.
	 */
	INT8U Stk1[APP_TASK_1_STK_SIZE];
	INT8U Stk2[APP_TASK_2_STK_SIZE];

	char sTask1[] = "Task1";
	char sTask2[] = "Task2";

	hardware_init();

	OSInit();

	err =
	    OSTaskCreate(MyTask, sTask1,
			 (void *)&Stk1[STK_HEAD(APP_TASK_1_STK_SIZE)],
			 APP_TASK_1_PRIO);

	if (err != OS_ERR_NONE) {
		printf("OSTaskCreate() failed for %s: Err = %d\n", sTask1,
		       (int)err);
	}

	err =
	    OSTaskCreate(MyTask, sTask2,
			 (void *)&Stk2[STK_HEAD(APP_TASK_2_STK_SIZE)],
			 APP_TASK_2_PRIO);

	if (err != OS_ERR_NONE) {
		printf("OSTaskCreate() failed for %s: Err = %d\n", sTask2,
		       (int)err);
	}

	OS_ENTER_CRITICAL();
	printf("all threads created\n");
	OS_EXIT_CRITICAL();

	OSStart();

	OS_ENTER_CRITICAL();
	printf("returned from OSStart()\n");
	OS_EXIT_CRITICAL();

	return 0;
}
