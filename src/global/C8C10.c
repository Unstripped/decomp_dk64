#include "common.h"
#include "actor.h"

extern Actor *D_807FBB40;
extern Actor *D_807FBB4C;
extern ActorGlobalState D_807FBB70;
extern Struct807FD580 *gActivePlayerState;

typedef struct R1C8aSub174 {
    /* 0x00 */ u8 pad0[0x88];
    /* 0x88 */ Actor *unk88;
} R1C8aSub174;

typedef struct R1C8aActor {
    /* 0x000 */ u8 pad0[0xEC];
    /* 0x0EC */ s16 unkEC;
    /* 0x0EE */ s16 unkEE;
    /* 0x0F0 */ s16 unkF0;
    /* 0x0F2 */ u8 padF2[0x82];
    /* 0x174 */ R1C8aSub174 *unk174;
    /* 0x178 */ s16 *unk178;
    /* 0x17C */ u8 pad17C[4];
    /* 0x180 */ s16 *unk180;
} R1C8aActor;

typedef struct R1C8aS90 {
    /* 0x00 */ u8 pad0[0x1A];
    /* 0x1A */ u16 unk1A;
    /* 0x1C */ u8 pad1C[9];
    /* 0x25 */ u8 unk25;
    /* 0x26 */ u8 pad26[6];
    /* 0x2C */ s16 unk2C;
    /* 0x2E */ s16 unk2E;
} R1C8aS90;

typedef struct R1C8aS98 {
    /* 0x00 */ u8 pad0[0x28];
    /* 0x28 */ s16 unk28;
    /* 0x2A */ s16 unk2A;
} R1C8aS98;

typedef struct R1C8aS9C {
    /* 0x00 */ u8 pad0[0x13];
    /* 0x13 */ u8 unk13;
} R1C8aS9C;

typedef struct R1C8aD580 {
    /* 0x000 */ u8 pad0[0x1F0];
    /* 0x1F0 */ s32 unk1F0;
    /* 0x1F4 */ s32 unk1F4;
} R1C8aD580;

typedef struct R1C8aPlayer {
    /* 0x000 */ u8 pad0[4];
    /* 0x004 */ R1C8aActor *unk4;
    /* 0x008 */ u8 pad8[0x208];
    /* 0x210 */ f32 unk210;
    /* 0x214 */ u8 pad214[4];
    /* 0x218 */ f32 unk218;
    /* 0x21C */ u8 pad21C[0xC];
    /* 0x228 */ f32 unk228;
    /* 0x22C */ u8 pad22C[4];
    /* 0x230 */ f32 unk230;
    /* 0x234 */ u8 pad234[0x8C];
    /* 0x2C0 */ u8 unk2C0;
} R1C8aPlayer;

#define R1C8aA ((R1C8aActor *)D_807FBB40)
#define R1C8aS ((R1C8aS90 *)D_807FDC90)
#define R1C8aV98 ((R1C8aS98 *)D_807FDC98)
#define R1C8aC ((R1C8aS9C *)D_807FDC9C)
#define R1C8aD ((R1C8aD580 *)gActivePlayerState)

extern R1C8aPlayer *gPlayerSlots;
extern s32 gCamActor;
extern s32 gFrameCounter;
extern s32 gCurrentMap;

void lightAdd(f32, f32, f32, f32, f32, f32, f32, s32, s32, s32, s32);
void camSetTarget(s32, void *, s32, s32, s32, s32, s32, s32, s32, s32, f32);
void camSetTargetCutsceneUnscaled(s32, void *, s32, s32, s32, s32, s32, s32, s32, s32, f32);
void camStartPath(void *, s32, s32);
void camSetFollowMode(s32);
void func_806B49B0(u8, s16, s16);
void func_8070D8C0(Actor *, s32, u8);
void playerStateQueueCallback();

