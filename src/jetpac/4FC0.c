#include "common.h"
typedef struct JetpacActor {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ u8 unk10;
    /* 0x11 */ u8 unk11;
    /* 0x12 */ u8 unk12;
    /* 0x13 */ u8 unk13;
    /* 0x14 */ s32 unk14;
    /* 0x18 */ s32 unk18;
    /* 0x1C */ s32 unk1C;
    /* 0x20 */ s32 unk20;
    /* 0x24 */ s32 unk24;
    /* 0x28 */ s32 unk28;
    /* 0x2C */ s32 unk2C;
    /* 0x30 */ s32 unk30;
    /* 0x34 */ s32 unk34;
    /* 0x38 */ s32 unk38;
    /* 0x3C */ s32 unk3C;
    /* 0x40 */ s32 unk40;
    /* 0x44 */ s32 unk44;
    /* 0x48 */ void (*unk48)(struct JetpacActor *);
    /* 0x4C */ void *unk4C;
} JetpacActor;
#define WRITE_GFX(pkt, _w0, _w1) { Gfx *_g = (Gfx *)(pkt); _g->words.w0 = (_w0); _g->words.w1 = (_w1); }
typedef struct {
    u8 pad[0x18];
} Struct_D_8002E800;
extern Struct_D_8002E800 D_8002E800[];
extern Struct_D_8002E800 D_8002E848[];
typedef struct {
    u8 pad[0x1C];
    s32 unk1C[2];
    u8 pad2[0x194 - 0x24];
} JetpacPlayer;

typedef struct {
    JetpacPlayer players[2];
    u8 pad[0x344 - (sizeof(JetpacPlayer) * 2)];
    s32 currentPlayer;
    u8 pad3[0x790 - 0x348];
    s32 unk790;
} JetpacGlobal;

extern JetpacGlobal D_8002EC30;
s32 func_80027250(f32, f32, f32, f32, f32, f32, f32, f32);
void func_8002976C(JetpacActor *actor);

extern void *D_8002E890;
extern void *D_8002E8C0;
extern void *D_8002E8D8;
extern void *D_8002E830;
extern void *D_8002E8A8;
extern s32 D_8002BA6C;
extern void *D_8002E878;
void func_80029F7C(JetpacActor *);
void func_8002A758(JetpacActor *);
void func_8002A67C(JetpacActor *);
void func_8002998C(JetpacActor *actor);
f32 func_8002A2DC(f32 arg0, f32 arg1);
f32 jetpacRandFloat(void);
void func_80029B90(JetpacActor *);
void func_80029C1C(JetpacActor *);
void func_8002A254(JetpacActor *arg0);
void func_8002A530(JetpacActor *actor);
f32 jetpacGetEntityCenterY(JetpacActor *);
extern f32 D_8002F054;
extern s32 D_8002F078;
void func_8002A374(JetpacActor *actor);
s32 func_80026FE0(void);
void func_80029204(JetpacActor *actor);
JetpacActor *jetpacFindFreeActor(void);
extern JetpacActor D_8002F1DC[];
extern JetpacActor D_8002E964;
extern JetpacActor D_8002E914;
JetpacActor *func_800292C4(void);
extern s32 D_8002E8F0;
void func_80029450(void);
s32 jetpacCheckLedgeCollision(f32, f32, f32, f32, s32);
s32 func_80029064(JetpacActor *);
void func_800294EC(JetpacActor *, s32);
void func_80024E70(s32 arg0);
void func_80025700(void *, s32, s32, void *, s32);
void func_80025A60(void *);
Gfx *func_806FD490(Gfx *, s32, s16, s16, s32);
void func_80029640(JetpacActor *actor, f32 a1, f32 a2);
void func_800298C8(JetpacActor *actor);
extern u8 D_80045BE0, D_80045BE1, D_80045BE2, D_80045BE3;
extern u8 D_8002E9C0, D_8002E9C4, D_8002E9C8, D_8002E9CC;

JetpacActor *jetpacFindFreeActor(void) {
    JetpacActor *actor = D_8002F1DC;
    s32 i = 0;

    do {
        if (actor->unk14 == 0) {
            return actor;
        }
        actor++;
    } while (++i < 6);
    return NULL;
}

