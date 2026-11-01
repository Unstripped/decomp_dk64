// mapChunkTraversePortals (src/global/55B20.c): stage 5 (MapA + W2Map): unchanged, 56 text lines, ring temps only. Root: cand-loop compare k6C0C[k].unk0 == slot->unk4: target emission is LHS first (t0 cand, t1 base, t2 add, t3 slot: monotone ring) while ours emits the RHS first (base t0, add t1, slot t2, cand t3); every later hunk (mapRectOverlapTest/mapRectIntersect arg temps) is that ring shift. Tried (no effect): ==/!= operand order, && split into nested ifs, if/else polarity, casts s16/s32/u16/u8 on either side, init-statement permutations, hill-climb dead statements (28k variants). FAKE kept: if (gMapChunks && gMapChunks) {} after mapRectIntersect.
typedef struct {
    /* 0x0 */ s16 unk0;
    /* 0x2 */ s16 unk2;
    /* 0x4 */ s16 unk4;
    /* 0x6 */ s16 unk6;
    /* 0x8 */ u8 unk8;
    /* 0x9 */ u8 unk9;
} MapATpSlot;

typedef struct {
    /* 0x0 */ s16 unk0;
    /* 0x2 */ s16 unk2;
    /* 0x4 */ s16 unk4;
    /* 0x6 */ u8 pad6[0xA];
} MapATpCand;

extern s32 actorTargetTableContainsId(s32);
void mapChunkIdListAddUniqueLimited(s32);
void mapChunkIdListAddUnique(s16);
s32 mapChunkHitListExcludes(s32);
s32 mapGridPointEmit(s32, f32, f32, f32);
s32 mapGridPointPlaneDistanceWithin(s32, f32, f32, f32, s16);
s32 mapGridQuadClipToFrustum(s32, f32, f32, f32);
void mapPolyProjectToScreenRect(s32, s32 *, s32 *, s32 *, s32 *);
void mapRectIntersect(s32, s32, s32, s32, s32, s32, s32, s32, s32 *, s32 *, s32 *, s32 *);
s32 mapRectOverlapTest(s32, s32, s32, s32, s32, s32, s32, s32, s32 *, s32 *, s32 *, s32 *);

// deadsweep round 1: full=70 text=66 inserted `if (gMapChunks && gMapChunks) {}` at line 81
// deadsweep round 1: full=70 text=66 inserted `if (gMapChunks && gMapChunks) {}` at line 81
void mapChunkTraversePortals(s16 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, f32 arg6, f32 arg7, f32 arg8) {
    s32 s1;
    s32 poly;
    s32 i;
    s32 spC8;
    s32 spC4;
    s32 spC0;
    s32 spBC;
    s32 spB8;
    s32 spB4;
    s32 spB0;
    s32 spAC;
    s32 spA8;
    s32 spA4;
    s32 spA0;
    s32 sp9C;
    u8 sp9B;
    u8 r;
    s32 sp94;
    s32 found;
    s32 k;

    mapChunkIdListAddUnique(arg0);
    i = 0;
    if (D_807F6C20 > 0) {
        do {
            if ((arg0 == ((MapATpSlot *)((u8 *)D_807F6C1C + i * 0xA))->unk2) && (mapNodeIdListContains(((MapATpSlot *)((u8 *)D_807F6C1C + i * 0xA))->unk4, arg1) == 0)) {
                if (((MapATpSlot *)((u8 *)D_807F6C1C + i * 0xA))->unk9 != 0) {
                    ((MapATpSlot *)((u8 *)D_807F6C1C + i * 0xA))->unk8 = 1;
                    s1 = i / 2;
                    if (mapChunkHitListExcludes(s1) != 0) {
                        found = mapGridPointEmit(s1, arg6, arg7, arg8);
                        r = found;
                        if (found != 0) {
                            spB0 = arg4;
                            spB8 = arg2;
                            spB4 = arg3;
                            spAC = arg5;
                        } else if (mapGridPointPlaneDistanceWithin(s1, arg6, arg7, arg8, ((MapATpSlot *)((u8 *)D_807F6C1C + i * 0xA))->unk6) != 0) {
                            sp94 = mapGridQuadClipToFrustum(s1, arg6, arg7, arg8);
                            if (sp94 != 0) {
                                mapPolyProjectToScreenRect(sp94, &spC8, &spC4, &spC0, &spBC);
                                sp9B = mapRectOverlapTest(spC8, spC4, spC0, spBC, arg2, arg3, arg4, arg5, &spB8, &spB4, &spB0, &spAC);
                            }
                        } else {
                            sp94 = 0;
                            found = 0;
                            k = 0;
                            while ((found == 0) && (k < D_807F6C10)) {
                                if ((i == ((MapATpCand *)D_807F6C0C)[k].unk2) && (((MapATpCand *)D_807F6C0C)[k].unk0 == ((MapATpSlot *)((u8 *)D_807F6C1C + i * 0xA))->unk4)) {
                                    found = 1;
                                } else {
                                    k++;
                                }
                            }
                            if ((found != 0) && (mapGridPointPlaneDistanceWithin(s1, arg6, arg7, arg8, ((MapATpCand *)((u8 *)D_807F6C0C + k * 0x10))->unk4) != 0)) {
                                poly = mapGridQuadClipToFrustum(s1, arg6, arg7, arg8);
                                if (poly != 0) {
                                    mapPolyProjectToScreenRect(poly, &spC8, &spC4, &spC0, &spBC);
                                    if (mapRectOverlapTest(spC8, spC4, spC0, spBC, arg2, arg3, arg4, arg5, &spB8, &spB4, &spB0, &spAC) != 0) {
                                        mapChunkIdListAddUniqueLimited(k);
                                    }
                                }
                            }
                            if (actorTargetTableContainsId(i) != 0) {
                                poly = mapGridQuadClipToFrustum(s1, arg6, arg7, arg8);
                                if (poly != 0) {
                                    mapPolyProjectToScreenRect(poly, &spC8, &spC4, &spC0, &spBC);
                                    if (mapRectOverlapTest(spC8, spC4, spC0, spBC, arg2, arg3, arg4, arg5, &spB8, &spB4, &spB0, &spAC) != 0) {
                                        D_807F6C2C[i] = 1;
                                    }
                                }
                            }
                        }
                        if (((sp94 != 0) && (sp9B != 0)) || r) {
                            D_807F6C2C[i] = 1;
                            s1 = ((MapATpSlot *)((u8 *)D_807F6C1C + i * 0xA))->unk4;
                            if (D_807F7078[s1] != 0) {
                                gMapChunks[s1].unk0 = 1;
                                gMapChunks[s1].unk1 |= 1 << gCurrentPlayerIndex;
                                mapRectIntersect(spB8, spB4, spB0, spAC, gMapChunks[s1].unk68, gMapChunks[s1].unk6C, gMapChunks[s1].unk70, gMapChunks[s1].unk74, &spA8, &spA4, &spA0, &sp9C);
                                if (gMapChunks && gMapChunks) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                                gMapChunks[s1].unk68 = spA8;
                                gMapChunks[s1].unk6C = spA4;
                                gMapChunks[s1].unk70 = spA0;
                                gMapChunks[s1].unk74 = sp9C;
                                D_807F6C30[arg1 * 2] = arg0;
                                mapChunkTraversePortals(s1, arg1 + 1, spB8, spB4, spB0, spAC, arg6, arg7, arg8);
                            }
                        }
                    }
                }
            }
            i++;
        } while (i < D_807F6C20);
    }
}
