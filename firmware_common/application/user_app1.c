/**********************************************************************************************************************
File: user_app1.c                                                                

----------------------------------------------------------------------------------------------------------------------
To start a new task using this user_app1 as a template:
 1. Copy both user_app1.c and user_app1.h to the Application directory
 2. Rename the files yournewtaskname.c and yournewtaskname.h
 3. Add yournewtaskname.c and yournewtaskname.h to the Application Include and Source groups in the IAR project
 4. Use ctrl-h (make sure "Match Case" is checked) to find and replace all instances of "user_app1" with "yournewtaskname"
 5. Use ctrl-h to find and replace all instances of "UserApp1" with "YourNewTaskName"
 6. Use ctrl-h to find and replace all instances of "USER_APP1" with "YOUR_NEW_TASK_NAME"
 7. Add a call to YourNewTaskNameInitialize() in the init section of main
 8. Add a call to YourNewTaskNameRunActiveState() in the Super Loop section of main
 9. Update yournewtaskname.h per the instructions at the top of yournewtaskname.h
10. Delete this text (between the dashed lines) and update the Description below to describe your task
----------------------------------------------------------------------------------------------------------------------

Description:
This is a user_app1.c file template 

------------------------------------------------------------------------------------------------------------------------
API:

Public functions:


Protected System functions:
void UserApp1Initialize(void)
Runs required initialzation for the task.  Should only be called once in main init section.

void UserApp1RunActiveState(void)
Runs current task state.  Should only be called once in main loop.


**********************************************************************************************************************/

#include "configuration.h"

/***********************************************************************************************************************
Global variable definitions with scope across entire project.
All Global variable names shall start with "G_UserApp1"
***********************************************************************************************************************/
/* New variables */
volatile u32 G_u32UserApp1Flags;                       /* Global state flags */


/*--------------------------------------------------------------------------------------------------------------------*/
/* Existing variables (defined in other files -- should all contain the "extern" keyword) */
extern volatile u32 G_u32SystemFlags;                  /* From main.c */
extern volatile u32 G_u32ApplicationFlags;             /* From main.c */

extern volatile u32 G_u32SystemTime1ms;                /* From board-specific source file */
extern volatile u32 G_u32SystemTime1s;                 /* From board-specific source file */


/***********************************************************************************************************************
Global variable definitions with scope limited to this local application.
Variable names shall start with "UserApp1_" and be declared as static.
***********************************************************************************************************************/
static fnCode_type UserApp1_StateMachine;            /* The state machine function pointer */
//static u32 UserApp1_u32Timeout;                      /* Timeout counter used across states */


/**********************************************************************************************************************
Function Definitions
**********************************************************************************************************************/

/*--------------------------------------------------------------------------------------------------------------------*/
/* Public functions                                                                                                   */
/*--------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------*/
/* Protected functions                                                                                                */
/*--------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------
Function: UserApp1Initialize

Description:
Initializes the State Machine and its variables.

Requires:
  -

Promises:
  - 
*/
void UserApp1Initialize(void)
{
  

  LedOff(WHITE);
  LedOff(PURPLE);
  LedOff(BLUE);
  LedOff(CYAN);
  LedOff(GREEN);
  LedOff(YELLOW);
  LedOff(ORANGE);
  LedOff(RED);
  
  
  PWMAudioOff(BUZZER1);
  PWMAudioSetFrequency(BUZZER1, 800);
  

  
  //static u16 u16LedRate=0;

  


 
  /* If good initialization, set state to Idle */
  if( 1 )
  {
    UserApp1_StateMachine = UserApp1SM_Idle;
  }
  else
  {
    /* The task isn't properly initialized, so shut it down and don't run */
    UserApp1_StateMachine = UserApp1SM_Error;
  }

} /* end UserApp1Initialize() */

  
/*----------------------------------------------------------------------------------------------------------------------
Function UserApp1RunActiveState()

Description:
Selects and runs one iteration of the current state in the state machine.
All state machines have a TOTAL of 1ms to execute, so on average n state machines
may take 1ms / n to execute.

Requires:
  - State machine function pointer points at current state

Promises:
  - Calls the function to pointed by the state machine function pointer
*/
void UserApp1RunActiveState(void)
{
  UserApp1_StateMachine();

} /* end UserApp1RunActiveState */


/*--------------------------------------------------------------------------------------------------------------------*/
/* Private functions                                                                                                  */
/*--------------------------------------------------------------------------------------------------------------------*/


/**********************************************************************************************************************
State Machine Function Definitions
**********************************************************************************************************************/

