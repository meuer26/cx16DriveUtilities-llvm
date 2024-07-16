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
void menuReadDriveStatus();

void myExit() {}

void menuReadDriveStatus()
{
    int anyKey;
    unsigned char driveStatus;
    unsigned char logicalFile = 10;
    unsigned char device;
        
    printf("\n\n\n        Enter device to read: ");
    scanf("%d", &device);

    driveStatus = readDriveStatus(logicalFile,device,COMMAND_CHANNEL);
    
    if (driveStatus == (unsigned char)0)
    {
        printf("\n        Device: %d", device);
        printf("\n        Status: %d - ", driveStatus);
        printCommandChannel(logicalFile,device,COMMAND_CHANNEL);
    }
    else if (driveStatus == (unsigned char)128)
    {
        printf("\n\n        Device: %d        ", device);
        printf("\n        Status: %d (Device Not Present)        ", driveStatus);
    }
    else if (driveStatus == (unsigned char)64)
    {
        printf("\n\n        Device: %d        ", device);
        printf("\n        Status: %d (End of File)        ", driveStatus);
    }
    else if (driveStatus == (unsigned char)32)
    {
        printf("\n\n        Device: %d        ", device);
        printf("\n        Status: %d (Cassette Checksum Error)        ", driveStatus);
    }
    else if (driveStatus == (unsigned char)16)
    {
        printf("\n\n        Device: %d        ", device);
        printf("\n        Status: %d (Verify Error)        ", driveStatus);
    }
    else if (driveStatus == (unsigned char)8)
    {
        printf("\n\n        Device: %d        ", device);
        printf("\n        Status: %d (Data Block Too Long)        ", driveStatus);
    }
    else if (driveStatus == (unsigned char)4)
    {
        printf("\n\n        Device: %d        ", device);
        printf("\n        Status: %d (Data Block Too Short)        ", driveStatus);
    }
    else if (driveStatus == (unsigned char)2)
    {
        printf("\n\n        Device: %d        ", device);
        printf("\n        Status: %d (Time Out on Listener)        ", driveStatus);
    }
    else if (driveStatus == (unsigned char)1)
    {
        printf("\n\n        Device: %d        ", device);
        printf("\n        Status: %d (Time Out on Talker)        ", driveStatus);
    }
    else
    {
        printf("\n\n        Device: %d        ", device);
        printf("\n        Status: %d (UNKNOWN ERROR!)        ", driveStatus);
    }

    cbm_k_close(logicalFile);
        
    printf("\n\n        Press 1 <enter> to continue or 0 <enter> to exit: ");
    scanf("%u", &anyKey);
    
    menuShow();

}

void menuEnumerateDrives()
{
    unsigned char device, driveStatus;
    int anyKey;
    unsigned char logicalFile = 10;

    device = (unsigned char)8;

    printf("\n        Enumerating Drive Statuses (8 - 15)\n");
    printf("        ___________________________________\n\n\n");

    while (device <= (unsigned char)15)
    {                
        sendDriveCommand(logicalFile, device, COMMAND_CHANNEL, (char*)"UJ");
        driveStatus = readDriveStatus(logicalFile,device,COMMAND_CHANNEL);

        if (driveStatus == (unsigned char)0)
        {
            printf("\n\n        Device: %d        ", device);
            printf("\n        Status: %d - ", driveStatus);
            printCommandChannel(logicalFile,device,COMMAND_CHANNEL);
        }
        else if (driveStatus == (unsigned char)128)
        {
            printf("\n\n        Device: %d        ", device);
            printf("\n        Status: %d (Device Not Present)        ", driveStatus);
        }
        else if (driveStatus == (unsigned char)64)
        {
            printf("\n\n        Device: %d        ", device);
            printf("\n        Status: %d (End of File)        ", driveStatus);
        }
        else if (driveStatus == (unsigned char)32)
        {
            printf("\n\n        Device: %d        ", device);
            printf("\n        Status: %d (Cassette Checksum Error)        ", driveStatus);
        }
        else if (driveStatus == (unsigned char)16)
        {
            printf("\n\n        Device: %d        ", device);
            printf("\n        Status: %d (Verify Error)        ", driveStatus);
        }
        else if (driveStatus == (unsigned char)8)
        {
            printf("\n\n        Device: %d        ", device);
            printf("\n        Status: %d (Data Block Too Long)        ", driveStatus);
        }
        else if (driveStatus == (unsigned char)4)
        {
            printf("\n\n        Device: %d        ", device);
            printf("\n        Status: %d (Data Block Too Short)        ", driveStatus);
        }
        else if (driveStatus == (unsigned char)2)
        {
            printf("\n\n        Device: %d        ", device);
            printf("\n        Status: %d (Time Out on Listener)        ", driveStatus);
        }
        else if (driveStatus == (unsigned char)1)
        {
            printf("\n\n        Device: %d        ", device);
            printf("\n        Status: %d (Time Out on Talker)        ", driveStatus);
        }
        else
        {
            printf("\n\n        Device: %d        ", device);
            printf("\n        Status: %d (UNKNOWN ERROR!)        ", driveStatus);
        }

        cbm_k_close(logicalFile);
        device++;
        logicalFile++;
    }

    printf("\n        ___________________________________\n");
    printf("\n\n        Press 0 <enter> to exit: ");
    scanf("%d", &anyKey);

    menuShow();
}

