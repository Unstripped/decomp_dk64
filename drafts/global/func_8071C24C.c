// func_8071C24C (src/global/11BC10.c): stage 3: compiled collision/light starter; current C has 0x78 frame versus target 0x58 from call ABI/prototype mismatches and needs local/layout refinement
typedef struct { u8 pad0[0x340]; f32 unk340; f32 unk344; f32 unk348; u8 pad34C[0x38]; void *unk384; } Ub6GroundActorView;
s32 collisionCheckGroundAtPoint(f32, f32, u8 *, f32 *);
void func_806086CC();
void func_80714944();
void lightAdd(f32, f32, f32, f32, f32, f32, f32, s32, s32, s32, s32);
void func_8071C004();
extern u8 D_8071FB54;
void func_8071C24C(Ub6GroundActorView *arg0, u8 *arg1) {
    f32 sp50; s16 sp4C; s16 sp4A; s16 sp48; f32 *temp_v0; f32 *temp_v0_2;
    if (arg0->unk384 == NULL) { temp_v0 = func_80610FE8(0xC); arg0->unk384 = temp_v0; *temp_v0 = 6.0f; }
    if (D_8076A0A8 == 0xAA) { sp4A = 0x46; sp48 = 0xFF; sp4C = 0; } else { sp4C = 0xFF; sp48 = 0xFF; sp4A = 0xFF; }
    temp_v0_2 = arg0->unk384; arg0->unk340 += 1.0f; arg0->unk344 += *temp_v0_2; *temp_v0_2 = (f32)((f64)*temp_v0_2 - 0.15); sp50 = arg0->unk344;
    if (collisionCheckGroundAtPoint(arg0->unk340, arg0->unk348, arg1, &sp50) == 0) *arg1 = 1;
    else if ((arg0->unk344 < sp50) && ((f64)*(f32 *)arg0->unk384 < 0.0)) *arg1 = 1;
    if (*arg1 != 0) { func_806086CC(arg0->unk340, arg0->unk344, arg1, arg0->unk348, 0xEA, 0xFF, 0x7F, 0x1E, 0x46, 9.0f, 0); func_80714998(2); func_807149B8(1); func_80714950(1); func_8071498C(&func_8071C004); func_80714944(7); func_80714CC0((s32)&D_8071FB54, 0.6666667f, arg0->unk340, sp50 + 10.0f, arg0->unk348); }
    lightAdd(arg0->unk340, arg0->unk344, arg0->unk348, 0.0f, 0.0f, 0.0f, 200.0f, 0, sp48, sp4A, sp4C);
}
