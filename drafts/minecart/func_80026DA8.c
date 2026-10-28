// func_80026DA8 (src/minecart/25F0.c): stage 4: frame 0x70 and s0-s2 set match, switch layout (case 1 empty + 2,3,4,5,6,0x3B) matches, 630 vs 628 insns; remaining diff: expected CSEs the sp68 stack-pointer load into one temp (lw v0,0x68(sp) reused for unkA and unkE across the swc1 unk7C/unk80 stores in switch2 case1) while ours reloads it (lw t7 / lw t2), shifting the t-register ring after; tried local alias t=sp68, pad variants. Frame needs padA before sp68 and padB,padC between sp66 and sp58.
typedef struct McA2_Tgt {
    u8 pad0[0xA];
    s16 unkA;
    u8 padC[0xE - 0xC];
    s16 unkE;
    u8 pad10[0x2C - 0x10];
    s16 unk2C;
} McA2_Tgt;

typedef struct McA2_Cart {
    u8 pad0[4];
    f32 **unk4;
    u8 pad8[0x60 - 8];
    s32 unk60;
    u8 pad64[0x7C - 0x64];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
    u8 pad88[0xE4 - 0x88];
    s16 unkE4;
    s16 unkE6;
    u8 padE8[0xEC - 0xE8];
    s16 unkEC;
    u8 padEE[0x11C - 0xEE];
    struct McA2_Cart *unk11C;
    u8 pad120[0x128 - 0x120];
    s16 unk128;
    u8 pad12A[0x132 - 0x12A];
    s16 unk132;
    u8 pad134[0x154 - 0x134];
    u8 unk154;
    u8 unk155;
    u8 pad156[0x15F - 0x156];
    u8 unk15F;
    u8 pad160[0x168 - 0x160];
    s16 unk168;
    u8 pad16A[1];
    u8 pad16B;
    u8 unk16C;
    u8 pad16D[7];
    McA2_Tgt *unk174;
} McA2_Cart;

typedef struct McA2_BB4C {
    u8 pad0[4];
    struct { u8 pad0[0x64]; u16 unk64; } *unk4;
    u8 pad8[0xE6 - 8];
    s16 unkE6;
} McA2_BB4C;

typedef struct McA2_D580 {
    u8 pad0[0x88];
    struct { u8 pad0[0xA4]; f32 unkA4; u8 padA8[0x174 - 0xA8]; s16 *unk174; } *unk88;
    u8 pad8C[0x104 - 0x8C];
    void *unk104;
    u8 pad108[0x1F0 - 0x108];
    s32 unk1F0;
} McA2_D580;

typedef struct McA2_DC9C {
    u8 pad0[0xB];
    u8 unkB;
} McA2_DC9C;

void camSetTarget(void *, void *, s32, s16, s32, s32, s32, s32, s32, s32, f32);
void actorDespawn(void *);
void func_80613C48(void *, s32, f32, f32);
void func_806086CC(f32, f32, f32, s32, s32, s32, s32, s32, f32, s32);

#define CB ((McA2_Cart *)D_807FBB40)
#define CD ((McA2_D580 *)D_807FD580)
#define C4C ((McA2_BB4C *)D_807FBB4C)