void func_806C3F10(u8 arg0, u8 arg1, u8 arg2) {
    s16 *sp3C = R1C8aA->unk178;

    if (!(D_807FBB40->unk60 & 0x10)) {
        D_807FDC98->unk46 |= 0x20;
        if (arg2) {
            camStartPath(D_807FBB40, arg2, 1);
        } else {
            camSetTargetCutsceneUnscaled(gCamActor, D_807FBB40, 4, 0x800, 0x19, 0, 0xA, 0x14, 0xC, 0, 0.1f);
        }
        D_807FDC9C->unk10 = 0x27;
        D_807FBB40->unk154 = 0x27;
        D_807FBB40->unk155[0] = 0;
    }
    {
        s32 d = D_807FDC90->unkC - D_807FDC9C->unk6;

        if (d < 0) {
            *sp3C = 0;
        } else {
            *sp3C = d;
        }
    }
    switch (D_807FBB40->unk154) {
        case 0x27:
            if ((R1C8aS->unk1A & 4) && (R1C8aS->unk25 & 0x7F) == arg0) {
                if (gPlayerSlots->unk2C0 == 0) {
                    func_8070D8C0(D_807FBB40, 0x10, 1);
                    D_807FBB40->unk154 = 0x29;
                    D_807FBB40->unk155[0] = 0;
                    D_807FDC9C->unk10 = 0x29;
                    R1C8aD->unk1F0 |= 0x10000;
                    playerStateQueueCallback(0x54, 0, 0);
                    R1C8aS->unk1A |= 0x8000;
                } else {
                    func_8070D8C0(D_807FBB40, 0x10, 0);
                    D_807FBB40->unk154 = 0x28;
                    D_807FBB40->unk155[0] = 0;
                    D_807FDC9C->unk10 = 0x28;
                    if (!arg2) {
                        camSetTarget(gCamActor, D_807FBB40, 4, 0x800, 0x19, 0, 0xA, 0x14, 0xC, 0x78, 0.1f);
                    }
                }
            }
        case 0x28:
            func_806B49B0(2, 0x23D, 0x23E);
            break;
        case 0x26:
        case 0x29:
            if (R1C8aS->unk1A & 0x8000) {
                if ((R1C8aS->unk1A & 4) && (R1C8aS->unk25 & 0x7F) == arg1) {
                    if (!arg2) {
                        camSetFollowMode(gCamActor);
                    }
                    camStartPath(D_807FBB4C, 3, 5);
                    D_807FBB40->unk154 = 0x28;
                    D_807FBB40->unk155[0] = 0;
                    D_807FDC9C->unk10 = 0x28;
                    R1C8aD->unk1F0 &= 0xFFFEFFFF;
                    R1C8aS->unk1A &= 0x7FFF;
                } else {
                    if (!arg2) {
                        camSetTarget(gCamActor, D_807FBB4C, 4, (s16)(gFrameCounter * 20), 0x1E, 0, 0xA, 0x1E, 0xC, 0, 0.2f);
                    }
                    D_807FBB4C->unkE6 = D_807FBB40->unkE6;
                    D_807FBB4C->unk7C = D_807FBB40->unk7C;
                    D_807FBB4C->unk80 = D_807FBB40->unk80 - 2.0f;
                    D_807FBB4C->unk84 = D_807FBB40->unk84;
                    D_807FBB4C->unk6A &= 0xFFFE;
                    D_807FBB4C->unk110 = 0;
                }
            }
            func_806B49B0((D_807FBB40->unk154 == 0x26) ? 0x26 : 2, 0x23D, 0x23E);
            break;
        case 0:
            break;
    }
}

void sfxAllocateChannel(s32, f32);

void func_806C43A8(void) {
    s32 sfx = 0;

    switch (gCurrentMap) {
        case 6:
            sfx = 3;
            break;
        case 0x6A:
            sfx = 0x6A;
            break;
        case 0x37:
            sfx = 0x4A;
            break;
    }
    if (sfx != 0) {
        sfxAllocateChannel(sfx, 1.0f);
    }
}

extern s16 D_80750AC8;

s32 flagGet(s16, s32);
s32 func_807142D8();
s32 slotQueueGetValue(s32, s32);
void func_80724CA4(s32, s32);
void func_80724E48(u8);
void actorSpawnNodeEntryAtActor(s32, s16);
void actorPlaceAttachedChildren(s32);
f32 func_80612794(s16);
f32 func_80612790(s16);
void func_805FF544(void);
void hudSpawnTextScreen(s32);

void func_806C4414(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6) {
    s16 *sp4C = R1C8aA->unk178;
    R1C8aSub174 *sub = gPlayerSlots->unk4->unk174;
    Actor *sp44 = sub->unk88;
    s32 var;

    D_80750AC8 = arg5;
    lightAdd(D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84, 0.0f, 0.0f, 0.0f, 80.0f, 0, 0xFF, 0xFF, 0xFF);
    if (!(D_807FBB40->unk60 & 0x10)) {
        var = -1;
        if (flagGet(arg6, 0) != 0 || func_807142D8() != 0) {
            if (arg3 == R1C8aC->unk13) {
                func_806C43A8();
            }
            D_807FBB40->unk154 = 0x40;
            return;
        }
        func_80724CA4(1, 1);
        if (arg3 == R1C8aC->unk13) {
            var = arg0;
        } else {
            playerStateQueueCallback(0x46, 0, 0);
            if (slotQueueGetValue(0xB, 0) < arg5) {
                D_807FBB40->unk15F = 0;
                var = arg1;
            } else {
                if (flagGet(arg6, 0) == 0) {
                    var = arg2;
                }
                D_807FBB40->unk15F = 0x80;
            }
        }
        *sp4C = 0xF;
        if (var >= 0) {
            camStartPath(0, (s16)var, 1);
        }
        if (sp44 != 0) {
            sp44->unk168 = 0;
        }
    }
    if (arg4 == R1C8aC->unk13 && (D_807FBB40->unk15F & 0x80) && D_807FDC90->unk2C == 0x5A && flagGet(arg6, 0) == 0) {
        actorSpawnNodeEntryAtActor(0x2D, arg6);
        sfxAllocateChannel(0x14, 1.0f);
    }
    actorPlaceAttachedChildren(-0x1E);
    func_80724E48(0);
    D_807FBB40->unkE6 = (D_807FDC94->unkE6 + 0x800) & 0xFFF;
    D_807FBB40->unk7C = func_80612794(R1C8aA->unkEE) * 12.0f + D_807FDC94->unk7C;
    D_807FBB40->unk84 = func_80612790(R1C8aA->unkEE) * 15.0f + D_807FDC94->unk84;
    D_807FBB40->unk80 = D_807FDC94->unk80 + (f32)*sp4C + func_80612794(gFrameCounter * 100) * 5.0f;
    R1C8aA->unkEE += 0x3C;
    switch (D_807FBB40->unk15F & 0x7F) {
        case 0:
            if (!(D_807FBB40->unk60 & 0x2000000)) {
                D_807FDC90->unk2C = 0x1E;
            } else {
                D_807FBB40->unk15F++;
            }
            break;
        case 1:
            if (D_807FBB40->unk60 & 0x2000000) {
                D_807FDC90->unk2C = 0x1E;
            } else {
                D_807FBB40->unk15F++;
                if (arg4 == R1C8aC->unk13) {
                    if (slotQueueGetValue(0xB, 0) >= arg5) {
                        D_807FDC90->unk2C = 0x78;
                    }
                }
            }
            break;
    }
    if (D_807FDC90->unk2C != 0) {
        D_807FDC90->unk2C--;
    }
    if (D_807FDC90->unk2C == 0) {
        if (++*sp4C >= 0x3D) {
            D_807FBB40->unk154 = 0x40;
            func_806C43A8();
            if (arg4 == R1C8aC->unk13) {
                if (flagGet(arg6, 0) != 0 || slotQueueGetValue(0xB, 0) >= arg5) {
                    func_805FF544();
                } else {
                    hudSpawnTextScreen(1);
                }
            }
        }
    }
}

