// func_806025D4 (src/global/7130.c): Stage 4, frame size 0x70, all 10 callee-saved registers matched, s8 *sp68 at 0x68 and sp64 at 0x64
typedef signed short s16;
typedef signed int s32;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned char u8;
typedef signed char s8;
typedef float f32;
typedef double f64;

typedef struct ALCSPlayer_s ALCSPlayer;
typedef struct ALSeqPlayer_s ALSeqPlayer;

extern s32 D_80745B20;
extern s32 D_80745B24;
extern s16 D_807458DC[];
extern f32 D_807458F4[];
extern s16 D_80745924[];
extern s32 D_8074593C[][12];
extern u8 D_80770560[];
extern f32 D_80770568[];
extern u16 D_80745658[];
extern u8 D_80745650;
extern ALCSPlayer *gSeqPlayers[];

void func_8060131C(s32, s32, s32);
void func_806013E8(s32, s32, s32);
void func_80602B60(s32, u8);
void func_8060A60C();
void func_8060A6A0();
u8 func_8060245C(s16);
u8 func_80602430(s16);
s32 alCSPGetState(ALCSPlayer *);
void alSeqpStop(ALSeqPlayer *);
void alCSPPlay(ALCSPlayer *);

void func_806025D4(void) {
    s8 *sp68;
    s8 sp68_buf[4];
    u8 sp64[4];
    u8 i;
    u8 j;
    s16 s5;
    u8 s1;
    u8 s2;
    s16 a3;

    sp68 = sp68_buf;
    *(s32 *)sp68 = D_80745B20;
    *(s32 *)sp64 = D_80745B24;

    if (D_80745650 != 0) {
        i = 0;
        do {
            sp64[i] = alCSPGetState(gSeqPlayers[i]);
        } while (++i < 4);

        i = 0;
        do {
            s5 = D_807458DC[i];
            if (s5 != 0) {
                s1 = func_8060245C((s16)s5);
                s2 = func_80602430((s16)s5);
                if (s5 == D_80770560[s2] && sp64[s2] == 1) {
                    if (D_80745924[i] == 1) {
                        D_80745924[i] = 2;
                    }
                    if (D_80745924[i] == 2) {
                        j = 0;
                        do {
                            s32 a1 = D_8074593C[j][s1];
                            if (a1 != 0) {
                                if (j & 2) {
                                    func_8060131C(s2, a1, (j & 1) ? 0 : 0xFF);
                                } else {
                                    func_806013E8(s2, a1, (j & 1) ? 0 : 0xFF);
                                }
                                D_8074593C[j][s1] = 0;
                            }
                        } while (++j < 4);
                    }
                }
                if (!(D_80745658[s5] & 0x100) && D_80745924[i] == 2) {
                    if (sp64[func_80602430((s16)s5)] == 0 || s5 != D_80770560[s2]) {
                        func_80602B60(s5, 0);
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
                        sp68[j] = -1;
                    } while (++j < 4);
                }
                sp68[func_80602430((s16)s5)] = i;
            }
        } while (++i < 12);

        i = 0;
        do {
            if (sp64[i] != 0) {
                if (sp64[i] == 1) {
                    if (sp68[i] == -1) {
                        func_8060A60C(i, 0);
                        if ((f64)D_80770568[i] < 0.1 || D_80770560[i] == 0x4B) {
                            alSeqpStop((ALSeqPlayer *)gSeqPlayers[i]);
                        }
                    } else {
                        a3 = D_807458DC[sp68[i]];
                        if (D_80770560[i] != a3 || (D_80745924[sp68[i]] == 0 && (D_80745658[a3] & 0x200))) {
                            alSeqpStop((ALSeqPlayer *)gSeqPlayers[i]);
                        } else if (D_80770568[i] == 0.0f) {
                            func_8060A60C(i, *(s32 *)&D_807458F4[sp68[i]]);
                        }
                    }
                }
            } else {
                if (sp68[i] != -1) {
                    a3 = D_807458DC[sp68[i]];
                    if (D_80770560[i] == a3 && D_80745924[sp68[i]] == 2) {
                        func_8060A60C(i, *(s32 *)&D_807458F4[sp68[i]]);
                        alCSPPlay(gSeqPlayers[i]);
                    } else {
                        func_8060A6A0(i, (u8)a3, *(s32 *)&D_807458F4[sp68[i]]);
                        D_80745924[func_8060245C(D_807458DC[sp68[i]])] = 1;
                    }
                }
            }
        } while (++i < 4);
    }
}
