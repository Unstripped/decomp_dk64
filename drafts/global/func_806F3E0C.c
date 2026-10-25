// func_806F3E0C (src/global/F56F0.c): Stage 3: reconstructed waypoint aim interpolation; closest raw-pointer draft reaches a 0x60 frame versus the 0x50 target.
typedef struct F5L1Control {
    u16 flags;
    s8 yaw;
    s8 pitch;
} F5L1Control;

typedef struct F5L1Waypoint {
    s16 x;
    s16 y;
    s16 z;
    u8 timer0;
    u8 timer1;
    u8 timer2;
    u8 speed;
    s16 timer3;
    s16 timer4;
    s16 timer5;
    s16 delay;
} F5L1Waypoint;

typedef struct F5L1Target {
    u8 pad0[0x1F0];
    s32 flags;
} F5L1Target;

typedef struct F5L1CamBlock {
    u8 pad0[0x210];
    f32 x;
    u8 pad214[4];
    f32 z;
    u8 pad21C[0xC];
    f32 targetX;
    u8 pad22C[4];
    f32 targetZ;
} F5L1CamBlock;

#define F5L1Cam ((F5L1CamBlock *)D_807FC924)

f32 func_80612D10(f32);
f32 func_80612D1C(f32);
void func_806D03BC(void);
void playerStateQueueCallback(s16, s32, s32, F5L1Waypoint **);
f32 mathAngleBetweenPointsDeg(s16, s16, s32, s32);
f32 mathCalculatePitchAngle(f32, f32, f32, f32, f32, f32, s32);
extern u8 D_807444EC;
extern s8 D_807463B8;
extern u8 D_8076A0B1;
extern s8 D_8076A0B3;
extern s32 D_807FBB60;
extern s16 *D_807FD708;
extern F5L1Waypoint *D_807FD70C;
extern Actor *D_807FD710;
extern s16 D_807FD714;
extern u8 D_807FD716;
extern s16 D_807FD718;
extern s32 D_807FD71C;

