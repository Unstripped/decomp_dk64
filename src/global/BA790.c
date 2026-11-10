#include "common.h"
#include "actor.h"
#include "proto/global/119370.h"
#include "proto/global/11BC10.h"
#include "proto/global/12E800.h"
#include "proto/global/19A00.h"
#include "proto/global/201B0.h"
#include "proto/global/35000.h"
#include "proto/global/5E2F0.h"
#include "proto/global/61AA0.h"
#include "proto/global/69E60.h"
#include "proto/global/70FD0.h"
#include "proto/global/7130.h"
#include "proto/global/80150.h"
#include "proto/global/89250.h"
#include "proto/global/8F4B0.h"
#include "proto/global/AA960.h"
#include "proto/global/BA790.h"

extern Actor *gCurrentActor;
extern Actor *gPrimaryPlayerActor;
extern ActorGlobalState gActorGlobalState;
extern u8 gBossFightPhase;

// View of the current actor (gCurrentActor) with the fields func_806B5A90 and func_806B640C need typed.
typedef struct BA790Actor {
    /* 0x000 */ u8 pad0[0x58];
    /* 0x058 */ s32 unk58;
    /* 0x05C */ u8 pad5C[4];
    /* 0x060 */ u32 unk60;
    /* 0x064 */ u8 pad64[0xA];
    /* 0x06E */ s16 unk6E;
    /* 0x070 */ u8 pad70[0xC];
    /* 0x07C */ f32 unk7C;
    /* 0x080 */ f32 unk80;
    /* 0x084 */ f32 unk84;
    /* 0x088 */ u8 pad88[0x1C];
    /* 0x0A4 */ f32 unkA4;
    /* 0x0A8 */ u8 padA8[0x10];
    /* 0x0B8 */ f32 unkB8;
    /* 0x0BC */ u8 padBC[4];
    /* 0x0C0 */ f32 unkC0;
    /* 0x0C4 */ u8 padC4[0x22];
    /* 0x0E6 */ s16 unkE6;
    /* 0x0E8 */ u8 padE8[6];
    /* 0x0EE */ s16 unkEE;
    /* 0x0F0 */ u8 padF0[0x48];
    /* 0x138 */ s32 unk138;
    /* 0x13C */ u8 pad13C[0x18];
    /* 0x154 */ u8 unk154;
    /* 0x155 */ u8 unk155;
    /* 0x156 */ u8 pad156[0x22];
    /* 0x178 */ s16 *unk178;
} BA790Actor;

#define BA790A ((BA790Actor *)gCurrentActor)

extern u8 D_807FBB85;
extern u8 gGameMode;
extern s32 gFrameCounter;
extern s16 D_80770628[];
extern s16 D_80770710[];
extern s32 gCamActor;
extern BA790Actor *D_807FBD6C;
extern u8 D_80720630;


