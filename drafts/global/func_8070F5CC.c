// func_8070F5CC (src/global/114270.c): stage 1: full pool setup, allocation, and random entry initialization reconstructed and compiled; frame/save set still differs
typedef struct R114c4SpawnView {
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
} R114c4SpawnView;

typedef struct R114c4EffectPool {
    u16 count;
    u8 unk2[2];
    R114c4SpawnView *entries;
} R114c4EffectPool;

typedef struct R114c4TextureSetup {
    u8 count;
    u8 type;
    u8 unk2[2];
    u16 *images;
    u8 unk8[2];
    u8 width;
    u8 height;
    s32 unkC;
    s32 unk10;
} R114c4TextureSetup;

typedef struct R114c4PlayerView {
    u8 unk0[0x210];
    f32 unk210;
    f32 unk214;
    f32 unk218;
    u8 unk21C[0xA8];
    f32 unk2C4;
} R114c4PlayerView;

extern u16 *D_807550E0;
extern u8 D_80755264;
extern u32 D_807FD9F0[];
extern u8 D_807FDA18;
extern u8 D_807FDA19;
extern s32 D_807FDA20;
extern s32 D_807FDA24;
extern u8 D_807FDA1A;
extern u8 D_807FDA1C;
extern u8 D_807FDA28;
extern u8 D_807FDA30;
extern void *D_807FC924;
void *func_80610FE8(s32);
void heapClearBlock(void *);
u32 func_80611A44(void);
void *func_8066B0F8(s32, s32, s32, s32);

void func_8070F5CC(u8 type, s16 arg1, f32 arg2, s16 arg3, s32 arg4, s32 arg5) {
    R114c4EffectPool *pool;
    R114c4SpawnView *entry;
    R114c4TextureSetup *setup;
    s16 i;
    s32 random;

    pool = (R114c4EffectPool *)D_807550E0;
    if (pool->count >= 0x80) {
        return;
    }
    if ((pool->count == 0) && (D_807FDA28 == 0)) {
        pool->entries = func_80610FE8(0x5C00);
        heapClearBlock(pool->entries);
        D_807FDA1C = type;
        setup = (R114c4TextureSetup *)((u8 *)&D_80755264 + (type * 0x14));
        for (i = 0; i < setup->count; i++) {
            D_807FD9F0[i] = (u32)func_8066B0F8(setup->type != 0 ? 0x19 : 7, setup->images[i], 1, 1);
        }
        D_807FDA18 = setup->width;
        D_807FDA19 = setup->height;
        D_807FDA20 = setup->unkC;
        D_807FDA24 = setup->unk10;
        D_807FDA28 = 1;
    }
    entry = &pool->entries[D_807FDA1A--];
    (&D_807FDA30)[D_807FDA1A + 1] = 0xFF;
    entry->unkB0 = 1;
    entry->unk4 = (f32)arg3;
    entry->unk8 = (f32)arg3;
    entry->unkC = (f32)(s16)arg4;
    entry->unk10 = arg2;
    entry->unk0 = arg1;
    entry->unkB1 = (u8)arg5;
    entry->unk14 = ((R114c4PlayerView *)D_807FC924)->unk2C4;
    entry->unk18 = ((R114c4PlayerView *)D_807FC924)->unk210;
    entry->unk1C = ((R114c4PlayerView *)D_807FC924)->unk218;
    random = (s32)(func_80611A44() >> 0xF) % 32767;
    entry->unk20 = (s16)(random % 0xFFF);
    random = (s32)(func_80611A44() >> 0xF) % 32767;
    entry->unk22 = (s16)(random % 360);
    switch (D_807FDA1C) {
    case 3:
        random = (s32)(func_80611A44() >> 0xF) % 32767;
        entry->unk28 = (f32)((f64)(random % 100) * 0.02);
        break;
    case 4:
    case 5:
        entry->unk20 = (s16)((s32)(func_80611A44() >> 0xF) % 20 + 5);
        entry->unk22 = 0;
        entry->unk28 = (f32)((s32)(func_80611A44() >> 0xF) % 70 + 30);
        if (((s32)(func_80611A44() >> 0xF) % 100) >= 81) {
            entry->unkB3 = 200;
        } else {
            entry->unkB3 = (u8)((s32)(func_80611A44() >> 0xF) % 6 + 5);
        }
        break;
    default:
        random = (s32)(func_80611A44() >> 0xF) % 32767;
        entry->unk28 = (f32)((f64)(random % 100) * 0.1);
        break;
    }
    pool->count++;
}
