// func_80653FA4 (src/global/55B20.c): stage 5 (S55c): natural rewrite D_807F6C18[i].field + q/qend do-while + s16 cnt + (s8)i arg (no proto needed: extern s32 mapObjectCollectIdsByType();). Matches structure; remaining: frame 0xB0 vs 0xA8, off in s8 vs v1 w/ sw v1,0x4C spills around calls (needs 1 more callee-saved candidate: target keeps sll s5,v0,16 / sra t5,s5,16 with raw blez v0 guard; mine blez t5, temp v1), const 1 s7 vs s8, flags base s6 vs s7
extern u32 D_807FBB68;
extern s32 D_8076A064;
extern s32 mapObjectCollectIdsByType();

void func_80653FA4(void) {
    s32 i;
    s8 *q;
    s8 *qend;
    s8 buf[0x10];
    u8 flags[0x34];
    s16 cnt;
    s32 idx;

    if (!(D_807FBB68 & 0x100)) {
        for (i = 0; i < D_807F6C28; i++) {
            flags[i] = 0;
        }
        for (i = 0; i < D_807F6C28; i++) {
            if (D_807F6C18[i].unk1 != 0) {
                flags[i] = 1;
                D_807F6C18[i].unk28 = D_8076A064;
                if (!(D_807F6C18[i].unk7 & 4)) {
                    D_807F6C18[i].unk8 = (s32)func_80653DF0((u8 *)D_807F6C18[i].unk8, (u8 *)D_807F6C18[i].unk10, 0x270F);
                    D_807F6C18[i].unk7 |= 4;
                    D_807F6C18[i].unk7 &= 0xFFFC;
                }
                cnt = mapObjectCollectIdsByType((s8)i, buf, 0x10);
                q = buf;
                qend = q + cnt;
                if (cnt > 0) {
                  do {
                    idx = *q;
                    if (flags[idx] == 0) {
                        if (D_807F6C18[idx].unk1 == 0) {
                            if (!(D_807F6C18[idx].unk7 & 4)) {
                                D_807F6C18[idx].unk8 = (s32)func_80653DF0((u8 *)D_807F6C18[idx].unk8, (u8 *)D_807F6C18[idx].unk10, 5);
                                if (D_807F6C18[idx].unk8 == D_807F6C18[idx].unk10) {
                                    D_807F6C18[idx].unk7 &= 0xFFFD;
                                    D_807F6C18[idx].unk7 |= 4;
                                } else {
                                    D_807F6C18[idx].unk7 |= 2;
                                }
                                D_807F6C18[idx].unk7 &= 0xFFFE;
                            }
                            flags[idx] = 1;
                        }
                    }
                    q++;
                  } while (q < qend);
                }
            }
        }
        for (i = 0; i < D_807F6C28; i++) {
            if (flags[i] == 0) {
                if (D_807F6C18[i].unk7 & 8) {
                    if (!(D_807F6C18[i].unk7 & 4)) {
                        D_807F6C18[i].unk8 = (s32)func_80653DF0((u8 *)D_807F6C18[i].unk8, (u8 *)D_807F6C18[i].unk10, 5);
                        if (D_807F6C18[i].unk8 == D_807F6C18[i].unk10) {
                            D_807F6C18[i].unk7 &= 0xFFFD;
                            D_807F6C18[i].unk7 |= 4;
                        } else {
                            D_807F6C18[i].unk7 |= 2;
                        }
                        D_807F6C18[i].unk7 &= 0xFFFE;
                    }
                } else if (!(D_807F6C18[i].unk7 & 1) && (u32)(D_8076A064 - D_807F6C18[i].unk28) >= 3U) {
                    mapChunkReleaseAssets((u8 *)D_807F6C18[i].unkC, (u8 *)D_807F6C18[i].unk8);
                    D_807F6C18[i].unk8 = D_807F6C18[i].unkC;
                    D_807F6C18[i].unk7 |= 1;
                    D_807F6C18[i].unk7 &= ~6;
                }
            }
            D_807F6C18[i].unk7 &= ~8;
        }
    }
}
