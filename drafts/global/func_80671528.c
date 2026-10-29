// func_80671528 (src/global/70FD0.c): stage 6 (also parked NON_MATCHING in copy): frame 0x88, all insns/stack/relocs match, only FP temp numbering differs from the 2nd cvt group on (target mtc1 f18/cvt f6/div f10, mine f6/f18/f10). volatile u8 arg4 reproduces lbu 0x9b reload; (f32)x / 8 keeps div.s. Tried: arg4 types, v1/v2 order, dead-if sweep on 5 globals, no-code casts per conversion (512 masks), /(f32)8.
typedef struct Col7DPlaneActor {
    u8 pad0[0x60];
    u32 unk60;
} Col7DPlaneActor;

typedef struct Col7DPlaneSub {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    u8 pad10[0xB0 - 0x10];
    s32 unkB0;
    s32 unkB4;
} Col7DPlaneSub;

extern CollisionBox *D_807FB5D4;

void func_80671528(arg0, arg1, arg2, arg3, arg4)
ActorTargetWork *arg0;
f32 *arg1;
f32 *arg2;
f32 *arg3;
volatile u8 arg4; // FAKE: reload arg4 from its stack home after the calls
{
    CollisionBox *box;
    f32 padA;
    Col7DPlaneSub *sub;
    f32 v1[3];
    f32 v2[3];
    f32 n[3];
    f32 padB;
    f32 x[3];
    f32 y[3];
    f32 z[3];
    f32 inv_len;

    sub = (Col7DPlaneSub *)arg0->unk140;
    if (arg4 != 0) {
        box = (CollisionBox *)func_806732A8(D_807FB5DC, D_807FB5F6);
    } else {
        box = D_807FB5D4;
    }
    x[0] = (f32)box->unk24 / 8;
    y[0] = (f32)box->unk28 / 8;
    z[0] = (f32)box->unk2C / 8;
    x[1] = (f32)box->unk30 / 8;
    y[1] = (f32)box->unk34 / 8;
    z[1] = (f32)box->unk38 / 8;
    x[2] = (f32)box->unk3C / 8;
    y[2] = (f32)box->unk40 / 8;
    z[2] = (f32)box->unk44 / 8;

    v1[0] = x[2] - x[0];
    v1[1] = y[2] - y[0];
    v1[2] = z[2] - z[0];

    v2[0] = x[1] - x[0];
    v2[1] = y[1] - y[0];
    v2[2] = z[1] - z[0];

    n[0] = (v1[1] * v2[2]) - (v2[1] * v1[2]);
    n[1] = (v1[2] * v2[0]) - (v2[2] * v1[0]);
    n[2] = (v1[0] * v2[1]) - (v2[0] * v1[1]);

    inv_len = 1.0f / sqrtf((n[2] * n[2]) + ((n[0] * n[0]) + (n[1] * n[1])));
    *arg1 = n[0] * inv_len;
    *arg2 = n[1] * inv_len;
    *arg3 = n[2] * inv_len;

    func_806744A8((ActorFacingWork *)box, sub->unk0, sub->unk4, sub->unk8, sub->unkC);
    if (arg4 != 0) {
        if (((Col7DPlaneActor *)arg0)->unk60 & 0x800) {
            D_807FB5C4 = sub->unkB0;
            D_807FB5CC = sub->unkB4;
        }
        sub->unkB0 = D_807FB5C4;
        sub->unkB4 = D_807FB5CC;
    }
}
