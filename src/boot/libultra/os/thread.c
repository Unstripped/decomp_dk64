#include "PR/os_internal.h"
#include "PRinternal/osint.h"

// ultralib thread.c's data only: DK64 links __osDequeueThread from exceptasm.s.
struct __osThreadTail __osThreadTail = { NULL, -1 };
OSThread* __osRunQueue = (OSThread*)&__osThreadTail;
OSThread* __osActiveQueue = (OSThread*)&__osThreadTail;
OSThread* __osRunningThread = NULL;
OSThread* __osFaultedThread = NULL;
