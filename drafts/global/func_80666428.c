// func_80666428 (src/global/6AD90.c): W4IntB: stage 5, 6 lines (was 10), 552/552, frame/regs exact. Remaining: t-ring of switch-selector sum: ours E2 sll t0/andi t1, addu v0,t5,t8 (E1+F operand order + v0 temp) vs target t6/t7, addu t0,t8,t5; one sw t7,56(sp) order. Fix = FAKE no-code defs + dead tests on sums (annealed hc_f3, 40k evals); sum spelling (E1+F)+E2 required (all 12 orders/assoc and a-(0-b) tried: no change).
typedef struct CollisionQueryPlayerState {
    u8 pad0[0x1F0];
    u32 unk1F0;
} CollisionQueryPlayerState;

typedef struct CollisionQueryActor {
    u8 pad0[0x5C];
    u16 unk5C;
    u8 pad5E[6];
    u32 unk64;
    u16 pad68;
    u16 unk6A;
    u16 unk6C;
    u8 pad6E[0x36];
    f32 unkA4;
    f32 unkA8;
    u8 padAC[0x24];
    u8 unkD0;
    u8 unkD1;
    u8 padD2[6];
    s16 unkD8;
    s16 unkDA;
    u8 padDC[0x30];
    s16 unk10C;
    u8 pad10E[2];
    u8 unk110;
    u8 pad111[0x63];
    CollisionQueryPlayerState *unk174;
} CollisionQueryActor;

u8 func_8062BCC8(void *, f32, f32, f32, s32);
u8 collisionTestSubmeshBoundary(f32, f32, f32 *, s32);
s32 func_8066A08C(Actor *, f32, f32, f32, f32 *);
void func_8067A7EC(Actor *, s32, s32, s32, f32, s32, u8);
s32 mathCheckCloserFloatThreshold(f32, f32, f32, u8);
extern f32 D_807F9460;
extern s8 D_807F9464;
extern f32 D_807F9468;
extern u8 D_807F946C;
extern u8 D_807F946D;
extern u8 D_807F946E;
extern Actor *D_807F9470;
extern f32 D_807F9474;
extern f32 D_807F9478;
extern f32 D_807F947C;
extern u32 D_807F9480;
extern u8 D_807F9484;
extern s16 D_807F9490;
extern s16 D_807F9492;
extern s16 D_807F9494;
extern s16 D_807F9498;
extern s16 D_807F949A;
extern s16 D_807F949C;
extern u8 D_807F949E;
extern u8 D_807F949F;
extern u8 D_807F94A0;
extern s16 D_807F94A2;
extern s16 D_807F94A4;
extern u8 D_807F94AA;
extern u8 D_807F94AB;
extern u8 D_807F94AC;
extern s8 D_807F94AD;
extern s8 D_807F94B2;
extern u8 D_807F94B6;
extern CollisionQueryPlayerState *D_807F94B8;
extern u8 D_807F9510;

