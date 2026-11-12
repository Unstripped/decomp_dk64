#include "common.h"
#include "sched.h"
#include "proto/global/131B0.h"
#include "proto/global/117190.h"
#include "proto/global/201B0.h"
#include "proto/global/2DE90.h"
#include "proto/global/F600.h"

extern s32 __osMotorAccess(OSPfs *, s32);

extern s32 gRumblePaused;
extern u8 gRumbleResetPending;
extern u8 gScreenRenderFlags;
extern u32 gFrameCounter;
extern u8 D_807ECD09;
extern OSMesgQueue D_807ECCF0;
extern PlayerStruct *gPlayerSlots;

// .bss 0x807F02D0-0x807F04C0
OSPfs gRumblePfs[4];
RumbleInfo gRumbleInfo[4];

void rumbleInfoClear(RumbleInfo *info) {
    bzero(info, sizeof(RumbleInfo));
}

void rumbleMotorStart(u8 port) {
    RumbleInfo *info;

    if (__osMotorAccess(&gRumblePfs[port], 1) == 4) {
        info = &gRumbleInfo[port];
        rumbleInfoClear(info);
        info->unk00 = 3;
    } else {
        gRumbleInfo[port].unk04 = 1;
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
    gRumbleInfo[port].unk04 = 0;
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
        if (menuIsTransitionType6() != 0 || menuIsTransitionTypeC() != 0) {
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
    return ((gGlobalPauseFlags & 0x4002) != 0) ||
           ((gScreenRenderFlags & 1) != 0) ||
           (screenWipeGetState() != 0) ||
           (camIsCutsceneActive() != 0) ||
           (menuIsTransitionType6() == 0 && menuIsTransitionTypeC() == 0 && menuIsTransitionTypeD() == 0);
}

void rumbleUpdate(void) {
    RumbleInfo *info;
    s32 i;
    s32 pad;
    u8 activeMask;

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
        activeMask = controllerGetActiveMask();
        for (i = 0; i < 4; i++, info++) {
            if (info->unk00 != 1) {
                if ((D_807ECD09 & (1 << i)) && (activeMask & (1 << i)) && (gFrameCounter % 15 == 0)) {
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
                            u8 intensity = info->unk05;

                            info->unk08 += intensity * 4;
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
