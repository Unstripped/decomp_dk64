// func_80664A38 (src/global/68EA0.c): Frame 0x38 matched; sister of func_80664834 (passes 0.4f in a1); stack slots sp24, sp28, sp2C, sp34 match
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
void func_80714A28(s32);
void func_80714CC0(void *, f32, f32, f32, f32);

extern u8 D_80720A7C;

void func_80664A38(s16 arg0) {
    f32 sp34;
    s32 sp2C;
    s32 sp28;
    s32 sp24;
    s32 temp;
    R1Small_68EA0_Entry *entry;

    if (((func_80611A44() % 10000) % 10) == 0) {
        sp24 = arg0 * sizeof(R1Small_68EA0_Entry);
        sp34 = (f64) D_807F9430[arg0].unk8 / 25.0;
        func_807149B8(1);
        func_80714998(2);
        func_80714A28(4);
        sp28 = func_80611A44();
        sp2C = func_80611A44();
        temp = func_80611A44();
        entry = (R1Small_68EA0_Entry *)((u8 *)D_807F9430 + sp24);
        func_80714CC0(&D_80720A7C, 0.4f,
            ((((f64) ((sp28 % 10000) % 300) / 20.0) - 7.5) * (f64) sp34) + (f64) entry->unk2,
            (((f64) ((sp2C % 10000) % 600) / 20.0) * (f64) sp34) + (f64) entry->unk4,
            ((((f64) ((temp % 10000) % 300) / 20.0) - 7.5) * (f64) sp34) + (f64) entry->unk6);
    }
}
