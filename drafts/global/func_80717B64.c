// func_80717B64 (src/global/11BC10.c): Accurate control flow and inferred state layouts; register allocation/stack frame mismatch.
typedef struct {
    u8 pad0[0x330];
    void *unk330;
    u8 pad334[4];
    void *unk338;
    u8 pad33C[4];
    f32 unk340;
    f32 unk344;
    f32 unk348;
    s16 unk34C;
    u8 pad34E[2];
    u8 unk350;
    u8 pad351[0xB];
    s32 unk35C;
    f32 unk360;
    f32 unk364;
    u8 pad368[5];
    u8 unk36D;
    u8 pad36E[0x16];
    void *unk384;
} TimedEffectActorView;

typedef struct {
    u8 pad0[0x16];
    s16 unk16;
} Ub2AttachView;

typedef struct {
    s16 unk0;
    s16 unk2;
    s16 unk4;
} Ub2FalloffState;

typedef struct {
    u8 pad0[0x210];
    f32 unk210;
    f32 unk214;
    f32 unk218;
} Ub2PlayerView;

extern Ub2PlayerView *D_807FC924;

void func_80717B64(arg0, arg1)
TimedEffectActorView *arg0;
s8 *arg1;
{
    Ub2FalloffState *sp24;
    f32 sp1C;
    f32 temp_fa1;
    f32 temp_ft4;
    f32 temp_fv0;
    f32 temp_fv0_2;
    f32 temp_fv1;
    s16 temp_v0_2;
    s16 temp_v0_3;
    s32 var_v1_2;
    Ub2FalloffState *temp_v0;
    Ub2FalloffState *var_v1;

    var_v1 = arg0->unk384;
    temp_ft4 = (f32) ((s32) (arg0->unk34C * 3) / 4);
    if (var_v1 == NULL) {
        sp1C = temp_ft4;
        temp_v0 = func_80610FE8(6);
        arg0->unk384 = temp_v0;
        temp_v0->unk0 = 0;
        temp_v0->unk2 = (s16) (((Ub2AttachView *) arg0->unk330)->unk16 * arg0->unk350);
        temp_v0->unk4 = (s16) arg0->unk36D;
        var_v1 = arg0->unk384;
    }
    temp_v0_2 = var_v1->unk0;
    if (temp_v0_2 == var_v1->unk2) {
        *arg1 = 1;
    } else {
        var_v1->unk0 = temp_v0_2 + 1;
    }
    temp_fv0 = D_807FC924->unk218 - arg0->unk348;
    temp_fv1 = D_807FC924->unk210 - arg0->unk340;
    sp1C = temp_ft4;
    sp24 = var_v1;
    temp_fa1 = D_807FC924->unk214 - arg0->unk344;
    temp_fv0_2 = sqrtf((temp_fv0 * temp_fv0) + ((temp_fv1 * temp_fv1) + (temp_fa1 * temp_fa1)));
    if (temp_fv0_2 < temp_ft4) {
        arg0->unk36D = (u8) sp24->unk4;
        return;
    }
    temp_v0_3 = sp24->unk4;
    var_v1_2 = (s32) ((f32) temp_v0_3 * ((temp_fv0_2 - temp_ft4) / ((f32) arg0->unk34C - temp_ft4)));
    if (temp_v0_3 < var_v1_2) {
        var_v1_2 = (s32) temp_v0_3;
    }
    arg0->unk36D = (u8) (temp_v0_3 - var_v1_2);
}
