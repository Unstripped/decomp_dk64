#include "common.h"
#include "actor.h"

typedef struct M55P3EffectBuf {
    /* 0x000 */ u8 unk0;
    /* 0x001 */ u8 unk1;
    /* 0x002 */ u8 unk2;
    /* 0x003 */ u8 unk3;
    /* 0x004 */ u8 unk4;
    /* 0x005 */ u8 pad5[0x2];
    /* 0x007 */ u8 unk7;
    /* 0x008 */ u8 pad8[0xC];
    /* 0x014 */ s32 unk14;
    /* 0x018 */ u8 pad18[0x4];
    /* 0x01C */ s32 unk1C;
    /* 0x020 */ u8 pad20[0x48];
    /* 0x068 */ s32 unk68;
    /* 0x06C */ s32 unk6C;
    /* 0x070 */ s32 unk70;
    /* 0x074 */ s32 unk74;
    /* 0x078 */ u8 pad78[0x150];
} M55P3EffectBuf;

extern u8 D_807F7078[];
extern s32 D_807F6C28;
extern M55P3EffectBuf *D_807F6C18;
extern u8 *D_807F6C1C;
extern s32 D_807F6C20;
extern u8 *D_807F6C2C;

#pragma GLOBAL_ASM("asm/global/nonmatchings/55B20/func_80650E20.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/55B20/func_80650ECC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/55B20/func_80651708.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/55B20/func_80651904.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/55B20/func_80651B64.s")

