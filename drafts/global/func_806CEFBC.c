// func_806CEFBC (src/global/CEAE0.c): stage 5: structure matches; target keeps xm/ym/zm-mids as div.s by 2.0 (use '/ 2' int, not 2.0f which becomes mul 0.5), stores results sp44/sp40/sp3C/sp38 to stack (not promoted in mine, only sp38 stored) and computes all three mids before loading arg0->unk8/unk0; sched/store diffs remain.
typedef struct G05CbArg {
    /* 0x0 */ f32 unk0;
    /* 0x4 */ Actor *unk4;
    /* 0x8 */ Actor *unk8;
} G05CbArg;

s32 func_806CF2EC(s32 *, s32 *);
void actorGetNodePos(void *, s32, f32 *, f32 *, f32 *);
void func_8067A70C(Actor *, Actor *, f32, f32, f32, s32, s32);

void func_806CEFBC(G05CbArg *arg0) {
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

    func_806CF2EC(&sp34, &sp30);
    actorGetNodePos(arg0->unk4, sp34, &sp60, &sp58, &sp50);
    actorGetNodePos(arg0->unk4, sp30, &sp64, &sp5C, &sp54);
    sp4C = (sp64 + sp60) / 2;
    sp48 = (sp5C + sp58) / 2;
    sp44 = (sp54 + sp50) / 2;
    sp40 = (sp4C - arg0->unk8->unk7C) * arg0->unk0 + arg0->unk8->unk7C;
    sp3C = (sp48 - arg0->unk8->unk80) * arg0->unk0 + arg0->unk8->unk80;
    sp38 = (sp44 - arg0->unk8->unk84) * arg0->unk0 + arg0->unk8->unk84;
    func_8067A70C(arg0->unk4, arg0->unk8, sp40, sp3C, sp38, 2, 1);
}
