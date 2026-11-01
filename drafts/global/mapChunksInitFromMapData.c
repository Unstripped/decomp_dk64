// mapChunksInitFromMapData (src/global/55B20.c): L650ECC stage 4 (same 9 saved regs + fs0, frame 0xED8 now matches; 387-hunk full / shape 75 vs 124 before). KEY NEW: frame needs 2 fewer uopt temp slots; merging locals (setup ptr e->p, val->j) gives frame 0xED8; '(s32)((u8 *)arg0 + base)' (pointer-typed sum) gives expected val+(arg0+base) tree; val = *(s32*)p = val + X chain gives the move v0,t4 copies (remove-able dead tests = hill-climb, 11 FAKE). Remaining: colOff natural plain scalar fuses into pointer IV s7 (expected keeps T2=w+4 0x54, w 0x58, colOff 0x5C separately in memory; &colOff dead use no longer needed for frame but reproduces it), D_807F70AC/D_807F6C20 &-cached (lui/addiu) in mine only, ptr regs order (a1/a3), tail 707A loop consts li/lui order.
typedef struct MapData {
    /* 0x00 */ u8 pad0[0xC];
    /* 0x0C */ s16 unkC;
    /* 0x0E */ u8 padE[0x26];
    /* 0x34 */ s32 unk34;
    /* 0x38 */ u8 pad38[0x20];
    /* 0x58 */ s32 unk58;
    /* 0x5C */ s32 unk5C;
    /* 0x60 */ s32 unk60;
    /* 0x64 */ s32 unk64;
    /* 0x68 */ s32 unk68;
    /* 0x6C */ s32 unk6C;
    /* 0x70 */ s32 unk70;
} MapData;

typedef struct MapRelocEntry {
    /* 0x0 */ u8 pad0[8];
    /* 0x8 */ s32 unk8;
    /* 0xC */ s32 unkC;
} MapRelocEntry;

extern s32 D_807F5DE8;
extern s32 D_807F70AC;
extern u8 D_807F70AB;
extern s16 D_807F7138;
extern u8 D_807F713A;
extern u8 D_807F7079;
extern u8 D_807F707A[];
extern u8 D_807F70AA;
extern Mtx *D_807F7074;
extern u8 *D_807F6C0C;
extern s32 D_807F6C10;
typedef struct {
    /* 0x00 */ s64 unk0;
    /* 0x08 */ s64 unk8;
    /* 0x10 */ s64 unk10;
    /* 0x18 */ s64 unk18;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ f32 unk24;
    /* 0x28 */ u8 unk28;
    /* 0x29 */ u8 pad29[0x7];
} MapGridPoint; /* 0x30 */

typedef struct {
    /* 0x00 */ f32 unk0[4];
    /* 0x10 */ f32 unk10[4];
    /* 0x20 */ f32 unk20[4];
} MapGridVectors;

extern MapGridVectors *D_807F6C14;
extern MapGridPoint *D_807F6C24;
extern struct MapCell *D_807F70B0;
extern struct MapBox *D_807F70B4;

void lightSetTargetColor(f32, f32, f32, s16);
void lightCopyTargetColors(s16);
void mapChunkBuildCellTable(s32, s32, void *, s32 *, s32, s32);
void mapGridTriangleBuildPlane(s32, void *);


