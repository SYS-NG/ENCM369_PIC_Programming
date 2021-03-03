/*!*********************************************************************************************************************
@file user_app.c                                                                
@brief User's tasks / applications are written here.  This description
should be replaced by something specific to the task.

------------------------------------------------------------------------------------------------------------------------
GLOBALS
- NONE

CONSTANTS
- NONE

TYPES
- NONE

PUBLIC FUNCTIONS
- NONE

PROTECTED FUNCTIONS
- void UserApp1Initialize(void)
- void UserApp1Run(void)


**********************************************************************************************************************/

#include "configuration.h"

/***********************************************************************************************************************
Global variable definitions with scope across entire project.
All Global variable names shall start with "G_<type>UserApp1"
***********************************************************************************************************************/
/* New variables */
volatile u8 G_u8UserAppFlags;                             /*!< @brief Global state flags */


/*--------------------------------------------------------------------------------------------------------------------*/
/* Existing variables (defined in other files -- should all contain the "extern" keyword) */
extern volatile u32 G_u32SystemTime1ms;                   /*!< @brief From main.c */
extern volatile u32 G_u32SystemTime1s;                    /*!< @brief From main.c */
extern volatile u32 G_u32SystemFlags;                     /*!< @brief From main.c */


/***********************************************************************************************************************
Global variable definitions with scope limited to this local application.
Variable names shall start with "UserApp_<type>" and be declared as static.
***********************************************************************************************************************/


/**********************************************************************************************************************
Function Definitions
**********************************************************************************************************************/

/*--------------------------------------------------------------------------------------------------------------------*/
/*! @publicsection */                                                                                            
/*--------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------*/
/*! @protectedsection */                                                                                            
/*--------------------------------------------------------------------------------------------------------------------*/

/*!--------------------------------------------------------------------------------------------------------------------
@fn void UserAppInitialize(void)

@brief
Initializes the application's variables.

Should only be called once in main init section.

Requires:
- NONE

Promises:
- NONE

*/
void UserAppInitialize(void)
{
    /*Timer0 control register initialization*
     * Timer on, asynchronous, 16 bit*
     *Fosc/4, 1:16 pre-scaler, 1:1 post-scaler*/
    T0CON0 = 0x90;
    T0CON1 = 0x54;
} /* end UserAppInitialize() */

  
/*!----------------------------------------------------------------------------------------------------------------------
@fn void UserAppRun(void)

@brief Application code that runs once per system loop

Requires:
- 

Promises:
- 

*/
void UserAppRun(void)
{
    /*Read LATA to temporary variable*/
    u8 u8output = LATA;
    /*Increment variable*/
    u8output++;  
    /*Write variable into LATA*/
    LATA = u8output|0x80;
    return;
} /* end UserAppRun */

/*!----------------------------------------------------------------------------------------------------------------------
@fn void TimeXus(u16 u16TimeXus)

@brief Sets Timer0 to count u16Microseconds

Requires:
- Timer0 configured so each tick takes 1 microsecond.
- u16TimeXus is the number of microseconds from 1 to 65535 to be counted.

Promises:
- Pre-loads TMR0H:L to clock out desired period.
- TMR0IF cleared.
- Timer0 enabled.
*/
void TimeXus(u16 u16counter)
{
    /*Disable Timer During Config*/
    T0CON0 &= 0x7F;
    /*set intialCount to "starting value"
     such that u16TimeXus count is required to reach 0xFFFF*/
    u16 u16initialCount = 0xFFFF - u16counter;
    /*Preload TMR0H and TMR0L*/
    TMR0L = u16initialCount & 0x00FF;
    TMR0H = u16initialCount >> 8;
    /*Clear TMR0IF and enable Timer 0*/
    PIR3 &= 0x7F;
    T0CON0 |= 0x80;
} /*End TimeXus()*/

/*------------------------------------------------------------------------------------------------------------------*/
/*! @privatesection */                                                                                            
/*--------------------------------------------------------------------------------------------------------------------*/





/*--------------------------------------------------------------------------------------------------------------------*/
/* End of File                                                                                                        */
/*--------------------------------------------------------------------------------------------------------------------*/