void func_806C4904(void) {
    func_806C4414(0, 1, 2, 0xF, 0x10, 0x32, 0x18);
}

void func_806C4948(void) {
    func_806C4414(6, 7, 8, 0x10, 0xE, 0x32, 0xD7);
}

void func_806C498C(void) {
    func_806C4414(1, 2, 3, 4, 5, 0x19, 0x13E);
}

void behaviourFrameBegin(void);
void actorUpdateModelMatrix(Actor *, s32);

void func_806C49D0(void) {
    behaviourFrameBegin();
    switch (gCurrentMap) {
        case 0x26:
            func_806C3F10(2, 6, 0);
            break;
        case 6:
            func_806C4904();
            break;
        case 0x37:
            func_806C4948();
            break;
        case 0x6A:
            func_806C498C();
            break;
        case 0x30:
            if (R1C8aC->unk13 == 6) {
                func_806C3F10(2, 7, 0x1A);
            } else {
                func_806C3F10(2, 3, 0);
            }
            break;
    }
    actorUpdateModelMatrix(D_807FBB40, 0);
}

extern u8 gPlayerCharacterId;
extern Actor *D_807FBB44;

f32 mathAngleBetweenPointsDeg(s32, s32, s32, s32);
void sfxPlayAtPositionPooled(f32, f32, f32, s32, s32, s32, s32, s32, f32, s32);
void actorSpawn(s32, s32);
void actorMoveWithinZone(s32, f32, f32, s32, f32);
void renderCallbacksRegister(void *, void *, s32);
void actorDrawAnimatedEffect();

u8 func_806C4AC4(u16 arg0, u16 arg1) {
    u8 ret = 0;
    s32 pad;
    s16 *sp44;
    s16 *sp40;
    f32 ang;

    pad = 0;
    sp40 = R1C8aA->unk178;
    sp44 = R1C8aA->unk180;
    if (!(D_807FBB40->unk60 & 0x10)) {
        D_807FDC98->unk46 |= 0x20;
        D_807FBB40->unkB8 = (f32)(u32)D_807FDC9C->unkC;
    }
    {
        s32 d = D_807FDC90->unkC - D_807FDC9C->unk6;

        if (d < 0) {
            *sp40 = 0;
        } else {
            *sp40 = d;
        }
    }
    switch (D_807FBB40->unk154) {
        case 0x37:
            actorMoveWithinZone(0x37, 0.0f, 0.0f, 0x22, 0.0f);
            break;
        case 2:
        case 0x26:
            R1C8aD->unk1F4 |= 0x40;
            ang = mathAngleBetweenPointsDeg((s32)D_807FBB40->unk7C, (s32)D_807FBB40->unk84, (s32)D_807FBB4C->unk7C, (s32)D_807FBB4C->unk84);
            R1C8aA->unkEC = (s16)(ang - mathAngleBetweenPointsDeg((s32)gPlayerSlots->unk228, (s32)gPlayerSlots->unk230, (s32)gPlayerSlots->unk210, (s32)gPlayerSlots->unk218));
            func_806B49B0(D_807FBB40->unk154, R1C8aV98->unk28, R1C8aV98->unk2A);
            D_807FBB40->unk15F = arg1 - D_807FDC90->unk2C + 1;
            if (D_807FBB70.unk0 != 0) {
                if (D_807FBB40->unk15F != D_807FBB70.unk1[0]) {
                    ret = 1;
                } else {
                    D_807FDC90->unk2C--;
                    if (D_807FDC90->unk2C == 0) {
                        ret = 2;
                    }
                }
            }
            if (gPlayerCharacterId != 1) {
                ret = 1;
            }
            if (*sp44 != 0) {
                (*sp44)--;
            } else if (D_807FBB40->unk168 < arg1) {
                sfxPlayAtPositionPooled(D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84, 0x1DD, 0xFF, 0x7F, 0x14, 0x14, 0.0f, 0);
                actorSpawn(0x18, 0);
                D_807FBB40->unk168++;
                D_807FBB44->unk15F = D_807FBB40->unk168;
                D_807FBB44->unk7C = D_807FBB40->unk7C;
                D_807FBB44->unk80 = D_807FBB40->unk80 - 10.0f;
                D_807FBB44->unk84 = D_807FBB40->unk84;
                D_807FBB44->unkE6 = D_807FBB40->unkE6;
                D_807FBB44->unk11C = (s32)D_807FBB40;
                *sp44 = arg0;
            }
            renderCallbacksRegister(actorDrawAnimatedEffect, D_807FBB40, 3);
            break;
    }
    actorUpdateModelMatrix(D_807FBB40, 0);
    return ret;
}

