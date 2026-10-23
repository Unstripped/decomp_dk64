// func_80658134 (src/global/55B20.c): stage 4/6: whole body matches target except prologue: target homes a1/a2/a3 but NOT a0 (no sw a0,0x30/lw reload); any >=4-register-arg call in a probe makes IDO home a0, so source shape unknown; slots for n1/n2 must be 0x24/0x28
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

s32 func_80658134(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 n1 = 0;
    s32 n2 = 0;

    D_807F6C88 = D_807F6C14[arg0].unk0[0];
    D_807F6C8C = D_807F6C14[arg0].unk10[0];
    D_807F6C90 = D_807F6C14[arg0].unk20[0];
    D_807F6C94 = D_807F6C14[arg0].unk0[1];
    D_807F6C98 = D_807F6C14[arg0].unk10[1];
    D_807F6C9C = D_807F6C14[arg0].unk20[1];
    D_807F6CA0 = D_807F6C14[arg0].unk0[2];
    D_807F6CA4 = D_807F6C14[arg0].unk10[2];
    D_807F6CA8 = D_807F6C14[arg0].unk20[2];
    D_807F6CAC = D_807F6C14[arg0].unk0[3];
    D_807F6CB0 = D_807F6C14[arg0].unk10[3];
    D_807F6CB4 = D_807F6C14[arg0].unk20[3];
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