void menuInitializeDrive()
{
    int anykey;
    unsigned char device;
    unsigned char logicalFile = 10;
       
    printf("\n\n\n        Enter drive to initialize : ");
    scanf("%d", &device);
    
    sendDriveCommand(logicalFile, device, COMMAND_CHANNEL, (char*)"i");
    cbm_k_close(logicalFile);

    printf("\n\n        Press 0 <enter> to exit: ");
    scanf("%d", &anykey);

    menuShow();
}

void menuResetDrive()
{
    unsigned char device, anykey;
    unsigned char logicalFile = 10;
       
    printf("\n\n\n        Enter drive to reset : ");
    scanf("%d", &device);
    
    sendDriveCommand(logicalFile, device, COMMAND_CHANNEL, (char*)"uj");
    printf("\n        ");
    printCommandChannel(logicalFile,device,COMMAND_CHANNEL);

    cbm_k_close(logicalFile);

    printf("\n\n        Press 0 <enter> to exit: ");
    scanf("%d", &anykey);

    menuShow();
}

void menuResetAllDrives()
{
    unsigned char device, anyKey;
    unsigned char logicalFile = 10;

    device = 8;

    printf("\n        Resetting All Drives (8 - 15)\n");

    while (device <= 15)
    {        
        sendDriveCommand(logicalFile, device, COMMAND_CHANNEL, (char*)"uj");
        cbm_k_close(logicalFile);

        device++;
        logicalFile++;
    }
    
    printf("\n        Complete...");
    printf("\n\n        Press 0 <enter> to exit: ");
    scanf("%d", &anyKey);

    menuShow();
}

void menuReadCMDGetPartition()
{
    unsigned char device, anykey;
    unsigned char logicalFile = 10;
       
    printf("\n\n\n        Enter drive number : ");
    scanf("%d", &device);
    
    sendDriveCommand(logicalFile, device, COMMAND_CHANNEL, (char*)"g-p");
    printf("\n        ");
    printCommandChannel(logicalFile,device,COMMAND_CHANNEL);

    cbm_k_close(logicalFile);

    printf("\n\n        Press 0 <enter> to exit: ");
    scanf("%d", &anykey);

    menuShow();
}

void menuChangeCMDPartition()
{
    unsigned char device, anykey, partition;
    unsigned char logicalFile = 10;
    char * commandIssued = malloc(4);
    char * tmpStorage = malloc(4);
    //char * partition = malloc(1);

    printf("\n\n\n        Enter drive number : ");
    scanf("%d", &device);
    
    printf("\n\n        Enter partition number : ");
    scanf("%d", partition);

    sprintf(tmpStorage, "%d", partition);

    commandIssued = strcat((char*)"cp", (char *)tmpStorage);

    sendDriveCommand(logicalFile, device, COMMAND_CHANNEL, (char*)commandIssued);
    printf("\n        ");
    printCommandChannel(logicalFile,device,COMMAND_CHANNEL);
    cbm_k_close(logicalFile);

    free(commandIssued);
    free(tmpStorage);
    //free(partition);

    printf("\n\n        Press 0 <enter> to exit: ");
    scanf("%d", &anykey);

    menuShow();
}

void menuDirectDiskCommand()
{
    unsigned char device, anykey;
    char * commandIssued;
    unsigned char logicalFile = 10;
    
    printf("\n\n\n        Enter drive number : ");
    scanf("%d", &device);
    
    printf("\n\n        Enter disk command : ");
    scanf("%d", commandIssued);

    sendDriveCommand(logicalFile, device, COMMAND_CHANNEL, commandIssued);
    cbm_k_close(logicalFile);

    printf("\n\n        Press 0 <enter> to exit: ");
    scanf("%d", &anykey);

    menuShow();
}

void menuCMDPartitionDirectory()
{
    unsigned char device, anykey;
    unsigned char logicalFile = 10;

    printf("\n\n\n        Enter drive number : ");
    scanf("%d", &device);
    
    loadCommand(logicalFile,device,COMMAND_CHANNEL, "$=p");

    printf("\n        ");
    printCommandChannel(logicalFile,device,COMMAND_CHANNEL);
    cbm_k_close(logicalFile);

    printf("\n\n        Press 0 <enter> to exit: ");
    scanf("%d", &anykey);

    menuShow();

}

void menuShow()
{
    int choice = 0;

    clearScreen();
    
    printf("\n\n\n        **** COMMANDER X16 DRIVE UTILITIES v0.1 ****");
    printf("\n                    dan@binarywonder.com");
    printf("\n\n\n        1.  Read Drive Status");
    printf("\n        2.  Enumerate Drives (8 - 15)");
    printf("\n        3.  Initialize Drive");
    printf("\n        4.  Reset Individual Drive");
    printf("\n        5.  Get Current CMD Partition");
    printf("\n        6.  Reset All Drives (8 - 15)");
    printf("\n        7.  Change CMD Partition");
    printf("\n        8.  Issue Direct Disk Command (Experimental)");
    printf("\n        9.  Get CMD Partition Directory (Experimental)");
    printf("\n        10. Exit to Basic");
    printf("\n\n\n        Choice: ");
    scanf("%d", &choice);

    if (choice == 1) { menuReadDriveStatus(); }
    else if (choice == 2) { menuEnumerateDrives(); }
    else if (choice == 3) { menuInitializeDrive(); }
    else if (choice == 4) { menuResetDrive(); }
    else if (choice == 5) { menuReadCMDGetPartition(); }
    else if (choice == 6) { menuResetAllDrives(); }
    else if (choice == 7) { menuChangeCMDPartition(); }
    else if (choice == 8) { menuDirectDiskCommand(); }
    else if (choice == 9) { menuCMDPartitionDirectory(); }
    else if (choice == 10) { myExit(); }
    else { menuShow(); }
}
