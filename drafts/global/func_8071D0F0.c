// func_8071D0F0 (src/global/11BC10.c): stage 6 (parked NON_MATCHING in 11BC10.c): 92 insns exact match, all stack homes match. Remaining 14 diff lines purely regalloc: pre-call motion in t0 vs v1 cascades lui D_807FD580 v0 vs t1 and D_807FBB4C load t1 vs t0
typedef struct {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
} FxInt1Motion16;

void actorGetNodePos(s32, s32, f32 *, f32 *, f32 *);
u8 func_805FF030(u8, u8);
extern u8 D_8076A0AB;
extern u16 D_807FC930[];

void func_8071D0F0(TimedEffectActorView *arg0, s8 *arg1) {
    FxInt1Motion16 *motion;
    LightOwnerView **lightNodePtr;
    s32 node;
    f32 factor;
    f64 pad;

    node = arg0->unk35C;
    motion = arg0->unk384;
    if (motion == NULL) {
        motion = func_80610FE8(0x10);
        arg0->unk384 = motion;
        motion->unk0 = 30.0f;
        motion = arg0->unk384;
    }
    actorGetNodePos(node, 1, &motion->unk4, &motion->unk8, &motion->unkC);
    factor = (f32)((f64)motion->unk0 / 30.0);
    arg0->unk340 = (D_807FBB4C->unk7C - motion->unk4) * factor + motion->unk4;
    lightNodePtr = &D_807FD580;
    arg0->unk344 = (D_807FBB4C->unk80 - motion->unk8) * factor + motion->unk8;
    arg0->unk348 = (D_807FBB4C->unk84 - motion->unkC) * factor + motion->unkC;
    motion->unk0 -= 1.0f;
    if (motion->unk0 == 0.0f) {
        if (D_807FBB4C && D_807FBB4C) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
        *(s32 *)((u8 *)(*lightNodePtr) + 0x1F0) |= 0x20000;
        D_807FC930[func_805FF030(D_8076A0AB, 0)]++;
        *arg1 = 1;
    }
}
