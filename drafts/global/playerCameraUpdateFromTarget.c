// playerCameraUpdateFromTarget (src/global/8F4B0.c): stage 5, score 44 (frame 0x58, 300/312 insns matched; minor regalloc in switch index/return)
#include "common.h"
#include "actor.h"

typedef struct {
    char pad[0xE4];
    s16 unkE4;
    s16 unkE6;
    char padE8[0x4];
    s16 unkEC;
} AimActorAngles;

void sfxPlayOnFreeSlot(s32, s32, f32, f32, s32, s32);
f32 func_80612794(s16);
void camUpdate(void *, void *, void *, void *, void *, void *, void *, void *, void *, void *);
s16 mathAngleBetweenPoints2D(f32, f32, f32, f32);
f32 mathAngleBetweenPointsRad(f32, f32, f32, f32);
void func_806C9D20(u8);
extern u8 D_807444EC;
extern s32 D_8076A0A8;
extern Actor *D_807FBB40;
extern Actor *D_807FBB4C;
extern s16 D_807FC624;
extern void *D_807FC924;

void playerCameraUpdateFromTarget(void) {
    void *sp54;
    s16 sp52;
    s16 pad50[1];
    s16 sp4E;
    f32 sp48;
    f32 pad44[1];
    f32 sp40;
    f32 sp3C;
    s16 sp3A;
    void *sp34;
    s32 pad30[1];
    f32 temp_fa0;
    f32 temp_fa1;
    f32 temp_fv0;
    f32 temp_fv1;
    f32 var_fv1;
    Actor *temp_a0_2;
    s16 temp_v0;
    s32 temp_v0_2;
    s16 temp_v1_3;
    s32 var_v1;
    u8 temp_v1_2;
    sp54 = D_807FBB40->unk174;
    sp4E = 0;
    sp3A = 0x1E;
    sp40 = 0.08f;
    sp3C = 8.0f;
    sp34 = (void *)((*(u8 *)((u8 *)sp54 + 0xFB) * 0x2F0) + (u8 *)D_807FC924);
    *(s16 *)((u8 *)sp34 + 0x2CC) = ((AimActorAngles *)D_807FBB40)->unkEC;
    ((AimActorAngles *)D_807FBB40)->unkEC = ((AimActorAngles *)D_807FBB40)->unkE4;
    *(s16 *)((u8 *)sp34 + 0x2CA) = (s16)(s32)*(f32 *)((u8 *)sp34 + 0x214);
    sp48 = mathAngleBetweenPointsRad(*(f32 *)((u8 *)sp34 + 0x218), *(f32 *)((u8 *)sp34 + 0x210), *(f32 *)((u8 *)sp34 + 0x230), *(f32 *)((u8 *)sp34 + 0x228));
    temp_fv1 = *(f32 *)((u8 *)sp34 + 0x230) - *(f32 *)((u8 *)sp34 + 0x218);
    temp_fa1 = *(f32 *)((u8 *)sp34 + 0x228) - *(f32 *)((u8 *)sp34 + 0x210);
    temp_fa0 = mathAngleBetweenPointsRad(0.0f, *(f32 *)((u8 *)sp34 + 0x214), sqrtf((temp_fv1 * temp_fv1) + (temp_fa1 * temp_fa1)), *(f32 *)((u8 *)sp34 + 0x22C)) + 3.1415927f;
    var_fv1 = temp_fa0;
    if (temp_fa0 > 6.2831855f) {
        var_fv1 = temp_fa0 - 6.2831855f;
    }
    if (var_fv1 > 3.1415927f) {
        var_fv1 = 3.1415927f - (var_fv1 - 3.1415927f);
    }
    *(f32 *)((u8 *)sp34 + 0x2D4) = 6.2831855f - sp48;
    *(f32 *)((u8 *)sp34 + 0x2D8) = 6.2831855f - var_fv1;
    func_806C9D20(*(u8 *)((u8 *)sp54 + 0xFB));
    sp52 = mathAngleBetweenPoints2D(*(f32 *)((u8 *)sp34 + 0x210), *(f32 *)((u8 *)sp34 + 0x218), *(f32 *)((u8 *)sp34 + 0x228), *(f32 *)((u8 *)sp34 + 0x230));
    camUpdate(D_807FBB40, (u8 *)sp34 + 0x210, (u8 *)sp34 + 0x214, (u8 *)sp34 + 0x218, (u8 *)sp34 + 0x228, (u8 *)sp34 + 0x22C, (u8 *)sp34 + 0x230, (u8 *)sp34 + 0x240, (u8 *)sp34 + 0x244, (u8 *)sp34 + 0x248);
    temp_v0 = mathAngleBetweenPoints2D(*(f32 *)((u8 *)sp34 + 0x210), *(f32 *)((u8 *)sp34 + 0x218), *(f32 *)((u8 *)sp34 + 0x228), *(f32 *)((u8 *)sp34 + 0x230));
    temp_a0_2 = *(Actor **)sp54;
    if (D_807FBB4C != temp_a0_2) {
        return;
    }
    if ((D_8076A0A8 == 0x1F) || (D_8076A0A8 == 0x33)) {
        if (D_807FC624 && D_807FC624) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
        ((AimActorAngles *)D_807FBB40)->unkE4 = (s16)(s32)(func_80612794(D_807FC624) * 100.0f);
        if (D_8076A0A8 == 0x1F) {
            if (D_807FC624 < 0x1E) {
                sfxPlayOnFreeSlot(0x15, 0x7FFF, 64.0f, 1.0f, 10, 128);
            }
            if ((D_807FC624 >= 0x800) && (D_807FC624 < 0x81E)) {
                sfxPlayOnFreeSlot(0x14, 0x7FFF, 64.0f, 1.0f, 10, 128);
            }
        }
        if (D_807444EC && D_807444EC) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
        D_807FC624 = (D_807FC624 + 0x1E) & 0xFFF;
        return;
    }
    if (D_807444EC != 1) {
            temp_v1_2 = temp_a0_2->unk154;
            if (D_8076A0A8 && D_8076A0A8) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
            switch ((s32)temp_v1_2) {
            case 0x63:
                sp40 = 0.02f;
                sp3C = 15.0f;
                goto calc_angle;
            case 0x7:
            case 0x8:
            case 0x9:
            case 0xA:
            case 0xB:
            case 0xF:
            case 0x10:
            case 0x11:
            case 0x12:
            case 0x13:
            case 0x14:
                sp3A = 0x64;
                sp40 = 0.1f;
            case 0x4F:
            case 0x69:
            case 0x6D:
calc_angle:
                temp_v1_3 = sp52 - temp_v0;
                if (temp_v1_3 >= 0x801) {
                    sp4E = temp_v1_3 - 0x1000;
                } else if (temp_v1_3 < -0x800) {
                    sp4E = temp_v1_3 + 0x1000;
                } else {
                    sp4E = temp_v1_3;
                }
                break;
            }
            temp_v0_2 = -sp3A;
            var_v1 = (temp_v0_2 < sp4E) ? sp4E : temp_v0_2;
            var_v1 = (var_v1 < sp3A) ? ((temp_v0_2 < sp4E) ? sp4E : temp_v0_2) : sp3A;
            temp_fv0 = (f32)((AimActorAngles *)D_807FBB40)->unkE4;
            ((AimActorAngles *)D_807FBB40)->unkE4 = (s16)(s32)(((((f32)var_v1 * sp3C) - temp_fv0) * sp40) + temp_fv0);
    }
}
