#include "PRinternal/macros.h"
#include "PR/os_internal.h"
#include "PRinternal/controller.h"
#include "PRinternal/siint.h"

OSPifRam __osPfsPifRam;

#pragma GLOBAL_ASM("asm/nonmatchings/libultra/io/pfsisplug/osPfsIsPlug.s")

#pragma GLOBAL_ASM("asm/nonmatchings/libultra/io/pfsisplug/__osPfsRequestData.s")

#pragma GLOBAL_ASM("asm/nonmatchings/libultra/io/pfsisplug/__osPfsGetInitData.s")
