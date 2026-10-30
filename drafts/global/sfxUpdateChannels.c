// sfxUpdateChannels (src/global/7130.c): Stage 5 (scheduling only): frame 0x70 exact, same insns/callee-saved set, parked NON_MATCHING in 7130.c. Only diff: beqz delay slot after 'andi t5,v0,2' - ours hoists 'move a0,s2' (identical head of both j&2 arms) into the beqz slot leaving nop in the jal slots; target keeps 'andi a0,s2,0xff' in each jal delay slot (+ t-reg renumbering cascade t5/t8). Wins: s5 s32 + idx s8 loop-block local (loop 4), vol(s32)/sel(u8) locals hoisting ternary and j&2 before the if, conv forms (s16)s5/(s16)(u16)s5/(s16)(s5^0) so no CSE spill, 'i = 0; do {' joined on loop B, two dead ifs (if(!s2){}, if(1){}) fix s7/s8. Tried for a0: s2 types, andi forms (s2&255 etc., still hoisted), bank local, val local, block-local vol/sel, arm swap.
#include "common.h"
#include "actor.h"

extern s8 D_80745650;
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

void func_8060131C(s32, s32, s32);
void func_806013E8(s32, s32, s32);
void sfxStopChannel();
void seqSetTargetVolume(s32, f32);
void seqLoadAndPlayWithReverb(s32, u8, f32);

// deadsweep round 3: full=62 text=62 inserted `if (D_8074593C && D_8074593C) {}` at line 18
void sfxUpdateChannels(void) {
    u8 i;
    u8 j;
    u8 s1;
    u8 s2;
    S7130aBytes4 sp68;
    S7130aUBytes4 sp64;
    s32 s5;
    s32 vol;
    u8 sel;

    sp68 = D_80745B20;
    sp64 = D_80745B24;

    if (*(u8 *)&D_80745650 != 0) {
        i = 0;
        do {
            sp64.b[i] = alCSPGetState(gSeqPlayers[i]);
        } while (++i < 4);

        i = 0; do {
            s5 = D_807458DC[i];
            if (s5 != 0) {
                s1 = sfxGetChannelIndex((s16)s5);
                s2 = sfxGetBankIndex((s16)(u16)s5);  // FAKE: (u16) keeps this conv from being CSE'd with the one above
                if (s5 == D_80770560[s2] && sp64.b[s2] == 1) {
                    if (D_80745924[i] == 1) {
                        D_80745924[i] = 2;
                    }
                    if (D_80745924[i] == 2) {
                        j = 0;
                        do {
                            if (!s2) {}  // FAKE: steers uopt register order (s7/s8)
                            vol = (j & 1) ? 0 : 0xFF;
                            sel = j & 2;
                            if (D_8074593C[j][s1] != 0) {
                                if (sel) {
                                    func_8060131C(s2, D_8074593C[j][s1], vol);
                                } else {
                                    func_806013E8(s2, D_8074593C[j][s1], vol);
                                }
                                D_8074593C[j][s1] = 0;
                            }
                        } while (++j < 4);
                    }
                }
                if (!(D_80745658[s5] & 0x100) && D_80745924[i] == 2) {
                    if (sp64.b[sfxGetBankIndex((s16)(s5 ^ 0))] == 0 || s5 != D_80770560[s2]) {  // FAKE: ^ 0 keeps this conv from being CSE'd with the earlier two
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
        if (1) {}  // FAKE: steers uopt register order (s7/s8)
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
                        seqLoadAndPlayWithReverb(i, (u8)D_807458DC[idx], D_807458F4[idx]);
                        D_80745924[sfxGetChannelIndex(D_807458DC[idx])] = 1;
                    }
                }
            }
        } while (++i < 4);
    }
}
