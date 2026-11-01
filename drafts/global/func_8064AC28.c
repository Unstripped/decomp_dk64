// func_8064AC28 (src/global/478F0.c): OlW stage 4 (unchanged, 19-28 diff lines by fv metric). Re-read target: p lives in stack home 0xA4 (sw v0,0xA4 after heapAlloc, lw v1/a0,0xA4 reload in each branch of flagGet) and each branch ends with a MIRRORED pair (flag branch: lw v1; or a0,v1; else: lw a0; or v1,a0) so a0 and v1 are two separate webs both holding p at the join (a0 = part[0] stores, v1 = loop-2 base + unk4F); both loops compute addiu s0,v1,6 separately (no PRE). Hill-climb 5400 iters of statement swaps/joins/decl swaps: no change. Needs two distinct p-valued variables whose copies are not propagated.
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

    if (*(CsEntrySet **)cs == NULL) {
        p = *(CsEntrySet **)cs = heapAlloc(0x50);
        p->unk4E = 0;
        if (flagGet(0x146, 0) != 0) {
            e = (CsEntryView *)p;
            for (i = 0; i < 9; i++) { e->state = 3; e = (CsEntryView *)((u8 *)e + 6); }
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
        for (i = 1, e = (CsEntryView *)((u8 *)p + 6); i < 9; i++, e = (CsEntryView *)((u8 *)e + 6)) {
            e->active = 1;
            e->timer = 10;
        }
        p->unk4F = 0;
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
