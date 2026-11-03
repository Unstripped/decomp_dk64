// func_80709890 (src/global/10E1D0.c): W3IntB 2026-11-02: unchanged 3 lines (V8 uadd arg0,0x2C v1, target a0). New tries, none < 3: V8 spellings (local/chain/swap/swap18/twoV) x all 32 subsets of the 5 FAKEs; deletion of <=2 base FAKEs x every (point,form) single over arg0/arg1/arg2/arg3/gFbTileTable/arg0->unk*; restricted pair search over the pointer-setup region (*p, p, arg0->unk8/unkC/unk18/unk20 tests, 12k pairs); no-code defs on locals (count/p/k/sum/b/q/r, 21k L2 evals). Trace: V8 (lr22) is live only in bb10 (arg0+0x2C hoisted there above the FAKE split) and interferes with cand 34 = the FAKE 'arg0->unk20' load (live bb10..loop, adjsave 4.0 > V8 3.0, coloured a0 first); removing the unk20 FAKEs rotates V8/VC/V18 to a1/a3/a0 (7-8 lines).
typedef struct MeshEntry {
    u32 unk0;
    u8 pad[0x18];
} MeshEntry;

typedef struct MeshBlobTail {
    u32 *unk0;
    s32 *unk4;
    u8 *unk8;
} MeshBlobTail;

typedef struct MeshBlobHeader {
    s32 unk0;
    s32 unk4;
    u8 *unk8;
    u8 *unkC;
    void *unk10;
    void *unk14;
    u32 *unk18;
    s32 *unk1C;
    s32 *unk20;
} MeshBlobHeader;

void *heapAlloc(s32);

s32 func_80709890(MeshBlobHeader *arg0, MeshBlobHeader **arg1, MeshBlobTail **arg2, s32 **arg3) {
    s32 count;
    s32 k;
    s32 sum;
    MeshBlobTail *b;
    u32 *p;
    u32 *r;
    MeshEntry *q;

    if (arg0 == NULL) {
        return 0;
    }
    if (arg1 == NULL) {
        return 0;
    }
    gFbTileTable = heapAlloc(0x708);
    arg0->unk10 = heapAlloc(arg0->unk0 * 0x10);
    arg0->unk14 = heapAlloc(arg0->unk0 * 0x10);
    if (arg0 && arg0) {} // FAKE: block split after the 3rd heapAlloc frees $v0 for walker p
    count = 1;
    arg0->unk8 = (u8 *)arg0 + 0x2C;
    arg0->unkC = arg0->unk8 + arg0->unk0 * 0xC;
    arg0->unk18 = (u32 *)(arg0->unkC + arg0->unk4 * 0x1C);
    p = arg0->unk18;
    if (arg0->unk20) {}  // FAKE: dead use steers V8/VC/V18 colouring order
    while (*p++ != 0) {
        if (arg0->unk20) {}  // FAKE: dead use in walker loop steers V8/VC colouring
        count++;
    }
    arg0->unk20 = (s32 *)arg0->unk18 + count;
    arg0->unk1C = arg0->unk20 + count;
    *arg1 = arg0;
    if (arg2 != NULL) {
        b = (MeshBlobTail *)(arg0->unk1C + count);
        b->unk8 = (u8 *)(b + 1);
        q = (MeshEntry *)b->unk8;
        if (gFbTileTable && gFbTileTable) {} // FAKE: block split steering loop-2 walker regalloc
        count = 1;
        while ((q++)->unk0 != 0) {
            count++;
        }
        k = 1;
        b->unk0 = r = (u32 *)(b->unk8 + count * 0x1C);
        while (*r++ != -1) {
            k++;
            if (r == 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
        }
        count = 0;
        b->unk4 = (s32 *)((u8 *)b->unk0 + k * 4);
        sum = 0;
        if (b->unk0[0] != -1) {
            do {
                b->unk4[count] = (s32)b->unk4 + k * 4 + sum * 2;
                sum += b->unk0[count];
                count++;
            } while (b->unk0[count] != -1);
        }
        *arg2 = b;
    }
    if (arg3 != NULL) {
        if (arg2 == NULL) {
            *arg3 = arg0->unk1C + count;
        } else {
            *arg3 = b->unk4 + count;
        }
    }
    return 1;
}
