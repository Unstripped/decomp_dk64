// func_8065F964 (src/global/63EC0.c): near-miss: exact instruction count (104 insns), stack layout/frame size 0xc8 vs 0xd0
typedef struct R1B63810_Struct_6C18 {
    u8 unk0;
    u8 pad1[0x67];
    s32 unk68;
    s32 unk6C;
    s32 unk70;
    s32 unk74;
    u8 pad78[0x150];
} R1B63810_Struct_6C18;

typedef struct R1B63810_Target {
    u8 pad0[0xC];
    f32 unkC;
    f32 unk10;
    u8 pad14[0x3C];
    s16 unk50[11];
    u8 unk66;
    u8 unk67;
} R1B63810_Target;

typedef struct R1B63810_Node {
    R1B63810_Target *target;
    u8 pad4[0xC];
    f32 x;
    f32 y;
    f32 z;
    u8 pad1C[0x24];
    s16 unk40;
    s16 unk42;
    s16 unk44;
    s16 unk46;
    u8 pad48[4];
    u8 unk4C;
    u8 pad4D[3];
    struct R1B63810_Node *next;
} R1B63810_Node;

extern R1B63810_Struct_6C18 *D_807F6C18;

void func_80657E24(s32, s32, s32, s32, s32, s32, s32, s32, s32 *, s32 *, s32 *, s32 *);
void func_806545D4(s32, s32, s32, s32, f32, f32, f32, u8, s32, s32, void *);

void func_8065F964(R1B63810_Node *arg0, f32 arg1, f32 arg2, f32 arg3, u8 arg4, s32 arg5, s32 arg6) {
    s32 spB4;
    s32 spB0;
    s32 spAC;
    s32 spA8;
    u8 sp70[0x38];
    R1B63810_Target *target = arg0->target;
    s32 s2 = 0;
    s32 s3 = 0;
    s32 s4 = 0;
    s32 s5 = 0;
    s32 i;

    for (i = 0; i < target->unk67; i++) {
        R1B63810_Struct_6C18 *entry = &D_807F6C18[target->unk50[i]];
        if (entry->unk0 == 1) {
            func_80657E24(s2, s3, s4, s5, entry->unk68, entry->unk6C, entry->unk70, entry->unk74, &spB4, &spB0, &spAC, &spA8);
            s2 = spB4;
            s3 = spB0;
            s4 = spAC;
            s5 = spA8;
        }
    }
    func_806545D4(s2, s3, s4, s5, arg1, arg2, arg3, arg4, arg5, arg6, sp70);
    arg0->unk40 = s2;
    arg0->unk42 = s3;
    arg0->unk44 = s4;
    arg0->unk46 = s5;
}
