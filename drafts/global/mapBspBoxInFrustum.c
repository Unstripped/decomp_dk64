// mapBspBoxInFrustum (src/global/2F550.c): Stage 5 count-exact (281 insns, size 0x464, frame 0xB0), parked NON_MATCHING in Bsp copy; deadsweep score 27 (was 75). Lever: loop sums written ((x*D0 + y*D1) + z*D2) + D3 (constant LAST) and '< 0.00' spelling; fixed load order. Remaining: sp8C/sp80/sp70 slots 120/116/112 vs target 140/128/112 (target spill slots, not named homes: try removing the named sp vars, direct (f32)argN compares, then 37 sp-lines off), FP colouring (zero const f18 vs ours f16; loop temps f12/f14/f2).
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
        if (((((ClipPlane *)arg10)[i].unk20 * arg0 + ((ClipPlane *)arg10)[i].unk28 * arg1) + ((ClipPlane *)arg10)[i].unk30 * arg2) + ((ClipPlane *)arg10)[i].unk38 < 0.00) {
            in1 = 1;
            if (in1 == 0.0f) {}  // FAKE: dead test steering FP/int candidate order
        }
        if (((((ClipPlane *)arg10)[i].unk20 * arg0 + ((ClipPlane *)arg10)[i].unk28 * arg4) + ((ClipPlane *)arg10)[i].unk30 * arg2) + ((ClipPlane *)arg10)[i].unk38 < 0.00) {
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
