// func_8069B3FC (src/global/9DD70.c): m2c stage-1 C only; not hand-matched
? actorDespawn(void *);                             /* extern */
? actorGetNodePos(void *, ?, f32 *, f32 *, f32 *);  /* extern */
s32 func_80611A44();                                /* extern */
? func_80614EBC(void *, ?);                         /* extern */
? func_806319C4(void *, ?);                         /* extern */
? func_80714950(s32);                               /* extern */
? func_8071498C(? *);                               /* extern */
? func_807149B8(?);                                 /* extern */
? func_80714C08(? *, f32, void *, s32, s32);        /* extern */
? sfxAllocateChannel(?, ?);                         /* extern */
? sfxStopChannel(?, ?, void **);                    /* extern */
extern ? D_8071FC58;
extern ? D_8071FC8C;
extern ? D_8071FCC0;
extern void *D_807FBB40;
extern void *D_807FBB4C;
extern ? func_80717D4C;

void func_8069B3FC(void) {
    s16 *sp7C;
    f32 sp70;
    f32 sp6C;
    f32 sp68;
    ? *sp60;
    ? *sp58;
    ? *var_s0_2;
    s32 temp_hi;
    s32 var_s1;
    s32 var_s5;
    u8 var_v1;
    void *temp_s1;
    void *var_s0;

    sp7C = D_807FBB40->unk174;
    temp_s1 = D_807FBB4C->unk174;
    if (!(D_807FBB40->unk60 & 0x10)) {
        D_807FBB40->unk144 = 1;
        D_807FBB40->unk60 = (s32) (D_807FBB40->unk60 | 0x400);
        func_80614EBC(D_807FBB40, 0x298);
        *sp7C = 0;
        sfxAllocateChannel(0x3B, 0x3F800000);
        goto block_29;
    }
    actorGetNodePos(D_807FBB40, 1, &sp70, &sp6C, &sp68);
    temp_s1->unk210 = sp70;
    temp_s1->unk214 = sp6C;
    var_s5 = 2;
    temp_s1->unk218 = sp68;
    var_s0 = D_807FBB40;
    var_v1 = var_s0->unk155;
    if ((s32) var_v1 < 4) {
        sp58 = &func_80717D4C;
        var_s0_2 = sp60;
        do {
            var_s1 = 0;
loop_5:
            func_8071498C(sp58);
            func_807149B8(1);
            func_80714950(((s32) ((s32) (func_80611A44() >> 0xF) % 10000) % 120) + 0x50);
            temp_hi = (s32) ((s32) (func_80611A44() >> 0xF) % 10000) % 3;
            switch (temp_hi) {                      /* switch 1; irregular */
            case 0:                                 /* switch 1 */
                var_s0_2 = &D_8071FC58;
                break;
            case 1:                                 /* switch 1 */
                var_s0_2 = &D_8071FC8C;
                break;
            case 2:                                 /* switch 1 */
                var_s0_2 = &D_8071FCC0;
                break;
            }
            func_80714C08(var_s0_2, 0.6f, D_807FBB40, var_s5, 0);
            var_s1 += 1;
            if (var_s1 != 2) {
                goto loop_5;
            }
            var_s5 += 1;
        } while (var_s5 != 3);
        sp60 = var_s0_2;
        var_s0 = D_807FBB40;
        var_v1 = var_s0->unk155;
    }
    switch (var_v1) {                               /* switch 2 */
    case 0:                                         /* switch 2 */
        *sp7C += 0x1E;
        var_s0 = D_807FBB40;
        break;
    case 1:                                         /* switch 2 */
        D_807FBB4C->unk155 = (u8) (D_807FBB4C->unk155 + 1);
        D_807FBB40->unk155 = (u8) (D_807FBB40->unk155 + 1);
        var_s0 = D_807FBB40;
        break;
    case 2:                                         /* switch 2 */
        *sp7C -= 0x2A;
        if (*sp7C < 0) {
            *sp7C = 0;
        }
        var_s0 = D_807FBB40;
        break;
    case 3:                                         /* switch 2 */
        *sp7C -= 0x2A;
        if (*sp7C < 0) {
            *sp7C = 0;
        }
        D_807FBB4C->unk155 = (u8) (D_807FBB4C->unk155 + 1);
        D_807FBB40->unk60 = (s32) (D_807FBB40->unk60 & 0xFFFF7FFF);
        D_807FBB40->unk128 = 0xFF;
        D_807FBB40->unk155 = (u8) (D_807FBB40->unk155 + 1);
        var_s0 = D_807FBB40;
        break;
    case 4:                                         /* switch 2 */
        *sp7C -= 0x2A;
        if (*sp7C < 0) {
            *sp7C = 0;
        }
        D_807FBB40->unk128 = (s16) (D_807FBB40->unk128 - 0x28);
        var_s0 = D_807FBB40;
        if (var_s0->unk128 < 0x28) {
            D_807FBB4C->unk155 = (u8) (D_807FBB4C->unk155 + 1);
            sfxStopChannel(0x3B, 0, &D_807FBB40);
            actorDespawn(D_807FBB40);
block_29:
            var_s0 = D_807FBB40;
        }
        break;
    }
    var_s0->unkE6 = (s16) (var_s0->unkE6 + *sp7C);
    func_806319C4(D_807FBB40, 0);
}