void slotQueueSetDisplayMode();

void func_806C4E8C(void) {
    slotQueueSetDisplayMode(5, 0, 0);
}

void csModelStateSetFirstByte();

void func_806C4EB4(void) {
    csModelStateSetFirstByte(0x2C, 0xB);
    func_806C4E8C();
}

void func_8070E8DC();

void func_806C4EE0(u8 arg0, u8 arg1) {
    R1C8aS->unk2E = 0;
    func_8070E8DC(1);
    func_8070D8C0(D_807FBB40, 0xF, arg0);
    D_807FBB40->unk154 = 0x29;
    D_807FBB40->unk155[0] = 0;
    D_807FBB40->unk168 = arg1;
    R1C8aA->unkF0 = 0;
}

typedef struct LgC4F5CA {
    /* 0x000 */ u8 pad0[0x60];
    /* 0x060 */ u32 unk60;
    /* 0x064 */ u8 pad64[0x18];
    /* 0x07C */ f32 unk7C;
    /* 0x080 */ f32 unk80;
    /* 0x084 */ f32 unk84;
    /* 0x088 */ u8 pad88[0x1C];
    /* 0x0A4 */ f32 unkA4;
    /* 0x0A8 */ u8 padA8[0x3E];
    /* 0x0E6 */ s16 unkE6;
    /* 0x0E8 */ u8 padE8[8];
    /* 0x0F0 */ s16 unkF0;
    /* 0x0F2 */ u8 padF2[0x38];
    /* 0x12A */ s16 unk12A;
    /* 0x12C */ u8 pad12C[0x28];
    /* 0x154 */ u8 unk154;
    /* 0x155 */ u8 unk155;
    /* 0x156 */ u8 pad156[8];
    /* 0x15E */ u8 unk15E;
    /* 0x15F */ u8 pad15F[9];
    /* 0x168 */ s16 unk168;
    /* 0x16A */ u8 pad16A[0x16];
    /* 0x180 */ s16 *unk180;
} LgC4F5CA;

typedef struct LgC4F5CG {
    /* 0x000 */ u8 pad0[0x1F4];
    /* 0x1F4 */ u32 unk1F4;
} LgC4F5CG;

typedef struct LgC4F5CS90 {
    /* 0x00 */ u8 pad0[0x1A];
    /* 0x1A */ u16 unk1A;
    /* 0x1C */ u8 pad1C[9];
    /* 0x25 */ u8 unk25;
    /* 0x26 */ u8 pad26[2];
    /* 0x28 */ u8 unk28[4];
    /* 0x2C */ s16 unk2C;
    /* 0x2E */ s16 unk2E;
} LgC4F5CS90;

#define LgA ((LgC4F5CA *)D_807FBB40)
#define LgB ((LgC4F5CA *)D_807FBB4C)
#define LgG ((LgC4F5CG *)gActivePlayerState)
#define LgS ((LgC4F5CS90 *)D_807FDC90)

void behaviourSetAnimIds(s32, s32, s32);
void func_806BFBF4(void);
s32 currentActorTestClearFlag(void);
void csModelStateSetFirstByte(s32, s32);
void actorScriptStart(Actor *, s32);
void func_8070E8DC(s32);
s32 camIsCutsceneActive(void);
void slotQueueSetDisplayMode(s32, s32, s32);
void func_8072A450(void);
void func_806C4EB4(void);
s32 func_80724A20(void);
void zoneEntryGetPosition(s32, s32, f32 *, f32 *, f32 *);
void actorClearMovementFlags(void *);
s32 func_8072881C(s32, void *);

