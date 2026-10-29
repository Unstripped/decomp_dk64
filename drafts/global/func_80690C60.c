// func_80690C60 (src/global/936B0.c): stage 5: frame 0x80, s0 only, insn count equal (parked NON_MATCHING). volatile u8 arg3 reproduces re-lbu but adds one extra lbu at merge; target pointer chain uses v0/v1 (mine t9/t0/t1), temp_v1 lh in v1/mflo t9 (mine a2/v1), ratio = dist/(unkB8*0.025f) hoisted before sp78 test (matched via local). Locals for chain/arg3 copy grow frame +8
typedef struct Prj9A_Sub104 {
    u8 pad0[0x104];
    Actor *unk104;
} Prj9A_Sub104;
typedef struct Prj9A_SubF3 {
    u8 pad0[0xF3];
    u8 unkF3;
} Prj9A_SubF3;
typedef struct Prj9A_Aim174 {
    u8 pad0[0x14];
    f32 unk14;
    u8 pad18[4];
    Actor *unk1C;
} Prj9A_Aim174;
extern s32 D_807FBB64;
void func_800268C0(s32);
void func_8071D260(void);
s32 func_80690F30(u16, void **, void *, s32, s32, s32, f32 *, f32 *, f32 *);

void func_80690C60(arg0, arg1, arg2, arg3)
u16 arg0;
Actor *arg1;
void *arg2;
volatile u8 arg3; // FAKE: volatile reproduces the per-path re-lbu of the stack-passed u8 instead of a CSE spill
{
    s32 temp_lo;
    Actor *sp78;
    s16 sp76;
    s16 temp_v1;
    s16 temp_t0;
    s16 sp70;
    s16 sp6E;
    s16 sp6C;
    f32 temp_fv0;
    f32 temp_fv1;
    f32 dist;
    f64 var_ft2;
    u32 temp_t4;
    Prj9A_Aim174 *sp50;
    f32 sp4C;
    f32 sp48;
    f32 sp44;
    f32 var_fv0;
    f32 ratio;

    sp50 = arg1->unk174;
    if (!((f64)arg1->unkB8 < 0.1)) {
        if ((arg2 != 0) && (((Prj9A_SubF3 *)((Prj9A_Sub104 *)((Actor *)arg1->unk11C)->unk174)->unk104->unk174)->unkF3 == 3)) {
            func_8071498C(func_8071D260);
            func_80714950(0x32);
            func_80714CC0(arg2, sp50->unk14, D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84);
        }
        if (func_80690F30(arg0, (void **)&sp78, arg1, 0, arg3, arg3 == 0, &sp4C, &sp48, &sp44) != 0) {
            sp76 = mathAngleBetweenPoints2D(sp4C, sp44, arg1->unk7C, arg1->unk84);
            temp_lo = mathAngleDistance(sp76, arg1->unkEE) / 10;
            temp_v1 = arg1->unkEE;
            temp_t0 = (temp_v1 + temp_lo) & 0xFFF;
            sp6E = (temp_v1 - temp_lo) & 0xFFF;
            sp70 = temp_t0;
            sp6C = mathAngleDistance(temp_t0, sp76);
            if (sp6C < mathAngleDistance(sp6E, sp76)) {
                arg1->unkEE = sp70;
            } else {
                arg1->unkEE = sp6E;
            }
            if (arg3 == 0) {
                temp_fv0 = sp4C - arg1->unk7C;
                temp_fv1 = sp44 - arg1->unk84;
                dist = sqrtf((temp_fv0 * temp_fv0) + (temp_fv1 * temp_fv1));
                if (dist < 100.0f) {
                    sp50->unk1C = sp78;
                    if ((sp78 != NULL) && (D_807FBB64 & 0x04000000)) {
                        func_800268C0(0x80);
                    }
                }
                ratio = dist / (arg1->unkB8 * 0.025f);
                if (sp78 != NULL) {
                    temp_t4 = sp78->unk15E;
                    var_ft2 = temp_t4;
                    var_fv0 = var_ft2 * 0.5;
                } else {
                    var_fv0 = 0.0f;
                }
                arg1->unkC0 = (((sp48 + var_fv0) - arg1->unk80) / ratio) / 0.025f;
            }
        } else if (sp50->unk1C != NULL) {
            if (D_807FBB64 & 0x04000000) {
                func_800268C0(4);
            }
            sp50->unk1C = NULL;
        }
    }
}
