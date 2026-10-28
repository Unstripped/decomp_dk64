// func_8064AC28 (src/global/478F0.c): CsNM6 stage 4 (19 insns diff, regs/webs only; frame + callee-saved set match). Cause: uopt PRE makes p+6 (loop-1 unrolled peel e=p+6 and loop-2 init e=p+6 share one value number) an expression candidate in a0 (mine: addiu a0,v1,6; move s0,a0; else path addiu a0,t0,6). Target computes addiu s0,v1,6 separately in both places and keeps p in TWO regs at the join (a0 for the part[0] timer/active stores, v1 for loop-2 base + unk4F; or a0,v1 in the flag branch, or v1,a0 in the else branch). Reproduced the target structure (4 insns diff) ONLY with a pointer q assigned in one branch and undefined in the other (invalid C); q = p in both branches is copy-propagated (19). Tried: loop forms (for/while/do, comma-for, p->part[i] index, (u8*)p+i*6), part0 via p/e/q, loop2 from i=0/1, separate e1/i1 loop vars (80), q = p at 5 positions x 4 decl positions, folded spellings of p+6 (all VN-folded), types of i/best/n/allDone/j, declaration-order hill climb (16 locals), deadsweep sweep incl. --extra p e i cs, permuter 600s -j2 (790 base, no gain).
void modelAnimEntryGetState(s16, s16, s16 *, f32 *, u8 *);
void modelAnimEntrySetTime(s16, s16, s16, f32);
void modelAnimEntrySetUnkC(s16, s16, s16);
void func_806086CC(f32, f32, f32, s16, s32, s32, s32, s32, f32, s32);
void func_8063DA40(s16, s16);
extern u8 D_8074E77C;
typedef struct CsB10Part {
    /* 0x0 */ u8 state;
    /* 0x1 */ u8 pad1;
    /* 0x2 */ s16 timer;
    /* 0x4 */ u8 active;
    /* 0x5 */ u8 pad5;
} CsB10Part;
typedef struct CsB10W {
    /* 0x00 */ u8 pad0[0x18];
    /* 0x18 */ u8 state;
    /* 0x19 */ u8 pad19;
    /* 0x1A */ s16 timer;
    /* 0x1C */ u8 active;
} CsB10W;
typedef struct CsB10Set {
    /* 0x00 */ u8 pad0[0x18];
    /* 0x18 */ CsB10Part part[9];
    /* 0x4E */ u8 unk4E;
    /* 0x4F */ u8 unk4F;
} CsB10Set;
void func_8064AC28(CsState *cs, s16 csId, s16 b, s16 c) {
    CsB10Set *p;
    CsB10W *e;
    s16 j;
    s16 anim;
    f32 animT;
    u8 animFlag;
    s32 i;
    Actor *pl;
    s32 best;
    u8 allDone = 1;
    u8 n = 0;
    f32 x;
    f32 y;
    f32 z;
    f32 d;
    f32 bestD;

    if (*(CsB10Set **)cs == NULL) {
        p = *(CsB10Set **)cs = func_80610FE8(0x50);
        p->unk4E = 0;
        if (flagGet(0x146, 0) != 0) {
            e = (CsB10W *)p;
            for (i = 0; i < 9; i++) { e->state = 3; e = (CsB10W *)((u8 *)e + 6); }
        } else {
            p->part[2].state = 2;
            p->part[5].state = 2;
            p->part[7].state = 2;
            p->part[0].state = 0;
            p->part[1].state = 3;
            p->part[3].state = 0;
            p->part[4].state = 1;
            p->part[6].state = 3;
            p->part[8].state = 1;
        }
        p->part[0].timer = 10;
        p->part[0].active = 1;
        for (i = 1, e = (CsB10W *)((u8 *)p + 6); i < 9; i++, e = (CsB10W *)((u8 *)e + 6)) {
            e->active = 1;
            e->timer = 10;
        }
        p->unk4F = 0;
    }
    p = *(CsB10Set **)cs;
    for (i = 0, e = (CsB10W *)p; i < 9; i++, e = (CsB10W *)((u8 *)e + 6)) {
        if (e->active != 0) {
            j = i + 1;
            n++;
            modelAnimEntryGetState(csId, j, &anim, &animT, &animFlag);
            if (anim == e->state && animT < 0.1 && e->timer == 0) {
                modelAnimEntrySetUnkC(csId, j, 0);
                modelAnimEntrySetTime(csId, j, anim, 0);
                e->active = 0;
                modelSlotGetNodePos(csId, 1, i + 1, &x, &y, &z);
                func_806086CC(x, y, z, 0x1AE, 0xFF, 0x7F, 0x14, 0x50, 0.7f, 0);
            }
            if (e->timer != 0) {
                e->timer--;
            }
        }
        if (e->active != 0 || e->state != 3) {
            allDone = 0;
        }
    }
    if (flagGet(0x146, 0) != 0) {
        p->unk4F = 0x14;
    }
    if (p->unk4F == 0) {
        pl = D_807FC924->unk4;
        if (pl->unk154 == 0x1C && pl->unk155[0] < 7 && D_8074E77C == 0 && pl->unk110 == 1) {
            if (csId == pl->unk10C) {
                bestD = 100000.0f;
                best = -1;
                i = 0;
                do {
                    modelSlotGetNodePos(csId, 1, i + 1, &x, &y, &z);
                    x = D_807FBB4C->unk7C - x;
                    z = D_807FBB4C->unk84 - z;
                    d = x * x + z * z;
                    if (d < bestD) {
                        best = i;
                        bestD = d;
                    }
                    i++;
                } while (i != 9);
                if (best >= 0) {
                    e = (CsB10W *)((u8 *)p + best * 6);
                    e->state++;
                    e->state %= 4;
                    e->active = 1;
                    modelAnimEntrySetUnkC(csId, best + 1, 0x19);
                    p->unk4F = 0x14;
                }
            }
        }
    }
    if (p->unk4F != 0) {
        p->unk4F--;
    }
    if (allDone != 0) {
        func_8063DA40(0xF, 0xA);
        heapFreeDeferred(*(void **)cs);
        cs->unk4B[0] = 0x28;
        *(void **)cs = NULL;
    }
}
