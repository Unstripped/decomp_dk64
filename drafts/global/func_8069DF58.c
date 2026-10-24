// func_8069DF58 (src/global/9DD70.c): stage 6: identical except one dead 'move a0,s0' in the bnezl delay slot (target: plain bnez + lw v1,0x174(s0)) and model spill 0x2c vs 0x28
extern Actor *D_807FBB40;
void func_806319C4(Actor *, s32);
s32 func_8069DC80(u8, void *, u8, u8, u8);

void func_8069DF58(void) {
    Actor *actor;
    s32 *model;

    actor = D_807FBB40;
    if (!(actor->unk60 & 0x10)) {
        model = (s32 *)actor->unk174;
        model[0] = func_8069DC80(0x14, (void *)model[0], 0, actor->unk155[0] / 10, 0x10);
        model[1] = func_8069DC80(0x14, (void *)model[1], 1, D_807FBB40->unk155[0] % 10, 0x10);
        actor = D_807FBB40;
    }
    func_806319C4(actor, 0);
}
