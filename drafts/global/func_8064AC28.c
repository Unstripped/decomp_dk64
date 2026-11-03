// func_8064AC28 (src/global/478F0.c): W3CountB 2026-11-02: PARKED stage 4, count-exact 340/340 (was 338), frame same, deadsweep full 13 (shape 7). Lever: extra pointer local q declared LAST (keeps every home offset) with 'q = p;' copies and q reads in the else arm / loop-2 init / unk4F (legal: q assigned on all paths before use; a q declared after p shifts the byte homes by 4). Remaining diff: q is callee-saved (move s2,v0) instead of the target's v1/a0 pair of p webs (lw v1; move a0,v1 / lw a0; move v1,a0).
void csModelStateSetFirstByte(s16, s16);
extern u8 gPlayerCharacterId;
typedef struct CsEntry {
    /* 0x0 */ u8 state;
    /* 0x1 */ u8 pad1;
    /* 0x2 */ s16 timer;
    /* 0x4 */ u8 active;
    /* 0x5 */ u8 pad5;
} CsEntry;
typedef struct CsEntryView {
    /* 0x00 */ u8 pad0[0x18];
    /* 0x18 */ u8 state;
    /* 0x19 */ u8 pad19;
    /* 0x1A */ s16 timer;
    /* 0x1C */ u8 active;
} CsEntryView;
typedef struct CsEntrySet {
    /* 0x00 */ u8 pad0[0x18];
    /* 0x18 */ CsEntry part[9];
    /* 0x4E */ u8 unk4E;
    /* 0x4F */ u8 unk4F;
} CsEntrySet;
void func_8064AC28(CsState *cs, s16 csId, s16 b, s16 c) {
    CsEntrySet *p;
    CsEntryView *e;
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
    CsEntrySet *q;

    if (*(CsEntrySet **)cs == NULL) {
        p = *(CsEntrySet **)cs = heapAlloc(0x50);
        q = p; // FAKE: second web of p (copy kept, steers uopt colouring and count)
        q->unk4E = 0; // FAKE: reads the q copy of p
        if (flagGet(0x146, 0) != 0) {
            e = (CsEntryView *)((u32)p | 0); // FAKE: blocks copy-propagation of e = p (stops uopt PRE'ing p + 6 into both arms)
            for (i = 0; i < 9; i++) { e->state = 3; e = (CsEntryView *)((u8 *)e + 6); }
        } else {
            p->part[2].state = 2;
        q = p; // FAKE: second web of p (copy kept, steers uopt colouring and count)
            q->part[5].state = 2; // FAKE: reads the q copy of p
            p->part[7].state = 2;
            q->part[0].state = 0; // FAKE: reads the q copy of p
            q->part[1].state = 3; // FAKE: reads the q copy of p
            p->part[3].state = 0;
            p->part[4].state = 1;
            q->part[6].state = 3; // FAKE: reads the q copy of p
        q = p; // FAKE: second web of p (copy kept, steers uopt colouring and count)
            q->part[8].state = 1; // FAKE: reads the q copy of p
        }
        p->part[0].timer = 10;
        p->part[0].active = 1;
        for (i = 1, e = (CsEntryView *)((u8 *)p + 6); i < 9; i++, e = (CsEntryView *)((u8 *)e + 6)) {
            e->active = 1;
            e->timer = 10;
        }
        q->unk4F = 0; // FAKE: reads the q copy of p
    }
    p = *(CsEntrySet **)cs;
    for (i = 0, e = (CsEntryView *)p; i < 9; i++, e = (CsEntryView *)((u8 *)e + 6)) {
        if (e->active != 0) {
            j = i + 1;
            n++;
            modelAnimEntryGetState(csId, j, &anim, &animT, &animFlag);
            if (anim == e->state && animT < 0.1 && e->timer == 0) {
                modelAnimEntrySetUnkC(csId, j, 0);
                modelAnimEntrySetTime(csId, j, anim, 0);
                e->active = 0;
                modelSlotGetNodePos(csId, 1, i + 1, &x, &y, &z);
                sfxPlayAtPositionPooled(x, y, z, 0x1AE, 0xFF, 0x7F, 0x14, 0x50, 0.7f, 0);
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
        pl = gPlayerSlots->unk4;
        if (pl->unk154 == 0x1C && pl->unk155[0] < 7 && gPlayerCharacterId == 0 && pl->unk110 == 1) {
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
                    e = (CsEntryView *)((u8 *)p + best * 6);
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
        csModelStateSetFirstByte(0xF, 0xA);
        heapFreeDeferred(*(void **)cs);
        cs->unk4B[0] = 0x28;
        *(void **)cs = NULL;
    }
}
