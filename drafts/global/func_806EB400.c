// func_806EB400 (src/global/EFDC0.c): Stage 4 (frame 0, no saved regs): C is behaviourally exact and parked in src under NON_MATCHING. Diff = 6 lines, regalloc only: target keeps result in a1 (andi t6,a1,1; move a1,t6; move a1,zero; move v0,a1) and the state byte in v1; ours puts state in v0 and the ternary result in v1. The pred copy 'move a1,v1' only appears with 'pred = (A||B); ... return c ? 0 : (pred & 1)' (|| value, not a named result var). Tried: named result var / if-else / early-return forms, u8/s32 pred, extra 'if (arg0) {}' liveness, deadsweep (no gain), joined source lines, 2 permuter runs (~12 min total, no gain).
typedef struct EfASubActor {
    u8 pad0[0xD4];
    s16 unkD4;
    u8 padD6[0x11A];
    s32 unk1F0;
} EfASubActor;

#define EfA_Q ((EfAQueuedCall *)D_807FC924)

s32 func_806EB400(Actor *arg0) {
    s32 pred;
    EfASubActor *sub;

    sub = (EfASubActor *)arg0->unk174;
    pred = (sub->unkD4 == 0) || (EfA_Q[D_807FC929].unk29C == 0x3F);
    if ((D_8074E77C[D_807FC929] == 7) || (sub->unk1F0 & 0x8000)) {
        return 0;
    }
    return ((arg0->unk154 == 0x34) || (arg0->unk154 == 0x36)) ? 0 : (pred & 1);
}
