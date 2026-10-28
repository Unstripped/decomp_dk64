// func_80709ACC (src/global/10E1D0.c): stage 6 (parked NON_MATCHING): shape-identical (62 insns), loop limit re-read from memory each iteration (stops IDO 4x unroll), only regalloc: out=v0/off=v1/max=a2/temp=a3/min=t0/i=t1 vs target min=v0/off=v1/temp=a2/max=a3/i=t0/out=t1; decl order and dead-stmt sweeps don't move it
typedef struct EaSortView { s32 unk0, unk4, unk8; u8 *unkC; s32 unk10, unk14; s32 *unk18, *unk1C, *unk20; } EaSortView;
typedef struct EaSortEntry { s32 unk0, unk4, unk8; u8 padC[0x10]; } EaSortEntry;
s32 func_80709ACC(EaSortView *arg0) {
    EaSortEntry *e; s32 min, max, i, out = 0, off = 0;
    while (*(s32 *)((u8 *)arg0->unk18 + out)) {
        e = (EaSortEntry *)(arg0->unkC + off);
        min = max = e->unk0;
        for (i = 0; i < *(s32 *)((u8 *)arg0->unk18 + out); i++, off += 0x1C, e++) {
            if (e->unk0 > max) max = e->unk0; else if (e->unk0 < min) min = e->unk0;
            if (e->unk4 > max) max = e->unk4; else if (e->unk4 < min) min = e->unk4;
            if (e->unk8 > max) max = e->unk8; else if (e->unk8 < min) min = e->unk8;
        }
        *(s32 *)((u8 *)arg0->unk20 + out) = min;
        *(s32 *)((u8 *)arg0->unk1C + out) = max;
        out += 4;
    }
    return 1;
}
