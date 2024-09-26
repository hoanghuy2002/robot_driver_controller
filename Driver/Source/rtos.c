#include <stdint.h>
#include <stdlib.h>
#include "rtos.h"
#include "rcc_driver.h"
#include "timer_driver.h"

#define Task_RunState 						1
#define Task_BlockState						99
#define Task_BlockWaitEvent					0

#define RTOS_Total_Task 					5

#define IdleTask_Symbol						-99
#define IdleTask_Size						128
#define RTOS_Node_Size						24

#define TaskTimer 							TIM4
#define TaskTimer_EnableCLK()				TIM4_EnableCLK()
#define TaskTimer_EnableCounter()		 	TIM4_EnableCounter()
#define TaskTimer_IRQHandler()			 	TIM4_IRQHandler()
#define TaskTimer_Priority					10
#define TaskTimer_IRQNumber					TIM4_IRQ
#define TaskTimer_Frequency					10000U




/***********************/
void Idle_Task(void);
int8_t Create_IdleTask(void);
void Delete_IdleTask(void);
void Create_IdleTaskStack(void);

void RTOS_Save_PSPValue(uint32_t Current_SP_Value);
volatile uint32_t* RTOS_Get_PSPValue(void);
__attribute__((naked)) void Switch_SP_To_PSP(void);
void RTOS_Update_NextTask(void);



void UnBlock_Task(void);
void PendSV_Handler(void);
void Create_TaskTimer(void);
	
/***********************/
	
static uint8_t RTOS_Number_TaskNode =0;
static uint8_t Task_CurrentNode =0;
volatile static uint16_t RTOS_Tick	=0;
struct RTOS_Node
{
	uint8_t Task_State;
	uint8_t Task_Priority;
	int16_t Task_Symbol;
	uint16_t Task_Tick;
	uint32_t *Task_FirstPSP;
	uint32_t *Task_PSP;
	void (*Task_Handler)(void);
	struct RTOS_Node *NextNode;
};

static struct RTOS_Node *Task_Node[RTOS_Total_Task+1];


int8_t RTOS_Delete_Task(uint16_t Task_Symbol)
{
	for(uint8_t Task_Index=1;Task_Index<=RTOS_Number_TaskNode;Task_Index++)
	{
		if(Task_Node[Task_Index]->Task_Symbol == Task_Symbol)
		{
			if(RTOS_Number_TaskNode > 1)
			{
				Task_Node[Task_Index-1]->NextNode = Task_Node[Task_Index]->NextNode;														
				free(Task_Node[Task_Index]->Task_FirstPSP);					
				free(Task_Node[Task_Index]);																										/*free memory stack of task*/
				for(uint8_t Task_Temp =Task_Index+1;Task_Temp<=RTOS_Number_TaskNode;Task_Temp++)
				{
					Task_Node[Task_Temp-1] = Task_Node[Task_Temp];
				}																																													/*free memory RTOS_Node struct of task*/
				RTOS_Number_TaskNode--;
			}
			else if(RTOS_Number_TaskNode == 1)
			{

				free(Task_Node[RTOS_Number_TaskNode]->Task_FirstPSP);																			/*free memory stack of task*/				
				free(Task_Node[RTOS_Number_TaskNode]);																								/*free memory RTOS_Node struct of task*/
				RTOS_Number_TaskNode--;
				Delete_IdleTask();
			}
			else
			{
				break;
			}
			return RTOS_Success;
			
		}
	}
	return RTOS_Failure;
}

int8_t Create_IdleTask(void)
{
	/*Create region for struct RTOS_Node of Idle_Task*/
	Task_Node[0] = (struct RTOS_Node *)calloc(RTOS_Node_Size,sizeof(uint8_t));			//This struct occupied 20
	/*Check create region is successfull or failure*/
	/*If Failure the fuction will return and abort create task*/
	if(Task_Node[0] == NULL)
	{
		return RTOS_Failure;
	}
	/*Create Node for Idle_Task*/
	Task_Node[0]->Task_PSP = (uint32_t *)calloc(IdleTask_Size,sizeof(uint8_t));
	if(Task_Node[0]->Task_PSP == NULL)
	{
		free(Task_Node[0]);
		return RTOS_Failure;
	}
	Task_Node[0]->Task_FirstPSP = Task_Node[0]->Task_PSP;
	Task_Node[0]->Task_PSP += IdleTask_Size/4;
	Task_Node[0]->Task_Handler = Idle_Task;
	Task_Node[0]->Task_State = Task_RunState;
	Task_Node[0]->Task_Tick = 0;
	Task_Node[0]->Task_Symbol =	IdleTask_Symbol;
	Task_Node[0]->Task_Priority = 255;
	
	return RTOS_Success;
}

