// func_80731784 (src/global/135D30.c): regalloc only: copies x=arg0,y=arg1 give arg0 in place a0 (target) but y lands a1/e a3 (target y a3/e a1, temp i+1 in t3, widen arg1 first). Tried dead reads, &0xFFFFFFFFu, operand swaps, permuter 200+300s.
typedef struct E2Ent {
    /* 0x0 */ u8 unk0;
    /* 0x1 */ u8 pad1;
    /* 0x2 */ s16 unk2;
    /* 0x4 */ s16 unk4;
    /* 0x6 */ u8 unk6;
    /* 0x7 */ u8 unk7;
} E2Ent;

extern E2Ent D_80755DA8[];

s32 func_80731784(s16 arg0, s16 arg1, s32 *arg2) {
    E2Ent *e;
    s32 n = 0x1F;
    s32 i;
    s32 y;
    s32 x;

    y = arg1;
    x = arg0;
    *arg2 = 0;
    for (i = 0; i < n; i++) {
        e = &D_80755DA8[i ^ 0];
        if (x == e->unk0 && y == e->unk2) {
            return e->unk4;
        }
        *arg2 = i + 1;
    }
    return -1;
}
