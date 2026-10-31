// func_80709890 (src/global/10E1D0.c): R2Aud1 stage 6: 6 diff lines; unk8/unkC/unk18 values land v1/a0/a3 vs target a0/a1/a3 (target colour order V8,VC,count,V18). Extra FAKE dead ifs on arg0/arg0->unk18/p/arg2, p computed from expression separately. hc 15k variants no gain.
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
    if (arg0) {}  // FAKE: dead
    gFbTileTable = heapAlloc(0x708);
    arg0->unk10 = heapAlloc(arg0->unk0 * 0x10);
    arg0->unk14 = heapAlloc(arg0->unk0 * 0x10);
    if (arg0 && arg0) {} // FAKE: block split after the 3rd heapAlloc frees $v0 for walker p
    arg0->unk8 = (u8 *)arg0 + 0x2C;
    arg0->unkC = arg0->unk8 + arg0->unk0 * 0xC;
    count = 1;
    p = (u32 *)(arg0->unkC + arg0->unk4 * 0x1C);
    arg0->unk18 = (u32 *)(arg0->unkC + arg0->unk4 * 0x1C);
    if (arg0->unk18) {}  // FAKE: dead
    while (*p++ != 0) {
        if (p) {}  // FAKE: dead
        count++;
    }
    arg0->unk20 = (s32 *)arg0->unk18 + count;
    arg0->unk1C = arg0->unk20 + count;
    *arg1 = arg0;
    if (arg2 != NULL) {
        b = (MeshBlobTail *)(arg0->unk1C + count);
        if (arg2) {}  // FAKE: dead
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
