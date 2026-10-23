// func_806049CC (src/global/7130.c): Stage 4: blocked on alCSPSetChlPan prototype (libaudio.h stock prototype vs Rare; cast generates jalr and sp-0x28 vs jal and sp-0x20)
#include "common.h"

extern u8 D_80745838;
extern u16 D_80745658[];
extern u8 D_80770560[];
extern ALCSPlayer *gSeqPlayers[];
extern ALCSPlayer *D_8076BF24;
extern s32 D_8076A0A8;

void func_80602CE0(s16, s32, u8);

void func_806049CC(s32 arg0) {
    u8 *ptr;
    u8 val;

    if (D_80745838 != 0) {
        if (arg0 == 0 && (D_80745658[D_80770560[arg0]] & 1)) {
            ((void (*)(ALCSPlayer *, s32, s32))alCSPSetChlPan)(gSeqPlayers[0], 0x3E99999A, 0x3FACCCCD);
        }
        ptr = &D_80770560[arg0];
        val = *ptr;
        if (val == 0x38) {
            func_80602CE0(0x38, 0x3C00, 1);
            val = *ptr;
        }
        if (val == 0x60) {
            if (D_8076A0A8 == 0xB8) {
                func_80602CE0(0x60, 0xE, 1);
            } else {
                func_80602CE0(0x60, 8, 1);
                alCSPSetChlVol(D_8076BF24, 1, 0x7F);
                alCSPSetChlVol(D_8076BF24, 2, 0x7F);
            }
            func_80602CE0(0x60, 0x10, 0);
        }
    } else {
        if (arg0 == 0 && (D_80745658[D_80770560[arg0]] & 1)) {
            ((void (*)(ALCSPlayer *, s32, s32))alCSPSetChlPan)(gSeqPlayers[0], 0, 0x3F800000);
        }
        ptr = &D_80770560[arg0];
        val = *ptr;
        if (val == 0x38) {
            func_80602CE0(0x38, 0x3C00, 0);
            val = *ptr;
        }
        if (val == 0x60) {
            if (D_8076A0A8 == 0xB8) {
                func_80602CE0(0x60, 0x1E, 1);
                return;
            }
            func_80602CE0(0x60, 0x10, 1);
            func_80602CE0(0x60, 8, 0);
            alCSPSetChlVol(D_8076BF24, 1, 0x64);
            alCSPSetChlVol(D_8076BF24, 2, 0x64);
        }
    }
}
