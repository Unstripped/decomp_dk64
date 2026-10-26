// func_806192A4 (src/global/19A00.c): stage 3: behavioral m2c translation compiles; frame is 0x50 vs target 0x48, stack locals are +8, and branch 4/5/3 rodata scheduling differs.
typedef struct { s16 unk0; s16 unk2; Actor *unk4; s32 unk8; s16 unkC; u8 padE[2]; f32 unk10; } P19L192NodeState;
typedef struct { u8 pad0[0x64]; u16 unk64; } P19L192ActorSub4;
typedef struct { u8 pad0[4]; ActorSub4 *unk4; u8 pad8[0x4C]; s32 unk54; u8 pad5C[0x8C]; s16 unkE4; s16 unkE6; s16 unkE8; u8 padEA[0x6A]; u8 unk154; u8 pad155[0x1F]; P19L192NodeState *unk174; } P19L192ActorView;
extern void *D_80746B80[];
void actorSpawn(s32, u16);
void func_8067B238(Actor *, Actor *, f32);
void func_80714998(s32);
void func_807149C8(s32, s32, s32, s32);

void func_806192A4(Actor *arg0) {
    u16 sp46, sp44, sp42, sp40;
    P19L192NodeState *sp38;
    f32 var_fs0;
    s32 temp_v0;
    P19L192NodeState *var_v1;
    var_fs0 = (f32)((f64)arg0->unk4->unk38 / 0.15);
    func_80614F4C((u8 *)&sp46); func_80614F4C((u8 *)&sp44); func_80614F4C((u8 *)&sp42); func_80614F4C((u8 *)&sp40);
    actorSpawn(0x139, sp42);
    func_8067B238(D_807FBB44, arg0, arg0->unk4->unk34);
    ((P19L192ActorView *)D_807FBB44)->unkE6 = ((P19L192ActorView *)arg0)->unkE6;
    ((P19L192ActorView *)D_807FBB44)->unkE8 = ((P19L192ActorView *)arg0)->unkE8;
    ((P19L192ActorView *)D_807FBB44)->unkE4 = ((P19L192ActorView *)arg0)->unkE4;
    var_v1 = ((P19L192ActorView *)D_807FBB44)->unk174; var_v1->unk10 = 0.0f;
    if (sp46 != 0xFFFF) {
        sp38 = var_v1; func_807149FC(-1); func_807149B8(1); temp_v0 = arg0->unk58;
        switch (temp_v0) {
            default: var_fs0 = (f32)((f64)var_fs0 * 0.2); break;
            case 0xBB: sp38 = var_v1; var_fs0 = (f32)((f64)var_fs0 * 0.4); func_807149C8(0, 0xFF, 0, 0xFF); break;
            case 4: case 5: sp38 = var_v1; func_80714998(0); var_v1->unk10 = -1.4f; var_fs0 = (f32)((f64)var_fs0 * 0.18); break;
            case 3: sp38 = var_v1; func_80714998(0); var_v1->unk10 = -1.4f; var_fs0 = (f32)((f64)var_fs0 * 0.25); break;
        }
    }
    D_807FBB44->unk80 -= var_v1->unk10;
    if (sp46 != 0xFFFF) { sp38 = var_v1; func_80714C08(D_80746B80[sp46], var_fs0, D_807FBB44, 1, 2); }
    var_v1->unk4 = arg0; var_v1->unk0 = sp44; var_v1->unk8 = ((P19L192ActorView *)arg0)->unk54; var_v1->unkC = ((P19L192ActorSub4 *)arg0->unk4)->unk64; var_v1->unk2 = sp40;
}
