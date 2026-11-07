// mapChunksInitFromMapData (src/global/55B20.c): stage 5: full=26 text=13 reloc=9 shape=26; DRAFT (R13_opus_12, base 263f8a21), 527/527 insns, frame 0xED8, every stack slot and loop 1-3 byte-exact. It needs orchestrator decisions (E) and (B). (E): define D_807F7078 in 55B20. Evidence: the 165D50_807F6CC0.bss symbols D_807F6D78..D_807F735E are referenced only by 55B20.c, so 55B20's .bss is probably contiguous 0x807F6C80-0x807F7360. IDO 5.3 puts tentative definitions in .bss (no COMMON). (B): stand-in externs. The linkable count-exact park is full=49 (was 213) in .scratch/R13_opus_12/55B20.c: extern flags with the single k<0x32 loop, and both (B) stores go through the &D_807F6C2C neighbour lda, which keeps the count. Remaining text diff: only the header's &D_807F6C20 lda, which is coloured (a1). The store and the heapAlloc reload sit in one uopt block, so 2 uses - 1 reglod > 0. The target leaves it symbolic. These do not change it: volatile reload, *1, guards or boundaries around it, store order swap, an array declaration. A stand-in symbol for the reload uncolours it, but as1 then hoists the load above the store, so the target's store and reload are the same as1 symbol but different uopt lda keys. This is a third symbol/declaration-identity question like (B). Route from 213: removed ALL old guards. The old `if (D_807F6C10 == 0) {}` in the 4th then-block blocked the PRE re-insertion of &gMapChunks[n] after the call, and that re-insertion is what makes the &chunk CSE s0. Declared the 7 holder locals between base and buf (count/buf at 116/120). Single flag loop k<0x32. `for (n = 0; ...)` fixes the s1/s6 zero-init order. `size = gMapChunks[n].unk40; total += size; ...(…, size, …)` copy-propagates, so the unk40/unk44 CSE bits come late. `size = n * 12;` + `(R13o6ColEntry *)((u8 *)(w + 4) + size)` puts the n*12 chain before w/w+4 and gives the spilltemps order colOff 92 / w 88 / w+4 84 with the target's add operand order. `if (arg0) {}` after the D_807F6C14 store is a uopt block boundary that gives the boxes holder a0. `if (arg0) {}` in loop 1 raises arg0's priority above the -1 constant (s7/fp). Deadsweep guards sit after loops 1, 2 and 3. | stage 4 (orchestrator, revisit 13): src park is now the count-exact full=213 body (1ea32ccc). Decision (E) is not a plain yaml change: 55B20 already owns .bss 0x807F6C80-0x807F6CC0 and D_807F7078 lies inside the shared bss blob 165D50 well after it; one TU cannot own two disjoint .bss ranges, so defining D_807F7078 in 55B20.c needs either a common-symbol placement route or proof that the flags belong to a hidden TU. (B) needs a second symbol at 0x807F6C10/0x807F6C0C (undecided; the park uses neighbour-symbol stores instead) | stage 4-5: DRAFT full=158 text=150 reloc=16 shape=70, 527/527 insns (count-exact) but needs 2 orchestrator decisions; linkable count-exact park full=213 (was 380) in .scratch/R13_opus_6/55B20.c. R13_opus_6 (base 4a81df91): the 4 missing insns are fully explained. (E) the flag loop is ONE loop 'for/do k<0x32: D_807F7078[k]=1': uopt unrolls x4 and PEELS k=0,1 as uopt-generated str Smt (no lda/const candidates) -> ring li t0/t6 + a0 only in loop; the shared 'lui at' of the two peeled sb needs D_807F7078 DEFINED in 55B20's TU (extern gives 2 luis, +1 insn) => bss layout change. (B) uopt lda identity is (sym,addr,size,offset) and global stores ARE lda uses (store+test in one block => coloured, stores via a1/a3); the target's X stores are symbolic and &D_807F6C10 starts at the test, &D_807F6C0C in the preheader, which happens exactly when the header stores and the loop use DIFFERENT lda nodes: loop reading via stand-in externs R13o6_cnt/R13o6_rel (same addresses) reproduces T69-T88 byte-exact; linkable substitute = rebasing the two stores via &D_807F6C2C-0x1C/&D_807F6C20-0x14 (FAKE, reloc-only). Block cuts, guards, while/do forms, volatile, explicit-address stores, tentative/static/function-static definitions all tested: none change it. (C) collision block natural int form '((T*)((s32)arg0+off+4))[n].offset + ((s32)arg0+off)', [n+1].offset for unk7C, T={s32;s16 x4} gives the target's 3 NC LICM/SR temps (w+4, w, n*12) exactly and drops volatile w/colOff (+1 insn) but shifts s-regs (arg0 s8, &buf s7): park uses it + sweep guards. (D) &buf must stay NC (target addiu a2,sp,120 per call): it is coloured because the &gMapChunks[n] CSEs get v0 instead of s0 (target), freeing an s-reg; unsolved. Remaining in draft: s-reg roles (&chunk CSE s0, (s16)n/total s4, n s6, -1 s8), &gMapChunks lda placement (guard after guScale), stack (count/buf 116/120, temps 92/88/84). | Prior: stage 3 (orchestrator, revisit 13): this draft is full=180 but 523 vs 527 instructions, so it is NOT the park; src keeps the count-exact stage-4 park (full=380). Next: regain the 4 instructions (the constant-1 web split into separate li t0/t6 stores and the collision `h` fold are the likely missing ones) while keeping R13_opus_1's holder merge, then re-park. R13_opus_1's full note follows.
typedef struct { s32 offset; s16 unk4; s16 unk6; s16 unk8; s16 unkA; } R13o6ColEntry;
extern s32 R13o6_cnt[];  // STAND-IN: needs a second symbol at 0x807F6C10 (see note)
extern u8 *R13o6_rel[];  // STAND-IN: needs a second symbol at 0x807F6C0C (see note)
u8 D_807F7078[0x32];  // needs 55B20 to define D_807F7078 in its .bss (peeled stores share one lui)
void mapChunksInitFromMapData(MapData *arg0) {
    s32 i;
    s32 off;
    s32 base;
    u8 *p;
    u32 total;
    s32 n;
    s32 chunkOff;
    s32 cellsOff;
    s32 boxesOff;
    s32 vecsOff;
    u8 buf[0xE38];
    s32 count;
    s32 k;
    s32 size;

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
        if (arg0) {}  // FAKE: uopt block boundary (boxes holder gets a0, no call in its block)
        base = arg0->unk34;
        off = arg0->unk64;
        chunkOff = arg0->unk68;
        cellsOff = arg0->unk6C;
        D_807F6C20 = *(s32 *)((u8 *)arg0 + cellsOff);
        D_807F6C1C = (u8 *)((u8 *)arg0 + cellsOff + 4);
        D_807F6C2C = heapAlloc(D_807F6C20);
        boxesOff = arg0->unk70;
        D_807F6C10 = *(s32 *)((u8 *)arg0 + boxesOff);
        D_807F6C0C = (u8 *)((u8 *)arg0 + boxesOff + 4);
        for (i = 0; i < R13o6_cnt[0]; i++) {
            if (((MapRelocEntry *)R13o6_rel[0])[i].unk8 != -1) {
                ((MapRelocEntry *)R13o6_rel[0])[i].unk8 += (s32)((u8 *)arg0 + base);
                if (arg0) {}  // FAKE: arg0 use at loop-1 weight (arg0 outranks the -1 constant: s7/fp)
            }
            if (((MapRelocEntry *)R13o6_rel[0])[i].unkC != -1) {
                ((MapRelocEntry *)R13o6_rel[0])[i].unkC += (s32)((u8 *)arg0 + base);
            }
        }
        if (D_807F5DE8 && D_807F5DE8) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
        gMapChunks = heapAlloc(gMapChunkCount * 0x1C8);
        p = (u8 *)arg0 + chunkOff;
        for (n = 0; n < gMapChunkCount; n++) {
            count = 0;
            gMapChunks[n].unk0 = 0;
            gMapChunks[n].unk1 = 0;
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
            size = gMapChunks[n].unk40;
            total += size;
            if (gMapChunks[n].unk5 == 2) {
                mapChunkBuildCellTable(gMapChunks[n].unk30, size, buf, &count, 1, n);
            }
            if (*(s32 *)p != -1) {
                *(s32 *)p += (s32)((u8 *)arg0 + base);
            }
            gMapChunks[n].unk34 = *(s32 *)p;
            p += 8;
            gMapChunks[n].unk44 = *(s32 *)(p - 4);
            size = gMapChunks[n].unk44;
            total += size;
            if (gMapChunks[n].unk5 == 2) {
                mapChunkBuildCellTable(gMapChunks[n].unk34, size, buf, &count, 2, n);
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
            size = n * 12;
            gMapChunks[n].unk78 = ((R13o6ColEntry *)((u8 *)((s32)arg0 + off + 4) + size))->offset + ((s32)arg0 + off);
            gMapChunks[n].unk7C = ((R13o6ColEntry *)((u8 *)((s32)arg0 + off + 4) + size))[1].offset + ((s32)arg0 + off);
            gMapChunks[n].unk80 = ((R13o6ColEntry *)((u8 *)((s32)arg0 + off + 4) + size))->unk4;
            gMapChunks[n].unk82 = ((R13o6ColEntry *)((u8 *)((s32)arg0 + off + 4) + size))->unk6;
            gMapChunks[n].unk84 = ((R13o6ColEntry *)((u8 *)((s32)arg0 + off + 4) + size))->unk8;
            gMapChunks[n].unk86 = ((R13o6ColEntry *)((u8 *)((s32)arg0 + off + 4) + size))->unkA;
            gMapChunks[n].unk28 = -1;
            if (count != 0) {
                gMapChunks[n].unk4C = heapAlloc(count * 0x24);
                memcpy(gMapChunks[n].unk4C, buf, count * 0x24);
                for (i = 0; i < count; i++) {
                    ((u8 *)(gMapChunks[n].unk4C))[i * 0x24 + 2] = 0xFF;
                }
            }
            gMapChunks[n].unk50 = count;
        }
        if (D_807F70AC == 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
        gMapGridTrianglePlanes = heapAlloc(D_807F6C20 / 2 * 0x30);
        for (k = 0; k < D_807F6C20 / 2; k++) {
            mapGridTriangleBuildPlane(k, &gMapGridTrianglePlanes[k]);
        }
        if (gMapChunks) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
        k = 0;
        do {
            D_807F7078[k] = 1;
            k++;
        } while (k < 0x32);
        D_807F70AA = 0;
    } else {
        gMapChunks = NULL;
    }
}
