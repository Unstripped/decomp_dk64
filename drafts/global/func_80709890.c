// func_80709890 (src/global/10E1D0.c): stage 6: 12 diff lines (regs only, 149 insns identical shape). KEY WIN (2026-10-31): loop 3 needs its OWN walker local (u32 *r; 'b->unk0 = r = (u32 *)...; while (*r++ != -1)') instead of reusing p: 48 -> 11 lines (merged p loops 1+3 forced p's intrinsic forbidden [v0,v1]). Two dead block-split statements remain (FAKE-tagged): 'if (arg0 && arg0) {}' after the 3rd heapAlloc (frees v0 so loop-1 walker p=v0, loaded=v1 now match) and deadsweep's 'if (r == 0) {}' after the loop-3 while brace: 8 lines. Left: unk8/unkC/unk18 values land a1/a3/a0 instead of a0/a1/a3 (unk18 expression candidate adj 4.0 > unk8/unkC 3.0 colours first). Tried: named locals / chained assignments / ordering for the three field values, 400 random decl orders, deadsweep round 2 (no gain), permuter (only dead 'if (k) {}').
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
    arg0->unk8 = (u8 *)arg0 + 0x2C;
    arg0->unkC = arg0->unk8 + arg0->unk0 * 0xC;
    arg0->unk18 = (u32 *)(arg0->unkC + arg0->unk4 * 0x1C);
    count = 1;
    p = arg0->unk18;
    while (*p++ != 0) {
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
            if (r == 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
            k++;
        }
        b->unk4 = (s32 *)((u8 *)b->unk0 + k * 4);
        count = 0;
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
