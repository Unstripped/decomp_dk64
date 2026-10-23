// func_80658134 (src/global/55B20.c): stage 4: body+frame+slots match; target homes a1/a2/a3 but NOT a0; any 4-register-arg call makes IDO spill a0 to its home slot (sw a0,0x30; lw t7,0x30) then use a temp. Tried: K&R, pointer-local, register, extra locals, permuter
extern f32 D_807F6C88;
extern f32 D_807F6C8C;
extern f32 D_807F6C90;
extern f32 D_807F6C94;
extern f32 D_807F6C98;
extern f32 D_807F6C9C;
extern f32 D_807F6CA0;
extern f32 D_807F6CA4;
extern f32 D_807F6CA8;
extern f32 D_807F6CAC;
extern f32 D_807F6CB0;
extern f32 D_807F6CB4;
extern f32 D_807F6E68[];
extern f32 D_807F6F58[];
extern f32 D_807F6D78[];

void func_806582F8(f32 *, f32 *, s32, s32 *, s32);

s32 func_80658134(arg0, arg1, arg2, arg3)
s32 arg0;
s32 arg1;
s32 arg2;
s32 arg3;
{
    s32 n1 = 0;
    s32 n2 = 0;
    M55P5GridSrc *src;

    src = &D_807F6C14[arg0];
    D_807F6C88 = src->unk0[0];
    D_807F6C8C = src->unk10[0];
    D_807F6C90 = src->unk20[0];
    D_807F6C94 = src->unk0[1];
    D_807F6C98 = src->unk10[1];
    D_807F6C9C = src->unk20[1];
    D_807F6CA0 = src->unk0[2];
    D_807F6CA4 = src->unk10[2];
    D_807F6CA8 = src->unk20[2];
    D_807F6CAC = src->unk0[3];
    D_807F6CB0 = src->unk10[3];
    D_807F6CB4 = src->unk20[3];
    func_806582F8(&D_807F6C88, D_807F6E68, 4, &n2, 0);
    if (n2 == 0) {
        return 0;
    }
    func_806582F8(D_807F6E68, D_807F6F58, n2, &n1, 1);
    if (n1 == 0) {
        return 0;
    }
    func_806582F8(D_807F6F58, D_807F6E68, n1, &n2, 2);
    if (n2 == 0) {
        return 0;
    }
    func_806582F8(D_807F6E68, D_807F6F58, n2, &n1, 3);
    if (n1 == 0) {
        return 0;
    }
    func_806582F8(D_807F6F58, D_807F6D78, n1, &n2, 4);
    if (n2 < 3) {
        n2 = 0;
    }
    return n2;
}
