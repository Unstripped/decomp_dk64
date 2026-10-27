// func_8002C76C (src/race/7BD0.c): stage 3 (pass 2): int regs/call args/structure match; frame 0x80 vs 0x78 (sp60 at 0x68 vs 0x60: two slot words too many). Slot model: named locals declared before the last stack-resident one take a slot in declaration order, but forward-substituted ones (var_a3) don't; unused pad locals sometimes did not add a slot (pad58 test: no frame change), extras at the bottom (~8 words of CSE/other) constant. Reusing var_a3 as the table index (dropping var_v0) shrank frame 0x88->0x80. Untried: drop sp48 slot via reuse, permuter with frame scoring.
typedef struct RaceE76CView {
    char pad0[0x34];
    u8 unk34;
    u8 unk35;
    u8 unk36;
    u8 unk37;
    char pad38[0x45 - 0x38];
    u8 unk45;
    u8 unk46;
} RaceE76CView;
extern s32 D_8002FCC0[];
u32 strlen(u8 *);
Gfx *func_806FE078(Gfx *, s32, s32, f32, f32, f32, f32);
#define RaceE76C ((RaceE76CView *)arg1)
#define RaceE_PUT(pkt, w0v, w1v) ((pkt)->words.w0 = (w0v), (pkt)->words.w1 = (w1v))

Gfx *func_8002C76C(Gfx *arg0, RaceUnknown174 *arg1) {
    RaceUnknown174 *temp_t1;
    Struct806C7C94 *temp_v0;
    u8 temp_t0;
    void *sp68;
    u8 var_t0_2;
    s32 sp60;
    s32 sp5C;
    u8 var_t0;
    s32 sp50;
    s32 sp4C;
    s32 sp48;
    s32 var_a3;

    temp_v0 = arg1->unk48;
    temp_t0 = RaceE76C->unk37;
    temp_t1 = arg1->unk30->unk174;
    sp60 = temp_v0->unk4 + 8;
    sp5C = temp_v0->unkA - 0x10;
    WRITE_GFX(arg0++, 0xE7000000, 0);
    WRITE_GFX(arg0++, 0xFA000000, 0xFFFFFFFF);
    var_a3 = temp_t1->unk0;
    if (var_a3 & 4) {
        if (temp_t0 < temp_t1->unk24) {
            var_t0 = temp_t0;
        } else {
            var_t0 = temp_t1->unk24;
        }
        if (var_t0 >= 2) {
            var_t0_2 = var_t0;
        } else {
            var_t0_2 = 1;
        }
        sp50 = (s32)func_8070E750(0x26, 0xB, 1);
        sp4C = (s32)func_8070E750(0x26, 0xC, 1);
        sp48 = strlen((u8 *)sp50);
        sp68 = func_80610FE8(sp48 + strlen((u8 *)sp4C) + 8);
        heapFreeDeferred(sp68);
        _sprintf(sp68, "%s %d %s %d", sp50, var_t0_2, sp4C, temp_t1->unk24);
        arg0 = func_806FC530(arg0, 1, (s16)(s32)(2.0f * (f32)(sp60 * 4)), (s16)(s32)(2.0f * (f32)(sp5C * 4)), sp68, 4);
        WRITE_GFX(arg0++, 0xDA380007, (u32)&D_20000C0);
        WRITE_GFX(arg0++, 0xDA380005, (u32)((u8 *)arg1 + (D_807444FC << 6) + 0x50));
        sp5C = (s32)((f32)sp5C - (0.5f * (f32)func_806FD894(1)));
        var_a3 = temp_t1->unk0;
    }
    if (var_a3 & 2) {
        var_a3 = RaceE76C->unk36;
        if ((var_a3 + 1) == temp_t1->unk1E) {
            var_a3 = 3;
        }
        if (RaceE76C->unk45 != 0) {
            var_a3 = 4;
        }
        arg0 = func_806FC530(arg0, 1, (s16)(s32)((f32)(sp60 * 4) + (f32)(sp60 * 4)), (s16)(s32)(2.0f * (f32)(sp5C * 4)), func_8070E750(0x26, D_8002FCC0[var_a3], 1), 4);
    }
    if (RaceE76C->unk34 >= 3 && RaceE76C->unk34 < 5) {
        arg0 = func_806FE078(arg0, RaceE76C->unk46, 2, 160.0f, 100.0f, 0.0f, 1.5f);
    }
    return arg0;
}
