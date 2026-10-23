// func_80653FA4 (src/global/55B20.c): stage 3: structure/blocks modelled with inline D_807F6C18 re-reads (matches target reload-after-store behaviour); frame 0xB0 vs 0xA8 because one expr temp spills; local layout rule for target: 0xA4 s32 i, 0xA0 u8* p, 0x90 s8 buf[0x10], 0x5C u8 flags[0x34], 0x50 q, 0x54 qend, 0x58 idx, 0x4C off, 0x4A s16 cnt
void func_80653FA4(void) {
    s32 i;
    u8 *p;
    s8 buf[0x10];
    u8 flags[0x34];
    s8 *q;
    s8 *qend;
    s32 idx;
    s32 off;
    s16 cnt;

    if (!(D_807FBB68 & 0x100)) {
        p = flags;
        i = 0;
        if (D_807F6C28 > 0) {
            qend = (s8 *)(p + D_807F6C28);
            do {
                p++;
                p[-1] = 0;
            } while ((u32)p < (u32)qend);
            i = 0;
        }
        off = 0;
        if (D_807F6C28 > 0) {
            do {
                if (((M55P3EffectBuf *)((u8 *)D_807F6C18 + off))->unk1 != 0) {
                    flags[i] = 1;
                    ((M55P3EffectBuf *)((u8 *)D_807F6C18 + off))->unk28 = D_8076A064;
                    if (!(((M55P3EffectBuf *)((u8 *)D_807F6C18 + off))->unk7 & 4)) {
                        ((M55P3EffectBuf *)((u8 *)D_807F6C18 + off))->unk8 =
                            (s32)func_80653DF0((u8 *)((M55P3EffectBuf *)((u8 *)D_807F6C18 + off))->unk8,
                                               (u8 *)((M55P3EffectBuf *)((u8 *)D_807F6C18 + off))->unk10, 0x270F);
                        ((M55P3EffectBuf *)((u8 *)D_807F6C18 + off))->unk7 |= 4;
                        ((M55P3EffectBuf *)((u8 *)D_807F6C18 + off))->unk7 &= 0xFFFC;
                    }
                    cnt = func_80658B08((s8)i, buf, 0x10);
                    q = buf;
                    qend = &q[cnt];
                    if (cnt > 0) {
                        do {
                            idx = *q;
                            if (flags[idx] == 0) {
                                if (((M55P3EffectBuf *)((u8 *)D_807F6C18 + idx * 0x1C8))->unk1 == 0) {
                                    if (!(((M55P3EffectBuf *)((u8 *)D_807F6C18 + idx * 0x1C8))->unk7 & 4)) {
                                        ((M55P3EffectBuf *)((u8 *)D_807F6C18 + idx * 0x1C8))->unk8 =
                                            (s32)func_80653DF0((u8 *)((M55P3EffectBuf *)((u8 *)D_807F6C18 + idx * 0x1C8))->unk8,
                                                               (u8 *)((M55P3EffectBuf *)((u8 *)D_807F6C18 + idx * 0x1C8))->unk10, 5);
                                        if (((M55P3EffectBuf *)((u8 *)D_807F6C18 + idx * 0x1C8))->unk8 ==
                                            ((M55P3EffectBuf *)((u8 *)D_807F6C18 + idx * 0x1C8))->unk10) {
                                            ((M55P3EffectBuf *)((u8 *)D_807F6C18 + idx * 0x1C8))->unk7 &= 0xFFFD;
                                            ((M55P3EffectBuf *)((u8 *)D_807F6C18 + idx * 0x1C8))->unk7 |= 4;
                                        } else {
                                            ((M55P3EffectBuf *)((u8 *)D_807F6C18 + idx * 0x1C8))->unk7 |= 2;
                                        }
                                        ((M55P3EffectBuf *)((u8 *)D_807F6C18 + idx * 0x1C8))->unk7 &= 0xFFFE;
                                    }
                                    flags[idx] = 1;
                                }
                            }
                            q++;
                        } while ((u32)q < (u32)qend);
                    }
                }
                i++;
                off += 0x1C8;
            } while (i < D_807F6C28);
            i = 0;
        }
        if (D_807F6C28 > 0) {
            p = flags;
            off = 0;
            do {
                if (*p == 0) {
                    if (((M55P3EffectBuf *)((u8 *)D_807F6C18 + off))->unk7 & 8) {
                        if (!(((M55P3EffectBuf *)((u8 *)D_807F6C18 + off))->unk7 & 4)) {
                            ((M55P3EffectBuf *)((u8 *)D_807F6C18 + off))->unk8 =
                                (s32)func_80653DF0((u8 *)((M55P3EffectBuf *)((u8 *)D_807F6C18 + off))->unk8,
                                                   (u8 *)((M55P3EffectBuf *)((u8 *)D_807F6C18 + off))->unk10, 5);
                            if (((M55P3EffectBuf *)((u8 *)D_807F6C18 + off))->unk8 ==
                                ((M55P3EffectBuf *)((u8 *)D_807F6C18 + off))->unk10) {
                                ((M55P3EffectBuf *)((u8 *)D_807F6C18 + off))->unk7 &= 0xFFFD;
                                ((M55P3EffectBuf *)((u8 *)D_807F6C18 + off))->unk7 |= 4;
                            } else {
                                ((M55P3EffectBuf *)((u8 *)D_807F6C18 + off))->unk7 |= 2;
                            }
                            ((M55P3EffectBuf *)((u8 *)D_807F6C18 + off))->unk7 &= 0xFFFE;
                        }
                    } else if (!(((M55P3EffectBuf *)((u8 *)D_807F6C18 + off))->unk7 & 1) &&
                               ((u32)(D_8076A064 - ((M55P3EffectBuf *)((u8 *)D_807F6C18 + off))->unk28) >= 3U)) {
                        func_80653EA8((u8 *)((M55P3EffectBuf *)((u8 *)D_807F6C18 + off))->unkC,
                                      (u8 *)((M55P3EffectBuf *)((u8 *)D_807F6C18 + off))->unk8);
                        ((M55P3EffectBuf *)((u8 *)D_807F6C18 + off))->unk8 =
                            ((M55P3EffectBuf *)((u8 *)D_807F6C18 + off))->unkC;
                        ((M55P3EffectBuf *)((u8 *)D_807F6C18 + off))->unk7 |= 1;
                        ((M55P3EffectBuf *)((u8 *)D_807F6C18 + off))->unk7 &= ~6;
                    }
                }
                ((M55P3EffectBuf *)((u8 *)D_807F6C18 + off))->unk7 &= ~8;
                p++;
                i++;
                off += 0x1C8;
            } while (i < D_807F6C28);
        }
    }
}
