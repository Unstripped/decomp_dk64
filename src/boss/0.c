#include "common.h"

typedef struct BossByteTable6 {
    u8 bytes[6];
} BossByteTable6;

typedef struct BossActorPos {
    u8 pad0[0x7C];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
} BossActorPos;

struct BossA_Struct_807FBB40;
extern struct BossA_Struct_807FBB40 *D_807FBB40;
extern BossByteTable6 D_8003598C;
extern u8 D_8071E864;
extern u8 D_8071FFA0;

void func_8067E2E4(void *, s32, f32);
void func_80714950();
void func_8071498C(void *);
void func_80714998(s32);
void func_807149B8(s32);
void func_807149C8(s32, s32, s32, s32);
void func_80714CC0(void *, f32, f32, f32, f32);

void func_80024000(void) {
    BossByteTable6 sp48;
    s16 i;

    for (i = 0; i < 6; i++) {
        sp48 = D_8003598C;
        func_8067E2E4(D_807FBB40, sp48.bytes[i], 3.0f);
    }

    for (i = 0; i < 12; i++) {
        func_8071498C((void *)(s32)&D_8071E864);
        func_80714950(i);
        func_807149B8(1);
        func_807149C8(0x8C, 0x8C, 0x8C, 0xFF);
        func_80714998(3);
        func_80714CC0(&D_8071FFA0, 2.5f, ((BossActorPos *)D_807FBB40)->unk7C, ((BossActorPos *)D_807FBB40)->unk80 + 40.0f, ((BossActorPos *)D_807FBB40)->unk84);
    }
}

typedef struct BossA_Struct_80024524_Entry {
    u8 pad0;
    u8 unk1;
    s16 unk2;
    u8 pad4[4];
} BossA_Struct_80024524_Entry;

typedef struct BossA_Struct_8002413C_1 {
    u8 id;
    u8 unk1;
    u8 pad2[2];
    f32 x;
    f32 y;
    f32 z;
} BossA_Struct_8002413C_1;

typedef struct BossA_Struct_8002413C_3 {
    s8 unk0;
    u8 id;
    s16 unk2;
    s16 unk4;
    s16 unk6;
} BossA_Struct_8002413C_3;

typedef struct BossA_Struct_8002413C_Template {
    s8 x;
    s8 y;
    s8 z;
    u8 pad3;
    f32 rotX;
    f32 rotY;
    f32 rotZ;
} BossA_Struct_8002413C_Template;

typedef struct BossA_Struct_807FBB40_Sub {
    u8 pad0[0x1C];
    union {
        BossA_Struct_80024524_Entry *entries;
        BossA_Struct_8002413C_3 *arr3;
    } u1C;
    BossA_Struct_8002413C_1 *arr2;
    BossA_Struct_8002413C_1 *arr1;
    u8 pad28[0x64 - 0x28];
    u16 unk64;
} BossA_Struct_807FBB40_Sub;

typedef struct BossA_Struct_807FBB40 {
    u8 pad0[4];
    BossA_Struct_807FBB40_Sub *sub;
    u8 pad8[0xE6 - 8];
    s16 unkE6;
    u8 padE8[0x146 - 0xE8];
    s16 unk146;
} BossA_Struct_807FBB40;

extern s32 D_8076A0A8;
extern BossA_Struct_807FBB40 *D_807FBB40;
extern u8 D_800358D8[5];
extern BossA_Struct_8002413C_Template D_800358E0[][5];
extern u8 D_80035994[8];

s32 flagGet(s32, s32);
void func_80724D28(s32, s32);
void func_80724DB0(s32, s32);
void func_80724CA4(s32, s32);

void func_8002413C(void) {
    s32 pad[4];
    u8 mode;
    s16 i;
    BossA_Struct_807FBB40_Sub *sub;
    BossA_Struct_8002413C_1 *v0;
    BossA_Struct_8002413C_1 *a0;
    BossA_Struct_8002413C_3 *a1;
    BossA_Struct_8002413C_Template *t;

    if (D_8076A0A8 == 8) {
        mode = 0;
    } else {
        mode = 1;
    }
    if (mode == 0) {
        if (flagGet(0x68, 2) != 0) {
            mode = 1;
            D_807FBB40->unk146 = 3;
        }
    }
    func_80724D28(1, 0xD);
    func_80724DB0(1, 5);
    func_80724CA4(1, 5);

    sub = D_807FBB40->sub;
    t = D_800358E0[mode];
    v0 = sub->arr1;
    a0 = sub->arr2;
    a1 = sub->u1C.arr3;

    for (i = 0; i < 5; i++) {
        v0->id = D_800358D8[i];
        v0->unk1 = 0xFF;
        v0->x = t[i].x;
        v0->y = t[i].y;
        v0->z = t[i].z;

        a0->id = D_800358D8[i];
        a0->unk1 = 0xFF;
        a0->x = t[i].rotX;
        a0->y = t[i].rotY;
        a0->z = t[i].rotZ;

        a1->unk0 = -0x80;
        a1->id = D_800358D8[i];
        a1->unk2 = 0;
        a1->unk4 = 0;
        a1->unk6 = 0;

        v0++;
        a0++;
        a1++;
    }

    for (i = 0; i < 8; i++) {
        v0->id = D_80035994[i];
        v0->unk1 = 0xFF;
        v0->x = 0.0f;
        v0->y = 0.0f;
        v0->z = 0.0f;
        v0++;
    }
}

typedef struct Boss2A_Struct_807FBB40_4300 {
    u8 pad0[4];
    BossA_Struct_807FBB40_Sub *sub;
    u8 pad8[0x7C - 8];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
} Boss2A_Struct_807FBB40_4300;

typedef struct Boss2A_Struct_807FDC90_4300 {
    u8 pad0[0x2C];
    s16 unk2C;
} Boss2A_Struct_807FDC90_4300;
struct BossA_Struct_80024EAC_DC90;
extern struct BossA_Struct_80024EAC_DC90 *D_807FDC90;
s32 func_806086CC(f32, f32, f32, s32, s32, s32, s32, s32, f32, s32);
f32 func_80612794(s16);
f32 func_80612790(s16);

void func_80024300(void) {
    s16 var_s2;
    BossA_Struct_8002413C_1 *var_s0;
    s32 var_a3;
    s32 var_v1;
    s16 temp_lo;

    var_s0 = D_807FBB40->sub->arr1;
    var_a3 = 0;
    var_v1 = 0xFF;
    switch (((Boss2A_Struct_807FDC90_4300 *)D_807FDC90)->unk2C) {
    case 19:
        var_a3 = 0x22;
        break;
    case 17:
        var_a3 = 0xF6;
        break;
    case 15:
        var_a3 = 0x17;
        break;
    case 13:
        var_a3 = 0xED;
        break;
    case 11:
        var_a3 = 0x18;
        break;
    case 9:
        var_a3 = 0x22;
        var_v1 = 0xC8;
        break;
    case 7:
        var_a3 = 0xED;
        var_v1 = 0x82;
        break;
    case 5:
        var_a3 = 0x18;
        var_v1 = 0x46;
        break;
    case 3:
        var_a3 = 0x3C;
        break;
    }

    if (var_a3 != 0) {
        func_806086CC(((Boss2A_Struct_807FBB40_4300 *)D_807FBB40)->unk7C,
                      ((Boss2A_Struct_807FBB40_4300 *)D_807FBB40)->unk80,
                      ((Boss2A_Struct_807FBB40_4300 *)D_807FBB40)->unk84,
                      var_a3, var_v1, 0x7F, 1, 0x1E, 0.3f, 0);
    }

    var_s2 = 0;
    D_807FBB40->sub->arr1[5].x = 99999.0f;
    do {
        if (var_s0->y >= 1800.0f) {
            var_s0->x = 99999.0f;
            var_s0->y = 99999.0f;
            var_s0->z = 99999.0f;
            var_s0++;
        } else {
            temp_lo = var_s2 * 400;
            var_s0->x += 200.0f * func_80612794(temp_lo);
            var_s0->z += 200.0f * func_80612790(temp_lo);
            var_s0->y += 100.0f;
            var_s0++;
        }
        var_s2++;
    } while (var_s2 < 13);
}

