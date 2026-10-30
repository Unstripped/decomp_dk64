// func_80656F14 (src/global/55B20.c): stage 5: structure matches (362 insns, frame 0xD8 after merging the func_80658134-result temp into 'found'; first 3 locals s1,i,r declared BEFORE the sp locals give the right 0x9C-0xC8 block offsets). Needs definition params 2-5 as s32 => prototype at 55B20.c:1281 must become (s16, s32, s32, s32, s32, s32, f32, f32, f32) (cfe redeclaration error otherwise). Remaining ~35 hunks: found/N regs (found v1, D_807F6C10 a0 in target; mine swapped), t0-t3 temp numbering in call setup, cand loop must be 'while (found==0 && k<D_807F6C10)' w/o guard; u8 r from found-temp (r = found = emit())
#include "common.h"

typedef struct {
    /* 0x0 */ s16 unk0;
    /* 0x2 */ s16 unk2;
    /* 0x4 */ s16 unk4;
    /* 0x6 */ s16 unk6;
    /* 0x8 */ u8 unk8;
    /* 0x9 */ u8 unk9;
} S55eSlot;

typedef struct {
    /* 0x0 */ s16 unk0;
    /* 0x2 */ s16 unk2;
    /* 0x4 */ s16 unk4;
    /* 0x6 */ u8 pad6[0xA];
} S55eCand;

extern u8 D_807F7078[];
extern MapChunk *D_807F6C18;
extern u8 *D_807F6C1C;
extern s32 D_807F6C20;
extern u8 *D_807F6C2C;
extern u8 *D_807F6C0C;
extern s32 D_807F6C10;
extern s16 D_807F6C30[];
extern u8 D_807FC929;
// MapChunk: typedef from src/global/55B20.c (fields unk0, unk1, unk68..unk74 used)

extern s32 actorTargetTableContainsId(s32);
void mapChunkIdListAddUniqueLimited(s32);
void mapChunkIdListAddUnique(s16);
s32 mapChunkHitListExcludes(s32);
s32 mapGridPointEmit(s32, f32, f32, f32);
s32 mapGridPointPlaneDistanceWithin(s32, f32, f32, f32, s16);
s32 func_80658134(s32, f32, f32, f32);
void func_80658624(s32, s32 *, s32 *, s32 *, s32 *);
void mapRectIntersect(s32, s32, s32, s32, s32, s32, s32, s32, s32 *, s32 *, s32 *, s32 *);
s32 mapRectOverlapTest(s32, s32, s32, s32, s32, s32, s32, s32, s32 *, s32 *, s32 *, s32 *);

void func_80656F14(s16 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, f32 arg6, f32 arg7, f32 arg8) {
    s32 s1;
    s32 i;
    u8 r;
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
    s32 sp94;
    s32 found;
    s32 k;

    mapChunkIdListAddUnique(arg0);
    i = 0;
    if (D_807F6C20 > 0) {
        do {
            if ((arg0 == ((S55eSlot *)((u8 *)D_807F6C1C + i * 0xA))->unk2) && (mapNodeIdListContains(((S55eSlot *)((u8 *)D_807F6C1C + i * 0xA))->unk4, arg1) == 0)) {
                if (((S55eSlot *)((u8 *)D_807F6C1C + i * 0xA))->unk9 != 0) {
                    ((S55eSlot *)((u8 *)D_807F6C1C + i * 0xA))->unk8 = 1;
                    s1 = i / 2;
                    if (mapChunkHitListExcludes(s1) != 0) {
                        found = mapGridPointEmit(s1, arg6, arg7, arg8);
                        r = found;
                        if (found != 0) {
                            spB0 = arg4;
                            spB8 = arg2;
                            spB4 = arg3;
                            spAC = arg5;
                        } else if (mapGridPointPlaneDistanceWithin(s1, arg6, arg7, arg8, ((S55eSlot *)((u8 *)D_807F6C1C + i * 0xA))->unk6) != 0) {
                            sp94 = func_80658134(s1, arg6, arg7, arg8);
                            if (sp94 != 0) {
                                func_80658624(sp94, &spC8, &spC4, &spC0, &spBC);
                                sp9B = mapRectOverlapTest(spC8, spC4, spC0, spBC, arg2, arg3, arg4, arg5, &spB8, &spB4, &spB0, &spAC);
                            }
                        } else {
                            sp94 = 0;
                            found = 0;
                            k = 0;
                            while ((found == 0) && (k < D_807F6C10)) {
                                if ((i == ((S55eCand *)D_807F6C0C)[k].unk2) && (((S55eCand *)D_807F6C0C)[k].unk0 == ((S55eSlot *)((u8 *)D_807F6C1C + i * 0xA))->unk4)) {
                                    found = 1;
                                } else {
                                    k++;
                                }
                            }
                            if ((found != 0) && (mapGridPointPlaneDistanceWithin(s1, arg6, arg7, arg8, ((S55eCand *)((u8 *)D_807F6C0C + k * 0x10))->unk4) != 0)) {
                                found = func_80658134(s1, arg6, arg7, arg8);
                                if (found != 0) {
                                    func_80658624(found, &spC8, &spC4, &spC0, &spBC);
                                    if (mapRectOverlapTest(spC8, spC4, spC0, spBC, arg2, arg3, arg4, arg5, &spB8, &spB4, &spB0, &spAC) != 0) {
                                        mapChunkIdListAddUniqueLimited(k);
                                    }
                                }
                            }
                            if (actorTargetTableContainsId(i) != 0) {
                                found = func_80658134(s1, arg6, arg7, arg8);
                                if (found != 0) {
                                    func_80658624(found, &spC8, &spC4, &spC0, &spBC);
                                    if (mapRectOverlapTest(spC8, spC4, spC0, spBC, arg2, arg3, arg4, arg5, &spB8, &spB4, &spB0, &spAC) != 0) {
                                        D_807F6C2C[i] = 1;
                                    }
                                }
                            }
                        }
                        if (((sp94 != 0) && (sp9B != 0)) || r) {
                            D_807F6C2C[i] = 1;
                            s1 = ((S55eSlot *)((u8 *)D_807F6C1C + i * 0xA))->unk4;
                            if (D_807F7078[s1] != 0) {
                                D_807F6C18[s1].unk0 = 1;
                                D_807F6C18[s1].unk1 |= 1 << D_807FC929;
                                mapRectIntersect(spB8, spB4, spB0, spAC, D_807F6C18[s1].unk68, D_807F6C18[s1].unk6C, D_807F6C18[s1].unk70, D_807F6C18[s1].unk74, &spA8, &spA4, &spA0, &sp9C);
                                D_807F6C18[s1].unk68 = spA8;
                                D_807F6C18[s1].unk6C = spA4;
                                D_807F6C18[s1].unk70 = spA0;
                                D_807F6C18[s1].unk74 = sp9C;
                                D_807F6C30[arg1 * 2] = arg0;
                                func_80656F14(s1, arg1 + 1, spB8, spB4, spB0, spAC, arg6, arg7, arg8);
                            }
                        }
                    }
                }
            }
            i++;
        } while (i < D_807F6C20);
    }
}
