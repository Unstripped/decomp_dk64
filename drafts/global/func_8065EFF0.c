// func_8065EFF0 (src/global/63810.c): near-miss: loop body arg evaluation order for func_8065A708
typedef struct R1B63810_Struct_EFF0 {
    u8 pad0[4];
    f32 unk4;
    f32 unk8;
    f32 unkC;
    s16 unk10;
    s16 unk12;
    s16 unk14;
    u8 unk16;
    u8 unk17;
    u8 unk18;
    u8 pad19[3];
} R1B63810_Struct_EFF0;

typedef struct R1B63810_Actor174_Sub {
    u8 pad0[0x1F0];
    s32 unk1F0;
} R1B63810_Actor174_Sub;

typedef struct R1B63810_Actor174 {
    u8 pad0[0x174];
    R1B63810_Actor174_Sub *unk174;
} R1B63810_Actor174;

extern s32 D_8076A0A8;
extern R1B63810_Actor174 *D_807FBB4C;
extern s16 D_80748A84;
extern s32 D_807FBB60;
extern s32 D_807FBB68;
extern R1B63810_Struct_EFF0 D_807F9070[];

void func_806595F0(s32);
void func_80659600(s16);
void func_80659610(s16);
void func_8065A708(f32, f32, f32, f32, f32, f32, f32, s32, s32, s32, s32);

void func_8065EFF0(void) {
    s32 i;
    R1B63810_Struct_EFF0 *entry;

    if (D_8076A0A8 == 0x30 && !(D_807FBB4C->unk174->unk1F0 & 0x100000)) {
        D_80748A84 = 0;
        return;
    }

    if (!(D_807FBB60 & 2)) {
        entry = D_807F9070;
        for (i = 0; i < D_80748A84; i++, entry++) {
            if (!(D_807FBB68 & 4)) {
                func_806595F0(2);
            }
            func_80659600(entry->unk12);
            func_80659610(entry->unk14);
            func_8065A708(entry->unk4, entry->unk8, entry->unkC, 0.0f, 0.0f, 0.0f, (f32)entry->unk10, 0, (s32)entry->unk16, (s32)entry->unk17, (s32)entry->unk18);
        }
    }
    D_80748A84 = 0;
}