void func_806C4F5C(void) {
    s32 pad;
    s16 *sp28;
    f32 dx;
    f32 dy;
    f32 dz;

    sp28 = LgA->unk180;
    behaviourFrameBegin();
    if (!(LgA->unk60 & 0x10)) {
        LgA->unk154 = 0x1E;
        behaviourSetAnimIds(0x244, 0x244, 0x246);
        LgA->unk15E = (u32)LgA->unk15E / 2.0;
    }
    LgG->unk1F4 &= ~0x40;
    switch (LgA->unk154) {
        case 0:
        case 14:
        case 15:
        case 30:
            func_806BFBF4();
            if (currentActorTestClearFlag() != 0) {
                csModelStateSetFirstByte(0x2D, 0x14);
                LgA->unk12A = 0x3E8;
                D_807FDC98->unk46 |= 0x24;
                func_8070D8C0(D_807FBB40, 0xF, 0);
                actorScriptStart(D_807FBB40, 0x244);
                LgA->unk154 = 0x27;
                LgS->unk2E = 0xF0;
            }
            break;
        case 39:
            LgG->unk1F4 |= 0x40;
            func_806B49B0(2, 0x244, 0x246);
            if ((LgS->unk1A & 4) && ((LgS->unk25 & 0x7F) == 3)) {
                LgA->unk154 = 0x28;
                LgA->unk155 = 0;
                actorScriptStart(D_807FBB40, 0x244);
            }
            break;
        case 40:
            LgG->unk1F4 |= 0x40;
            switch (LgA->unk155) {
                case 0:
                case 1:
                case 2:
                    if (LgA->unkA4 + 10.0f < LgA->unk80) {
                        LgA->unk80 -= 2.0f;
                    }
                    dx = LgB->unk7C - LgA->unk7C;
                    dy = LgB->unk80 - LgA->unk80;
                    dz = LgB->unk84 - LgA->unk84;
                    if (dx * dx + dy * dy + dz * dz < 6400.0f) {
                        LgA->unk155 = 3;
                        camStartPath(D_807FBB40, 0x1A, 1);
                        actorScriptStart(D_807FBB40, 0x245);
                    } else if (LgS->unk2E != 0) {
                        LgS->unk2E--;
                    } else {
                        LgA->unk154 = 0x29;
                        LgA->unk155 = 0;
                        LgS->unk2E = 0;
                        func_8070E8DC(1);
                        func_8070D8C0(D_807FBB40, 0xF, 2);
                    }
                    break;
                case 3:
                    if (camIsCutsceneActive() == 0) {
                        csModelStateSetFirstByte(0x2C, 0x1E);
                        *sp28 = 0x78;
                        LgS->unk2C = 0xA;
                        LgA->unk154 = 2;
                        LgA->unk155 = 0;
                        slotQueueSetDisplayMode(5, 0, 1);
                        actorScriptStart(D_807FBB40, 0x244);
                    }
                    break;
            }
            func_8072A450();
            break;
        case 41:
            if (LgA->unkF0 == 0) {
                camStartPath(D_807FBB40, 0x1C, 1);
                LgA->unkF0++;
            } else if (camIsCutsceneActive() == 0) {
                if (LgA->unk168 == 0) {
                    func_806C4EB4();
                    hudSpawnTextScreen(3);
                    LgA->unk154 = 0x2A;
                    LgA->unk155 = 0;
                } else if (LgA->unkF0 == 1) {
                    csModelStateSetFirstByte(0xEB, 0xA);
                    LgA->unkF0++;
                }
                LgA->unk80 += 3.0f;
                LgS->unk2E++;
                if (LgS->unk2E >= 0x83) {
                    D_807FDC98->unk46 &= 0xFFFB;
                    func_806C4EB4();
                    LgA->unk154 = 0x3C;
                }
            }
            func_8072A450();
            break;
        case 42:
            func_80724A20();
            break;
        case 48:
            LgA->unkE6 = 0xA82;
            LgB->unkE6 = 0xA82;
            zoneEntryGetPosition(8, 2, &LgA->unk7C, &LgA->unk80, &LgA->unk84);
            actorClearMovementFlags(D_807FBB4C);
            zoneEntryGetPosition(8, 2, &LgB->unk7C, &LgB->unk80, &LgB->unk84);
            LgB->unk80 -= 25.0f;
            LgA->unk154 = 0x28;
            LgA->unk155 = 0;
            actorScriptStart(D_807FBB40, 0x244);
            LgS->unk25 = 2;
            slotQueueSetDisplayMode(5, 0, 1);
            break;
    }
    switch (func_806C4AC4(0x78, 0xA)) {
        case 1:
            func_806C4EE0(2, 0);
            break;
        case 2:
            func_806C4EE0(3, 1);
            break;
    }
    func_8072881C(0, LgS->unk28);
}

void func_806C55D8(void) {
}

typedef struct LgC55E0Sub4 {
    /* 0x00 */ u8 pad0[0x64];
    /* 0x64 */ u16 unk64;
} LgC55E0Sub4;

typedef struct LgC55E0A {
    /* 0x000 */ u8 pad0[4];
    /* 0x004 */ LgC55E0Sub4 *unk4;
    /* 0x008 */ u8 pad8[0x58];
    /* 0x060 */ u32 unk60;
    /* 0x064 */ u8 pad64[0x18];
    /* 0x07C */ f32 unk7C;
    /* 0x080 */ f32 unk80;
    /* 0x084 */ f32 unk84;
    /* 0x088 */ u8 pad88[0x5C];
    /* 0x0E4 */ s16 unkE4;
    /* 0x0E6 */ s16 unkE6;
    /* 0x0E8 */ s16 unkE8;
    /* 0x0EA */ u8 padEA[0x40];
    /* 0x12A */ s16 unk12A;
    /* 0x12C */ u8 pad12C[0x28];
    /* 0x154 */ u8 unk154;
    /* 0x155 */ u8 unk155;
    /* 0x156 */ u8 pad156[0x12];
    /* 0x168 */ s16 unk168;
    /* 0x16A */ u8 pad16A[0x16];
    /* 0x180 */ s16 *unk180;
} LgC55E0A;

typedef struct LgC55E0G {
    /* 0x000 */ u8 pad0[0x1F0];
    /* 0x1F0 */ u32 unk1F0;
    /* 0x1F4 */ u32 unk1F4;
} LgC55E0G;

typedef struct LgC55E0S90 {
    /* 0x00 */ u8 pad0[0x25];
    /* 0x25 */ u8 unk25;
    /* 0x26 */ u8 pad26[2];
    /* 0x28 */ u8 unk28[4];
    /* 0x2C */ s16 unk2C;
} LgC55E0S90;

#define LA ((LgC55E0A *)D_807FBB40)
#define LA4C ((LgC55E0A *)D_807FBB4C)
#define LG ((LgC55E0G *)gActivePlayerState)
#define LS90 ((LgC55E0S90 *)D_807FDC90)

