// menuDrawHighScoreTable (src/menu/3E10.c): stage 5: text identical except last 5 insns of loop tail (target addiu s3;slti at,t2,5;sll t1,s3;move s2,t2;bnez;sra s3,t1 in delay; mine sll t1 before slti, move s2 in delay; same regs, frame exact). NM1 harness (reduced TU, ~0.1s/compile) swept ~4000 variants, all stay at 5 lines: loop forms (do/while ++i / i++ before or after var_s3 / for / while / break-based / comma-in-condition / flag temps / i-1 compares), i type s16/s32/u8/u16, 600 random declaration orders, extra temps (s32/s16/u8 n, t, f) at many decl positions, void-return toggles on f317/_sprintf, do{}while(0) wraps, dead if(G&&G){}, e as inline expr vs named pointer, shift-pair temps. Permuter 240s: no improvement. Parked NON_MATCHING.
extern s8 D_80033F60;
extern s8 D_800339A8;
extern s8 D_80033F61;
extern s16 D_80744518;
extern char *D_800339AC[];
extern u32 D_8076A064;
s32 hudDrawScaledText(s32, s16, s16, f32, void *);

s32 menuDrawHighScoreTable(void *arg0, s32 arg1) {
    void *temp_s0;
    f32 sp140;
    f32 sp13C;
    s32 ft4;
    Menu3B_Struct_6 *e;
    Menu3B_Struct_6 *sp130;
    char sp68[0xC8];
    s16 var_s3;
    s16 i;

    temp_s0 = *(void **)((u8 *)arg0 + 0x174);
    D_807FBB60 &= ~0x10;
    func_800317E8(temp_s0, 160.0f, 20.0f, &sp140, &sp13C, 2, 0, 1.0f);
    arg1 = textDrawStringVtx(arg1, 1, 0x280, (s16)(sp13C * 4.0), ((void **)D_80033F28)[D_800339A8 + 0x5F], 0x81);
    func_800317E8(temp_s0, 160.0f, 205.0f, &sp140, &sp13C, 2, 0, 1.0f);
    i = 0;
    var_s3 = (s16)(sp13C * 4.0);
    if (D_80033F60 >= 0) {
        _sprintf(sp68, "%s", ((void **)D_80033F28)[0x63]);
        i = 1;
    } else if (D_80033F60 == -2) {
        _sprintf(sp68, "%s %d.", ((void **)D_80033F28)[0x64], D_80744518);
        i = 1;
    }
    if (i != 0) {
        arg1 = hudDrawScaledText(arg1, 0x280, var_s3, 0.6f, sp68);
    }
    i = 0;
    func_800317E8(temp_s0, 20.0f, 120.0f, &sp140, &sp13C, 2, 0, 2.0f);
    var_s3 = 0xC8;
    ft4 = (s16)(s32)(sp140 * 4.0f);
    if (D_800339A8 == 0) {
        sp130 = D_80744548;
    } else {
        sp130 = D_80744568;
    }
    do {
        _sprintf(sp68, "%d.", i + 1);
        e = (Menu3B_Struct_6 *)((u8 *)sp130 + i * 6);
        arg1 = textDrawStringVtx(arg1, 1, (s16)(ft4 + 0x50), var_s3, sp68, 1);
        _sprintf(sp68, "%c %c %c", e->unk2, e->unk3, e->unk4);
        arg1 = textDrawStringVtx(arg1, 0x81, (s16)(ft4 + 0x118), var_s3, sp68, 1);
        _sprintf(sp68, "%d", e->unk0);
        arg1 = textDrawStringVtx(arg1, 0x81, (s16)(0x3E8 - ft4), var_s3, sp68, 1);
        if (i == D_80033F60 && (D_8076A064 & 0x1F) < 0x14) {
            arg1 = textDrawStringVtx(arg1, 0x81, (s16)(ft4 + 0x118), var_s3 + 0x34, D_800339AC[D_80033F61], 1);
        }
        var_s3 += 0x6C;
    } while (++i < 5);
    return arg1;
}
