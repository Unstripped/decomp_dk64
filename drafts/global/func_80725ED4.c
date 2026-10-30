// func_80725ED4 (src/global/1295B0.c): stage 4; 50 diff lines. Matches exact instructions and registers throughout entire body; only diff is frame size 0x70 vs 0x68
s32 func_80725ED4(arg0, arg1, arg2, arg3, arg4, arg5)
u8 arg0;
Actor *arg1;
F1Tbl *arg2;
s16 *arg3;
s16 *arg4;
s16 *arg5;
{
    s32 found;
    s32 best;
    s32 stop;
    s16 i;
    F1Ent *e;

    stop = 0;
    found = 0;
    if (arg0 & 1) {
        best = 0;
    } else {
        best = 0xF423F;
    }
    for (i = 0; i < arg2->count10 && !stop; i++) {
        e = F1ENT(arg2, i);
        if (!(e->flags & 0x80) && ((e->flags & 0x7F) == 3)) {
            if (segmentIntersectsCircle2D((s32)arg1->unk7C, (s32)arg1->unk84, e->x, e->z, (s32)D_807FDC94->unk7C, (s32)D_807FDC94->unk84, 0x14) == 0) {
                if (zoneCanReachPoint(arg1, e->x, e->y, e->z, arg2) != 0) {
                    s32 d;
                    if (((arg0 & 1) && (d = (s32)(((D_807FDC94->unk7C - e->x) * (D_807FDC94->unk7C - e->x)) + ((D_807FDC94->unk84 - e->z) * (D_807FDC94->unk84 - e->z))), best < d)) ||
                        ((arg0 & 2) && (d = (s32)(((arg1->unk7C - e->x) * (arg1->unk7C - e->x)) + ((arg1->unk84 - e->z) * (arg1->unk84 - e->z))), d < best))) {
                        best = d;
                        *arg3 = e->x;
                        *arg4 = e->y;
                        *arg5 = e->z;
                        found = 1;
                        if (arg0 & 0x80) {
                            if (((randomNonNegative() >> 0xF) % 100) >= 0x33) {
                                stop = 1;
                            }
                        }
                    }
                }
            }
        }
    }
    return found;
}