void func_806F3E0C(F5L1Control *arg0, s32 arg1) {
    F5L1Target *sp4C;
    f32 sp48;
    f32 sp44;
    f32 sp40;
    F5L1Waypoint *sp3C;
    F5L1Waypoint *sp38;
    f32 sp34;
    f32 sp30;
    s16 sp2E;
    f32 temp_fa0;
    f32 temp_ft1;
    f32 temp_fv0;
    f32 temp_fv0_2;
    f32 temp_fv1;
    f32 var_fv1;
    f32 var_fv1_2;
    f32 var_fv1_3;
    f32 var_fv1_4;
    f32 var_fv1_5;
    f32 var_fv1_6;
    f64 var_ft2;
    s16 temp_v0;
    s16 var_a0;
    s32 var_t2;
    s8 temp_v0_2;
    s8 temp_v1;
    u8 temp_t6;
    F5L1Target *temp_t3;
    F5L1Waypoint *var_t0;
    F5L1Waypoint *var_t1;

    var_t0 = D_807FD70C;
    temp_t3 = D_807FD710->unk174;
    sp34 = 0.2f;
    temp_t6 = var_t0->speed;
    var_t1 = var_t0 + 1;
    var_ft2 = (f64) temp_t6;
    if ((s32) temp_t6 < 0) {
        var_ft2 += 4294967296.0;
    }
    var_t2 = 0;
    sp30 = (f32) (var_ft2 * 0.7);
    temp_fv0 = D_807FD710->unk7C - (f32) var_t0->x;
    temp_fv1 = D_807FD710->unk84 - (f32) var_t1->z;
    if (((temp_fv0 * temp_fv0) + (temp_fv1 * temp_fv1)) < 100.0f) {
        var_t2 = 1;
    }
    if ((D_807FD716 == 0) & 1) {
        D_807FD716 |= 1;
        arg0->yaw = 0;
        arg0->pitch = 0;
    }
    if (var_t2 & 0xFF) {
        if (*D_807FD708 == (D_807FD714 + 2)) {
            D_807463B8 = 0;
            if (D_807444EC == 0) {
                D_8076A0B1 &= 0xFFEF;
                D_8076A0B3 = 0xFF;
            }
            if (D_807FD718 != 0) {
                sp3C = var_t0;
                sp38 = var_t1;
                sp4C = temp_t3;
                playerStateQueueCallback(D_807FD718, D_807FD71C, 0, &D_807FD70C);
            }
            temp_t3->flags |= 1;
            sp38 = var_t1;
            D_807FBB60 &= ~0x400;
            sp3C = var_t0;
            func_806D03BC();
        } else {
            D_807FD714 += 1;
            var_t0 = D_807FD70C + 1;
            D_807FD70C = var_t0;
            var_t1 = var_t0 + 1;
        }
    }
    arg0->flags = 0U;
    sp38 = var_t1;
    sp3C = var_t0;
    timerDecrementOrSetFlag(&arg0->flags, &var_t0->timer3, &var_t0->timer0, 0x8000);
    timerDecrementOrSetFlag(&arg0->flags, &var_t0->timer4, &var_t0->timer1, 0x4000);
    timerDecrementOrSetFlag(&arg0->flags, &var_t0->timer5, &var_t0->timer2, 0x2000);
    var_a0 = 0;
    temp_v0 = var_t0->delay;
    if (temp_v0 != 0) {
        var_t0->delay = temp_v0 - 1;
        sp2E = 0;
    } else {
        if (D_807FD716 & 2) {
            D_807FD716 &= 0xFFFD;
            sp34 = 1.0f;
        }
        if (D_807FD710->unk154 == 0x4F) {
            sp38 = var_t1;
            temp_ft1 = (f32) ((f64) (mathAngleBetweenPointsDeg(var_t1->x, var_t1->z, (s32) D_807FD710->unk7C, (s32) D_807FD710->unk84) * 0.017453292f) - ((f64) ((f32) D_807FD710->unkE6 * 3.1415927f) * 0.00048828125));
            sp48 = temp_ft1;
            temp_fv0_2 = mathCalculatePitchAngle((f32) var_t1->x, (f32) var_t1->y, (f32) var_t1->z, D_807FD710->unk7C, D_807FD710->unk80, D_807FD710->unk84, 0);
            sp40 = temp_fv0_2;
            arg0->flags |= 0x4000;
            sp2E = (s16) temp_ft1;
            if ((func_80612D1C(temp_fv0_2) * sp30) > -128.0f) {
                var_fv1 = func_80612D1C(sp40) * sp30;
            } else {
                var_fv1 = -128.0f;
            }
            if (var_fv1 < 127.0f) {
                if ((func_80612D1C(sp40) * sp30) > -128.0f) {
                    var_fv1_2 = func_80612D1C(sp40) * sp30;
                } else {
                    var_fv1_2 = -128.0f;
                }
                var_a0 = (s16) var_fv1_2;
            } else {
                var_a0 = (s16) 127.0f;
            }
        } else {
            sp38 = var_t1;
            sp44 = mathAngleBetweenPointsDeg((s16) F5L1Cam->targetX, (s16) F5L1Cam->targetZ, (s32) F5L1Cam->x, (s32) F5L1Cam->z);
            temp_fa0 = (mathAngleBetweenPointsDeg(var_t1->x, var_t1->z, (s32) D_807FD710->unk7C, (s32) D_807FD710->unk84) * 0.017453292f) - (sp44 * 0.017453292f);
            sp48 = temp_fa0;
            if ((func_80612D1C(temp_fa0) * sp30) > -128.0f) {
                var_fv1_3 = func_80612D1C(sp48) * sp30;
            } else {
                var_fv1_3 = -128.0f;
            }
            if (var_fv1_3 < 127.0f) {
                if ((func_80612D1C(sp48) * sp30) > -128.0f) {
                    var_fv1_4 = func_80612D1C(sp48) * sp30;
                } else {
                    var_fv1_4 = -128.0f;
                }
                sp2E = (s16) var_fv1_4;
            } else {
                sp2E = (s16) 127.0f;
            }
            if ((func_80612D10(sp48) * sp30) > -128.0f) {
                var_fv1_5 = func_80612D10(sp48) * sp30;
            } else {
                var_fv1_5 = -128.0f;
            }
            if (var_fv1_5 < 127.0f) {
                if ((func_80612D10(sp48) * sp30) > -128.0f) {
                    var_fv1_6 = func_80612D10(sp48) * sp30;
                } else {
                    var_fv1_6 = -128.0f;
                }
                var_a0 = (s16) var_fv1_6;
            } else {
                var_a0 = (s16) 127.0f;
            }
        }
    }
    temp_v0_2 = arg0->yaw;
    temp_v1 = arg0->pitch;
    arg0->yaw = (s8) ((f32) temp_v0_2 + ((f32) (sp2E - temp_v0_2) * sp34));
    arg0->pitch = (s8) ((f32) temp_v1 + ((f32) (var_a0 - temp_v1) * sp34));
}
