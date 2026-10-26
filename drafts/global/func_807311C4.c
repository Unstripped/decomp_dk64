// func_807311C4 (src/global/135D30.c): 56 vs 58 insns: target keeps i (sltiu) AND pointer s0, and builds s0 as 'sll t7,zero,3; addu s0,t7,t8' (unfolded &tbl[0]); mine addiu s0 directly; rest identical, frame same
typedef struct E2Rng {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    s16 unk6;
} E2Rng;

extern E2Rng D_80756024[];
void func_8073129C(s16, u8, u8);
s32 func_80731AA8(s32, s32, u8);

void func_807311C4(s16 arg0) {
    u32 i;
    s32 res = -1;
    E2Rng *e = D_80756024;

    for (i = 0; i < 0x21 && res == -1; i++, e++) {
        if (arg0 >= e->unk0 && arg0 <= e->unk2) {
            if (func_80731AA8(e->unk0, e->unk2 - e->unk0 + 1, 0) == e->unk4) {
                res = e->unk6;
            }
        }
    }
    if (res >= 0) {
        func_8073129C(res, 1, 1);
    }
}
