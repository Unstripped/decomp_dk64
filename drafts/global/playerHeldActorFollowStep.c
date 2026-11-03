// playerHeldActorFollowStep (src/global/CEAE0.c): W3CountB 2026-11-02: PARKED stage 4, count-exact 73/73, frame 0x68 same, deadsweep full 20 (was draft 15 at 76 insns). Legal: nat lerp forms + two dead tests each legalised by a real def right before it ('sp4C = arg0->unk0; if (!sp4C) {}' ... 'sp3C = 0.0f; if (sp3C == 0.0f) {}'); a block of pre-defs at the top loses the effect (49), uninitialised reads reached the same 20. Remaining diff: target colours mid0 f16 / mid1 f18 as vars (u/v/w/mid2 uncoloured); ours spills mid1 (swc1 72(sp)/lwc1) and forward-substitutes mid2.
typedef struct HeldActorFollowArg {
    /* 0x0 */ f32 unk0;
    /* 0x4 */ Actor *unk4;
    /* 0x8 */ Actor *unk8;
} HeldActorFollowArg;

void func_8067A70C(s32, Actor *, f32, f32, f32, u8, u8);

void playerHeldActorFollowStep(HeldActorFollowArg *arg0) {
    f32 sp64;
    f32 sp60;
    f32 sp5C;
    f32 sp58;
    f32 sp54;
    f32 sp50;
    f32 sp4C;
    f32 sp48;
    f32 sp44;
    f32 sp40;
    f32 sp3C;
    f32 sp38;
    s32 sp34;
    s32 sp30;

    playerGetHoldNodeIndices(&sp34, &sp30);
    actorGetNodePos(arg0->unk4, sp34, &sp60, &sp58, &sp50);
    sp4C = arg0->unk0; // FAKE: legalises the dead test below
    if (!sp4C) {} // FAKE
    actorGetNodePos(arg0->unk4, sp30, &sp64, &sp5C, &sp54);
    sp4C = (sp64 + sp60) / 2;
    sp48 = (sp5C + sp58) / 2;
    sp3C = 0.0f; // FAKE: legalises the dead test below
    if (sp3C == 0.0f) {} // FAKE
    sp44 = (sp54 + sp50) / 2;
    sp40 = (sp4C - arg0->unk8->unk7C) * arg0->unk0 + arg0->unk8->unk7C;
    sp3C = (sp48 - arg0->unk8->unk80) * arg0->unk0 + arg0->unk8->unk80;
    sp38 = (sp44 - arg0->unk8->unk84) * arg0->unk0 + arg0->unk8->unk84;
    func_8067A70C((s32)arg0->unk4, arg0->unk8, sp40, sp3C, sp38, 2, 1);
}
