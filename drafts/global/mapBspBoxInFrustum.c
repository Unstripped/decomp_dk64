// mapBspBoxInFrustum (src/global/2F550.c): stage 3: 8 corner tests rewritten as ONE && chain (target is a single chain returning 0), D3 + ((a*D0 + b*D1) + c*D2) < 0.0 each; 289 vs 281 insns, frame 0xB8 vs 0xB0 (was 283/0xD0). Target: sp8C/sp80/sp70 f32 memory locals at 0x8C/0x80/0x70 (y,z store then reload via lwc1, x first used from fa1 and stored later in a bc1f delay slot), D[0..3] in f16/fs0/fs3/f2, saves fs0-fs3 (f20-f26) used by the first block AND by the loop's hoisted cvt.d.w of arg0/1/2/4; mine uses only f20-f24, stores sp8C/sp70 twice and spills 4 extra temps (slots 0x70/0x6C/0xB0/0xC0); mul/add operand order also differs from target (D2*z vs z*D2: sp70/sp80 must NOT be value-numbered; volatile on all 3 gives frame 0x78/296 insns, volatile on y/z only 298/0x90). Later half (clip loop, calls) already near-identical
f32 boxMinCornerDistance(s16, s16, s16, s16, s16, s16, f32, f32, f32);
s32 clipPolyToBox(s32, s16, s16, s16, s16, s16, s16, void *);

s32 mapBspBoxInFrustum(s16 arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5, f32 arg6, f32 arg7, f32 arg8, f32 arg9, void *arg10) {
    f32 sp8C;
    f32 sp80;
    f32 sp70;
    s32 in1;
    s32 in2;
    s32 behind;
    s32 i;

    sp8C = arg0;
    sp80 = arg1;
    sp70 = arg2;
    if (D_807F5E50[3] + ((sp8C * D_807F5E50[0] + sp80 * D_807F5E50[1]) + sp70 * D_807F5E50[2]) < 0.0 &&
        D_807F5E50[3] + ((sp8C * D_807F5E50[0] + sp80 * D_807F5E50[1]) + arg5 * D_807F5E50[2]) < 0.0 &&
        D_807F5E50[3] + ((sp8C * D_807F5E50[0] + arg4 * D_807F5E50[1]) + sp70 * D_807F5E50[2]) < 0.0 &&
        D_807F5E50[3] + ((sp8C * D_807F5E50[0] + arg4 * D_807F5E50[1]) + arg5 * D_807F5E50[2]) < 0.0 &&
        D_807F5E50[3] + ((arg3 * D_807F5E50[0] + sp80 * D_807F5E50[1]) + sp70 * D_807F5E50[2]) < 0.0 &&
        D_807F5E50[3] + ((arg3 * D_807F5E50[0] + sp80 * D_807F5E50[1]) + arg5 * D_807F5E50[2]) < 0.0 &&
        D_807F5E50[3] + ((arg3 * D_807F5E50[0] + arg4 * D_807F5E50[1]) + sp70 * D_807F5E50[2]) < 0.0 &&
        D_807F5E50[3] + ((arg3 * D_807F5E50[0] + arg4 * D_807F5E50[1]) + arg5 * D_807F5E50[2]) < 0.0) {
        return 0;
    }
    in1 = 0;
    in2 = 0;
    behind = 0;
    if (sp8C <= arg6 && arg6 <= (f32)arg3 && sp80 <= arg7 && arg7 <= (f32)arg4 && sp70 <= arg8 && arg8 <= (f32)arg5) {
        return 1;
    }
    for (i = 0; i < 5 && behind == 0; i++) {
        if (((ClipPlane *)arg10)[i].unk38 + ((((ClipPlane *)arg10)[i].unk20 * arg0 + ((ClipPlane *)arg10)[i].unk28 * arg1) + ((ClipPlane *)arg10)[i].unk30 * arg2) < 0.0) {
            in1 = 1;
        }
        if (((ClipPlane *)arg10)[i].unk38 + ((((ClipPlane *)arg10)[i].unk20 * arg0 + ((ClipPlane *)arg10)[i].unk28 * arg4) + ((ClipPlane *)arg10)[i].unk30 * arg2) < 0.0) {
            in2 = 1;
        }
        if (in1 != 0 && in2 != 0) {
            behind = 1;
        }
    }
    if (behind == 0 && boxMinCornerDistance(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8) < arg9) {
        return 1;
    }
    for (i = 0; i < 5; i++) {
        if (clipPolyToBox(i, arg0, arg1, arg2, arg3, arg4, arg5, arg10) != 0) {
            return 1;
        }
    }
    return 0;
}
