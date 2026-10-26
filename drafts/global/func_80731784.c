// func_80731784 (src/global/135D30.c): 32/32 insns; i^0 stops strength reduction; remaining: arg0/arg1 s16 widening roles swapped (target moves arg1 via t8->a3, arg0 in place a0; mine reverse) so e/t3 get a1/t3 vs a0/a0
typedef struct E2Ent {
    u8 unk0;
    u8 pad1;
    s16 unk2;
    s16 unk4;
    u8 unk6;
    u8 unk7;
} E2Ent;

extern E2Ent D_80755DA8[];

s32 func_80731784(s16 arg0, s16 arg1, s32 *arg2) {
    E2Ent *e;
    s32 n = 0x1F;
    s32 i;

    *arg2 = 0;
    for (i = 0; i < n; i++) {
        e = &D_80755DA8[i ^ 0];
        if (arg0 == e->unk0 && arg1 == e->unk2) {
            return e->unk4;
        }
        *arg2 = i + 1;
    }
    return -1;
}
