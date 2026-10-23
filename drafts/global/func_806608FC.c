// func_806608FC (src/global/63EC0.c): logic matches, frame size difference
extern u8 D_807F93C4;
extern f32 D_807F93C8[];
extern f32 D_807F93D4;
extern f32 D_807F93DC;
extern f32 D_807F93E4;
extern f32 D_807F93E8;

f32 func_80612794(s16);
f32 sqrtf(f32);

f32 func_806608FC(R1C_Water *water, s16 arg1, s16 arg2, u8 type) {
    f32 sin1;
    s32 temp;
    R1C_SubStruct *sub;
    f32 dx, dz, dist, diff;
    f32 h, baseH;
    f32 edgeDist, d;

    switch (type) {
    case 0:
        sub = water->unk0;
        temp = (s32)(sub->unk8 * (f32)arg2);
        sin1 = func_80612794((s16)((water->unk30 + (s32)(sub->unk4 * (f32)arg1)) % 4095));
        sub = water->unk0;
        return (func_80612794((s16)((water->unk34 + temp) % 4095)) * sub->unk10) + ((f32)sub->unk4E + water->unk4 + (sub->unkC * sin1));

    case 1:
    case 2:
        baseH = (f32)water->unk0->unk4E + water->unk4;
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
                h += baseH;
            } else if ((f64)diff > 150.0) {
                h = baseH;
            } else {
                h = (f32)((f64)baseH + ((f64)h + ((0.0 - (f64)h) * (((f64)diff - 50.0) / 100.0))));
            }
        } else {
            h = baseH;
        }

        if (type == 2) {
            d = (f32)(arg1 - water->unk0->unk46);
            if (d < 0.0f) d = -d;
            edgeDist = d;

            d = (f32)(arg1 - water->unk0->unk4A);
            if (d < 0.0f) d = -d;
            if (d < edgeDist) edgeDist = d;

            d = (f32)(arg2 - water->unk0->unk4C);
            if (d < 0.0f) d = -d;
            if (d < edgeDist) edgeDist = d;

            d = (f32)(arg2 - water->unk0->unk48);
            if (d < 0.0f) d = -d;
            if (d < edgeDist) edgeDist = d;

            if ((f64)edgeDist < 100.0) {
                h = (f32)((f64)baseH + ((f64)(h - baseH) * ((f64)edgeDist / 100.0)));
            }
        }
        return h;

    default:
        return 0.0f;
    }
}
