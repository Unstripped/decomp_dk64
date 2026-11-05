// mapChunksInitFromMapData (src/global/55B20.c): stage 4: full=399 text=513 reloc=15 shape=81; real insns=527/527, frame=3800/3800, saved s0-s8+ra+f20 exact. Base 87a710b0fd190439287cafdcc06ce5e395d3fce4. Private copy parked NON_MATCHING; normal fdiff OK, --non-matching exits 0. Plain C fdiff FAILED: Section .text content mismatch (built: 33520 bytes, expected: 33520 bytes); relocations mismatch. Fixed 8-byte frame excess without changing buf[0xE54]: replaced w4 with w+4 and reused j for collision-header address instead of nested k. Reused i to cache header offsets unk58/unk6C, removing repeated alias-conservative loads and reaching exact count. Fresh inherited draft was full413 shape115, 532 actual instructions, frame3808 (older 527-count note stale). Tried buffer -8 (frame fixed but buf/count/w offsets still wrong, rejected unsupported capacity change), all volatile subsets/offset expression combinations, nested k elimination and j/off reuse, fresh cached-header locals (grew frame), existing i/p/total header caches, all 4-FAKE removal subsets, natural 50-byte flag loops (for/while/do/pointer), D70AA dead-read removal, coordinated header/loop local partitions, restoring w4 while eliminating j. Lower raw-distance alternative roles_flag_do_1_1_body.c full382 shape73 has 524 insns so is stage3, retained only in scratch. Natural do-loop flags plus removing D70AA FAKE restore three independent constant-one webs but do not fix other shapes. Remaining structural/register/stack-position differences; no matched result.
void mapChunksInitFromMapData(MapData *arg0) {
    s32 i;
    s32 off;
    s32 base;
    u8 buf[0xE54];
    s32 count;
    u8 *p;
    u32 total;
    s32 j;
    volatile s32 colOff;  // FAKE: retains collision-header offset stack accesses
    volatile s32 w;  // FAKE: retains collision-data base stack accesses

    D_807F70AC = 0;
    D_807F713A = 0;
    D_807F70AB = 0;
    if (gMapChunkCount != 0) {
        D_807F7138 = arg0->unkC;
        D_807F7074 = heapAlloc(0x40);
        guScale(D_807F7074, 1.0f / 3.0f, 1.0f / 3.0f, 1.0f / 3.0f);
        i = arg0->unk58;
        D_807F70AC = *(s32 *)((u8 *)arg0 + i);
        D_807F70B0 = (struct MapCell *)((u8 *)arg0 + i + 4);
        D_807F70B4 = (struct MapBox *)((u8 *)arg0 + arg0->unk5C + 4);
        D_807F6C14 = (MapGridVectors *)((u8 *)arg0 + arg0->unk60);
        base = arg0->unk34;
        off = arg0->unk64;
        j = arg0->unk68;
        i = arg0->unk6C;
        D_807F6C20 = *(s32 *)((u8 *)arg0 + i);
        D_807F6C1C = (u8 *)((u8 *)arg0 + i + 4);
        D_807F6C2C = heapAlloc(D_807F6C20);
        D_807F6C10 = *(s32 *)((u8 *)arg0 + arg0->unk70);
        D_807F6C0C = (u8 *)((u8 *)arg0 + arg0->unk70 + 4);
        for (i = 0; i < D_807F6C10; i++) {
            if (((MapRelocEntry *)D_807F6C0C)[i].unk8 != -1) {
                ((MapRelocEntry *)D_807F6C0C)[i].unk8 += (s32)((u8 *)arg0 + base);
            }
            if (((MapRelocEntry *)D_807F6C0C)[i].unkC != -1) {
                ((MapRelocEntry *)D_807F6C0C)[i].unkC += (s32)((u8 *)arg0 + base);
            }
        }
        gMapChunks = heapAlloc(gMapChunkCount * 0x1C8);
        p = (u8 *)arg0 + j;
        i = 0;
        if (gMapChunkCount > 0) {
            w = (s32)arg0 + off;
            colOff = 0;
            do {
                count = 0;
                gMapChunks[i].unk0 = 0;
                gMapChunks[i].unk1 = 0;
                if (D_807F70AC == 0) {}  // FAKE: dead statement (steers uopt colouring)
                gMapChunks[i].unk14 = 0;
                gMapChunks[i].unk1C = 0;
                gMapChunks[i].unk24 = 0;
                gMapChunks[i].unk7 = 4;
                gMapChunks[i].unk54 = *(s32 *)(p + 0x2C) + D_807F5DE8;
                gMapChunks[i].unk58 = gMapChunks[i].unk54;
                lightSetTargetColor(p[0] / 255.0, p[1] / 255.0, p[2] / 255.0, (s16)i);
                lightCopyTargetColors((s16)i);
                gMapChunks[i].unk6 = p[3];
                p += 0xC;
                gMapChunks[i].unk5 = p[-8];
                gMapChunks[i].unk3 = *(s32 *)(p - 4);
                j = *(s32 *)p;
                if (j != -1) {
                    j = *(s32 *)p = j + (s32)((u8 *)arg0 + base);
                }
                p += 8;
                gMapChunks[i].unk2C = j;
                gMapChunks[i].unk3C = *(s32 *)(p - 4);
                total = gMapChunks[i].unk3C;
                if (gMapChunks[i].unk5 == 2) {
                    D_807F713A = 1;
                    mapChunkBuildCellTable(gMapChunks[i].unk2C, gMapChunks[i].unk3C, buf, &count, 0, i);
                }
                j = *(s32 *)p;
                if (j != -1) {
                    j = *(s32 *)p = j + (s32)((u8 *)arg0 + base);
                }
                p += 8;
                gMapChunks[i].unk30 = j;
                gMapChunks[i].unk40 = *(s32 *)(p - 4);
                total += gMapChunks[i].unk40;
                if (gMapChunks[i].unk5 == 2) {
                    mapChunkBuildCellTable(gMapChunks[i].unk30, gMapChunks[i].unk40, buf, &count, 1, i);
                }
                j = *(s32 *)p;
                if (j != -1) {
                    j = *(s32 *)p = j + (s32)((u8 *)arg0 + base);
                }
                p += 8;
                gMapChunks[i].unk34 = j;
                gMapChunks[i].unk44 = *(s32 *)(p - 4);
                total += gMapChunks[i].unk44;
                if (gMapChunks[i].unk5 == 2) {
                    mapChunkBuildCellTable(gMapChunks[i].unk34, gMapChunks[i].unk44, buf, &count, 2, i);
                }
                j = *(s32 *)p;
                if (j != -1) {
                    j = *(s32 *)p = j + (s32)((u8 *)arg0 + base);
                }
                p += 8;
                gMapChunks[i].unk38 = j;
                gMapChunks[i].unk48 = *(s32 *)(p - 4);
                total += gMapChunks[i].unk48;
                gMapChunks[i].unk8 = gMapChunks[i].unk2C + ((total >> 3) << 3);
                gMapChunks[i].unkC = gMapChunks[i].unk2C;
                gMapChunks[i].unk10 = gMapChunks[i].unk8;
                if (gMapChunks[i].unk5 == 2) {
                    mapChunkBuildCellTable(gMapChunks[i].unk38, gMapChunks[i].unk48, buf, &count, 3, i);
                }
                gMapChunks[i].unk5C = *(s32 *)(p + 4);
                p += 8;
                gMapChunks[i].unk60 = 0;
                gMapChunks[i].unk64 = 0;
                if (gMapChunks == 0) {}  // FAKE: dead statement (steers uopt colouring)
                {
                    j = (w + 4) + colOff;
                    gMapChunks[i].unk78 = *(s32 *)j + w;
                    gMapChunks[i].unk7C = *(s32 *)(j + 0xC) + w;
                    gMapChunks[i].unk80 = *(s16 *)(j + 4);
                    gMapChunks[i].unk82 = *(s16 *)(j + 6);
                    gMapChunks[i].unk84 = *(s16 *)(j + 8);
                    gMapChunks[i].unk86 = *(s16 *)(j + 0xA);
                }
                gMapChunks[i].unk28 = -1;
                if (count != 0) {
                    gMapChunks[i].unk4C = heapAlloc(count * 0x24);
                    memcpy(gMapChunks[i].unk4C, buf, count * 0x24);
                    for (j = 0; j < count; j++) {
                        ((u8 *)(gMapChunks[i].unk4C))[j * 0x24 + 2] = 0xFF;
                    }
                }
                gMapChunks[i].unk50 = count;
                colOff += 12;
                i++;
            } while (i < gMapChunkCount);
        }
        gMapGridTrianglePlanes = heapAlloc(D_807F6C20 / 2 * 0x30);
        for (i = 0; i < D_807F6C20 / 2; i++) {
            mapGridTriangleBuildPlane(i, (u8 *)gMapGridTrianglePlanes + i * 0x30);
            if (D_807F70AA == 0) {}  // FAKE: dead statement (steers uopt colouring)
        }
        D_807F7079 = 1;
        D_807F7078[0] = 1;
        p = D_807F707A;
        do {
            *p++ = 1;
            if (D_807F707A) {}  // FAKE: dead statement (steers uopt colouring)
            *p++ = 1;
            *p++ = 1;
            *p++ = 1;
        } while (p != &D_807F70AA);
        D_807F70AA = 0;
    } else {
        gMapChunks = NULL;
    }
}
