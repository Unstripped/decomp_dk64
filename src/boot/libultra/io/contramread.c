#include "PRinternal/macros.h"
#include "PR/os_internal.h"
#include "PR/rcp.h"
#include "PRinternal/controller.h"
#include "PRinternal/siint.h"

#define READFORMAT(ptr) ((__OSContRamReadFormat*)(ptr))

s32 __osPfsLastChannel = -1;

#pragma GLOBAL_ASM("asm/nonmatchings/libultra/io/contramread/__osContRamRead.s")
