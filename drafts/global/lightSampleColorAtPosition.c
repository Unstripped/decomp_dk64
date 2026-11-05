// lightSampleColorAtPosition (src/global/5E2F0.c): stage 4: full=94 text=85 reloc=6 shape=39; 404 actual instructions both (407 including trailing padding), normalized count 443 vs 441 includes relocation rows; frame 136 and callee-saved set exact. Retained prior best. Matcher9 tried dx/dy/dz inline field expressions and cached coordinate/subtraction expressions (all 7 subsets, with/without FAKEs), reuse delta locals for normalized axes, scalar/array/struct normal and delta vectors, nested/comma/inlined normalization, reuse dot as factor and staged range/diff subtraction, typed FP-zero tests, and scalar/array/struct r or rgb accumulators: no improvement. Inline field expressions across sqrtf recompute loads and grow code; coordinate-expression substitutions retain count but disturb frame/coloring. Array vectors retain stores but worsen allocation; structs compile like scalar locals. Prior 300.0/zero/r priority and missing normal stores remain unresolved.
void lightSampleColorAtPosition(f32 arg0, f32 arg1, f32 arg2, s16 arg3, u8 *arg4, u8 *arg5, u8 *arg6, s16 arg7) {
    f32 pad[1];
    LightTrigger *entry;
    f32 r;
    f32 g;
    f32 b;
    s32 three;
    s32 i;

    if (mapChunkIsInUse(arg7) == 0) {
        *arg4 = *arg5 = *arg6 = 0xFF;
        return;
    }
    if (D_807F7EC8 == 0) {
        *arg4 = (s32)(D_8076A0B4[arg7] * 255.0f);
        *arg5 = (s32)(D_8076A0B8[arg7] * 255.0f);
        if (D_8076A0BC && D_8076A0BC) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
        *arg6 = (s32)(D_8076A0BC[arg7] * 255.0f);
        return;
    }
    r = D_8076A0B4[arg7]; g = D_8076A0B8[arg7]; b = D_8076A0BC[arg7];  // LAYOUT: one line changes as1 scheduling of the three loads
    three = 3;
    for (i = 0; i < D_807F7EC8; i++) {
        {
            entry = &D_807F7BC8[i];
            if (g == 0) {}  // FAKE: hcL
            switch (entry->unk3E) {
            default:
                break;
            case 1: {
                f32 dz;
                f32 dy;
                f32 nz;
                f32 nx;
                f32 ny;
                f32 dx;
                f32 dist;
                f32 dot;
                f32 factor;
                if (b > 0.0f) {}  // FAKE: hcL

                dx = arg0 - (f32)(entry->unk38 / three);
                dy = arg1 - (f32)(entry->unk3A / three);
                dz = arg2 - (f32)(entry->unk3C / three);
                dist = sqrtf((dz * dz) + ((dx * dx) + (dy * dy)));
                if (dist == 0.0f) {
                    dist = 0.1f;
                }
                nz = dz / dist;
                nx = dx / dist;
                ny = dy / dist;
                dot = (entry->unk14 * nz) + ((nx * entry->unkC) + (ny * entry->unk10));
                if (dot < 0.0f) {
                    if (nx == 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                    dot = 0.0f;
                    if (dot && dot) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                }
                if (entry->unk0 <= dot) {
                    if (entry->unk4 <= dot) {
                        factor = 1.0f;
                    } else {
                        factor = (dot - entry->unk0) * entry->unk8;
                    }
                    if ((f64)dist > 300.0) {
                        if (ny && ny) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                        if ((f64)dist > 1100.0) {
                            factor = 0.0f;
                        } else {
                            factor = (f64)factor * (1.0 - (((f64)dist - 300.0) / 800.0));
                            if (arg1) {}  // FAKE: hcL
                    if (entry->unk3C == 0) {}  // FAKE: hcL
                            if (entry) {}  // FAKE: hcL
                        }
                    }
                    r += entry->unk2C * factor;
                    if (entry->unk3A != 0) {}  // FAKE: hcL
                    g += entry->unk30 * factor;
                    if (D_8076A0BC == 0) {}  // FAKE: hcL
                    b += entry->unk34 * factor;
                }
                break;
            }
            case 0: {
                f32 dx;
                f32 dy;
                f32 dz;
                f32 dist;
                f32 diff_val;
                f32 range;
                f32 max_range;
                f32 factor;

                dz = (f32)(entry->unk3C / three) - arg2;
                dx = (f32)(entry->unk38 / three) - arg0;
                dy = (f32)(entry->unk3A / three) - arg1;
                dist = sqrtf((dz * dz) + ((dx * dx) + (dy * dy)));
                    if (entry->unk38) {}  // FAKE: hcL
                if (entry->unk4 == 0) {}  // FAKE: hcL
                diff_val = dist - (f32)arg3;
                if (dist <= (f32)arg3) {
                    diff_val = 0.1f;
    if (arg6 != 0) {}  // FAKE: hcL
                }
                range = entry->unk28 / 3.0f;
                if (diff_val < range) {
                    r += entry->unk2C;
                    g += entry->unk30;
                    b += entry->unk34;
                } else {
                    max_range = ((1.0f / entry->unk24) / 3.0f) - range;
                    if ((diff_val - range) < max_range) {
                        factor = 1.0f - ((diff_val - range) / max_range);
                        r += entry->unk2C * factor;
                        if (entry->unk2C) {}  // FAKE: hcL
                        g += entry->unk30 * factor;
                        b += entry->unk34 * factor;
                    }
                }
                break;
            }
            }
        }
    }
    if (r > 1.0f) {
        r = 1.0f;
    }
    if (g > 1.0f) {
        g = 1.0f;
        if (arg0) {}  // FAKE: hcL
    }
    if (b > 1.0f) {
        b = 1.0f;
    if (arg6 && arg6) {}  // FAKE: hcL
    }
    *arg4 = (s32)(r * 255.0f);
    *arg5 = (s32)(g * 255.0f);
    if (arg1 < 0.0f) {}  // FAKE: hcL
    *arg6 = (s32)(b * 255.0f);
    if (D_807F7BC8 && D_807F7BC8) {}  // FAKE: hcL
}
