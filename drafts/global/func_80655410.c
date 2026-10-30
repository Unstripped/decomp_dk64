// func_80655410 (src/global/55B20.c): stage 5-6: frame/spills/regs match; deadsweep text=12 of 532. Remaining: load order of cell/chunk chain after func_8065BAA0 (lw t2/t3 before lw t5), j-loop tail lui a0/addiu a0 vs addiu s3 delay slot, else-branch func_8065C990 arg0 in v0+move a0 (mine a0 direct). Keys: 4 dummy words + u8 q=j in if block (matrixCache arg4 is u8), named locals matrix (after memcpy) src (memcpy source) key (cell.unk2 before node=), nodeIdx/found init after call, flag=1 AFTER the 8065BAA0 call.
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
s32 func_8065BAA0(f32, f32, f32, s16, s16, s16, s16, s16, s16, s32, u8 *);
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
void func_80655410(f32 arg0, f32 arg1, f32 arg2) {
    s32 i;
    s32 obj;
    void *matrix;
    u8 *src;
    s16 key;
    s32 e4;
    L655410Node *node;
    s16 boxIdx;
    s32 j;
    s32 k;
    s32 nodeIdx;
    s32 found;
    u8 hit;
    s32 p1;
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
                        j = 0;
                        do {
                            if (L655410_CELL[k].unk10[j] != 0) {
                                boxIdx = L655410_CELL[k].unk2;
                                obj = func_8065BAA0(arg0, arg1, arg2, D_807F70B4[boxIdx].unk0, D_807F70B4[boxIdx].unk2, D_807F70B4[boxIdx].unk4, D_807F70B4[boxIdx].unk6, D_807F70B4[boxIdx].unk8, D_807F70B4[boxIdx].unkA, i, &hit);
                                nodeIdx = 0;
                                found = 0;
                                key = L655410_CELL[k].unk2;
                                node = L655410_CHUNK[i].unk4C;
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
                            j += 1;
                        } while (j != 2);
                    }
                }
            } else {
                if (flag == 0) {
                    obj = func_8065BAA0(arg0, arg1, arg2, -0x8000, -0x8000, -0x8000, -0x8000, -0x8000, -0x8000, -1, &hit);
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
