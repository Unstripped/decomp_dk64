// func_8064A258 (src/global/478F0.c): CsNM3 stage 4 (4-line diff): only tail left: target reloads rem lo(0x64) then hi(0x60) then lbu allDone in the bnez delay slot; mine lw hi, lbu, lw lo, nop. Found: named u64 elapsed + `t->left = ...; if (t->left == 0 || allDone)` puts the spill slot at 0x60 (named s64 rem sat at 0x88-0x90); `ok |= sixth; if (e->active != 0 || ok == 0)`; for (i = 0, e = t; i < 9; i++, e += 6); trailing dead `if (allDone && allDone) {}` fixes the slot!=-1 beql/sll hoist (deadsweep with --extra allDone); pad4E store first then ascending ent[] stores fixes li t0,2. Tried: cmp forms/casts, named rem, assign-in-cond, 6 compare orders, random store perms, dead stmts.
extern u64 osGetTime(void);
typedef struct CsB9FxEnt {
    /* 0x0 */ u8 state;
    /* 0x1 */ u8 pad1;
    /* 0x2 */ s16 timer;
    /* 0x4 */ u8 active;
    /* 0x5 */ u8 pad5;
} CsB9FxEnt; /* 0x6 */
typedef struct CsB9Fx {
    /* 0x00 */ u64 last;
    /* 0x08 */ s64 duration;
    /* 0x10 */ s64 left;
    /* 0x18 */ CsB9FxEnt ent[9];
    /* 0x4E */ u8 pad4E;
    /* 0x4F */ u8 cool;
} CsB9Fx; /* 0x50 */
typedef struct CsB9FxRow {
    /* 0x00 */ u8 pad0[0x18];
    /* 0x18 */ u8 state;
    /* 0x19 */ u8 pad19;
    /* 0x1A */ s16 timer;
    /* 0x1C */ u8 active;
    /* 0x1D */ u8 pad1D;
} CsB9FxRow;
typedef struct CsB9FxSel {
    /* 0x00 */ u8 pad0[0x12];
    /* 0x12 */ u8 state;
    /* 0x13 */ u8 pad13[3];
    /* 0x16 */ u8 active;
} CsB9FxSel;
#define CsB9Sel(t, i) ((CsB9FxSel *)((u8 *)(t) + (i) * 6))
typedef struct CsB9FxView {
    /* 0x00 */ u8 pad0[0x10];
    /* 0x10 */ s16 slot;
    /* 0x12 */ u8 pad12[0x4A];
    /* 0x5C */ u8 unk5C;
    /* 0x5D */ u8 pad5D;
    /* 0x5E */ u16 unk5E;
} CsB9FxView;
extern f32 D_80770BC0[];
void modelAnimEntryGetState(s16, s16, s16 *, f32 *, u8 *);
void modelAnimEntrySetUnkC(s16, s16, s16);
void modelAnimEntrySetTime(s16, s16, s16, f32);
void func_806086CC(f32, f32, f32, s16, s32, s32, s32, s32, f32, s32);

void func_8064A258(CsState *cs, s16 csId, s16 b, s16 c) {
    s32 u1; /* unused: reserves frame slots */
    s32 sixth;
    u8 ok;
    s16 st;
    f32 frac;
    u8 spC7;
    s32 i;
    CsB9Fx *t;
    CsB9FxRow *e;
    u8 allDone;
    f32 x;
    f32 y;
    f32 z;
    u8 count;
    u8 timerRan;
    s32 g1;
    s32 g2;
    u64 elapsed;
    s32 g3;

    allDone = 1;
    timerRan = 0;
    count = 0;
    if (*(CsB9Fx **)cs == NULL) {
        t = func_80610FE8(0x50);
        *(CsB9Fx **)cs = t;
        t->pad4E = 0;
        t->ent[0].state = 0;
        t->ent[1].state = 1;
        t->ent[2].state = 3;
        t->ent[3].state = 1;
        t->ent[4].state = 2;
        t->ent[5].state = 1;
        t->ent[6].state = 3;
        t->ent[7].state = 0;
        t->ent[8].state = 1;
        for (i = 0; i != 9; i++) {
            t->ent[i].active = 1;
            t->ent[i].timer = 0x8C;
        }
        t->cool = 0;
        t->last = osGetTime();
        t->duration = 0x3C;
        t->left = 0;
        ((CsB9FxView *)cs)->slot = sfxSlotAllocateSource(csId, 0x12F, 0, 1, 0xFF, 1.0f, 0);
    }
    t = *(CsB9Fx **)cs;
    t->last += D_807445B0;
    for (i = 0, e = (CsB9FxRow *)t; i != 9; i++, e = (CsB9FxRow *)((u8 *)e + 6)) {
        if (e->active != 0) {
            count++;
            modelAnimEntryGetState(csId, i + 1, &st, &frac, &spC7);
            if (st == e->state && frac < 0.1 && e->timer == 0) {
                modelAnimEntrySetUnkC(csId, i + 1, 0);
                modelAnimEntrySetTime(csId, i + 1, st, 0);
                e->active = 0;
                modelSlotGetNodePos(csId, 1, i + 1, &x, &y, &z);
                func_806086CC(x, y, z, 0x1AE, 0xFF, 0x7F, 0x14, 0x50, 0.7f, 0);
            }
            if (e->timer != 0) {
                e->timer--;
                timerRan = 1;
            }
        }
        ok = e->state == 0;
        sixth = i == 6 && e->state == 2;
        ok |= sixth;
        if (e->active != 0 || ok == 0) {
            allDone = 0;
        }
    }
    if (timerRan != 0) {
        t->last = osGetTime();
    }
    if (((CsB9FxView *)cs)->slot != -1) {
        D_80770BC0[((CsB9FxView *)cs)->slot] = count;
        if (count == 0) {
            func_80605380(((CsB9FxView *)cs)->slot);
            ((CsB9FxView *)cs)->slot = -1;
        }
    }
    if (((CsB9FxView *)cs)->unk5C != 0 && ((CsB9FxView *)cs)->unk5E == 0x26) {
        if (CsB9Sel(t, ((CsB9FxView *)cs)->unk5C)->active == 0 && t->cool == 0) {
            CsB9Sel(t, ((CsB9FxView *)cs)->unk5C)->state++;
            CsB9Sel(t, ((CsB9FxView *)cs)->unk5C)->state = CsB9Sel(t, ((CsB9FxView *)cs)->unk5C)->state % 4;
            CsB9Sel(t, ((CsB9FxView *)cs)->unk5C)->active = 1;
            modelAnimEntrySetUnkC(csId, ((CsB9FxView *)cs)->unk5C, 0x19);
            t->cool = 5;
        }
    }
    if (t->cool != 0) {
        t->cool--;
    }
    elapsed = (osGetTime() - t->last) * 64;
    t->left = t->duration - elapsed / 3000 / 1000000;
    if (t->left == 0 || allDone) {
        heapFreeDeferred(*(CsB9Fx **)cs);
        if (allDone != 0) {
            cs->unk4B[0] = 0x28;
        } else {
            cs->unk4B[0] = 0x1E;
        }
        *(CsB9Fx **)cs = NULL;
    }
    renderCallbacksRegister(func_8068DBA4, t, 5);
    if (allDone && allDone) {
    }
}
