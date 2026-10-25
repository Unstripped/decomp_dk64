// func_80717930 (src/global/11BC10.c): stage 4: target frame and saved registers match; allocator result timing and FP register allocation remain
typedef struct { s16 unk0, unk2, unk4, unk6, unk8; } Ub1Motion10;
typedef struct { u8 pad0[4]; ActorSub4 *unk4; } Ub1ScaleHolder;
typedef struct { u8 pad0[0x32C]; u8 unk32C; u8 pad32D[0xB]; Ub1ScaleHolder *unk338; u8 pad33C[4]; f32 unk340, unk344, unk348; u8 pad34C[0x10]; s32 unk35C; f32 unk360, unk364; u8 pad368[0x1C]; Ub1Motion10 *unk384; u8 pad388[4]; u16 unk38C; } Ub1ActorView;
extern Actor *D_807FBB4C;
void *func_80610FE8(s32); s32 func_80611A44(void); f32 func_80612790(s16); f32 func_80612794(s16);
void func_80717930(Ub1ActorView *arg0, void *arg1) {
    f32 temp_fv0; f32 var_ft1; s32 temp_v1; Ub1Motion10 *temp_s1; void *temp_v0; Ub1ScaleHolder *temp_v0_2;
    if (arg0->unk384 == NULL) { temp_v0 = func_80610FE8(0xA); arg0->unk384 = temp_v0; ((Ub1Motion10 *)temp_v0)->unk0 = (func_80611A44() >> 0xF) % 4095; ((Ub1Motion10 *)temp_v0)->unk2 = arg0->unk340; ((Ub1Motion10 *)temp_v0)->unk4 = arg0->unk348; temp_v1 = arg0->unk35C; if (temp_v1 & 0x8000) { arg0->unk35C = temp_v1 & 0xFFFF7FFF; ((Ub1Motion10 *)temp_v0)->unk6 = 0xC8; ((Ub1Motion10 *)temp_v0)->unk8 = 0xA; } else { ((Ub1Motion10 *)temp_v0)->unk6 = 0x46; ((Ub1Motion10 *)temp_v0)->unk8 = 0xF; } temp_v0_2 = arg0->unk338; if (temp_v0_2 != NULL) { temp_fv0 = temp_v0_2->unk4->unk38 / 0.15; ((Ub1Motion10 *)temp_v0)->unk8 = ((Ub1Motion10 *)temp_v0)->unk8 * temp_fv0; arg0->unk35C = arg0->unk35C * temp_fv0; } }
    temp_s1 = arg0->unk384; if (arg0->unk38C & 2) { arg0->unk340 = func_80612794(temp_s1->unk0) * arg0->unk35C + D_807FBB4C->unk7C; var_ft1 = func_80612790(temp_s1->unk0) * arg0->unk35C + D_807FBB4C->unk84; } else { arg0->unk340 = func_80612794(temp_s1->unk0) * arg0->unk35C + temp_s1->unk2; var_ft1 = func_80612790(temp_s1->unk0) * arg0->unk35C + temp_s1->unk4; } arg0->unk348 = var_ft1; arg0->unk344 += temp_s1->unk8 * 0.1; temp_s1->unk0 += temp_s1->unk6;
}
