// mapChunksApplyLights (src/global/55B20.c): stage 6: PARKED NON_MATCHING in 55B20.c. frame 0xD0/spills/regs/schedule match; deadsweep text=3 of 532: else-branch func_8065C990 arg0 (unk60[D_807444FC]) lives in v0 + 'move a0,v0' in target, mine loads it straight into a0 (addu a1,t1,a0). Tried named locals/register/casts/operand swaps/dead stmts (deadsweep+random search)/permuter: no change. Keys: 2 pad words + u8 q=j (matrixCache arg4 u8) + named locals matrix/src/key; key=..;node=.. on ONE line; nodeIdx/found init after call; flag=1 after 8065BAA0 call; for(j=0;j<2;j++) (do-while left the loop-tail delay slot wrong).
typedef struct L655410Node {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ u8 pad2[0x12];
    /* 0x14 */ void *unk14[2];
    /* 0x1C */ u8 pad1C[0x8];
} L655410Node;

typedef struct L655410Cell {
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
} L655410Cell;

typedef struct L655410Effect {
    /* 0x000 */ u8 unk0;
    /* 0x001 */ u8 unk1;
    /* 0x002 */ u8 unk2;
    /* 0x003 */ u8 unk3;
    /* 0x004 */ u8 unk4;
    /* 0x005 */ u8 unk5;
    /* 0x006 */ u8 pad6[0x46];
    /* 0x04C */ L655410Node *unk4C;
    /* 0x050 */ u8 pad50[4];
    /* 0x054 */ u8 *unk54;
    /* 0x058 */ u8 *unk58;
    /* 0x05C */ s32 unk5C;
    /* 0x060 */ void *unk60[4];
    /* 0x070 */ u8 pad70[0x158];
} L655410Effect;

void matrixCacheResetStats(void);
void lightClearActiveCount(void);
s32 lightCollectVolumesInBounds(f32, f32, f32, s16, s16, s16, s16, s16, s16, s32, u8 *);
void *matrixCacheLookup(s32, s32, s16, u8);
void *matrixCacheInsert(s32, s32, s16, u8, s32, u8);
void func_8065C990(void *, void *, s32, void *, s32, s32);
void func_8065FB64(f32, f32, f32);
extern f32 D_807F7EEC;
extern f32 D_807F7EF0;
extern f32 D_807F7EF4;
extern s32 D_807FBB60;
extern u8 D_807F78C0;

#define L655410_CHUNK ((L655410Effect *)D_807F6C18)
#define L655410_CELL ((L655410Cell *)D_807F70B0)
void mapChunksApplyLights(f32 arg0, f32 arg1, f32 arg2) {
    s32 i;
    s32 obj;
    void *matrix;
    u8 *src;
    s16 key;
    s32 pad0;
    L655410Node *node;
    s16 boxIdx;
    s32 j;
    s32 k;
    s32 nodeIdx;
    s32 found;
    u8 hit;
    s32 pad1;
    u8 q;
    u8 flag;
    flag = 0;
    matrixCacheResetStats();
    lightClearActiveCount();
    for (i = 0; i < D_807F6C28; i++) {
        if ((L655410_CHUNK[i].unk3 != 0) && (L655410_CHUNK[i].unk0 == 1) && (L655410_CHUNK[i].unk4 == 0)) {
            L655410_CHUNK[i].unk4 = 1;
            if (L655410_CHUNK[i].unk5 == 2) {
                flag = 0;
                for (k = 0; k < D_807F70AC; k++) {
                    if ((i == L655410_CELL[k].unk0) && (L655410_CELL[k].unk19 != 0)) {
                        for (j = 0; j < 2; j++) {
                            if (L655410_CELL[k].unk10[j] != 0) {
                                boxIdx = L655410_CELL[k].unk2;
                                obj = lightCollectVolumesInBounds(arg0, arg1, arg2, D_807F70B4[boxIdx].unk0, D_807F70B4[boxIdx].unk2, D_807F70B4[boxIdx].unk4, D_807F70B4[boxIdx].unk6, D_807F70B4[boxIdx].unk8, D_807F70B4[boxIdx].unkA, i, &hit);
                                nodeIdx = 0;
                                found = 0;
                                key = L655410_CELL[k].unk2; node = L655410_CHUNK[i].unk4C;  // FAKE: same-line statements steer scheduling
                                do {
                                    if (key == node->unk0) {
                                        found = 1;
                                    } else {
                                        nodeIdx += 1;
                                        node += 1;
                                    }
                                } while (found == 0);
                                if (D_807FBB60 & 0x10) {
                                    q = j;
                                    L655410_CHUNK[i].unk4C[nodeIdx].unk14[j] = matrixCacheLookup(obj, i, boxIdx, q);
                                    if (L655410_CHUNK[i].unk4C[nodeIdx].unk14[j] == NULL) {
                                        L655410_CHUNK[i].unk4C[nodeIdx].unk14[j] = matrixCacheInsert(obj, i, boxIdx, q, L655410_CELL[k].unk10[j], hit);
                                        src = L655410_CHUNK[i].unk54 + L655410_CELL[k].unk8[j] * 0x10;
                                        memcpy(L655410_CHUNK[i].unk4C[nodeIdx].unk14[j], src, L655410_CELL[k].unk10[j] * 0x10);
                                        matrix = L655410_CHUNK[i].unk4C[nodeIdx].unk14[j];
                                        D_807F7EEC = ((f32 *)D_8076A0B4)[i];
                                        D_807F7EF0 = ((f32 *)D_8076A0B8)[i];
                                        D_807F7EF4 = ((f32 *)D_8076A0BC)[i];
                                        func_8065C990(matrix, (u8 *)matrix + L655410_CELL[k].unk10[j] * 0x10, 1, &D_807F78C0, obj, L655410_CHUNK[i].unk3 == 1);
                                    }
                                }
                            }
                        }
                    }
                }
            } else {
                if (flag == 0) {
                    obj = lightCollectVolumesInBounds(arg0, arg1, arg2, -0x8000, -0x8000, -0x8000, -0x8000, -0x8000, -0x8000, -1, &hit);
                    flag = 1;
                }
                if (L655410_CHUNK[i].unk60[D_807444FC] == NULL) {
                    L655410_CHUNK[i].unk60[D_807444FC] = heapAlloc(L655410_CHUNK[i].unk5C);
                }
                memcpy(L655410_CHUNK[i].unk60[D_807444FC], L655410_CHUNK[i].unk54, L655410_CHUNK[i].unk5C);
                D_807F7EEC = ((f32 *)D_8076A0B4)[i];
                D_807F7EF0 = ((f32 *)D_8076A0B8)[i];
                D_807F7EF4 = ((f32 *)D_8076A0BC)[i];
                if (D_807FBB60 & 0x10) {
                    func_8065C990(L655410_CHUNK[i].unk60[D_807444FC], (u8 *)L655410_CHUNK[i].unk60[D_807444FC] + L655410_CHUNK[i].unk5C, 1, &D_807F78C0, obj, L655410_CHUNK[i].unk3 == 1);
                }
            }
            L655410_CHUNK[i].unk58 = L655410_CHUNK[i].unk60[D_807444FC];
        }
    }
    func_8065FB64(arg0, arg1, arg2);
}
#undef L655410_CHUNK
#undef L655410_CELL