void func_8002450C(u8 *arg0, u8 arg1, u8 arg2) {
    arg0[arg1 + 6] = arg2;
}

void func_80024524(u8 arg0, s16 arg1) {
    BossA_Struct_80024524_Entry *entry = &D_807FBB40->sub->u1C.entries[arg0];
    if (arg0 == 3) {
        entry->unk1 = 0x2F;
    }
    entry->unk2 = arg1;
}


typedef struct BossPieceAnim {
    u8 pad0;
    u8 cnt[5];
    u8 state[5];
    u8 pad0B;
    s16 ang[5];
    u8 pad16[2];
    f32 f1[5];
    f32 f2[5];
} BossPieceAnim;

void func_8068A764(void *, u8);
void func_8068A784(void *, u8);
void sfxPlayActorSound(void *, s32, s32, s32, s32, s32, f32, s32);
void sfxStopSlotSound();
void actorScriptStart(void *, s32);

typedef struct BossActorState {
    u8 pad0[0x154];
    u8 unk154;
} BossActorState;

#define A154 (((BossActorState *)D_807FBB40)->unk154)
#define BB ((Boss2A_Struct_807FBB40_4300 *)D_807FBB40)
#define OBJ ((BossPieceAnim *)arg0)

u8 bossPieceStep(u8 *arg0, u8 arg1, f32 arg2, f32 arg3, f32 arg4) {
    u8 ret;
    BossA_Struct_8002413C_1 *p1;
    BossA_Struct_8002413C_1 *p2;
    BossA_Struct_807FBB40 *sp3C;

    sp3C = D_807FBB40;
    ret = 0;
    p1 = &sp3C->sub->arr1[arg1];
    p2 = &sp3C->sub->arr2[arg1];
    switch (OBJ->state[arg1]) {
    case 5:
        OBJ->f1[arg1] = 30.0f;
        OBJ->ang[arg1] = arg1 * 0x800 + 0x400;
        OBJ->f2[arg1] = 100.0f;
        OBJ->state[arg1] = 6;
    case 6:
        p1->x += OBJ->f1[arg1] * func_80612794(OBJ->ang[arg1]);
        p1->z += OBJ->f1[arg1] * func_80612790(OBJ->ang[arg1]);
        p1->y += OBJ->f2[arg1];
        OBJ->f2[arg1] -= 10.0f;
        if (OBJ->f2[arg1] < -200.0f) {
            OBJ->f2[arg1] = -200.0f;
        }
        if (p1->y < -300.0f) {
            p1->y = -300.0f;
            if (-50.0f < OBJ->f2[arg1]) {
                func_8067E2E4(D_807FBB40, (u8)(arg1 + 1), 1.5f);
                func_8068A784(D_807FBB40, arg1);
                OBJ->state[arg1] = 0;
                ret = 1;
                break;
            }
            if (!arg1) {
                func_806086CC(BB->unk7C, BB->unk80, BB->unk84, 0x36, (u32)(120.0f - OBJ->f2[arg1] > 255.0f ? 255.0f : 120.0f - OBJ->f2[arg1]), 0x7F, 0x28, 0, 0.3f, 0);
            }
            OBJ->f2[arg1] *= -0.5;
        }
        break;
    case 1:
        switch (arg1) {
        case 0:
            sfxPlayActorSound(D_807FBB40, 0x127, 0, 1, 1, 0xFF, 1.0f, 0);
            break;
        case 2:
            sfxPlayActorSound(D_807FBB40, 0x127, 0, 1, 1, 0xFF, 1.1f, 0);
            break;
        case 4:
            sfxPlayActorSound(D_807FBB40, 0x127, 0, 1, 1, 0xFF, 1.3f, 0);
            break;
        }
        func_8068A764(D_807FBB40, arg1);
        OBJ->state[arg1] = 2;
        OBJ->cnt[arg1] = 0;
    case 2:
        if ((f32)++OBJ->cnt[arg1] < arg2) {
            f32 t = (f32)OBJ->cnt[arg1] / arg2;
            p1->x = D_800358E0[0][arg1].x + (-D_800358E0[0][arg1].x) * t;
            p1->y = D_800358E0[0][arg1].y + (-D_800358E0[0][arg1].y) * t;
            p1->z = D_800358E0[0][arg1].z + (-D_800358E0[0][arg1].z) * t;
        } else if (arg2 == (f32)OBJ->cnt[arg1]) {
            switch (arg1) {
            case 0:
            case 2:
            case 4:
                sfxStopSlotSound(D_807FBB40, 1);
                break;
            }
        } else if (arg3 == (f32)OBJ->cnt[arg1]) {
            switch (A154) {
            case 0x27:
                actorScriptStart(D_807FBB40, 0x264);
                break;
            case 0x2E:
                actorScriptStart(D_807FBB40, 0x265);
                break;
            default:
                actorScriptStart(D_807FBB40, 0x266);
                break;
            }
        } else if (arg3 + 1.0f == (f32)OBJ->cnt[arg1]) {
            p2->x = 1.0f;
            p2->y = 1.0f;
            p2->z = 1.0f;
        } else if (arg4 < (f32)OBJ->cnt[arg1]) {
            ret = 1;
            OBJ->state[arg1] = 0;
        }
        break;
    case 3:
        switch (arg1) {
        case 0:
            sfxPlayActorSound(D_807FBB40, 0x127, 0, 1, 1, 0xFF, 1.0f, 0);
            break;
        case 2:
            sfxPlayActorSound(D_807FBB40, 0x127, 0, 1, 1, 0xFF, 1.1f, 0);
            break;
        }
        OBJ->state[arg1] = 4;
        OBJ->cnt[arg1] = arg4;
    case 4:
        if (arg2 < (f32)--OBJ->cnt[arg1]) {
            p2->x = p2->x + (D_800358E0[0][arg1].rotX - p2->x) * 0.08;
            p2->y = p2->y + (D_800358E0[0][arg1].rotY - p2->y) * 0.08;
            p2->z = p2->z + (D_800358E0[0][arg1].rotZ - p2->z) * 0.09;
        } else if (OBJ->cnt[arg1] > 0) {
            f32 t = (f32)OBJ->cnt[arg1] / arg2;
            p1->x = D_800358E0[0][arg1].x + (-D_800358E0[0][arg1].x) * t;
            p1->y = D_800358E0[0][arg1].y + (-D_800358E0[0][arg1].y) * t;
            p1->z = D_800358E0[0][arg1].z + (-D_800358E0[0][arg1].z) * t;
        } else {
            func_8068A784(D_807FBB40, arg1);
            OBJ->state[arg1] = 0;
            if (arg1 == 0 || arg1 == 2) {
                sfxStopSlotSound(D_807FBB40, 1);
            }
            ret = 1;
        }
        break;
    }
    return ret;
}


typedef struct BossA_Struct_80024EAC_DC90 {
    u8 pad0[8];
    s16 unk8;
} BossA_Struct_80024EAC_DC90;

typedef struct BossA_Struct_80024EAC_DC94 {
    u8 pad0[0x7C];
    f32 unk7C;
    u8 pad80[4];
    f32 unk84;
} BossA_Struct_80024EAC_DC94;

