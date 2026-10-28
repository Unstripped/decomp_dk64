// func_80024CA4 (src/multiplayer/0.c): stage 4 (frame 0x108, 9 s-regs + f20-f30 saves match; 403 harness diff lines of 409; char spCC[24] needed for 0x108). Remaining regalloc: target keeps IV temps sp8C(i*0x2F0)/sp90(i*4) in memory (all 9 s regs taken: s1=var_s1/idx u8, s2=temp_s2/ft5, s3=&spCC, s4=rect, s5=pre, s6=col(alpha|0xFFFFFF00), s7=i, fp=0xFA000000); mine puts &spCC in s1, alpha+temp_s2+ft5 merged in s2, idx in s4, IVs in v0/v1. Decoded gfx: SetPrimColor(255,255,255,255-a) for BAD LUCK, (255,255,255,a) via shared u32 col, (100,30,0,a) for the pre!=0 branch; spF0/spC0 = (f32)func_806FD894(1) (u32 return). Not tried: permuter on this (368 insns).
typedef struct MpA_CA4_Rect {
    char pad[4];
    s16 unk4;
    s16 unk6;
    s16 unk8;
    s16 unkA;
} MpA_CA4_Rect;

typedef struct MpA_CA4_Data {
    char pad[0x20];
    MpA_CA4_Rect *unk20[4];
    Mtx *unk30;
    char pad2[0x70 - 0x34];
    u8 unk70;
} MpA_CA4_Data;

typedef struct MpA_CA4_Act {
    char pad[0x129];
    u8 unk129;
    char pad2[0x154 - 0x12A];
    u8 unk154;
} MpA_CA4_Act;

typedef struct MpA_CA4_Plr {
    char pad[4];
    MpA_CA4_Act *unk4;
    char pad2[0x2F0 - 8];
} MpA_CA4_Plr;

u32 func_806FD894(s32);

Gfx *func_80024CA4(Gfx *arg0, void *arg1) {
    MpA_CA4_Data *sp104;
    f32 spF0;
    char spCC[24];
    f32 spC0;
    Gfx *var_s0;
    s32 var_s7;
    u8 var_s1;
    MpA_CA4_Act *act;
    MpA_CA4_Rect *rect;
    f32 fx;
    f32 fy;
    s32 pre;
    s32 temp_s2;
    u32 col;
    s16 ft5;
    MpA_CA4_Rect **sp90;
    s32 sp8C;

    sp104 = (MpA_CA4_Data *)((Struct_800249D8_Arg1_MpDraw *)arg1)->unk174;
    spF0 = (f32) func_806FD894(1);
    spC0 = (f32) func_806FD894(1);
    var_s0 = func_800246EC(arg0, sp104, 0.0f);
    gSPDisplayList(var_s0++, &D_1000118);
    gSPMatrix(var_s0++, &D_20000C0, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
    gSPMatrix(var_s0++, sp104->unk30, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gDPPipeSync(var_s0++);
    gDPSetCombineMode(var_s0++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
    var_s7 = 0;
    if ((s32) D_807FC928 > 0) {
        sp90 = sp104->unk20;
        sp8C = 0;
        do {
            act = ((MpA_CA4_Plr *)(D_807FC924 + sp8C))->unk4;
            var_s1 = 0xFF;
            rect = *sp90;
            if (act->unk154 == 0x84) {
                var_s1 = act->unk129;
                gDPSetPrimColor(var_s0++, 0, 0, 255, 255, 255, (u8) (0xFF - var_s1));
                fx = (f32) ((f64) rect->unk4 + ((f64) (rect->unk8 - rect->unk4) * 0.5));
                fy = (f32) ((f64) rect->unk6 + ((f64) (rect->unkA - rect->unk6) * 0.5));
                _sprintf(spCC, "BAD LUCK");
                var_s0 = func_806FC530(var_s0, 1, (s16) (s32) ((f32) ((f64) fx - ((f64) func_806FBD5C(1, spCC) * 0.25)) * 8.0f), (s16) (s32) ((f32) ((f64) fy - ((f64) spF0 * 0.25)) * 8.0f), spCC, 4);
            }
            if (var_s1 != 0) {
                temp_s2 = var_s1 & 0xFF;
                col = temp_s2 | 0xFFFFFF00;
                var_s0->words.w1 = col;
                var_s0->words.w0 = 0xFA000000;
                var_s0++;
                if (sp104->unk70 == 0) {
                    var_s1 = var_s7;
                    fx = (f32) rect->unk4 + 4.0f;
                    fy = ((f32) rect->unkA - ((8.0f + spC0) * 0.5f)) * 8.0f;
                    pre = (s32) func_806F8AD4(3, var_s1);
                    if (pre != 0) {
                        gDPSetPrimColor(var_s0++, 0, 0, 100, 30, 0, temp_s2);
                        _sprintf(spCC, "%d", pre);
                    } else {
                        _sprintf(spCC, "%d", func_806F8AD4(2, var_s1));
                    }
                    ft5 = (s16) (s32) fy;
                    var_s0 = func_806FC530(var_s0, 1, (s16) (s32) (fx * 8.0f), ft5, spCC, 4);
                    if (pre != 0) {
                        var_s0->words.w0 = 0xFA000000;
                        var_s0->words.w1 = col;
                        var_s0++;
                    }
                    _sprintf(spCC, "%d", func_806F8AD4(4, var_s1));
                    var_s0 = func_806FC530(var_s0, 1, (s16) (s32) (((f32) rect->unk8 - ((f32) (func_806FBD5C(1, spCC) + 8) * 0.5f)) * 8.0f), ft5, spCC, 4);
                }
                _sprintf(spCC, "%d", mpGetPlayerScore(var_s7));
                var_s0 = func_806FC530(var_s0, 1, (s16) (s32) (((f32) rect->unk8 - (((f32) func_806FBD5C(1, spCC) * 0.5f) + 50.0f)) * 8.0f), (s16) (s32) ((f32) ((f64) rect->unk6 + (8.0 + ((f64) (8.0f - (spC0 * 0.5f)) * 0.5))) * 8.0f), spCC, 4);
            }
            var_s7 += 1;
            sp8C += 0x2F0;
            sp90 += 1;
        } while (var_s7 < (s32) D_807FC928);
    }
    return var_s0;
}
