// func_80664834 (src/global/68EA0.c): Frame 0x28 matched (120/131 insns); sequential func_80611A44 calls and 0.0f arg1; 11 insns diff from t1/t9 regalloc swap between arg0 and D_807F9430
#include "common.h"
#include "actor.h"

typedef struct R1Small_68EA0_Entry {
    u16 unk0;
    s16 unk2;
    s16 unk4;
    s16 unk6;
    s16 unk8;
    s16 unkA;
} R1Small_68EA0_Entry;

extern R1Small_68EA0_Entry *D_807F9430;

s32 func_80611A44(void);
void func_807149B8(s32);
void func_80714998(s32);
void func_80714950(s32);
void func_8071498C(void *);
void func_807149C8(s32, s32, s32, s32);
void func_80714A08(f32, f32);
void func_80714A28(s32);
void func_80714CC0(void *, f32, f32, f32, f32);

extern u8 D_807213D0;
void func_80717DB4(void);

void func_80664834(s16 arg0) {
    R1Small_68EA0_Entry *entry;
    s32 sp20;
    s32 temp;

    if (((func_80611A44() % 10000) % 12) == 0) {
        func_807149B8(1);
        func_80714998(7);
        func_80714950(((func_80611A44() % 10000) % 50) - 120);
        func_8071498C(func_80717DB4);
        func_807149C8(255, 200, 200, 200);
        func_80714A08(0.2f, 0.1f);
        func_80714A28(4);
        sp20 = func_80611A44();
        temp = func_80611A44();
        entry = &D_807F9430[arg0];
        func_80714CC0(&D_807213D0, 0.0f,
            (((f64) ((sp20 % 10000) % 100) / 20.0) + (f64) entry->unk2) - 2.5,
            (f64) entry->unk4 + 4.0,
            (((f64) ((temp % 10000) % 100) / 20.0) + (f64) entry->unk6) - 2.5);
    }
}
