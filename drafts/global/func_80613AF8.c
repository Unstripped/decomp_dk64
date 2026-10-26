// func_80613AF8 (src/global/17B90.c): stage 6; exact control flow/instruction count; remaining diff is integer register allocation in table lookup
typedef struct { u8 pad[0x4E]; s16 value; } Global;
typedef struct { u8 pad[4]; void *unk4; u8 pad2[0x50]; s32 value; } Controller;
extern Global *D_807FD580;
extern u16 *D_807FBB58;
void func_80613C48(void *, s16, f32, f32);
void func_80613AF8(Controller *arg0, s16 arg1, f32 arg2, f32 arg3) {
    s32 flag;
    s16 index;
    u16 *table;
    s32 value;
    if (arg1 >= 0) {
        flag = arg1 & 0x4000;
        index = arg1 - flag;
        D_807FD580->value = index;
        value = arg0->value;
        table = D_807FBB58;
        arg1 = table[((index * 7 + value - 2) & 0xFFFF)] + flag;
    } else D_807FD580->value = arg1;
    func_80613C48(arg0, arg1, arg2, arg3);
}
