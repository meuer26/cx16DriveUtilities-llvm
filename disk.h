// Modified from https://github.com/llvm-mos/llvm-mos-sdk/blob/main/examples/cx16/k_cbm_file_test.c

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <cbm.h> 
#include <cx16.h>


uint8_t cbm_get_status(uint8_t lfn, uint8_t device, uint8_t channel);
uint8_t cbm_device_cmd(uint8_t lfn, uint8_t device, uint8_t channel, const char *cmd);