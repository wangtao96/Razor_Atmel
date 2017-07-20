/***********************************************************************************************************************
File: main.c                                                                

Description:
Container for the EiE firmware.  
***********************************************************************************************************************/

#include "configuration.h"

/***********************************************************************************************************************
Global variable definitions with scope across entire project.
All Global variable names shall start with "G_"
***********************************************************************************************************************/
/* New variables */
volatile u32 G_u32SystemFlags = 0;                     /* Global system flags */
volatile u32 G_u32ApplicationFlags = 0;                /* Global applications flags: set when application is successfully initialized */

  s8 s8ComuNum=0;
  u8 u8ComuNum=0;
  u32 u32ComuNum;
 bool bCN=FALSE;/*****BOOL has been defined already*****/
 
 typedef struct
 {
   u8 u8ServerNumber;
   DrinkType asServingTray[6];
   void* psNextServer;
 }ServerType;


/*--------------------------------------------------------------------------------------------------------------------*/
/* External global variables defined in other files (must indicate which file they are defined in) */
extern volatile u32 G_u32SystemTime1ms;                /* From board-specific source file */
extern volatile u32 G_u32SystemTime1s;                 /* From board-specific source file */


/***********************************************************************************************************************
Global variable definitions with scope limited to this local application.
Variable names shall start with "Main_" and be declared as static.
***********************************************************************************************************************/


/***********************************************************************************************************************
Main Program
Main has two sections:

1. Initialization which is run once on power-up or reset.  All drivers and applications are setup here without timing
contraints but must complete execution regardless of success or failure of starting the application. 

2. Super loop which runs infinitely giving processor time to each application.  The total loop time should not exceed
1ms of execution time counting all application execution.  SystemSleep() will execute to complete the remaining time in
the 1ms period.
***********************************************************************************************************************/

void main(void)
{
  
   u16 u16Viewer;
   u16Viewer=0x5A;
   u16* pu16Pointer;
   u8 u8Viewer;
   u8Viewer =0xA5;
   u8* pu8Pointer;
   
   pu16Pointer=&u16Viewer;
   pu8Pointer=&u8Viewer;
   
   pu16Pointer++;
   pu8Pointer--;
   *pu16Pointer-=2;
   *pu8Pointer+=3;
   *pu16Pointer++;
   *pu16Pointer--;
   *pu16Pointer ++;
	
  
  
  G_u32SystemFlags |= _SYSTEM_INITIALIZING;


  
  /**************************************************/
  /**************************************************/
  /**************************************************/
  /**************************************************/
  /**************************************************/
  
  /*
  u16 u16NumBit=0x1234;
  u16NumBit|=~_Bit6(u16);
  u16NumBit&=_Bit6(u16);
  u16NumBit|=~_Bit13;
  u16NumBit&=_Bit13;
  
  */
  
  u8 u8CurrentServer;
  ServerType sServer1;
  ServerType* psServerParser;

  ServerType sServer2;
  ServerType sSerber3;
  ServerType sServer4;
  
  psServerParser=&sServer1;
  sServer1.u8ServerNumber=6;
  u8CurrentServer=psServerParser->u8ServerNumber;
  


  

  

  /* Low level initialization */
  WatchDogSetup(); /* During development, does not reset processor if timeout */
  GpioSetup();
  ClockSetup();
  InterruptSetup();
  SysTickSetup();

  /* Driver initialization */
  MessagingInitialize();
  UartInitialize();
  DebugInitialize();

  /* Debug messages through DebugPrintf() are available from here */

  ButtonInitialize();
  TimerInitialize();  
  SspInitialize();
  TWIInitialize();
  Adc12Initialize();
  
  LcdInitialize();
  LedInitialize();
  AntInitialize();
  AntApiInitialize();
  SdCardInitialize();

  /* Application initialization */

  UserApp1Initialize();
  UserApp2Initialize();
  UserApp3Initialize();

  
  /* Exit initialization */
  SystemStatusReport();
  G_u32SystemFlags &= ~_SYSTEM_INITIALIZING;
    
  /* Super loop */  
  while(1)
  {
    WATCHDOG_BONE();
    
    /*
    u8 au8Arrey1[]={'H','E','L','L','O','u','f','o'};
    u8 au8Arrey2[]="HELLO1h6";
    u8 au8Arrey3[]={72,69,76,76,79,23,5,112};
    u8 au8Arrey4[]={72,69,76,76,79,68,28,69};

    s8 s8ch[8]={'a',' ','s','t','r','i','n','g'};
    
    */
  
    
    /* Drivers */
    LedUpdate();
    ButtonRunActiveState();
    UartRunActiveState();
    TimerRunActiveState(); 
    SspRunActiveState();
    TWIRunActiveState();
    Adc12RunActiveState();
    MessagingRunActiveState();
    DebugRunActiveState();
    LcdRunActiveState();
    AntRunActiveState();
    AntApiRunActiveState();
    SdCardRunActiveState();

    /* Applications */
    UserApp1RunActiveState();
    UserApp2RunActiveState();
    UserApp3RunActiveState();
    
    /* System sleep*/
    HEARTBEAT_OFF();
    SystemSleep();
    HEARTBEAT_ON();
    
  } /* end while(1) main super loop */
  
} /* end main() */


/*--------------------------------------------------------------------------------------------------------------------*/
/* End of File */
/*--------------------------------------------------------------------------------------------------------------------*/
