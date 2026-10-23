#include "common.h"
#include "actor.h"

extern s8 D_807F7F00;

void func_8065CDA0(s8 arg0) {
    D_807F7F00 = arg0;
}

extern Gfx D_80748310[6][2];

void func_8065CDB0(Gfx *arg0, Gfx *arg1) {
    while (arg0 != arg1) {
        int found = 0;
        int i = 0;

        for (; i < 6 && !found; ) {
            if (arg0->words.w0 == D_80748310[i][0].words.w0 && arg0->words.w1 == D_80748310[i][0].words.w1) {
                found = 1;
            } else {
                i++;
            }
        }
        if (found) {
            gSPDisplayList(arg0++, 0x06000000 + i * 0x10);
        } else {
            arg0++;
        }
    }
}

typedef struct {
    u8 pad0[0x21C];
    f32 x;
    f32 y;
    f32 z;
    u8 pad228[0x27C - 0x228];
    f32 unk27C;
    u8 pad280[0x2F0 - 0x280];
} R1A_PlayerStruct;
extern R1A_PlayerStruct *D_807FC924;
extern u8 D_807FC929;
extern s32 D_8076A0A8;
f32 func_8065CFB8(s16, f32);
f32 func_8065D0FC(f32);
#define R2A_SQ(x) ((x) * (x))

void func_8065CE4C(f32 arg0, f32 arg1, f32 arg2, f32 arg3, s16 arg4, s16 *arg5) {
    s32 pad;
    f32 dist;
    f32 fv1;

    dist = sqrtf(R2A_SQ(arg0 - D_807FC924[D_807FC929].x) + R2A_SQ(arg1 - D_807FC924[D_807FC929].y) + R2A_SQ(arg2 - D_807FC924[D_807FC929].z));
    if (D_8076A0A8 == 0x26) {
        arg3 = func_8065CFB8(arg4, arg3);
        if (arg3 < dist) {
            *arg5 = 0;
            return;
        }
    }
    arg0 = func_8065D0FC(arg3);
    fv1 = (arg0 * 3.0f) / (f32)4;
    if (dist < fv1) {
        *arg5 = 0xFF;
        return;
    }
    *arg5 = (s32)(((dist - fv1) / (arg0 - fv1)) * 255.0f);
    if (*arg5 >= 0x100) {
        *arg5 = 0xFF;
    }
    *arg5 = 0xFF - *arg5;
}

extern f32 D_807F6940;

f32 func_8065CFB8(s16 arg0, f32 arg1) {
    if ((arg0 == 0xB2) || (arg0 == 0x253)) {
        arg1 = (f64)arg1 + (600.0 - (f64)arg1) * (f64)D_807F6940;
    }
    return arg1;
}

extern Gfx D_80748370[6][2];
extern Gfx D_807483D0[6][2];

Gfx *func_8065D008(Gfx *gdl, s16 arg1, u8 arg2) {
    if (arg1 == 0xFF) {
        if ((u8)D_807F7F00 != 0 || arg2) {
            gSPSegment(gdl++, 6, osVirtualToPhysical(&D_80748310));
        } else {
            gSPSegment(gdl++, 6, osVirtualToPhysical(&D_80748370));
        }
    } else {
        gDPSetFogColor(gdl++, 0, 0, 0, arg1);
        gSPSegment(gdl++, 6, osVirtualToPhysical(&D_807483D0));
    }
    return gdl;
}

extern f32 D_807F5FDC;
extern f32 D_807F5FE0;

f32 func_8065D0FC(f32 arg0) {
    if ((f64)D_807FC924[D_807FC929].unk27C == 45.0) {
        return arg0;
    }
    return (arg0 / D_807F5FDC) * D_807F5FE0;
}

typedef struct {
    s32 unk0;
    s16 unk4;
    s16 unk6;
    void *unk8;
} R1A_Struct807F8E90;
extern R1A_Struct807F8E90 D_807F8E90[4];
extern s16 D_807F8E8A;

void func_8065D170(void) {
    s32 i;
    for (i = 0; i < 4; i++) {
        D_807F8E90[i].unk0 = -1;
    }
    D_807F8E8A = 0;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/61AA0/func_8065D1AC.s")

void func_8065D244(s16 arg0) {
    D_807F8E8A = arg0;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/61AA0/func_8065D254.s")

void func_8065D964(s16 *arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4) {
    arg0[0] = arg1;
    arg0[1] = 0;
    arg0[2] = arg2;
    arg0[4] = arg3 << 5;
    arg0[5] = arg4 << 5;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/61AA0/func_8065D994.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/61AA0/func_8065E040.s")


s32 func_8065E0CC(void) {
    if ((D_8076A0A8 == 6) || (D_8076A0A8 == 8) || (D_8076A0A8 == 0x37) || (D_8076A0A8 == 0x53) || (D_8076A0A8 == 0x6A) || (D_8076A0A8 == 0xC4) || (D_8076A0A8 == 0xC5)) {
        return 0;
    }
    return 1;
}

extern s16 D_807F9058;
extern s16 D_807F905A;

void func_8065E124(void) {
    D_807F9058 = 0;
    D_807F905A = 0;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/61AA0/func_8065E138.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/61AA0/func_8065E634.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/61AA0/func_8065E81C.s")

s32 func_8065E81C(s32, s32);
extern s32 D_807F9064;

s32 func_8065EA44(void) {
    D_807F9064 = ((u32)D_807F9064 * 3) >> 2;
    if ((u32)D_807F9064 < 0x10000) {
        return 0;
    }
    return func_8065E81C(1, 0);
}

s32 func_8065EA98(s32 arg0, s16 arg1, u8 arg2) {
    return (arg1 * 16 + arg0 * 4 + arg2) % 100;
}

extern s32 D_807F9068;

void func_8065EACC(void) {
    if (D_807F9064 != 0x9C40) {
        D_807F9068 = D_807F9064;
    }
    D_807F9064 = 0x9C40;
}

void func_8065EAF4(void) {
    D_807F9064 = D_807F9068;
}
