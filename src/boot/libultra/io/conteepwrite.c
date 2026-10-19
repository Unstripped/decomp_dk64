#include "PRinternal/macros.h"
#include "PR/os_internal.h"
#include "PR/rcp.h"
#include "PRinternal/controller.h"
#include "PRinternal/siint.h"

void __osPackEepWriteData(u8 address, u8* buffer);
s32 __osEepStatus(OSMesgQueue* mq, OSContStatus* data);

#pragma GLOBAL_ASM("asm/nonmatchings/libultra/io/conteepwrite/osEepromWrite.s")

#pragma GLOBAL_ASM("asm/nonmatchings/libultra/io/conteepwrite/__osPackEepWriteData.s")

#pragma GLOBAL_ASM("asm/nonmatchings/libultra/io/conteepwrite/__osEepStatus.s")
