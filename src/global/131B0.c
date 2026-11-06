// The boot segment's osGetIntMask implementation takes the interrupt mask to set
// (asm/libultra/os/getintmask.s reads $a0), but ultralib's header prototypes it as
// osGetIntMask(void). Preempt that header and declare the 1-argument form the
// game's code calls.
#define _OS_EXCEPTION_H_
#include <PR/ultratypes.h>
typedef u32 OSIntMask;
typedef u32 OSHWIntr;

#include "sched.h"

extern s32 __osMotorAccess(OSPfs *, s32);

extern s32 gRumblePaused;
extern u8 gRumbleResetPending;
extern u8 D_8076A0B1;
extern u32 gFrameCounter;
extern u8 D_807ECD09;
extern OSMesgQueue D_807ECCF0;
extern u8 D_807F0474[];
extern u32 D_807FBB60;
extern PlayerStruct *gPlayerSlots;

void rumbleInfoClear(RumbleInfo *info);
void rumbleMotorStart(u8 port);
void rumbleMotorStop(u8 port);
void rumbleResetAll(s32 unused);
s32 rumbleGetPakState(u8 port);
void rumbleRequest(u8 playerIndex, u8 intensity, s32 duration);
void rumbleInfoCancel(RumbleInfo *info);
void rumbleCancel(u8 playerIndex);
void rumbleShutdown(void);
void rumbleInit(void);
int rumbleShouldPause(void);
void rumbleUpdate(void);
void rumbleSetPaused(s32 paused);

extern s32 controllerGetPort(s32);
extern u8 controllerGetActiveMask(void);
extern u32 screenWipeGetState(void);
extern u32 camIsCutsceneActive(void);
extern s32 func_8071432C(void);
extern s32 func_8071441C(void);
extern s32 func_807143E8(void);

// .bss 0x807F02D0-0x807F04C0
OSPfs gRumblePfs[4];
RumbleInfo gRumbleInfo[4];

void rumbleInfoClear(RumbleInfo *info) {
    bzero(info, 0x14);
}

void rumbleMotorStart(u8 port) {
    RumbleInfo *info;

    if (__osMotorAccess(&gRumblePfs[port], 1) == 4) {
        info = &gRumbleInfo[port];
        rumbleInfoClear(info);
        info->unk00 = 3;
    } else {
        D_807F0474[port * 0x14] = 1;
    }
}

void rumbleMotorInit(u8 port) {
    s32 ret = osMotorInit(&D_807ECCF0, &gRumblePfs[port], port);

    switch (ret) {
    case 0:
        gRumbleInfo[port].unk00 = 1;
        break;
    case 1:
        gRumbleInfo[port].unk00 = 0;
        break;
    case 11:
        gRumbleInfo[port].unk00 = 2;
        break;
    case 4:
        gRumbleInfo[port].unk00 = 3;
        break;
    }
}

void rumbleMotorStop(u8 port) {
    rumbleMotorInit(port);
    __osMotorAccess(&gRumblePfs[port], 0);
    __osMotorAccess(&gRumblePfs[port], 0);
    __osMotorAccess(&gRumblePfs[port], 0);
    D_807F0474[port * 0x14] = 0;
}

void rumbleResetAll(s32 unused) {
    s32 i;
    s32 j;

    for (i = 0; i < 4; i++) {
        rumbleInfoClear(&gRumbleInfo[i]);
        gRumbleInfo[i].unk00 = 0;
        if (D_807ECD09 & (1 << i)) {
            for (j = 0; j < 2; j++) {
                rumbleMotorStop(i);
            }
        }
    }
}

s32 rumbleGetPakState(u8 port) {
    if (port >= 4) {
        return 0;
    }
    return gRumbleInfo[controllerGetPort(port)].unk00;
}

void rumbleRequest(u8 playerIndex, u8 intensity, s32 duration) {
    RumbleInfo *info;

    info = &gRumbleInfo[controllerGetPort(playerIndex)];
    if (gRumblePaused != 1 && info->unk00 == 1 && gPlayerSlots[playerIndex].unk2EB == 0) {
        if (func_8071432C() != 0 || func_8071441C() != 0) {
            if (info->unk12 != 0) {
                if (info->unk10 >= 0x1F) {
                    return;
                }
                info->unk12 = 0;
                info->unk10 = 0;
            }
            info->unk0C = duration;
            info->unk05 = intensity;
        }
    }
}

void rumbleInfoCancel(RumbleInfo *info) {
    if (info->unk00 == 1) {
        info->unk05 = 0;
        info->unk0C = 0;
    }
}

void rumbleCancel(u8 playerIndex) {
    rumbleInfoCancel(&gRumbleInfo[controllerGetPort(playerIndex)]);
}

void rumbleShutdown(void) {
    rumbleResetAll(1);
    rumbleSetPaused(1);
}

void rumbleInit(void) {
    rumbleResetAll(0);
    rumbleSetPaused(1);
}

int rumbleShouldPause(void) {
    return ((D_807FBB60 & 0x4002) != 0) ||
           ((D_8076A0B1 & 1) != 0) ||
           (screenWipeGetState() != 0) ||
           (camIsCutsceneActive() != 0) ||
           (func_8071432C() == 0 && func_8071441C() == 0 && func_807143E8() == 0);
}

void rumbleUpdate(void) {
    RumbleInfo *info;
    s32 i;
    s32 pad_w;
    u8 pad;

    info = gRumbleInfo;
    if (gRumblePaused == 1) {
        if (rumbleShouldPause() == 0) {
            rumbleSetPaused(0);
        }
    } else {
        if (rumbleShouldPause() != 0) {
            rumbleSetPaused(1);
        }
    }

    if (gRumbleResetPending != 0) {
        rumbleResetAll(0);
    }
    gRumbleResetPending = 0;

    if (gRumblePaused != 1) {
        pad = controllerGetActiveMask();
        for (i = 0; i < 4; i++, info++) {
            if (info->unk00 != 1) {
                if ((D_807ECD09 & (1 << i)) && (pad & (1 << i)) && (gFrameCounter % 15 == 0)) {
                    rumbleMotorStop(i);
                }
            } else {
                if (info->unk12 == 0) {
                    info->unk12 = info->unk10 >= 0x33;
                }
                if (info->unk0C == 0 && info->unk05 == 0) {
                    if (info->unk10 != 0) {
                        info->unk10--;
                    }
                }
                if (info->unk05 == 0) {
                    if (info->unk04 != 0) {
                        rumbleMotorStop(i);
                    }
                } else {
                    if (info->unk0C != 0) {
                        info->unk0C--;
                        info->unk10++;
                    }
                    if (info->unk0C == 0 || info->unk12 != 0) {
                        rumbleInfoCancel(info);
                    } else {
                        if (info->unk08 >= 0x100) {
                            if (info->unk04 == 0) {
                                rumbleMotorStart(i);
                            }
                            info->unk08 -= 0x100;
                        } else {
                            u8 val = info->unk05;
                            info->unk08 += val * 4;
                            if (info->unk04 != 0) {
                                rumbleMotorStop(i);
                            }
                        }
                    }
                }
            }
        }
    }
}

void rumbleSetPaused(s32 paused) {
    if (paused != gRumblePaused) {
        gRumblePaused = paused;
        gRumbleResetPending = 1;
    }
}
