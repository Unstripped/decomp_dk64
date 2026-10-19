#include "PR/os_internal.h"
#include "PR/rcp.h"

u32 osPiGetStatus(void) {
    return IO_READ(PI_STATUS_REG);
}
