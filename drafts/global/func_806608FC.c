// func_806608FC (src/global/63EC0.c): stage 5 (EffC2): frame/callee-saved match; 22 text lines (shape 4): dz/dx f0/f2 swap (dz=f0 expected; mine dz=f2 whichever sum order), h f14 vs f18 (so 100.0 const lands f16/f17 not f14/f15), 'move a0,v0' (sub var in a0 vs expected CSE'd v0 -- dropping sub shifts case-0 regs), type spill slot 32 vs 36. Wins: (dx*dx)+(dz*dz) sum order; '/ (100.0 * 1.0)' permuter find (FAKE) stops per-branch 100.0 CSE; 2 FAKEs total (D_807F93E4 dead stmt + this). Local decl order doesn't affect regs (permuted 262).
typedef struct EffBHeightSub2 {
    u8 pad0[4];
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    u8 pad14[0x46 - 0x14];
    s16 unk46;
    s16 unk48;
    s16 unk4A;
    s16 unk4C;
    s16 unk4E;
} EffBHeightSub2;

f32 sqrtf(f32);

f32 func_806608FC(EffectNode *water, s32 arg1, s32 arg2, u8 type) {
    s32 temp1;
    s32 temp;
    EffBHeightSub2 * sub;
    f32 dx;
    f32 dz;
    f32 dist;
    f32 diff;
    f32 h;
    f32 baseH;
    f32 edgeDist;
    s32 d;
    f32 sin1;

    switch (type) {
    case 0:
        {
            temp1 = (s32)(((EffBHeightSub2 *)water->unk0)->unk4 * (f32)arg1);
            temp = (s32)(((EffBHeightSub2 *)water->unk0)->unk8 * (f32)arg2);
            sin1 = func_80612794((s16)((water->unk30 + temp1) % 4095));
        }
        return (func_80612794((s16)((water->unk34 + temp) % 4095)) * ((EffBHeightSub2 *)water->unk0)->unk10) + ((f32)((EffBHeightSub2 *)water->unk0)->unk4E + water->unk4 + (((EffBHeightSub2 *)water->unk0)->unkC * sin1));

    case 1:
    case 2:
        if (D_807F93C4 != 0) {
            dz = (f32)arg2 - D_807F93C8[1];
            dx = (f32)arg1 - D_807F93C8[0];
            dist = sqrtf((dx * dx) + (dz * dz));
            if (dist < D_807F93DC) {
                diff = D_807F93DC - dist;
            } else {
                diff = -(D_807F93DC - dist);
            }
            if (D_807F93DC < D_807F93E8) {
                h = D_807F93D4;
            } else if (D_807F93E4 < D_807F93DC) {
                h = 0.0f;
            } else {
                h = (f32)((f64)D_807F93D4 + ((0.0 - (f64)D_807F93D4) * (f64)((D_807F93DC - D_807F93E8) / (D_807F93E4 - D_807F93E8))));
            }
            if ((f64)diff < 50.0) {
                baseH = (f32)((EffBHeightSub2 *)water->unk0)->unk4E + water->unk4;
                h += baseH;
            } else if ((f64)diff > 150.0) {
                baseH = (f32)((EffBHeightSub2 *)water->unk0)->unk4E + water->unk4;
                h = baseH;
            } else {
                baseH = (f32)((EffBHeightSub2 *)water->unk0)->unk4E + water->unk4;
                h = (f32)((f64)baseH + ((f64)h + ((0.0 - (f64)h) * (((f64)diff - 50.0) / (100.0 * 1.0)))));  // FAKE: folds to 100.0 but keeps the constant out of the sibling-branch CSE (steers f-reg pick)
            }
        } else {
            baseH = (f32)((EffBHeightSub2 *)water->unk0)->unk4E + water->unk4;
            h = baseH;
        }

        if (type == 2) {
            sub = (EffBHeightSub2 *)water->unk0;
            d = arg1 - sub->unk46;
            edgeDist = (f32)(d > 0 ? d : -d);

            d = arg1 - sub->unk4A;
            dx = (f32)(d > 0 ? d : -d);
            if (dx < edgeDist) edgeDist = dx;

            d = arg2 - sub->unk4C;
            dx = (f32)(d > 0 ? d : -d);
            if (dx < edgeDist) edgeDist = dx;
            if (D_807F93E4 && D_807F93E4) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)

            d = arg2 - sub->unk48;
            dx = (f32)(d > 0 ? d : -d);
            if (dx < edgeDist) edgeDist = dx;

            if ((f64)edgeDist < 100.0) {
                h = (f32)((f64)baseH + ((f64)(h - baseH) * ((f64)edgeDist / 100.0)));
            }
        }
        return h;

    default:
        return 0.0f;
    }
}
