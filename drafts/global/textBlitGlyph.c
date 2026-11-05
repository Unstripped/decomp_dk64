// textBlitGlyph (src/global/100180.c): Matcher8 stage 5: improved full79/text79/reloc0/shape23 to full62/text62/reloc0/shape22, expected/got161 instructions, frame80 with s0-s3. Base 5937b87d0f81c5da18c52ccd9f3c872eee7ca511. Private park .scratch/Matcher8-textBlitGlyph/100180.c; plain C .scratch/Matcher8-textBlitGlyph/plain-best62.c. Reuse consumed u8 arg4 as the per-row low-bit flag (removes lead local), fixing both shared spill homes 24(sp)->28(sp) and alone improving 79->78. Spell the first odd-width tail update as *dst = *dst | (*src << 4), not compound |=: this changes ugen temporary allocation across the following branches and gives text62 with no FAKEs or signature changes. Entry scheduling/Boolean-width lowering and scratch-register differences remain. Plain-C fdiff: FAILED: Section .text content mismatch (built: 9312 bytes, expected: 9312 bytes), CURRENT(2737). New dead ends: reusing arg2 as j/ret/srcRow; counter-return reuse; coordinated explicit u8/s8/s16 casts on Boolean/mask/width expressions; a single width local before and after arg0 narrowing; named/reused raw phase-byte loads; actual int/unsigned int/char locals; source/destination pointer signature variants; K&R signatures with/without prototype; narrow raw flags normalized at return. All failed to beat text78 before the explicit-store discovery. Completed permute.py -j2 --seconds600 (33k iterations), rescored all 84 outputs plus label-removal and arg4-reuse variants with deadsweep; weighted permuter best1787 is not best normalized target score. Artificial repeated masks and unused labels rejected (best54 needs eleven redundant &0xff masks plus a carrier). Natural full-assignment first tail branch yields62; exhaustive 16 tail-store forms and 128 inner-store expansion combinations found no better candidate. Prior SlotTex2: as1 deletion scans invalid; label-only schedule fix lacked a C route; uopt trace plus raw/masked/normalized flags, return forms, pointer/shift forms, flag types, coordinated carriers, isolated first-param narrowing, and entry statement order did not improve79. Keep these dead ends; do not repeat.
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
