// func_80655410 (src/global/55B20.c): stage 3: structure/behaviour right, 414/432 insns. Frame 0xC8 vs 0xD0; original has 2 more local slots and its u8 locals are at 0x96(flag)/0x9F(hit) while cfe packs mine adjacently; consequence: original spills i to 0xCC (mine keeps it in a saved reg), so original recomputes D_807F6C18/eff and D_8076A0B4/B8/BC lazily after calls instead of hoisting. Tried: caching eff/nodes vs direct global expressions (direct is closer), several declaration orders (no effect on allocation), uopt_trace -l6, padding locals (frame wrong), callee arg-slot rule probed (float args 1,2 -> f12/f14, slot>=2 -> a2/a3). func_8065BAA0 is (f32,f32,f32,s16 x6,s32,u8*) (no pointer arg - a0 there is just the live address of D_807F70B0).
/* Draft for global/func_80655410 (VRAM 0x80655410, 432 insns).
 * Stage reached: ~3 (behaviourally equivalent C, same basic-block order).
 * Remaining diff: stack frame 0xC8 vs 0xD0 (original declares ~2 more slots;
 * u8 locals `flag` at 0x96 and `hit` at 0x9F are 9 bytes apart there, while
 * cfe packs mine adjacently), so `i` is in a saved register here but spilled
 * at 0xCC in the original; that in turn lets uopt hoist the D_8076A0B4/B8/BC
 * address computations above matrixCacheInsert (original recomputes them lazily
 * after memcpy).  414 vs 432 instructions.
 */
typedef struct L55410Node {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ u8 pad2[0x12];
    /* 0x14 */ void *unk14[2];
    /* 0x1C */ u8 pad1C[0x8];
} L55410Node;

typedef struct L55410Cell {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ s16 unk2;
    /* 0x04 */ s16 unk4;
    /* 0x06 */ s16 unk6;
    /* 0x08 */ s16 unk8[2];
    /* 0x0C */ s16 unkC;
    /* 0x0E */ s16 unkE;
    /* 0x10 */ s16 unk10[2];
    /* 0x14 */ u8 pad14[4];
    /* 0x18 */ u8 unk18;
    /* 0x19 */ u8 unk19;
    /* 0x1A */ u8 pad1A[2];
} L55410Cell;

typedef struct L55410Effect {
    /* 0x000 */ u8 unk0;
    /* 0x001 */ u8 unk1;
    /* 0x002 */ u8 unk2;
    /* 0x003 */ u8 unk3;
    /* 0x004 */ u8 unk4;
    /* 0x005 */ u8 unk5;
    /* 0x006 */ u8 pad6[0x46];
    /* 0x04C */ L55410Node *unk4C;
    /* 0x050 */ u8 pad50[4];
    /* 0x054 */ u8 *unk54;
    /* 0x058 */ u8 *unk58;
    /* 0x05C */ s32 unk5C;
    /* 0x060 */ void *unk60[4];
    /* 0x070 */ u8 pad70[0x158];
} L55410Effect;

void matrixCacheResetStats(void);
void lightClearActiveCount(void);
s32 func_8065BAA0(f32, f32, f32, s16, s16, s16, s16, s16, s16, s32, u8 *);
void *matrixCacheLookup(s32, s32, s16, s32);
void *matrixCacheInsert(s32, s32, s16, s32, s32, u8);
void func_8065C990(void *, void *, s32, void *, s32, s32);
void *heapAlloc(s32);
void func_8065FB64(f32, f32, f32);
extern f32 D_8076A0B4[];
extern f32 D_8076A0B8[];
extern f32 D_8076A0BC[];
extern f32 D_807F7EEC;
extern f32 D_807F7EF0;
extern f32 D_807F7EF4;
extern s32 D_807FBB60;
extern u8 D_807F78C0;

