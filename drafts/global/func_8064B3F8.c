// func_8064B3F8 (src/global/478F0.c): from .scratch/CsB10/func_8064B3F8_best.c
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
