// func_80689418 (src/global/8D3E0.c): m2c baseline draft; node tick and actor lifecycle loop
? actorDeregisterActive(void *);                    /* extern */
? actorRegisterActive(void *);                      /* extern */
s32 actorSpawnFromInfo(s32 *, s16);                 /* extern */
s32 func_80612E90(void *, s16, ?);                  /* extern */
? func_80613794(void *, s32);                       /* extern */
? func_8068A1B8();                                  /* extern */
extern ? D_8074E8B0;
extern void *D_807FBB44;
extern void *D_807FC400;

void func_80689418(void) {
    void *sp78;
    s16 sp76;
    s16 sp74;
    f32 sp70;
    f32 sp6C;
    f32 sp68;
    s32 sp64;
    s32 sp60;
    s32 sp5C;
    s16 *var_v0;
    s16 temp_a1;
    s16 temp_a1_2;
    s32 var_a0;
    s32 var_v1;
    void *temp_a0;
    void *temp_s0;
    void *temp_s0_2;
    void *temp_v0;
    void *temp_v0_2;
    void *var_s1;

    var_s1 = D_807FC400;
    if (var_s1 != NULL) {
        do {
            if (var_s1->unk48 != 0) {
                if (var_s1->unk60(var_s1) != 0) {
                    temp_s0 = var_s1->unk44;
                    if (!(temp_s0->unk60 & 0x200000)) {
                        actorDeregisterActive(temp_s0);
                        temp_a0 = var_s1->unk44;
                        var_s1->unk48 = 0U;
                        var_s1->unk10 = (f32) temp_a0->unk7C;
                        var_s1->unk14 = (f32) temp_a0->unk80;
                        var_s1->unk18 = (f32) temp_a0->unk84;
                        var_s1->unk4A = (s16) temp_a0->unk12C;
                        func_80613794(temp_a0, 0);
                        func_80613794(var_s1->unk44, 1 & 0xFF);
                        func_80613794(var_s1->unk44, 2);
                    }
                }
            } else if (var_s1->unk5C(var_s1) != 0) {
                temp_s0_2 = var_s1->unk44;
                var_v1 = 0;
                var_a0 = 0;
                if (temp_s0_2 == NULL) {
                    temp_a1 = var_s1->unk0 + 0x10;
                    var_v0 = &D_8074E8B0 + (0 * 0x30);
loop_9:
                    if (temp_a1 == *var_v0) {
                        var_a0 = 1 & 0xFF;
                    } else {
                        var_v1 += 1;
                        var_v0 += 0x30;
                    }
                    if ((var_a0 == 0) && (var_v1 < 0x80)) {
                        goto loop_9;
                    }
                    sp5C = (s32) temp_a1;
                    temp_v0 = &D_8074E8B0 + (var_v1 * 0x30);
                    sp64 = temp_v0->unk4;
                    sp60 = (s32) temp_v0->unk2;
                    sp68 = var_s1->unk4;
                    sp6C = var_s1->unk8;
                    sp70 = var_s1->unkC;
                    sp76 = 0;
                    sp78 = var_s1 + 0x24;
                    sp74 = var_s1->unk1C;
                    if (actorSpawnFromInfo(&sp5C, temp_a1) != 0) {
                        var_s1->unk48 = 1U;
                        var_s1->unk44 = (void *) D_807FBB44;
                        D_807FBB44->unk11C = (s32) var_s1->unk50;
                        temp_v0_2 = D_807FBB44->unk4;
                        if (temp_v0_2 != NULL) {
                            temp_v0_2->unk34 = (f32) ((f64) var_s1->unk20 * 0.15);
                            D_807FBB44->unk4->unk38 = (f32) ((f64) var_s1->unk20 * 0.15);
                            D_807FBB44->unk4->unk3C = (f32) ((f64) var_s1->unk20 * 0.15);
                        }
                    }
                } else if (var_s1->unk48 == 0) {
                    temp_a1_2 = var_s1->unk58;
                    if (temp_a1_2 != 0) {
                        var_s1->unk44->unk0 = func_80612E90(temp_s0_2, temp_a1_2, 0);
                    }
                    actorRegisterActive(var_s1->unk44);
                    var_s1->unk48 = 1U;
                }
            }
            var_s1 = var_s1->unk68;
        } while (var_s1 != NULL);
    }
    func_8068A1B8();
}
