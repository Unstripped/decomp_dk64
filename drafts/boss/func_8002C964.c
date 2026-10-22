// func_8002C964 (src/boss/8520.c): from .scratch/Boss3C/func_8002C964_best.c
? func_8002C5F4(void *);                            /* extern */
? func_8002C748(?);                                 /* extern */
? func_8002C7CC();                                  /* extern */
? func_8002C8B4(void *);                            /* extern */
? func_806086CC(f32, f32, void *, f32, ?, s32, s32, s32, s32, f32, s32); /* extern */
s32 func_80611A44();                                /* extern */
f32 func_80612790(s16);                             /* extern */
f32 func_80612794(s16);                             /* extern */
? func_80613C48(void *, ?, ?, ?);                   /* extern */
? func_80614EBC(void *, ?);                         /* extern */
s32 func_8061CB50();                                /* extern */
? func_8061CC40(void *, ?, ?);                      /* extern */
? func_80626110(s32, ?, ?);                         /* extern */
s32 func_80629148(void *, ?);                       /* extern */
? func_806319C4(void *, ?);                         /* extern */
s16 func_80665DE0(?32, ?32, void *, s32, s32);      /* extern */
? func_8067E278(?, ?);                              /* extern */
? func_806AD260(?, ?, ?);                           /* extern */
? func_806AD9AC();                                  /* extern */
s16 func_806CC190(s16, s16, ?);                     /* extern */
? func_807248B0(void *, f32);                       /* extern */
s32 func_80726D7C(?);                               /* extern */
? func_80729B00();                                  /* extern */
? func_8072AB74(?, ?32, ?32, ?, f32);               /* extern */
? func_8072B324(void *, u8);                        /* extern */
? func_8072D714(s32, ?);                            /* extern */
? func_8072D9D4();                                  /* extern */
s32 func_8073110C(?, ?);                            /* extern */
extern s32 D_807F5D10;
extern void *D_807FBB40;
extern u8 D_807FBB85;
extern s32 D_807FBD6C;
extern u8 D_807FBD70;
extern void *D_807FDC90;
extern void *D_807FDC94;
extern void *D_807FDC98;
extern void *D_807FDC9C;

