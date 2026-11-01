// func_80731784 (src/global/135D30.c): stage 6: 30 insns, frame matches. Regalloc diff on a0..a3 (target: arg0 in a0, e in a1, arg1 in a3, i+1 in t3; ours: arg0 in a3, e in a0, arg1 in a1, i+1 in a0)
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
