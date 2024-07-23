#include <stdio.h>
#include "disk.h"
#include "screen.h"
#include "constants.h"
#include <cx16.h>
#include <cbm.h>
#include <string.h>
#include <stdlib.h>
#include "main.h"


void menuShow();
void myExit();

void myExit() {}


uint8_t cbm_get_status(uint8_t lfn, uint8_t device, uint8_t channel);
uint8_t cbm_device_cmd(uint8_t lfn, uint8_t device, uint8_t channel, const char *cmd);

void show_status(void) 
{
    printf("%s=%c%d \"%s\"%c\n", cbm_error < 20 ? "success" : "failure",
         cbm_error < 20 ? CH_WHITE : CH_LIGHTRED, cbm_error, cbm_status,
         CH_WHITE);
}


void menuEnumerateDrives()
{
    uint8_t device; 
    uint8_t driveStatus;
    int anyKey;
    uint8_t logicalFile = 10;

    device = (unsigned char)8;

    printf("\n        Enumerating Drive Statuses (8 - 15)\n");
    printf("        ___________________________________\n\n\n");

    while (device <= (unsigned char)15)
    {                
        cbm_device_cmd(logicalFile, device, (uint8_t)COMMAND_CHANNEL, (char*)"UJ");

        cbm_get_status(logicalFile, device, (uint8_t)COMMAND_CHANNEL);
        printf("        Initial device 8 status: \"%s\"\n\n", cbm_status);

        cbm_k_close(logicalFile);
        device++;
        logicalFile++;
    }

    printf("\n        ___________________________________\n");
    printf("\n\n        Press 0 <enter> to exit: ");
    scanf("%d", &anyKey);

    menuShow();
}

void menuShow()
{
    int choice = 0;

    clearScreen();
    
    printf("\n\n\n        **** COMMANDER X16 DRIVE UTILITIES v0.1 ****");
    printf("\n                    dan@binarywonder.com");
    printf("\n\n\n        1.  Read Drive Status");
    printf("\n        10. Exit to Basic");
    printf("\n\n\n        Choice: ");
    scanf("%d", &choice);

    if (choice == 1) { menuEnumerateDrives(); }
    else if (choice == 10) { myExit(); }
    else { menuShow(); }
}
