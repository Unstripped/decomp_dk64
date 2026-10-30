// func_8002C76C (src/race/7BD0.c): stage 4+ (parked): frame 0x78, all stack slots (sp68/u8/sp60/sp5C/sp50/sp4C/sp48/spill 0x30), saved regs and ~all regs/schedule match; 13 diff lines left = string reloc addend (.rodata+4 vs sym, harmless), ori t6 / addiu t7 order in the 3rd gfx pair (2 lines), plus lh a2,50(sp) vs lw only if the file prototype is NOT changed. Needs textDrawStringVtx prototype s16 for params 3 and 4 (Gfx *textDrawStringVtx(Gfx *, s32, s16, s16, void *, s32)): then the s16 spill reloads with lh; whole 7BD0 copy still TEXT OK with that prototype. Findings: the O-region bloat was the WRITE_GFX macro's block-scope 'Gfx *_g' locals (one home each, siblings do not share); using ONE function-level Gfx *g0 for 3 of the 4 writes (real WRITE_GFX kept only for the 2nd) removes 3 words and gives frame 0x78 with the 15-word named layout (pads at 0x6c, 0x58/0x54 replaced by var_v0/ret); order of the 1st write: g0->words.w1 then w0. sp48 = strlen(a); sp48 += strlen(b); sp68 = heapAlloc(sp48 + 8) reproduces the 'sw v0,72(sp) in the 2nd strlen jal delay slot / lw v1,72' spill + addu order. u32 ret = textGetFontHeight(1); (0.5f * (f32)ret) fixes the f4/f6 FP order. A separate int var_v0 (not var_a3) for the table index puts it in v0 (target) instead of a3. Single u8 var_t0 with the two ternaries (see previous note). Untried: the remaining ori/addiu swap (tried g01/g10 orientation, comma/ret temps, hex spellings, base+offset forms).
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
Gfx *textDrawAnimated(Gfx *, s32, s32, f32, f32, f32, f32);
#define RaceE76C ((RaceE76CView *)arg1)

Gfx *func_8002C76C(Gfx *arg0, RaceUnknown174 *arg1) {
    RaceUnknown174 *temp_t1;
    Struct806C7C94 *temp_v0;
    s32 pad6C;
    void *sp68;
    u8 var_t0;
    s32 sp60;
    s32 sp5C;
    s32 var_v0;
    u32 ret;
    s32 sp50;
    s32 sp4C;
    s32 sp48;
    s32 var_a3;
    Gfx *g0;

    temp_v0 = arg1->unk48;
    var_t0 = RaceE76C->unk37;
    temp_t1 = arg1->unk30->unk174;
    sp60 = temp_v0->unk4 + 8;
    sp5C = temp_v0->unkA - 0x10;
    g0 = arg0++;
        g0->words.w1 = 0;
        g0->words.w0 = 0xE7000000;
    WRITE_GFX(arg0++, 0xFA000000, 0xFFFFFFFF);
    var_a3 = temp_t1->unk0;
    if (var_a3 & 4) {
        var_t0 = (var_t0 < temp_t1->unk24) ? var_t0 : temp_t1->unk24;
        var_t0 = (var_t0 >= 2) ? var_t0 : 1;
        sp50 = (s32)textTableGetString(0x26, 0xB, 1);
        sp4C = (s32)textTableGetString(0x26, 0xC, 1);
        sp48 = strlen((u8 *)sp50);
        sp48 += strlen((u8 *)sp4C);
        sp68 = heapAlloc(sp48 + 8);
        heapFreeDeferred(sp68);
        _sprintf(sp68, "%s %d %s %d", sp50, var_t0, sp4C, temp_t1->unk24);
        arg0 = textDrawStringVtx(arg0, 1, (s16)(s32)(2.0f * (f32)(sp60 * 4)), (s16)(s32)(2.0f * (f32)(sp5C * 4)), sp68, 4);
        g0 = arg0++;
        g0->words.w0 = 0xDA380007;
        g0->words.w1 = (u32)&D_20000C0;
        g0 = arg0++;
        g0->words.w0 = 0xDA380005;
        g0->words.w1 = (u32)((u8 *)arg1 + (D_807444FC << 6) + 0x50);
        ret = textGetFontHeight(1);
        sp5C = (s32)((f32)sp5C - (0.5f * (f32)ret));
        var_a3 = temp_t1->unk0;
    }
    if (var_a3 & 2) {
        var_v0 = RaceE76C->unk36;
        if ((var_v0 + 1) == temp_t1->unk1E) {
            var_v0 = 3;
        }
        if (RaceE76C->unk45 != 0) {
            var_v0 = 4;
        }
        arg0 = textDrawStringVtx(arg0, 1, (s16)(s32)((f32)(sp60 * 4) + (f32)(sp60 * 4)), (s16)(s32)(2.0f * (f32)(sp5C * 4)), textTableGetString(0x26, D_8002FCC0[var_v0], 1), 4);
    }
    if (RaceE76C->unk34 >= 3 && RaceE76C->unk34 < 5) {
        arg0 = textDrawAnimated(arg0, RaceE76C->unk46, 2, 160.0f, 100.0f, 0.0f, 1.5f);
    }
    return arg0;
}
