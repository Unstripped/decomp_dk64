// func_806A2B90 (src/global/A7710.c): stage 1 only: m2c starter, not attempted by hand. Shape: display-list builder (gfx, actor); 5 WRITE_GFX quads then branch on actor->unk15F==0xB (func_8070068C + func_806FC530 path) else 2pi-2*unk160 double math + func_806FE078, then unk154==2 tail with func_80612D1C/80612D10 double math and func_80714CC0
s32 func_805FCA64();                                /* extern */
f32 func_80612D10(f32);                             /* extern */
f32 func_80612D1C(f32);                             /* extern */
void *func_806FC530(void *, ?, s16, s16, s32, s32); /* extern */
void *func_806FD9B4(u8);                            /* extern */
void *func_806FE078(void *, u8, s32, f32, f32, f32, f32); /* extern */
void *func_8070068C(void *, void *, void *);        /* extern */
? func_8071495C();                                  /* extern */
? func_80714CC0(? *, ?, f32, f32, f32);             /* extern */
extern ? D_1000118;
extern ? D_2000180;
extern ? D_8071FC58;
extern void *D_807FC924;

void *func_806A2B90(void *arg0, void *arg1) {
    void *sp5C;
    f32 sp40;
    f32 sp34;
    s32 sp30;
    s32 var_v0;
    u8 temp_t9;
    void *temp_s0;
    void *temp_s0_2;
    void *temp_s0_3;
    void *temp_s0_4;
    void *temp_s0_5;
    void *temp_s0_6;
    void *temp_v0;
    void *var_s0;

    var_s0 = arg0;
    sp5C = arg1->unk174;
    if (func_805FCA64() != 0) {
        temp_s0 = var_s0 + 8;
        var_s0->unk4 = &D_1000118;
        var_s0->unk0 = 0xDE000000;
        temp_s0_2 = temp_s0 + 8;
        var_s0->unk8 = 0xFC119623;
        temp_s0->unk4 = 0xFF2FFFFF;
        temp_s0->unk8 = 0xFA000000;
        temp_s0_3 = temp_s0_2 + 8;
        temp_s0_2->unk4 = (s32) ((arg1->unk128 & 0xFF) | ~0xFF);
        temp_s0_4 = temp_s0_3 + 8;
        temp_s0_2->unk8 = 0xDA380003;
        temp_s0_3->unk4 = &D_2000180;
        temp_s0_3->unk8 = 0xE200001C;
        temp_s0_4->unk4 = 0x504240;
        temp_t9 = arg1->unk15F;
        temp_s0_5 = temp_s0_4 + 8;
        sp30 = (s32) temp_t9;
        if (temp_t9 == 0xB) {
            temp_s0_6 = func_8070068C(temp_s0_5, temp_s0_3, temp_s0_4);
            var_s0 = func_806FC530(temp_s0_6, 0x86, (s16) (s32) (arg1->unk7C * 4.0f), (s16) ((D_807FC924->unk276 * 4) - 0x3C), func_806FD9B4(sp5C->unk10)->unk4, 1);
        } else {
            var_v0 = 8;
            sp40 = (f32) (6.2831854820251465 - (2.0 * arg1->unk160));
            if (arg1->unk168 == 3) {
                var_v0 = -7;
            }
            temp_v0 = func_806FE078(temp_s0_5, sp5C->unk10, sp30, arg1->unk7C + (f32) var_v0, arg1->unk80 + 5.0f, 0.0f, 1.0f);
            var_s0 = temp_v0;
            if (arg1->unk154 == 2) {
                var_s0 = func_8070068C(temp_v0);
                func_8071495C();
                sp34 = func_80612D1C(sp40);
                func_80714CC0(&D_8071FC58, 0x3F000000, (f32) (((f64) sp34 * 40.0) + (f64) (40.0f + arg1->unk7C)), (f32) (((f64) func_80612D10(sp40) * 25.0) + (f64) arg1->unk80), 0.0f);
            }
        }
    }
    return var_s0;
}
