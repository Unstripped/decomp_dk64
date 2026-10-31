// playerCameraUpdateFromTarget (src/global/8F4B0.c): W2Ring stage 5 (36 diff lines incl 6 reloc-addend lines; ring FIXED, E-chain order fixed): 's16 tmpd; tmpd = D_807FC624 + 0x1E; tmpd &= 0xFFF; D_807FC624 = tmpd;' + 's32 dd = sp52 - temp_v0; temp_v0 = dd; temp_v1_3 = dd;' (B conversion first -> sll a0,sll a1,sra t1,sra t0 order matches). Remaining: B var (temp_v0) coloured a2 vs target a1 (sll/sra/move a2 vs a1 and sh a2,78(sp)); one ring slot (t4 vs t5 at addiu t4,a0,4096 and everything after). Tried dd type/decl position (no change), two fresh s16 vars (collapse to one chain).
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
extern s16 D_807FC624;

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
    s32 dd;
    s16 tmpd;
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
    if (D_807FBB4C != *(Actor **)sp54) {
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
        tmpd = D_807FC624 + 0x1E;
        tmpd &= 0xFFF;
        D_807FC624 = tmpd;
        return;
    }
    if (D_807444EC != 1) {
            var_v1 = (*(Actor **)sp54)->unk154;
            switch (var_v1) {
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
                dd = sp52 - temp_v0;
                temp_v0 = dd;
                temp_v1_3 = dd;
                if (temp_v1_3 >= 0x801) {
                    sp4E = temp_v1_3 - 0x1000;
                } else {
                    sp4E = temp_v0;
                    if (temp_v1_3 < -0x800) {
                        sp4E = temp_v1_3 + 0x1000;
                    }
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
