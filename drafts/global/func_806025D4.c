// func_806025D4 (src/global/7130.c): Stage 3 (frame 0x78 vs 0x70, insns 308 vs 305, 17 structural hunks). Same callee-saved set (s0-s8,ra). Found: stack arrays must be struct-typed locals initialised by struct assignment from D_80745B20/24 (lw/sw copy) so &sp68 is CSE'd/hoisted into a callee-saved reg and i=0 hoists above the if; s5 s32 + (s16) casts; sp68[i] as block var s8 idx. Remaining: (1) uopt CSEs the two (s16)s5 conversions across the first call and spills the temp (sw t5,84(sp)) where target recomputes sll/sra twice, +8 frame; (2) target evaluates (j & 1 ? 0 : 0xFF) before the lw of D_8074593C[j][s1] (a var for it drags FP callee-saved regs f20/f22 in and frame to 0x88); (3) reg assignment order differs (i s3 vs s4, hoisted &sp68 s7 vs s8)
#include "common.h"

extern u8 D_80745650;
extern u16 D_80745658[];
extern s16 D_807458DC[];
extern f32 D_807458F4[];
extern s16 D_80745924[];
extern s32 D_8074593C[][12];
extern u8 D_80770560[];
extern f32 D_80770568[];
extern ALCSPlayer *gSeqPlayers[];

/* The two stack arrays are block-copied from these static initialisers (D_80745B20 = -1s, D_80745B24 = 0s):
 * a struct-typed local makes the compiler emit one lw/sw copy and keep &sp68 in a callee-saved register. */
typedef struct {
    s8 b[4];
} S7130aBytes4;
typedef struct {
    u8 b[4];
} S7130aUBytes4;
extern S7130aBytes4 D_80745B20;
extern S7130aUBytes4 D_80745B24;

u8 sfxGetBankIndex(s16);
u8 sfxGetChannelIndex(s16);
void func_8060131C(s32, s32, s32);
void func_806013E8(s32, s32, s32);
void sfxStopChannel(s32, u8);
void seqSetTargetVolume(s32, f32);
void func_8060A6A0(s32, u8, f32);

void func_806025D4(void) {
    u8 i;
    u8 j;
    u8 s1;
    u8 s2;
    S7130aBytes4 sp68;
    S7130aUBytes4 sp64;
    s32 s5;

    sp68 = D_80745B20;
    sp64 = D_80745B24;

    if (*(u8 *)&D_80745650 != 0) {
        i = 0;
        do {
            sp64.b[i] = alCSPGetState(gSeqPlayers[i]);
        } while (++i < 4);

        i = 0;
        do {
            s5 = D_807458DC[i];
            if (s5 != 0) {
                s1 = sfxGetChannelIndex((s16)s5);
                s2 = sfxGetBankIndex((s16)s5);
                if (s5 == D_80770560[s2] && sp64.b[s2] == 1) {
                    if (D_80745924[i] == 1) {
                        D_80745924[i] = 2;
                    }
                    if (D_80745924[i] == 2) {
                        j = 0;
                        do {
                            if (D_8074593C[j][s1] != 0) {
                                if (j & 2) {
                                    func_8060131C(s2, D_8074593C[j][s1], (j & 1) ? 0 : 0xFF);
                                } else {
                                    func_806013E8(s2, D_8074593C[j][s1], (j & 1) ? 0 : 0xFF);
                                }
                                D_8074593C[j][s1] = 0;
                            }
                        } while (++j < 4);
                    }
                }
                if (!(D_80745658[s5] & 0x100) && D_80745924[i] == 2) {
                    if (sp64.b[sfxGetBankIndex((s16)s5)] == 0 || s5 != D_80770560[s2]) {
                        sfxStopChannel(s5, 0);
                    }
                }
            }
        } while (++i < 12);

        i = 0;
        do {
            s5 = D_807458DC[i];
            if (s5 != 0) {
                if (D_80745658[s5] & 0x80) {
                    j = 0;
                    do {
                        sp68.b[j] = -1;
                    } while (++j < 4);
                }
                sp68.b[sfxGetBankIndex((s16)s5)] = i;
            }
        } while (++i < 12);

        i = 0;
        do {
            s8 idx = sp68.b[i];
            if (sp64.b[i] != 0) {
                if (sp64.b[i] == 1) {
                    if (idx == -1) {
                        seqSetTargetVolume(i, 0.0f);
                        if ((f64)D_80770568[i] < 0.1 || D_80770560[i] == 0x4B) {
                            alSeqpStop((ALSeqPlayer *)gSeqPlayers[i]);
                        }
                    } else {
                                                if (D_80770560[i] != D_807458DC[idx] || (D_80745924[idx] == 0 && (D_80745658[D_807458DC[idx]] & 0x200))) {
                            alSeqpStop((ALSeqPlayer *)gSeqPlayers[i]);
                        } else if (D_80770568[i] == 0.0f) {
                            seqSetTargetVolume(i, D_807458F4[idx]);
                        }
                    }
                }
            } else {
                if (idx != -1) {
                                        if (D_80770560[i] == D_807458DC[idx] && D_80745924[idx] == 2) {
                        seqSetTargetVolume(i, D_807458F4[idx]);
                        alCSPPlay(gSeqPlayers[i]);
                    } else {
                        func_8060A6A0(i, (u8)D_807458DC[idx], D_807458F4[idx]);
                        D_80745924[sfxGetChannelIndex(D_807458DC[idx])] = 1;
                    }
                }
            }
        } while (++i < 4);
    }
}
