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

void rumbleInfoClear(RumbleInfo *);
void rumbleMotorStart(u8);
void rumbleMotorStop(u8);
void rumbleResetAll(s32);
s32 rumbleGetPakState(u8);
void rumbleRequest(u8, u8, s32);
void rumbleInfoCancel(RumbleInfo *);
void rumbleCancel(u8);
void rumbleShutdown(void);
void rumbleInit(void);
int rumbleShouldPause(void);
void rumbleUpdate(void);
void rumbleSetPaused(s32);

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

void rumbleInfoClear(RumbleInfo *arg0) {
    bzero(arg0, 0x14);
}

void rumbleMotorStart(u8 arg0) {
    RumbleInfo *sp18;

    if (__osMotorAccess(&gRumblePfs[arg0], 1) == 4) {
        sp18 = &gRumbleInfo[arg0];
        rumbleInfoClear(sp18);
        sp18->unk00 = 3;
    } else {
        D_807F0474[arg0 * 0x14] = 1;
    }
}

void rumbleMotorInit(u8 arg0) {
    s32 ret = osMotorInit(&D_807ECCF0, &gRumblePfs[arg0], arg0);

    switch (ret) {
    case 0:
        gRumbleInfo[arg0].unk00 = 1;
        break;
    case 1:
        gRumbleInfo[arg0].unk00 = 0;
        break;
    case 11:
        gRumbleInfo[arg0].unk00 = 2;
        break;
    case 4:
        gRumbleInfo[arg0].unk00 = 3;
        break;
    }
}

void rumbleMotorStop(u8 arg0) {
    rumbleMotorInit(arg0);
    __osMotorAccess(&gRumblePfs[arg0], 0);
    __osMotorAccess(&gRumblePfs[arg0], 0);
    __osMotorAccess(&gRumblePfs[arg0], 0);
    D_807F0474[arg0 * 0x14] = 0;
}

void rumbleResetAll(s32 arg0) {
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

s32 rumbleGetPakState(u8 arg0) {
    if (arg0 >= 4) {
        return 0;
    }
    return gRumbleInfo[controllerGetPort(arg0)].unk00;
}

void rumbleRequest(u8 arg0, u8 arg1, s32 arg2) {
    RumbleInfo *info;

    info = &gRumbleInfo[controllerGetPort(arg0)];
    if (gRumblePaused != 1 && info->unk00 == 1 && gPlayerSlots[arg0].unk2EB == 0) {
        if (func_8071432C() != 0 || func_8071441C() != 0) {
            if (info->unk12 != 0) {
                if (info->unk10 >= 0x1F) {
                    return;
                }
                info->unk12 = 0;
                info->unk10 = 0;
            }
            info->unk0C = arg2;
            info->unk05 = arg1;
        }
    }
}

void rumbleInfoCancel(RumbleInfo *arg0) {
    if (arg0->unk00 == 1) {
        arg0->unk05 = 0;
        arg0->unk0C = 0;
    }
}

void rumbleCancel(u8 arg0) {
    rumbleInfoCancel(&gRumbleInfo[controllerGetPort(arg0)]);
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

void rumbleSetPaused(s32 arg0) {
    if (arg0 != gRumblePaused) {
        gRumblePaused = arg0;
        gRumbleResetPending = 1;
    }
}
