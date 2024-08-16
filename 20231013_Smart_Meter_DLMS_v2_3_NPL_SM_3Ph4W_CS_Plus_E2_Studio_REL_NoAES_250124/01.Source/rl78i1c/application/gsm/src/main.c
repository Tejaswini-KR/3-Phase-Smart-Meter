/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>
#include "event_log.h"
#include "gsm_typedef.h"
#include "utils.h"

void GSM_PollingProcess(void);
void test_process();

int main()
{
    bool_t isOk = FALSE;
    set_log_level(LOG_DEBUG);
    // set_log_level(LOG_INFO);
    
    //log_info("GSM - Finite State Machine - Starts");
    
    isOk = TRUE;
    
    do {
        GSM_PollingProcess();
        
        if (isOk) {
            test_process();
            //msleep(250);
        }
    } while ( isOk == TRUE );

    //log_info("GSM - Finite State Machine - Ends");

    return 0;
}