extern BossA_Struct_80024EAC_DC90 *D_807FDC90;
extern BossA_Struct_80024EAC_DC94 *D_807FDC94;

void func_80614D00(void *, f32, f32);
s32 func_806CC10C(s16, s16);
void actorMoveWithinZone(s32, f32, f32, s32, f32);

void func_80024EAC(void) {
    s32 res;
    u16 sp2A;

    sp2A = D_807FBB40->sub->unk64;
    func_806CC10C(D_807FDC90->unk8, D_807FBB40->unkE6);
    actorMoveWithinZone(0x45, D_807FDC94->unk7C, D_807FDC94->unk84, 0x16, 0.0f);
    res = func_806CC10C(D_807FDC90->unk8, D_807FBB40->unkE6);
    if (res > 0) {
        if (sp2A != 0x260) {
            actorScriptStart(D_807FBB40, 0x260);
        }
    } else if (res < 0) {
        if (sp2A != 0x25F) {
            actorScriptStart(D_807FBB40, 0x25F);
        }
    } else if (sp2A != 0x25A) {
        actorScriptStart(D_807FBB40, 0x25A);
        func_80614D00(D_807FBB40, 1.0f, 0.0f);
    }
}

typedef struct Boss2A_Struct_807FBB40_4FA8 {
    u8 pad0[0x154];
    u8 unk154;
    u8 unk155;
} Boss2A_Struct_807FBB40_4FA8;

u8 bossPieceStep(u8 *, u8, f32, f32, f32);
void animSetLoopLimit(void *, s32, s32);

void func_80024FA8(void *arg0, u8 *arg1, s32 arg2, u8 *arg3) {
    u8 i;
    u8 res;

    i = 0;
    res = 0;
    switch (((Boss2A_Struct_807FBB40_4FA8 *)D_807FBB40)->unk155) {
    case 2:
        if (*arg3 != 0xFF) {
            do {
                func_8002450C(arg1, arg3[i++], 1);
            } while (arg3[i] != 0xFF);
        }
        ((Boss2A_Struct_807FBB40_4FA8 *)D_807FBB40)->unk155 = 3;
        break;
    case 3:
        if (*arg3 != 0xFF) {
            do {
                if (((Boss2A_Struct_807FBB40_4FA8 *)D_807FBB40)->unk154 == 0x27 ||
                    ((Boss2A_Struct_807FBB40_4FA8 *)D_807FBB40)->unk154 == 0x2E) {
                    res = bossPieceStep(arg1, arg3[i++], 50.0f, 70.0f, 90.0f);
                } else {
                    res = bossPieceStep(arg1, arg3[i++], 10.0f, 15.0f, 50.0f);
                }
            } while (arg3[i] != 0xFF);
        }
        if (res != 0) {
            ((Boss2A_Struct_807FBB40_4FA8 *)D_807FBB40)->unk155 = 4;
            animSetLoopLimit(D_807FBB40, 1, 1);
        }
        break;
    }
}

void bossPieceListStep(void *arg0, u8 *arg1, s32 arg2, u8 *arg3) {
    u8 i;
    u8 res;

    i = 0;
    res = 0;
    switch (((Boss2A_Struct_807FBB40_4FA8 *)D_807FBB40)->unk155) {
    case 2:
        if (*arg3 != 0xFF) {
            do {
                func_8002450C(arg1, arg3[i++], 3);
            } while (arg3[i] != 0xFF);
        }
        ((Boss2A_Struct_807FBB40_4FA8 *)D_807FBB40)->unk155 = 3;
        break;
    case 3:
        if (*arg3 != 0xFF) {
            do {
                res = bossPieceStep(arg1, arg3[i++], 10.0f, 20.0f, 30.0f);
            } while (arg3[i] != 0xFF);
        }
        if (res != 0) {
            ((Boss2A_Struct_807FBB40_4FA8 *)D_807FBB40)->unk155 = 4;
            animSetLoopLimit(D_807FBB40, 1, 1);
        }
        break;
    }
}

void actorClearNodeFlag(void *, s32);
void actorSetNodeFlag(void *, s32);

void func_8002531C(void) {
    actorClearNodeFlag(D_807FBB40, 3);
    actorClearNodeFlag(D_807FBB40, 4);
    actorClearNodeFlag(D_807FBB40, 5);
}

void func_80025364(void) {
    actorSetNodeFlag(D_807FBB40, 3);
    actorSetNodeFlag(D_807FBB40, 4);
    actorSetNodeFlag(D_807FBB40, 5);
}

typedef struct BossActorUnkC0 {
    u8 pad0[0xC0];
    f32 unkC0;
} BossActorUnkC0;

extern u8 D_8071AF30;
extern u8 D_80720120;

void func_807149A8(s32);
void func_80714C08(void *, f32, void *, s32, s32);

void func_800253AC(void) {
    f32 val;
    s32 p;
    f64 dval;

    dval = (0.0 < (f64)((BossActorUnkC0 *)D_807FBB40)->unkC0) ? (f64)((BossActorUnkC0 *)D_807FBB40)->unkC0 : 0.0;
    val = (f32)((f32)((dval / 150.0) * 0.12) + 0.3) * 4.0f;
    p = (s32)&D_8071AF30;
    func_807149B8(1);
    func_8071498C((void *)p);
    func_807149A8(1000);
    func_80714950(D_807FBB40);
    func_80714C08(&D_80720120, val, D_807FBB40, 3, 0);
    func_807149B8(1);
    func_8071498C((void *)p);
    func_807149A8(1000);
    func_80714950(D_807FBB40);
    func_80714C08(&D_80720120, val, D_807FBB40, 4, 0);
}

typedef struct Boss3B_178 {
    u8 pad0[0x12];
    u16 unk12;
    u8 unk14;
    u8 unk15;
    u8 pad16[2];
    u8 unk18;
    u8 unk19;
} Boss3B_178;
typedef struct Boss3B_Sp78 {
    u8 unk0;
    u8 pad1[0xF];
    s16 unk10;
    s16 unk12;
} Boss3B_Sp78;
typedef struct Boss3B_Sub4 {
    u8 pad0[0x10];
    s16 unk10;
} Boss3B_Sub4;
typedef struct Boss3B_Unk4 {
    Boss3B_Sub4 *unk0;
    u8 pad4[0x34 - 4];
    f32 unk34;
    f32 unk38;
} Boss3B_Unk4;
typedef struct Boss3B_Actor {
    u8 pad0[4];
    Boss3B_Unk4 *unk4;
    u8 pad8[0x60 - 8];
    u32 unk60;
    u8 pad64[0x6A - 0x64];
    u16 unk6A;
    u8 pad6C[4];
    s16 unk70;
    s16 unk72;
    u8 pad74[8];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
    u8 pad88[0xB4 - 0x88];
    f32 unkB4;
    f32 unkB8;
    u8 padBC[4];
    f32 unkC0;
    f32 unkC4;
    f32 unkC8;
    u8 padCC[0xE6 - 0xCC];
    s16 unkE6;
    u8 padE8[0xEE - 0xE8];
    s16 unkEE;
    u8 padF0[0x12A - 0xF0];
    s16 unk12A;
    u8 pad12C[0x138 - 0x12C];
    s32 unk138;
    u8 pad13C[8];
    u8 unk144;
    u8 pad145;
    s16 unk146;
    u8 pad148[0xC];
    u8 unk154;
    u8 unk155;
    u8 pad156[0x16A - 0x156];
    u8 unk16A;
    u8 unk16B;
    u8 unk16C;
    u8 pad16D[0x178 - 0x16D];
    Boss3B_178 *unk178;
    Boss3B_Sp78 *unk17C;
} Boss3B_Actor;
typedef struct Boss3B_DC90 {
    u8 pad0[0xA];
    s16 unkA;
    u8 padC[2];
    s16 unkE;
    u8 pad10[0x28 - 0x10];
    u8 unk28[4];
    s16 unk2C;
    s16 unk2E;
} Boss3B_DC90;
typedef struct Boss3B_DC94 {
    u8 pad0[0x7C];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
} Boss3B_DC94;
typedef struct Boss3B_DC98 {
    u8 pad0[0x2C];
    f32 unk2C;
    f32 unk30;
    u8 pad34[4];
    f32 unk38;
} Boss3B_DC98;
typedef struct Boss3B_DCA0_Sub {
    u8 pad0[0x28];
    s16 unk28;
    s16 unk2A;
    s16 unk2C;
    u8 pad2E[0x82 - 0x2E];
    s16 unk82;
    u8 pad84[2];
    s16 unk86;
} Boss3B_DCA0_Sub;
typedef struct Boss3B_DCA0 {
    u8 pad0[0x14];
    Boss3B_DCA0_Sub *unk14;
} Boss3B_DCA0;

