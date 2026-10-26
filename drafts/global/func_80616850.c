// func_80616850 (src/global/19A00.c): stage 4: reordered state save reduces to score 40; remaining diff is initial global/state register allocation (a1/v0 versus v0/v1).
typedef struct P19dState {
    u8 pad0[0x5C];
    u16 unk5C;
    u8 pad5E[2];
    s32 unk60;
    u16 unk64;
    u8 pad66[2];
    u8 *unk68;
    u8 *unk6C;
    void (*unk70)(Actor *);
    s32 unk74;
    s32 unk78;
    s32 unk7C;
    f32 unk80;
    s32 unk84;
    s32 unk88;
} P19dState;

extern u8 *D_807F5AF0;
extern s32 D_807F5AF4;
void func_80614F4C(u8 *);
void func_80614EBC(Actor *, u16);

s32 func_80616850(Actor *arg0) {
    s32 sp24;
    u16 sp22;
    P19dState *sp1C;

    sp1C = (P19dState *)arg0->unk4;
    sp24 = sp1C->unk88;
    D_807F5AF0++;
    func_80614F4C((u8 *)&sp22);
    sp1C->unk5C = sp1C->unk64;
    sp1C->unk60 = D_807F5AF0 - sp1C->unk68;
    func_80614EBC(arg0, sp22);
    D_807F5AF0 = sp1C->unk6C;
    sp1C->unk88 = sp24;
    return D_807F5AF4;
}
