#include "common.h"

s32 func_805FCA64(void);
Gfx *func_8068DC54(Gfx *, s32, s32, void *, s16, void *);
Gfx *textDrawAnimated(Gfx *, u8, s32, f32, f32, f32, f32);
Gfx *func_8070068C(Gfx *);
extern Gfx D_1000118;
extern Gfx D_2000180;

Gfx *bonusRenderCounterHud(Gfx *gdl, void *arg1) {
    void *temp_s0;
    Gfx *temp_v0;

    temp_s0 = *(void **)((u8 *)arg1 + 0x178);
    if (func_805FCA64()) {
        gSPDisplayList(gdl++, &D_1000118);
        gdl = func_8070068C(gdl);
        gDPSetCombineMode(gdl++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
        gDPSetPrimColor(gdl++, 0, 0, 255, 255, 255, 255);
        gSPMatrix(gdl++, &D_2000180, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gdl = func_8068DC54(
            textDrawAnimated(gdl, *(u8 *)((u8 *)temp_s0 + 9), 8, 30.0f, 36.0f, 0.0f, 1.5f),
            0x26, 0x32, (u8 *)temp_s0 + 2, *(s16 *)((u8 *)temp_s0 + 4), (u8 *)temp_s0 + 8);
    }
    return gdl;
}

void spawnNodeActivateAndSetState(s32, s32, s32);
void bonusInitSounds(void) {
    spawnNodeActivateAndSetState(1, 0x40, 0);
    spawnNodeActivateAndSetState(2, 0x40, 0);
    spawnNodeActivateAndSetState(3, 0x40, 0);
    spawnNodeActivateAndSetState(4, 0x40, 0);
    spawnNodeActivateAndSetState(5, 0x40, 0);
}

typedef struct LB3bState {
    u16 unk0;
    s16 unk2;
    s16 unk4;
    u8 pad6[3];
    u8 unk9;
} LB3bState;

typedef struct LB3bActor {
    u8 pad0[0x60];
    u32 unk60;
    u8 pad64[0x7C - 0x64];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
    u8 pad88[0xB8 - 0x88];
    f32 unkB8;
    u8 padBC[0x11C - 0xBC];
    struct LB3bActor *unk11C;
    u8 pad120[0x154 - 0x120];
    u8 unk154;
    u8 unk155;
    u8 pad156[9];
    u8 unk15F;
    u8 pad160[0x178 - 0x160];
    LB3bState *unk178;
} LB3bActor;

typedef struct LB3bC9C {
    u8 pad0[0xA];
    u8 unkA;
    u8 unkB;
    u8 pad0C[8];
    u8 unk14;
} LB3bC9C;

typedef struct LB3bTbl {
    u8 pad0[0x258];
    s32 unk258[8];
    u8 *unk278[8];
} LB3bTbl;

extern void *D_807FBB40;
extern void *D_807FBB48;
extern void *D_807FBB4C;
extern void *D_807FDC98;
extern void *D_807FDC9C;
extern s32 D_8076A0A8;
extern s16 D_8076AEF2;
extern u16 D_80744508;
extern s16 D_80750AC4;
extern u8 D_807FBDC4;
extern LB3bTbl D_807FBB70;
extern u8 D_8002D863[];

#define LB ((LB3bActor *)D_807FBB40)
#define LP ((LB3bActor *)D_807FBB4C)
#define LQ ((LB3bActor *)D_807FBB48)
#define LC ((LB3bC9C *)D_807FDC9C)

void behaviourFrameBegin(void);
void func_8072177C(void *, s16, s16, s16, s32, s32, s32, s32, s32);
void currentActorClearFlag(void);
s32 currentActorTestClearFlag(void);
void slotQueueSetDisplayMode(s32, s32, s32);
void func_806A2A10(s32, s32, u8);
s32 randomNonNegative(void);
void csModelStateSetByte(s16, s32, s32);
void csModelStateSetFirstByte(s32, s32);
void func_806C8E58(s32);
void func_80614E78(void *, s32);
void func_806D03BC(void);
s32 func_8070E750(s32, s32, s32);
s32 gfxResourceCreate(s32, char *, s32, f32, f32, f32);
void func_806FDAB8(u8, f32);
void *spawnNodeActivate(s16, s32);
s32 strlen(char *);
s32 func_80610FE8(s32);
void heapFreeDeferred(s32);
s32 _sprintf(char *, const char *, ...);
void textSpawnMarkerChecked(s32, s32, s32, s32, s32, s32, s32, s32);
s32 slotQueueGetValue(s32, s32);
void bonusEndWin(u8, u8);
void bonusEndLose(u8, u8);
void func_80726EE0(s32);
void func_80724A20(void);
void func_80641874(s32, s32);
void camResumePath(void *);
void actorSetStateTwo(void *);
void func_8070E8DC(s32);
void func_8070D8C0(void *, s32, u8);
void sfxAllocateChannel(s32, f32);
u16 camStartPath(s32, s32, s32);
void sfxPlayFromActorWithAltitudeCheck(void *, s32, s32, s32, s32);
void renderCallbacksRegister(void *, void *, s32);

void bonusControllerUpdate(void) {
    s16 i;
    LB3bState *s;
    u8 sp6F;
    u8 sp6E;
    s32 sp68;
    u8 sp67;
    u8 v3;
    u8 a2v;
    s32 sp60;
    s32 pad5C;
    s32 pad58;
    s32 sp54;
    s32 pad50;
    volatile s32 pad4C;
    s32 t;
    u8 *pv;

    s = LB->unk178;
    behaviourFrameBegin();
    sp6F = LC->unk14;
    sp6E = LC->unkA;
    func_8072177C(D_807FBB4C, LP->unk7C, LP->unk80 + 30.0f, LP->unk84, 0xFF, 0xFF, 0xFF, 0xFF, 0);
    if (!(LB->unk60 & 0x10)) {
        sp67 = 0;
        currentActorClearFlag();
        *(u16 *)((u8 *)D_807FDC98 + 0x46) |= 0x80;
        slotQueueSetDisplayMode(2, 0, 1);
        slotQueueSetDisplayMode(5, 0, 1);
        slotQueueSetDisplayMode(4, 0, 2);
        LB->unk154 = 0;
        func_806A2A10(0xDC, 0x2A, LC->unkB);
        switch (sp6F) {
        case 14:
            csModelStateSetByte((randomNonNegative() >> 15) % 32767 % 4, 1, 1);
        case 0:
        case 4:
        case 13:
tail:
            sp68 = func_8070E750(0x1A, 2, 1);
            sp67 = 1;
            break;
        case 15:
            func_806C8E58(8);
            LQ->unk154 = 0xC;
            LQ->unk155 = 0;
            func_80614E78(D_807FBB48, 9);
            LQ->unkB8 = 0.0f;
            func_806D03BC();
            goto tail;
        case 1:
        case 10:
        case 12:
        case 16:
            s->unk2 = 0;
            break;
        case 3:
            bonusInitSounds();
            break;
        case 5:
            bonusInitSounds();
        case 2:
        case 6:
        case 7:
        case 8:
        case 11:
            D_80750AC4 = 0;
            sp68 = func_8070E750(0x1A, 3, 1);
            sp67 = 1;
            break;
        case 9:
            ((LB3bActor *)spawnNodeActivate((randomNonNegative() >> 15) % 32767 % 8 + 0x11, 0))->unk15F = 1;
            break;
        }
        if (sp67 != 0) {
            s->unk9 = gfxResourceCreate(1, (char *)sp68, 8, 0.0f, 0.0f, 0.0f);
            func_806FDAB8(s->unk9, 0.0f);
            s->unk4 = sp6E;
            s->unk2 = sp6E;
        }
    }
    if (LB->unk154 == 0) {
        i = 0;
        if (D_807FBDC4 > 0) {
            do {
                if (D_807FBB70.unk258[i] == 3) {
                    a2v = 1;
                    v3 = D_807FBB70.unk278[i][3];
                    switch (sp6F) {
                    case 0:
                        if (s->unk4 != 0) {
                            if (s->unk4 >= 2) {
                                sp68 = func_8070E750(0x1A, 0xF, 1);
                                sp60 = func_80610FE8(strlen((char *)sp68) + 5);
                                heapFreeDeferred(sp60);
                                _sprintf((char *)sp60, "%d %s", s->unk4, (char *)sp68);
                            } else {
                                sp60 = func_8070E750(0x1A, 0x10, 1);
                            }
                            textSpawnMarkerChecked(0, 0, 0x8C, sp60, 0, 0x28, 8, 8);
                            a2v = 0;
                        }
                        break;
                    case 16:
                        if (s->unk2 == 0 && v3 != 0x28) {
                            textSpawnMarkerChecked(0, 0, 0x8C, func_8070E750(0x1A, 0x17, 1), 0, 0x28, 8, 8);
                            a2v = 0;
                        }
                        if (v3 == 0x28) {
                            a2v = 0;
                        }
                        break;
                    case 2:
                        a2v = 1;
                        if (slotQueueGetValue(0xB, 0) < sp6E) {
                            if (s->unk4 >= 2) {
                                sp68 = func_8070E750(0x1A, 0x11, 1);
                                sp54 = func_80610FE8(strlen((char *)sp68) + 5);
                                _sprintf((char *)sp54, "%d %s", sp6E - slotQueueGetValue(0xB, 0), (char *)sp68);
                            } else {
                                sp54 = func_8070E750(0x1A, 0x12, 1);
                            }
                            textSpawnMarkerChecked(0, 0, 0x8C, sp54, 0, 0x28, 8, 8);
                            a2v = 0;
                        }
                        break;
                    case 7:
                    case 8:
                    case 9:
                    case 11:
                    case 15:
                        a2v = 0;
                        break;
                    case 12:
                    case 13:
                        a2v = 0;
                        if (v3 != 0x12) {
                            if (v3 == 0x27) {
                                LB->unk15F += 1;
                                if (LB->unk15F >= 3) {
                                    csModelStateSetFirstByte(2, 0xA);
                                }
                            } else {
                                bonusEndLose(1, 1);
                            }
                        }
                        break;
                    }
                    if (a2v != 0) {
                        bonusEndWin(1, 0xE);
                        func_80726EE0(0);
                    }
                }
            } while (++i < D_807FBDC4);
        }
    }
    if (LB->unk154 == 0) {
        switch (sp6F) {
        case 15:
            func_80724A20();
        case 4:
        case 11:
        case 13:
        case 14:
            if (s->unk4 == 0) {
                bonusEndWin(1, 0xE);
            }
        case 0:
            if ((((sp6E - D_80744508) < 0) ? 0 : (sp6E - D_80744508)) != s->unk4) {
                func_806FDAB8(s->unk9, 3.1415927f);
                s->unk4 = ((sp6E - D_80744508) < 0) ? 0 : (sp6E - D_80744508);
            }
            goto render;
        case 7:
        case 8:
            func_80724A20();
            goto render;
        case 5:
            if (D_8076A0A8 == 0x85 && s->unk4 == 1) {
                if (LB->unk155 == 0) {
                    LB->unk155 += 1;
                    func_80641874(0, 0);
                    func_80641874(1, 0);
                    func_80641874(2, 0);
                }
            }
        case 6:
            if (s->unk4 == 0) {
                bonusEndWin(1, 0xE);
            }
        case 2:
            if ((((sp6E - slotQueueGetValue(0xB, 0)) < 0) ? 0 : (sp6E - slotQueueGetValue(0xB, 0))) != s->unk4) {
                func_806FDAB8(s->unk9, 3.1415927f);
                s->unk4 = ((sp6E - slotQueueGetValue(0xB, 0)) < 0) ? 0 : (sp6E - slotQueueGetValue(0xB, 0));
            }
render:
            if (s->unk0 >= 2) {
                renderCallbacksRegister(bonusRenderCounterHud, D_807FBB40, 3);
            }
            break;
        case 9:
        case 10:
        case 12:
        case 16:
            func_80724A20();
            break;
        }
    }
    switch (s->unk0) {
    case 0:
        if (currentActorTestClearFlag() != 0) {
            currentActorClearFlag();
            if (D_8076AEF2 == 0x11) {
                func_8070E8DC(2);
            }
            func_8070D8C0(D_807FBB40, 0, D_8002D863[sp6F << 2]);
            s->unk0 += 1;
        }
        break;
    case 1:
        if (!(LB->unk60 & 0x02000000)) {
            camResumePath(D_807FBB40);
            actorSetStateTwo(LB->unk11C);
            switch (D_8076A0A8) {
            case 3:
            case 0x23:
            case 0x32:
            case 0xA5:
            case 0xC9:
            case 0xCA:
            case 0xD1:
            case 0xD2:
            case 0xD3:
            case 0xD4:
                t = 0x75;
                break;
            default:
                switch (sp6F) {
                case 1:
                    t = 0x59;
                    break;
                case 0:
                    if (!pv && !pv && !pv) {
                    }
                    t = 0x52;
                    break;
                default:
                    t = 8;
                    break;
                }
                break;
            }
            sfxAllocateChannel(t, 1.0f);
            s->unk0 += 1;
        }
        break;
    }
    switch (LB->unk154) {
    case 0:
        if ((sp6F == 1 || sp6F == 0 || sp6F == 2 || sp6F == 0x10) && LP->unk80 < 0.0f) {
            bonusEndLose(1, 1);
            return;
        }
        if (sp6F == 4 && LP->unk80 < -20.0f) {
            sfxPlayFromActorWithAltitudeCheck(D_807FBB40, 0x362, 0xFF, 0x7F, 0);
            bonusEndLose(0, 1);
            camStartPath((s32)D_807FBB40, 1, 1);
            return;
        }
        if (LP->unk154 == 0x73) {
            if (sp6F == 1) {
                bonusEndLose(1, 0x13);
                return;
            }
            bonusEndLose(1, 1);
            return;
        }
        if (sp6F == 3 && LP->unk154 == 0x31) {
            bonusEndLose(1, 0x14);
            return;
        }
        pv = &sp6F;
        if (LB->unk11C->unk154 == 5) {
            if (*pv == 3) {
                bonusEndWin(1, 0x15);
                return;
            }
            bonusEndLose(1, 0x16);
            return;
        }
        break;
    case 1:
        LB->unk11C->unk154 = 0;
        LB->unk154 += 1;
        break;
    case 0x27:
        func_806FDAB8(s->unk9, 3.1415927f);
        s->unk4 -= 1;
        if (s->unk4 == 0) {
            bonusEndWin(1, 0xE);
            return;
        }
        LB->unk154 = 0;
        break;
    case 0x28:
        s->unk2 = 1;
        LB->unk154 = 0;
        break;
    case 0x37:
        bonusEndLose(1, 1);
        return;
    case 0x12:
        bonusEndWin(1, 0xE);
        break;
    }
}

Gfx *func_80024D3C(Gfx *gdl, u8 arg1) {
    gSPDisplayList(gdl++, &D_1000118);
    gDPSetCombineMode(gdl++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
    gDPSetPrimColor(gdl++, 0, 0, 255, 255, 255, 255);
    return gdl;
}


s32 bonusGetSoundForMap(void) {
    switch (D_8076A0A8) {
    case 0x35:
        return 0x261;
    case 0x49:
        return 0x262;
    case 0x9B:
        return 0x263;
    case 0x9C:
        return 0x264;
    case 0x9F:
        return 0x265;
    case 0x9D:
        return 0x266;
    case 0x9E:
        return 0x267;
    case 0xA0:
        return 0x268;
    case 0xA1:
        return 0x269;
    case 0xA2:
        return 0x26A;
    default:
        return -1;
    }
}

void n_alSndpPlay(s32, s32, s32, s32, f32, s32, void *);
void camRequestPathLength(void);
void actorSpawnNodeEntryScaled(s32, f32, f32, f32, s32, s32, s32, s32);
void func_805FF898(void);
void func_806C9974(s32, s32);
void n_alSndpPostEvent(void *, s32, s16);
void func_80609140(s32, s32, f32, f32, s32, s32);
extern s32 D_8076D1F8;
extern void *D_807FD580;

void func_80024E38(void) {
    u8 *temp_s0;

    temp_s0 = *(u8 **)((u8 *)D_807FBB40 + 0x178);
    behaviourFrameBegin();
    if (!(*(u32 *)((u8 *)D_807FBB40 + 0x60) & 0x10)) {
        *(u16 *)temp_s0 = 0x12C;
        *(s16 *)(temp_s0 + 0xA) = 0;
        *(s16 *)(temp_s0 + 0x8) = 0;
        n_alSndpPlay(D_8076D1F8, 0x1E6, 0, 0x40, 1.0f, 0x80, temp_s0 + 4);
        func_806A2A10(0xDC, 0x2A, *(u8 *)((u8 *)D_807FDC9C + 0xB));
        spawnNodeActivateAndSetState(1, 0x40, 0x10);
        spawnNodeActivateAndSetState(2, 0x40, 0x10);
        spawnNodeActivateAndSetState(3, 0x40, 0x10);
        spawnNodeActivateAndSetState(4, 0x40, 0x10);
        *(u8 *)((u8 *)D_807FBB40 + 0x154) = 0;
        *(u8 *)((u8 *)D_807FBB40 + 0x155) = 0;
        camRequestPathLength();
        *(u16 *)(temp_s0 + 0x18) = camStartPath(0, 0, 1);
    }
    switch (*(u8 *)((u8 *)D_807FBB40 + 0x154)) {
    case 0:
        if (*(u16 *)(temp_s0 + 0x18) != 0) {
            (*(u16 *)(temp_s0 + 0x18))--;
        } else {
            actorSetStateTwo(*(void **)((u8 *)D_807FBB40 + 0x11C));
            *(u8 *)((u8 *)D_807FBB40 + 0x154) = 1;
        }
        break;
    case 1:
        if (*(u8 *)(*(u8 **)((u8 *)D_807FBB40 + 0x11C) + 0x154) == 5) {
            textSpawnMarkerChecked(0x81, 0, 0x78, func_8070E750(0x1A, 0x15, 1), 0, 0x28, 8, 8);
            func_80726EE0(0);
            sfxAllocateChannel(0x28, 1.0f);
            actorSpawnNodeEntryScaled(0x56, 588.0f, 240.0f, 582.0f, 0, 0, bonusGetSoundForMap(), 0);
            *(u8 *)((u8 *)D_807FBB40 + 0x154) = 2;
        }
        if (*(u8 *)((u8 *)D_807FBB4C + 0x154) == 0x39) {
            func_805FF898();
            func_806C9974(0, 0x40);
            *(u8 *)((u8 *)D_807FBB40 + 0x154) = 2;
        }
        break;
    }
    {
        s32 temp_v0_3 = *(s16 *)(temp_s0 + 0x8) - 0x96;
        (*(u16 *)temp_s0)--;
        if (temp_v0_3 < 0x1F40) {
            *(s16 *)(temp_s0 + 0x8) = 0x1F40;
        } else {
            *(s16 *)(temp_s0 + 0x8) = temp_v0_3;
        }
    }
    {
        s32 temp_v1_2 = *(s16 *)(temp_s0 + 0xA) + 0x3E8;
        if (*(s16 *)(temp_s0 + 0x8) < temp_v1_2) {
            *(s16 *)(temp_s0 + 0xA) = *(s16 *)(temp_s0 + 0x8);
        } else {
            *(s16 *)(temp_s0 + 0xA) = temp_v1_2;
        }
    }
    n_alSndpPostEvent(*(void **)(temp_s0 + 4), 8, *(s16 *)(temp_s0 + 0xA));
    if (*(u32 *)((u8 *)D_807FD580 + 0x1F0) & 0xC0000) {
        if (*(u16 *)temp_s0 < 0x129) {
            *(u16 *)temp_s0 = 0x12C;
            if (*(u32 *)((u8 *)D_807FD580 + 0x1F0) & 0x40000) {
                if (((randomNonNegative() >> 15) % 1000) & 1) {
                    func_80609140(0x1E7, 0x7FFF, 64.0f, 1.0f, 0x14, 0x80);
                } else {
                    func_80609140(0x1EA, 0x7FFF, 64.0f, 1.0f, 0x14, 0x80);
                }
            } else {
                func_80609140(0x1E8, 0x7FFF, 64.0f, 1.0f, 0x14, 0x80);
            }
        }
        {
            s32 temp_v0_5 = *(s16 *)(temp_s0 + 0x8) + 0x4650;
            if (temp_v0_5 >= 0x8000) {
                *(s16 *)(temp_s0 + 0x8) = 0x7FFF;
            } else {
                *(s16 *)(temp_s0 + 0x8) = temp_v0_5;
            }
        }
        *(u32 *)((u8 *)D_807FD580 + 0x1F0) &= 0xFFF3FFFF;
    }
    switch (*(u16 *)temp_s0) {
    case 0x0:
    case 0x14:
    case 0x28:
    case 0x3C:
    case 0x50:
        func_80609140(0x1E9, 0x7FFF - *(u16 *)temp_s0 * 0x96, 64.0f, 1.0f, 0xA, 0x80);
        if (*(u16 *)temp_s0 == 0) {
            *(u16 *)temp_s0 = 0xC8;
        }
        break;
    }
}
