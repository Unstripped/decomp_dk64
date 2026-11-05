// menuRenderOptionDescription (src/menu/E550.c): stage 4 improved, Base05eae3cc2edbb5a497074c2a4825b276d546c9a2. Corrected full=66 text=66 reloc=0 shape=13 n=417/417 frame232. IMPORTANT scorer boundary bug: D_80032F48 is a global alias on the final jr-ra delay slot (addiu sp,sp,232); deadsweep/as1probe stop at its objdump header and omit the target delay slot. Their raw target n416 and raw full67/shape14 are truncated; restoring the real target delay slot gives full66/shape13 with correct n417. Nominal prior draft full85/n415 was two instructions short against complete target. New levers: y=0 and do on one source line removes an as1 scheduling barrier (as1 scan proof reproduced in C); arg1=&off plus first-call dereference makes off addressable and spills it at212(sp); duplicate D_800339D0 dead test fixes post-loop saved-register rotation to width-address=s1, font-height=s2, first-string=s3; fresh Gfx* textDl for first hudDrawScaledText return improves final argument scheduling. Keeps prior yo reuse, off declaration -20 and four old dead tests removed. Remaining: loop t5/ra/s1 cycle, alpha spill76 vs target96, x-loop andi vs move, graphics-temporary v0/v1 vs targett1/t2, ring offsets after text x conversion, and off v1 vs targett0. Tried parameter/real-local scaling, nested narrow casts, scalar/array/union storage, scalar coordinate sharing and frame-preserving endpoint layouts, signed/unsigned Gfx operands, endpoint ordering, zero-valued spC0 terms; no further gain. Actual ABI discrepancies textGetFontHeight u8(s16), texCacheFindOrLoad arg u16, textDrawStringVtx font s16/flagsu8: 30 corrected-prototype combinations left code unchanged, no header edits. uopt level5 traced. as1 scan rounds2 (3949 edits/round) found the same-line route; remaining apparent lower-count deletions invalid. deadsweep rounds2 improved raw74 to68, subsequent 752 variants on fresh-return best found none. Permuter -j2 --seconds600,14969 iterations: bestscore1012 remeasures rawfull78/shape26/n417 and rejected; natural fresh-return-local derivative is retained instead. Plain C fdiff: FAILED: Section .text content mismatch (built: 2560 bytes, expected: 2560 bytes); no relocation mismatch. Default parked fdiff: OK. Copy .scratch/Matcher4-menuRenderOptionDescription/E550.c; merge improved park only, not a match.
extern Gfx D_1000118[];
extern Mtx D_20000C0;
extern s16 D_80744490;
extern s16 D_80744494;
extern u8 D_8074450C;
char *textTableGetString(s32, s32, s32);
s32 textGetFontHeight(s32);
s32 texCacheFindOrLoad(s32);
s32 textGetStringWidth(s32, char *);
Gfx *textDrawStringVtx(Gfx *, s32, s16, s16, char *, s32);
Gfx *hudDrawScaledText(Gfx *, s16, s16, f32, char *);

Gfx *menuRenderOptionDescription(Gfx *dl, void *arg1) {
    u32 tex;
    s32 alpha;
    s32 y;
    s32 xo;
    s32 off;
    u16 x;
    s16 xx;
    char *spCC;
    char *spC8;
    char *spC4;
    s32 spC0;
    s32 yo;
    s32 yyo;
    s32 yy;
    Gfx *textDl;

    spCC = textTableGetString(0xD, 0, 1);
    spC8 = textTableGetString(0xD, 1, 1);
    spC4 = textTableGetString(0xD, 2, 1);
    spC0 = textGetFontHeight(1);
    gDPPipeSync(dl++);
    gSPDisplayList(dl++, D_1000118);
    gSPSetOtherMode(dl++, G_SETOTHERMODE_L, 3, 29, 0x0F0A4000);
    gDPSetCombine(dl++, 0x119623, 0xFF2FFFFF);
    gSPMatrix(dl++, &D_20000C0, G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH);
    alpha = D_800339D0 * 15;
    if (alpha > 0xFF) {
        alpha = 0xFF;
    }
    gDPSetPrimColor(dl++, 0, 0, alpha, alpha, alpha, 0xFF);
    gSPSetOtherMode(dl++, G_SETOTHERMODE_H, 12, 2, 0);
    gSPSetOtherMode(dl++, G_SETOTHERMODE_H, 19, 1, 0);
    tex = texCacheFindOrLoad(0xB0);
    yo = (s32)(((f32)D_80744494 - 82.0f) * 0.5f);
    y = 0; do {  // FAKE: one source line removes a scheduling barrier before the loop.
        xo = (s32)(((f32)D_80744490 - 204.0f) * 0.5f);
        yy = y + 0x29;
        yyo = yo + 0x29;
        x = 0;
        if (x && x) {}  // FAKE: deadsweep: steers uopt candidate priority
        do {
            gDPLoadTextureTile_4b(dl++, tex, G_IM_FMT_I, 204, 82, x, y, x + 0x66, yy, 0,
                                  G_TX_CLAMP, G_TX_CLAMP, 0, 0, 0, 0);
            gSPTextureRectangle(dl++, xo << 2, yo << 2, (xo + 0x66) << 2, yyo << 2, 0, x << 5, y << 5, 0x400, 0x400);
            x += 0x66;
            xo += 0x66;
        } while (x != 0xCC);
        y += 0x29;
        yo += 0x29;
    } while (y != 0x52);
    gSPSetOtherMode(dl++, G_SETOTHERMODE_H, 12, 2, 0x2000);
    gSPSetOtherMode(dl++, G_SETOTHERMODE_H, 19, 1, 0x80000);
    x = (s32)((f32)(D_80744490 - textGetStringWidth(1, spCC)) * 0.5f);
    yo = (s32)((((f32)D_80744494 - 82.0f) * 0.5f) - (f32)spC0);
    gDPSetPrimColor(dl++, 0, 0, 0xFF, 0xFF, 0xFF, alpha);
    if (D_800339D0 && D_800339D0) {}  // FAKE: duplicate reference steers the post-loop register allocation.
    if (D_800339D0 && D_800339D0) {}  // FAKE: deadsweep/hill-climb: steers uopt candidate priority
    gSPSetOtherMode(dl++, G_SETOTHERMODE_L, 3, 29, 0x504240);
    gDPSetCombine(dl++, 0xFF97FF, 0xFF2CFE7F);
    dl = textDrawStringVtx(dl, 1, (s16)(x * 4), (s16)(yo * 4), spCC, 0);
    xx = (s32)((f32)D_80744490 * 0.5f) * 4;
    arg1 = &off;  // FAKE: address-taken offset retains its stack home across the first text draw.
    off = D_8074450C * 0xC8;
    xx = xx | 0;  // FAKE: deadsweep/hill-climb: steers uopt candidate priority
    textDl = hudDrawScaledText(dl, xx, (s16)(*(s32 *)arg1 * 4), .5f, spC8);  // FAKE: .5f spells a separate constant web (argument via lui a3, no mfc1).
    return hudDrawScaledText(textDl, xx, (s16)((s32)((f64)off + (f64)spC0 * 0.5) * 4), .5f, spC4);
}
