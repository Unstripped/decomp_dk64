#include "PRinternal/macros.h"
#include "PR/os_internal.h"
#include "PR/R4300.h"
#include "PR/rcp.h"
#include "PRinternal/viint.h"

// TODO: this comes from a header
#ident "$Revision: 1.17 $"

__OSViContext vi[2] ALIGNED(0x8) = { 0 };
__OSViContext* __osViCurr = &vi[0];
__OSViContext* __osViNext = &vi[1];

#pragma GLOBAL_ASM("asm/nonmatchings/libultra/io/vi/__osViInit.s")
