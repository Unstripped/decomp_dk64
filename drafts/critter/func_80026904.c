// func_80026904 (src/critter/0.c): stage 5 (score 605, only scheduling/regs left). def is (u8*,u8*) so decl 'void func_80026904(void);' must become 'void func_80026904();'. Diff: target sb 1E0=1 comes after sll (late) and 'lh a3,0x2e(sp); addu a3,a3,t1' (sp2E in a3) vs ours li/sb early, lh t2; addu a3,t1,t2. Tried: temp_t2 s32/s16, statement order, commutative order, (0,x), sp2E s32, comma-in-args. no local temp_v0 (use arg0[0x1E2] twice) fixed v0/v1.
s16 mathAngleBetweenPoints2D(f32, f32, f32, f32);

void func_80026904(u8 *arg0, u8 *arg1) {
    s16 sp2E;
    s32 temp_t2;
    u8 *temp_a0;

    if (arg0[0x1E2] == 2) {
        func_8002646C(arg0, *(u8 **)(arg1 + 8));
        return;
    }
    if (arg0[0x1E2] == 0) {
        temp_a0 = *(u8 **)(arg0 + 0x58);
        if (temp_a0[0x25] != 0) {
            critterCalcDistToPlayer(arg0);
            if (D_80029BA4 != *(void **)(arg0 + 0x54)) {
                func_80026338(arg0, arg1);
                return;
            }
            if (arg0[0x1E0] == 2 && *(f32 *)(arg0 + 0x3C) < (f32)*(s16 *)((u8 *)D_80029BA4 + 0xA)) {
                sp2E = mathAngleBetweenPoints2D(*(f32 *)(arg0 + 8), *(f32 *)(arg0 + 0x10), *(f32 *)(D_807FBB48 + 0x7C), *(f32 *)(D_807FBB48 + 0x84));
                temp_t2 = (sp2E + (func_806119A0() & 0x7FF)) - 0x400;
                arg0[0x1E0] = 1;
                func_80025DB8(*(void **)(arg0 + 0x54), arg0, 0, (s16)temp_t2, 1);
            }
        } else if (D_80029BA4 == *(void **)(arg0 + 0x54)) {
            *(u8 **)(arg0 + 0x54) = temp_a0;
            func_80025F3C(temp_a0, arg0, 1, 1);
            arg0[0x40] = 0xFF;
        }
    }
}

extern void *D_80029BA4;
