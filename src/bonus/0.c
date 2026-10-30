#include "common.h"
#include "actor.h"

s32 func_805FCA64(void);
Gfx *hudDrawRollingCounter(Gfx *, s32, s32, void *, s16, void *);
Gfx *textDrawAnimated(Gfx *, u8, s32, f32, f32, f32, f32);
Gfx *func_8070068C(Gfx *);
extern Gfx D_1000118;
extern Gfx D_2000180;

typedef struct LB3bState {
    u16 unk0;
    s16 unk2;
    s16 unk4;
    u8 pad6[2];
    u8 unk8;
    u8 unk9;
} LB3bState;

Gfx *bonusRenderCounterHud(Gfx *gdl, Actor *arg1) {
    LB3bState *s = *(LB3bState **)((u8 *)arg1 + 0x178);

    if (func_805FCA64()) {
        gSPDisplayList(gdl++, &D_1000118);
        gdl = func_8070068C(gdl);
        gDPSetCombineMode(gdl++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
        gDPSetPrimColor(gdl++, 0, 0, 255, 255, 255, 255);
        gSPMatrix(gdl++, &D_2000180, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gdl = hudDrawRollingCounter(
            textDrawAnimated(gdl, s->unk9, 8, 30.0f, 36.0f, 0.0f, 1.5f),
            0x26, 0x32, &s->unk2, s->unk4, &s->unk8);
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

typedef struct LB3bSnd {
    u16 unk0;
    u8 pad2[2];
    void *unk4;
    s16 unk8;
    s16 unkA;
    u8 padC[0xC];
    u16 unk18;
} LB3bSnd;

typedef struct LB3bTbl {
    u8 pad0[0x258];
    s32 unk258[8];
    u8 *unk278[8];
} LB3bTbl;

extern Actor *D_807FBB40;
extern Actor *D_807FBB48;
extern Actor *D_807FBB4C;
extern s32 D_8076A0A8;
extern s16 D_8076AEF2;
extern u16 D_80744508;
extern s16 D_80750AC4;
extern u8 D_807FBDC4;
extern LB3bTbl D_807FBB70;
extern u8 D_8002D863[];

void behaviourFrameBegin(void);
void commandQueuePush(void *, s16, s16, s16, s32, s32, s32, s32, s32);
void currentActorClearFlag(void);
s32 currentActorTestClearFlag(void);
void slotQueueSetDisplayMode(s32, s32, s32);
void hudSpawnCountdownTimer(s32, s32, u8);
s32 randomNonNegative(void);
void csModelStateSetByte(s16, s32, s32);
void csModelStateSetFirstByte(s32, s32);
void func_806C8E58(s32);
void func_80614E78(void *, s32);
void func_806D03BC(void);
char *textTableGetString(s32, s32, s32);
s32 gfxResourceCreate(s32, char *, s32, f32, f32, f32);
void func_806FDAB8(u8, f32);
void *spawnNodeActivate(s16, s32);
s32 strlen(char *);
char *heapAlloc(s32);
void heapFreeDeferred(void *);
s32 _sprintf(char *, const char *, ...);
void textSpawnMarkerChecked(s32, s32, s32, char *, s32, s32, s32, s32);
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
u16 camStartPath(void *, s32, s32);
void sfxPlayFromActorWithAltitudeCheck(void *, s32, s32, s32, s32);
void renderCallbacksRegister(void *, void *, s32);

void bonusControllerUpdate(void) {
    s16 i;
    LB3bState *s;
    u8 sp6F;
    u8 sp6E;
    char *sp68;
    u8 sp67;
    u8 v3;
    u8 a2v;
    char *sp60;
    s32 pad5C;
    s32 pad58;
    char *sp54;
    s32 pad50;
    s32 pad4C;
    s32 t;
    u8 *pv;

    s = *(LB3bState **)((u8 *)D_807FBB40 + 0x178);
    behaviourFrameBegin();
    sp6F = D_807FDC9C->unk14;
    sp6E = D_807FDC9C->unkA;
    commandQueuePush(D_807FBB4C, D_807FBB4C->unk7C, D_807FBB4C->unk80 + 30.0f, D_807FBB4C->unk84, 0xFF, 0xFF, 0xFF, 0xFF, 0);
    if (!(D_807FBB40->unk60 & 0x10)) {
        sp67 = 0;
        currentActorClearFlag();
        D_807FDC98->unk46 |= 0x80;
        slotQueueSetDisplayMode(2, 0, 1);
        slotQueueSetDisplayMode(5, 0, 1);
        slotQueueSetDisplayMode(4, 0, 2);
        D_807FBB40->unk154 = 0;
        hudSpawnCountdownTimer(0xDC, 0x2A, D_807FDC9C->unkB);
        switch (sp6F) {
        case 14:
            csModelStateSetByte((randomNonNegative() >> 15) % 32767 % 4, 1, 1);
        case 0:
        case 4:
        case 13:
tail:
            sp68 = textTableGetString(0x1A, 2, 1);
            sp67 = 1;
            break;
        case 15:
            func_806C8E58(8);
            D_807FBB48->unk154 = 0xC;
            D_807FBB48->unk155[0] = 0;
            func_80614E78(D_807FBB48, 9);
            D_807FBB48->unkB8 = 0.0f;
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
            sp68 = textTableGetString(0x1A, 3, 1);
            sp67 = 1;
            break;
        case 9:
            ((Actor *)spawnNodeActivate((randomNonNegative() >> 15) % 32767 % 8 + 0x11, 0))->unk15F = 1;
            break;
        }
        if (sp67 != 0) {
            s->unk9 = gfxResourceCreate(1, sp68, 8, 0.0f, 0.0f, 0.0f);
            func_806FDAB8(s->unk9, 0.0f);
            s->unk4 = sp6E;
            s->unk2 = sp6E;
        }
    }
    if (D_807FBB40->unk154 == 0) {
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
                                sp68 = textTableGetString(0x1A, 0xF, 1);
                                sp60 = heapAlloc(strlen(sp68) + 5);
                                heapFreeDeferred(sp60);
                                _sprintf(sp60, "%d %s", s->unk4, sp68);
                            } else {
                                sp60 = textTableGetString(0x1A, 0x10, 1);
                            }
                            textSpawnMarkerChecked(0, 0, 0x8C, sp60, 0, 0x28, 8, 8);
                            a2v = 0;
                        }
                        break;
                    case 16:
                        if (s->unk2 == 0 && v3 != 0x28) {
                            textSpawnMarkerChecked(0, 0, 0x8C, textTableGetString(0x1A, 0x17, 1), 0, 0x28, 8, 8);
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
                                sp68 = textTableGetString(0x1A, 0x11, 1);
                                sp54 = heapAlloc(strlen(sp68) + 5);
                                _sprintf(sp54, "%d %s", sp6E - slotQueueGetValue(0xB, 0), sp68);
                            } else {
                                sp54 = textTableGetString(0x1A, 0x12, 1);
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
                                D_807FBB40->unk15F += 1;
                                if (D_807FBB40->unk15F >= 3) {
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
    if (D_807FBB40->unk154 == 0) {
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
                if (D_807FBB40->unk155[0] == 0) {
                    D_807FBB40->unk155[0] += 1;
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
        if (!(D_807FBB40->unk60 & 0x02000000)) {
            camResumePath(D_807FBB40);
            actorSetStateTwo((void *)D_807FBB40->unk11C);
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
    switch (D_807FBB40->unk154) {
    case 0:
        if ((sp6F == 1 || sp6F == 0 || sp6F == 2 || sp6F == 0x10) && D_807FBB4C->unk80 < 0.0f) {
            bonusEndLose(1, 1);
            return;
        }
        if (sp6F == 4 && D_807FBB4C->unk80 < -20.0f) {
            sfxPlayFromActorWithAltitudeCheck(D_807FBB40, 0x362, 0xFF, 0x7F, 0);
            bonusEndLose(0, 1);
            camStartPath(D_807FBB40, 1, 1);
            return;
        }
        if (D_807FBB4C->unk154 == 0x73) {
            if (sp6F == 1) {
                bonusEndLose(1, 0x13);
                return;
            }
            bonusEndLose(1, 1);
            return;
        }
        if (sp6F == 3 && D_807FBB4C->unk154 == 0x31) {
            bonusEndLose(1, 0x14);
            return;
        }
        pv = &sp6F;
        if (((Actor *)D_807FBB40->unk11C)->unk154 == 5) {
            if (*pv == 3) {
                bonusEndWin(1, 0x15);
                return;
            }
            bonusEndLose(1, 0x16);
            return;
        }
        break;
    case 1:
        ((Actor *)D_807FBB40->unk11C)->unk154 = 0;
        D_807FBB40->unk154 += 1;
        break;
    case 0x27:
        func_806FDAB8(s->unk9, 3.1415927f);
        s->unk4 -= 1;
        if (s->unk4 == 0) {
            bonusEndWin(1, 0xE);
            return;
        }
        D_807FBB40->unk154 = 0;
        break;
    case 0x28:
        s->unk2 = 1;
        D_807FBB40->unk154 = 0;
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
void sfxPlayOnFreeSlot(s32, s32, f32, f32, s32, s32);
extern s32 D_8076D1F8;
extern void *D_807FD580;

typedef struct LB3bInput {
    u8 pad0[0x1F0];
    u32 unk1F0;
} LB3bInput;

#define LD ((LB3bInput *)D_807FD580)

void func_80024E38(void) {
    LB3bSnd *snd;

    snd = *(LB3bSnd **)((u8 *)D_807FBB40 + 0x178);
    behaviourFrameBegin();
    if (!(D_807FBB40->unk60 & 0x10)) {
        snd->unk0 = 0x12C;
        snd->unkA = 0;
        snd->unk8 = 0;
        n_alSndpPlay(D_8076D1F8, 0x1E6, 0, 0x40, 1.0f, 0x80, &snd->unk4);
        hudSpawnCountdownTimer(0xDC, 0x2A, D_807FDC9C->unkB);
        spawnNodeActivateAndSetState(1, 0x40, 0x10);
        spawnNodeActivateAndSetState(2, 0x40, 0x10);
        spawnNodeActivateAndSetState(3, 0x40, 0x10);
        spawnNodeActivateAndSetState(4, 0x40, 0x10);
        D_807FBB40->unk154 = 0;
        D_807FBB40->unk155[0] = 0;
        camRequestPathLength();
        snd->unk18 = camStartPath(0, 0, 1);
    }
    switch (D_807FBB40->unk154) {
    case 0:
        if (snd->unk18 != 0) {
            snd->unk18--;
        } else {
            actorSetStateTwo((void *)D_807FBB40->unk11C);
            D_807FBB40->unk154 = 1;
        }
        break;
    case 1:
        if (((Actor *)D_807FBB40->unk11C)->unk154 == 5) {
            textSpawnMarkerChecked(0x81, 0, 0x78, textTableGetString(0x1A, 0x15, 1), 0, 0x28, 8, 8);
            func_80726EE0(0);
            sfxAllocateChannel(0x28, 1.0f);
            actorSpawnNodeEntryScaled(0x56, 588.0f, 240.0f, 582.0f, 0, 0, bonusGetSoundForMap(), 0);
            D_807FBB40->unk154 = 2;
        }
        if (D_807FBB4C->unk154 == 0x39) {
            func_805FF898();
            func_806C9974(0, 0x40);
            D_807FBB40->unk154 = 2;
        }
        break;
    }
    {
        s32 temp_v0_3 = snd->unk8 - 0x96;
        snd->unk0--;
        if (temp_v0_3 < 0x1F40) {
            snd->unk8 = 0x1F40;
        } else {
            snd->unk8 = temp_v0_3;
        }
    }
    {
        s32 temp_v1_2 = snd->unkA + 0x3E8;
        if (snd->unk8 < temp_v1_2) {
            snd->unkA = snd->unk8;
        } else {
            snd->unkA = temp_v1_2;
        }
    }
    n_alSndpPostEvent(snd->unk4, 8, snd->unkA);
    if (LD->unk1F0 & 0xC0000) {
        if (snd->unk0 < 0x129) {
            snd->unk0 = 0x12C;
            if (LD->unk1F0 & 0x40000) {
                if (((randomNonNegative() >> 15) % 1000) & 1) {
                    sfxPlayOnFreeSlot(0x1E7, 0x7FFF, 64.0f, 1.0f, 0x14, 0x80);
                } else {
                    sfxPlayOnFreeSlot(0x1EA, 0x7FFF, 64.0f, 1.0f, 0x14, 0x80);
                }
            } else {
                sfxPlayOnFreeSlot(0x1E8, 0x7FFF, 64.0f, 1.0f, 0x14, 0x80);
            }
        }
        {
            s32 temp_v0_5 = snd->unk8 + 0x4650;
            if (temp_v0_5 >= 0x8000) {
                snd->unk8 = 0x7FFF;
            } else {
                snd->unk8 = temp_v0_5;
            }
        }
        LD->unk1F0 &= ~0xC0000;
    }
    switch (snd->unk0) {
    case 0x0:
    case 0x14:
    case 0x28:
    case 0x3C:
    case 0x50:
        sfxPlayOnFreeSlot(0x1E9, 0x7FFF - snd->unk0 * 0x96, 64.0f, 1.0f, 0xA, 0x80);
        if (snd->unk0 == 0) {
            snd->unk0 = 0xC8;
        }
        break;
    }
}
