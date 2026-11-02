// mapBspBoxInFrustum (src/global/2F550.c): Stage 5 (was 3), diff 75, frame 0xB0 matches, 283 vs 285 lines, shape diff 10: chain written as ((x*D0 + y*D1) + z*D2) + D3 with (f32)arg casts (not named sp vars) in the 8 corner tests, 6 dead assigned s32 pads (frame +24 = target), 3 loop dead tests. Remaining: FP colouring (target zero const f0 first, then n3 f2, z0n2 f12, x0 f14, n0 f16, x0n0 f18; ours zero last f18) + x0/y0/z0 home offsets (target 140/128/112, ours 120/116/112).
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
    s32 pd0;
    s32 pd1;
    s32 pd2;
    s32 pd3;
    s32 pd4;
    s32 pd5;

    pd0 = 0;  // FAKE: dead pad, grows frame by a word
    pd1 = 0;  // FAKE: dead pad, grows frame by a word
    pd2 = 0;  // FAKE: dead pad, grows frame by a word
    pd3 = 0;  // FAKE: dead pad, grows frame by a word
    pd4 = 0;  // FAKE: dead pad, grows frame by a word
    pd5 = 0;  // FAKE: dead pad, grows frame by a word
    sp8C = arg0;
    sp80 = arg1;
    sp70 = arg2;
    if ((((f32)arg0 * D_807F5E50[0] + (f32)arg1 * D_807F5E50[1]) + (f32)arg2 * D_807F5E50[2]) + D_807F5E50[3] < 0.0 &&
        (((f32)arg0 * D_807F5E50[0] + (f32)arg1 * D_807F5E50[1]) + arg5 * D_807F5E50[2]) + D_807F5E50[3] < 0.0 &&
        (((f32)arg0 * D_807F5E50[0] + arg4 * D_807F5E50[1]) + (f32)arg2 * D_807F5E50[2]) + D_807F5E50[3] < 0.0 &&
        (((f32)arg0 * D_807F5E50[0] + arg4 * D_807F5E50[1]) + arg5 * D_807F5E50[2]) + D_807F5E50[3] < 0.0 &&
        ((arg3 * D_807F5E50[0] + (f32)arg1 * D_807F5E50[1]) + (f32)arg2 * D_807F5E50[2]) + D_807F5E50[3] < 0.0 &&
        ((arg3 * D_807F5E50[0] + (f32)arg1 * D_807F5E50[1]) + arg5 * D_807F5E50[2]) + D_807F5E50[3] < 0.0 &&
        ((arg3 * D_807F5E50[0] + arg4 * D_807F5E50[1]) + (f32)arg2 * D_807F5E50[2]) + D_807F5E50[3] < 0.0 &&
        ((arg3 * D_807F5E50[0] + arg4 * D_807F5E50[1]) + arg5 * D_807F5E50[2]) + D_807F5E50[3] < 0.0) {
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
            if (in1 == 0.0f) {}  // FAKE: dead test steering FP/int candidate order
        }
        if (((ClipPlane *)arg10)[i].unk38 + ((((ClipPlane *)arg10)[i].unk20 * arg0 + ((ClipPlane *)arg10)[i].unk28 * arg4) + ((ClipPlane *)arg10)[i].unk30 * arg2) < 0.0) {
            in2 = 1;
            if (arg9 > 0.0f) {}  // FAKE: dead test steering FP candidate order
        }
        if (in1 != 0 && in2 != 0) {
            behind = 1;
            if (arg4 > 0.0f) {}  // FAKE: dead test steering FP candidate order
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
