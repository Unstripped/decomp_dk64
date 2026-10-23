// func_806608FC (src/global/63EC0.c): from .scratch/R4A63EC0/func_806608FC_best.c
typedef struct R4A_SubStruct {
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
} R4A_SubStruct;

f32 func_80612794(s16);

f32 func_806608FC(EffectNode *water, s32 arg1, s32 arg2, u8 type) {
    f32 sin1;
    s32 temp;
    R4A_SubStruct *sub;
    f32 dx, dz, dist, diff;
    f32 h, baseH;
    f32 edgeDist;

    switch (type) {
    case 0:
        sub = (R4A_SubStruct *)water->unk0;
        {
            s32 temp1 = (s32)(sub->unk4 * (f32)arg1);
            temp = (s32)(sub->unk8 * (f32)arg2);
            sin1 = func_80612794((s16)((water->unk30 + temp1) % 4095));
        }
        sub = (R4A_SubStruct *)water->unk0;
        return (func_80612794((s16)((water->unk34 + temp) % 4095)) * sub->unk10) + ((f32)sub->unk4E + water->unk4 + (sub->unkC * sin1));

    case 1:
    case 2:
        if (D_807F93C4 != 0) {
            dz = (f32)arg2 - D_807F93C8[1];
            dx = (f32)arg1 - D_807F93C8[0];
            dist = sqrtf((dz * dz) + (dx * dx));
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
                baseH = (f32)((R4A_SubStruct *)water->unk0)->unk4E + water->unk4;
                h += baseH;
            } else if ((f64)diff > 150.0) {
                baseH = (f32)((R4A_SubStruct *)water->unk0)->unk4E + water->unk4;
                h = baseH;
            } else {
                baseH = (f32)((R4A_SubStruct *)water->unk0)->unk4E + water->unk4;
                h = (f32)((f64)baseH + ((f64)h + ((0.0 - (f64)h) * (((f64)diff - 50.0) / 100.0))));
            }
        } else {
            baseH = (f32)((R4A_SubStruct *)water->unk0)->unk4E + water->unk4;
            h = baseH;
        }

        if (type == 2) {
            s32 d;
            sub = (R4A_SubStruct *)water->unk0;
            d = arg1 - sub->unk46;
            if (d < 0) d = -d;
            edgeDist = (f32)d;

            d = arg1 - sub->unk4A;
            if (d < 0) d = -d;
            if ((f32)d < edgeDist) edgeDist = (f32)d;

            d = arg2 - sub->unk4C;
            if (d < 0) d = -d;
            if ((f32)d < edgeDist) edgeDist = (f32)d;

            d = arg2 - sub->unk48;
            if (d < 0) d = -d;
            if ((f32)d < edgeDist) edgeDist = (f32)d;

            if ((f64)edgeDist < 100.0) {
                h = (f32)((f64)baseH + ((f64)(h - baseH) * ((f64)edgeDist / 100.0)));
            }
        }
        return h;

    default:
        return 0.0f;
    }
}
