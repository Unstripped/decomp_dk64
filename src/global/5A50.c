#define alCSPSetChlPriority alCSPSetChlPriority_unused
#define alCSPSetChlPan alCSPSetChlPan_unused
#define alCSPSendMidi alCSPSendMidi_unused
#include "common.h"
#undef alCSPSetChlPriority
#undef alCSPSetChlPan
#undef alCSPSendMidi

void alCSPSendMidi();

void alCSPSetChlPriority(ALCSPlayer *, u8, u8, u8, s32);
void alCSPSetChlPan(ALCSPlayer *, f32, f32);

typedef struct {
    u8 pad[0xF8];
} Struct8076BF48;

typedef struct {
    u8 pad[0xEC];
} Struct8076C328_Marker;

typedef struct {
    Struct8076C328_Marker marker[4];
} Struct8076C328;

extern Struct8076BF48 D_8076BF48[];
extern Struct8076C328 D_8076C328[];

s32 __n_alCSeqNextDelta(Struct8076BF48 *, Struct8076C328 *, u8, s32);

extern ALCSPlayer *D_8076BF20[];
void func_80737E90(ALCSPlayer *, s32);
void func_80737F0C(ALCSPlayer *, s32, u8);
void func_80737FD8(ALCSPlayer *, s32);
void func_8073801C(ALCSPlayer *, s32);
void func_80738080(ALCSPlayer *, s32, u8);
void func_807380CC(ALCSPlayer *, s32, u8);
void func_80738118(ALCSPlayer *, s32, u8);
void func_8060B140(s32, s32 *, s32 *, s32, s32, s32, s32);
extern s32 D_8000DDCC;
extern s32 D_8076D200;

#pragma GLOBAL_ASM("asm/global/nonmatchings/5A50/func_80600D50.s")

void func_806010A0(void) {
    s32 sp34;
    s32 sp30;
    s32 pad1;
    s32 temp;

    sp34 = 0x80;
    func_8060B140(D_8000DDCC, &D_8076D200, &sp34, 0, 0, 0, 0);
    temp = D_8076D200;
    sp30 = 0x2C0;
    func_8060B140(D_8000DDCC + temp, &D_8076D200, &sp30, 0, 0, 0, 0);
}

void func_80601120(u8 arg0) {
    if (alCSPGetState(D_8076BF20[arg0]) == 0) {
        alCSPPlay(D_8076BF20[arg0]);
    }
}

s32 func_8060116C(u8 arg0) {
    return alCSPGetState(D_8076BF20[arg0]);
}

void func_806011A0(u8 arg0, s32 arg1) {
    func_80737E90(D_8076BF20[arg0], arg1);
}

typedef struct {
    s32 a, b, c;
} Struct806011D4;

void func_806011D4(Struct806011D4 arg0) {
}

void func_806011E4(u8 arg0, s32 arg1, u8 arg2) {
    func_80737F0C(D_8076BF20[arg0], arg1, arg2);
}

void func_80601224(u8 arg0, s32 arg1) {
    func_80737FD8(D_8076BF20[arg0], arg1);
}

void func_80601258(u8 arg0, s32 arg1) {
    func_8073801C(D_8076BF20[arg0], arg1);
}

void func_8060128C(u8 arg0, u8 arg1, u8 arg2) {
    func_80738080(D_8076BF20[arg0], arg1, arg2);
}

void func_806012D4(u8 arg0, u8 arg1, u8 arg2) {
    func_807380CC(D_8076BF20[arg0], arg1, arg2);
}
void func_8060131C(u8 arg0, s32 arg1, u8 arg2) {
    s32 i;

    for (i = 0; i < 16; i++) {
        if (arg1 & (1 << i)) {
            func_8060128C(arg0, i, arg2);
        }
    }
}

void func_806013A0(u8 arg0, u8 arg1, u8 arg2) {
    func_80738118(D_8076BF20[arg0], arg1, arg2);
}

void func_806013E8(u8 arg0, s32 arg1, u8 arg2) {
    s32 i;

    for (i = 0; i < 16; i++) {
        if (arg1 & (1 << i)) {
            func_80738118(D_8076BF20[arg0], i, arg2);
        }
    }
}

void func_80601484(u8 arg0, s32 arg1, s32 arg2) {
    s32 i;

    for (i = 0; i < 16; i++) {
        if (arg1 & (1 << i)) {
            if (arg2 != 0) {
                func_80601258(arg0, i);
            } else {
                func_80601224(arg0, i);
            }
        }
    }
}

void func_8060151C(u8 arg0, s32 arg1, s32 arg2) {
    s32 i;

    for (i = 0; i < 16; i++) {
        if (arg1 & (1 << i)) {
            if (arg2 != 0) {
                D_8076BF20[arg0]->chanMask |= arg1;
            } else {
                D_8076BF20[arg0]->chanMask &= arg1 ^ 0xFFFF;
            }
        }
    }
}

void func_806015E0(u8 arg0, s32 arg1, s32 arg2) {
    s32 i;

    for (i = 0; i < 16; i++) {
        if (arg1 & (1 << i)) {
            alCSPSetChlFXMix(D_8076BF20[arg0], i, arg2);
        }
    }
}

void func_80601678(u8 arg0, u8 arg1, u8 arg2) {
    alCSPSendMidi(D_8076BF20[arg0], 0, (u8)(arg1 | 0xB0), 0x21, arg2);
}

void func_806016D0(u8 arg0, u8 arg1, u8 arg2) {
    alCSPSendMidi(D_8076BF20[arg0], 0, (u8)(arg1 | 0xB0), 0x22, arg2);
}

void func_80601728(u8 arg0, u8 arg1, u8 arg2) {
    alCSPSendMidi(D_8076BF20[arg0], 0, (u8)(arg1 | 0xB0), 0x23, arg2);
}
void func_80601780(u8 arg0, s32 tempo) {
    alCSPSetTempo(D_8076BF20[arg0], tempo);
}

ALCSeq *func_806017B4(u8 arg0) {
    return alCSPGetSeq(D_8076BF20[arg0]);
}
void func_806017E8(u8 arg0, u8 arg1, u8 arg2, u8 arg3, s32 arg4) {
    alCSPSetChlPriority(D_8076BF20[arg0], arg1, arg2, arg3, arg4);
}

void func_80601848(u8 arg0, f32 arg1, f32 arg2) {
    alCSPSetChlPan(D_8076BF20[arg0], arg1, arg2);
}

void func_8060188C(u8 arg0, s32 arg1) {
    D_8076BF20[arg0]->nextDelta += arg1;
}

s32 func_806018B4(u8 arg0) {
    return D_8076BF20[arg0]->curTime;
}
s32 func_806018D4(u8 arg0, u8 arg1, s32 arg2) {
    return __n_alCSeqNextDelta(&D_8076BF48[arg0], &D_8076C328[arg0], arg1, arg2);
}

void func_8060193C(u8 arg0, u8 arg1) {
    alCSeqSetLoc((ALCSeq *)&D_8076BF48[arg0], (ALCSeqMarker *)&D_8076C328[arg0].marker[arg1]);
}

void func_806019B8(u8 arg0, s32 ticks, u8 status, u8 byte1, s32 byte2) {
    alCSPSendMidi(D_8076BF20[arg0], ticks, status, byte1, byte2);
}
