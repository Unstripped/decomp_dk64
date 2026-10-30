// func_80651904 (src/global/55B20.c): stage 4 (S55a revisit): natural C using buf[idx] struct index (S55aEntry 0x24 = s16 key + s32 a[4] + s32 b[4]; S55aCell 0x1C with s16 unk8[4]); same callee-saved set s0-s7, no ra, frame 0x28 (as target). Remaining diff regalloc only (shape ~39): buf copied to s0 because n takes a2 first; invariants (-1,0x24,&cells,&chunks,kind,chunk) land in s4-s7 instead of v0/t0-t3; found/cfound/cidx in v1/t1/t2 instead of s0/s4/s3; target uses multu only for n*0x24 and shifts for *count*0x24 (ours multu everywhere). Needs definition 'u8 kind' (lbu 0x3b(sp)): file prototype (s32,s32,void*,s32*,s32,s32) conflicts unless K&R def (cfe warning only; parked that way in 55B20.c). deadsweep greedy 5 rounds -> full 90 (fake if (D_807F70B0==0){} etc., not natural); dead params uses at top, declaration-order permutations (120), permuter 420s (5193->4708) no help.
typedef struct S55aNode {
    /* 0x0 */ u32 unk0;
    /* 0x4 */ s32 unk4;
} S55aNode;

typedef struct S55aEntry {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ u8 pad2[2];
    /* 0x04 */ s32 unk4[4];
    /* 0x14 */ s32 unk14[4];
} S55aEntry; /* 0x24 */

typedef struct S55aCell {
    /* 0x00 */ u8 pad0[0x2];
    /* 0x02 */ s16 unk2;
    /* 0x04 */ u8 pad4[0x4];
    /* 0x08 */ s16 unk8[4];
    /* 0x10 */ u8 pad10[0xC];
} S55aCell; /* 0x1C */

void func_80651904(S55aNode *list, s32 size, S55aEntry *buf, s32 *count, u8 kind, s32 chunk) {
    s32 n;
    s32 key;
    s32 found;
    s32 idx;
    s32 cfound;
    s32 cidx;

    if (size != 0) {
        do {
            idx = 0;
            found = 0;
            size -= 8;
            if ((list->unk0 >> 24) == 0) {
                n = *count;
                key = list->unk4;
                cidx = 0;
                cfound = 0;
                if (n > 0) {
                    do {
                        if (key == buf[idx].unk0) {
                            found = 1;
                        } else {
                            idx += 1;
                        }
                    } while (idx < n && found == 0);
                }
                do {
                    if (key == ((S55aCell *)D_807F70B0)[cidx].unk2) {
                        cfound = 1;
                    } else {
                        cidx += 1;
                    }
                } while (cfound == 0);
                if (found == 0) {
                    buf[n].unk0 = key;
                    *(s32 *)((u8 *)buf + *count * 0x24 + 4) = -1;
                    *(s32 *)((u8 *)buf + *count * 0x24 + 8) = -1;
                    *(s32 *)((u8 *)buf + *count * 0x24 + 0xC) = -1;
                    *(s32 *)((u8 *)buf + *count * 0x24 + 0x10) = -1;
                    *(s32 *)((u8 *)buf + *count * 0x24 + kind * 4 + 4) = (s32)list + 8;
                    *(s32 *)((u8 *)buf + *count * 0x24 + kind * 4 + 0x14) = (((S55aCell *)D_807F70B0)[cidx].unk8[kind] << 4) + D_807F6C18[chunk].unk58;
                    *count += 1;
                } else {
                    *(s32 *)((u8 *)buf + idx * 0x24 + kind * 4 + 4) = (s32)list + 8;
                    *(s32 *)((u8 *)buf + idx * 0x24 + kind * 4 + 0x14) = (((S55aCell *)D_807F70B0)[cidx].unk8[kind] << 4) + D_807F6C18[chunk].unk58;
                }
            }
            list += 1;
        } while (size != 0);
    }
}