void mapChunksInitFromMapData(MapData *arg0) {
    s32 i;
    s32 off;
    s32 base;
    u8 buf[0xE54];
    s32 count;
    u8 *p;
    u32 total;
    s32 j;
    s32 colOff;

    D_807F70AC = 0;
    D_807F713A = 0;
    D_807F70AB = 0;
    if (D_807F6C28 != 0) {
        D_807F7138 = arg0->unkC;
        D_807F7074 = heapAlloc(0x40);
        guScale(D_807F7074, 1.0f / 3.0f, 1.0f / 3.0f, 1.0f / 3.0f);
        p = (u8 *)arg0 + arg0->unk58;
        D_807F70AC = *(s32 *)p;
        D_807F70B0 = (struct MapCell *)(p + 4);
        p = (u8 *)arg0 + arg0->unk5C;
        D_807F70B4 = (struct MapBox *)(p + 4);
        D_807F6C14 = (MapGridVectors *)((u8 *)arg0 + arg0->unk60);
        base = arg0->unk34;
        off = arg0->unk64;
        j = arg0->unk68;
        p = (u8 *)arg0 + arg0->unk6C;
        D_807F6C20 = *(s32 *)p;
        D_807F6C1C = p + 4;
        D_807F6C2C = heapAlloc(D_807F6C20);
        p = (u8 *)arg0 + arg0->unk70;
        D_807F6C10 = *(s32 *)p;
        D_807F6C0C = p + 4;
        if (D_807F5DE8 && D_807F5DE8) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
        for (i = 0; i < D_807F6C10; i++) {
            if (((MapRelocEntry *)D_807F6C0C)[i].unk8 != -1) {
                ((MapRelocEntry *)D_807F6C0C)[i].unk8 += (s32)((u8 *)arg0 + base);
            }
            if (!D_807F6C1C) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
            if (((MapRelocEntry *)D_807F6C0C)[i].unkC != -1) {
                ((MapRelocEntry *)D_807F6C0C)[i].unkC += (s32)((u8 *)arg0 + base);
            }
        }
        D_807F6C18 = heapAlloc(D_807F6C28 * 0x1C8);
        p = (u8 *)arg0 + j;
        i = 0;
        if (D_807F6C28 > 0) {
            colOff = 0;
            do {
                count = 0;
                D_807F6C18[i].unk0 = 0;
                D_807F6C18[i].unk1 = 0;
                D_807F6C18[i].unk14 = 0;
                D_807F6C18[i].unk1C = 0;
                D_807F6C18[i].unk24 = 0;
                D_807F6C18[i].unk7 = 4;
                D_807F6C18[i].unk54 = *(s32 *)(p + 0x2C) + D_807F5DE8;
                if (D_807F70B0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                D_807F6C18[i].unk58 = D_807F6C18[i].unk54;
                lightSetTargetColor(p[0] / 255.0, p[1] / 255.0, p[2] / 255.0, (s16)i);
                if (!D_807F6C0C) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                if (D_807F6C14 == 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                lightCopyTargetColors((s16)i);
                D_807F6C18[i].unk6 = p[3];
                p += 0xC;
                D_807F6C18[i].unk5 = p[-8];
                D_807F6C18[i].unk3 = *(s32 *)(p - 4);
                j = *(s32 *)p;
                if (j != -1) {
                    j = *(s32 *)p = j + (s32)((u8 *)arg0 + base);
                }
                p += 8;
                D_807F6C18[i].unk2C = j;
                D_807F6C18[i].unk3C = *(s32 *)(p - 4);
                total = D_807F6C18[i].unk3C;
                if (D_807F6C18[i].unk5 == 2) {
                    D_807F713A = 1;
                    mapChunkBuildCellTable(D_807F6C18[i].unk2C, D_807F6C18[i].unk3C, buf, &count, 0, i);
                }
                j = *(s32 *)p;
                if (j != -1) {
                    j = *(s32 *)p = j + (s32)((u8 *)arg0 + base);
                }
                p += 8;
                D_807F6C18[i].unk30 = j;
                D_807F6C18[i].unk40 = *(s32 *)(p - 4);
                total += D_807F6C18[i].unk40;
                if (D_807F6C18[i].unk5 == 2) {
                    mapChunkBuildCellTable(D_807F6C18[i].unk30, D_807F6C18[i].unk40, buf, &count, 1, i);
                }
                j = *(s32 *)p;
                if (D_807F6C0C) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                if (j != -1) {
                    j = *(s32 *)p = j + (s32)((u8 *)arg0 + base);
                }
                p += 8;
                D_807F6C18[i].unk34 = j;
                D_807F6C18[i].unk44 = *(s32 *)(p - 4);
                total += D_807F6C18[i].unk44;
                if (D_807F6C18[i].unk5 == 2) {
                    mapChunkBuildCellTable(D_807F6C18[i].unk34, D_807F6C18[i].unk44, buf, &count, 2, i);
                }
                if (D_807F70AC != 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                j = *(s32 *)p;
                if (j != -1) {
                    if (!D_807F70B4) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                    j = *(s32 *)p = j + (s32)((u8 *)arg0 + base);
                }
                p += 8;
                D_807F6C18[i].unk38 = j;
                D_807F6C18[i].unk48 = *(s32 *)(p - 4);
                total += D_807F6C18[i].unk48;
                D_807F6C18[i].unk8 = D_807F6C18[i].unk2C + ((total >> 3) << 3);
                D_807F6C18[i].unkC = D_807F6C18[i].unk2C;
                D_807F6C18[i].unk10 = D_807F6C18[i].unk8;
                if (D_807F6C18[i].unk5 == 2) {
                    mapChunkBuildCellTable(D_807F6C18[i].unk38, D_807F6C18[i].unk48, buf, &count, 3, i);
                }
                D_807F6C18[i].unk5C = *(s32 *)(p + 4);
                p += 8;
                D_807F6C18[i].unk60 = 0;
                D_807F6C18[i].unk64 = 0;
                D_807F6C18[i].unk78 = *(s32 *)((u8 *)arg0 + off + 4 + colOff) + ((s32)arg0 + off);
                if (!D_807F6C2C) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                D_807F6C18[i].unk7C = *(s32 *)((u8 *)arg0 + off + 4 + colOff + 0xC) + ((s32)arg0 + off);
                D_807F6C18[i].unk80 = *(s16 *)((u8 *)arg0 + off + 4 + colOff + 4);
                D_807F6C18[i].unk82 = *(s16 *)((u8 *)arg0 + off + 4 + colOff + 6);
                D_807F6C18[i].unk84 = *(s16 *)((u8 *)arg0 + off + 4 + colOff + 8);
                D_807F6C18[i].unk86 = *(s16 *)((u8 *)arg0 + off + 4 + colOff + 0xA);
                D_807F6C18[i].unk28 = -1;
                if (count != 0) {
                    D_807F6C18[i].unk4C = heapAlloc(count * 0x24);
                    memcpy(D_807F6C18[i].unk4C, buf, count * 0x24);
                    for (j = 0; j < count; j++) {
                        ((u8 *)D_807F6C18[i].unk4C)[j * 0x24 + 2] = 0xFF;
                    }
                }
                D_807F6C18[i].unk50 = count;
                colOff += 0xC;
                i++;
            } while (i < D_807F6C28);
        }
        D_807F6C24 = heapAlloc(D_807F6C20 / 2 * 0x30);
        for (i = 0; i < D_807F6C20 / 2; i++) {
            mapGridTriangleBuildPlane(i, (u8 *)D_807F6C24 + i * 0x30);
            if (D_807F70AA) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
        }
        D_807F7079 = 1;
        D_807F7078[0] = 1;
        p = D_807F707A;
        do {
            *p++ = 1;
            *p++ = 1;
            *p++ = 1;
            *p++ = 1;
            if (D_807F707A) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
        } while (p != &D_807F70AA);
        D_807F70AA = 0;
    } else {
        D_807F6C18 = NULL;
    }
}
