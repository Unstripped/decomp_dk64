// mapChunksInitFromMapData (src/global/55B20.c): stage 4: full=380 text=363 reloc=17 shape=93 (was full399/text513); frame 0xED8 exact, saved s0-s8+ra+f20 exact. Base 685f6570. R12_fable_4 (2026-11-06) derived from the target asm: (1) target reloc blocks are uopt's coloured *p load candidate updated after the store (lw v0,0(s2); beq s8,v0; addu t4,v0,t6; sw t4; move v0,t4): write 'if (*(s32*)p != -1) *(s32*)p += base; unkXX = *(s32*)p;' with NO j variable -> beq s8,v0 and the t4 temp match, and two frame slots (j + its sum temploc) disappear. (2) unk68 holder (s1 across the gMapChunks heapAlloc) must be its own variable (chunkOff), never the loop-2 reloc value (v0 forbidden across calls). (3) loop-2 counter (s6) is a different variable (n) from the loop-1/inner counter i (s0): one variable across loops gets one colour; with i in loop1+inner only, uopt places the inner 'i = 0' at the if(count) body start and as1 XBB-hoists it into the join block exactly like the target's 'or s0,zero,zero'. If i is also loop-3's counter, uopt PRE-merges the zero inits (after loop 1 + after the inner loop) and drops loop-3's init: loop 3 needs a fresh counter k, with &gMapGridTrianglePlanes[k] (IV+base operand order). (4) every header offset (unk58/5C/60/6C/70) is read into a short-lived local (v1/a0/a1/v1/a0): reusing i/k/n/total/off/chunkOff for it gives that variable's callee-saved colour; separate locals give the target's v1/a0/a1. (5) the final flag loop is uopt's unrolled+IV-eliminated 'for (k = 0; k < 0x30; k++) D_807F707A[k] = 1;' (pointer v0 to &D_807F70AA); reusing p for it stretched p's range below &gMapChunks priority. (6) B9 (after blez) holds only LICM/SR temps, so 0x54/0x58/0x5C (w+4, w, n*12 IV) are uopt temps, not declared vars: natural indexed forms tried (u8*-struct index folds the base into a pointer IV in s7; int form makes 7 derived IVs; non-volatile colOff makes 6 derived IVs); volatile w/colOff + h kept as FAKE for now. buf shrunk to 0xE30 only to fit the 5 holder locals in the 0xED8 frame (13 four-byte slots: 2 above base, base, buf, count, 5 at 0x60-0x70, 3 temps, 0x50 spare). REMAINING: p (s2) vs &gMapChunks (s3) priority (target p first), loop-3 k (s0) vs its IV (s1) order (k 41/3 < IV 31/2 here: k's 'k = 0' block adds one block to its range), holder colours a1/a2/a3 vs v1/a0/a1 in B4, pre-loop stores sw X(at) vs web 0(aN) for D_807F6C10/0C/20, constant-1 web (target: separate li t0/t6 for D_807F7079/78 stores, a0 only in the loop), the three collision temps. Previous note: stage 4: full=399 text=513 reloc=15 shape=81; real insns=527/527, frame=3800/3800, saved s0-s8+ra+f20 exact. Base 87a710b0fd190439287cafdcc06ce5e395d3fce4. Private copy parked NON_MATCHING; normal fdiff OK, --non-matching exits 0. Plain C fdiff FAILED: Section .text content mismatch (built: 33520 bytes, expected: 33520 bytes); relocations mismatch. Fixed 8-byte frame excess without changing buf[0xE54]: replaced w4 with w+4 and reused j for collision-header address instead of nested k. Reused i to cache header offsets unk58/unk6C, removing repeated alias-conservative loads and reaching exact count. Fresh inherited draft was full413 shape115, 532 actual instructions, frame3808 (older 527-count note stale). Tried buffer -8 (frame fixed but buf/count/w offsets still wrong, rejected unsupported capacity change), all volatile subsets/offset expression combinations, nested k elimination and j/off reuse, fresh cached-header locals (grew frame), existing i/p/total header caches, all 4-FAKE removal subsets, natural 50-byte flag loops (for/while/do/pointer), D70AA dead-read removal, coordinated header/loop local partitions, restoring w4 while eliminating j. Lower raw-distance alternative roles_flag_do_1_1_body.c full382 shape73 has 524 insns so is stage3, retained only in scratch. Natural do-loop flags plus removing D70AA FAKE restore three independent constant-one webs but do not fix other shapes. Remaining structural/register/stack-position differences; no matched result.
void mapChunksInitFromMapData(MapData *arg0) {
    s32 i;
    s32 off;
    s32 base;
    u8 buf[0xE30];
    s32 count;
    u8 *p;
    u32 total;
    s32 n;
    s32 chunkOff;
    s32 cellsOff;
    s32 boxesOff;
    s32 vecsOff;
    s32 triOff;
    s32 relocOff;
    s32 k;
    s32 h;
    volatile s32 colOff;  // FAKE: retains collision-header offset stack accesses
    volatile s32 w;  // FAKE: retains collision-data base stack accesses

    D_807F70AC = 0;
    D_807F713A = 0;
    D_807F70AB = 0;
    if (gMapChunkCount != 0) {
        D_807F7138 = arg0->unkC;
        D_807F7074 = heapAlloc(0x40);
        guScale(D_807F7074, 1.0f / 3.0f, 1.0f / 3.0f, 1.0f / 3.0f);
        cellsOff = arg0->unk58;
        D_807F70AC = *(s32 *)((u8 *)arg0 + cellsOff);
        D_807F70B0 = (struct MapCell *)((u8 *)arg0 + cellsOff + 4);
        boxesOff = arg0->unk5C;
        D_807F70B4 = (struct MapBox *)((u8 *)arg0 + boxesOff + 4);
        vecsOff = arg0->unk60;
        D_807F6C14 = (MapGridVectors *)((u8 *)arg0 + vecsOff);
        base = arg0->unk34;
        off = arg0->unk64;
        chunkOff = arg0->unk68;
        triOff = arg0->unk6C;
        D_807F6C20 = *(s32 *)((u8 *)arg0 + triOff);
        D_807F6C1C = (u8 *)((u8 *)arg0 + triOff + 4);
        D_807F6C2C = heapAlloc(D_807F6C20);
        relocOff = arg0->unk70;
        D_807F6C10 = *(s32 *)((u8 *)arg0 + relocOff);
        D_807F6C0C = (u8 *)((u8 *)arg0 + relocOff + 4);
        for (i = 0; i < D_807F6C10; i++) {
            if (((MapRelocEntry *)D_807F6C0C)[i].unk8 != -1) {
                ((MapRelocEntry *)D_807F6C0C)[i].unk8 += (s32)((u8 *)arg0 + base);
            }
            if (((MapRelocEntry *)D_807F6C0C)[i].unkC != -1) {
                ((MapRelocEntry *)D_807F6C0C)[i].unkC += (s32)((u8 *)arg0 + base);
            }
        }
        gMapChunks = heapAlloc(gMapChunkCount * 0x1C8);
        p = (u8 *)arg0 + chunkOff;
        n = 0;
        if (gMapChunkCount > 0) {
            w = (s32)arg0 + off;
            colOff = 0;
            do {
                count = 0;
                gMapChunks[n].unk0 = 0;
                gMapChunks[n].unk1 = 0;
                if (D_807F70AC == 0) {}  // FAKE: dead statement (steers uopt colouring)
                gMapChunks[n].unk14 = 0;
                gMapChunks[n].unk1C = 0;
                gMapChunks[n].unk24 = 0;
                gMapChunks[n].unk7 = 4;
                gMapChunks[n].unk54 = *(s32 *)(p + 0x2C) + D_807F5DE8;
                gMapChunks[n].unk58 = gMapChunks[n].unk54;
                lightSetTargetColor(p[0] / 255.0, p[1] / 255.0, p[2] / 255.0, (s16)n);
                lightCopyTargetColors((s16)n);
                gMapChunks[n].unk6 = p[3];
                p += 0xC;
                gMapChunks[n].unk5 = p[-8];
                gMapChunks[n].unk3 = *(s32 *)(p - 4);
                if (*(s32 *)p != -1) {
                    *(s32 *)p += (s32)((u8 *)arg0 + base);
                }
                gMapChunks[n].unk2C = *(s32 *)p;
                p += 8;
                gMapChunks[n].unk3C = *(s32 *)(p - 4);
                total = gMapChunks[n].unk3C;
                if (gMapChunks[n].unk5 == 2) {
                    D_807F713A = 1;
                    mapChunkBuildCellTable(gMapChunks[n].unk2C, gMapChunks[n].unk3C, buf, &count, 0, n);
                }
                if (*(s32 *)p != -1) {
                    *(s32 *)p += (s32)((u8 *)arg0 + base);
                }
                gMapChunks[n].unk30 = *(s32 *)p;
                p += 8;
                gMapChunks[n].unk40 = *(s32 *)(p - 4);
                total += gMapChunks[n].unk40;
                if (gMapChunks[n].unk5 == 2) {
                    mapChunkBuildCellTable(gMapChunks[n].unk30, gMapChunks[n].unk40, buf, &count, 1, n);
                }
                if (*(s32 *)p != -1) {
                    *(s32 *)p += (s32)((u8 *)arg0 + base);
                }
                gMapChunks[n].unk34 = *(s32 *)p;
                p += 8;
                gMapChunks[n].unk44 = *(s32 *)(p - 4);
                total += gMapChunks[n].unk44;
                if (gMapChunks[n].unk5 == 2) {
                    mapChunkBuildCellTable(gMapChunks[n].unk34, gMapChunks[n].unk44, buf, &count, 2, n);
                }
                if (*(s32 *)p != -1) {
                    *(s32 *)p += (s32)((u8 *)arg0 + base);
                }
                gMapChunks[n].unk38 = *(s32 *)p;
                p += 8;
                gMapChunks[n].unk48 = *(s32 *)(p - 4);
                total += gMapChunks[n].unk48;
                gMapChunks[n].unk8 = gMapChunks[n].unk2C + ((total >> 3) << 3);
                gMapChunks[n].unkC = gMapChunks[n].unk2C;
                gMapChunks[n].unk10 = gMapChunks[n].unk8;
                if (gMapChunks[n].unk5 == 2) {
                    mapChunkBuildCellTable(gMapChunks[n].unk38, gMapChunks[n].unk48, buf, &count, 3, n);
                }
                gMapChunks[n].unk5C = *(s32 *)(p + 4);
                p += 8;
                gMapChunks[n].unk60 = 0;
                gMapChunks[n].unk64 = 0;
                if (gMapChunks == 0) {}  // FAKE: dead statement (steers uopt colouring)
                {
                    h = (w + 4) + colOff;
                    gMapChunks[n].unk78 = *(s32 *)h + w;
                    gMapChunks[n].unk7C = *(s32 *)(h + 0xC) + w;
                    gMapChunks[n].unk80 = *(s16 *)(h + 4);
                    gMapChunks[n].unk82 = *(s16 *)(h + 6);
                    gMapChunks[n].unk84 = *(s16 *)(h + 8);
                    gMapChunks[n].unk86 = *(s16 *)(h + 0xA);
                }
                gMapChunks[n].unk28 = -1;
                if (count != 0) {
                    gMapChunks[n].unk4C = heapAlloc(count * 0x24);
                    memcpy(gMapChunks[n].unk4C, buf, count * 0x24);
                    for (i = 0; i < count; i++) {
                        ((u8 *)(gMapChunks[n].unk4C))[i * 0x24 + 2] = 0xFF;
                    }
                }
                gMapChunks[n].unk50 = count;
                colOff += 12;
                n++;
            } while (n < gMapChunkCount);
        }
        gMapGridTrianglePlanes = heapAlloc(D_807F6C20 / 2 * 0x30);
        for (k = 0; k < D_807F6C20 / 2; k++) {
            mapGridTriangleBuildPlane(k, &gMapGridTrianglePlanes[k]);
        }
        D_807F7079 = 1;
        D_807F7078[0] = 1;
        for (k = 0; k < 0x30; k++) {
            D_807F707A[k] = 1;
        }
        D_807F70AA = 0;
    } else {
        gMapChunks = NULL;
    }
}
