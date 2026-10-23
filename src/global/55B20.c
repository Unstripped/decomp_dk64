#include "common.h"
#include "actor.h"

typedef struct M55P3EffectBuf {
    /* 0x000 */ u8 unk0;
    /* 0x001 */ u8 unk1;
    /* 0x002 */ u8 unk2;
    /* 0x003 */ u8 unk3;
    /* 0x004 */ u8 unk4;
    /* 0x005 */ u8 pad5[0x1];
    /* 0x006 */ u8 unk6;
    /* 0x007 */ u8 unk7;
    /* 0x008 */ u8 pad8[0xC];
    /* 0x014 */ s32 unk14;
    /* 0x018 */ u8 pad18[0x4];
    /* 0x01C */ s32 unk1C;
    /* 0x020 */ u8 pad20[0x4];
    /* 0x024 */ s32 unk24;
    /* 0x028 */ u8 pad28[0x40];
    /* 0x068 */ s32 unk68;
    /* 0x06C */ s32 unk6C;
    /* 0x070 */ s32 unk70;
    /* 0x074 */ s32 unk74;
    /* 0x078 */ u32 unk78;
    /* 0x07C */ u32 unk7C;
    /* 0x080 */ s16 unk80;
    /* 0x082 */ s16 unk82;
    /* 0x084 */ s16 unk84;
    /* 0x086 */ s16 unk86;
    /* 0x088 */ u8 pad88[0x140];
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

extern s32 D_807F6C80;
extern s16 D_807F6C58[];
extern s32 D_807F70AC;
struct M55P2SearchEntry;
struct M55P2BoxEntry;
extern struct M55P2SearchEntry *D_807F70B0;
extern struct M55P2BoxEntry *D_807F70B4;
extern u8 D_807F7140;

void func_806307AC(s32);
s32 func_8063070C(s32);
s32 func_80630890(s32, f32, f32, f32, void *);
void func_806323C0(s32);
s32 func_8063A38C(s32, s32, f32, f32, f32);
void func_8063B4C0(void *, s32);
s32 func_80653684(void *, f32, f32);
s32 func_80653804(void *, f32, f32);
void func_80652FDC(f32, f32, f32, s16, s16, s16 *);
s16 func_806531B8(f32, f32, f32, s32);
s32 func_806533C4(f32, f32, f32);
s32 func_806534E0(f32, f32, f32, s16, u8 *, f32 *);

void func_806526E0(u8 arg0) {
    s32 i;

    i = 0;
    if (D_807F6C28 > 0) {
        do {
            if ((D_807F6C18[i].unk0 == 1) || arg0) {
                func_806307AC(D_807F6C18[i].unk14);
                func_806307AC(D_807F6C18[i].unk1C);
            }
            i += 1;
        } while (i < D_807F6C28);
    }
}

void func_80652790(u8 arg0) {
    s32 i;

    i = 0;
    if (D_807F6C28 > 0) {
        do {
            if ((D_807F6C18[i].unk0 == 1) || arg0) {
                D_807F6C18[i].unk14 = func_8063070C(D_807F6C18[i].unk14);
                D_807F6C18[i].unk1C = func_8063070C(D_807F6C18[i].unk1C);
            }
            i += 1;
        } while (i < D_807F6C28);
    }
}

void func_80652858(f32 arg0, f32 arg1, f32 arg2, u8 arg3) {
    s32 var_s3;
    s32 var_s1;

    var_s3 = 0;
    if (D_807F6C28 > 0) {
        var_s1 = 0;
        do {
            if (D_807F6C18[var_s1].unk0 == 1 || arg3) {
                D_807F6C18[var_s1].unk14 = func_80630890(D_807F6C18[var_s1].unk14, arg0, arg1, arg2, (void *)((u8 *)&D_807F6C18[var_s1] + 0x18));
                D_807F6C18[var_s1].unk1C = func_80630890(D_807F6C18[var_s1].unk1C, arg0, arg1, arg2, (void *)((u8 *)&D_807F6C18[var_s1] + 0x20));
            }
            var_s3 += 1;
            var_s1 += 1;
        } while (var_s3 < D_807F6C28);
    }
}

void func_8065297C(void) {
    s32 i;

    i = 0;
    if (D_807F6C28 > 0) {
        do {
            func_806323C0(D_807F6C18[i].unk14);
            func_806323C0(D_807F6C18[i].unk1C);
            i += 1;
        } while (i < D_807F6C28);
    }
}

#ifdef NON_MATCHING
void func_80652A08(f32 arg0, f32 arg1, f32 arg2, u8 arg3) {
    s32 var_v1;
    s32 var_s0;
    s32 var_s1;
    void *temp_v0;

    var_v1 = D_807F6C28;
    var_s1 = 0;
    if (var_v1 > 0) {
        var_s0 = 0;
        do {
            if (((M55P3EffectBuf *)((u8 *)D_807F6C18 + var_s0))->unk0 == 1 || arg3) {
                if (((M55P3EffectBuf *)((u8 *)D_807F6C18 + var_s0))->unk6 != 0) {
                    ((M55P3EffectBuf *)((u8 *)D_807F6C18 + var_s0))->unk24 = 0;
                } else {
                    ((M55P3EffectBuf *)((u8 *)D_807F6C18 + var_s0))->unk24 = func_8063A38C(((M55P3EffectBuf *)((u8 *)D_807F6C18 + var_s0))->unk14, ((M55P3EffectBuf *)((u8 *)D_807F6C18 + var_s0))->unk1C, arg0, arg1, arg2);
                }
                var_v1 = D_807F6C28;
            }
            var_s1 += 1;
            var_s0 += 0x1C8;
        } while (var_s1 < var_v1);
    }
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/55B20/func_80652A08.s")
#endif

typedef struct {
    /* 0x00 */ u8 pad0[0x14];
    /* 0x14 */ void *next;
} M55P2Node;

#ifdef NON_MATCHING
void func_80652B04(void) {
    s32 var_s2;
    s32 var_s3;
    s32 var_s4;
    void *node;
    void *next;

    D_807F7140 = 0;
    var_s3 = 0;
    if (D_807F6C28 > 0) {
        var_s4 = 0;
        do {
            if (((M55P3EffectBuf *)((u8 *)D_807F6C18 + var_s4))->unk1 != 0) {
                var_s2 = 1;
            } else {
                var_s2 = 0;
            }
            node = (void *)((M55P3EffectBuf *)((u8 *)D_807F6C18 + var_s4))->unk14;
            if (node != NULL) {
                do {
                    next = ((M55P2Node *)node)->next;
                    func_8063B4C0(node, var_s2 & 0xFF);
                    node = next;
                } while (next != NULL);
            }
            var_s3 += 1;
            var_s4 += 0x1C8;
        } while (var_s3 < D_807F6C28);
    }
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/55B20/func_80652B04.s")
#endif

#pragma GLOBAL_ASM("asm/global/nonmatchings/55B20/func_80652BC8.s")

#ifdef NON_MATCHING
s32 func_80652DB4(f32 arg0, f32 arg1, f32 arg2) {
    s16 *var_v1;
    s16 temp_t1;
    s16 temp_v0;
    s32 i;

    i = 0;
    if (D_807F6C28 == 0) {
        return 0xFF;
    }
    temp_v0 = func_806531B8(arg0, arg1, arg2, 0);
    if (D_807F6C80 > 0) {
        var_v1 = &D_807F6C58[i];
        do {
            temp_t1 = *var_v1;
            var_v1++;
            if (temp_v0 == temp_t1) {
                return 1;
            }
        } while ((u32)var_v1 < (u32)&D_807F6C58[D_807F6C80]);
    }
    return 0;
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/55B20/func_80652DB4.s")
#endif

s32 func_80652E58(s16 arg0) {
    s32 var_v1;

    if (D_807F6C28 == 0) {
        return 0xFF;
    }
    if (D_807F6C18[arg0].unk1 != 0) {
        var_v1 = 1;
    } else {
        var_v1 = 0;
    }
    return var_v1 & 0xFF;
}

s32 func_80652EBC(s16 arg0) {
    s32 var_v1;

    if (D_807F6C28 == 0) {
        return 0xFF;
    }
    if (D_807F6C18[arg0].unk0 == 1) {
        var_v1 = 1;
    } else {
        var_v1 = 0;
    }
    return var_v1 & 0xFF;
}

s32 func_80652F24(s16 arg0, s16 arg1) {
    s32 var_v1;

    if (D_807F6C28 == 0) {
        return 1;
    }
    if (D_807F6C18[arg1].unk1 & (1 << arg0)) {
        var_v1 = 1;
    } else {
        var_v1 = 0;
    }
    return var_v1 & 0xFF;
}

s16 func_80652F9C(f32 arg0, f32 arg1, f32 arg2, s16 arg3) {
    s16 temp;

    func_80652FDC(arg0, arg1, arg2, arg3, -1, &temp);
    return temp;
}

typedef struct M55P2BoxEntry {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ s16 unk2;
    /* 0x04 */ s16 unk4;
    /* 0x06 */ s16 unk6;
    /* 0x08 */ s16 unk8;
    /* 0x0A */ s16 unkA;
} M55P2BoxEntry;

typedef struct M55P2SearchEntry {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ s16 unk2;
    /* 0x04 */ s16 unk4;
    /* 0x06 */ u8 pad6[0x12];
    /* 0x18 */ u8 unk18;
    /* 0x19 */ u8 pad19[0x3];
} M55P2SearchEntry;

#ifdef NON_MATCHING
void func_80652FDC(f32 arg0, f32 arg1, f32 arg2, s16 arg3, s16 arg4, s16 *arg5) {
    s16 temp_v1;
    s32 var_s1;

    var_s1 = 0;
    if (D_807F70AC > 0) {
        do {
            if ((arg3 == D_807F70B0[var_s1].unk0) && (arg4 == D_807F70B0[var_s1].unk4)) {
                temp_v1 = D_807F70B0[var_s1].unk2;
                if (((f32)D_807F70B4[temp_v1].unk0 <= arg0) && (arg0 <= (f32)D_807F70B4[temp_v1].unk6) && ((f32)D_807F70B4[temp_v1].unk2 <= arg1) && (arg1 <= (f32)D_807F70B4[temp_v1].unk8) && ((f32)D_807F70B4[temp_v1].unk4 <= arg2) && (arg2 <= (f32)D_807F70B4[temp_v1].unkA)) {
                    *arg5 = temp_v1;
                    func_80652FDC(arg0, arg1, arg2, arg3, temp_v1, arg5);
                }
            }
            var_s1 += 1;
        } while (var_s1 < D_807F70AC);
    }
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/55B20/func_80652FDC.s")
#endif

#ifdef NON_MATCHING
s16 func_806531B8(f32 arg0, f32 arg1, f32 arg2, s32 arg3) {
    s16 sp70[200];
    f32 sp200;
    u8 sp207;
    f32 temp_fs0;
    f32 temp_fs1;
    f32 temp_fs2;
    f32 var_fs0;
    s16 var_s1;
    s16 var_s3;
    s32 var_s0;
    s32 var_s1_2;
    s32 var_s2;
    void *temp_v0;
    u8 *var_s0_2;

    var_s2 = 0;
    if (D_807F6C28 == 0) {
        return -1;
    }
    temp_fs0 = arg0 * 6.0f;
    temp_fs1 = arg1 * 6.0f;
    temp_fs2 = arg2 * 6.0f;
    if (func_806534E0(temp_fs0, temp_fs1, temp_fs2, arg3, &sp207, &sp200) != 0) {
        if (sp207 == 0) {
            return arg3;
        }
        sp70[0] = arg3;
        var_s2 = 1;
        *(f32 *)&sp70[2] = sp200;
    }
    var_s0 = 0;
    var_s1 = 0;
    if (D_807F6C28 > 0) {
        do {
            if (arg3 != var_s1) {
                if (func_806534E0(temp_fs0, temp_fs1, temp_fs2, var_s1, &sp207, &sp200) != 0) {
                    if (sp207 == 0) {
                        var_s0 = 1;
                    } else {
                        temp_v0 = (u8 *)sp70 + var_s2 * 8;
                        *(s16 *)temp_v0 = var_s1;
                        var_s2 += 1;
                        var_s1 += 1;
                        *(f32 *)((u8 *)temp_v0 + 4) = sp200;
                    }
                } else {
                    var_s1 += 1;
                }
            } else {
                var_s1 += 1;
            }
        } while ((var_s0 == 0) && (var_s1 < D_807F6C28));
    }
    if (var_s0 != 0) {
        return var_s1;
    }
    var_fs0 = *(f32 *)&sp70[2];
    if (var_s2 == 0) {
        return arg3;
    }
    var_s3 = sp70[0];
    var_s1_2 = 0;
    if (var_s2 > 0) {
        var_s0_2 = (u8 *)sp70;
        do {
            var_s1_2 += 1;
            if (func_806533C4(var_fs0, *(f32 *)(var_s0_2 + 4), temp_fs1) != 0) {
                var_fs0 = *(f32 *)(var_s0_2 + 4);
                var_s3 = *(s16 *)var_s0_2;
            }
            var_s0_2 += 8;
        } while (var_s1_2 != var_s2);
    }
    return var_s3;
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/55B20/func_806531B8.s")
#endif

#ifdef NON_MATCHING
s32 func_806533C4(f32 arg0, f32 arg1, f32 arg2) {
    s32 var_v0;
    s32 var_v1;
    f32 var_fv0;
    f32 var_fv1;

    var_v0 = 0;
    if (arg0 <= arg2) {
        var_v0 = 1;
    } else if ((arg0 - arg2) < 60.0f) {
        var_v0 = 1;
    }
    var_v1 = 0;
    if (arg1 <= arg2) {
        var_v1 = 1;
    } else if ((arg1 - arg2) < 60.0f) {
        var_v1 = 1;
    }
    if (var_v0 != 0 || var_v1 != 0) {
        if (var_v1 != 0) {
            if (var_v0 == 0) {
                return 1;
            }
            if (arg2 < arg0) {
                var_fv0 = arg0 - arg2;
            } else {
                var_fv0 = arg2 - arg0;
            }
            if (arg2 < arg1) {
                var_fv1 = arg1 - arg2;
            } else {
                var_fv1 = arg2 - arg1;
            }
            if (var_fv0 < var_fv1) {
                return 0;
            }
            return 1;
        }
        return 0;
    }
    return 0;
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/55B20/func_806533C4.s")
#endif

typedef struct {
    /* 0x00 */ u8 pad0[6];
    /* 0x06 */ s16 unk6;
    /* 0x08 */ u8 pad8[0xA];
    /* 0x12 */ u8 unk12;
    /* 0x13 */ u8 pad13[1];
} M55P2CollNode;

s32 func_806534E0(f32 arg0, f32 arg1, f32 arg2, s16 arg3, u8 *arg4, f32 *arg5) {
    M55P2CollNode *var_s0;
    M55P2CollNode *temp_s1;
    M55P3EffectBuf *temp_v0;

    temp_v0 = (M55P3EffectBuf *)((u8 *)D_807F6C18 + arg3 * 0x1C8);
    if (arg0 < (f32)temp_v0->unk80) {
        return 0;
    }
    if (arg2 < (f32)temp_v0->unk82) {
        return 0;
    }
    if ((f32)temp_v0->unk84 < arg0) {
        return 0;
    }
    if ((f32)temp_v0->unk86 < arg2) {
        return 0;
    }
    var_s0 = (M55P2CollNode *)temp_v0->unk78;
    temp_s1 = (M55P2CollNode *)temp_v0->unk7C;
    if (var_s0 != temp_s1) {
        do {
            if ((func_80653684(var_s0, arg0, arg2) != 0) && (func_80653804(var_s0, arg0, arg2) != 0)) {
                if (var_s0->unk12 & 1) {
                    *arg4 = 0;
                } else {
                    *arg4 = 1;
                    *arg5 = (f32)var_s0->unk6;
                }
                return 1;
            }
            var_s0++;
        } while (var_s0 != temp_s1);
    }
    return 0;
}

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
        D_807F70B0[off].unk18 = 0;
        off += 1;
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