#pragma GLOBAL_ASM("asm/jetpac/nonmatchings/4FC0/func_80029064.s")

void func_800291AC(JetpacActor *arg0) {
    arg0->unk14 = 4;
    arg0->unk2C = 0;
    arg0->unk38 = 0;
    arg0->unk30 = (s32)arg0->unk0 & 0xFFF8;
    arg0->unk34 = (s32)arg0->unk4 & 0xFFF8;
    func_80024E70(5);
}

void func_80029204(JetpacActor *arg0) {
    s32 temp_v0 = arg0->unk14;

    if (temp_v0 == 3) {
        func_80025700(arg0->unk4C, (s32)arg0->unk0, (s32)arg0->unk4, &arg0->unk10, arg0->unk18);
        return;
    }
    if (temp_v0 == 4) {
        func_80025A60(&arg0->unk30);
        if (arg0->unk38 < 7) {
            func_80025700(arg0->unk4C, (s32)arg0->unk0, (s32)arg0->unk4, &arg0->unk10, arg0->unk18);
        }
    }
}

JetpacActor *func_800292C4(void) {
    s32 pad;
    JetpacActor *actor;
    JetpacActor sp20;

    actor = jetpacFindFreeActor();
    sp20 = D_8002E914;
    if (actor == NULL) {
        return NULL;
    }
    *actor = sp20;
    actor->unk0 = 0.0f;
    actor->unk4 = (f32)((((s32)(jetpacRandFloat() * 15.0f) % 15) * 8) + 32);
    switch ((s32)(jetpacRandFloat() * 4.0f) % 4) {
    case 0:
        actor->unk10 = 0;
        break;
    case 1:
        actor->unk11 = 0;
        break;
    case 2:
        actor->unk10 = 0;
        actor->unk12 = 0;
        break;
    case 3:
        actor->unk11 = 0;
        actor->unk12 = 0;
        break;
    }
    return actor;
}

#pragma GLOBAL_ASM("asm/jetpac/nonmatchings/4FC0/func_80029450.s")

#pragma GLOBAL_ASM("asm/jetpac/nonmatchings/4FC0/func_800294EC.s")

#pragma GLOBAL_ASM("asm/jetpac/nonmatchings/4FC0/func_80029640.s")

void func_8002976C(JetpacActor *arg0) {
    switch (arg0->unk14) {
    case 3:
        if (jetpacCheckLedgeCollision((f32)arg0->unk1C + arg0->unk0 + arg0->unk8,
                          (f32)arg0->unk20 + arg0->unk4 + arg0->unkC,
                          (f32)arg0->unk24 + arg0->unk0 + arg0->unk8,
                          (f32)arg0->unk28 + arg0->unk4 + arg0->unkC, 1) >= 0) {
            func_800291AC(arg0);
        } else if (func_80029064(arg0) == 0) {
            arg0->unk0 += arg0->unk8;
            arg0->unk4 += arg0->unkC;
        }
        break;
    case 4:
        arg0->unk2C++;
        if (arg0->unk2C >= 15) {
            arg0->unk14 = 0;
        }
        break;
    }
}

void func_80029884(JetpacActor *actor) {
    actor->unk28 = 0xB;
    func_80029640(actor, 1.6f, 0.5f);
    actor->unk48 = func_800298C8;
}

void func_800298C8(JetpacActor *actor) {
    func_8002976C(actor);
    actor->unk4C = &D_8002E800[(s32)actor->unk0 % 2];
}

void func_8002992C(JetpacActor *arg0) {
    arg0->unk48 = func_8002998C;
    arg0->unk44 = 0x50;
    if (arg0->unk4 < 88.0f) {
        arg0->unk8 = -1.2f;
    } else {
        arg0->unk8 = 1.2f;
    }
    arg0->unkC = -0.8f;
    arg0->unk4C = &D_8002E830;
}

