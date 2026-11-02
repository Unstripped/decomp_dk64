// lightSampleColorAtPosition (src/global/5E2F0.c): UNPARKED 2026-11-02: park was 406 insns vs target 407 (count-inexact parks stay drafts); Light(r5): stage 5 unchanged (text 80/shape 61, park kept). Target facts: zero web f28 hoisted and USED by dist==0, dot<0, dot=0, factor=0 (ours hoists f28 but loop uses rematerialise mtc1 zero: const web 379 uses not substituted), nx f18/ny f20 stored to 84/88 (dead stores, never reloaded) while nz stored 92 and reloaded at once, d[] at 96..104. Tried r5: function-scope nx/ny/nz in all 6 orders (no change), dead tests/inits of n* around the loop (worse 170+), nz as 1-elem array (188), 0 vs 0.0f vs (f32)0 spellings (worse), 100-gen random self-assign/dead-test hill-climb (no gain).
void lightSampleColorAtPosition(f32 arg0, f32 arg1, f32 arg2, s16 arg3, u8 *arg4, u8 *arg5, u8 *arg6, s16 arg7) {
    f32 pad[10];
    f32 d[3];
    LightTrigger *entry;
    f32 r;
    f32 g;
    f32 b;
    s32 three;
    s32 i;

    if (mapChunkIsInUse(arg7) == 0) {
        if (arg0 > 0.0f) {}  // FAKE: steers FP zero-constant web
        *arg6 = 0xFF;
        *arg5 = 0xFF;
        *arg4 = 0xFF;
        return;
    }
    if (D_807F7EC8 == 0) {
        *arg4 = (s32)(D_8076A0B4[arg7] * 255.0f);
        *arg5 = (s32)(D_8076A0B8[arg7] * 255.0f);
        if (arg6 != 0) {} // FAKE: regalloc steer (random search)
        *arg6 = (s32)(D_8076A0BC[arg7] * 255.0f);
        return;
    }
    r = D_8076A0B4[arg7];
    g = D_8076A0B8[arg7];
    b = D_8076A0BC[arg7];
    three = 3;
    for (i = 0; i < D_807F7EC8; i++) {
        {
            entry = &D_807F7BC8[i];
            switch (entry->unk3E) {
            default:
                break;
                if (arg7) {} // FAKE: regalloc steer (random search)
            case 1: {
                f32 nx;
                f32 ny;
                f32 nz;
                f32 dist;
                f32 dot;
                f32 factor;

                d[0] = arg0 - (f32)(entry->unk38 / three);
                d[1] = arg1 - (f32)(entry->unk3A / three);
                d[2] = arg2 - (f32)(entry->unk3C / three);
                dist = sqrtf((d[2] * d[2]) + ((d[0] * d[0]) + (d[1] * d[1])));
                if (dist == 0.0f) {
        if (1) {} // FAKE: regalloc steer (random search)
                    dist = 0.1f;
                }
                nz = d[2] / dist;
                nx = d[0] / dist;
                    if (r && r) {} // FAKE: regalloc steer (random search)
                ny = d[1] / dist;
                dot = (entry->unk14 * nz) + ((nx * entry->unkC) + (ny * entry->unk10));
                if (dot < 0.0f) {
                    dot = 0.0f;
                }
                if (entry->unk0 <= dot) {
                    if (entry->unk4 <= dot) {
                        factor = 1.0f;
                    } else {
                        factor = (dot - entry->unk0) * entry->unk8;
                        if (nx == 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                    }
                    if ((f64)dist > 300.0) {
                        if ((f64)dist > 1100.0) {
                            factor = 0.0f;
                        } else {
                            factor = (f64)factor * (1.0 - (((f64)dist - 300.0) / 800.0));
                        }
                    }
                    r += entry->unk2C * factor;
                    g += entry->unk30 * factor;
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
                    if (arg6 != 0) {} // FAKE: regalloc steer (random search)
                diff_val = dist - (f32)arg3;
                if (dist <= (f32)arg3) {
                    diff_val = 0.1f;
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
                        g += entry->unk30 * factor;
                        b += entry->unk34 * factor;
                        if (arg3 + 1.0f) {} // FAKE: regalloc steer (random search)
                    }
                }
                break;
                if (b != 0) {} // FAKE: regalloc steer (random search)
            }
            }
        }
    }
    if (r > 1.0f) {
        r = 1.0f;
    }
    if (g > 1.0f) {
        g = 1.0f;
    }
    if (b > 1.0f) {
        b = 1.0f;
    }
    *arg4 = (s32)(r * 255.0f);
    *arg5 = (s32)(g * 255.0f);
    if (arg6 == 0) {} // FAKE: regalloc steer (random search)
    if (D_8076A0B4 && D_8076A0B4) {} // FAKE: regalloc steer (random search)
    *arg6 = (s32)(b * 255.0f);
}