void func_80651BC0(s16 arg0, s8 arg1) {
    D_807F7078[arg0] = arg1;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/55B20/func_80651BE0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/55B20/func_80651C2C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/55B20/func_8065214C.s")

void func_806521F8(void) {
    s32 i;

    for (i = 0; i < D_807F6C28; i++) {
        D_807F6C18[i].unk0 = 0;
        D_807F6C18[i].unk68 = 0;
        D_807F6C18[i].unk6C = 0;
        D_807F6C18[i].unk70 = 0;
        D_807F6C18[i].unk74 = 0;
    }
    for (i = 0; i < D_807F6C20; i++) {
        D_807F6C1C[i * 0xA + 8] = 0;
        D_807F6C2C[i] = 0;
    }
}

s32 func_806522CC(s16 arg0, s16 arg1, s16 arg2) {
    M55P3EffectBuf *entry;

    entry = (M55P3EffectBuf *)((s32)D_807F6C18 + arg2 * 0x1C8);
    if (entry->unk1 == 0) {
        return 0;
    }
    if ((arg0 >= entry->unk68) && (arg1 >= entry->unk6C) && (entry->unk70 >= arg0) && (entry->unk74 >= arg1)) {
        return 1;
    }
    return 0;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/55B20/func_80652374.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/55B20/func_806524A0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/55B20/func_80652594.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/55B20/func_806526E0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/55B20/func_80652790.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/55B20/func_80652858.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/55B20/func_8065297C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/55B20/func_80652A08.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/55B20/func_80652B04.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/55B20/func_80652BC8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/55B20/func_80652DB4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/55B20/func_80652E58.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/55B20/func_80652EBC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/55B20/func_80652F24.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/55B20/func_80652F9C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/55B20/func_80652FDC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/55B20/func_806531B8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/55B20/func_806533C4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/55B20/func_806534E0.s")

typedef struct {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ s16 unk2;
    /* 0x04 */ s16 unk4;
    /* 0x06 */ u8 pad6[6];
    /* 0x0C */ s16 unkC;
    /* 0x0E */ s16 unkE;
    /* 0x10 */ s16 unk10;
    /* 0x12 */ u8 pad12[2];
} M55P3Box;

s32 func_80653684(void *arg0, f32 arg1, f32 arg2) {
    f32 temp_fa1;
    f32 temp_fv1;
    f32 var_fv0;
    f32 var_fv0_2;
    f32 var_fv0_3;
    f32 var_fv0_4;
    s16 temp_a1;
    s16 temp_a2;
    s16 temp_v1;
    s16 temp_v0;
    M55P3Box *box;

    box = arg0;
    temp_v1 = box->unk2;
    temp_v0 = box->unk0;
    if (temp_v0 < temp_v1) {
        var_fv0 = (f32) temp_v0;
    } else {
        var_fv0 = (f32) temp_v1;
    }
    temp_fv1 = (f32) box->unk4;
    if (!(var_fv0 < temp_fv1)) {
        var_fv0 = temp_fv1;
    }
    if (arg1 < var_fv0) {
        return 0;
    }
    temp_a1 = box->unkC;
    temp_a2 = box->unkE;
    if (temp_a1 < temp_a2) {
        var_fv0_2 = (f32) temp_a1;
    } else {
        var_fv0_2 = (f32) temp_a2;
    }
    temp_fa1 = (f32) box->unk10;
    if (!(var_fv0_2 < temp_fa1)) {
        var_fv0_2 = temp_fa1;
    }
    if (arg2 < var_fv0_2) {
        return 0;
    }
    if (temp_v1 < temp_v0) {
        var_fv0_3 = (f32) temp_v0;
    } else {
        var_fv0_3 = (f32) temp_v1;
    }
    if (!(temp_fv1 < var_fv0_3)) {
        var_fv0_3 = temp_fv1;
    }
    if (var_fv0_3 < arg1) {
        return temp_v1 * 0;
    }
    if (temp_a2 < temp_a1) {
        var_fv0_4 = (f32) temp_a1;
    } else {
        var_fv0_4 = (f32) temp_a2;
    }
    if (!(temp_fa1 < var_fv0_4)) {
        var_fv0_4 = temp_fa1;
    }
    if (var_fv0_4 < arg2) {
        return 0;
    }
    return 1;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/55B20/func_80653804.s")


typedef struct {
    /* 0x000 */ u8 pad0[4];
    /* 0x004 */ void *unk4;
    /* 0x008 */ u8 pad8[0x270 - 0x8];
    /* 0x270 */ s16 unk270;
    /* 0x272 */ s16 unk272;
    /* 0x274 */ s16 unk274;
    /* 0x276 */ s16 unk276;
    /* 0x278 */ s16 unk278;
    /* 0x27A */ s16 unk27A;
    /* 0x27C */ u8 pad27C[0x288 - 0x27C];
    /* 0x288 */ f32 unk288;
    /* 0x28C */ u8 pad28C[4];
    /* 0x290 */ s16 unk290;
    /* 0x292 */ u8 pad292[0x2F0 - 0x292];
} M55P3Player;

extern M55P3Player *D_807FC924;
extern u8 D_807FC929;

void func_80653A70(s16 arg0) {
    D_807F6C18[arg0].unk0 = 1;
    D_807F6C18[arg0].unk1 |= 1 << D_807FC929;
    D_807F6C18[arg0].unk68 = D_807FC924[D_807FC929].unk270;
    D_807F6C18[arg0].unk6C = D_807FC924[D_807FC929].unk272;
    D_807F6C18[arg0].unk70 = D_807FC924[D_807FC929].unk274;
    D_807F6C18[arg0].unk74 = D_807FC924[D_807FC929].unk276;
}

extern u8 D_807F70AB;

void func_80653B70(s8 arg0) {
    D_807F70AB = arg0;
}

void func_8062AD28(f32, f32, f32, void *, void *);
void func_8062AC68(Mtx *);
void func_8062A944(f32, f32, f32);
s16 func_806531B8(f32, f32, f32, s32);
void mapUpdateFogDistance(f32 *, s16);
void func_806521F8();
void func_80653A70(s16);
void func_806547A8(f32, f32, f32);
void func_80654380(f32, f32, f32);
void func_80654A2C(f32, f32, f32);
void func_80656F14(s16, s32, s16, s16, s16, s16, f32, f32, f32);
void func_8065F678(f32, f32, f32, u8);
void actorCalculateTargetDistancesAndAngles(f32, f32, f32);
void func_80655410(f32, f32, f32);
extern u8 D_807F5E20[];
extern u8 D_807F5E68[];
extern u8 D_807444FC;
extern f32 D_807F5FB4;
extern f32 D_807F5FB0;
extern s16 D_807F7138;
extern s32 D_807F6C80;
extern s8 D_807F6C08;

void func_80653B80(f32 arg0, f32 arg1, f32 arg2) {
    D_807FC924[D_807FC929].unk290 = func_806531B8(arg0, arg1, arg2, D_807FC924[D_807FC929].unk290);
    if (D_807F70AB != 0) {
        D_807FC924[D_807FC929].unk290 = *(s16 *)((u8 *)D_807FC924[D_807FC929].unk4 + 0x12C);
    }
    mapUpdateFogDistance(&D_807FC924[D_807FC929].unk288, D_807FC924[D_807FC929].unk290);
    D_807F7138 = (s16)(s32)D_807FC924[D_807FC929].unk288;
    func_8062A944(D_807F5FB4, D_807F5FB0, (f32)D_807F7138);
    func_8062AC68((Mtx *)((u8 *)D_807FC924 + D_807FC929 * 0x2F0 + (D_807444FC << 6) + 8));
    func_8062AD28(arg0, arg1, arg2, &D_807F5E68, &D_807F5E20);
    func_806521F8();
    func_80653A70(D_807FC924[D_807FC929].unk290);
    func_806547A8(arg0, arg1, arg2);
    D_807F6C80 = 0;
    D_807F6C08 = 0;
    func_80656F14(D_807FC924[D_807FC929].unk290, 0, D_807FC924[D_807FC929].unk270, D_807FC924[D_807FC929].unk272, D_807FC924[D_807FC929].unk274, D_807FC924[D_807FC929].unk276, arg0, arg1, arg2);
    func_80654380(arg0, arg1, arg2);
    func_8065F678(arg0, arg1, arg2, D_807FC929);
    actorCalculateTargetDistancesAndAngles(arg0, arg1, arg2);
    func_80655410(arg0, arg1, arg2);
}

extern s32 func_8066B0F8(s32, s32, s32, s32);

#pragma GLOBAL_ASM("asm/global/nonmatchings/55B20/func_80653DF0.s")


extern void collisionBstLookupByHash(u32, u32 *, u32 *);
extern s32 assetFreeBuffer(void *, s32, s32);

void func_80653EA8(u8 *arg0, u8 *arg1) {
    s32 pad[2];
    u32 sp44;
    u32 sp40;
    u32 temp_a0;
    u32 new_var;

    if (arg0 != arg1) {
        do {
            if ((new_var = (*(u32 *)arg0 >> 0x18)) == 0xFD) {
                if (sp40) {
                }
                temp_a0 = *(u32 *)(arg0 + 4);
                if ((temp_a0 >= 0x80000000U) && (temp_a0 < 0xA0000000U)) {
                    collisionBstLookupByHash(temp_a0, &sp44, &sp40);
assetFreeBuffer((void *)*(u32 *)(arg0 + 4), 0x542, 0x22); *(u32 *)(arg0 + 4) = sp40;
                }
            }
            arg0 += 8;
        } while (arg0 != arg1);
    }
}

void func_80653F68(s16 arg0) {
    D_807F6C18[arg0].unk7 |= 8;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/55B20/func_80653FA4.s")

extern s32 D_807F70AC;
extern s32 D_807F70B0;

extern void func_80654418(f32, f32);
extern void func_80655258(f32, f32, f32, s32);

void func_80654380(f32 arg0, f32 arg1, f32 arg2) {
    s32 i;
    s32 off;

    func_80654418(arg0, arg1);
    i = 0;
    off = 0;
    while (i < D_807F70AC) {
        i++;
        *((u8 *)(D_807F70B0 + off) + 0x18) = 0;
        off += 0x1C;
    }
    func_80655258(arg0, arg1, arg2, -1);
    func_80654A2C(arg0, arg1, arg2);
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/55B20/func_80654418.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/55B20/func_806545D4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/55B20/func_806547A8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/55B20/func_80654A2C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/55B20/func_80654BC0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/55B20/func_80654CCC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/55B20/func_80654E84.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/55B20/func_80654FEC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/55B20/func_80655258.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/55B20/func_80655410.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/55B20/func_80655AD0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/55B20/func_80655BF0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/55B20/func_80655CF8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/55B20/func_80655DD0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/55B20/func_80656B98.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/55B20/func_80656E58.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/55B20/func_80656F14.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/55B20/func_806574B8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/55B20/func_80657508.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/55B20/func_8065756C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/55B20/func_806575D0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/55B20/func_8065776C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/55B20/func_80657974.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/55B20/func_80657CB0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/55B20/func_80657E24.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/55B20/func_80657F14.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/55B20/func_80658000.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/55B20/func_80658134.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/55B20/func_806582F8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/55B20/func_8065850C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/55B20/func_80658624.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/55B20/func_806588E0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/55B20/func_80658930.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/55B20/func_80658B08.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/55B20/func_80658BD0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/55B20/func_80658C10.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/55B20/func_80658CCC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/55B20/func_80658DAC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/55B20/func_80658E58.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/55B20/func_80658E8C.s")
