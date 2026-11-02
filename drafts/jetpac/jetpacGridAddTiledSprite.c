// jetpacGridAddTiledSprite (src/jetpac/1460.c): W3SchedB R5: unchanged stage 6 (4 lines). Stream facts: record type 0x30 = '.noalias', 0x31 = '.alias' (w1 low16 0x2e74 = $23,$sp). Any stream with the in-loop '.alias' present and NO '.noalias' between it and the post-inc sw gives full 0 (the '.alias' can sit anywhere before the sw, even before the loop lw); removing all 4 or only the later pair gives 17/4. Mini-TU study (.scratch/W3SchedB/m/*.c, mini2.py): ugen ALWAYS emits '.alias reg,$sp' after a conditional branch that leaves the OUTERMOST loop (return/goto out; a break to an outer loop or a forward if inside the loop does not), and ALWAYS re-emits '.noalias reg,$sp' before the first memory op through that reg afterwards (load or store); tried return/goto/else-return/post-inc forms (q1-q9, s1-s7, g1-g5): no C form skips the re-emit. Inserting '.loc' records near the sw does not help (tj_loc.py). Hypothesis: the original's store base register is not a ugen-tracked pointer at that point (not the same lda web as the guard load). || PREVIOUS: jetpacGridAddTiledSprite (src/jetpac/1460.c): stage 6: 129 insns, 1 pair diff (4 lines): target 'addiu t8,v0,1; sw t8,0(s7); lw t9,80(sp)' vs ours 'lw t9,80(sp); addiu; sll t4; sw'. as1probe: ugen emits '.noalias $23,$sp' (rec before the post-inc sw, re-emitted after a '.alias $23,$sp' that follows the in-loop bge); dropping ONLY that rec (keeping .alias) gives full=0, dropping the .alias too gives 4. Tried (Jet, leftovers5 w2): 26k-compile hill-climb of self-assign/|0 no-code defs + line joins at every statement boundary (no gain), 10 spellings of the post-inc dst statement (ya=D_80045BD0++, split, e/f/g/h/i forms), cond spellings (>0xFF, !(<), u32 cast), 6 struct-copy spellings, local counter pointer (144 insns), dropping each dead test subset (only first '!h' and '!ya' tests needed). All keep the noalias before the sw.
typedef struct {
    s32 unk0;
    u8 pad4[6];
    s16 unkA;
    s16 unkC;
    u8 padE[2];
    s16 unk10;
    s16 unk12;
    u8 pad14[4];
} J1aSprite;

extern J1aSprite D_80042BD0[][256];
extern u8 D_807444FC;
extern s32 D_80045BD0;
typedef struct {
    u8 pad0[0x18];
} JetpacSprite;
void jetpacGridAddSprite(JetpacSprite *arg0, s32 arg1, s32 arg2, u8 *arg3, s32 arg4);

void jetpacGridAddTiledSprite(JetpacSprite *arg0, s32 arg1, s32 arg2, u8 *arg3, s32 arg4) {
    s32 ya;
    s32 h;
    s32 xd;
    J1aSprite *dst;
    s32 w;
    s32 dy;
    s32 yEnd;
    s32 dx;
    s32 xEnd;

    w = ((J1aSprite *)arg0)->unkA - 1;
    h = ((J1aSprite *)arg0)->unkC - 1;

    if (D_80045BD0 < 0x100) {
        if (arg1 < 0) {
            arg1 += 0x100;
        }
        dy = 0;
        yEnd = arg2;
        if (h > 0) {
            do {
                yEnd += 8;
                yEnd &= 0xFFF8;
                yEnd -= arg2;
                dx = 0;
                xEnd = arg1;
                if (yEnd >= h) {
                    if (!h) {
                    }
                    yEnd = h;
                    if (!h) {
                    }
                }
                if (w > 0) {
                    do {
                        if (D_80045BD0 >= 0x100) {
                            return;
                        }
                        dst = &D_80042BD0[D_807444FC][D_80045BD0++];
                        *dst = *(J1aSprite *)arg0;
                        xEnd += 8;
                        xEnd &= 0xFFF8;
                        xEnd -= arg1;
                        if (xEnd >= w) {
                            xEnd = w;
                        }
                        if (arg4 != 0) {
                            dst->unk10 = dst->unk10 + w - xEnd;
                        } else {
                            dst->unk10 = dst->unk10 + dx;
                        }
                        dst->unk12 = dst->unk12 + dy;
                        dst->unkA = xEnd - dx + 1;
                        dst->unkC = yEnd - dy + 1;
                        ya = arg2 + dy;
                        xd = arg1 + dx;
                        if (xd >= 0x100) {
                            xd -= 0x100;
                        }
                        jetpacGridAddSprite((JetpacSprite *)dst, xd, ya, arg3, arg4);
                        dx = xEnd;
                        xEnd = xEnd + arg1;
                        if (!w) {
                        }
                        if (!w) {
                        }
                    } while (dx < w);
                    if (!ya) {
                    }
                    if (!yEnd) {
                    }
                }
                dy = yEnd;
                yEnd = yEnd + arg2;
            } while (dy < h);
        }
    }
}