s32 func_80666428(Actor *arg0, f32 arg1, f32 arg2, f32 arg3, u8 *arg4, f32 *arg5, u8 *arg6, f32 *arg7, u8 arg8) {
    u8 sp5F;
    u8 sp5E;
    f32 sp58;
    f32 sp54;
    f32 sp50;
    u8 new2;
    u8 val2;
    u8 sp4D;
    u8 new_var;
    f32 sp40;

    D_807F946E = 0;
    if (D_807F94B4 == 1) {
        collisionClearFlags();
        *arg4 = 0;
        *arg6 = 0;
        D_807F94B4 = 0;
        return 0;
    }
    if (arg0 != NULL) {
        ((CollisionQueryActor *)arg0)->unk110 = 0;
        ((CollisionQueryActor *)arg0)->unk6A &= 0xFBF1;
        ((CollisionQueryActor *)arg0)->unk10C = -1;
        D_807F94B6 = 0;
        D_807F9464 = 0;
        D_807F946C = 0;
        D_807F946D = arg8;
        ((CollisionQueryActor *)arg0)->unk64 &= ~0x40;
        if (((CollisionQueryActor *)arg0)->unk5C & 1) {
            D_807F94B8 = ((CollisionQueryActor *)arg0)->unk174;
            D_807F94B8->unk1F0 &= ~0x6000;
        }
    }
    D_807F951D = 0;
    D_807F94AB = 0;
    D_807F94AC = 0;
    D_807F94AD = 0;
    collisionClearFlags();
    D_807F94B2 = 0;
    D_807F9484 = 0;
    D_807F9510 = 0;
    sp58 = arg2;
    sp5F = collisionTestSubmeshBoundary(arg1, arg3, &sp58, (s32)arg0);
    if ((sp5F != 0) && (arg0 != NULL)) {
        ((CollisionQueryActor *)arg0)->unkA8 = sp58;
        ((CollisionQueryActor *)arg0)->unkD0 = D_807F949E;
    }
    if (D_807F94B4 != 2) {
        sp54 = 99999.0f;
        sp5E = func_8062BCC8(arg0, arg1, arg3, arg2, (s32)&sp54);
        sp50 = 99999.0f;
        val2 = func_8066A08C(arg0, arg1, arg3, arg2, &sp50);
    } else {
        sp5E = 0;
        val2 = 0;
    }
    val2 = val2 * 1;  // FAKE: raises sp5E/val2 adjsave so arg0 takes s0 (no code)
    sp5E = sp5E & 0x1FF;  // FAKE: raises sp5E/val2 adjsave so arg0 takes s0 (no code)
    if ((((sp5E * 2) & 0xFF) + ((val2 * 4) & 0xFF))) {}  // FAKE: raises sp5E/val2 adjsave so arg0 takes s0 (no code)
    if ((((val2 * 4) & 0xFF) + sp5F)) {}  // FAKE: raises sp5E/val2 adjsave so arg0 takes s0 (no code)
    sp5E = sp5E * 1;  // FAKE: raises sp5E/val2 adjsave so arg0 takes s0 (no code)
    if ((((sp5E * 2) & 0xFF) + sp5F)) {}  // FAKE: raises sp5E/val2 adjsave so arg0 takes s0 (no code)
    sp5E = sp5E + 0;  // FAKE: raises sp5E/val2 adjsave so arg0 takes s0 (no code)
    sp5E = sp5E ^ 0;  // FAKE: raises sp5E/val2 adjsave so arg0 takes s0 (no code)
    sp5E = sp5E & 0xFF;  // FAKE: raises sp5E/val2 adjsave so arg0 takes s0 (no code)
    if (sp5E) {}  // FAKE: raises sp5E/val2 adjsave so arg0 takes s0 (no code)
    val2 = val2 * 1;  // FAKE: raises sp5E/val2 adjsave so arg0 takes s0 (no code)
    sp5E = sp5E * 1;  // FAKE: raises sp5E/val2 adjsave so arg0 takes s0 (no code)
    val2 = val2 * 1;  // FAKE: raises sp5E/val2 adjsave so arg0 takes s0 (no code)
    if ((((sp5E * 2) & 0xFF) + sp5F)) {}  // FAKE: raises sp5E/val2 adjsave so arg0 takes s0 (no code)
    val2 = val2 ^ 0;  // FAKE: raises sp5E/val2 adjsave so arg0 takes s0 (no code)
    val2 = val2 | 0;  // FAKE: raises sp5E/val2 adjsave so arg0 takes s0 (no code)
    val2 = val2 ^ 0;  // FAKE: raises sp5E/val2 adjsave so arg0 takes s0 (no code)
    switch (((((sp5E * 2) & 0xFF) + sp5F) + ((val2 * 4) & 0xFF)) & 0xFF) {
    case 0:
        sp4D = 0;
        break;
    case 1:
        sp4D = 1;
        break;
    case 2:
        sp4D = 2;
        break;
    case 3:
        if (mathCheckCloserFloatThreshold(sp54, sp58, (f32)((f64)arg2 + 4.0), 0) != 0) {
            sp4D = 1;
        } else {
            sp4D = 2;
        }
        break;
    case 4:
        sp4D = 3;
        break;
    case 5:
        if (mathCheckCloserFloatThreshold(sp50, sp58, (f32)((f64)arg2 + 4.0), 0) != 0) {
            sp4D = 1;
        } else {
            sp4D = 3;
        }
        break;
    case 6:
        if (mathCheckCloserFloatThreshold(sp50, sp54, (f32)((f64)arg2 + 4.0), 0) != 0) {
            sp4D = 2;
        } else {
            sp4D = 3;
        }
        break;
    case 7:
        sp40 = (f32)((f64)arg2 + 4.0);
        if (mathCheckCloserFloatThreshold(sp54, sp58, sp40, 0) != 0) {
            if (mathCheckCloserFloatThreshold(sp50, sp58, sp40, 0) != 0) {
                sp4D = 1;
            } else {
                sp4D = 3;
            }
        } else if (mathCheckCloserFloatThreshold(sp54, sp50, sp40, 0) != 0) {
            sp4D = 3;
        } else {
            sp4D = 2;
        }
    }
    switch (sp4D) {
    default:
        D_807F94AA = 0;
        break;
    case 1:
        if (arg0 != NULL) {
            ((CollisionQueryActor *)arg0)->unkD1 = D_807F949E;
            ((CollisionQueryActor *)arg0)->unkDA = D_807F9498;
            ((CollisionQueryActor *)arg0)->unkD8 = D_807F9490;
            ((CollisionQueryActor *)arg0)->unkA4 = sp58;
            if ((D_807F94B6 != 0) && (((CollisionQueryActor *)arg0)->unk6C & 1)) {
                ((CollisionQueryActor *)arg0)->unk6A |= 0x400;
            }
        }
        D_807F94A4 = D_807F9498;
        D_807F94A2 = D_807F9490;
        D_807F948C = sp58;
        D_807F94AA = D_807F94AB;
        D_807F951D = 1;
        break;
    case 2:
        if (arg0 != NULL) {
            ((CollisionQueryActor *)arg0)->unkD1 = D_807F949F;
            ((CollisionQueryActor *)arg0)->unkDA = D_807F949A;
            ((CollisionQueryActor *)arg0)->unkD8 = D_807F9492;
            ((CollisionQueryActor *)arg0)->unkA4 = sp54;
            if (((CollisionQueryActor *)arg0)->unk6C & 1) {
                ((CollisionQueryActor *)arg0)->unk110 = 1;
            }
        }
        D_807F94A4 = D_807F949A;
        D_807F94A2 = D_807F9492;
        D_807F948C = sp54;
        D_807F94AA = D_807F94AC;
        D_807F951D = 2;
        break;
    case 3:
        if (arg0 != NULL) {
            ((CollisionQueryActor *)arg0)->unkD1 = D_807F94A0;
            ((CollisionQueryActor *)arg0)->unkDA = D_807F949C;
            ((CollisionQueryActor *)arg0)->unkD8 = D_807F9494;
            ((CollisionQueryActor *)arg0)->unkA4 = sp50;
            if (((CollisionQueryActor *)arg0)->unk6C & 1) {
                func_8067A7EC(arg0, (s32)D_807F9470, *(s32 *)&D_807F9474, *(s32 *)&D_807F9478, D_807F947C, (s32)D_807F9480, *(u8 *)&D_807F94B2);
                ((CollisionQueryActor *)arg0)->unk6A |= 8;
            }
        }
        D_807F94A4 = D_807F949C;
        D_807F94A2 = D_807F9494;
        D_807F948C = sp50;
        D_807F94AA = *(u8 *)&D_807F94AD;
        D_807F951D = 3;
        break;
    }
    *arg4 = *(u8 *)&D_807F9464;
    *arg5 = D_807F9460;
    *arg6 = D_807F946C;
    *arg7 = D_807F9468;
    D_807F94B4 = 0;
    return (sp5F | ((sp5E * 2) & 0xFF) | ((val2 * 4) & 0xFF)) & 0xFF;
}
