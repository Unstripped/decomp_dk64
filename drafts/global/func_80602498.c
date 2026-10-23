// func_80602498 (src/global/7130.c): Stage 6, score 25, all insns and schedule matched; diff is t4 vs t5 regalloc in loop counter
typedef signed short s16;
typedef signed int s32;
typedef unsigned char u8;
typedef signed char s8;
typedef float f32;

typedef struct {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    s16 unk6;
    u8 unk8;
    u8 unk9;
} Struct7130_Entry;

typedef struct {
    char pad0[0x210];
    f32 unk210;
    f32 unk214;
    f32 unk218;
} AudPlayerPos;

extern u8 D_80745654;
extern s8 D_80745650;
extern u8 D_80770DC9;
extern u8 D_80770DD8[];
extern AudPlayerPos *D_807FC924;
extern s32 D_8076A0A8;
extern Struct7130_Entry D_807459FC[];

s16 func_806531B8(f32, f32, f32, s32);
void func_80602A94(s32, f32);

void func_80602498(void) {
    u8 i;
    s16 count;
    s16 v0;
    Struct7130_Entry *entry;

    D_80745650 = 1;
    if (D_80745654 != 0) {
        if (D_80770DD8[1] == 0xFF) {
            D_80770DD8[1] = 0;
        }
        return;
    }

    count = 29;
    v0 = func_806531B8(D_807FC924->unk210, D_807FC924->unk214, D_807FC924->unk218, 0);

    i = 0; do {
        entry = &D_807459FC[i];
        if (D_8076A0A8 == entry->unk0 && v0 == entry->unk2) {
            D_80770DC9 = entry->unk8;
            func_80602A94(entry->unk4, 1.0f);
            if (entry->unk6 != 0) {
                count = entry->unk6;
                D_80770DD8[1] = count;
            }
            return;
        }
    } while (++i < count);

    D_80770DD8[1] = 0xFF;
}
