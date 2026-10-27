// func_8002CBEC (src/race/7BD0.c): stage 3: all 20 gfx word stores + 4 sprite calls + loop match modulo regs; sole structural diff: the 2.0f float args are hoisted into callee-saved $f20 (frame 0x60 vs 0x58, +sdc1/ldc1) instead of per-call lui/mtc1 into $f0 (tried 2.0, 2, 2.0f; 'x*2 int literal' trick irrelevant here); loop v1 vs a0 reg; first packet w1/w0 store order. permuter 240s found nothing for it
struct RaceECB3;
typedef struct RaceECBPair {
    struct RaceUnknownActor *unk0;
    struct RaceECB3 *unk4;
} RaceECBPair;
typedef struct RaceECBView {
    u8 unk0;
    char pad1[0x13];
    u16 unk14;
    u16 unk16;
    u16 unk18;
    u16 unk1A;
    char pad1C[2];
    u8 unk1E;
    char pad1F;
    RaceECBPair *unk20;
} RaceECBView;
typedef struct RaceECB3 {
    char pad0[0x27];
    u8 unk27;
    char pad28[4];
    struct RaceUnknownActor *unk2C;
} RaceECB3;

Gfx *func_8002CBEC(Gfx *arg0, RaceUnknownActor *arg1) {
    RaceECBView *temp_s5;
    RaceECBPair *var_s2;
    RaceECB3 *temp_s0;
    RaceUnknownActor *temp_t0;
    RaceUnknownActor *temp_v1;
    RaceECBPair *temp_s6;
    s32 var_s3;
    s32 var_v0;
    s32 var_v1;

    temp_s5 = (RaceECBView *)arg1->unk174;
    if (temp_s5->unk0 & 1) {
        temp_s6 = temp_s5->unk20;
        { Gfx *_g = arg0++; _g->words.w1 = 0; _g->words.w0 = 0xE7000000; }
        { Gfx *_g = arg0++; _g->words.w1 = 0xFFFFFFFF; _g->words.w0 = 0xD7000000; }
        WRITE_GFX(arg0++, 0xE200001C, 0x00504240);
        arg0 = func_805FD030(arg0);
        var_v0 = 0x40;
        WRITE_GFX(arg0++, 0xFA000000, 0x3CA0);
        WRITE_GFX(arg0++, 0xE3000A01, 0);
        WRITE_GFX(arg0++, 0xFCFFFFFF, 0xFFFDF6FB);
        WRITE_GFX(arg0++, 0xF6148170, 0x00048070);
        WRITE_GFX(arg0++, 0xE7000000, 0);
        WRITE_GFX(arg0++, 0xFA000000, 0x8000FF64);
        WRITE_GFX(arg0++, 0xF6150070, 0x00040068);
        WRITE_GFX(arg0++, 0xF6150178, 0x00040170);
        WRITE_GFX(arg0++, 0xF6048170, 0x00040070);
        WRITE_GFX(arg0++, 0xF6150170, 0x00148070);
        WRITE_GFX(arg0++, 0xE7000000, 0);
        WRITE_GFX(arg0++, 0xFA000000, 0xFFFFFFB4);
        WRITE_GFX(arg0++, 0xFC119623, 0xFF2FFFFF);
        WRITE_GFX(arg0++, 0xDA380003, (u32)&D_2000180);
        WRITE_GFX(arg0++, 0xDA380007, (u32)&D_20000C0);
        WRITE_GFX(arg0++, 0xD7000002, 0x80008000);
        arg0 = func_8068C5A8(arg0, temp_s5->unk14, 3, 1, 0x40, 0x40, 0x88, 0x130, 2, 2, 0, 0.0f);
        arg0 = func_8068C5A8(arg0, temp_s5->unk16, 3, 1, var_v0, 0x40, 0x108, 0x130, 2, 2, 0, 0.0f);
        arg0 = func_8068C5A8(arg0, temp_s5->unk18, 3, 1, 0x40, 0x40, 0x88, 0xB0, 2, 2, 0, 0.0f);
        arg0 = func_8068C5A8(arg0, temp_s5->unk1A, 3, 1, 0x40, 0x40, 0x108, 0xB0, 2, 2, 0, 0.0f);
        var_s3 = 0;
        var_s2 = temp_s6;
        if (temp_s5->unk1E > 0) {
            do {
                temp_t0 = var_s2->unk0;
                if (temp_t0 != NULL) {
                    temp_s0 = var_s2->unk4;
                    if (temp_s0->unk27 == 0) {
                        var_v0 = 0x80;
                        var_v1 = 0x80;
                    } else {
                        var_v0 = 0xFF;
                        if (temp_s0->unk27 != 1) {
                            goto next;
                        }
                        var_v1 = 0;
                    }
                    arg0 = func_8002BDDC(arg0, arg1, temp_t0->unk7C, temp_t0->unk84, var_v0, 0, var_v1);
                    temp_v1 = temp_s0->unk2C;
                    if (temp_v1 != NULL) {
                        arg0 = func_8002BDDC(arg0, arg1, temp_v1->unk7C, temp_v1->unk84, 0xFF, 0xC8, 0);
                    }
                }
next:
                var_s3 += 8;
                var_s2++;
            } while (var_s3 < (temp_s5->unk1E * 8));
        }
    }
    return func_8002BEE8(arg0, arg1);
}
