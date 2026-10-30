// func_806EB400 (src/global/EFDC0.c): Stage 4 (frame 0, no saved regs; 8 text lines): park matches the || result copy 'move a1,v1' but the return value lives in cfe temp #1328 (v1, shared by the || value and the ternary) and the state byte takes v0; target keeps pred AND the result in the same variable (a1: 'andi t6,a1,1; move a1,t6' / 'move a1,zero' / 'move v0,a1'), state byte in v1, and branches 'beq 0x34,Z; beq 0x36,Z; andi in delay'. uopt_trace -l 6: candidates sub(v0) tmp1328(v1) arg0(a0) pred(a1) and state(v0); the target needs the ternary result outside tmp1328 (so state can reuse v1) while def1 of pred keeps its copy (copy-prop removes it whenever pred's only use is the else-arm 'x &= 1'). Tried: x/pred/r variable splits x u8 s8 u16 s16 u32 s32 int, if/else, ternary-assign, !(A||B), nested ternaries, comma, compound &=, named state locals, dead 'if (sub)' (no effect), deadsweep with sub/pred/arg0 extras, 2 permuter runs + 7 min -j 2 (no score below base).
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
