// func_8069FA40 (src/global/A2F10.c): stage 2/3: single f64 local gives frame 0x100 and every stack offset identical to the target except one anonymous f32 temp at 0x38 (target 0x2C, shares that slot with a spilled s32) and the s32 label copy is copy-propagated away (target keeps it: sw a2C + lh a2E); code order otherwise identical
typedef struct M4ActorTail {
    /* 0x000 */ u8 pad0[0x60];
    /* 0x060 */ u32 unk60;
    /* 0x064 */ u8 pad64[0x18];
    /* 0x07C */ f32 unk7C;
    /* 0x080 */ f32 unk80;
    /* 0x084 */ f32 unk84;
    /* 0x088 */ u8 pad88[0x58];
    /* 0x0E0 */ f32 unkE0;
    /* 0x0E4 */ u8 padE4[2];
    /* 0x0E6 */ s16 unkE6;
    /* 0x0E8 */ u8 padE8[6];
    /* 0x0EE */ s16 unkEE;
    /* 0x0F0 */ u8 padF0[0x6F];
    /* 0x15F */ u8 unk15F;
    /* 0x160 */ f64 unk160;
} M4ActorTail;
extern Actor *D_807FBB40;
extern Gfx D_1000118;
#define WRITE_GFX(pkt, _w0, _w1) { Gfx *_g = (Gfx *)(pkt); _g->words.w0 = (_w0); _g->words.w1 = (_w1); }

extern char *D_80750338[];
Gfx *func_8070068C(Gfx *);
void *_sprintf(char *, const char *, ...);
void *heapAlloc(s32);
void heapFreeDeferred(void *);
s16 textGetStringWidth(u8, char *);
Gfx *textDrawStringVtx(Gfx *, s32, s16, s16, s32, s32);

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

    scale = (f64)((M4ActorTail *)arg1)->unkE0 - 2.0;
    if (scale < 0.01) {
        scale = 0.01;
    }
    sp64 = 0;
    spFC = (f32)(scale * 0.3);
    WRITE_GFX(arg0++, 0xDE000000, (u32)&D_1000118);
    WRITE_GFX(arg0++, 0xFC119623, 0xFF2FFFFF);
    WRITE_GFX(arg0++, 0xE200001C, 0x00504240);
    WRITE_GFX(arg0++, 0xE7000000, 0);
    WRITE_GFX(arg0++, 0xFA000000, (arg1->unkE6 & 0xFF) | 0xFFFFFF00);
    arg0 = func_8070068C(arg0);
    sp78 = heapAlloc(0x40);
    heapFreeDeferred(sp78);
    sp65 = 1;
    switch (((M4ActorTail *)arg1)->unk15F) {
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
        _sprintf(sp68, D_80750338[((M4ActorTail *)arg1)->unk15F]);
        break;
    default:
        if (((M4ActorTail *)arg1)->unk15F & 0x80) {
            sp65 = 3;
            spFC = (f32)(4.0 - (f64)spFC);
            _sprintf(sp68, "%d", 0xA - (((M4ActorTail *)arg1)->unk15F & 0x3F));
        } else if (((M4ActorTail *)arg1)->unk15F & 0x40) {
            sp65 = 3;
            spFC = (f32)(4.0 - (f64)spFC);
            _sprintf(sp68, "%d", 8 - (((M4ActorTail *)arg1)->unk15F & 0x3F));
        } else {
            _sprintf(sp68, "%d", ((M4ActorTail *)arg1)->unk15F);
        }
        break;
    }
    sp2C = sp65;
    sp66 = textGetStringWidth(sp65, sp68);
    if (sp64 != 0) {
        arg1->unk7C = (f32)((0x140 - sp66) * 2);
    }
    guScaleF(spBC, spFC, spFC, 1.0f);
    guTranslateF(sp7C, (f32)((f64)arg1->unk7C + 2.0 * (f64)sp66),
                 arg1->unk80 * 4.0f, 0.0f);
    guMtxCatF(spBC, sp7C, spBC);
    guMtxF2L(spBC, (Mtx *)sp78);
    WRITE_GFX(arg0++, 0xDA380003, (u32)sp78);
    textDrawStringVtx(arg0, (s16)sp2C, (s16)(sp66 * -2), 0, sp68, 0);
}
