// func_80613BA0 (src/global/17B90.c): stage 4; sibling of AF8; remaining diff is typed control flow and register allocation
typedef struct { u8 pad[0x4E]; s16 value; } Global;
typedef struct { u8 pad[4]; void *unk4; u8 pad2[0x50]; s32 value; } Controller;
extern Global *D_807FD580;
extern u16 *D_807FBB58;
void func_80613CA8(void *, s16, f32, f32);
void func_80613BA0(Controller *arg0, s16 arg1, f32 arg2, f32 arg3) {
    s32 flag = arg1 & 0x4000;
    s16 index = arg1 - flag;
    if (arg1 >= 0) arg1 = D_807FBB58[((index * 7 + arg0->value - 2) & 0xFFFF)] + flag;
    D_807FD580->value = arg1;
    func_80613CA8(arg0, arg1, arg2, arg3);
}
