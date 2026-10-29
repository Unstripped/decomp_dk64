// func_8002A7F8 (src/race/6650.c): FE3c: stage 5, 24 diff lines (was 30). then-arm now: sp4E=(s16)(s32)(cos*sp20); fv0 = sin*sp20; sp4E &= 0xFFF; a3 = (s32)fv0 & 0xFFF (float temp splits the call from the mask so the sp4E reload/andi lands at t4,t5 like target). Remaining: then-arm raw trunc goes to 'mfc1 a3' (dest hint) vs target 'mfc1 t9' + andi t0/sll t1/sra a3, plus 3 later t-reg numbers (else-arm sra/sll, final mfc1). Split forms (a3=(s32)fv0; a3&=0xFFF) give the target then-arm exactly but shift the else-arm ring (li t7 vs t4, +3 hidden temps); else-arm 'a0=(a0+0x800)&0xFFF' merged hints a0 (46). Tried ~1000 statement-order/cast/var-reuse/dummy-stmt variants. actorUpdateFloorContactAndTilt prototype must be (Actor_BB40 *, f32) in 6650.c (only decl in file).
void actorUpdateFloorContactAndTilt(Actor_BB40 *, f32); /* file decl must be f32 (li a1,0 for 0.0f); was s32 */
void func_8002A7F8(Struct_sp58 *arg0) {
    f32 sp5C;
    f32 sp58;
    f32 sp54;
    volatile u8 sp53;
    s16 a1;
    s16 sp4E;
    s16 a3;
    f32 fv1;
    f32 sp44;
    f32 sp40;
    f32 fv0;
    s32 v0;
    s16 sp36;
    s16 sp34;
    s16 sp32;
    s16 v1;
    s16 a0;
    f32 sp20;

    sp53 = D_807FBB40->unk6A & 1;
    a1 = D_807FBB40->unkE6;
    if (!(D_807FBB40->unk60 & 0x10)) {
        D_807FBB40->unk144 = 0x3C;
        D_807FBB40->unk60 |= 0x10400;
        D_807FBB40->unk154 = 0;
        D_807FBB40->unk155 = 0;
        D_807FBB40->unkB8 = 0.0f;
        D_807FBB40->unkC4 = -20.0f;
        D_807FBB40->unkC8 = -900.0f;
        D_807FBB40->unkF8 = 0x12C;
    }
    sp5C = func_80612794(D_807FBB40->unkEE) * D_807FBB40->unkB8;
    sp58 = func_80612790(D_807FBB40->unkEE) * D_807FBB40->unkB8;
    if (arg0->unk20 != 0) {
        a1 = a1 + 0x800;
        a1 = a1 & 0xFFF;
        arg0->unk4 = (f32)((f64)arg0->unk4 * 0.85);
    }
    if (sp53 != 0) {
        fv0 = (f32)((f64)(arg0->unk8 * D_807FBB40->unkB8) * 0.2);
        if (!(fv0 > 1.0f)) {
            fv0 = 1.0f;
        }
        sp54 = (f32)((f64)(arg0->unk4 * 35.0f) + ((f64)D_807FBB40->unkB8 * 0.13));
        sp44 = (f32)((f64)(D_807FBB40->unkB8 * D_807FBB40->unkB8 * 0.00025f) + (27.0 + (f64)fv0));
    } else {
        sp54 = arg0->unk4 * 2;
        sp44 = (D_807FBB40->unkB8 * D_807FBB40->unkB8 * 0.00002f) + 2;
    }
    sp5C += func_80612794(a1) * sp54;
    sp58 += func_80612790(a1) * sp54;
    D_807FBB40->unkB8 = sqrtf((sp5C * sp5C) + (sp58 * sp58));
    D_807FBB40->unkEE = (s16)(s32)(func_80611BB4(sp5C, sp58) * 651.8986f);
    if (sp53 != 0) {
        sp34 = 0x400 - D_807FBB40->unkDE;
        sp36 = func_806CC10C(D_807FBB40->unkDC, D_807FBB40->unkE6);
        sp20 = (f32)sp34;
        sp4E = (s16)(s32)(func_80612790(sp36) * sp20);
        fv0 = func_80612794(sp36) * sp20;
        sp4E = sp4E & 0xFFF;
        a3 = (s32)fv0 & 0xFFF;
    } else {
        v1 = mathAngleFromVector2D(D_807FBB40->unkB8, D_807FBB40->unkC0);
        a0 = D_807FBB40->unkEE;
        if (v1 >= 0x800) {
            v1 = 0xFFF - v1;
            a0 = a0 + 0x800;
            a0 = a0 & 0xFFF;
        }
        sp32 = func_806CC10C(a0, D_807FBB40->unkE6);
        sp20 = (f32)v1;
        sp4E = (s16)(s32)(func_80612790(sp32) * sp20);
        a3 = (s32)(func_80612794(sp32) * sp20);
        sp4E = sp4E & 0xFFF;
        a3 = a3 & 0xFFF;
    }
    fv1 = arg0->unk8;
    sp40 = arg0->unk10 * arg0->unkC;
    if (fv1 > 0) {
        if (sp40 > 0.0f) {
            fv0 = sp40;
        } else {
            fv0 = -sp40;
        }
        if (fv0 > 0.1f) {
            if (sp40 >= 0.0f) {
                v0 = 1;
            } else {
                v0 = -1;
            }
            sp40 += 2.0f * (f32)v0 * fv1;
        }
    }
    D_807FBB40->unkE8 = func_806CC190(D_807FBB40->unkE8, sp4E, 4.0f, a3);
    D_807FBB40->unkE4 = func_806CC190(D_807FBB40->unkE4, (s32)a3, 4.0f, a3);
    D_807FBB40->unkB8 = D_807FBB40->unkB8 - sp44;
    fv1 = D_807FBB40->unkB8;
    if (fv1 < 0.0f) {
        D_807FBB40->unkB8 = 0.0f;
        fv1 = D_807FBB40->unkB8;
    }
    if (arg0->unk20 != 0) {
        if (fv1 < 100.0f) {
            D_807FBB40->unkB8 = fv1;
            fv1 = D_807FBB40->unkB8;
        } else {
            D_807FBB40->unkB8 = 100.0f;
            fv1 = D_807FBB40->unkB8;
        }
    }
    fv0 = fv1 - D_807FBB40->unkBC;
    if (fv0 < 0.0f) {
        fv0 = 0.0f;
    }
    D_807FBB40->unkE6 = (s16)(s32)((f64)D_807FBB40->unkE6 + ((f64)(sp40 * -40.0f) * (1.0 + ((f64)fv0 * 0.05))));
    D_807FBB40->unkE6 = D_807FBB40->unkE6 & 0xFFF;
    D_807FBB40->unkC0 = D_807FBB40->unkC0 + D_807FBB40->unkC4;
    fv1 = D_807FBB40->unkC8;
    if (D_807FBB40->unkC0 < fv1) {
        D_807FBB40->unkC0 = fv1;
    }
    a0 = D_807FBB40->unkEE;
    actorStepPhysics(D_807FBB40, a0, a0);
    actorApplyVelocity(D_807FBB40);
    actorUpdateFloorContactAndTilt(D_807FBB40, 0.0f);
    if (D_807FBB64 & 0x2000) {
        func_8002F490(arg0);
    }
}
