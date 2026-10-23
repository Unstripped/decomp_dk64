// func_8065FB64 (src/global/63EC0.c): near-miss: exact 0x98 frame (inlined floats fixed 0xa0 bloat), loop regalloc
typedef struct R1B63810_Struct_6C18 {
    u8 unk0;
    u8 pad1[2];
    u8 unk3;
    u8 pad4[0x64];
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
    u8 pad14[0x32];
    s16 unk46;
    s16 unk48;
    s16 unk4A;
    s16 unk4C;
    s16 unk4E;
    s16 unk50[11];
    u8 unk66;
    u8 unk67;
    u8 unk68;
} R1B63810_Target;

typedef struct R1B63810_Node {
    R1B63810_Target *target;
    f32 unk4;
    u8 pad8[8];
    f32 x;
    f32 y;
    f32 z;
    s32 unk1C[4];
    u8 pad2C[0x14];
    s16 unk40;
    s16 unk42;
    s16 unk44;
    s16 unk46;
    s16 unk48;
    u8 pad4A[2];
    u8 unk4C;
    u8 pad4D[3];
    struct R1B63810_Node *next;
} R1B63810_Node;

extern R1B63810_Struct_6C18 *D_807F6C18;
extern R1B63810_Node *D_807F93C0;
extern s32 D_807FBB60;
extern u8 D_807444FC;
extern f32 D_8076A0B4[];
extern f32 D_8076A0B8[];
extern f32 D_8076A0BC[];
extern void *D_807F78C0;
extern f32 D_807F7EEC;
extern f32 D_807F7EF0;
extern f32 D_807F7EF4;

s32 func_8065BAA0(f32, f32, f32, s16, s32, s32, s32, s32, s32, s32, u8 *);
void func_8065C990(s32, s32, s32, void *, s32, s32);

void func_8065FB64(f32 arg0, f32 arg1, f32 arg2) {
    u8 sp8F;
    R1B63810_Node *node = D_807F93C0;

    if (node != NULL) {
        do {
            u8 flags = node->unk4C;
            if ((flags & 1) && !(flags & 2)) {
                R1B63810_Target *target = node->target;
                s16 s1 = target->unk50[0];
                if (target->unk68 != 0) {
                    s32 v0 = func_8065BAA0(arg0, arg1, arg2, target->unk46,
                                           (s32)(((f32)target->unk4E + node->unk4) - (target->unk10 + target->unkC)), target->unk48, target->unk4A,
                                           (s32)(((f32)target->unk4E + node->unk4) + (target->unk10 + target->unkC)), target->unk4C, s1, &sp8F);
                    D_807F7EEC = D_8076A0B4[s1];
                    D_807F7EF0 = D_8076A0B8[s1];
                    D_807F7EF4 = D_8076A0BC[s1];
                    if (D_807FBB60 & 0x10) {
                        s32 temp_a0 = node->unk1C[D_807444FC];
                        func_8065C990(temp_a0, temp_a0 + node->unk48 * 16, 1, &D_807F78C0, v0, D_807F6C18[s1].unk3 == 1);
                    }
                    node->unk4C |= 2;
                }
            }
            node = node->next;
        } while (node != NULL);
    }
}
