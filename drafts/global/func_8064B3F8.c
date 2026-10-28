// func_8064B3F8 (src/global/478F0.c): CsB10 stage 4: only $t1/$t9 swap (lui+lw D_807F6000 in t1 vs expected t9; sll/addu offset t9 vs t1). needs CsB10Saved{f32 v[10]} from 478F0.c above func_8064B2AC. Tried locals/idx/plus/cast variants, 27k permuter iterations min 40, deadsweep no improvement.
void func_8064B3F8(CsState *cs, s16 csId, s16 b, s16 c) {
    CsB10Saved *p = *(CsB10Saved **)cs;
    CsB0Slot *slot;
    f32 sx;
    f32 sy;
    f32 sz;

    slot = &D_807F6000[hashTableLookup(csId)];
    sx = slot->x;
    sy = slot->y;
    sz = slot->z;

    cs->unk14[c] = (p->v[0] - sx) / b;
    cs->unk14[c + 1] = (p->v[1] - sy) / b;
    cs->unk14[c + 2] = (p->v[2] - sz) / b;
}
