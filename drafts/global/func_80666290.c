// func_80666290 (src/global/699B0.c): regalloc t6 vs v0 in lbu unkCC branch
void actorGetNodePos();
void func_80666428(Actor *, f32, f32, f32, ...);
extern u8 D_807F94B3;
extern u8 D_807F94BC;

void func_80666290(Actor *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, u8 arg5) {
    f32 sp3C;
    f32 sp38;
    f32 sp34;

    D_807F94BC = 0;
    D_807F94B3 = 0;
    if ((arg1 = *(u8*)((u8*)arg0 + 0xCC)) != 0 && arg0->unk110 == 0 && (arg0->unk60 & 0x10)) {
        actorGetNodePos(arg0, arg1, &sp3C, &sp38, &sp34);
    } else {
        sp3C = arg0->unk7C;
        sp38 = arg0->unk8C;
        sp34 = arg0->unk84;
    }
    func_80666428(arg0, sp3C, sp38, sp34, arg1, arg2, arg3, arg4, arg5);
}
