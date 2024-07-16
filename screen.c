#include "constants.h"

void clearScreen()
{
    asm ("      lda #$93");
    asm ("      jmp CHROUT");

}