void func_80728950(s32);
void currentActorAnimSetFrame(s32, s32);
void camResumePath(void);
void slotQueueUpdate(s32, s32, s32);
void func_806C4E8C(void);
void func_8072DC7C(s32);
void actorSetPositionFromPoint(Actor *, Struct807FDC9C *);
s16 mathAngleBetweenPoints2D(f32, f32, f32, f32);
void effectSpawnSmoke(u8);

void func_806C55E0(void) {
    s32 pad;
    s16 *sp20;

    sp20 = LA->unk180;
    behaviourFrameBegin();
    if (!(LG->unk1F0 & 0x100000)) {
        LA->unk154 = 0x40;
        return;
    }
    if (!(LA->unk60 & 0x10)) {
        behaviourSetAnimIds(0x357, 0x357, 0x359);
        D_807FDC98->unk46 |= 0x20;
        LA->unk154 = 0x1E;
        LA->unk12A = 0x3E8;
        func_80728950(0);
    }
    switch (LA->unk154) {
        case 0x1E:
            effectSpawnSmoke(1);
            func_80724A20();
            break;
        case 0x27:
            switch (LA->unk155) {
                case 0:
                    if (camIsCutsceneActive() == 0) {
                        currentActorAnimSetFrame(0, 0);
                        camStartPath(D_807FBB40, 0x13, 1);
                        LA->unk155++;
                    }
                    break;
                case 1:
                    if (currentActorTestClearFlag() != 0) {
                        actorScriptStart(D_807FBB40, 0x354);
                        LA->unk155++;
                    }
                    break;
                case 3:
                    func_8070D8C0(D_807FBB40, 0x15, 0);
                    LA->unk155++;
                    break;
                case 4:
                    if (!(LA->unk60 & 0x2000000)) {
                        camResumePath();
                        LA->unk154 = 0x28;
                    }
                    break;
            }
            break;
        case 0x28:
            if (LA4C->unk154 == 0x63) {
                if ((LA->unk7C - LA4C->unk7C) * (LA->unk7C - LA4C->unk7C) + (LA->unk84 - LA4C->unk84) * (LA->unk84 - LA4C->unk84) < 10000.0f) {
                    camStartPath(D_807FBB40, 0x15, 1);
                    func_8070D8C0(D_807FBB40, 0x15, 1);
                    LA->unk154 = 0x29;
                    LA->unk155 = 0;
                }
            }
            break;
        case 0x29:
            switch (LA->unk155) {
                case 0:
                    if (!(LA->unk60 & 0x2000000)) {
                        actorScriptStart(D_807FBB40, 0x358);
                        LA->unk155 = 1;
                    }
                    break;
                case 2:
                    camResumePath();
                    D_807FDC98->unk46 |= 0x24;
                    LA->unk154 = 2;
                    slotQueueSetDisplayMode(5, 0, 1);
                    slotQueueUpdate(5, 1, 0);
                    *sp20 = 0x78;
                    LS90->unk2C = 0x10;
                    LA->unk168 = 0;
                    actorScriptStart(D_807FBB40, 0x357);
                    break;
            }
            break;
        case 0x2A:
            switch (LA->unk155) {
                case 0:
                    LA->unkE4 = 0;
                    LA->unkE8 = 0;
                    if (!(LA->unk60 & 0x2000000)) {
                        camResumePath();
                        func_806C4E8C();
                        if (LA->unk4->unk64 == 0x35A && LA4C->unk154 == 0x63) {
                            hudSpawnTextScreen(4);
                            LA->unk155 = 3;
                        } else {
                            LA->unk155++;
                            LA->unk60 &= ~0x8000;
                        }
                    }
                    break;
                case 1:
                    func_8072DC7C(5);
                    break;
                case 2:
                    LA->unk154 = 0x3C;
                    break;
                case 3:
                    func_80724A20();
                    break;
            }
            break;
        case 0x30:
            actorScriptStart(D_807FBB40, 0x355);
            actorSetPositionFromPoint(D_807FBB40, D_807FDC9C);
            LS90->unk25 = 0;
            LA->unk168 = 0;
            actorClearMovementFlags(D_807FBB4C);
            LA4C->unk80 = LA->unk80;
            LA4C->unk7C = func_80612794(LA->unkE6) * 50.0f + LA->unk7C;
            LA4C->unk84 = func_80612790(LA->unkE6) * 50.0f + LA->unk84;
            LA4C->unkE6 = mathAngleBetweenPoints2D(LA->unk7C, LA->unk84, LA4C->unk7C, LA4C->unk84);
            camStartPath(D_807FBB40, 0x15, 1);
            func_8070D8C0(D_807FBB40, 0x15, 1);
            LA->unk154 = 0x29;
            LA->unk155 = 0;
            break;
    }
    LG->unk1F4 &= ~0x40;
    switch (func_806C4AC4(0x78, 0x10)) {
        case 1:
            actorSetPositionFromPoint(D_807FBB40, D_807FDC9C);
            func_8070D8C0(D_807FBB40, 0x15, 2);
            actorScriptStart(D_807FBB40, 0x35A);
            LA->unk154 = 0x2A;
            LA->unk155 = 0;
            camStartPath(D_807FBB40, 0x16, 1);
            break;
        case 2:
            actorSetPositionFromPoint(D_807FBB40, D_807FDC9C);
            func_8070D8C0(D_807FBB40, 0x15, 3);
            actorScriptStart(D_807FBB40, 0x35B);
            LA->unk154 = 0x2A;
            LA->unk155 = 0;
            camStartPath(D_807FBB40, 0x14, 1);
            break;
    }
    if (LA->unk154 != 0x1E) {
        func_8072881C(0, LS90->unk28);
    }
}

