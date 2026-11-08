// hudPauseMenuRender (src/global/ACDC0.c): stage 5: full=172 text=167 reloc=2 shape=19 n=993; 890 instructions + 103 relocations, matching the target count, and frame 0x1A0. Whole-file fdiff FAILS (2150). Improved draft only, not a match.
// Matching src still uses GLOBAL_ASM. The FP-register instruction projection matches (GP names ignored, branches excluded). No target bytes or hashes were changed.
// The guarded case-2 do-loop plus its list predicate keep case 1's HUD pointer in a0: incoming at the loop header, reloaded after hudDrawItemLabel and hudDrawCountPair, and reused by the fade maximum. Replacing the case-2 list predicate with a HUD predicate adds a redundant maximum-pointer load; direct field rewrites without this CFG change promote HUD to a saved register.
// The explicit case-1 i*5 value and dead use remove the redundant index reload/move. The angle guard preserves s2. Shared fade-input locals preserve FP allocation in all three maxima. Splitting the case-0 y0 conversion from its subtraction preserves the final signed-half result and improves scratch-register ordering.
// Remaining: coordinate prefix (7 normalized differences, 2 shape); case-0 phase scheduling, text-loop setup/latch scheduling, and b-format string pointer; case-1 counter-lookup load/branch scheduling; and integer scratch-register names. Inspect ugen/as1 records rather than inferring the scratch FIFO from scheduled asm alone.
// Permuter output is only a hint. Preserve multi-statement source lines when preprocessing it; tools/permute.py's current wrapper regex misses normal function openings. The reviewed hints used here are shift factorization and splitting the signed-half phase-coordinate assignment.
typedef struct {
    f32 unk0;
    f32 unk4;
    s16 unk8[2];
    s16 unkC[2];
    s16 unk10;
    s8 unk12;
    u8 pad13;
    s8 unk14;
    u8 pad15[2];
    s8 unk17;
} HudPauseMenuState;

f32 mathCosF(s16);
f32 mathSinF(s16);
s32 mapGetHubWorldIndex(s32, s32);
s32 menuGetTimerFlag(void);
Gfx *hudDrawCountPair(s16, s16, s16, s16, Gfx *, s8, f32);
Gfx *hudDrawItemLabel(Gfx *, HudEntry *, s32);
extern s16 D_807FC992[];
extern u8 D_807FCC4C;
extern s8 D_807FCC4B;
extern s32 gFrameCounter;
extern u8 gCurrentWorldId;
extern s8 D_80750538;
extern s16 D_8075056C[];
extern s8 D_807FC80C;
extern s8 D_807FC818[];
extern f32 D_807FC840[];
extern f32 D_807FC868[];
extern f32 D_807FC890[];

