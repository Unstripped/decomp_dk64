// func_8062EDA8 (src/global/2F550.c): stage 5: same loop/branch shape (41 vs 46 insns); target keeps the output pointer in callee-saved s0 (frame 8, sw s0/lw s0) and a1 homed at 12(sp), ours uses a3/v1 with no s0 and no frame. Tried indexed loop and m2c-style p/q locals.
typedef struct R2F550a2Chunk {
    /* 0x00 */ u8 unk0;
    /* 0x01 */ u8 unk1;
    /* 0x02 */ u8 pad2[6];
    /* 0x08 */ s32 unk8;
    /* 0x0C */ u8 padC[0x70];
} R2F550a2Chunk; /* 0x7C */

extern u8 D_807F5FC1;
extern R2F550a2Chunk *D_807F5FC4;

typedef struct R2F550a2Cmd {
    u32 unk0;
    u32 unk4;
} R2F550a2Cmd;

R2F550a2Cmd *func_8062EDA8(R2F550a2Cmd *arg0, u8 arg1) {
    R2F550a2Cmd *p;
    R2F550a2Cmd *q;
    R2F550a2Chunk *c;
    s32 i;

    p = arg0;
    for (i = 0; i < D_807F5FC1; i++) {
        c = &D_807F5FC4[i];
        if (arg1 == c->unk1) {
            q = p;
            q->unk0 = ((c->unk0 * 4) & 0xFFFF) | 0xDB060000;
            p++;
            q->unk4 = D_807F5FC4[i].unk8;
        }
    }
    return p;
}