extern Boss3B_Actor *D_807FBB44;
extern Boss3B_Actor *D_807FBB4C;
extern u8 D_807FBB70[];
extern Boss3B_DC98 *D_807FDC98;
extern Boss3B_DCA0 *D_807FDCA0;

extern u8 *D_800358B0[][5];
extern u8 D_80035980;
extern u8 D_80035984;
extern u8 D_80035988;
extern u8 D_80035CB8;
extern u8 D_80035CC0[];
extern s32 D_80627F04;
void effectUpdateAndDispatch(void);
void effectNodeSetSubVal(s32, u8);
extern u8 D_807444EC;
extern s8 D_80750190;
extern s16 D_807502D8;
extern f32 D_807502F4;
extern s32 D_8076A064;
extern s16 D_80770628[];
extern s16 D_80770710[];
extern s32 gCamActor;

void func_80024000();
void bossPieceListStep();
void func_800253AC();
void func_80027770();
void func_80027840();
void bossScriptStep(u8 *, s32, f32);
void bossSpawnParticleRing();
s32 randomNonNegative();
void func_80613C48(void *, s16, f32, f32);
void func_80613CA8(s32, s16, f32, f32);
s32 camIsCutsceneActive();
void camStartPath(void *, s32, s32);
void camStartShake();
void camSetSecondTarget();
s32 currentActorTestClearFlag();
void currentActorClearFlag();
void actorUpdateModelMatrix();
void screenShakeStart(f32, f32, f32, f32, f32, f32);
s32 mathAngleBetweenPoints2D(f32, f32, f32, f32);
void effectSpawnBoneDebris();
void effectSpawnBoneWhite(void *, s16, f32, f32, f32, f32, s32);
void effectSpawnJointBeam();
void animSetSpeed(void *, s32, f32);
void animSetLoopMode();
s32 animIsPlaying();
void projectileSetTargetCoords(f32, f32, f32);
void projectileGetTargetCoords();
void projectileSpawnNodeEntry(s32, s32, f32, s16, f32, f32, void *);
void projectileAimAndSpawn(s32, s16, f32, f32, f32, f32, f32, void *);
void projectileClampAngleAndSpawn(s16, s32, s32, s32, f32, f32, f32, f32, f32, void *);
void projectileSpawnWithShockwave(s32, f32, s32, s32, s32, s32, f32, f32, f32, f32);
void actorSetUniformScale(void *, f32);
s32 func_8072881C();
void behaviourFrameBegin();
void func_8072A450();
s32 func_8072D13C();

#define D_807FBB40 ((Boss3B_Actor *)D_807FBB40)
#define D_807FDC90 ((Boss3B_DC90 *)D_807FDC90)
#define D_807FDC94 ((Boss3B_DC94 *)D_807FDC94)