Gfx *hudPauseMenuRender(Gfx *dl, Actor *actor) {
    char buf[0x40];
    HudPauseMenuState *hud;
    s16 j;
    s16 i;
    s16 y;
    s32 off;
    s32 t0;
    HudTextEntry *it;
    HudCountEntry *tab;
    Gfx *ret;
    Gfx *list;
    s32 sp138;
    s16 ang;
    s16 y0;
    s8 s2;
    u8 ph;
    f32 fa;
    f32 fb;
    f32 fc;
    f32 fd;
    f32 fadeInput0;
    f32 fadeInput4;
    u8 framePad[8];

    hud = actor->customState;
    tab = gPlayerInventoryTable;
    sp138 = mapGetHubWorldIndex(gCurrentWorldId, 1);
    list = heapAlloc(0x1F40);
    heapFreeDeferred(list);
    gSPDisplayList(dl++, list);
    ret = dl;
    dl = hudSetupTextState(list);
    for (i = 0; i < 2; i++) {
        it = D_807FC7F0[i];
        if (it != 0) {
            for (j = 0; j < D_807FC7F8[i]; j++) {
                fa = hud->unk0;
                if ((s8)((HudTextEntry *)((u8 *)it + j * 0x18))->unk10 == 2) {
                    fa += hud->unk4;
                }
                off = ((HudTextEntry *)((u8 *)it + j * 0x18))->unk8;
                y = ((HudTextEntry *)((u8 *)it + j * 0x18))->unkA;

                off = (u16)(off * 4);
                off += (s32)(fa * ((HudTextEntry *)((u8 *)it + j * 0x18))->unk0);

                y *= 4;
                y += (s32)(fa * ((HudTextEntry *)((u8 *)it + j * 0x18))->unk4);
                off = (s16)((u32)off + ((HudTextEntry *)((u8 *)it + j * 0x18))->unkC * 4);
                y += ((HudTextEntry *)((u8 *)it + j * 0x18))->unkE * 4;
                y += hud->unkC[i] * 4;
                if (off) {} // FAKE: keep the X coordinate in s0.
if (off) {} // FAKE: keep the X coordinate in s0.

                dl = textDrawStringVtx(dl, 1, off, y, ((HudTextEntry *)((u8 *)it + j * 0x18))->unk11, 1);
            }
        }
    }
    switch (hud->unk12) {
        case 0:
            s2 = D_807FCC4B;
            y0 = 0x140; /* narrow var: keeps (f32)0x140 unfolded */
            y0 = (s32)((f32)y0 * hud->unk0);
            y0 = 0xA0 - y0;
            j = 0; ph = D_807FCC4C * 0x34 - 0x34; if (D_807FCC4C > 0) { fb = (f32)(u32)ph; do { // LAYOUT: preserve the phase conversion schedule.
                    s32 off;
                    f32 fa;
                    f32 fc;
                    f32 fd;
                    f32 fe;
                    f32 fh;
                    s16 y;
                    off = ((j << 9) << 1) + gFrameCounter * 200; // FAKE: reproduce ugen scratch-register ordering.
                    ang = off;
                    fa = mathSinF(ang) * 0.3f + 3.0f;
                    fc = mathSinF(off + 0x800) * 0.3f + 3.0f;
                    fd = mathSinF((off >> 1) + 0x200) * 10.0f;
                    fe = mathSinF(ang);
                    fa = fa * 0.75f;
                    fd = fd * 0.75f;
                    fc = fc * 0.75f;
                    fe = (fe * 0.5f + 0.5f) * 30.0f * 0.75f;
                    gDPPipeSync(dl++);
                    gDPSetPrimColor(dl++, 0, 0, 0xFF, 0xFF, 0xFF, 0x50);
                    y = (s32)((f32)(j * 0x69 + 0x280) + fd - fb);
                    fh = -fc;
                    dl = renderRotatedSprite(dl, 0x5D, 0, 2, 0x30, 0x2A, y, y0 + (s16)(s32)fe, fa, fh, 0, 0.0f);
                    gDPPipeSync(dl++);
                    (dl++)->words.w1 = 0xFFFFFFFF;
                    dl[-1].words.w0 = 0xFA000000;
                    if (s2 > 0) {
                        s32 m;
                        off = s2 - 1;
                        if (off < 3) {
                            m = off;
                        } else {
                            m = 3;
                        }
                        dl = renderRotatedSprite(dl, (u16)(m + 0x5A), 0, 2, 0x30, 0x2A, y, (s32)((f32)y0 + fe), fa, fh, 0, 0.0f);
                    }
                    if (s2 - 4 < 0) {
                        s2 = 0;
                    } else {
                        s2 = s2 - 4;
                    }
                    j++;
                } while (j < ((u8 *)tab)[0x2FC]);
            }
            gDPPipeSync(dl++);
            y = 0x198;
            j = 0;
            ang = (s32)((1.0f - hud->unk0) * 255.0f);
            if (ang < 0) {
                ang = 0;
            }
            if (ang >= 0x100) {
                ang = 0xFF;
            }
            if (hud->unk17 != 3) {
                do {
                    if (j == hud->unk17) {
                        gDPSetPrimColor(dl++, 0, 0, 0xFF, 0xFF, 0xFF, ang);
                    } else {
                        gDPSetPrimColor(dl++, 0, 0, 0xFF, 0xFF, 0xFF, ang >> 1);
                    }
                    if (j == 2 && (sp138 == 7 || (sp138 == 8 && menuGetTimerFlag() != 0 && *(s8 *)D_807505CC == 0))) {
                        j++;
                    }
                    i = j;
                    if (j == 1 && *(s8 *)D_807505CC != 0) {
                        i = 4;
                    }
                    if (i == 2 && *(s8 *)D_807505CC != 0) {
                        i = 5;
                    }
                    dl = hudDrawScaledText(dl, 0x280, y, 0.7f, D_807FC7E0[i]);
                    j++;
                    y += 0x44;
                } while (j < 3);
            } else {
                gDPSetPrimColor(dl++, 0, 0, 0xFF, 0xFF, 0xFF, ang);
                dl = hudDrawScaledText(dl, 0x280, 0x198, 0.7f, D_807FC7E0[7]);
                _sprintf(buf, "q %s", D_807FC7E0[16]);
                dl = hudDrawScaledText(dl, 0x280, 0x1E8, 1.0, buf);
                _sprintf(buf, "b %s", (0, D_807FC7E0)[17]); // FAKE: permuter address-web hint
                dl = hudDrawScaledText(dl, 0x280, 0x238, 1.0, buf);
            }
            break;
        case 1:

            for (i = 0; i < 2; i++) {
                s32 angv;
                actor = (Actor *)(hud->unkC[i] * 4); // FAKE: reuse the consumed parameter to remove off1's stack home.
                angv = -hud->unk10;
                fa = 1.0f - hud->unk0;
                if ((s32)actor < 0x3B6 && (s32)actor >= -0x3B5) {
                    if (fa > 0.05f) {
                        f32 fc;
                        f32 fe;
                        f32 ff;
                        s16 sa;
                        s16 yy;
                t0 = (s32)(s64)(i * 5); // FAKE: retain the row index across the coordinate setup.
                if (t0) {} // FAKE: keep the row index available before the inner loop.
                        fb = 180.0f * fa;
                        fa = fa * 3.0f;
                        fc = 32.0f * fa;
                        if (D_807FC828 == 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                        fd = 6.0f * fa;
                        fe = 30.0f * fa;
                        fc = 480.0f + fc;
                        ff = (f32)((f64)fa * 1.33);
                        j = 0;
                        do {

if (angv) {} // FAKE: keep the angle in s2.
                            sa = angv;
                            yy = (u16)(s32)(mathSinF(sa) * fb) + 0x280; // FAKE: narrow before the offset to steer the conversion temporary.
                            y0 = (s32)(mathCosF(sa) * fb);
                            yy += 0x20;
                            off = j + t0;
                            D_807FC840[off] = (f32)yy - fd;
                            D_807FC868[off] = (f32)(s16)((s16)(fc - (f32)y0) + (s32)actor) - fe; // FAKE: narrow before the row offset to steer conversion temporaries.
                            D_807FC890[off] = ff;
                            if (((s8 *)&D_80750530)[j] != 0) {
                                D_807FC890[off] = (f32)((f64)D_807FC890[off] * 0.75);
                            }
                            j++;
                            angv += 0x333;
                        } while (j < 5);
                        gDPPipeSync(dl++);
                    }
                    dl = hudDrawItemLabel(dl, (HudEntry *)hud, i);
                }
                if (hud->unk8[i] != 8) {
                    
                    
                    f32 fc;
                    it = (HudTextEntry *)((s32)(s64)(s32)hud); // FAKE: separate call-free HUD pointer live range.
                    fadeInput4 = ((HudPauseMenuState *)it)->unk4;
                    fadeInput0 = ((HudPauseMenuState *)it)->unk0;
                    if (D_807FC868 && D_807FC868) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                    fc = 780.0f;
                    if (D_8075056C && D_8075056C) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                    if (fadeInput4 < fadeInput0) {
                        fd = fadeInput0;
                    } else {
                        fd = fadeInput4;
                    }
                    if ((s32)actor == 0) {
                        fc = fc + fd * 400.0;
                    }
                    j = *(s16 *)((u8 *)D_807FC992 + hud->unk14 * 0x5E + D_80750560[hud->unk8[i]] * 2);
                    dl = hudDrawCountPair(0x2A8, (s32)((f32)(s32)actor + fc), j, 5, dl, 0, 0.8f);
                }
            }
            D_80750538++;
            if (D_80750538 >= 0xE) {
                D_80750538 = 0;
            }
            break;
        case 2:
            i = 0;
            if (i < 2) { // FAKE: retain the CFG split that places C1 HUD reloads.
                do {
                if ((list != 0) != 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                off = hud->unkC[i] * 4;
                if (off < 0x3B6 && off >= -0x3B5) {
                    dl = hudDrawItemLabel(dl, (HudEntry *)hud, i);
                }
                t0 = 0;
                for (j = 0; j < 5; j++) {
                    t0 += gPlayerInventoryTable[j].unk42[D_80750560[hud->unk8[i]]];
                }
                if (hud->unk8[i] != 8) {
                    
                    
                    it = (HudTextEntry *)((s32)(s64)(s32)hud); // FAKE: separate call-free HUD pointer live range.
                    fadeInput4 = ((HudPauseMenuState *)it)->unk4;
                    if (D_807FC890 && D_807FC890) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                    fadeInput0 = ((HudPauseMenuState *)it)->unk0;
                    if (D_807FC868 && D_807FC868) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                    fc = 780.0f;
                    if (fadeInput4 < fadeInput0) {
                        fd = fadeInput0;
                    } else {
                        if (list != 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                        fd = fadeInput4;
                    }
                    if (off == 0) {
                        fc = fc + fd * 400.0;
                    }
                    dl = hudDrawCountPair(0x2B0, (s32)((f32)off + fc), t0, 0x19, dl, 0, 0.8f);
                }
                            } while (++i < 2);
            }
            break;
        case 3:
            dl = hudDrawScaledText(hudDrawScaledText(dl, 0x280, 0x74, 0.5f, D_807FC7E0[D_807FC818[D_807FC80C] + 18]), 0x280, 0x3C, 0.65, D_807FC7E0[6]);
            {
                f32 fb;
                    it = (HudTextEntry *)((s32)(s64)(s32)hud); // FAKE: separate call-free HUD pointer live range.
                fadeInput4 = ((HudPauseMenuState *)it)->unk4;
                fadeInput0 = ((HudPauseMenuState *)it)->unk0;
                if (fadeInput4 < fadeInput0) {
                    fc = fadeInput0;
                } else {
                    fc = fadeInput4;
                }
                fb = (1.0f - fc) * 0.65f;
                if (fb < 0.01f) {
                    fb = 0.01f;
                }
                dl = hudDrawCountPair(0x280, 0x33C, (&D_807FC828)[D_807FC818[D_807FC80C]], D_8075056C[D_807FC818[D_807FC80C]], dl, 1, fb);
            }
            if (((!i) && (!i)) && (!i)) {} // FAKE: steer the index candidate lifetime.
            break;
    }
    dl->words.w0 = 0xDF000000;
    dl->words.w1 = 0;
    if (D_80750530 == 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
    return ret;
}
