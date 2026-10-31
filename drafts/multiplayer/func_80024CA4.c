// func_80024CA4 (src/multiplayer/0.c): QOv1: stage 6, 29 diff lines (was 110), shape identical (registers only). Key fixes: col/idx/pre/temp_s2 named locals replaced by g0 packet pointer + CSE'd (var_s1 & 0xFF)|0xFFFFFF00 (col is an expression temp, i=s7/col=s6 now close), else{var_s1=0xFF} arm (emits the b), fy split, dead if (D_1000118)/(D_807FC924==0). Remaining: g0 packet ptr lands in v1 (target v0), so 'move a2,v0' vs 'move a2,s5' (pre), D_807FC924 load in v0 vs t0 (dead D_807FC924 stmt shifts ring but takes v0), t-ring numbers; deadsweep+permuter 540s+decl-order perms: no further gain.
u32 textGetFontHeight(s32);

Gfx *func_80024CA4(Gfx *arg0, MpControllerActor *arg1) {
    MpControllerState *sp104;
    Gfx *g0;
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
    MpViewport *rect;

    sp104 = arg1->unk174;
    spF0 = (f32) textGetFontHeight(1);
    spC0 = (f32) textGetFontHeight(1);
    var_s0 = func_800246EC(arg0, sp104, 0.0f);
    gSPDisplayList(var_s0++, &D_1000118);
    gSPMatrix(var_s0++, &D_20000C0, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
    gSPMatrix(var_s0++, sp104->unk30, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gDPPipeSync(var_s0++);
    gDPSetCombineMode(var_s0++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
    for (var_s7 = 0; var_s7 < D_807FC928; var_s7++) {
            rect = sp104->unk20[var_s7];
            if (D_807FC924[var_s7].unk4->unk154 == 0x84) {
                fx = (f32) ((f64) rect->unk4 + ((f64) (rect->unk8 - rect->unk4) * 0.5));
                fy = (f32) ((f64) rect->unk6 + ((f64) (rect->unkA - rect->unk6) * 0.5));
                var_s1 = (u8) D_807FC924[var_s7].unk4->unk128;
                gDPSetPrimColor(var_s0++, 0, 0, 255, 255, 255, (u8) (0xFF - var_s1));
                _sprintf(spCC, "BAD LUCK");
                fx = (f32) ((f64) fx - ((f64) textGetStringWidth(1, spCC) * 0.25));
                fy = (f32) ((f64) fy - ((f64) spF0 * 0.25));
                var_s0 = textDrawStringVtx(var_s0, 1, (s16) (fx * 8.0f), (s16) (fy * 8.0f), spCC, 4);
            } else {
                var_s1 = 0xFF;
                if (D_807FC924 == 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
            }
            if (var_s1 == 0) {
            } else {
                g0 = var_s0++;
                g0->words.w1 = (var_s1 & 0xFF) | 0xFFFFFF00;
                g0->words.w0 = 0xFA000000;
                if (sp104->unk70 == 0) {
                    idx = var_s7;
                    fx = (f32) rect->unk4 + 4.0f;
                    fy = (f32) rect->unkA - ((8.0f + spC0) * 0.5f);
                    fy = fy * 8.0f;
                    pre = (s32) slotQueueGetValue(3, idx);
                    if (pre != 0) {
                        g0 = var_s0++; g0->words.w0 = 0xFA000000; g0->words.w1 = (var_s1 & 0xFF) | 0x641E0000; // FAKE: same-line packet stores steer as1 scheduling
                        _sprintf(spCC, "%d", pre);
                    } else {
                        _sprintf(spCC, "%d", slotQueueGetValue(2, idx));
                        if (D_1000118) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                    }
                    temp_s2 = (s16) fy;
                    var_s0 = textDrawStringVtx(var_s0, 1, (s16) (fx * 8.0f), temp_s2, spCC, 4);
                    if (pre != 0) {
                        g0 = var_s0++;
                        g0->words.w0 = 0xFA000000;
                        g0->words.w1 = (var_s1 & 0xFF) | 0xFFFFFF00;
                    }
                    _sprintf(spCC, "%d", slotQueueGetValue(4, idx));
                    fx = (f32) rect->unk8 - ((f32) (textGetStringWidth(1, spCC) + 8) * 0.5f);
                    var_s0 = textDrawStringVtx(var_s0, 1, (s16) (fx * 8.0f), temp_s2, spCC, 4);
                }
                _sprintf(spCC, "%d", mpGetPlayerScore(var_s7));
                fx = (f32) rect->unk8 - (((f32) textGetStringWidth(1, spCC) * 0.5f) + 50.0f);
                fy = (f32) ((f64) rect->unk6 + (8.0 + ((f64) (8.0f - (spC0 * 0.5f)) * 0.5))) * 8.0f;
                var_s0 = textDrawStringVtx(var_s0, 1, (s16) (fx * 8.0f), (s16) fy, spCC, 4);
            }
    }
    return var_s0;
}