void func_80655410(f32 arg0, f32 arg1, f32 arg2) {
    s32 i;
    s32 obj;
    L55410Node *node;
    s16 boxIdx;
    s32 j;
    s32 k;
    s32 off;
    s32 cellOff;
    s32 nodeIdx;
    s32 found;
    u8 flag;
    u8 hit;

    flag = 0;
    matrixCacheResetStats();
    lightClearActiveCount();
    if (D_807F6C28 > 0) {
        i = 0;
        off = 0;
        do {
            if ((((L55410Effect *)((u8 *)D_807F6C18 + off))->unk3 != 0) && (((L55410Effect *)((u8 *)D_807F6C18 + off))->unk0 == 1) && (((L55410Effect *)((u8 *)D_807F6C18 + off))->unk4 == 0)) {
                ((L55410Effect *)((u8 *)D_807F6C18 + off))->unk4 = 1;
                if (((L55410Effect *)((u8 *)D_807F6C18 + off))->unk5 == 2) {
                    flag = 0;
                    k = 0;
                    cellOff = 0;
                    while (k < D_807F70AC) {
                        if ((i == ((L55410Cell *)((u8 *)D_807F70B0 + cellOff))->unk0) && (((L55410Cell *)((u8 *)D_807F70B0 + cellOff))->unk19 != 0)) {
                            j = 0;
                            do {
                                if (((L55410Cell *)D_807F70B0)[k].unk10[j] != 0) {
                                    boxIdx = ((L55410Cell *)((u8 *)D_807F70B0 + cellOff))->unk2;
                                    nodeIdx = 0;
                                    found = 0;
                                    obj = func_8065BAA0(arg0, arg1, arg2, D_807F70B4[boxIdx].unk0, D_807F70B4[boxIdx].unk2, D_807F70B4[boxIdx].unk4, D_807F70B4[boxIdx].unk6, D_807F70B4[boxIdx].unk8, D_807F70B4[boxIdx].unkA, i, &hit);
                                    node = ((L55410Effect *)((u8 *)D_807F6C18 + off))->unk4C;
                                    do {
                                        if (((L55410Cell *)((u8 *)D_807F70B0 + cellOff))->unk2 == node->unk0) {
                                            found = 1;
                                        } else {
                                            nodeIdx += 1;
                                            node = (L55410Node *)((u8 *)node + 0x24);
                                        }
                                    } while (found == 0);
                                    if (D_807FBB60 & 0x10) {
                                        ((L55410Node *)((u8 *)((L55410Effect *)((u8 *)D_807F6C18 + off))->unk4C + nodeIdx * 0x24))->unk14[j] = matrixCacheLookup(obj, i, boxIdx, j);
                                        if (((L55410Node *)((u8 *)((L55410Effect *)((u8 *)D_807F6C18 + off))->unk4C + nodeIdx * 0x24))->unk14[j] == NULL) {
                                            ((L55410Node *)((u8 *)((L55410Effect *)((u8 *)D_807F6C18 + off))->unk4C + nodeIdx * 0x24))->unk14[j] = matrixCacheInsert(obj, i, boxIdx, j, ((L55410Cell *)D_807F70B0)[k].unk10[j], hit);
                                            memcpy(((L55410Node *)((u8 *)((L55410Effect *)((u8 *)D_807F6C18 + off))->unk4C + nodeIdx * 0x24))->unk14[j], ((L55410Effect *)((u8 *)D_807F6C18 + off))->unk54 + ((L55410Cell *)D_807F70B0)[k].unk8[j] * 0x10, ((L55410Cell *)D_807F70B0)[k].unk10[j] * 0x10);
                                            D_807F7EEC = D_8076A0B4[i];
                                            D_807F7EF0 = D_8076A0B8[i];
                                            D_807F7EF4 = D_8076A0BC[i];
                                            func_8065C990(((L55410Node *)((u8 *)((L55410Effect *)((u8 *)D_807F6C18 + off))->unk4C + nodeIdx * 0x24))->unk14[j], (u8 *)((L55410Node *)((u8 *)((L55410Effect *)((u8 *)D_807F6C18 + off))->unk4C + nodeIdx * 0x24))->unk14[j] + ((L55410Cell *)D_807F70B0)[k].unk10[j] * 0x10, 1, &D_807F78C0, obj, ((L55410Effect *)((u8 *)D_807F6C18 + off))->unk3 == 1);
                                        }
                                    }
                                }
                                j += 1;
                            } while (j != 2);
                        }
                        k += 1;
                        cellOff += 0x1C;
                    }
                } else {
                    if (flag == 0) {
                        flag = 1;
                        obj = func_8065BAA0(arg0, arg1, arg2, -0x8000, -0x8000, -0x8000, -0x8000, -0x8000, -0x8000, -1, &hit);
                    }
                    if (((L55410Effect *)D_807F6C18)[i].unk60[D_807444FC] == NULL) {
                        ((L55410Effect *)D_807F6C18)[i].unk60[D_807444FC] = heapAlloc(((L55410Effect *)((u8 *)D_807F6C18 + off))->unk5C);
                    }
                    memcpy(((L55410Effect *)((u8 *)D_807F6C18 + off))->unk60[D_807444FC], ((L55410Effect *)((u8 *)D_807F6C18 + off))->unk54, ((L55410Effect *)((u8 *)D_807F6C18 + off))->unk5C);
                    D_807F7EEC = D_8076A0B4[i];
                    D_807F7EF0 = D_8076A0B8[i];
                    D_807F7EF4 = D_8076A0BC[i];
                    if (D_807FBB60 & 0x10) {
                        func_8065C990(((L55410Effect *)((u8 *)D_807F6C18 + off))->unk60[D_807444FC], (u8 *)((L55410Effect *)((u8 *)D_807F6C18 + off))->unk60[D_807444FC] + ((L55410Effect *)((u8 *)D_807F6C18 + off))->unk5C, 1, &D_807F78C0, obj, ((L55410Effect *)((u8 *)D_807F6C18 + off))->unk3 == 1);
                    }
                }
                ((L55410Effect *)((u8 *)D_807F6C18 + off))->unk58 = ((L55410Effect *)((u8 *)D_807F6C18 + off))->unk60[D_807444FC];
            }
            off += 0x1C8;
            i += 1;
        } while (i < D_807F6C28);
    }
    func_8065FB64(arg0, arg1, arg2);
}
