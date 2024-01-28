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

/* Function common to all tasks */
void MyTask(void *p_arg)
{
	char *sTaskName = (char *)p_arg;
#if OS_CRITICAL_METHOD == 3
	OS_CPU_SR cpu_sr = 0;
#endif

	OS_ENTER_CRITICAL();
	printf("Name: %s status: RED\n", sTaskName);
	OS_EXIT_CRITICAL();

	while (1) {

		/*
		 * printf uses mutex to get terminal access, therefore
		 * must enter critical section
		 */

		OS_ENTER_CRITICAL();
		printf("Name: %s\n", sTaskName);
		OS_EXIT_CRITICAL();

		// only one traffic light for now
		if (strcmp(sTaskName, "Task 1") == 0) {
			// TODO: take semaphore
			OSTimeDly(OS_TICKS_PER_SEC * 5); // safety margin

			printf("Name: %s status: RED+YELLOW\n", sTaskName);
			OSTimeDly(OS_TICKS_PER_SEC * 1);
			
			printf("Name: %s status: GREEN\n", sTaskName);
			OSTimeDly(OS_TICKS_PER_SEC * 15);
			
			printf("Name: %s status: GREEN+YELLOW\n", sTaskName);
			OSTimeDly(OS_TICKS_PER_SEC * 1);

			printf("Name: %s status: RED\n", sTaskName);
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

	char sTask1[] = "Task 1";
	char sTask2[] = "Task 2";

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
