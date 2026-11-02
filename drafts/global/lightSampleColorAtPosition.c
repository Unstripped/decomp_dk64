// lightSampleColorAtPosition (src/global/5E2F0.c): Light(u6): stage 4 (count 404=404, frame 136, 48/48 blocks, f20-f30 saved set identical), deadsweep score full 109 text 98 shape 50 (reloc 8). Structure: case1 locals nx,ny,nz,dx,dy,dz scalars declared n-first; 4x 'if (D_807F7EC8 == 0) {}' at loop head raise static block count so uopt's d-values flip from callee-saved f20-f24 to caller-saved with spills around sqrtf (matches target stores before jal). Remaining: spill slots 84/88/92 vs target 96/100/104, n-value stores at 84/88/92 missing, dead hoisted zero in f22 (r lands f30), 300.0 not hoisted, first D_807F7EC8==0 branch reg order (lw t7 vs v1).
void lightSampleColorAtPosition(f32 arg0, f32 arg1, f32 arg2, s16 arg3, u8 *arg4, u8 *arg5, u8 *arg6, s16 arg7) {
    f32 pad[1];
    LightTrigger *entry;
    f32 r;
    f32 g;
    f32 b;
    s32 three;
    s32 i;

    if (mapChunkIsInUse(arg7) == 0) {
        *arg6 = 0xFF;
        *arg5 = 0xFF;
        *arg4 = 0xFF;
        return;
    }
    if (D_807F7EC8 == 0) {
        *arg4 = (s32)(D_8076A0B4[arg7] * 255.0f);
        *arg5 = (s32)(D_8076A0B8[arg7] * 255.0f);
        if (D_8076A0BC && D_8076A0BC) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
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
            if (g == 0) {}  // FAKE: hcL
            switch (entry->unk3E) {
            default:
                break;
            case 1: {
                f32 nx;
                f32 ny;
                f32 nz;
                f32 dx;
                f32 dy;
                f32 dz;
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
