// func_80613AF8 (src/global/17B90.c): stage 6; permuter best 125; remaining table lookup register allocation and call scheduling
typedef struct { u8 pad0[0x4E]; s16 value; } Perm3GlobalView;
typedef struct { u8 pad0[0x58]; s32 value; } Perm3Controller;
extern Struct807FD580 *D_807FD580;
extern u16 *D_807FBB58;
void func_80613C48(Perm3Controller *, s16, f32, f32);

void func_80613AF8(Perm3Controller *arg0, s16 arg1, f32 arg2, f32 arg3) {
    s32 flag;
    s16 index;
    u16 *table;
    s32 value;

    if (arg1 >= 0) {
        flag = arg1 & 0x4000;
        index = arg1 - flag;
        ((Perm3GlobalView *)D_807FD580)->value = index;
        value = arg0->value;
        table = D_807FBB58;
        arg1 = table[((index * 7 + value - 2) & 0xFFFF)] + flag;
    } else {
        ((Perm3GlobalView *)D_807FD580)->value = arg1;
    }
    func_80613C48(arg0, arg1, arg2, arg3);
}
