// modelAnimEntryBuildKeyMatrix (src/global/54150.c): stage 4: K&R park unchanged (full=93 shape=27). R13_sonnet_xhigh_3 (base 555ed2b6) FINDINGS: (1) the K&R `u32 arg1` + `*(f32*)&arg1` makes arg1 address-taken, so uopt never colours it; the target's `mov.s $f14,$f4` weight copy is a coloured SPLIT PIECE of a real `f32 arg1` (candidate 37). ANSI route: file-scope prototype `void modelAnimEntryBuildKeyMatrix(u8, f32, ModelBTrack *, u8 *, u8);` (typedefs hoisted above it), `f32 unk4` in ModelAnimEntryRaw, definition `(u8 arg0, f32 arg1, ModelBTrack *arg2, u8 *arg3, u8 arg4)`, pads q0..q2 (frame 256 needs 3 not 5); the matched caller stays identical (lw a1,4(s1)). This regime reaches full=92 shape=29 with natural c6..c8 3-statement chains, `c7 = 0;` right after `off = D_807F6BE0;` (FAKE: dead store gives c7 the lower candidate bit so c7 takes $f12 and c6 $f18 on the adjsave tie), c0 `fa = next; c0 = fa - cur; c0 *= w; c0 += cur;`, c1 `cur + (next - cur) * w`, c2 `c2 = next - cur; c2 = c2 * w + cur;` (body in .scratch/R13_sonnet_xhigh_3/ansi92_best_body.c; compiles only with that prototype/field change). (2) uopt ends a node when var refs >= 20 (`varreflimit`, uoptinput.c endblock; a `lod` of a variable is counted unless forwarded; `c *= w` after `c = a - b` counts again, killed tree); simulator .scratch/R13_sonnet_xhigh_3/cuts.py reproduces node cuts exactly: z-tail+c6+c7 = node 12, c8..c1-first = node 13, rest + switch = node 14. (3) target needs: z f16, c6 f18, c7 f12 in node 12; weight piece f14 over nodes 13-14; c1 f18 coloured, c0/c8 uncoloured, c2 f2; cur-key loads of c0,c1,c2 all `f0` - with only 2 nodes after node 12 two colour-f0 CSE candidates cannot share a node, so at least one cur load is not a coloured web: UNRESOLVED (spellings that stop uopt CSE of cur leave two loads, full 165+). Remaining diff in the 92 variant: weight piece uncoloured (node 13 is full: cur loads f0/f2/f14 + fa f12 + c0 f18 + z f16), hence no `mov.s $f14,$f4`, c8 product lands in $f10 not $f4, c0 coloured. Guards `if (X) {}` add 2 uopt nodes each but keep real code here. Searches: 729+46k form grids, 5k neighbourhood, GA over forms+dead stmts (floor 92), deadsweep from ANSI baseline (floor 107). Tools: .scratch/R13_sonnet_xhigh_3/{h,evtr,sig,sigscore,cuts,ga2}.py.  | Prior: stage 4: full=93 text=93 reloc=0 shape=27; R12_sonnet_xhigh_4 (base 564cfef3) Q0548 XBB-window survey: as1probe keep on the park, patched as1 variants limit 0/1/2/3/5/10/100 (L100 built privately from as1patch by patching `li t4,10` at 0x42ace4 to 100, built with /usr/bin/make in .scratch/R12_sonnet_xhigh_4/as1L) and jr-live, plus as1probe scan. RESULT: pure uopt FP colouring (c7 f-reg ownership, swc1 spill order), no as1 lever. Limits 0/1/2/3/5/10 all full=93 n=387; limit 100 is WORSE (108): a wider window hoists more than the target, so the stock window already matches the target's hoisting and shrinking it changes nothing; jrlive 95; scan hits are only deletes/swaps at records 387-420 and 585-594. No guard route. | Prior: stage 4: full=93 text=93 reloc=0 shape=27; R11_modelAnimEntryBuildKeyMatrix2 (base 9d6acd9d): verified stage 4 park remains closest at full=93 text=93 reloc=0 shape=27 (351/351 insns, frame 256, s0 only). Investigated uopt_trace -l5/-l6 and as1probe scan (3185 edits, best 91 via instruction deletes); confirmed mismatch is uopt candidate negative-saving decisions on c7 FP colour, c0/c2 spill lifetimes, and arg1 split copy across 9 interpolated float components, not as1 scheduling; deadsweep sweep 364 variants found no improvement; exact park form restored in .scratch/R11_modelAnimEntryBuildKeyMatrix2/54150.c; whole-file fdiff OK. | Prior: stage 4: verified whole-TU normalized full/text 93, 351/351 instructions, frame 256, s0 only, zero FAKEs. Expand c8/c0/c1/c2 subtract/multiply/add and reuse fa for the weight before c2; fixes c6/c1=f18 and arg4=v0. Remaining c7 FP colour, c0/c2 spill lifetimes and arg1 split copy. Prior FAKE-free 98 note was not reproducible: actual cleaned old draft full310/frame272. Tried interpolation stage partitions, shared result/product/delta carriers, factor copies, shared key loads, singleton struct fields, ANSI f32 signature, and 600s two-worker permuter. Reviewed best permuter coefficient-reuse hint gave no normalized improvement without its dummy goto/no-op scaffolding. Final parked fdiff OK; NON_MATCHING compilation succeeds.
typedef struct ModelBTrack {
    u8 *unk0;
    u8 *unk4;
} ModelBTrack;