typedef struct R1C8CBG {
    /* 0x000 */ u8 pad0[0x1F4];
    /* 0x1F4 */ u32 unk1F4;
} R1C8CBG;

typedef struct R1C8CBA {
    /* 0x000 */ u8 pad0[0x60];
    /* 0x060 */ u32 unk60;
    /* 0x064 */ u8 pad64[0x18];
    /* 0x07C */ f32 unk7C;
    /* 0x080 */ f32 unk80;
    /* 0x084 */ f32 unk84;
    /* 0x088 */ u8 pad88[0x5C];
    /* 0x0E4 */ s16 unkE4;
    /* 0x0E6 */ s16 unkE6;
    /* 0x0E8 */ s16 unkE8;
    /* 0x0EA */ u8 padEA[2];
    /* 0x0EC */ s16 unkEC;
    /* 0x0EE */ s16 unkEE;
    /* 0x0F0 */ s16 unkF0;
    /* 0x0F2 */ u8 padF2[0x62];
    /* 0x154 */ u8 unk154;
    /* 0x155 */ u8 unk155;
    /* 0x156 */ u8 pad156[9];
    /* 0x15F */ u8 unk15F;
    /* 0x160 */ u8 pad160[8];
    /* 0x168 */ s16 unk168;
    /* 0x16A */ u8 pad16A[0xA];
    /* 0x174 */ R1C8CBG *unk174;
} R1C8CBA;

typedef struct R1C8CBCfg {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ Actor *unkC;
    /* 0x10 */ R1C8CBA *unk10;
    /* 0x14 */ s16 unk14;
    /* 0x16 */ s16 unk16;
    /* 0x18 */ u8 pad18[2];
    /* 0x1A */ s16 unk1A;
    /* 0x1C */ s16 unk1C;
    /* 0x1E */ s8 unk1E;
} R1C8CBCfg;

typedef struct R1C8CBPlayer {
    /* 0x000 */ u8 pad0[0x210];
    /* 0x210 */ f32 unk210;
    /* 0x214 */ u8 pad214[4];
    /* 0x218 */ f32 unk218;
    /* 0x21C */ u8 pad21C[0x68];
    /* 0x284 */ f32 unk284;
} R1C8CBPlayer;

typedef struct R1C8CB580 {
    /* 0x000 */ u8 pad0[0x1EC];
    /* 0x1EC */ u8 unk1EC;
    /* 0x1ED */ u8 pad1ED[3];
    /* 0x1F0 */ s32 unk1F0;
} R1C8CB580;

#define R1A ((R1C8CBA *)D_807FBB40)
#define R1A4C ((R1C8CBA *)D_807FBB4C)
#define R1D580 ((R1C8CB580 *)gActivePlayerState)

extern s16 D_8076A0AA;
extern s32 D_8071FB08;
extern u32 D_807FBB60;
#define R1C8CBP ((R1C8CBPlayer *)gPlayerSlots)
extern s16 D_807FD802;
extern s16 D_807FD804;
extern s16 D_807FD806;
void actorAttachChildCallbacks(void);
void actorDespawn(Actor *);
void func_80614E78(Actor *, s32);
s32 randomNonNegative(void);
void func_807149B8(s32);
void func_8071C818(void);
void func_8071498C(void (*)(void));
void func_80714CC0(void *, f32, f32, f32, f32);
f32 sqrtf(f32);
s32 func_8072DE10(u16);
s32 spawnNodeIdForActor(Actor *);
s32 func_80731784(s16, s16, s32 *);
void flagSet(s16, s32, s32);
void eepromSavePlayerData();
void camProjectToScreen(f32, f32, f32, f32 *, f32 *, s32, f32, s32);
s32 func_8073195C(s16);
void lightSetColor(f32, f32, f32, s16);
void sfxStopChannel();

