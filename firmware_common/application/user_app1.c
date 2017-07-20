/**********************************************************************************************************************
File: user_app.c                                                                

----------------------------------------------------------------------------------------------------------------------
To start a new task using this user_app as a template:
 1. Copy both user_app.c and user_app.h to the Application directory
 2. Rename the files yournewtaskname.c and yournewtaskname.h
 3. Add yournewtaskname.c and yournewtaskname.h to the Application Include and Source groups in the IAR project
 4. Use ctrl-h (make sure "Match Case" is checked) to find and replace all instances of "user_app" with "yournewtaskname"
 5. Use ctrl-h to find and replace all instances of "UserApp" with "YourNewTaskName"
 6. Use ctrl-h to find and replace all instances of "USER_APP" with "YOUR_NEW_TASK_NAME"
 7. Add a call to YourNewTaskNameInitialize() in the init section of main
 8. Add a call to YourNewTaskNameRunActiveState() in the Super Loop section of main
 9. Update yournewtaskname.h per the instructions at the top of yournewtaskname.h
10. Delete this text (between the dashed lines) and update the Description below to describe your task
----------------------------------------------------------------------------------------------------------------------

Description:
This is a user_app.c file template 

------------------------------------------------------------------------------------------------------------------------
API:

Public functions:


Protected System functions:
void UserAppInitialize(void)
Runs required initialzation for the task.  Should only be called once in main init section.

void UserAppRunActiveState(void)
Runs current task state.  Should only be called once in main loop.


**********************************************************************************************************************/

#include "configuration.h"

/***********************************************************************************************************************
Global variable definitions with scope across entire project.
All Global variable names shall start with "G_"
***********************************************************************************************************************/
/* New variables */
volatile u32 G_u32UserAppFlags;                       /* Global state flags */


/*--------------------------------------------------------------------------------------------------------------------*/
/* Existing variables (defined in other files -- should all contain the "extern" keyword) */
extern volatile u32 G_u32SystemFlags;                  /* From main.c */
extern volatile u32 G_u32ApplicationFlags;             /* From main.c */

extern volatile u32 G_u32SystemTime1ms;                /* From board-specific source file */
extern volatile u32 G_u32SystemTime1s;                 /* From board-specific source file */


/***********************************************************************************************************************
Global variable definitions with scope limited to this local application.
Variable names shall start with "UserApp_" and be declared as static.
***********************************************************************************************************************/

//static u8 UserApp1_au8MyName[] = "LCD Example";     
static u8 UserApp1_CursorPosition1;
static u8 UserApp1_CursorPosition2;

static fnCode_type UserApp1_StateMachine;            /* The state machine function pointer */
static u32 UserApp1_u32Timeout;                      /* Timeout counter used across states */


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
Function: UserAppInitialize

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
	
	LCDCommand(LCD_CLEAR_CMD);	
	
	LCDMessage(LINE1_START_ADDR,"0");//WHITE
	LCDMessage(LINE1_START_ADDR+2,"0");//PURPLE
	LCDMessage(LINE1_START_ADDR+5,"0");//BLUE
	LCDMessage(LINE1_START_ADDR+8,"0");//CYAN
	LCDMessage(LINE1_START_ADDR+11,"0");//GREEN
	LCDMessage(LINE1_START_ADDR+14,"0");//YELLOW
	LCDMessage(LINE1_START_ADDR+17,"0");//ORANGE
	LCDMessage(LINE1_START_ADDR+19,"0");//RED
	
	
	LCDMessage(LINE2_START_ADDR,"TIME:");
	

	if( 1 )
	{
		UserApp1_StateMachine = UserApp1SM_Idle;
	}
	else
	{
	/* The task isn't properly initialized, so shut it down and don't run */
		UserApp1_StateMachine = UserApp1SM_FailedInit;
	}
	
	
} /* end UserAppInitialize() */


/*----------------------------------------------------------------------------------------------------------------------
Function UserAppRunActiveState()

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
  
  
  

 } /* end UserAppRunActiveState */


/*--------------------------------------------------------------------------------------------------------------------*/
/* Private functions                                                                                                  */
/*--------------------------------------------------------------------------------------------------------------------*/


/**********************************************************************************************************************
State Machine Function Definitions
**********************************************************************************************************************/

/*-------------------------------------------------------------------------------------------------------------------*/
/* Wait for a message to be queued */
static void UserApp1SM_Idle(void)
{
	static u16 u16TimeCounter=0;
	static u16 u16TimeTemp=0;
	static u8 au8ThousandTime[]="0000";
	static u8 u8Limit=0;
	static u8 u8Court=0;
	//Set up your command
	sLedLimit asLimitLevel[]=
	{
		{RED,1000,TRUE,LED_PWM_20,LINE1_START_ADDR+19},
		{GREEN,3000,TRUE,LED_PWM_20,LINE1_START_ADDR+11},
		{RED,6000,FALSE,LED_PWM_0,LINE1_START_ADDR+19},
		{GREEN,9000,FALSE,LED_PWM_0,LINE1_START_ADDR+11}
	};
	

	
	
	//Time counter ms
	if(u16TimeTemp%1000==0)
	{
		//thousand's place
		u8Court=u16TimeCounter/1000;
		au8ThousandTime[0]=u8Court+'0';
		
		//hundred's place
		u8Court=(u16TimeCounter%1000)/100;
		au8ThousandTime[1]=u8Court+'0';
		
		//ten's place
		u8Court=((u16TimeCounter%1000)%100)/10;
		au8ThousandTime[2]=u8Court+'0';
		
		u8Court=((u16TimeCounter%1000)%100)%10;
		au8ThousandTime[3]=u8Court+'0';
		
		//print time on LCD ms
		LCDMessage(LINE2_START_ADDR+5,au8ThousandTime);
		u16TimeTemp=0;
	}
	
	
	u16TimeCounter++;
	u16TimeTemp++;
	
	//LED status
	if(u16TimeCounter==asLimitLevel[u8Limit].u16Counter)
	{
		LedPWM(asLimitLevel[u8Limit].eLED,asLimitLevel[u8Limit].eLightRate);
		
		if(asLimitLevel[u8Limit].bOn)
		{
			LCDMessage(asLimitLevel[u8Limit].u8Addr,"1");
		}
		else
		{
			LCDMessage(asLimitLevel[u8Limit].u8Addr,"0");
		}
		u8Limit++;
	}
	
	//10s for a circulation
	if(u16TimeCounter==10000)
	{
		u16TimeCounter=0;
		u8Limit=0;
	}
	
	
	
} /* end UserAppSM_Idle() */
     

/*-------------------------------------------------------------------------------------------------------------------*/
/* Handle an error */
static void UserApp1SM_Error(void)          
{
  
} /* end UserAppSM_Error() */


/*-------------------------------------------------------------------------------------------------------------------*/
/* State to sit in if init failed */
static void UserApp1SM_FailedInit(void)          
{
    
} /* end UserAppSM_FailedInit() */


/*--------------------------------------------------------------------------------------------------------------------*/
/* End of File                                                                                                        */
/*--------------------------------------------------------------------------------------------------------------------*/

