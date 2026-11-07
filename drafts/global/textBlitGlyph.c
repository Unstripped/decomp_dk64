// textBlitGlyph (src/global/100180.c): stage 6: full=60 text=60 reloc=0 shape=0 n=161 (was stage 5 full=62 shape=22); park in src updated. Frame 0x50, spill slot 28(sp), uopt colouring, schedule and return sequence are exact; the ENTIRE remaining diff is ugen scratch-ring names ($t6-$t9) from the loop header on. Key structure: u8 phaseBit/oddBit mask locals (their store narrowings burn ring temps exactly like the target entry), no bool locals (tests spell (phaseBit != 0) so all phase tests share the v0 uneq candidate), return ((phaseBit != 0) && oddBit) + arg1 + (u32)arg0 (the && hidden temp + s32 pad = 32 bytes of cfe locals -> spill at -52), tail arm1 compound *dst |= *src << 4 (dst loaded first), dstRow = (u8 *)(arg6 * 16 + arg1) + arg6 * arg4. RING MODEL (verified with 0 mismatches over whole-function ugen listings of 3 variants, script .scratch/argon/tbg/fifo.py): ugen allocates $14/$15/$24/$25 from a FIFO free list (alloc = front, frees appended in operand order at last use). Inverting the target final asm: the loop arm needs queue [25,24,14,15] at $33 and the tail arm [24,25,15,14], while both headers narrow into the FIFO front ($14 / $15). HYPOTHESIS, not established: if the target's ugen emitted these instructions in the same order and blocks as ours (unverified: as1 hoists across blocks, Q0548, fills delay slots, e.g. j++ sits in arm1's beqz slot, and renames), FIFO would need one extra alloc+free after each header narrowing plus queue [14,15,25,24] at $32 (ours [25,15,24,14]); a different ugen order/placement of the visible instructions would explain the same final asm. Next step: map as1 provenance on our own t.s vs final asm for the loop header/arm1 and tail blocks before searching for a hidden-event construct again. Ruled out: extra narrowings (dn1-dn6: as1 collapses the header to one andi), s16/u16/s8 low-bit locals (sll/sra stay visible), low-bit in reused u8 locals, assignment-in-condition, for/while/do inner-loop forms (canonicalised), 315+126+728 entry statement orders, 45 entry-tail spellings, 7 dstRow spellings (arg4-product-first gives [14,15,..] at $32 but moves visible entry regs). Permuter 1500 s -j3 best = this body.
s32 textBlitGlyph(u8 arg0, s32 arg1, s32 arg2, s16 arg3, u8 arg4, s8 *arg5, u8 arg6) {
    u8 *srcRow;
    u8 *dst;
    s16 j;
    s16 row;
    u8 *src;
    u8 phaseBit;
    u8 oddBit;
    u8 *dstRow;
    s32 pad;
    src = (u8 *)arg2;
    srcRow = (u8 *)arg2 + (arg3 >> 1);
    oddBit = arg0 & 1;
    phaseBit = *(u8 *)arg5 & 1;
    dstRow = (u8 *)(arg6 * 16 + arg1) + arg6 * arg4;
    *(u8 *)arg5 = *(u8 *)arg5 + arg0;
    arg0 >>= 1;
    dst = dstRow;
    for (row = 0; row < 0x10; row++) {
        j = 0;
        if (arg0 > 0) {
            arg4 = arg3 & 1;
            do {
                if (arg4 && !(phaseBit != 0)) {
                    *dst |= *src++ << 4;
                    *dst++ |= (*src & 0xF0) >> 4;
                } else if (arg4 && (phaseBit != 0)) {
                    *dst |= *src++ & 0xF;
                    dst++;
                    *dst |= *src & 0xF0;
                } else if (arg4 == 0 && (phaseBit != 0)) {
                    *dst++ |= (*src & 0xF0) >> 4;
                    *dst |= *src++ << 4;
                } else {
                    *dst++ |= *src++;
                }
                j++;
            } while (j < arg0);
        }
        srcRow += 0x100;
        if (oddBit) {
            arg4 = arg3 & 1;
            if (arg4 && !(phaseBit != 0)) {
                *dst |= *src << 4;
            } else if (arg4 && (phaseBit != 0)) {
                *dst |= *src << 4;
            } else if (arg4 == 0 && (phaseBit != 0)) {
                *dst |= (*src & 0xF0) >> 4;
            } else {
                *dst |= *src;
            }
        }
        dstRow -= arg6;
        src = srcRow;
        dst = dstRow;
    }
    return ((phaseBit != 0) && oddBit) + arg1 + (u32)arg0;
}
