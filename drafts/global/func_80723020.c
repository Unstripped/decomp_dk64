// func_80723020 (src/global/127B00.c): Fx127A2 stage 4: frame 0x70 ok (sp54 declared after 'found'); remaining diff reg alloc (flag web splits s0/s1; j/dst/src swapped s0/s1/s2) + lw t4 vs sw order after alloc; has deadsweep FAKE stmts; needs PathPoint (10-byte s16 struct) decl from 127B00.c copy
void *memcpy(void *, const void *, unsigned int);

s32 func_80723020(s32 arg0, s32 arg1, u8 arg2, f32 arg3, f32 arg4, f32 arg5, u8 arg6) {
    PathEntry *path;
    PathPlayback **slot;
    s32 i;
    s32 found;
    PathPoint sp54;
    s32 extra;
    s32 j;
    s32 dstOff;
    s32 srcOff;

    i = 0;
    found = 0;
    extra = 0;
    if (D_807FDB90[arg1] == NULL) {
        return -1;
    }
    while (i < 0x20 && !found) {
        if (D_807FDBF8[i] == NULL) {
            found = 1;
        } else {
            if (arg2 && arg2) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
            i++;
        }
    }
    if (!found) {
        return -1;
    }
    if (D_807FDB90[arg1]->unk4 == 1 && arg2 == 0) {
        return -1;
    }
    slot = &D_807FDBF8[i];
    *slot = func_80610FE8(0x2C);
    path = (PathEntry *)&(*slot)->unk4;
    path->unk4 = D_807FDB90[arg1]->unk4;
    path->unk0 = func_80610FE8(path->unk4 * 10 + 10);
    if (arg2 != 0) {
        path->unk4++;
        ((u8 *)&sp54)[8] = arg6;
        sp54.unk2 = arg3;
        sp54.unk4 = arg4;
        sp54.unk6 = arg5;
        memcpy(path->unk0, &sp54, 10);
        extra = 1;
        if (arg2) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
    }
    dstOff = extra * 10;
    srcOff = 0;
    for (j = 0; j < D_807FDB90[arg1]->unk4; j++) {
        memcpy(path->unk0 + dstOff, D_807FDB90[arg1]->unk0 + srcOff, 10);
        srcOff += 10;
        dstOff += 10;
    }
    (*slot)->unk0 = arg0;
    (*slot)->unkC = 0.0f;
    *(s32 *)((u8 *)*slot + 0x1C) = 0;
    *(s32 *)((u8 *)*slot + 0x10) = 0;
    (*slot)->unk16 = 0;
    (*slot)->unk15 = 0;
    (*slot)->unk14 = 0;
    (*slot)->unk18 = 1;
    (*slot)->unk21 = 0;
    (*slot)->unk20 = 1;
    return i;
}
