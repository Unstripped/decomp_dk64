// func_80696574 (src/global/936B0.c): Unattempted starter draft from m2c (reached budget limit)
? actorDespawn(void *);                             /* extern */
? func_80608528(void *, ?, ?, ?, s32);              /* extern */
s32 func_80611A44();                                /* extern */
f32 func_80612790(s16);                             /* extern */
? func_8061F0B0(s32, ?, ?);                         /* extern */
? func_806319C4(void *, ?);                         /* extern */
? func_8065D254(void *, ?, ?, ?, s32, s32, s32, s32, s32, s32, f32); /* extern */
? func_806651FC(void *);                            /* extern */
? func_80665564(void *, f32);                       /* extern */
? func_80666280(?, ?, ? *);                         /* extern */
? func_80666290(void *, ? *, ? *, ? *, ? *, s32);   /* extern */
? func_8067ACB4(void *);                            /* extern */
? func_80685B44(? *, ?, ?, ?, s32, s32, s32, s32, s32); /* extern */
? playerStateQueueCallback(?, void *, ?);                      /* extern */
extern ? D_8071FFA0;
extern s16 D_807502D0;
extern f32 D_807502F8;
extern s32 D_8076A068;
extern void *D_807FBB40;
extern s32 D_807FBB64;
extern ? D_807FBB70;
extern void *D_807FD580;

void func_80696574(void) {
    ? sp79;
    ? sp78;
    ? sp70;
    ? sp6C;
    f32 temp_fv0;
    f32 temp_fv0_3;
    f64 temp_fv0_2;
    f64 var_fv1;
    s16 var_v0;
    s32 temp_a0;
    s32 temp_ft2;
    s32 temp_t5;
    s32 var_v0_2;
    u8 temp_v1_2;
    void *temp_s0;
    void *temp_s0_2;
    void *temp_v0;
    void *temp_v1;

    if (!(D_807FBB40->unk60 & 0x10)) {
        temp_fv0 = D_807FBB40->unk80;
        D_807FBB40->unk9C = temp_fv0;
        D_807FBB40->unkA0 = temp_fv0;
        if (D_807FBB64 & 0x80000) {
            D_807FBB40->unk144 = 0x3C;
        } else {
            D_807FBB40->unk144 = 0x1C;
        }
        *D_807FBB40->unk174 = D_8076A068;
        D_807FBB40->unk60 = (s32) (D_807FBB40->unk60 | 0x80000);
        func_80666290(D_807FBB40, &sp79, &sp70, &sp78, &sp6C, (s32) sp77);
        D_807FBB40->unkC4 = (f32) (D_807502F8 - (f32) ((s32) ((s32) (func_80611A44() >> 0xF) % 32767) % 10));
        D_807FBB40->unk6A = (u16) (D_807FBB40->unk6A & 0xFFFE);
    }
    if (D_807FBB70.unk200 == 5) {
        temp_v0 = D_807FBB70.unk1FC->unk174;
        temp_v1 = temp_v0->unk88;
        if ((temp_v1 != NULL) && ((temp_a0 = temp_v1->unk58, (temp_a0 == 0x1D)) || (temp_a0 == 0x50))) {
            func_8061F0B0(temp_v0->unk104, 0xA, 0x14);
            playerStateQueueCallback(0x34, D_807FBB40, 0);
            func_80685B44(&D_8071FFA0, 0, 0x3F800000, 4, 0x14, 0x96, (s32) D_807FBB40->unk7C, (s32) D_807FBB40->unk80, (s32) D_807FBB40->unk84);
            actorDespawn(D_807FBB40);
        }
    } else {
        var_v0 = 0;
        temp_s0 = D_807FBB40;
        if ((s32) D_807FBB70.unk254 > 0) {
            do {
                var_v0 += 1;
                if ((&D_807FBB70 + (var_v0 * 4))->unk258 == 1) {
                    temp_s0->unk154 = 1U;
                }
            } while (var_v0 < (s32) D_807FBB70.unk254);
        }
        if (temp_s0->unk154 == 1) {
            func_80666280(1, 1, &D_807FBB70);
            func_8067ACB4(D_807FBB40);
            func_806651FC(D_807FBB40);
            func_80665564(D_807FBB40, (f32) ((((f64) func_80612790((s16) (D_807FBB40->unkE8 + 0x800)) * 0.5) + 0.5) * 15.0));
            temp_s0_2 = D_807FBB40;
            temp_t5 = temp_s0_2->unk6A & 1;
            var_v0_2 = temp_t5;
            if ((temp_t5 != 0) && !(temp_s0_2->unk6C & 1)) {
                temp_v1_2 = temp_s0_2->unk155;
                if ((s32) temp_v1_2 < 2) {
                    temp_s0_2->unk155 = (u8) (temp_v1_2 + 1);
                    D_807FBB40->unkC0 = (f32) ((f64) (D_807FBB40->unkA0 - D_807FBB40->unk80) * 1.5);
                    func_8061F0B0(D_807FD580->unk104, 0xA, 0x14);
                    func_80608528(D_807FBB40, 0x1C1, 0xFF, 0x7F, 0x1E);
                    func_80685B44(&D_8071FFA0, 0, 0x3F800000, 4, 0x14, 0x96, (s32) D_807FBB40->unk7C, (s32) D_807FBB40->unk80, (s32) D_807FBB40->unk84);
                    var_v0_2 = D_807FBB40->unk6A & 1;
                }
            }
            if (var_v0_2 == 0) {
                temp_fv0_2 = (f64) temp_s0_2->unkC0 * 0.5;
                if (temp_fv0_2 > 0.0) {
                    var_fv1 = temp_fv0_2;
                } else {
                    var_fv1 = -temp_fv0_2;
                }
                temp_s0_2->unkE8 = (s16) (s32) ((f64) temp_s0_2->unkE8 - var_fv1);
            }
            temp_s0_2->unkC0 = (f32) (temp_s0_2->unkC0 + temp_s0_2->unkC4);
            temp_fv0_3 = (f32) D_807502D0;
            if (D_807FBB40->unkC0 < temp_fv0_3) {
                D_807FBB40->unkC0 = temp_fv0_3;
            }
        }
        temp_ft2 = (s32) (temp_s0->unk4->unk38 * 300.0f);
        func_8065D254(temp_s0, 0x3C8, 0x40, 0x40, (s32) (s16) temp_ft2, (s32) (s16) temp_ft2, 1, 0x96, 0x96, 0, 1.0f);
    }
    func_806319C4(D_807FBB40, 0);
}
