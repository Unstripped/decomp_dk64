// func_806CA1B4 (src/global/CEAE0.c): G02 stage 6: only temp numbering differs: target chain lw t9,4(v1)/lw t0/lh t1 then lhu t2; ours evaluates the G02_P->unk24C lhu first (t9) and chain t0,t1,t2. Matched via ret kept in a2 (func_807270C0 called with 2 args, leftover a2), decl order, ==operand order no effect; local s16 model var or nesting changes idx/ret allocation (a1/v1 swap)
typedef struct G02ModelRef {
    /* 0x00 */ u8 pad0[0x10];
    /* 0x10 */ s16 unk10;
} G02ModelRef;

typedef struct G02PlayerState {
    /* 0x000 */ u8 pad0[0x246];
    /* 0x246 */ s8 unk246;
    /* 0x247 */ s8 unk247;
    /* 0x248 */ s8 unk248;
    /* 0x249 */ u8 unk249;
    /* 0x24A */ u8 unk24A;
    /* 0x24B */ u8 pad24B;
    /* 0x24C */ u16 unk24C;
    /* 0x24E */ u16 unk24E;
} G02PlayerState;

typedef struct G02PlayerSlot {
    /* 0x0 */ s32 unk0;
    /* 0x4 */ Actor *unk4;
    /* 0x8 */ u8 pad8[0x2E8];
} G02PlayerSlot;

#define G02_P ((G02PlayerState *)D_807FD580)
#define G02_MODEL(a) (*(G02ModelRef **)(a)->unk4)

extern G02PlayerSlot *D_807FC924;
Actor *func_807270C0(s32, s32);

s32 func_806CA1B4(s32 arg0) {
    s8 idx = G02_P->unk247;
    s32 ret = 1;
    Actor *actor = NULL;

    if (idx >= 0) {
        actor = D_807FC924[idx].unk4;
    } else {
        s8 temp = G02_P->unk246;

        if (temp > 0) {
            actor = func_807270C0(temp, 0);
        }
    }
    if (actor != NULL && G02_MODEL(actor)->unk10 == G02_P->unk24C && (s32)G02_P->unk24E >= arg0) {
        ret = 0;
    }
    return ret;
}
