// func_80024CA4 (src/multiplayer/0.c): stage 5 (frame 0x108 + all 9 s-regs + f20-f30 + stack layout spF0=240/spC0=192/buf=204/sp104=260 match; opcode-skeleton diff 16 of 368, harness 299 diff lines: remaining s0/s1 swap (var_s0 vs var_s1) and s6/s7 swap (col vs i), f20/f24 swap (fy vs spF0*0.25), IV slots (sp8C/sp90, uopt temps, kept in memory like target) at 136/140 vs 140/144 with the empty-then form, $t rotation (target li t8,255;subu t9). Recipe: for(var_s7=0;..;var_s7++); declare sp104; 4 locals; spF0; 1; char spCC[32]; 2; spC0; 3 (layout needs groups 4/1/2/3 above spC0 - act inlined as ((Plr*)D_807FC924)[i].unk4->, rect = sp104->unk20[i]); s32 var_s1 (u8 breaks roles), mask temp_s2 = var_s1&0xFF, separate col=temp_s2|0xFFFFFF00 kept across calls, s32 idx used as the Gfx pointer for the first colour write (pointer cast, block-local Gfx* grows the frame by 8), pre reused as pointer for the 2nd, fx/fy tmps assigned before the call, else{var_s1=0xFF} gives the b, if(var_s1==0){}else{...} (empty then). 0xFA000000 stays in s8 by itself.
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
    u32 col;
    f32 fx;
    f32 fy;
    s32 temp_s2;
    f32 spF0;
    Gfx *var_s0;
    char spCC[32];
    s32 var_s7;
    s32 var_s1;
    f32 spC0;
    s32 pre;
    s32 idx;
    MpA_CA4_Rect *rect;

    sp104 = (MpA_CA4_Data *)((Struct_800249D8_Arg1_MpDraw *)arg1)->unk174;
    spF0 = (f32) func_806FD894(1);
    spC0 = (f32) func_806FD894(1);
    var_s0 = func_800246EC(arg0, sp104, 0.0f);
    gSPDisplayList(var_s0++, &D_1000118);
    gSPMatrix(var_s0++, &D_20000C0, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
    gSPMatrix(var_s0++, sp104->unk30, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gDPPipeSync(var_s0++);
    gDPSetCombineMode(var_s0++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
    for (var_s7 = 0; var_s7 < (s32) D_807FC928; var_s7++) {
            var_s1 = 0xFF;
            rect = sp104->unk20[var_s7];
            if (((MpA_CA4_Plr *)D_807FC924)[var_s7].unk4->unk154 == 0x84) {
                fx = (f32) ((f64) rect->unk4 + ((f64) (rect->unk8 - rect->unk4) * 0.5));
                fy = (f32) ((f64) rect->unk6 + ((f64) (rect->unkA - rect->unk6) * 0.5));
                var_s1 = ((MpA_CA4_Plr *)D_807FC924)[var_s7].unk4->unk129;
                gDPSetPrimColor(var_s0++, 0, 0, 255, 255, 255, (u8) (0xFF - var_s1));
                _sprintf(spCC, "BAD LUCK");
                fx = (f32) ((f64) fx - ((f64) func_806FBD5C(1, spCC) * 0.25));
                fy = (f32) ((f64) fy - ((f64) spF0 * 0.25));
                var_s0 = func_806FC530(var_s0, 1, (s16) (s32) (fx * 8.0f), (s16) (s32) (fy * 8.0f), spCC, 4);
            } else {
                var_s1 = 0xFF;
            }
            if (var_s1 == 0) {
            } else {
                temp_s2 = var_s1 & 0xFF;
                col = temp_s2 | 0xFFFFFF00;
                idx = (s32) var_s0++;
                ((Gfx *) idx)->words.w1 = col;
                ((Gfx *) idx)->words.w0 = 0xFA000000;
                if (sp104->unk70 == 0) {
                    idx = var_s7;
                    fx = (f32) rect->unk4 + 4.0f;
                    fy = ((f32) rect->unkA - ((8.0f + spC0) * 0.5f)) * 8.0f;
                    pre = (s32) func_806F8AD4(3, idx);
                    if (pre != 0) {
                        gDPSetPrimColor(var_s0++, 0, 0, 100, 30, 0, temp_s2);
                        _sprintf(spCC, "%d", pre);
                    } else {
                        _sprintf(spCC, "%d", func_806F8AD4(2, idx));
                    }
                    temp_s2 = (s16) (s32) fy;
                    var_s0 = func_806FC530(var_s0, 1, (s16) (s32) (fx * 8.0f), temp_s2, spCC, 4);
                    if (pre != 0) {
                        pre = (s32) var_s0++;
                        ((Gfx *) pre)->words.w0 = 0xFA000000;
                        ((Gfx *) pre)->words.w1 = col;
                    }
                    _sprintf(spCC, "%d", func_806F8AD4(4, idx));
                    var_s0 = func_806FC530(var_s0, 1, (s16) (s32) (((f32) rect->unk8 - ((f32) (func_806FBD5C(1, spCC) + 8) * 0.5f)) * 8.0f), temp_s2, spCC, 4);
                }
                _sprintf(spCC, "%d", mpGetPlayerScore(var_s7));
                var_s0 = func_806FC530(var_s0, 1, (s16) (s32) (((f32) rect->unk8 - (((f32) func_806FBD5C(1, spCC) * 0.5f) + 50.0f)) * 8.0f), (s16) (s32) ((f32) ((f64) rect->unk6 + (8.0 + ((f64) (8.0f - (spC0 * 0.5f)) * 0.5))) * 8.0f), spCC, 4);
            }
    }
    return var_s0;
}
