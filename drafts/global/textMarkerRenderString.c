// textMarkerRenderString (src/global/9DD70.c): stage 5, parked NON_MATCHING in 9DD70.c: 350/350 insns, frame 0x60, all stack slots (0x2C/0x30/0x4A/0x54/0x56/0x57/0x5C), cases/switch order, FP code identical. Only diff: final 0xFA000000 Gfx write goes through s0 instead of a v0 copy ('or v0,s0,zero' starts the join block; target default path has it in the b delay slot) + ~14 regs renamed after it. Tried: function-level Gfx g/g2, ptr copies, gfx+1 / ++gfx forms, deadsweep (no improvement), permuter 900s (no 0).
extern Gfx D_1000118;
#define S9D_GFX(pkt, _w0, _w1) { Gfx *_g = (Gfx *)(pkt); _g->words.w0 = (_w0); _g->words.w1 = (u32)(_w1); }

extern s32 D_8074E880[];
void func_80717404(void);
void func_8071495C(void);
void vtxGradientSetPosition(s16);
extern Gfx *textDrawStringVtx(Gfx *, s16, s16, s16, char *, u8);

void textMarkerRenderString(Gfx *gfx, Actor *actor) {
    char **sub;
    s16 x;
    s16 y;
    u8 state;
    u8 mode;
    s16 width;

    if (&state == 0) {} // FAKE: keeps state/mode/width/x/y in spill-style home slots
    sub = actor->unk174;
    state = 3;
    mode = (u8)actor->unk84;
    S9D_GFX(gfx++, 0xDE000000, &D_1000118);
    S9D_GFX(gfx++, 0xFC119623, 0xFF2FFFFF);

    x = actor->unk155[0];
    switch (x) {
        case 2:
            vtxGradientSetPosition((s16)(actor->unk15F * 3 + 0x4000));
            break;
        case 0:
            if (actor->unk84 == 1.0f) {
                s16 w2;

                w2 = (s16)(s32)((((f64)actor->unk15F * 0.0078125 > 1.0 ? 1.0 : (f64)actor->unk15F * 0.0078125) * 0.9) * (f64)textGetStringWidth((s16)(s32)actor->unk84, (s32)*sub) + (f64)actor->unk7C * 0.25);
                func_807149B8(1);
                func_8071498C(func_80717404);
                func_80714950(0xA);
                func_8071495C();
                func_80714CC0((void *)D_8074E880[((randomNonNegative() >> 0xF) % 1000) % 3], 1.0f, (f32)w2, (f32)((f64)actor->unk80 * 0.25 + 12.0), -5.0f);
            }
        default:
            vtxGradientSetPosition((s16)(actor->unk15F * 3));
            break;
    }

    x = (s16)(s32)actor->unk7C;
    y = (s16)(s32)actor->unk80;
    switch (mode) {
        case 1:
            width = textGetStringWidth((s16)(s32)actor->unk84, (s32)*sub);
            state = 0x13;
            gfx = renderAppendScaledMatrix(gfx, (ActorPositionView *)actor, width, 0.8f);
            state &= 0xFFFE;
            x = -(width * 2);
            y = 0;
            break;
        case 6:
            state = 0x23;
            S9D_GFX(gfx++, 0xE3000A01, 0x100000);
            S9D_GFX(gfx++, 0xE200001C, 0x0C184240);
            break;
        case 0:
            mode = 6;
            width = textGetStringWidth(6, (s32)*sub);
            actor->unk7C = (f32)((D_80744490 - width) * 2);
            gfx = renderAppendScaledMatrix(gfx, (ActorPositionView *)actor, width, 0.8f);
            state = 0;
            x = -(width * 2);
            y = 0;
            break;
        case 10:
            mode = 6;
            gfx = renderAppendScaledMatrix(gfx, (ActorPositionView *)actor, 0, 0.8f);
            state = 0;
            x = 0;
            y = 0;
            break;
    }

    S9D_GFX(gfx++, 0xFA000000, (actor->unk16A << 24) | (actor->unk16B << 16) | (actor->unk16C << 8) | actor->unk15F);
    textDrawStringVtx(gfx, (s16)mode, x, y, *sub, state);
}