void func_8002998C(JetpacActor *arg0) {
    s32 res;

    switch (arg0->unk14) {
    case 3:
        res = jetpacCheckLedgeCollision((f32)arg0->unk1C + arg0->unk0 + arg0->unk8,
                            (f32)arg0->unk20 + arg0->unk4 + arg0->unkC,
                            (f32)arg0->unk24 + arg0->unk0 + arg0->unk8,
                            (f32)arg0->unk28 + arg0->unk4 + arg0->unkC, 1);
        if (res >= 0) {
            func_800294EC(arg0, res);
        }
        if (func_80029064(arg0) == 0) {
            if ((arg0->unk4 + arg0->unkC) < 24.0f) {
                arg0->unkC = -arg0->unkC;
            }
            arg0->unk4 += arg0->unkC;
            arg0->unk0 += arg0->unk8;
            if ((s32)arg0->unk0 & 2) {
                arg0->unk18 ^= 1;
            }
        }
        break;
    case 4:
        arg0->unk2C++;
        if (arg0->unk2C >= 15) {
            arg0->unk14 = 0;
        }
        break;
    }
}

void func_80029AF8(JetpacActor *arg0) {
    arg0->unk48 = func_80029C1C;
    arg0->unk44 = 0x28;
    if (arg0->unk4 < 88.0f) {
        arg0->unk8 = -1.2f;
    } else {
        arg0->unk8 = 1.2f;
    }
    func_80029B90(arg0);
    arg0->unk2C = (s32)((jetpacRandFloat() * 60.0f) + 10.0f);
}

void func_80029B90(JetpacActor *arg0) {
    if ((f64)arg0->unkC == 0.0) {
        if ((f64)jetpacRandFloat() < 0.5) {
            arg0->unkC = -0.6f;
            return;
        }
        arg0->unkC = 0.6f;
        return;
    }
    arg0->unkC = 0.0f;
}

void func_80029C1C(JetpacActor *arg0) {
    s32 res;

    switch (arg0->unk14) {
    case 3:
        if (--arg0->unk2C == 0) {
            func_80029B90(arg0);
            arg0->unk2C = (s32)((jetpacRandFloat() * 60.0f) + 10.0f);
        }
        res = jetpacCheckLedgeCollision((f32)arg0->unk1C + arg0->unk0 + arg0->unk8,
                            (f32)arg0->unk20 + arg0->unk4 + arg0->unkC,
                            (f32)arg0->unk24 + arg0->unk0 + arg0->unk8,
                            (f32)arg0->unk28 + arg0->unk4 + arg0->unkC, 1);
        if (res >= 0) {
            func_800294EC(arg0, res);
            if (arg0->unk2C < 10) {
                arg0->unk2C = 10;
            }
        }
        if (func_80029064(arg0) == 0) {
            if ((arg0->unk4 + arg0->unkC) < 24.0f) {
                arg0->unkC = -arg0->unkC;
            }
            arg0->unk4 += arg0->unkC;
            arg0->unk0 += arg0->unk8;
            arg0->unk4C = &D_8002E848[(s32)(arg0->unk0 / 4) % 2];
        }
        break;
    case 4:
        arg0->unk2C++;
        if (arg0->unk2C >= 15) {
            arg0->unk14 = 0;
        }
        break;
    }
}

void func_80029E0C(JetpacActor *arg0) {
    arg0->unk48 = func_80029F7C;
    arg0->unk44 = 0x37;
    arg0->unk2C = (s32)((jetpacRandFloat() * 60.0f) + 10.0f);
    arg0->unk40 = (u32)((jetpacRandFloat() * 180.0f) + 10.0f);
    arg0->unk28 = 8;
    if (arg0->unk4 < 88.0f) {
        arg0->unk18 = 0;
    } else {
        arg0->unk18 = 1;
    }
    arg0->unk8 = 0.0f;
    if (D_8002BA6C != 0) {
        arg0->unkC = -0.8f;
    } else {
        arg0->unkC = 0.8f;
    }
    arg0->unk4C = &D_8002E878;
}