void Create_IdleTaskStack(void)
{
	/*Create Register in Stack for Task*/
	uint32_t *pPSP;
	pPSP = (uint32_t *)Task_Node[0]->Task_PSP;
	pPSP--;
	*pPSP = 0x01000000; ///xPSR

	pPSP--;
	*pPSP = (uint32_t)Task_Node[0]->Task_Handler; 				/// PC

	pPSP--;
	*pPSP = 0xFFFFFFFD; ///LR

	for (uint8_t i=0;i<5;i++)				// - 5*4 byte region for R12-R3-R2-R1-R0,each register occupied 4 byte
	{
		pPSP--;
		*pPSP =0;
	}	
	
	Task_Node[0]->Task_PSP = (uint32_t *)pPSP;			//PSP of task point to R0
}


void UnBlock_Task(void)
{
	for(uint8_t i=0;i<RTOS_Number_TaskNode;i++)
	{
		if(Task_Node[i+1]->Task_State == Task_BlockState)
		{
			if(Task_Node[i+1]->Task_Tick == RTOS_Tick)
			{
				Task_Node[i+1]->Task_State = Task_RunState;
			}
		}
	}
}


void RTOS_Save_PSPValue(uint32_t Current_SP_Value)
{
	Task_Node[Task_CurrentNode]->Task_PSP =(uint32_t *) Current_SP_Value;
}


volatile uint32_t* RTOS_Get_PSPValue(void)
{
	return Task_Node[Task_CurrentNode]->Task_PSP;
}

__attribute__((naked)) void Switch_SP_To_PSP(void)
{
	//// Coppy Idle's PSP Value to PSP
	__asm volatile ("PUSH {LR}");
	__asm volatile ("BL RTOS_Get_PSPValue");
	__asm volatile ("POP {LR}");
	__asm volatile ("MSR PSP,R0");

	//// Switch SP
	__asm volatile ("MOV R0,#0x02");
	__asm volatile ("MSR CONTROL,R0");

	/// EXIT
	__asm volatile ("BX LR");

}

void RTOS_Update_NextTask(void)
{
	uint8_t Task_NextNode = 0;
	for(uint8_t i=1;i<=RTOS_Number_TaskNode+1;i++)
	{
		uint8_t Task_CheckNode = (Task_CurrentNode+i)%(RTOS_Number_TaskNode+1);
		if((Task_Node[Task_CheckNode]->Task_State == Task_RunState)&&(Task_Node[Task_CheckNode]->Task_Priority < Task_Node[Task_NextNode]->Task_Priority))
		{
			Task_NextNode = Task_CheckNode;
		}
	}
	Task_CurrentNode = Task_NextNode;
}



void TaskTimer_IRQHandler()
{
	volatile static uint8_t Count_To_Create_IdleTaskStack =0;
	if(Count_To_Create_IdleTaskStack ==0)
	{
		Disable_IRQ();
		Count_To_Create_IdleTaskStack++;
		Create_IdleTaskStack();
		TaskTimer_EnableCounter();					/*Starting Count in Task Timer*/
		Enable_IRQ();
	}
	TIM4->SR &= ~(uint32_t)(1<<0);
	RTOS_Tick++;
	UnBlock_Task();
	System_SetPending_PENSV();
}

void PendSV_Handler(void)
{
	
	//Save R4-R11 to Current Task's Stack
	__asm volatile ("MRS R0,PSP"); /// Get Current Running Task's PSP
	__asm volatile ("STMDB R0!,{R4-R11}"); /// Save R4-R11 to Current Task's Stack and update R0
	__asm volatile ("PUSH {LR}");
	__asm volatile ("BL RTOS_Save_PSPValue");  /// Save Current Task's PSP Value

	/// Update NextTask
	__asm volatile ("BL RTOS_Update_NextTask");


	///Retrieve Next Task's Information
	__asm volatile ("BL RTOS_Get_PSPValue");    /// Get Next Task's Past PSP Value
	__asm volatile ("LDMIA R0!,{R4-R11}");  /// Using that PSP to Retrive R4-R11 to Register

	/// Save The Next Task's PSP value to SP(PSP)
	__asm volatile ("MSR PSP,R0");

	__asm volatile ("POP {LR}");
	/// Exit
	__asm volatile ("BX LR");

}

void Idle_Task(void)
{
	while(1);
}

void Create_TaskTimer(void)
{
	TaskTimer_EnableCLK();
	TIM_ConfigureCounterStruct CustomTimer = New_TIM_ConfigureCounterStruct;
	CustomTimer.Timer = TaskTimer;
	CustomTimer.TIMER_AutoReloadPreload = Enable;
	CustomTimer.TIMER_DirectionMode = TIMER_UpCounterMode;
	CustomTimer.TIMER_Counter =0;
	CustomTimer.TIMER_PreScaler = (uint16_t)(GetTimer_Clock(TaskTimer)/TaskTimer_Frequency);
	CustomTimer.TIMER_AutoReload = (uint16_t)(TaskTimer_Tick*TaskTimer_Frequency);
	TIM_ConfigureCounter(&CustomTimer);
}