void func_800254D0(void) {
    s32 pad_top[1];
    Boss3B_Sp78 *sp78;
    u8 *sp74;
    f32 pad_mid;
    u8 sp6F;
    u8 sp6E;
    s32 pad_bot[1];
    Boss3B_178 *temp_s1;


    temp_s1 = D_807FBB40->unk178;
    sp78 = D_807FBB40->unk17C;
    sp74 = D_800358B0[(D_8076A0A8 == 8) ? 0 : 1][temp_s1->unk14];
    sp6F = (temp_s1->unk12 & 1) ? 1 : 2;
    sp6E = 0;
    behaviourFrameBegin();
    if (!(D_807FBB40->unk60 & 0x10)) {
        D_807FDC98->unk38 = 0.002f;
        camSetSecondTarget(gCamActor, 0, 0);
        func_80027840(&D_80035CC0);
        D_807FBB40->unkC4 = (f32) D_807502F4;
        D_807FBB40->unkC8 = (f32) D_807502D8;
        func_8002531C();
        D_807FDC98->unk2C = 0.01f;
        D_807FDC98->unk30 = 3.0f;
        D_807FBB40->unk12A = 0x3E8;
        animSetSpeed(D_807FBB40, 1, 0.2f);
        animSetLoopMode(D_807FBB40, 1, 1);
        D_807FBB40->unk146 = 0;
        func_8002413C();
        D_807FBB40->unkB8 = 0.0f;
        func_80614D00(D_807FBB40, 0.0f, 0.0f);
        {
            u32 var_v0 = (u32) effectUpdateAndDispatch;
            u32 end = (u32) effectNodeSetSubVal;
            s32 checksum = 0;
            D_807FBB40->unk154 = (u8) *(temp_s1->unk15 + sp74);
            temp_s1->unk15 = (u8) (temp_s1->unk15 + 1);
            D_807FBB40->unk155 = 0U;
            while (var_v0 < end) {
                checksum += *(s32 *) var_v0;
                var_v0 += 4;
            }
            if (checksum != 0x3D6E227F) {
                *(s32 *)((u32)&D_80627F04) = 0x27BDFF38;
            }
        }
    }
    func_8072881C(0, D_807FDC90->unk28);
    if ((D_807FBB70[0x200] == 9) || (D_807FBB70[0x15] != 0)) {
        func_8067E2E4(D_807FBB40, 0xC, 2.0f);
        D_807FBB40->unk138 = 0;
        D_807FBB40->unk144 = 1;
        currentActorClearFlag();
        actorScriptStart(D_807FBB40, 0x262);
        camStartPath(D_807FBB40, 9, 1);
        D_807FBB40->unk154 = 0x37U;
        D_807FBB40->unk155 = 0U;
    } else if (D_807FBB70[0x200] == 4) {
        func_8002531C();
        D_807FBB40->unk154 = 0x4DU;
        D_807FBB40->unk155 = 0U;
        D_807FBB40->unk138 = 0;
        D_80750190 = 1;
        func_8067E2E4(D_807FBB40, 0xC, 2.0f);
        actorScriptStart(D_807FBB40, 0x262);
        temp_s1->unk15 = 0U;
        temp_s1->unk14 = (u8) (temp_s1->unk14 + 1);
        sp74 = D_800358B0[(D_8076A0A8 == 8) ? 0 : 1][temp_s1->unk14];
        camStartPath(D_807FBB40, 4, 1);
    }
    switch ((u32) D_807FBB40->unk154) {                     /* switch 1 */
    case 0x1F:                                      /* switch 1 */
        func_80613C48(D_807FBB40, 0x39A, 0.0f, 0.0f);
        func_80614D00(D_807FBB40, 0.0f, 0.0f);
        D_807FBB40->unk146 = 3;
        D_807FBB40->unk154 = (u8) *(temp_s1->unk15 + sp74);
        temp_s1->unk15 = (u8) (temp_s1->unk15 + 1);
        D_807FBB40->unk155 = 0U;
        break;
    case 0x1E:                                      /* switch 1 */
        if (currentActorTestClearFlag() != 0) {
            D_807FBB40->unk154 = 0x40U;
            bossSpawnParticleRing(0x1A, D_807FDCA0->unk14->unk28, D_807FDCA0->unk14->unk2A, D_807FDCA0->unk14->unk2C, 0x800, 6);
        }
        break;
    case 0x37:                                      /* switch 1 */
        switch (D_807FBB40->unk155) {                          /* switch 2 */
        case 1:                                     /* switch 2 */
            effectSpawnJointBeam(0xD, 0x11, 0x12, 0x16);
            break;
        case 2:                                     /* switch 2 */
            if (!(D_8076A064 & 3)) {
                func_8067E2E4(D_807FBB40, (((s32) ((s32) (randomNonNegative() >> 0xF) % 32767) % 10) + 0xD) & 0xFF, 1.0f);
            }
            if (currentActorTestClearFlag() != 0) {
                func_80024000();
                actorScriptStart(D_807FBB40, 0x263);
                D_807FDC90->unk2C = 0x14;
                D_807FBB40->unk155 = 3U;
                D_807FBB40->unk60 = (s32) (D_807FBB40->unk60 | 0x800000);
                D_807FBB40->unk16A = 0x1E;
                D_807FBB40->unk16B = 0x1E;
                D_807FBB40->unk16C = 0x1E;
            }
            break;
        case 3:                                     /* switch 2 */
            if (D_807FDC90->unk2C != 0) {
                D_807FDC90->unk2C--;
                func_80024300();
            } else if (currentActorTestClearFlag() != 0) {
                if (D_807FBB40->unk70 == -1) {
                    sfxPlayActorSound(D_807FBB40, 0x131, 0x3C, 1, 1, 0xFF, 1.0f, 0);
                }
                D_807FBB40->unk72 = 0;
                D_807FBB40->unk155 = 4U;
                func_80613CA8(D_807FBB40, 0x39A, 0.0f, 30.0f);
                D_807FBB40->unkEE = 0;
            }
            func_80027770();
            break;
        case 4:                                     /* switch 2 */
            D_807FBB40->unk72 = (s16) (D_807FBB40->unk72 + 1);
            effectSpawnBoneDebris((s16) (((s32) ((s32) (randomNonNegative() >> 0xF) % 32767) % 7) + 0x1D), 1);
            D_807FBB40->unkE6 = (s16) (D_807FBB40->unkE6 + D_807FBB40->unkEE);
            if (D_807FBB40->unkEE + 10 > 500) {
                D_807FBB40->unkEE = 500;
            } else {
                D_807FBB40->unkEE += 10;
            }
            actorSetUniformScale(D_807FBB40, (f32) ((f64) D_807FBB40->unk4->unk34 * 0.99));
            D_807FBB40->unk80 = (f32) ((f64) D_807FBB40->unk80 + ((f64) (356.0f - D_807FBB40->unk80) * 0.03));
            if ((f64) D_807FBB40->unk4->unk38 < 0.04) {
                D_807FBB40->unk155 = 5U;
            }
            break;
        case 5:                                     /* switch 2 */
            sfxStopSlotSound(D_807FBB40, 1);
            D_807FBB40->unk154 = 0x40U;
            bossSpawnParticleRing(0x124, (s16) (s32) D_807FBB40->unk7C, (s16) (s32) D_807FBB40->unk80, (s16) (s32) D_807FBB40->unk84, mathAngleBetweenPoints2D((f32) D_807FDCA0->unk14->unk82, (f32) D_807FDCA0->unk14->unk86, D_807FBB40->unk7C, D_807FBB40->unk84), 5);
            break;
        }
        break;
    case 0x27:                                      /* switch 1 */
        if (flagGet(0x68, 2) != 0) {
            D_807FBB40->unk154 = (u8) *(temp_s1->unk15 + sp74);
            temp_s1->unk15 = (u8) (temp_s1->unk15 + 1);
            D_807FBB40->unk155 = 0U;
            break;
        }
        case 0x29:                                  /* switch 1 */
        case 0x2D:                                  /* switch 1 */
        case 0x2E:                                  /* switch 1 */
            switch (D_807FBB40->unk155) {                      /* switch 3 */
            case 0:                                 /* switch 3 */
                if ((D_807444EC != 1) || (currentActorTestClearFlag() != 0)) {
                    animSetLoopLimit(D_807FBB40, 1, 1);
                    sp78->unk0 = 0U;
                    D_807FBB40->unk155 = 1U;
                    func_806086CC(D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84, 0x3A, 0xFF, 0x7F, 1, 0x1E, 0.3f, 0);
                }
                break;
            case 1:                                 /* switch 3 */
                if ((animIsPlaying(D_807FBB40, 1) == 0) && (sp78->unk0 == 0)) {
                    func_806086CC(D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84, 0x174, 0xC8, 0x7F, 1, 0x1E, 0.3f, 0);
                    sp78->unk0 = 1U;
                }
                if ((D_807444EC != 1) || (currentActorTestClearFlag() != 0)) {
                    D_807FBB40->unk155 = 2U;
                }
                break;
            case 2:                                 /* switch 3 */
            case 3:                                 /* switch 3 */
                if (D_807FBB40->unk154 == 0x29) {
                    func_80024FA8(temp_s1, sp78, sp74, &D_80035984);
                } else if (D_807FBB40->unk154 == 0x2E) {
                    func_80024FA8(temp_s1, sp78, sp74, &D_80035988);
                } else {
                    func_80024FA8(temp_s1, sp78, sp74, &D_80035980);
                }
                break;
            case 4:                                 /* switch 3 */
                if ((D_807444EC != 1) || (currentActorTestClearFlag() != 0)) {
                    D_807FBB40->unk154 = (u8) *(temp_s1->unk15 + sp74);
                    temp_s1->unk15 = (u8) (temp_s1->unk15 + 1);
                    D_807FBB40->unk155 = 0U;
                }
                break;
            }
        break;
    case 0x28:                                      /* switch 1 */
        switch (D_807FBB40->unk155) {                          /* switch 4; irregular */
        case 0:                                     /* switch 4 */
            currentActorClearFlag();
            func_80613C48(D_807FBB40, 0x3AF, 0.0f, 4.0f);
            D_807FBB40->unk155 = 1U;
            /* fallthrough */
        case 1:                                     /* switch 4 */
            if (!(D_8076A064 & 7)) {
                effectSpawnJointBeam(0xD, 0x16, 0x17, 0x1C);
            }
            if (currentActorTestClearFlag() != 0) {
                func_8067E2E4(D_807FBB40, 6, 1.0f);
                func_8067E2E4(D_807FBB40, 7, 1.0f);
                actorScriptStart(D_807FBB40, 0x26C);
                func_8002450C(sp78, 0, 5);
                func_8002450C(sp78, 1, 5);
                func_806086CC(D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84, 0x22, 0xFF, 0x7F, 1, 0x1E, 0.3f, 0);
                func_806086CC(D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84, 0x3C, 0xFF, 0x7F, 1, 0x1E, 0.3f, 0);
                D_807FBB40->unk155 = 2U;
            }
            break;
        case 2:                                     /* switch 4 */
            bossPieceStep(sp78, 0, 50.0f, 70.0f, 90.0f);
            if (bossPieceStep(sp78, 1, 50.0f, 70.0f, 90.0f) != 0) {
                D_807FBB40->unk154 = (u8) *(temp_s1->unk15 + sp74);
                temp_s1->unk15 = (u8) (temp_s1->unk15 + 1);
                D_807FBB40->unk155 = 0U;
            }
            break;
        }
        break;
    case 0x13:                                      /* switch 1 */
    case 0x1A:                                      /* switch 1 */
    case 0x1B:                                      /* switch 1 */
    case 0x2F:                                      /* switch 1 */
        switch (D_807FBB40->unk155) {                        /* switch 5 */
        case 0:                                     /* switch 5 */
            if (sp78->unk10 >= -0x3FFF) {
                sp78->unk10 -= 0x190;
                if (D_807FBB40->unk70 == -1) {
                    sfxPlayActorSound(D_807FBB40, 0x1F0, 1, 1, 1, 0xFF, 1.0f, 0);
                }
            } else {
                if (D_807FBB40->unk154 == 0x2F) {
                    actorScriptStart(D_807FBB40, 0x268);
                }
                sfxStopSlotSound(D_807FBB40, 1);
                D_807FBB40->unk155 = 1U;
                D_807FDC90->unk2E = 0;
                D_807FBB40->unkB8 = 0.0f;
            }
            {
                s16 val = sp78->unk10;

                sp78->unk12 = sp78->unk10;
                func_80024524(2, val);
            }
            func_80024524(3, sp78->unk12);
            break;
        case 1:                                     /* switch 5 */
            D_807FDC90->unk2E += (D_807FBB40->unk154 == 0x2F) ? 10 : 4;
            if (D_807FDC90->unk2E >= 0x12D) {
                D_807FDC90->unk2E = 0x12C;
            }
            D_807FBB40->unkC0 = (f32) D_807FDC90->unk2E;
            func_800253AC();
            sp6E = 1;
            actorMoveWithinZone(0x45, 510.0f, 480.0f, 0x292, 0.0f);
            if (D_807FBB40->unkB4 > 30.0f) {
                D_807FBB40->unkB8 = 100.0f;
            }
            if (D_807FBB40->unkB4 > 150.0f) {
                D_807FBB40->unk155 = 2U;
            }
            break;
        case 2:                                     /* switch 5 */
            actorMoveWithinZone(0x45, 510.0f, 480.0f, 0x292, 0.0f);
            if (D_8076A064 & 8) {
                func_800253AC();
                sp6E = 1;
                D_807FBB40->unkC0 = 100.0f;
            }
            if ((D_807444EC != 1) || (currentActorTestClearFlag() != 0)) {
                if (D_807FBB40->unk154 == 0x2F) {
                    D_807FBB40->unk154 = (u8) *(temp_s1->unk15 + sp74);
                    temp_s1->unk15 = (u8) (temp_s1->unk15 + 1);
                    D_807FBB40->unk155 = 0U;
                } else {
                    D_807FBB40->unk155 = 3U;
                }
            }
            break;
        case 3:                                     /* switch 5 */
            actorMoveWithinZone(0x45, 510.0f, 480.0f, 0x292, 0.0f);
            if (D_807FBB40->unk6A & 1) {
                projectileSpawnWithShockwave(0xB8, 0.14f, 0x64, 0xFF, 0x96, 7, 1.04f, 40.0f, 8.0f, 600.0f);
                func_806086CC(D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84, 0x221, 0xC8, 0x7F, 1, 0, 0.3f, 0);
                func_80613C48(D_807FBB44, 0x4F9, 0.0f, 0.0f);
                func_80614D00(D_807FBB44, 0.5f, 0.0f);
                func_806086CC(D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84, 0x24A, 0xFF, 0x7F, 1, 0x1E, 0.3f, 0);
                func_806086CC(D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84, 0x36, 0xFF, 0x7F, 1, 0x1E, 0.3f, 0);
                D_807FBB40->unk155 = 4U;
                D_807FDC90->unk2C = 0x3C;
            }
            break;
        case 4:                                     /* switch 5 */
            if ((D_807FDC90->unk2C == 0x28) || (D_807FDC90->unk2C == 0x32)) {
                func_806086CC(D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84, 0x1C1, 0xB4, 0x7F, 1, 0x1E, 0.3f, 0);
            }
            if (D_807FDC90->unk2C != 0) {
                D_807FDC90->unk2C--;
            } else {
                D_807FBB40->unk154 = (u8) *(temp_s1->unk15 + sp74);
                temp_s1->unk15 = (u8) (temp_s1->unk15 + 1);
                D_807FBB40->unk155 = 0U;
            }
            break;
        }
        break;
    case 0x2C:                                      /* switch 1 */
        {
            s32 pad;
            sp78->unk10 = -sp78->unk10 * 0.1 + sp78->unk10;
            sp78->unk12 = -sp78->unk12 * 0.1 + sp78->unk12;
            func_80024524(3, sp78->unk12);
            func_80024524(2, sp78->unk10);
        }
        /* fallthrough */
    case 0x2B:                                      /* switch 1 */
        switch (D_807FBB40->unk155) {                        /* switch 6; irregular */
        case 0:                                     /* switch 6 */
            animSetLoopLimit(D_807FBB40, 1, 1);
            D_807FBB40->unk155 = 2U;
            func_806086CC(D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84, 0x3A, 0xFF, 0x7F, 1, 0x1E, 0.3f, 0);
            break;
        case 2:                                     /* switch 6 */
        case 3:                                     /* switch 6 */
            bossPieceListStep(temp_s1, sp78, sp74, (D_807FBB40->unk154 == 0x2B) ? &D_80035980 : &D_80035984);
            break;
        case 4:                                     /* switch 6 */
            D_807FBB40->unk154 = (u8) *(temp_s1->unk15 + sp74);
            temp_s1->unk15 = (u8) (temp_s1->unk15 + 1);
            D_807FBB40->unk155 = 0U;
            break;
        }
        break;
    case 0x2A:                                      /* switch 1 */
        switch (D_807FBB40->unk155) {                        /* switch 7; irregular */
        case 0:                                     /* switch 7 */
            actorScriptStart(D_807FBB40, 0x257);
            D_807FBB40->unk155 = 1U;
            break;
        case 2:                                     /* switch 7 */
            D_807FBB40->unk154 = (u8) *(temp_s1->unk15 + sp74);
            temp_s1->unk15 = (u8) (temp_s1->unk15 + 1);
            D_807FBB40->unk155 = 0U;
            break;
        }
        break;
    case 0x11:                                      /* switch 1 */
    case 0x57:                                      /* switch 1 */
        switch (D_807FBB40->unk155) {                          /* switch 8 */
        case 0:                                     /* switch 8 */
            actorScriptStart(D_807FBB40, (D_807FBB40->unk154 == 0x57) ? 0x258 : 0x259);
            D_807FBB40->unk155 = 1U;
            /* fallthrough */
        case 1:                                     /* switch 8 */
            actorMoveWithinZone(0x45, D_807FDC94->unk7C, D_807FDC94->unk84, (D_807FBB40->unk154 == 0x57) ? 0x210 : 0x212, 0.0f);
            break;
        case 2:                                     /* switch 8 */
            actorMoveWithinZone(0x45, D_807FDC94->unk7C, D_807FDC94->unk84, 0x212, 0.0f);
            break;
        case 3:                                     /* switch 8 */
            if (D_807FBB40->unk154 == 0x11) {
                screenShakeStart(D_807FBB40->unk7C, D_807FBB40->unk84, 20.0f, 2.0f, 8.0f, 400.0f);
            }
            camStartShake(gCamActor, 5, 0x14);
            break;
        case 5:                                     /* switch 8 */
            D_807FBB40->unkB8 = 0.0f;
            D_807FBB40->unk154 = (u8) *(temp_s1->unk15 + sp74);
            temp_s1->unk15 = (u8) (temp_s1->unk15 + 1);
            D_807FBB40->unk155 = 0U;
            break;
        }
        break;
    case 0x30:                                      /* switch 1 */
        actorMoveWithinZone(0x45, 510.0f, 480.0f, 0x292, 0.0f);
        if (D_8076A064 & 8) {
            func_800253AC();
            sp6E = 1;
            D_807FBB40->unkC0 = 100.0f;
        }
        switch (D_807FBB40->unk155) {                        /* switch 9 */
        case 0:                                     /* switch 9 */
            temp_s1->unk18 = sp74[temp_s1->unk15++];
            temp_s1->unk19 = temp_s1->unk18;
            D_807FBB40->unk155 = 1U;
            actorScriptStart(D_807FBB40, 0x269);
            break;
        case 2:                                     /* switch 9 */
            projectileGetTargetCoords(D_807FBB40, 5U);
            projectileSpawnNodeEntry(0x1E, 5, 1.2f, D_807FBB40->unkE6, 600.0f, 300.0f, D_807FBB40);
            func_806086CC(D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84, 0xF6, 0xFF, 0x7F, 1, 0x1E, 0.3f, 0);
            effectSpawnBoneWhite(D_807FBB40, 5, 2.0f, 0.0f, 0.0f, 0.0f, -0x50);
            if (temp_s1->unk19 != 0) {
                temp_s1->unk19--;
                D_807FBB40->unk155 = 1U;
            } else {
                actorScriptStart(D_807FBB40, 0);
                func_80613C48(D_807FBB40, 0x3A8, 0.0f, 10.0f);
                D_807FBB40->unk155 = 3U;
                D_807FDC90->unk2C = 0x1E;
            }
            break;
        case 3:                                     /* switch 9 */
            if (D_807FDC90->unk2C != 0) {
                D_807FDC90->unk2C--;
            } else {
                D_807FBB40->unk155 = 4U;
            }
            break;
        case 4:                                     /* switch 9 */
            projectileSetTargetCoords((f32) (((s32) (randomNonNegative() >> 15) % 20)) + D_807FDC94->unk7C, D_807FDC94->unk80 + 400.0f, (f32) (((s32) (randomNonNegative() >> 15) % 20)) + D_807FDC94->unk84);
            projectileAimAndSpawn(0x1E, 0xA, 1.2f, D_807FDC94->unk7C, D_807FDC94->unk80, D_807FDC94->unk84, 600.0f, D_807FBB40);
            D_807FDC90->unk2C = 0x14;
            D_807FBB40->unk155 = 5U;
            /* fallthrough */
        case 5:                                     /* switch 9 */
            if (D_807FDC90->unk2C == 0xF) {
                func_806086CC(D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84, 0xF4, 0xFF, 0x7F, 1, 0x1E, 0.3f, 0);
            }
            if (D_807FDC90->unk2C != 0) {
                D_807FDC90->unk2C--;
            } else {
                temp_s1->unk18--;
                if (temp_s1->unk18 != 0) {
                    D_807FBB40->unk155 = 4U;
                } else {
                    D_807FBB40->unk154 = (u8) *(temp_s1->unk15 + sp74);
                    temp_s1->unk15 = (u8) (temp_s1->unk15 + 1);
                    D_807FBB40->unk155 = 0U;
                }
            }
            break;
        }
        break;
    case 0x46:                                      /* switch 1 */
        switch (D_807FBB40->unk155) {                        /* switch 10 */
        case 0:                                     /* switch 10 */
            temp_s1->unk12 = (u16) (temp_s1->unk12 | 1);
            temp_s1->unk18 = (u8) *(temp_s1->unk15++ + sp74);
            temp_s1->unk19 = (u8) *(temp_s1->unk15++ + sp74);
            D_807FBB40->unk155 = 1U;
            /* fallthrough */
        case 1:                                     /* switch 10 */
            D_807FDC90->unk2C = (s16) temp_s1->unk19;
            if (!(temp_s1->unk12 & 1) && (temp_s1->unk14 != 0)) {
                D_807FDC90->unk2C = 0;
                temp_s1->unk18 = (u8) (temp_s1->unk18 + 1);
            }
            D_807FBB40->unk155 = 2U;
            /* fallthrough */
        case 2:                                     /* switch 10 */
            if (D_807FDC90->unk2C != 0) {
                func_80024EAC();
                D_807FDC90->unk2C = (s16) (D_807FDC90->unk2C - 1);
            } else {
                actorScriptStart(D_807FBB40, (sp6F == 1) ? 0x25D : 0x25E);
                D_807FBB40->unk155 = 3U;
            }
            break;
        case 4:                                     /* switch 10 */
            projectileGetTargetCoords(D_807FBB40, sp6F);
            projectileClampAngleAndSpawn(D_807FBB40->unkE6, 0x320, 0x1E, 1, 0.7f, D_807FDC94->unk7C, D_807FDC94->unk80 + 5.0f, D_807FDC94->unk84, (f32) ((temp_s1->unk14 * 0x50) + 0x1F4), D_807FBB40);
            func_806086CC(D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84, 0x18, 0xFF, 0x7F, 1, 0x1E, 0.3f, 0);
            effectSpawnBoneWhite(D_807FBB40, sp6F, 2.0f, 0.0f, 0.0f, 0.0f, -0x50);
            temp_s1->unk12 = (u16) (temp_s1->unk12 ^ 1);
            D_807FBB40->unk155 = 5U;
            break;
        case 6:                                     /* switch 10 */
            if (temp_s1->unk18 != 0) {
                temp_s1->unk18--;
                D_807FBB40->unk155 = 1U;
                break;
            }
            D_807FBB40->unk154 = (u8) *(temp_s1->unk15 + sp74);
            temp_s1->unk15 = (u8) (temp_s1->unk15 + 1);
            D_807FBB40->unk155 = 0U;
            break;
        }
        break;
    case 0x48:                                      /* switch 1 */
        switch (D_807FBB40->unk155) {                        /* switch 11; irregular */
        case 0:                                     /* switch 11 */
            D_807FBB40->unk138 = -1;
            func_80025364();
            D_807FDC90->unk2C = (s16) *(temp_s1->unk15 + sp74);
            temp_s1->unk15 = (u8) (temp_s1->unk15 + 1);
            if (camIsCutsceneActive() != 0) {
                actorScriptStart(D_807FBB40, 0x267);
            } else {
                actorScriptStart(D_807FBB40, 0x261);
            }
            D_807FBB40->unk155 = 1U;
            /* fallthrough */
        case 1:                                     /* switch 11 */
            if (D_807FDC90->unk2C != 0) {
                D_807FDC90->unk2C--;
                break;
            }
            func_8002531C();
            D_807FBB40->unk154 = (u8) *(temp_s1->unk15 + sp74);
            temp_s1->unk15 = (u8) (temp_s1->unk15 + 1);
            D_807FBB40->unk155 = 0U;
            break;
        }
        break;
    case 0x4D:                                      /* switch 1 */
        switch (D_807FBB40->unk155) {                        /* switch 12; irregular */
        case 0:                                     /* switch 12 */
            currentActorClearFlag();
            actorMoveWithinZone(0x4D, 0.0f, 0.0f, 0x12, 0.0f);
            break;
        case 1:                                     /* switch 12 */
            actorMoveWithinZone(0x4D, 0.0f, 0.0f, 0x12, 0.0f);
            effectSpawnJointBeam(0xD, 0x16, 0x17, 0x1C);
            break;
        case 2:                                     /* switch 12 */
            if (currentActorTestClearFlag() != 0) {
                actorScriptStart(D_807FBB40, 0x263);
                D_807FBB40->unk155 = 3U;
            }
            effectSpawnJointBeam(0xD, 0x16, 0x17, 0x1C);
            effectSpawnJointBeam(9, 0xB, 0xC, 0xC);
            break;
        case 3:                                     /* switch 12 */
            effectSpawnBoneWhite(D_807FBB40, (s16) (((s32) ((s32) (randomNonNegative() >> 0xF) % 32767) % 20) + 9), 2.0f, 0.0f, 0.0f, 0.0f, -0x50);
            if (currentActorTestClearFlag() != 0) {
                D_807FBB40->unk138 = -1;
                D_807FBB40->unk154 = (u8) *(temp_s1->unk15 + sp74);
                temp_s1->unk15 = (u8) (temp_s1->unk15 + 1);
                D_807FBB40->unk155 = 0U;
                D_80750190 = 0;
            }
            break;
        }
        break;
    case 0x26:                                      /* switch 1 */
        switch (D_807FBB40->unk155) {                        /* switch 13; irregular */
        case 0:                                     /* switch 13 */
            func_80027840(&D_80035CB8);
            D_807FBB40->unk155 = 1U;
            /* fallthrough */
        case 1:                                     /* switch 13 */
            actorMoveWithinZone(0x42, (f32) D_807FDC90->unkA, (f32) D_807FDC90->unkE, 0x290, 0.0f);
            if (D_8076A064 & 8) {
                func_800253AC();
                sp6E = 1;
                D_807FBB40->unkC0 = 100.0f;
            }
            if (func_8072D13C(D_807FBB40->unk154, 0) != 0) {
                D_807FBB40->unk155 = 2U;
            }
            break;
        case 2:                                     /* switch 13 */
            D_807FBB40->unk154 = (u8) *(temp_s1->unk15 + sp74);
            temp_s1->unk15 = (u8) (temp_s1->unk15 + 1);
            D_807FBB40->unk155 = 0U;
            break;
        }
        break;
    case 0x43:                                      /* switch 1 */
    case 0x44:                                      /* switch 1 */
        switch (D_807FBB40->unk155) {                        /* switch 14; irregular */
        case 0:                                     /* switch 14 */
            actorScriptStart(D_807FBB40, (D_807FBB40->unk154 == 0x44) ? 0x25C : 0x25B);
            D_807FBB40->unk155 = 1U;
            break;
        case 2:                                     /* switch 14 */
            if (D_807FBB40->unk154 == 0x44) {
                screenShakeStart(D_807FBB40->unk7C, D_807FBB40->unk84, 20.0f, 2.0f, 8.0f, 400.0f);
                func_806086CC(D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84, 0x36, 0xFF, 0x7F, 1, 0x1E, 0.3f, 0);
            }
            D_807FBB40->unk154 = (u8) *(temp_s1->unk15 + sp74);
            temp_s1->unk15 = (u8) (temp_s1->unk15 + 1);
            D_807FBB40->unk155 = 0U;
            break;
        }
        break;
    case 0x47:                                      /* switch 1 */
        switch (D_807FBB40->unk155) {                        /* switch 15 */
        case 2:                                     /* switch 15 */
        case 4:                                     /* switch 15 */
            break;
        case 0:                                     /* switch 15 */
            actorScriptStart(D_807FBB40, 0x26A);
            D_807FBB40->unk155 = 1U;
            /* fallthrough */
        case 1:                                     /* switch 15 */
            actorMoveWithinZone(0x45, D_807FDC94->unk7C, D_807FDC94->unk84, 0x292, 0.0f);
            if (D_807FBB40->unk6A & 1) {
                actorScriptStart(D_807FBB40, 0x26B);
                D_807FBB40->unk155 = 2U;
            }
            break;
        case 3:                                     /* switch 15 */
            projectileGetTargetCoords(D_807FBB40, 5U);
            projectileAimAndSpawn(0x59, 1, 1.5f, D_807FBB4C->unk7C, D_807FBB4C->unk80 + 2.0f, D_807FBB4C->unk84, 300.0f, D_807FBB40);
            func_806086CC(D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84, 0x128, 0xFF, 0x7F, 1, 0x1E, 0.3f, 0);
            func_806086CC(D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84, 0x188, 0xFF, 0x7F, 1, 0x1E, 0.3f, 0);
            D_807FBB40->unk155 = 4U;
            break;
        default:                                    /* switch 15 */
            D_807FBB40->unk154 = (u8) *(temp_s1->unk15 + sp74);
            temp_s1->unk15 = (u8) (temp_s1->unk15 + 1);
            D_807FBB40->unk155 = 0U;
            break;
        }
        break;
    case 0x23:                                      /* switch 1 */
    case 0x42:                                      /* switch 1 */
        if (D_807FBB40->unk4->unk0->unk10 != 0x39A) {
            actorScriptStart(D_807FBB40, 0x256);
        }
        /* fallthrough */
    default:                                        /* switch 1 */
        bossScriptStep(sp74, 0x10, 0.0f);
        break;
    }
    if (sp6E != 0) {
        if ((D_807FBB40->unk70 != -1) && (D_80770710[D_80770628[D_807FBB40->unk70]] != 0x114)) {
            sfxStopSlotSound(D_807FBB40, 1);
        }
        if (D_807FBB40->unk70 == -1) {
            sfxPlayActorSound(D_807FBB40, 0x114, 1, 1, 1, 0xFF, 0.5f, 0);
        }
    } else {
        if ((D_807FBB40->unk70 != -1) && (D_80770710[D_80770628[D_807FBB40->unk70]] == 0x114)) {
            sfxStopSlotSound(D_807FBB40, 1);
        }
    }
    func_8072A450();
    actorUpdateModelMatrix(D_807FBB40, 0);
}