#if 0
// ~2 insns off: switch delay slot register assignment and players[currentPlayer].unk1C[1] indexing
void func_80029F7C(JetpacActor *arg0) {
    s32 var_v1 = arg0->unk14;

    switch (var_v1) {
    case 3:
        if (arg0->unk2C == 0) {
            if (jetpacCheckLedgeCollision((f32)arg0->unk1C + arg0->unk0 + arg0->unk8,
                              (f32)arg0->unk20 + arg0->unk4 + arg0->unkC,
                              (f32)arg0->unk24 + arg0->unk0 + arg0->unk8,
                              (f32)arg0->unk28 + arg0->unk4 + arg0->unkC, 1) >= 0) {
                func_800291AC(arg0);
            } else {
                arg0->unk40--;
            }
            if (arg0->unk40 == 0) {
                func_800291AC(arg0);
            }
            var_v1 = arg0->unk14;
        } else if (D_8002BA6C != 0 && arg0->unk4 < 32.0f) {
            func_800291AC(arg0);
            var_v1 = arg0->unk14;
        }

        if (var_v1 == 3) {
            func_80029064(arg0);
            var_v1 = arg0->unk14;
        }
        if (var_v1 == 4) {
            D_8002EC30.players[D_8002EC30.currentPlayer].unk1C[1] += arg0->unk44;
            return;
        }

        if (arg0->unk2C != 0) {
            arg0->unk2C--;
            if (D_8002BA6C != 0) {
                arg0->unkC = -0.8f;
            } else {
                arg0->unkC = 0.8f;
            }
            if (arg0->unk2C == 0) {
                if (arg0->unk18 != 0) {
                    arg0->unk8 = -1.6f;
                } else {
                    arg0->unk8 = 1.6f;
                }
                arg0->unk10 = 0xFF;
                arg0->unk11 = 0xFF;
                arg0->unk12 = 0xFF;
            }
        }

        if (arg0->unk2C == 0 && (D_8002EC30.unk790 & 2)) {
            if (jetpacGetEntityCenterY(arg0) < D_8002F054 + (f32)D_8002F078) {
                arg0->unkC = 0.8f;
            } else {
                arg0->unkC = -0.8f;
            }
        }
        arg0->unk0 += arg0->unk8;
        arg0->unk4 += arg0->unkC;
        return;
    case 4:
        arg0->unk2C++;
        if (arg0->unk2C >= 15) {
            arg0->unk14 = 0;
        }
        return;
    }
}
#endif
#pragma GLOBAL_ASM("asm/jetpac/nonmatchings/4FC0/func_80029F7C.s")

void func_8002A254(JetpacActor *arg0) {
    arg0->unk48 = func_8002A530;
    arg0->unk44 = 0x32;
    if (arg0->unk4 < 88.0f) {
        arg0->unk18 = 0;
    } else {
        arg0->unk18 = 1;
    }
    func_8002A374(arg0);
}

void func_8002A2AC(JetpacActor *arg0) {
    arg0->unk28 = 8;
    arg0->unk4C = &D_8002E890;
    func_8002A254(arg0);
}

#pragma GLOBAL_ASM("asm/jetpac/nonmatchings/4FC0/func_8002A2DC.s")

#pragma GLOBAL_ASM("asm/jetpac/nonmatchings/4FC0/func_8002A374.s")

void func_8002A530(JetpacActor *arg0) {
    s32 res;

    switch (arg0->unk14) {
    case 3:
        func_8002A374(arg0);
        res = jetpacCheckLedgeCollision((f32)arg0->unk1C + arg0->unk0 + arg0->unk8,
                            (f32)arg0->unk20 + arg0->unk4 + arg0->unkC,
                            (f32)arg0->unk24 + arg0->unk0 + arg0->unk8,
                            (f32)arg0->unk28 + arg0->unk4 + arg0->unkC, 1);
        if (res >= 0) {
            func_800294EC(arg0, res);
        }
        if (func_80029064(arg0) == 0) {
            if ((arg0->unk4 + arg0->unkC) < 24.0f) {
                arg0->unkC = -arg0->unkC;
            }
            arg0->unk4 += arg0->unkC;
            arg0->unk0 += arg0->unk8;
        }
        break;
    case 4:
        arg0->unk2C++;
        if (arg0->unk2C >= 15) {
            arg0->unk14 = 0;
        }
        break;
    }
}

#pragma GLOBAL_ASM("asm/jetpac/nonmatchings/4FC0/func_8002A67C.s")

void func_8002A6C0(JetpacActor *arg0) {
    arg0->unk48 = func_8002A758;
    arg0->unk44 = 0x3C;
    arg0->unk2C = (s32)(jetpacRandFloat() * 16.0f);
    if (arg0->unk4 < 88.0f) {
        arg0->unk8 = -1.2f;
    } else {
        arg0->unk8 = 1.2f;
    }
    func_8002A67C(arg0);
    arg0->unk4C = &D_8002E8A8;
}