typedef struct ModelBKey {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    f32 unk14;
    f32 unk18;
    f32 unk1C;
    f32 unk20;
} ModelBKey; /* 0x24 */

void matrixMakeRotationX(f32 (*)[4], f32);
void matrixMakeRotationY(f32 (*)[4], f32);
void matrixMakeRotationZ(f32 (*)[4], f32);

void modelAnimEntryBuildKeyMatrix(arg0, arg1, arg2, arg3, arg4)
u8 arg0;
u32 arg1;
ModelBTrack *arg2;
u8 *arg3;
u8 arg4;
{
    u32 off;
    f32 x;
    f32 y;
    f32 z;
    f32 c6;
    f32 c7;
    f32 c8;
    f32 c0;
    f32 c1;
    f32 c2;
    f32 fa;
    f32 fb;
    s32 q0;  // pad words: frame/home layout
    s32 q1;
    s32 q2;
    s32 q3;
    s32 q4;
    float work[4][4];
    float mtx[4][4];

    off = D_807F6BE0;
    fa = ((ModelBKey *)arg3)[arg0 + 1].unkC;
    fb = ((ModelBKey *)arg3)[arg0].unkC;
    x = fa - fb;
    if (-180.0 > x) {
        x += 360.0;
    } else if (180.0 < x) {
        x -= 360.0;
    }
    x *= (*(f32 *)&arg1);
    x += fb;
    fa = ((ModelBKey *)arg3)[arg0 + 1].unk10;
    fb = ((ModelBKey *)arg3)[arg0].unk10;
    y = fa - fb;
    if (y < -180.0) {
        y += 360.0;
    } else if (y > 180.0) {
        y -= 360.0;
    }
    y *= (*(f32 *)&arg1);
    y += fb;
    fa = ((ModelBKey *)arg3)[arg0 + 1].unk14;
    fb = ((ModelBKey *)arg3)[arg0].unk14;
    z = fa - fb;
    if (z < -180.0) {
        z += 360.0;
    } else if (180.0 < z) {
        z -= 360.0;
    }
    z *= (*(f32 *)&arg1);
    z += fb;
    c6 = ((ModelBKey *)arg3)[1 + arg0].unk18 - ((ModelBKey *)arg3)[arg0].unk18;
    c6 *= (*(f32 *)&arg1);
    c6 += ((ModelBKey *)arg3)[arg0].unk18;
    c7 = (*(f32 *)&arg1) * (((ModelBKey *)arg3)[1 + arg0].unk1C - ((ModelBKey *)arg3)[arg0].unk1C) + ((ModelBKey *)arg3)[arg0].unk1C;
    c8 = ((ModelBKey *)arg3)[arg0 + 1].unk20 - ((ModelBKey *)arg3)[arg0].unk20;
    c8 *= (*(f32 *)&arg1);
    c8 += ((ModelBKey *)arg3)[arg0].unk20;
    c0 = ((ModelBKey *)arg3)[arg0 + 1].unk0 - ((ModelBKey *)arg3)[arg0].unk0;
    c0 *= (*(f32 *)&arg1);
    c0 += ((ModelBKey *)arg3)[arg0].unk0;
    c1 = ((ModelBKey *)arg3)[arg0 + 1].unk4 - ((ModelBKey *)arg3)[arg0].unk4;
    c1 *= (*(f32 *)&arg1);
    c1 += ((ModelBKey *)arg3)[arg0].unk4;
    fa = (*(f32 *)&arg1);
    c2 = ((ModelBKey *)arg3)[arg0 + 1].unk8 - ((ModelBKey *)arg3)[arg0].unk8;
    c2 *= fa;
    c2 += ((ModelBKey *)arg3)[arg0].unk8;
    switch (arg4 & 0xF) {
    case 0:
        break;
    case 1:
        c6 *= (f32)(0.125 * (arg4 >> 4 & 0xF));
        break;
    case 2:
        c7 *= (f32)(0.125 * (arg4 >> 4 & 0xF));
        break;
    case 3:
        c8 *= (f32)(0.125 * (arg4 >> 4 & 0xF));
        break;
    case 4:
        x *= (f32)((arg4 >> 4 & 0xF) * 0.125);
        break;
    case 5:
        y *= (f32)(0.125 * (arg4 >> 4 & 0xF));
        break;
    case 6:
        z *= (f32)(((arg4 >> 4) & 0xF) * 0.125);
        break;
    case 7:
        c0 *= (f32)((arg4 >> 4 & 0xF) * 0.125);
        break;
    case 8:
        c1 *= (f32)(((arg4 >> 4) & 0xF) * 0.125);
        break;
    case 9:
        c2 *= (f32)(0.125 * (arg4 >> 4 & 0xF));
        break;
    }
    memcpy(work, arg2->unk4 + off, 0x40);
    guScaleF(mtx, c0, c1, c2);
    guMtxCatF(work, mtx, work);
    matrixMakeRotationZ(mtx, z);
    guMtxCatF(work, mtx, work);
    matrixMakeRotationY(mtx, y);
    guMtxCatF(work, mtx, work);
    matrixMakeRotationX(mtx, x);
    guMtxCatF(work, mtx, work);
    guTranslateF(mtx, c6, c7, c8);
    guMtxCatF(work, mtx, work);
    memcpy(mtx, arg2->unk4 + 0x40 + off, 0x40);
    guMtxCatF(work, mtx, work);
    guMtxF2L(work, (Mtx *)(off + arg2->unk0));
}