void func_806C5C20(void) {
    f32 sp54;
    f32 sp50;
    f32 dist;
    s32 sp44[2];

    behaviourFrameBegin();
    actorClearMovementFlags(D_807FBB40);
    if (!(D_807FBB40->unk60 & 0x10)) {
        D_807FDC98->unk46 |= 0x40;
        D_807FBB40->unk12A = 0xFA;
        func_80724CA4(2, 1);
    }
    if ((randomNonNegative() >> 15) % 1000 >= 0x3CB) {
        D_807FBB40->unkB8 = D_807FDC9C->unkC << 2;
    }
    func_80724E48(6);
    actorMoveWithinZone(1, D_807FDC94->unk7C, D_807FDC94->unk84, 0x2C9, 0.0f);
    if (!(gFrameCounter & 3)) {
        func_807149B8(1);
        func_8071498C(func_8071C818);
        func_80714CC0(&D_8071FB08, 1.6f, D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84);
    }
    if (!(gActivePlayerState->unk1F0 & 0x8000)) {
        dist = sqrtf((R1C8CBP->unk218 - D_807FBB40->unk84) * (R1C8CBP->unk218 - D_807FBB40->unk84) +
                     (R1C8CBP->unk210 - D_807FBB40->unk7C) * (R1C8CBP->unk210 - D_807FBB40->unk7C)) -
               R1C8CBP->unk284;
        if (D_807FD804 >= 0x8A && D_807FD804 < 0xB1 && D_807FD806 >= 0x61 && D_807FD806 < 0x88 && dist < D_807FD802) {
            if (R1D580->unk1EC != 1) {
                if (func_8072DE10(0x1388) != 0) {
                    actorScriptStart(D_807FBB40, 0x2B6);
                }
            }
            R1D580->unk1EC = 1;
        } else {
            if (R1D580->unk1EC != 2) {
                actorScriptStart(D_807FBB40, 0x2B5);
            }
            R1D580->unk1EC = 2;
        }
    }
    if ((gActivePlayerState->unk1F0 & 0x8000) && R1D580->unk1EC == 1) {
        if (D_807FBB40->unk154 != 0x40) {
            flagSet(func_80731784(D_8076A0AA, spawnNodeIdForActor(D_807FBB40), sp44), 1, 0);
            eepromSavePlayerData();
        }
        D_807FBB40->unk154 = 0x40;
    }
    if (D_807FBB40->unk154 != 0x40) {
        sfxAllocateChannel(0x42, 1.0f);
    } else {
        sfxStopChannel(0x42, 0);
    }
    camProjectToScreen(D_807FBB40->unk7C, D_807FBB40->unk80 + 10.0f, D_807FBB40->unk84, &sp54, &sp50, 0, 1.0f, 0);
    D_807FD804 = sp54;
    D_807FD806 = sp50;
    actorUpdateModelMatrix(D_807FBB40, 0);
}


void func_806C5FEC(void) {
    R1C8CBCfg *p;

    p = (R1C8CBCfg *)D_807FBB40->unk174;
    if (!(D_807FBB40->unk60 & 0x10)) {
        p->unk1C = 0;
        D_807FBB40->unk60 |= 0x400;
    }
    p->unk1C++;
    switch (p->unk1E) {
        case 1:
            if (R1A4C->unk155 == 3) {
                func_8070D8C0(D_807FBB40, 0x1E, 3);
                p->unk1E = 2;
            } else if (p->unk10->unk154 != 0x83) {
                p->unk1E = 3;
            }
            break;
        case 2:
            if (!(D_807FBB40->unk60 & 0x2000000)) {
                p->unk1E = 3;
                camResumePath();
            }
            break;
        default:
            if (p->unk10->unk154 != 0x83) {
                p->unk10->unk174->unk1F4 &= ~0x10;
                p->unk10->unk60 &= ~0x40000000;
                p->unk10->unk60 |= 1;
                p->unk10->unkE8 = p->unk16;
                p->unk10->unkE4 = p->unk14;
                D_807FBB60 |= 0x10030;
                lightSetColor(p->unk0, p->unk4, p->unk8, p->unk1A);
                sfxStopChannel(0x3B, 0);
                actorDespawn(p->unkC);
                actorDespawn(D_807FBB40);
                return;
            }
            break;
    }
    actorUpdateModelMatrix(D_807FBB40, 0);
}


void func_806C61C8(void) {
    f32 x;
    f32 z;
    f32 sinv;

    if (!(D_807FBB40->unk60 & 0x10)) {
        R1A->unkEC = 0x3C;
        actorScriptStart(D_807FBB40, 0x23D);
        if (R1A4C->unk154 == 0xC) {
            func_80614E78((Actor *)D_807FBB4C, 0x87);
        }
    }
    x = func_80612794(R1A4C->unkE6) * 50.0f + R1A4C->unk7C;
    z = func_80612790(R1A4C->unkE6) * 50.0f + R1A4C->unk84;
    R1A->unkE6 = (R1A4C->unkE6 + 0x800) & 0xFFF;
    if (R1A->unkEC == 0x3C) {
        D_807FBB40->unk7C = func_80612794(R1A->unkEE) * 10.0f + x;
        D_807FBB40->unk84 = func_80612790(R1A->unkEE) * 10.0f + z;
    }
    R1A->unk80 = func_80612794(gFrameCounter * 100) * 5.0f + (R1A->unk15F + R1A4C->unk80 + 3.0f + R1A->unkEC);
    if (!(D_807FBB40->unk60 & 0x10)) {
        if (R1A->unkF0 != 0) {
            R1A->unk15F = 0x14;
            actorSpawnNodeEntryAtActor(0x2D, func_8073195C(R1A->unkF0));
        }
    }
    if (R1A->unkF0 != 0) {
        actorPlaceAttachedChildren(-0x1E);
    }
    sinv = func_80612794(gFrameCounter * 50);
    R1A->unkEE = R1A->unkEE + 60.0f * sinv;
    if (D_807FBB40->unk60 & 0x2000000) {
        R1A->unk168 = 0x14;
    }
    if (R1A->unk168 != 0) {
        R1A->unk168--;
    }
    if (R1A->unk168 == 0) {
        R1A->unkEC++;
        if (R1A->unkEC >= 0x3D) {
            if (R1A->unkF0 != 0) {
                actorAttachChildCallbacks();
            }
            actorDespawn(D_807FBB40);
            camResumePath();
            if (R1A4C->unk154 == 0xC) {
                func_80614E78((Actor *)D_807FBB4C, 9);
            }
        }
    } else if (R1A->unkEC >= 0x10) {
        R1A->unkEC--;
    }
    actorUpdateModelMatrix(D_807FBB40, 0);
}