s32 func_806B5A90(s32 aggroRange, s32 unused) {
    u8 ret;
    s16 diff;
    s32 sel;
    f32 fv;
    s32 x;
    u32 t;
    s16 q;
    s32 r;

    ret = 0;
    if (BA790A->unkEE < BA790A->unkE6) {
        diff = BA790A->unkE6 - BA790A->unkEE;
    } else {
        diff = BA790A->unkEE - BA790A->unkE6;
    }
    if (gBossFightPhase == 9 || D_807FBB85 != 0) {
        if (gCurrentActor->state != 0x37 && gCurrentActor->state != 0x38) {
            switch (gCurrentActor->actorType) {
            case 0xAF:
                if (gGameMode == 1) {
                    if (gCurrentActor->flags & 4) {
                        gCurrentActor->state = 0x38;
                        BA790A->unk155 = 0;
                    } else {
                        behaviourSetFloorAndState40();
                    }
                } else {
                    gCurrentActor->state = 0x37;
                    BA790A->unk155 = 0;
                }
                break;
            case 0xB6:
                sfxSpawnTableNodes(gCurrentActor);
                tagBarrelDespawnEffects();
                behaviourSetFloorAndState40();
                break;
            }
        }
    }
    if (diff >= 0x1F5 && diff < 0xE0C) {
        func_80685210(0.5f, 0x32, (gFrameCounter & 1) + 2);
        BA790A->unkB8 = BA790A->unkB8 / 2;
        if (BA790A->unk6E == -1) {
            sfxPlayActorSound(gCurrentActor, 0x122, 0, 0, 0, 0xFF, 1.0f, 0);
        }
    } else {
        if (BA790A->unk6E != -1 && D_80770710[D_80770628[BA790A->unk6E]] == 0x122) {
            sfxStopSlotSound(gCurrentActor, 0);
        }
    }
    switch (gCurrentActor->state) {
    case 0x33:
        if (gBossFightPhase == 2) {
            BA790A->unkC0 = 150.0f;
            BA790A->unkEE = D_807FBD6C->unkEE;
        }
        if (BA790A->unk155) {
            x = 0;
        } else {
            x = 2;
        }
        actorMoveWithinZone(0x33, gBehaviourTargetActor->x, gBehaviourTargetActor->z, x, 6.0f);
        if (gCurrentActor->actorType == 0xB6) {
            enemyAggroStateUpdate(aggroRange, 0x24E, 0x24D);
        }
        break;
    case 0:
    case 4:
        sfxStopSlotSound(gCurrentActor, 0);
        if (BA790A->unk155 == 0) {
            actorUpdateFloorContactAndTilt(gCurrentActor, 6.0f);
            BA790A->unk155 = 1;
        }
        if (gGameMode != 1) {
            if (gCurrentActor->actorType == 0xB6) {
                x = 0x24D;
            } else {
                x = 0x24C;
            }
            enemyAggroStateUpdate(aggroRange, 0x24E, x);
        }
        if (gCurrentActor->state == 0x33) {
            ret = 1;
            BA790A->unkB8 = gBehaviourExtraState->unkD;
            q = mathAngleBetweenPoints2D(gBehaviourTargetActor->x, gBehaviourTargetActor->z, gCurrentActor->x, gCurrentActor->z);
            BA790A->unkE6 = q;
            BA790A->unkEE = q;
        }
        break;
    case 0x38:
        switch (BA790A->unk155) {
        case 1:
            break;
        case 0:
            actorScriptStart(gCurrentActor, 0x24B);
            BA790A->unk155 = BA790A->unk155 + 1;
            break;
        case 2:
            tagBarrelSpawnActorSmokePuffs(0, 1);
            behaviourSetFloorAndState40();
            break;
        }
        break;
    case 0x37:
        sel = BA790A->unk155;
        if (sel >= 2) {
            if (sel - 0x82 < 0) {
                x = 0;
            } else {
                x = sel - 0x82;
            }
            if (sel * 6 >= 0x23) {
                r = 0x22;
            } else {
                r = (sel * 6) & 0xFF;
            }
            q = r;
            t = (u32)((1.0 - (f64)x * 0.03125) * 230.0) & 0xFF;
            if (t != 0) {
                billboardSubmit(gCurrentActor, 0x3C3, 0x40, 0x40, q, q, 1, 0x96, t, 0, 1.0f);
            } else {
                behaviourSetFloorAndState40();
            }
            sel = BA790A->unk155;
            if (sel >= 0x17) {
                x = 0x16;
            } else {
                x = sel;
            }
            fv = ((22.0 - (f64)x) / 20.0) * 200.0;
            if (fv > 130.0) {
                fv = 200.0f;
            }
            lightAdd(BA790A->unk7C, BA790A->unk80, BA790A->unk84, 0.0f, 0.0f, 0.0f, fv, 0, 0xFF, 0xFF, 0xFF);
            sel = BA790A->unk155;
        }
        if (sel < 4) {
            actorMoveWithinZone(0x33, gBehaviourTargetActor->x, gBehaviourTargetActor->z, 0x20, 6.0f);
            sel = BA790A->unk155;
        }
        switch (sel) {
        case 0:
            actorScriptStart(gCurrentActor, 0x24B);
            BA790A->unk155 = BA790A->unk155 + 1;
            break;
        case 2:
            sfxSpawnTableNodes(gCurrentActor);
            tagBarrelSpawnActorSmokePuffs(1, 1);
            actorSetNodeFlag(gCurrentActor, 3);
            camStartShakeFromPoint(gCamActor, 5, 0x14, BA790A->unk7C, BA790A->unk80, BA790A->unk84, 200.0f, 400.0f);
            BA790A->unk155 = BA790A->unk155 + 1;
            break;
        case 4:
            sfxStopSlotSound(gCurrentActor, 0);
            BA790A->unkEE = BA790A->unkE6;
            sfxPlayActorSound(gCurrentActor, 0x136, 0, 0, 0, 0xFF, 1.0f, 0);
            effectSetDuration(5);
            effectSetDepth(1);
            effectSetColor(0xFF, 0xFF, 0xFF, 1);
            effectSetMode(1);
            effectSetScale(-0.4f, 0.4f);
            effectSetCallback(effectSparkSpawnUpdate);
            effectCreateAtPosition(&D_80720630, 0.3f, BA790A->unk7C, BA790A->unkA4 + 7.0f, BA790A->unk84);
            BA790A->unk60 &= ~4;
            BA790A->unk155 = BA790A->unk155 + 1;
            break;
        case 1:
        case 3:
            break;
        case 5:
            BA790A->unk138 = 0;
            actorClearNodeFlag(gCurrentActor, 3);
        default:
            BA790A->unk155 = BA790A->unk155 + 1;
            break;
        }
        break;
    default:
        behaviourUpdateContactAndState(0x24E);
        break;
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
    return ret;
}


void func_806B63E0(void) {
    behaviourFrameBegin();
    func_806B5A90(0x2710, 0);
}

extern u8 gGameMode;
extern s32 gCurrentMap;


void func_806B640C(void) {
    s16 *p = BA790A->unk178;
    s16 i;
    s32 sel;
    s32 a;

    behaviourFrameBegin();
    if (!(gCurrentActor->flags & 0x10)) {
        actorClearNodeFlag(gCurrentActor, 3);
        *p = -gBehaviourExtraState->unkAWide;
    }
    if (gGameMode == 1) {
        for (i = 0; i < gActorGlobalState.unk254; i++) {
            if (gActorGlobalState.unk258[i] == 3) {
                gCurrentActor->unk144 = 0x24;
                actorScriptStart(gCurrentActor, 0x24F);
            }
        }
        lightUpdateFromActorLighting(&gCurrentActor->tintR, &gCurrentActor->tintG, &gCurrentActor->tintB);
    }
    sel = gCurrentActor->state;
    if (sel != 0x37 && sel != 0x38) {
        if (*p > 0) {
            (*p)--;
            if (*p == 0xA) {
                sfxPlayAtPositionPooled(gCurrentActor->x, gCurrentActor->y, gCurrentActor->z, 0x150, 0xFF, 0x7F, 0x1E, 0x32, 0.3f, 0);
            }
            if (*p == 0) {
                gActorGlobalState.unk200 = 9;
            }
        }
    }
    if (gCurrentMap == 6) {
        a = 0x9C40;
    } else {
        a = 0x2710;
    }
    if (func_806B5A90(a, *p) != 0) {
        *p = -*p;
    }
}