void func_80026DA8(void) {
    s32 padA;
    McA2_Tgt *sp68;
    s16 sp66;
    s32 padB;
    s32 padC;
    f32 sp58;
    f32 sp54;
    f32 sp50;
    f32 sp4C;
    McA2_Cart *s2;
    s16 *p;
    f64 d;
    f32 var;
    f32 x;
    s16 v;

    s2 = CB->unk11C;
    sp68 = s2->unk174;
    sp66 = CB->unk168 * CB->unkEC;
    if (!(CB->unk60 & 0x10)) {
        func_80613C48(D_807FBB40, 0x59C, 0.0f, 0.0f);
        CB->unk60 |= 0x800000;
        ((u8 *)CB)[0x16A] = 0xFF;
        ((u8 *)CB)[0x16B] = 0xFF;
        CB->unk16C = 0xFF;
        CB->unk60 &= ~0x8000;
        CB->unk128 = 0x96;
    }
    CB->unkE6 = s2->unkE6;
    CB->unk7C = (f32)(((f64)(((func_80612794((s16)(s2->unkE6 + sp66)) * 47.0f) + s2->unk7C) - CB->unk7C) * 0.3) + (f64)CB->unk7C);
    CB->unk84 = (f32)(((f64)(((func_80612790((s16)(s2->unkE6 + sp66)) * 47.0f) + s2->unk84) - CB->unk84) * 0.3) + (f64)CB->unk84);
    CB->unk80 = (f32)((f64)CB->unk80 + ((f64)((s2->unk80 - 10.0f) - CB->unk80) * 0.3));
    switch (s2->unk154) {
    case 1:
        break;
    case 2:
    case 3:
        if ((CB->unk168 == 1 && s2->unk154 == 2) || (CB->unk168 == -1 && s2->unk154 == 3)) {
            p = CD->unk88->unk174;
            func_80026C54();
            switch (s2->unk155) {
            case 0:
                if (*p == 0) {
                    CB->unk155 = 0;
                    actorScriptStart(D_807FBB40, 0x312);
                    s2->unk155 = 1;
                    func_80026B6C((TargetStruct *)sp68, 2.2f);
                }
                break;
            case 1:
                d = (f64)CB->unk4[0][1] / 17.0;
                var = (d > 1.0) ? 1.0 : d;
                x = (f32)(((f64)func_80612790((s16)(s32)(var * 2048.0f + 2048.0f)) * 0.5) + 0.5);
                CB->unk7C = ((f32)sp68->unkA - CB->unk7C) * x + CB->unk7C;
                CB->unk80 = (CB->unk80 + 10.0f) + ((CD->unk88->unkA4 - (CB->unk80 + 10.0f)) * x);
                CB->unk84 = ((f32)sp68->unkE - CB->unk84) * x + CB->unk84;
                if (C4C->unk4->unk64 == 0x294 || (CB->unk4[0][1] > 16.0f && CB->unk4[0][1] < 18.0f)) {
                    CB->unk132 = 1;
                } else {
                    CB->unk132 = 0;
                }
                if (CB->unk155 != 0) {
                    s2->unk155 = 0xFF;
                }
                break;
            }
        }
        break;
    case 4:
    case 5:
        if ((CB->unk168 == 1 && s2->unk154 == 4) || (CB->unk168 == -1 && s2->unk154 == 5)) {
            func_80026C54();
            switch (s2->unk155) {
            case 0:
                sp68->unk2C = 0x46;
                s2->unk155 = 1;
                CB->unk132 = 1;
                func_806086CC(CB->unk7C, CB->unk80, CB->unk84, 0x301, 0xFF, 0x7F, 0, 0, 0.0f, 0);
            case 1:
                func_80026B6C((TargetStruct *)sp68, 0.3f);
                v = sp68->unk2C;
                sp68->unk2C = v - 1;
                if (v != 0) {
                    sp58 = (f32)(((f64)func_80612790((s16)(s32)(((f64)sp68->unk2C / 70.0) * 2048.0 + 2048.0)) * 0.5) + 0.5);
                    sp54 = func_80612794((s16)(s32)(2048.0f * sp58));
                    sp50 = func_80612794((s16)(s32)(sp58 * 1536.0f + 1024.0f)) * (f32)(CB->unk168 * -110);
                    sp4C = (f32)(((f64)func_80612790((s16)(s32)(sp58 * 4096.0f)) * 0.5 + 0.5) * 50.0 + -30.0);
                    CB->unk7C = ((func_80612794((s16)(C4C->unkE6 - 0x400)) * sp50 + (f32)sp68->unkA) - CB->unk7C) * sp54 + CB->unk7C;
                    CB->unk80 = CB->unk80 + (((CD->unk88->unkA4 + sp4C) - CB->unk80) * sp54);
                    CB->unk84 = ((func_80612790((s16)(C4C->unkE6 - 0x400)) * sp50 + (f32)sp68->unkE) - CB->unk84) * sp54 + CB->unk84;
                    if (sp68->unk2C < 0x10) {
                        CB->unk132 = 0;
                    }
                } else {
                    s2->unk155 = 0xFF;
                }
                break;
            }
            if (CB->unk168 == 1) {
                CB->unkE4 = func_806CC190(CB->unkE4, 0xC00, 0x40E00000);
            } else {
                CB->unkE4 = func_806CC190(CB->unkE4, 0x400, 0x40E00000);
            }
        }
        break;
    case 6:
        if (s2->unk155 == 0) {
            sp68->unk2C = ((McA2_DC9C *)D_807FDC9C)->unkB;
            s2->unk155 = 1;
        }
        if (CB->unk168 == 1) {
            CB->unkE4 = func_806CC190(CB->unkE4, 0xC00, 0x41800000);
        } else {
            CB->unkE4 = func_806CC190(CB->unkE4, 0x400, 0x41800000);
        }
        if (sp68->unk2C != 0) {
            sp68->unk2C--;
        } else {
            s2->unk155 = 0xFF;
        }
        if (CB->unk155 == 0 && s2->unk15F == 4) {
            CD->unk1F0 |= 0x10000000;
            CB->unk15F = 0xB4;
            CB->unk155++;
        }
        CB->unkEC = func_806CC190(CB->unkEC, 0x64, 0x41200000);
        break;
    case 0x3B:
        actorDespawn(D_807FBB40);
        break;
    }
    if (s2->unk154 == 6) {
        if (CB->unk15F != 0) {
            CB->unk15F -= 0xC;
            camSetTarget(CD->unk104, CD->unk88, 4, (CB->unk15F << 12) / 360, 0x64, 0, 5, 0x23, 0x14, 0, 0.2f);
        }
    }
    if (s2->unk154 != 6) {
        if (CB->unkE4 != 0) {
            CB->unkE4 = func_806CC190(CB->unkE4, 0, 0x41000000);
            CB->unkEC = func_806CC190(CB->unkEC, 0x2BC, 0x41200000);
        }
    }
    actorUpdateModelMatrix(D_807FBB40, 0);
}
