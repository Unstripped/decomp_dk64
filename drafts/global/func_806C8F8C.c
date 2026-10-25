// func_806C8F8C (src/global/CC800.c): G01 stage 6 near-miss: s1 for arg0 instead of spill to home 0x20(sp); 0xFF const hoisted into s1; regs shift after
typedef struct G01Sub4 {
    /* 0x00 */ u8 pad0[0x1C];
    /* 0x1C */ u8 *unk1C;
    /* 0x20 */ u8 *unk20;
    /* 0x24 */ u8 *unk24;
} G01Sub4;

typedef struct G01Act {
    /* 0x000 */ u8 pad0[4];
    /* 0x004 */ G01Sub4 *unk4;
    /* 0x008 */ u8 pad8[0x50];
    /* 0x058 */ s32 unk58;
    /* 0x05C */ u8 pad5C[4];
    /* 0x060 */ u32 unk60;
    /* 0x064 */ u8 pad64[0xDC];
    /* 0x140 */ ActorSub140 *unk140;
    /* 0x144 */ u8 pad144[0x34];
    /* 0x178 */ void *unk178;
} G01Act;

typedef struct G01Arg8F8C {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ u8 pad8[2];
    /* 0x0A */ u16 unkA;
    /* 0x0C */ u32 unkC;
} G01Arg8F8C;

#define G01A ((G01Act *)D_807FBB48)

void func_806136B4(Actor *, void *);
void actorSub140Free(ActorSub140 *);
void func_806134B4(Actor *, u16);
ActorSub140 *func_80665F24(Actor *);
void *func_80610FE8(s32);
void func_806C8220(s32, void *, s32);
void func_806F833C(s32);

void func_806C8F8C(void *arg) {
    G01Arg8F8C *arg0 = arg;

    G01A->unk58 = arg0->unk0;
    D_807FD584 = arg0->unk4;
    func_806136B4(D_807FBB48, arg0);
    actorSub140Free(G01A->unk140);
    func_806134B4(D_807FBB48, arg0->unkA);
    G01A->unk140 = func_80665F24(D_807FBB48);
    G01A->unk60 &= ~0x1000;
    G01A->unk60 |= arg0->unkC;
    G01A->unk4->unk1C = func_80610FE8(0x100);
    *G01A->unk4->unk1C = 0;
    G01A->unk4->unk20 = func_80610FE8(0x100);
    *G01A->unk4->unk20 = 0xFF;
    G01A->unk4->unk24 = func_80610FE8(0x100);
    *G01A->unk4->unk24 = 0xFF;
    func_806C8220(1, G01A->unk178, G01A->unk58);
    func_806F833C(0);
}
