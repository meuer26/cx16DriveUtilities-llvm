// Modified from https://github.com/llvm-mos/llvm-mos-sdk/blob/main/examples/cx16/k_cbm_file_test.c

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <cbm.h> 
#include <cx16.h> 
#include "disk.h"

extern char cbm_status[64];
extern uint8_t cbm_error;

// read device status channel, returns cbm_error and sets cbm_status
uint8_t cbm_get_status(uint8_t lfn, uint8_t device, uint8_t channel) 
{
    uint8_t len = 0;

    cbm_k_setlfs(lfn, device, channel);
    cbm_k_setnam("");
    cbm_k_open();
    cbm_k_chkin(lfn);
    
    while (len < sizeof(cbm_status) && !cbm_k_readst()) 
    {
        uint8_t c = cbm_k_chrin();
        if (c == '\r') 
        {
            break;
        }
        
        cbm_status[len++] = c;
    }
  
    cbm_status[len] = 0;
    cbm_k_clrch();
    cbm_k_close(lfn);
    cbm_error = ((cbm_status[0] - '0') * 10) + (cbm_status[1] - '0');
  
    if (cbm_error < 20) // quash trivial errors
    {
        cbm_error = 0;
    }

    return cbm_error;
}

// send device command
uint8_t cbm_device_cmd(uint8_t lfn, uint8_t device, uint8_t channel, const char *cmd) 
{
    cbm_k_setlfs(lfn, device, channel);
    cbm_k_setnam(cmd);
    cbm_k_open();
    cbm_k_close(lfn);
    
    return cbm_get_status(lfn, device, channel);
}