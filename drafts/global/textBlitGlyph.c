// textBlitGlyph (src/global/100180.c): BlitGlyph (base 0475d51c), stage 5/6: no improved C; retained full62/text62/reloc0/shape22, 161/161 instructions, frame0x50 and s0-s3. Whole-file plain-C fdiff remains Section .text mismatch (9312/9312 bytes), CURRENT(2737); final .scratch/BlitGlyph/100180.c restored exact base park and fdiff OK. L5 candidate map: phase bit13/adjsave41.625 -> v0, odd45/1.3333 -> v1 (both 23 interfering neighbors, constrained); unconstrained src0/193.875 -> t0, srcRow5/3.875 -> t1, phase-byte cvt18/3 -> t2, w2var23/13.875 -> t3, arg0cvt27/4 -> t4, shift28/3 -> t5, dstRow30/3.875 -> s0, arg6var34/1.25 -> s1, dst49/286.375 -> s2, row57/3.875 -> s3. Raw AND bits19 and47 are not separate colored live ranges in baseline. Target raw-mask t2/t4 ownership therefore requires genuinely changed candidate construction, not priority-only tuning. Ugen source eval.p: Ustr3017-3040 passes destination hint; immediate binary3919-3926 forwards it; shared-node2681-2683 discards hint; eval2/1680-1688 evaluates children without hint. Raw masks + in-place arg0 shift + normalized return recreate t4 phase-mask/t5 byte and single sltu v0 (full141/shape14/n160), but false phase==0 tests continue to use raw mask while true tests use normalized value, extending both lifetimes and miscoloring width/v1, src/t1, srcRow/t2, oddBool/t0; spill24 not28. No successful inverse-sharing route: nested !/==0, deferred local zero, no-code integer wrappers collapse; u8 bool cast retains two real andi (full130/n162). Rejected coordinated operand-kill carriers (full188-221), raw/normalized flag signedness and width (141-244), raw-mask no-CFG zero-product reuse (143-220), witness+width mutation (146-153), arg4 narrowing-before-mask chain (127/n158; coordinated 127-244). No new externs or header edits. Evidence .scratch/BlitGlyph/as1-{base,raw,boolcast,kill}/ and .scratch/trace/.scratch_BlitGlyph_{100180,raw-whole}.list.
Matcher8 stage 5: improved full79/text79/reloc0/shape23 to full62/text62/reloc0/shape22, expected/got161 instructions, frame80 with s0-s3. Base 5937b87d0f81c5da18c52ccd9f3c872eee7ca511. Private park .scratch/Matcher8-textBlitGlyph/100180.c; plain C .scratch/Matcher8-textBlitGlyph/plain-best62.c. Reuse consumed u8 arg4 as the per-row low-bit flag (removes lead local), fixing both shared spill homes 24(sp)->28(sp) and alone improving 79->78. Spell the first odd-width tail update as *dst = *dst | (*src << 4), not compound |=: this changes ugen temporary allocation across the following branches and gives text62 with no FAKEs or signature changes. Entry scheduling/Boolean-width lowering and scratch-register differences remain. Plain-C fdiff: FAILED: Section .text content mismatch (built: 9312 bytes, expected: 9312 bytes), CURRENT(2737). New dead ends: reusing arg2 as j/ret/srcRow; counter-return reuse; coordinated explicit u8/s8/s16 casts on Boolean/mask/width expressions; a single width local before and after arg0 narrowing; named/reused raw phase-byte loads; actual int/unsigned int/char locals; source/destination pointer signature variants; K&R signatures with/without prototype; narrow raw flags normalized at return. All failed to beat text78 before the explicit-store discovery. Completed permute.py -j2 --seconds600 (33k iterations), rescored all 84 outputs plus label-removal and arg4-reuse variants with deadsweep; weighted permuter best1787 is not best normalized target score. Artificial repeated masks and unused labels rejected (best54 needs eleven redundant &0xff masks plus a carrier). Natural full-assignment first tail branch yields62; exhaustive 16 tail-store forms and 128 inner-store expansion combinations found no better candidate. Prior SlotTex2: as1 deletion scans invalid; label-only schedule fix lacked a C route; uopt trace plus raw/masked/normalized flags, return forms, pointer/shift forms, flag types, coordinated carriers, isolated first-param narrowing, and entry statement order did not improve79. Keep these dead ends; do not repeat.
Finisher2b (base 82b768fd2cde4792d240c55bf4f4cd4bc3e0be85): retained full62 stage-5 park. Boolean odd alone is full71/163 rows; unsigned narrowed width full101/frame72; parameter halving plus both raw-mask witnesses full166/frame64. Witnesses preserve raw masks but do not preserve the constrained/unconstrained graph or saved set. No improved C retained. Evidence: .scratch/Finisher2b-textBlitGlyph/*-score.txt and raw-mask-l5.txt; final private park fdiff OK.
s32 textBlitGlyph(u8 arg0, s32 arg1, s32 arg2, s16 arg3, u8 arg4, s8 *arg5, u8 arg6) {
    u8 *srcRow;
    u8 *dst;
    s16 j;
    s16 row;
    u8 *src;
    s32 phase;
    s32 w2;
    u8 *dstRow;
    s32 ret;
    s32 odd;
    src = (u8 *)arg2;
    srcRow = (u8 *)(arg2 + (arg3 >> 1));
    phase = (*(u8 *)arg5 & 1) != 0;
    w2 = arg0 >> 1;
    dstRow = (u8 *)arg1 + arg6 * 16 + arg6 * arg4;
    odd = arg0 & 1;
    dst = dstRow;
    *(u8 *)arg5 = *(u8 *)arg5 + arg0;
    arg0 = w2;
    for (row = 0; row < 0x10; row++) {
        j = 0;
        if (w2 > 0) {
            arg4 = arg3 & 1;
            do {
                if (arg4 && phase == 0) {
                    *dst |= *src++ << 4;
                    *dst++ |= (*src & 0xF0) >> 4;
                } else if (arg4 && phase != 0) {
                    *dst |= *src++ & 0xF;
                    dst++;
                    *dst |= *src & 0xF0;
                } else if (arg4 == 0 && phase != 0) {
                    *dst++ |= (*src & 0xF0) >> 4;
                    *dst |= *src++ << 4;
                } else {
                    *dst++ |= *src++;
                }
                j++;
            } while (j < w2);
        }
        srcRow += 0x100;
        if (odd != 0) {
            arg4 = arg3 & 1;
            if (arg4 && phase == 0) {
                *dst = *dst | (*src << 4);
            } else if (arg4 && phase != 0) {
                *dst |= *src << 4;
            } else if (arg4 == 0 && phase != 0) {
                *dst |= (*src & 0xF0) >> 4;
            } else {
                *dst |= *src;
            }
        }
        dstRow -= arg6;
        src = srcRow;
        dst = dstRow;
    }
    ret = phase;
    if (phase != 0) {
        ret = odd;
    }
    return ret + arg1 + arg0;
}
