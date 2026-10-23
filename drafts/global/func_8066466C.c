// func_8066466C (src/global/68EA0.c): 114/115 insns matched; only 5a4 regalloc diff: add.s destination in $f6 instead of $f14. Tried all 18 operand/association permutations, temporaries, comma operator, inlining
#include "common.h"
#include "actor.h"

typedef struct R3Small_Player {
    u8 pad0[0x21C];
    f32 x;
    f32 y;
    f32 z;
} R3Small_Player;

extern R3Small_Player *D_807FC924;
extern u8 D_807FC928;
typedef struct R1Small_68EA0_Entry {
    u16 unk0;
    s16 unk2;
    s16 unk4;
    s16 unk6;
    s16 unk8;
    s16 unkA;
} R1Small_68EA0_Entry;

extern R1Small_68EA0_Entry *D_807F9430;
extern s16 D_807F9434;

s32 func_8063C2A8(s16);
void func_80664834(s16);
void func_80664A38(s16);

void func_8066466C(void) {
    s32 i;
    f32 dz;
    f32 dx;
    f32 dy;

    if (D_807FC928 < 2) {
        for (i = 0; i < D_807F9434; i++) {
            dz = D_807FC924->z - D_807F9430[i].unk6;
            dx = D_807FC924->x - D_807F9430[i].unk2;
            dy = D_807FC924->y - D_807F9430[i].unk4;
            if ((f64)((dz * dz) + ((dx * dx) + (dy * dy))) < 90000.0) {
                if (D_807F9430[i].unkA != -1 && func_8063C2A8(D_807F9430[i].unkA)) {
                    switch (D_807F9430[i].unk0) {
                        case 1:
                        case 0x10:
                        case 0xF3:
                        case 0x138:
                            func_80664834(i);
                            break;
                        case 0x74:
                        case 0x288:
                            func_80664A38(i);
                            break;
                    }
                }
            }
        }
    }
}