/*-------------------------------------------------------------------------------------------------------------------*/
/* Wait for ??? */
static void UserApp1SM_Idle(void)
{
	//you have a correct password already
	static u8 au8RealPassword[]={1,2,3,1,2,3};
	static u8 au8UserPassword[]={0,0,0,0,0,0};
	static u8 u8Index=0;
	static u8 u8Confirm=0;
	static u16 u16Counter1=0;
	static u16 u16Counter2=0;
	static bool bPressed1=FALSE;
	static bool bPressed2=FALSE;
	static bool bPressed3=FALSE;
	static bool bIsOk=TRUE;
	u8 u8TempIndex;
	
	//you wanna to change your password
	static u8 u8ChangeCounter=0;
	static u8 u8i=0;
	static u8 au8ChangePassword[]={0,0,0,0,0,0};
	static u8 au8DebugNum[1];
	
	if(u8ChangeCounter==1);
	{
		DebugScanf(au8DebugNum);
		
		if(u8i<=6)
		{
			switch(au8DebugNum[0])
			{
				case 1:
					{
						au8ChangePassword[u8i]=au8DebugNum[0];
						break;
					}
				
				case 2:
					{
						au8ChangePassword[u8i]=au8DebugNum[0];
						break;
					}
				case 3:
					{
						au8ChangePassword[u8i]=au8DebugNum[0];
						break;
					}
				default:
					{
						break;
					}	
			}
			u8i++;
			
			if(u8i==6)
			{
				u8i=0;
			}
		}
	}

	//button confirmed
	if(WasButtonPressed(BUTTON3))
	{
		ButtonAcknowledge(BUTTON0);
		ButtonAcknowledge(BUTTON1);
		ButtonAcknowledge(BUTTON2);
		ButtonAcknowledge(BUTTON3);		
		u8Confirm++;
		bPressed2=TRUE;
		PWMAudioOn(BUZZER1);
		
		if(u8Confirm==1)
		{
			LedOn(BLUE);
			LedOff(WHITE);
			LedOff(PURPLE);
		}
		
		if(u8Confirm==2)
		{
			LedOff(BLUE);
			bPressed3=TRUE;
		}
	}
	
	//confirming
	if(bPressed2)
	{
		u16Counter1++;
		
		if(u16Counter1==60)
		{
			PWMAudioOff(BUZZER1);
		}
		
		if(u16Counter1==120)
		{
			PWMAudioOn(BUZZER1);
		}
		
		if(u16Counter1==180)
		{
			PWMAudioOff(BUZZER1);
			u16Counter1=0;
			bPressed2=FALSE;
		}
	}
	
	//entering
	if(bPressed3)
	{
		if(u8ChangeCounter==0)
		{
			for(u8TempIndex=0;u8TempIndex<6;u8TempIndex++)
			{
				if(au8RealPassword[u8TempIndex]!=
				   au8UserPassword[u8TempIndex])
				{
					bIsOk=FALSE;
					break;
				}
			}
			
			if(bIsOk)//password is correct
			{
				LedOn(WHITE);
				LedOff(PURPLE);
			}
			else//password is incorrect
			{
				LedOff(WHITE);
				LedOn(PURPLE);
			}
			
			u8TempIndex=0;
			
			//reset the user password
			for(u8TempIndex=0;u8TempIndex<6;u8TempIndex++)
			{
				au8UserPassword[u8TempIndex]=0;
			}
			
			u8Confirm=0;
			u8Index=0;
			u8TempIndex=0;
			bIsOk=TRUE;
			bPressed3=FALSE;
		}
		
		if(WasButtonPressed(BUTTON0))
		{
			ButtonAcknowledge(BUTTON0);
			LedOn(YELLOW);
			u8ChangeCounter=1;
		}
		
		if(WasButtonPressed(BUTTON1))
		{
			ButtonAcknowledge(BUTTON1);
			LedOff(YELLOW);
			u8ChangeCounter=0;
			bPressed3=FALSE;
		}
	}
	
	if(u8Confirm==1)
	{	
		if(u8Index<=6)
		{
			if(u8Index<6)
			{
				if(WasButtonPressed(BUTTON0))//press button0
				{
					ButtonAcknowledge(BUTTON0);
					LedOn(RED);
					PWMAudioOn(BUZZER1);
					bPressed1=TRUE;
					au8UserPassword[u8Index]=1;
					u8Index++;
				}
			
				if(WasButtonPressed(BUTTON1))//press button1
				{
					ButtonAcknowledge(BUTTON1);
					LedOn(RED);
					PWMAudioOn(BUZZER1);
					bPressed1=TRUE;
					au8UserPassword[u8Index]=2;
					u8Index++;
				}
			
				if(WasButtonPressed(BUTTON2))//press button2
				{
					ButtonAcknowledge(BUTTON2);
					LedOn(RED);
					PWMAudioOn(BUZZER1);
					bPressed1=TRUE;
					au8UserPassword[u8Index]=3;
					u8Index++;
				}
			}
			
			if(bPressed1==TRUE)
			{
				u16Counter1++;
				
				if(u16Counter1==100)
				{
					u16Counter1=0;
					LedOff(RED);
					PWMAudioOff(BUZZER1);
					bPressed1=FALSE;
				}
			}			
		}
	}
	
}
 /* end UserApp1SM_Idle() */
    

/*-------------------------------------------------------------------------------------------------------------------*/
/* Handle an error */
static void UserApp1SM_Error(void)          
{
  
} /* end UserApp1SM_Error() */



/*--------------------------------------------------------------------------------------------------------------------*/
/* End of File                                                                                                        */
/*--------------------------------------------------------------------------------------------------------------------*/