int8_t RTOS_Create_Task(void (*Task_Handler)(void),uint16_t Task_Size,uint8_t Task_Priority,int16_t Task_Symbol)
{
	/*Check Have any task_node before has same Task_Symbol with new task_node*/
	for(uint8_t i=0;i<=RTOS_Number_TaskNode;i++)
	{
		if(Task_Node[i]->Task_Symbol == Task_Symbol)
		{
			return RTOS_Failure;
		}
	}
	/*Create Idle Task*/
	RTOS_Number_TaskNode ++;
	if (RTOS_Number_TaskNode ==1)
	{
		if(Create_IdleTask() == RTOS_Failure)
		{
			return RTOS_Failure;
		}
	}
	/*Check Is total task were create node over than Total node permission*/ 
	if(RTOS_Number_TaskNode>RTOS_Total_Task)
	{
		RTOS_Number_TaskNode --;
		return RTOS_OverTask;
	}
	
	/*Create region for struct RTOS_Node of Task*/
	Task_Node[RTOS_Number_TaskNode] = (struct RTOS_Node *)calloc(RTOS_Node_Size,sizeof(uint8_t));	//This struct occupied 20 byte
	/*Check create region is successfull or failure*/
	/*If Failure the fuction will return and abort create task*/
	if(Task_Node[RTOS_Number_TaskNode] == NULL)
	{
		RTOS_Number_TaskNode --;
		return RTOS_Failure;
	}
	
	/*Create region for Stack of Task*/ 
	Task_Node[RTOS_Number_TaskNode]->Task_PSP = (uint32_t *)calloc(Task_Size,sizeof(uint8_t));
	/*Check create region is successfull or failure*/
	/*If Failure the fuction will return and abort create task*/
	if(Task_Node[RTOS_Number_TaskNode]->Task_PSP == NULL)
	{
		free(Task_Node[RTOS_Number_TaskNode]);
		RTOS_Number_TaskNode --;
		return RTOS_Failure;
	}
	if(RTOS_Number_TaskNode ==0)
	{
		Delete_IdleTask();
	}
	Task_Node[RTOS_Number_TaskNode]->Task_FirstPSP = Task_Node[RTOS_Number_TaskNode]->Task_PSP;
	Task_Node[RTOS_Number_TaskNode]->Task_PSP += Task_Size/4;
	/* Configure feature for task*/
	Task_Node[RTOS_Number_TaskNode]->Task_Handler = Task_Handler;										// link to handler function which is define in application
	Task_Node[RTOS_Number_TaskNode]->Task_State = Task_RunState;											// task always in run status when is created
	Task_Node[RTOS_Number_TaskNode]->Task_Tick = 0;																	// this parameter is used for task_delay and will be block status
	Task_Node[RTOS_Number_TaskNode]->Task_Priority = Task_Priority;									// task priority - lower value higher priority
	Task_Node[RTOS_Number_TaskNode]->Task_Symbol = Task_Symbol;
	Task_Node[RTOS_Number_TaskNode-1]->NextNode = Task_Node[RTOS_Number_TaskNode];				// penultimate node link to last node
	Task_Node[RTOS_Number_TaskNode]->NextNode = Task_Node[0];												// last node link to first node (first node always is Idle_Task)		
	
	/*Create Register in Stack for Task*/
	uint32_t *pPSP;
	pPSP = (uint32_t *)Task_Node[RTOS_Number_TaskNode]->Task_PSP;
	pPSP--;
	*pPSP = 0x01000000; ///xPSR

	pPSP--;
	*pPSP = (uint32_t)Task_Node[RTOS_Number_TaskNode]->Task_Handler; 				/// PC

	pPSP--;
	*pPSP = 0xFFFFFFFD; ///LR

	pPSP -=13;					// - 13*4 byte region for 13 normal register (R0-R12), each normal register occupied 4 byte
	
	Task_Node[RTOS_Number_TaskNode]->Task_PSP = (uint32_t *)pPSP;			//PSP of task point to 
	
	return RTOS_Success;
}

void Delete_IdleTask(void)
{
	free(Task_Node[0]->Task_FirstPSP);														/*free memory stack of idle task*/
	free(Task_Node[0]);																			/*free memory RTOS_Node struct of idle task*/
}

void RTOS_Run_Task(void)
{
	if(RTOS_Number_TaskNode >= 1)
	{
		// Run RTOS's kernel
		Disable_IRQ();
		Create_TaskTimer();
		Switch_SP_To_PSP();
		TIM_ConfigureInterrupt(TaskTimer,TIMER_UpdateInterrupt,TaskTimer_Priority,TaskTimer_IRQNumber);
		NVIC_SetPending_IRQ(TaskTimer_IRQNumber);
		Enable_IRQ();
	}
}

void RTOS_Delay_Task(float Time_Delay)
{
	if(Time_Delay == Task_DelayWaitEvent)
	{
		Task_Node[Task_CurrentNode]->Task_State = Task_BlockWaitEvent;
	}
	else
	{
		Task_Node[Task_CurrentNode]->Task_Tick = RTOS_Tick+(uint16_t)Time_Delay;
		Task_Node[Task_CurrentNode]->Task_State = Task_BlockState;
	}
	System_SetPending_PENSV();
}





