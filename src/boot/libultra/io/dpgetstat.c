#include "PR/os_internal.h"
#include "PR/rcp.h"

u32 osDpGetStatus(void) {
    return IO_READ(DPC_STATUS_REG);
}
