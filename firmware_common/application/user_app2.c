/**********************************************************************************************************************
File: user_app2.c                                                                

Description:
This is a user_app2.c file template 

------------------------------------------------------------------------------------------------------------------------
API:

Public functions:


Protected System functions:
void UserApp2Initialize(void)
Runs required initialzation for the task.  Should only be called once in main init section.

void UserApp2RunActiveState(void)
Runs current task state.  Should only be called once in main loop.


**********************************************************************************************************************/

#include "configuration.h"

/***********************************************************************************************************************
Global variable definitions with scope across entire project.
All Global variable names shall start with "G_UserApp2"
***********************************************************************************************************************/
/* New variables */
volatile u32 G_u32UserApp2Flags;                       /* Global state flags */


/*--------------------------------------------------------------------------------------------------------------------*/
/* Existing variables (defined in other files -- should all contain the "extern" keyword) */
extern volatile u32 G_u32SystemFlags;                  /* From main.c */
extern volatile u32 G_u32ApplicationFlags;             /* From main.c */

extern volatile u32 G_u32SystemTime1ms;                /* From board-specific source file */
extern volatile u32 G_u32SystemTime1s;                 /* From board-specific source file */


/***********************************************************************************************************************
Global variable definitions with scope limited to this local application.
Variable names shall start with "UserApp2_" and be declared as static.
***********************************************************************************************************************/
static fnCode_type UserApp2_StateMachine;            /* The state machine function pointer */
//static u32 UserApp2_u32Timeout;                      /* Timeout counter used across states */


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
Function: UserApp2Initialize

Description:
Initializes the State Machine and its variables.

Requires:
  -

Promises:
  - 
*/
void UserApp2Initialize(void)
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
	
	
	DebugPrintf("\n\r*******************************************\n\r");
	DebugPrintf("LED Programming Interface\n\r");
	DebugPrintf("Press 1 to program LED command sequence\n\r");
	DebugPrintf("Press 2 to show current USER program");
	DebugPrintf("\n\r*******************************************\n\r");
	
	
  /* If good initialization, set state to Idle */
  if( 1 )
  {
    UserApp2_StateMachine = UserApp2SM_Idle;
  }
  else
  {
    /* The task isn't properly initialized, so shut it down and don't run */
    UserApp2_StateMachine = UserApp2SM_FailedInit;
  }

} /* end UserApp2Initialize() */

  
/*----------------------------------------------------------------------------------------------------------------------
Function UserApp2RunActiveState()

Description:
Selects and runs one iteration of the current state in the state machine.
All state machines have a TOTAL of 1ms to execute, so on average n state machines
may take 1ms / n to execute.

Requires:
  - State machine function pointer points at current state

Promises:
  - Calls the function to pointed by the state machine function pointer
*/
void UserApp2RunActiveState(void)
{
  UserApp2_StateMachine();

} /* end UserApp2RunActiveState */


/*--------------------------------------------------------------------------------------------------------------------*/
/* Private functions                                                                                                  */
/*--------------------------------------------------------------------------------------------------------------------*/


/**********************************************************************************************************************
State Machine Function Definitions
**********************************************************************************************************************/

