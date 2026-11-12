#ifndef BOOT_H
#define BOOT_H

#include "common.h"

// Boot thread control blocks (bss 0x80011560). The reset and main threads are each
// followed by their 0x1000-byte stack, so the next control block doubles as the
// stack top of the previous thread: &sMainThread for sResetThread, &D_800138C0 for sMainThread.
extern OSThread sResetThread;
extern OSThread sMainThread;
extern OSThread D_800138C0; // noExpPakScreen thread (boot/1630)

#endif
