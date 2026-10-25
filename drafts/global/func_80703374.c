// func_80703374 (src/global/103AB0.c): Stage 5: compiled display-list setup reconstruction; parameter shaping and constant materialization remain divergent.
extern s16 D_80744498;
extern s16 D_8074449C;
extern s16 D_807444A0;
extern s16 D_807444A4;

#define WRITE_GFX(pkt, _w0, _w1) { Gfx *_g = (Gfx *)(pkt); _g->words.w0 = (_w0); _g->words.w1 = (_w1); }

Gfx *func_80703374(Gfx *arg0, s32 arg1, s32 arg2, s32 arg3, u8 arg4) {
    if (arg4 != 0) {
        WRITE_GFX(arg0++, 0xD9000000, 0);
        WRITE_GFX(arg0++, 0xD9FFFFFF, 0x200004);
        WRITE_GFX(arg0++, 0xD7000000, 0xFFFFFFFF);
        WRITE_GFX(arg0++, 0xE7000000, 0);
        WRITE_GFX(arg0++, 0xE200001C, 0x504340);
        WRITE_GFX(arg0++, 0xFA000000, ((arg1 & 0xFF) << 0x18) | ((arg2 & 0xFF) << 0x10) | ((arg3 & 0xFF) << 8) | arg4);
        WRITE_GFX(arg0++, 0xE3000A01, 0);
        WRITE_GFX(arg0++, 0xFCFFFFFF, 0xFFFDF6FB);
        WRITE_GFX(arg0++, (((s32)((f32)D_80744498 * 4.0f) & 0xFFF) << 0xC) | 0xED000000 | ((s32)((f32)D_8074449C * 4.0f) & 0xFFF),
                  (((s32)((f32)D_807444A0 * 4.0f) & 0xFFF) << 0xC) | ((s32)((f32)D_807444A4 * 4.0f) & 0xFFF));
        WRITE_GFX(arg0++, ((D_807444A0 & 0x3FF) << 0xE) | 0xF6000000 | ((D_807444A4 & 0x3FF) * 4),
                  ((D_80744498 & 0x3FF) << 0xE) | ((D_8074449C & 0x3FF) * 4));
    }
    WRITE_GFX(arg0++, 0xE7000000, 0);
    return arg0;
}
