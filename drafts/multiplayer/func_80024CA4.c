// func_80024CA4 (src/multiplayer/0.c): stage 5 (OPS 2 of 368 mnemonic diffs; harness score 242 vs 295): fixed this round: var_s0/var_s1 swap (drop else{var_s1=0xFF}), col/i swap (dummy 'if (col) {}' before 'if (pre != 0)' block), last two textDrawStringVtx calls via named fx/fy statements. Remaining: (a) expected 'b' after BAD LUCK block + no extra 'andi t4,s2,0xff' on primcolor alpha (target alpha reg already masked; idx then has own reg: ours col=s5/idx-temp=s6/pre=s1 vs target col=s6/idx=var_s1=s1/pre=s5), (b) fx/fy f20/f22 mirrored, (c) IV slots 136/140 vs 140/144. Reusing var_s1 for idx hoists the mask above the branch (worse).
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

u32 textGetFontHeight(s32);

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
    spF0 = (f32) textGetFontHeight(1);
    spC0 = (f32) textGetFontHeight(1);
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
                fx = (f32) ((f64) fx - ((f64) textGetStringWidth(1, spCC) * 0.25));
                fy = (f32) ((f64) fy - ((f64) spF0 * 0.25));
                var_s0 = textDrawStringVtx(var_s0, 1, (s16) (s32) (fx * 8.0f), (s16) (s32) (fy * 8.0f), spCC, 4);
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
                    pre = (s32) slotQueueGetValue(3, idx);
                    if (pre != 0) {
                        gDPSetPrimColor(var_s0++, 0, 0, 100, 30, 0, temp_s2);
                        _sprintf(spCC, "%d", pre);
                    } else {
                        _sprintf(spCC, "%d", slotQueueGetValue(2, idx));
                    }
                    temp_s2 = (s16) (s32) fy;
                    var_s0 = textDrawStringVtx(var_s0, 1, (s16) (s32) (fx * 8.0f), temp_s2, spCC, 4);
                    if (col) {
                    }
                    if (pre != 0) {
                        pre = (s32) var_s0++;
                        ((Gfx *) pre)->words.w0 = 0xFA000000;
                        ((Gfx *) pre)->words.w1 = col;
                    }
                    _sprintf(spCC, "%d", slotQueueGetValue(4, idx));
                    fx = (f32) rect->unk8 - ((f32) (textGetStringWidth(1, spCC) + 8) * 0.5f);
                    var_s0 = textDrawStringVtx(var_s0, 1, (s16) (s32) (fx * 8.0f), temp_s2, spCC, 4);
                }
                _sprintf(spCC, "%d", mpGetPlayerScore(var_s7));
                fx = (f32) rect->unk8 - (((f32) textGetStringWidth(1, spCC) * 0.5f) + 50.0f);
                fy = (f32) ((f64) rect->unk6 + (8.0 + ((f64) (8.0f - (spC0 * 0.5f)) * 0.5))) * 8.0f;
                var_s0 = textDrawStringVtx(var_s0, 1, (s16) (s32) (fx * 8.0f), (s16) (s32) fy, spCC, 4);
            }
    }
    return var_s0;
}
