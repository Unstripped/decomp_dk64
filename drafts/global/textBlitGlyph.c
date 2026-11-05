// textBlitGlyph (src/global/100180.c): SlotTex2 stage 5, unchanged best: full79 text79 reloc0 shape23, expected/got161 instructions, frame80 with s0-s3. Entry scheduling/Boolean-width lowering and temporary-ring rotations remain; generated shared spill24(sp) versus target28(sp). Plain-C fdiff: FAILED: Section .text content mismatch (built: 9312 bytes, expected: 9312 bytes). Began with as1probe keep and scan --rounds3: greedy instruction deletions reduce score but remove required work/count, rejected. Separate nondeleting scan --rounds3 only improves via a prologue label (insert16:label ->75/shape33/n161); no directly emit-able useful C scheduling route. Uopt5 inspected candidate ordering/live ranges. Tried Boolean raw/masked/normalized representations, return-expression variants, pointer/shift spellings, flag widths, coordinated mask carriers, and isolated explicit first-parameter narrowing; none improved exact-count baseline. No signature changes retained. Permuter -j2 --seconds600 was started, then cancelled at orchestrator wrap-up request; no validated result adopted. No new searches started after request. Private copy .scratch/SlotTex2/100180.c restored to original NON_MATCHING park and plain fdiff prints OK (assembly-backed, not C match). Previous spill/candidate-order findings remain valid.
s32 textBlitGlyph(u8 arg0, s32 arg1, s32 arg2, s16 arg3, u8 arg4, s8 *arg5, u8 arg6) {
    u8 *srcRow;
    u8 *dst;
    u8 lead;
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
            lead = arg3 & 1;
            do {
                if (lead && phase == 0) {
                    *dst |= *src++ << 4;
                    *dst++ |= (*src & 0xF0) >> 4;
                } else if (lead && phase != 0) {
                    *dst |= *src++ & 0xF;
                    dst++;
                    *dst |= *src & 0xF0;
                } else if (lead == 0 && phase != 0) {
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
            lead = arg3 & 1;
            if (lead && phase == 0) {
                *dst |= *src << 4;
            } else if (lead && phase != 0) {
                *dst |= *src << 4;
            } else if (lead == 0 && phase != 0) {
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
