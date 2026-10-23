// func_80656F14 (src/global/55B20.c): stage 2-3: m2c-derived structure; frame 0xF0 vs 0xD8 (6 extra spilled locals); needs word-typed args 2-5 (existing file prototype says s16, conflicts)
// (6 extra spilled locals); nested loops/conditions reconstructed from the asm, but the
// signature conflicts with the existing prototype at 55B20.c:671
// (void func_80656F14(s16, s32, s16, s16, s16, s16, f32, f32, f32)), which is wrong: the
// target body reloads args 2-5 as words (lw 0xE0/0xE4/0xE8/0xEC(sp)) and stores words in the
// prologue, so the definition is word-typed for those params (K&R-ish). Not parked: types not
// verified, so the C is not provably behaviour-equivalent.
#include "common.h"

typedef struct {
    /* 0x0 */ s16 unk0;
    /* 0x2 */ s16 unk2;
    /* 0x4 */ s16 unk4;
    /* 0x6 */ s16 unk6;
    /* 0x8 */ u8 unk8;
    /* 0x9 */ u8 unk9;
} R2P5Slot;

typedef struct {
    /* 0x0 */ s16 unk0;
    /* 0x2 */ s16 unk2;
    /* 0x4 */ s32 unk4;
    /* 0x8 */ u8 pad8[0x8];
} R2P5Candidate;

extern R2P5Candidate *D_807F6C0C;
extern s16 D_807F6C30[];
extern s32 D_807F6C10;
extern u8 D_807FC929;

extern s32 actorTargetTableContainsId(s32);
extern void func_80657508(s32);
extern s32 func_806575D0(s32, f32, f32, f32);
extern void func_8065756C(s16);
extern s32 func_80655CF8(s16, s32);
extern s32 func_806574B8(s32);
extern s32 func_80658000(s32, f32, f32, f32, s32);
extern s32 func_80658134(s32, f32, f32, f32);
extern void func_80658624(s32, s32 *, s32 *, s32 *, s32 *);
extern s32 func_80657F14(s32, s32, s32, s32, s32, s32, s32, s32, s32 *, s32 *, s32 *, s32 *);
extern void func_80657E24(s32, s32, s32, s32, s32, s32, s32, s32, s32 *, s32 *, s32 *, s32 *);

void func_80656F14(s16 arg0, s32 arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5, f32 arg6, f32 arg7, f32 arg8) {
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
    s16 slotIdx;
    s32 s1;
    s32 i;
    s32 off;
    s32 r;
    s32 r2;
    s32 r3;
    s32 found;
    s32 k;
    R2P5Slot *slot;
    R2P5Candidate *cand;

    func_8065756C(arg0);
    i = 0;
    off = 0;
    if (D_807F6C20 > 0) {
        do {
            slot = (R2P5Slot *)((u8 *)D_807F6C1C + off);
            if ((arg0 == slot->unk2) && (func_80655CF8(slot->unk4, arg1) == 0)) {
                slot = (R2P5Slot *)((u8 *)D_807F6C1C + off);
                if (slot->unk9 != 0) {
                    slot->unk8 = 1;
                    s1 = i / 2;
                    if (func_806574B8(s1) != 0) {
                        r = func_806575D0(s1, arg6, arg7, arg8);
                        if (r != 0) {
                            spB0 = arg4;
                            spB8 = arg2;
                            spB4 = arg3;
                            spAC = arg5;
                        } else if (func_80658000(s1, arg6, arg7, arg8, ((R2P5Slot *)((u8 *)D_807F6C1C + off))->unk6) != 0) {
                            r2 = func_80658134(s1, arg6, arg7, arg8);
                            sp94 = r2;
                            if (r2 != 0) {
                                func_80658624(r2, &spC8, &spC4, &spC0, &spBC);
                                sp9B = func_80657F14(spC8, spC4, spC0, spBC, arg2, arg3, arg4, arg5, &spB8, &spB4, &spB0, &spAC);
                            }
                        } else {
                            sp94 = 0;
                            found = 0;
                            k = 0;
                            if (D_807F6C10 > 0) {
                                cand = (R2P5Candidate *)((u8 *)D_807F6C0C + 0);
                                do {
                                    if ((i == cand->unk2) && (cand->unk0 == ((R2P5Slot *)((u8 *)D_807F6C1C + off))->unk4)) {
                                        found = 1;
                                    } else {
                                        k++;
                                        cand++;
                                    }
                                } while ((found == 0) && (k < D_807F6C10));
                            }
                            if ((found != 0) && (func_80658000(s1, arg6, arg7, arg8, ((R2P5Candidate *)((u8 *)D_807F6C0C + k * 0x10))->unk4) != 0)) {
                                r3 = func_80658134(s1, arg6, arg7, arg8);
                                if (r3 != 0) {
                                    func_80658624(r3, &spC8, &spC4, &spC0, &spBC);
                                    if (func_80657F14(spC8, spC4, spC0, spBC, arg2, arg3, arg4, arg5, &spB8, &spB4, &spB0, &spAC) != 0) {
                                        func_80657508(k);
                                    }
                                }
                            }
                            if (actorTargetTableContainsId(i) != 0) {
                                r3 = func_80658134(s1, arg6, arg7, arg8);
                                if (r3 != 0) {
                                    func_80658624(r3, &spC8, &spC4, &spC0, &spBC);
                                    if (func_80657F14(spC8, spC4, spC0, spBC, arg2, arg3, arg4, arg5, &spB8, &spB4, &spB0, &spAC) != 0) {
                                        D_807F6C2C[i] = 1;
                                    }
                                }
                            }
                        }
                        if (((sp94 != 0) && (sp9B != 0)) || (r & 0xFF)) {
                            D_807F6C2C[i] = 1;
                            slotIdx = ((R2P5Slot *)((u8 *)D_807F6C1C + off))->unk4;
                            if (D_807F7078[slotIdx] != 0) {
                                D_807F6C18[slotIdx].unk0 = 1;
                                D_807F6C18[slotIdx].unk1 |= 1 << D_807FC929;
                                func_80657E24(spB8, spB4, spB0, spAC, D_807F6C18[slotIdx].unk68, D_807F6C18[slotIdx].unk6C, D_807F6C18[slotIdx].unk70, D_807F6C18[slotIdx].unk74, &spA8, &spA4, &spA0, &sp9C);
                                D_807F6C18[slotIdx].unk68 = spA8;
                                D_807F6C18[slotIdx].unk6C = spA4;
                                D_807F6C18[slotIdx].unk70 = spA0;
                                D_807F6C18[slotIdx].unk74 = sp9C;
                                D_807F6C30[arg1 * 2] = arg0;
                                func_80656F14(slotIdx, arg1 + 1, spB8, spB4, spB0, spAC, arg6, arg7, arg8);
                            }
                        }
                    }
                }
            }
            i++;
            off += 0xA;
        } while (i < D_807F6C20);
    }
}