/*-------------------------------------------------------------------------------------------------------------------*/
/* Wait for ??? */
static void UserApp2SM_Idle(void)
{
    
	//Debug state
	static u8 au8DebugPress[1];
	static u8 u8CurrentOrUser=0;
	static u8 au8UserEnter[12];
	u8* pu8UserEnter=au8UserEnter;
	static u8 u8OnTime=0;
	static u8 u8OffTime=0;
	static u8 u8OnTimeCourt=0;
	static bool bCorrect=TRUE;
	
	//Time counter 
	static u16 u16TimeCounter=0;
	static u16 u16TimeTemp=0;
	static u8 au8ThousandTime[]="0000";
	static u8 u8TimeLimit=0;
	static u8 u8Court=0;
	
	//Arrey enter
	u8 au8Store[]={'r','o','y','g','c','b','p','w','R','O','Y','G','C','B','P','W'};
	static u8 u8ArreyLimit=0;
	
	//Set up your command
	sLedLimit asLimitLevel[]=
	{
		{RED,1000,TRUE,LED_PWM_20,LINE1_START_ADDR+19},
		{GREEN,3000,TRUE,LED_PWM_20,LINE1_START_ADDR+11},
		{RED,6000,FALSE,LED_PWM_0,LINE1_START_ADDR+19},
		{GREEN,9000,FALSE,LED_PWM_0,LINE1_START_ADDR+11}
	};
	
	//set up your user command
	sUserLedLimit asUserLimitLevel[]=
	{
		eUserLED,u16UserCounter,bUserOn,eLightRate,u8UserAddr
	};
	
	//Tera interface
	DebugScanf(au8DebugPress)0;
	
	if(au8DebugPress[0]=='1')
	{
		//enter your command
		DebugScanf(au8DebugPress[0]);
		for(u8ArreyLimit=0;u8ArreyLimit<12;u8ArreyLimit++)
		{
			au8UserEnter[u8ArreyLimit]=
			
			if(au8UserEnter[u8ArreyLimit]=='\0')
			{
				break;
			}
		}
		
		u8ArreyLimit=0;
		DebugPress[0]=0;
		
		//cheak your command
		for(u8ArreyLimit=0;u8ArreyLimit<sizeof(au8Store);u8ArreyLimit++)
		{
			if(*pu8UserEnter!=au8Store[u8ArreyLimit])
			{
				bCorrect=FALSE;
				break;
			}
			else
			{
				eUserLED=*pu8UserEnter;
				pu8UserEnter++;
				
				if(*pu8UserEnter!='-')
				{
					bCorrect=FALSE;
					break;
				}
				else
				{
					pu8UserEnter++;
					
					if(*pu8UserEnter<'0'||*pu8UserEnter>'9')
					{
						bCorrect=FALSE;
						break;
					}
					else
					{
						while(*pu8UserEnter>='0'&&*pu8UserEnter<='9')
						{
							u8OnTime+=(*pu8UserEnter+0);
							pu8UserEnter++;
						}
						
						if(pu8UserEnter!='-')
						{
							bCorrect=FALSE;
							break;
						}
						else
						{
							pu8UserEnter++;
							
							if(*pu8UserEnter<'0'&&*pu8UserEnter>'9')
							{
								bCorrect=FALSE;
								break;
							}
							else
							{
								while(*pu8UserEnter>='0'&&*pu8UserEnter<='9')
								{
									u8OffTime+=(*pu8UserEnter+0);
									pu8UserEnter++;
								}
								
								if(*pu8UserEnter!='\r')
								{
									bCorrect=FALSE;
									break;
								}
								else
								{
									bCorrect=TRUE;
								}
							}
						}
					}
				}
			}
		}
		
		
	
	}
	
	
	if(au8DebugPress[0]=='2')
	{		
		if(WasButtonPressed(BUTTON0))
		{
			ButtonAcknowledge(BUTTON0);
			
			DebugPrintf("\n\r\n\rCurrent USER program:\n\r\n\r");
			DebugPrintf("LED   ON TIME   OFF TIME\n\r");
			DebugPrintf("------------------------\n\r");
			DebugPrintf(" R    1000      6000\n\r");
			DebugPrintf(" G    3000      9000\n\r");
			DebugPrintf("------------------------\n\r");
			
			u8CurrentOrUser=1;
		}

		
		if(u8CurrentOrUser==1)
		{
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
			for(u8TimeLimit=0;u8TimeLimit<sizeof(asLimitLevel);u8TimeLimit++)
			{
				if(u16TimeCounter==asLimitLevel[u8TimeLimit].u16Counter)
				{
					LedPWM(asLimitLevel[u8TimeLimit].eLED,asLimitLevel[u8TimeLimit].eLightRate);
					
					if(asLimitLevel[u8TimeLimit].bOn)
					{
						LCDMessage(asLimitLevel[u8TimeLimit].u8Addr,"1");
					}
					else
					{
						LCDMessage(asLimitLevel[u8TimeLimit].u8Addr,"0");
					}
				}
			}
			
			//10s for a circulation
			if(u16TimeCounter==10000)
			{
				u16TimeCounter=0;
				u8TimeLimit=0;
			}
			
			
		}
	}
	
} /* end UserApp2SM_Idle() */
     

/*-------------------------------------------------------------------------------------------------------------------*/
/* Handle an error */
static void UserApp2SM_Error(void)          
{
	
	
} /* end UserApp2SM_Error() */



/*-------------------------------------------------------------------------------------------------------------------*/
/* State to sit in if init failed */
static void UserApp2SM_FailedInit(void)          
{
    
} /* end UserApp2SM_FailedInit() */


/*--------------------------------------------------------------------------------------------------------------------*/
/* End of File                                                                                                        */
/*--------------------------------------------------------------------------------------------------------------------*/