void func_8002C964(void) {
    void *sp3C;
    f32 temp_fv0_2;
    f32 temp_fv0_3;
    f64 temp_fv0;
    s16 temp_v0;
    s16 temp_v0_2;
    s16 temp_v1_4;
    s16 var_v1;
    u8 temp_t8;
    u8 temp_v1;
    u8 temp_v1_2;
    u8 temp_v1_3;
    void *temp_a0;
    void *temp_a0_2;

    sp3C = D_807FBB40->unk178;
    func_80729B00();
    temp_a0 = D_807FBB40;
    if (!(temp_a0->unk60 & 0x10)) {
        func_8002C748(0);
        func_8002C748(1);
        D_807FDC98->unk30 = 2.5f;
        D_807FDC98->unk46 = (u16) (D_807FDC98->unk46 & 0xFFF7);
        D_807FDC98->unk46 = (u16) (D_807FDC98->unk46 | 0x200);
        D_807FBB40->unk60 = (s32) (D_807FBB40->unk60 | 0x400);
        D_807FBB40->unk132 = 4;
        D_807FBB40->unk154 = 0x1E;
        func_807248B0(D_807FBB40, (f32) (2.0 * (f64) D_807FBB40->unk4->unk34));
        func_806AD9AC();
    }
    if (((D_807FBD70 == 9) || (D_807FBB85 != 0)) && (temp_a0->unk154 != 0x37)) {
        if (func_8073110C(0xF7, 0) != 0) {
            func_8067E278(0, 1);
            D_807FBB40->unk154 = 0x40;
        } else {
            func_8061CC40(D_807FBB40, 6, 1);
            D_807FBB40->unkC0 = 200.0f;
            func_8072D714(D_807FBD6C, 0x2F7);
        }
    }
    temp_t8 = temp_a0->unk154;
    switch (temp_t8) {                              /* switch 1 */
    case 0x28:                                      /* switch 1 */
        temp_v1 = temp_a0->unk155;
        switch (temp_v1) {                          /* switch 2; irregular */
        case 0:                                     /* switch 2 */
            func_8061CC40(temp_a0, 8, 1);
            func_80614EBC(D_807FBB40, 0);
            func_80613C48(D_807FBB40, 0x589, 0, 0);
            D_807FDC90->unk2C = 0;
            D_807FBB40->unk155 = 1U;
            D_807FBB40->unk144 = 1;
            func_806086CC(D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40, D_807FBB40->unk84, 0x2FC, 0xFF, 0x7F, 0, 0, 0.0f, 0);
            /* fallthrough */
        case 1:                                     /* switch 2 */
            D_807FDC90->unk2C = (s16) (D_807FDC90->unk2C + 8);
            if (D_807FDC90->unk2C >= 0x259) {
                D_807FBB40->unk155 = 2U;
            }
            D_807FBB40->unk80 = (f32) (D_807FBB40->unk80 + 2.0f);
            D_807FBB40->unkE6 = (s16) (D_807FBB40->unkE6 + D_807FDC90->unk2C);
            temp_fv0 = (f64) D_807FBB40->unk4->unk38;
            func_807248B0(D_807FBB40, (f32) (((0.3 - temp_fv0) * 0.05) + temp_fv0));
            break;
        case 2:                                     /* switch 2 */
            D_807FDC90->unk2C = (s16) (D_807FDC90->unk2C - 0x14);
            var_v1 = D_807FDC90->unk2C;
            if (var_v1 < 0) {
                D_807FDC90->unk2C = 0;
                var_v1 = D_807FDC90->unk2C;
            }
            D_807FBB40->unkE6 = (s16) (D_807FBB40->unkE6 + var_v1);
            if (func_80629148(D_807FBB40, 8) != 0) {
                D_807FBB40->unk155 = 3U;
                D_807FBB40->unk60 = (s32) (D_807FBB40->unk60 & ~4);
            }
            break;
        case 3:                                     /* switch 2 */
            if (func_80629148(temp_a0, 8) != 0) {
                D_807FBB40->unk15E = 0xA;
                D_807FDC90->unk28 = (s32) (D_807FDC90->unk28 | 0x8000);
                D_807FBB40->unk132 = 1;
                D_807FBB40->unk154 = 0x23;
                func_8072B324(D_807FBB40, D_807FDC9C->unkD);
                D_807FBB40->unk144 = 0x24;
                func_80614EBC(D_807FBB40, 0x2F4);
            }
            break;
        }
        break;
    case 0x1E:                                      /* switch 1 */
        temp_v1_2 = temp_a0->unk155;
        switch (temp_v1_2) {                        /* switch 3; irregular */
        case 0:                                     /* switch 3 */
            if (func_80629148(temp_a0) != 0) {
                D_807FDC90->unk28 = (s32) (D_807FDC90->unk28 | 0x8000);
                D_807FBB40->unk155 = 1U;
            }
            break;
        case 2:                                     /* switch 3 */
            temp_fv0_2 = temp_a0->unk80;
            if ((temp_fv0_2 - temp_a0->unkA4) > 300.0f) {
                temp_a0->unk80 = (f32) (temp_fv0_2 - 10.0f);
            } else {
                D_807FDC90->unk28 = (s32) (D_807FDC90->unk28 | 0x8000);
                D_807FBB40->unk155 = 3U;
            }
            break;
        case 3:                                     /* switch 3 */
            if (func_80629148(temp_a0) != 0) {
                D_807FBB40->unk154 = 0x27;
                D_807FBB40->unk155 = 0U;
                func_80626110(D_807F5D10, 0, 0);
            }
            break;
        }
        break;
    case 0x27:                                      /* switch 1 */
        D_807FBB40->unkE6 = func_806CC190(D_807FBB40->unkE6, func_80665DE0(D_807FDC94->unk7C, D_807FDC94->unk84, temp_a0, temp_a0->unk7C, temp_a0->unk84), 0x41000000);
        temp_a0_2 = D_807FBB40;
        temp_v1_3 = temp_a0_2->unk155;
        switch (temp_v1_3) {                        /* switch 4; irregular */
        case 0:                                     /* switch 4 */
            func_8002C5F4(temp_a0_2);
            D_807FBB40->unk155 = 1U;
            break;
        case 1:                                     /* switch 4 */
            if ((func_80726D7C(2) == 0) && (func_80726D7C(3) == 0) && (func_80726D7C(4) == 0)) {
                D_807FBB40->unk155 = 2U;
                D_807FDC90->unk2C = 0x96;
                D_807FDC90->unk28 = (s32) (D_807FDC90->unk28 | 0x8000);
                D_807FBB40->unk132 = 8;
                func_80614EBC(D_807FBB40, 0x2FA);
            }
            if ((func_8061CB50() == 0) && (((s32) (func_80611A44() >> 0xF) % 1000) >= 0x3E4)) {
                func_80614EBC(D_807FBB40, 0x2FD);
                D_807FBB40->unk155 = 3U;
            }
            break;
        case 2:                                     /* switch 4 */
            temp_v1_4 = D_807FDC90->unk2C;
            if ((temp_v1_4 != 0) && (D_807FBD70 != 4)) {
                D_807FDC90->unk2C = (s16) (temp_v1_4 - 1);
            } else {
                if (D_807FBD70 == 4) {
                    func_80614EBC(temp_a0_2, 0x2FC);
                    func_8072D9D4();
                    sp3C->unk2 = 0x96;
                    sp3C->unk4 = 0x800;
                    D_807FBB40->unkEE = (s16) D_807FBB40->unkE6;
                    if (D_807FBB40->unk134 == 1) {
                        D_807FBB40->unk154 = 0x28;
                        D_807FBB40->unk155 = 0U;
                    }
                }
                temp_a0_2->unk132 = 4;
                D_807FDC90->unk28 = (s32) (D_807FDC90->unk28 | 0x8000);
                D_807FBB40->unk155 = 0U;
            }
            break;
        case 4:                                     /* switch 4 */
            temp_a0_2->unk155 = 1U;
            func_8002C8B4(temp_a0_2);
            break;
        }
        break;
    case 0x23:                                      /* switch 1 */
        func_8072AB74(0x23, D_807FDC94->unk7C, D_807FDC94->unk84, 0, 0.0f);
        break;
    case 0x37:                                      /* switch 1 */
        func_806AD260(0x2F7, 1, 0);
        break;
    }
    if (sp3C->unk2 > 0) {
        temp_fv0_3 = func_80612794(sp3C->unk4);
        temp_v0 = sp3C->unk2;
        sp3C->unk4 = (s16) (sp3C->unk4 + 0x32);
        sp3C->unk2 = (s16) (temp_v0 - 1);
        sp3C->unk0 = (s16) (s32) (temp_fv0_3 * (f32) temp_v0);
        D_807FBB40->unkE8 = (s16) -sp3C->unk0;
        D_807FBB40->unk7C = (f32) ((func_80612794(D_807FBB40->unkEE) * (f32) sp3C->unk0) + (f32) D_807FDC9C->unk4);
        D_807FBB40->unk84 = (f32) ((func_80612790(D_807FBB40->unkEE) * (f32) sp3C->unk0) + (f32) D_807FDC9C->unk8);
        temp_v0_2 = sp3C->unk0;
        D_807FBB40->unk80 = (f32) ((f32) D_807FDC9C->unk6 - sqrtf((f32) (0x1C390 - (temp_v0_2 * temp_v0_2))));
    }
    if (D_807FDC90->unk28 & 0x8000) {
        func_8002C7CC();
    }
    func_806319C4(D_807FBB40, 0);
}
