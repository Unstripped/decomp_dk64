// func_8070F5CC (src/global/114270.c): stage 1: local spawn-entry view and initializer compiled; pool setup and random initialization remain
typedef struct R114bSpawnView {
    s16 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    f32 unk14;
    f32 unk18;
    f32 unk1C;
    s16 unk20;
    s16 unk22;
    f32 unk24;
    f32 unk28;
    u8 unk2C[0x84];
    u8 unkB0;
    u8 unkB1;
    u8 unkB2;
    u8 unkB3;
} R114bSpawnView;

extern u16 *D_807550E0;

void func_8070F5CC(s32 type, s16 arg1, f32 arg2, s16 arg3, s16 arg4, s32 arg5) {
    R114bSpawnView *entry;
    s32 index;

    if (*D_807550E0 >= 0x80) {
        return;
    }
    index = *D_807550E0;
    entry = (R114bSpawnView *)((u8 *)D_807550E0 + 4 + (index * 0xB8));
    entry->unkB0 = 1;
    entry->unk4 = arg3;
    entry->unk8 = arg3;
    entry->unkC = arg4;
    entry->unk10 = arg2;
    entry->unk0 = arg1;
    entry->unkB1 = arg5;
    entry->unk20 = type;
    (*D_807550E0)++;
}
