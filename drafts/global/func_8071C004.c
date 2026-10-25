// func_8071C004 (src/global/11BC10.c): stage 3: compiled state/light starter; frame 0x50 vs target 0x58 and callback/light helper prototypes and branch shape still differ
typedef struct { u8 pad0[0x16]; s16 unk16; } Ub6CData;
typedef struct { u8 pad0[0x330]; Ub6CData *unk330; u8 pad334[0xC]; f32 unk340; f32 unk344; f32 unk348; s16 unk34C; s16 unk34E; u8 pad350; u8 unk351; u8 pad352[0xA]; s32 unk35C; } Ub6CActorView;
void func_806086CC();
void func_807149FC(s32);
void lightAdd(f32, f32, f32, f32, f32, f32, f32, s32, s32, s32, s32);
void func_8071C24C();
extern u8 D_807201D4;
void func_8071C004(Ub6CActorView *arg0, s8 *arg1) {
    s16 sp48; s16 sp46; s16 sp44; f32 temp_fv0; s16 temp_v0_2;
    if (D_8076A0A8 == 0xAA) { sp46 = 0x46; sp44 = 0xFF; sp48 = 0; } else { sp48 = 0xFF; sp46 = 0xFF; sp44 = 0xFF; }
    switch (arg0->unk35C) {
    case 0:
        temp_v0_2 = arg0->unk34E;
        if ((temp_v0_2 == 0xA) && (arg0->unk351 == 0)) {
            func_806086CC(arg0->unk340, arg0->unk344, arg0->unk348, 0xE4, 0xFF, 0x7F, 0x1E, 0x46, 9.0f, 0);
            func_807149FC(-1); func_807149B8(1); func_8071498C(&func_8071C24C);
            func_80714CC0((s32)&D_807201D4, 0.8f, arg0->unk340, arg0->unk344, arg0->unk348); return;
        }
        temp_fv0 = (f32)(arg0->unk330->unk16 * 2);
        lightAdd(arg0->unk340, arg0->unk344, arg0->unk348, 0.0f, 0.0f, 0.0f, 200.0f * (f32)(1.0 - (f64)((temp_fv0 - (f32)((temp_v0_2 * 2) + arg0->unk351)) / temp_fv0)), 0, 0xFF, sp46, sp48); return;
    case 1:
        temp_fv0 = (f32)(arg0->unk330->unk16 * 2);
        lightAdd(arg0->unk340, arg0->unk344, arg0->unk348, 0.0f, 0.0f, 0.0f, 200.0f * ((temp_fv0 - (f32)((arg0->unk34E * 2) + arg0->unk351)) / temp_fv0), 0, 0xFF, sp46, sp48); return;
    }
}
