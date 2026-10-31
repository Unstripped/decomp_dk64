// func_8069FA40 (src/global/A2F10.c): stage 5: frame 0x100, spill 0x2C and every stack offset match; ONLY diff: last WRITE_GFX (0xDA380003) keeps 'move v0,s0' _g web in target, ours folds it into s0. Key fixes: scale as named f64 with if/else duplicating (f64)unkE0-2.0 (not ternary/temp: frame +8), s32 sp2C=label via textGetStringWidth(sp2C = sp65,..) + (s16)sp2C, s32 sel=unk15F used in switch/arms with 'sel ^ 0' selector, (0x140-w)<<1, textGetStringWidth s32(s16,char*), textDrawStringVtx(Gfx*,s16,s16,s16,u8*,u8)
extern char *D_80750338[];
Gfx *func_8070068C(Gfx *);
void *_sprintf(char *, const char *, ...);
void *heapAlloc(s32);
void heapFreeDeferred(void *);
s32 textGetStringWidth(s16, char *);
Gfx *textDrawStringVtx(Gfx *, s16, s16, s16, u8 *, u8);

void func_8069FA40(Gfx *arg0, Actor *arg1) {
    f32 spFC;
    f32 spBC[4][4];
    f32 sp7C[4][4];
    void *sp78;
    char sp68[0x10];
    s16 sp66;
    u8 sp65;
    u8 sp64;
    s32 sp2C;
    f64 scale;
    s32 sel;

    if (((f64)((ActorTail *)arg1)->unkE0 - 2.0) < 0.01) { scale = 0.01; } else { scale = (f64)((ActorTail *)arg1)->unkE0 - 2.0; }
    spFC = (f32)(scale * 0.3);
    sp64 = 0;
    WRITE_GFX(arg0++, 0xDE000000, (u32)&D_1000118);
    WRITE_GFX(arg0++, 0xFC119623, 0xFF2FFFFF);
    WRITE_GFX(arg0++, 0xE200001C, 0x00504240);
    WRITE_GFX(arg0++, 0xE7000000, 0);
    WRITE_GFX(arg0++, 0xFA000000, (arg1->unkE6 & 0xFF) | 0xFFFFFF00);
    arg0 = func_8070068C(arg0);
    sp78 = heapAlloc(0x40);
    heapFreeDeferred(sp78);
    sp65 = 1;
    sel = arg1->unk15F;
    switch (sel ^ 0) {  // FAKE: keeps the switch selector copy (v0) out of copy propagation
    case 0:
        _sprintf(sp68, "ROUND");
        break;
    case 0x1E:
    case 0x1F:
    case 0x20:
    case 0x21:
    case 0x22:
    case 0x23:
    case 0x24:
    case 0x25:
    case 0x26:
        sp64 = 1;
        _sprintf(sp68, D_80750338[sel]);
        break;
    default:
        if (sel & 0x80) {
            sp65 = 3;
            spFC = (f32)(4.0 - (f64)spFC);
            _sprintf(sp68, "%d", 0xA - (sel & 0x3F));
        } else if (sel & 0x40) {
            sp65 = 3;
            spFC = (f32)(4.0 - (f64)spFC);
            _sprintf(sp68, "%d", 8 - (sel & 0x3F));
        } else {
            _sprintf(sp68, "%d", sel);
        }
        break;
    }
    sp66 = textGetStringWidth(sp2C = sp65, sp68);
    if (sp64 != 0) {
        arg1->unk7C = (f32)((0x140 - sp66) << 1);
    }
    guScaleF(spBC, spFC, spFC, 1.0f);
    guTranslateF(sp7C, (f32)((f64)arg1->unk7C + 2.0 * (f64)sp66),
                 arg1->unk80 * 4.0f, 0.0f);
    guMtxCatF(spBC, sp7C, spBC);
    guMtxF2L(spBC, (Mtx *)sp78);
    WRITE_GFX(arg0++, 0xDA380003, (u32)sp78);
    textDrawStringVtx(arg0, (s16)sp2C, (s16)(sp66 * -2), 0, sp68, 0);
}