#pragma GLOBAL_ASM("asm/jetpac/nonmatchings/4FC0/func_8002A758.s")

void func_8002A8F0(JetpacActor *actor) {
    actor->unk28 = 0xE;
    actor->unk4C = &D_8002E8C0;
    func_80029640(actor, 1.2f, 0.3f);
    actor->unk48 = func_8002976C;
}

void func_8002A944(JetpacActor *arg0) {
    arg0->unk28 = 0xE;
    arg0->unk4C = &D_8002E8D8;
    func_8002A254(arg0);
}

s32 func_8002A974(f32 x1, f32 y1, f32 x2, f32 y2) {
    JetpacActor *actor = D_8002F1DC;
    s32 *playerData;
    s32 i;

    for (i = 0; i < 6; i++, actor++) {
        if (actor->unk14 == 3) {
            if (func_80027250(x1, y1, x2, y2,
                              actor->unk0 + (f32)actor->unk1C,
                              actor->unk4 + (f32)actor->unk20,
                              actor->unk0 + (f32)actor->unk24,
                              actor->unk4 + (f32)actor->unk28)) {
                playerData = D_8002EC30.players[D_8002EC30.currentPlayer].unk1C;
                func_800291AC(actor);
                playerData[1] += actor->unk44;
                return 1;
            }
        }
    }
    return 0;
}

void func_8002AAD4(void) {
    s32 i;
    JetpacActor sp24;
    JetpacActor *actor;

    sp24 = D_8002E964;
    actor = D_8002F1DC;
    i = 0;
    do {
        *actor++ = sp24;
        i++;
    } while (i < 6);

    for (i = 0; i < 3; i++) {
        func_80029450();
    }
    D_8002E8F0 = (s32)(jetpacRandFloat() * 180.0f);
}

#pragma GLOBAL_ASM("asm/jetpac/nonmatchings/4FC0/func_8002ABDC.s")

void func_8002AD8C(void) {
    JetpacActor *actor = D_8002F1DC;
    s32 i;

    if (func_80026FE0() == 0) {
        for (i = 0; i < 6; i++, actor++) {
            if (actor->unk14 >= 2 && actor->unk4C != NULL) {
                func_80029204(actor);
            }
        }
    }
}

void func_8002AE00(Gfx **arg0) {
    Gfx *g = *arg0;
    WRITE_GFX(g++, 0xE7000000, 0);
    WRITE_GFX(g++, 0xE3000A01, 0);
    WRITE_GFX(g++, 0xD9000000, 0);
    WRITE_GFX(g++, 0xD9FFFFFF, 0x00200004);
    WRITE_GFX(g++, 0xFC30FE61, 0x55FEF379);
    WRITE_GFX(g++, 0xE200001C, 0x0F0A4000);
    *arg0 = g;
}

void func_8002AE94(s8 arg0, s8 arg1, s8 arg2, s8 arg3) {
    D_80045BE0 = arg0;
    D_80045BE1 = arg1;
    D_80045BE2 = arg2;
    D_80045BE3 = arg3;
}

void func_8002AEC8(s8 arg0, s8 arg1, s8 arg2, s8 arg3) {
    D_8002E9C0 = arg0;
    D_8002E9C4 = arg1;
    D_8002E9C8 = arg2;
    D_8002E9CC = arg3;
}

void func_8002AEFC(Gfx **arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    Gfx *g = *arg0;

    if (arg4 != 0) {
        gDPSetPrimColor(g++, 0, 0, D_8002E9C0, D_8002E9C4, D_8002E9C8, D_8002E9CC);
        gDPSetEnvColor(g++, D_80045BE0, D_80045BE1, D_80045BE2, D_80045BE3);
    } else {
        gDPSetPrimColor(g++, 0, 0, D_80045BE0, D_80045BE1, D_80045BE2, D_80045BE3);
        gDPSetEnvColor(g++, D_8002E9C0, D_8002E9C4, D_8002E9C8, D_8002E9CC);
    }
    *arg0 = func_806FD490(g, 4, (s16)arg2, (s16)arg3, arg1);
}
