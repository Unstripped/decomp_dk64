// func_80653FA4 (src/global/55B20.c): stage 5 (S55c, parked NON_MATCHING): natural D_807F6C18[i].field rewrite; frame 0xA8, flags 0x5C, buf 0x90, i 0xA4, v1 spill slot 0x4C all match (decl order i,q,buf,flags,qend,idx found by brute force; q above arrays, qend/idx below). Remaining 19 lines regalloc: target keeps q=s2 (addiu s2,sp,144 AFTER the call), flags[idx] ptr s3, qend s6 and a dead s5 holding sll v0,16 with raw 'blez v0' guard; mine hoists &buf into s6 (move s3,s6), q=s3, qend=s5, guard sltu/beqz. 4 deadsweep FAKEs on globals/buf in the draft
extern u32 D_807FBB68;
extern s32 D_8076A064;
extern s32 mapObjectCollectIdsByType();

void func_80653FA4(void) {
    s32 i;
    s8 *q;
    s8 buf[0x10];
    u8 flags[0x34];
    s8 *qend;
    s32 idx;

    if (!(D_807FBB68 & 0x100)) {
        for (i = 0; i < D_807F6C28; i++) {
            if (D_8076A064 == 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
            flags[i] = 0;
        }
        if (D_8076A064 && D_8076A064) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
        for (i = 0; i < D_807F6C28; i++) {
            if (D_807F6C18[i].unk1 != 0) {
                flags[i] = 1;
                D_807F6C18[i].unk28 = D_8076A064;
                if (!(D_807F6C18[i].unk7 & 4)) {
                    D_807F6C18[i].unk8 = (s32)func_80653DF0((u8 *)D_807F6C18[i].unk8, (u8 *)D_807F6C18[i].unk10, 0x270F);
                    D_807F6C18[i].unk7 |= 4;
                    D_807F6C18[i].unk7 &= 0xFFFC;
                }
                q = buf;
                qend = q + (s16)mapObjectCollectIdsByType((s8)i, buf, 0x10);
                if (buf == 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                if (qend > q) {
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
                                    if (buf) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
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