#undef D_807FBB40
#undef D_807FDC90
#undef D_807FDC94

s32 randomNonNegative(void);
void effectSpawnBoneDefault(void *, s16, f32, f32, f32, f32, s32);

void func_80027770(void) {
    u8 val;

    if (!(D_8076A064 & 3)) {
        if (!(D_8076A064 & 0xF)) {
            val = 0xC;
        } else {
            val = ((randomNonNegative() >> 15) % 0x7FFF) % 7 + 0x1D;
        }
        func_80714998(3);
        func_807149C8(0x50, 0x50, 0x50, 0xC8);
        effectSpawnBoneDefault(D_807FBB40, val, 2.0f, 0.0f, 0.0f, 0.0f, -0x78);
    }
}

#pragma GLOBAL_ASM("asm/boss/nonmatchings/0/D_80035C00.s")

#pragma GLOBAL_ASM("asm/boss/nonmatchings/0/D_80035C14.s")

#pragma GLOBAL_ASM("asm/boss/nonmatchings/0/D_80035C28.s")

#pragma GLOBAL_ASM("asm/boss/nonmatchings/0/D_80035C3C.s")

#pragma GLOBAL_ASM("asm/boss/nonmatchings/0/D_80035C44.s")

#pragma GLOBAL_ASM("asm/boss/nonmatchings/0/D_80035C5C.s")

#pragma GLOBAL_ASM("asm/boss/nonmatchings/0/D_80035C78.s")

#pragma GLOBAL_ASM("asm/boss/nonmatchings/0/D_80035C94.s")

#pragma GLOBAL_ASM("asm/boss/nonmatchings/0/D_80035CB8.s")

#pragma GLOBAL_ASM("asm/boss/nonmatchings/0/D_80035CC0.s")
