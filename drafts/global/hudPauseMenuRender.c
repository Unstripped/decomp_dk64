// hudPauseMenuRender (src/global/ACDC0.c): stage 6: full=105 text=101 reloc=4 shape=6 n=993; the only text diff is a consistent t3<->t4 renaming of ugen's scratch ring from loop 1's body entry to the end (99 lines): the target frees the hoisted &D_807FC7F8[i] temp (t4) before the i*4 index temp (t3) in the loop-1 header, ours the reverse. Everything else matches: list memory-resident via a dead 'if (list == NULL) {}' before the switch, case 0 as 'for (j = 0; j < ((u8 *)tab)[0x2FC]; j++)' with ph read through tab (CSE gives blez v0), case 2 fade loads unk4 first with a dead prologue 'fadeInput0 = hud->unk0' pinning the candidate order (f2/f12), case-3 FAKE removed (end constant lui t8). Parked in src under NON_MATCHING.
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
    s32 cnt;
    u8 framePad[4];

    hud = actor->customState;
    fadeInput0 = hud->unk0; // FAKE: first appearance orders the fade candidates (fadeInput0 -> f2, fadeInput4 -> f12).
    tab = gPlayerInventoryTable;
    sp138 = mapGetHubWorldIndex(gCurrentWorldId, 1);
    list = heapAlloc(0x1F40);
    heapFreeDeferred(list);
    gSPDisplayList(dl++, list);
    ret = dl;
    dl = hudSetupTextState(list);
    for (i = 0; i < 2; i++) {
        it = D_807FC7F0[i];
        if (it != NULL) {
            for (j = 0; j < D_807FC7F8[i]; j++) {
                fa = hud->unk0;
                if ((s8)((HudTextEntry *)((u8 *)it + j * 0x18))->unk10 == 2) {
                    fa += hud->unk4;
                }
                off = ((HudTextEntry *)((u8 *)it + j * 0x18))->unk8;
                y = ((HudTextEntry *)((u8 *)it + j * 0x18))->unkA;
                off = off * 4 + (s32)(fa * ((HudTextEntry *)((u8 *)it + j * 0x18))->unk0);
                y *= 4;
                y += (u16)(s32)(fa * ((HudTextEntry *)((u8 *)it + j * 0x18))->unk4);
                off = (s16)((u32)off + ((HudTextEntry *)((u8 *)it + j * 0x18))->unkC * 4);
                y += ((HudTextEntry *)((u8 *)it + j * 0x18))->unkE * 4;
                y += hud->unkC[i] * 4;
                dl = textDrawStringVtx(dl, 1, off, y, ((HudTextEntry *)((u8 *)it + j * 0x18))->unk11, 1);
            }
        }
    }

    if (list == NULL) {} // FAKE: keeps list in memory
    switch (hud->unk12) {
        case 0:
            ph = ((u8 *)tab)[0x2FC] * 0x34 - 0x34;
            s2 = D_807FCC4B;
            y0 = 0x140;
            y0 = 0xA0 - (s16)((f32)y0 * hud->unk0);
            for (j = 0; j < ((u8 *)tab)[0x2FC]; j++) {
                s32 off;
                f32 fa;
                f32 fc;
                f32 fd;
                f32 fe;
                f32 fh;
                s16 y;
                fb = (f32)(u32)ph;
                off = (j << 10) + gFrameCounter * 200;
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
            }
            gDPPipeSync(dl++);
            y = 0x198;
            ang = (s32)((1.0f - hud->unk0) * 255.0f);
            if (ang < 0) {
                ang = 0;
            }
            if (ang >= 0x100) {
                ang = 0xFF;
            }
            if (hud->unk17 != 3) {
                for (j = 0; j < 3; j++) {
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
                    y += 0x44;
                }
            } else {
                gDPSetPrimColor(dl++, 0, 0, 0xFF, 0xFF, 0xFF, ang);
                dl = hudDrawScaledText(dl, 0x280, 0x198, 0.7f, D_807FC7E0[7]);
                _sprintf(buf, "q %s", D_807FC7E0[16]);
                dl = hudDrawScaledText(dl, 0x280, 0x1E8, 1.0, buf);
                _sprintf(buf, "b %s", D_807FC7E0[17]);
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
                        t0 = i * 5;
                        fb = 180.0f * fa;
                        fa = fa * 3.0f;
                        fc = 32.0f * fa;
                        fc = 480.0f + fc;
                        fd = 6.0f * fa;
                        fe = 30.0f * fa;
                        ff = (f32)((f64)fa * 1.33);
                        for (j = 0; j < 5; j++) {
                            if (angv) {} // FAKE: keep the angle in s2.
                            sa = angv;
                            yy = (s32)(mathSinF(sa) * fb);
                            yy += 0x280;
                            y0 = (s32)(mathCosF(sa) * fb);
                            yy += 0x20;
                            off = j + t0;
                            D_807FC840[off] = (f32)yy - fd;
                            D_807FC868[off] = (f32)(s16)((s16)(fc - (f32)y0) + (s32)actor) - fe; // FAKE: narrow before the row offset to steer conversion temporaries.
                            D_807FC890[off] = ff;
                            if (((s8 *)&D_80750530)[j] != 0) {
                                D_807FC890[off] = (f32)((f64)D_807FC890[off] * 0.75);
                            }
                            angv += 0x333;
                        }
                        gDPPipeSync(dl++);
                    }
                    dl = hudDrawItemLabel(dl, (HudEntry *)hud, i);
                }
                if (hud->unk8[i] != 8) {
                    f32 fc;
                    fd = (hud->unk4 < hud->unk0) ? hud->unk0 : hud->unk4;
                    fc = 780.0f;
                    if ((s32)actor == 0) {
                        fc = fc + fd * 400.0;
                    }
                    j = gPlayerInventoryTable[hud->unk14].unk42[D_80750560[hud->unk8[i]]];
                    dl = hudDrawCountPair(0x2A8, (s32)((f32)(s32)actor + fc), j, 5, dl, 0, 0.8f);
                }
            }
            D_80750538++;
            if (D_80750538 >= 0xE) {
                D_80750538 = 0;
            }
            break;
        case 2:
            for (i = 0; i < 2; i++) {
                off = hud->unkC[i] * 4;
                if (off < 0x3B6 && off >= -0x3B5) {
                    dl = hudDrawItemLabel(dl, (HudEntry *)hud, i);
                }
                cnt = 0;
                for (j = 0; j < 5; j++) {
                    cnt += gPlayerInventoryTable[j].unk42[D_80750560[hud->unk8[i]]];
                }
                if (hud->unk8[i] != 8) {
                    fadeInput4 = hud->unk4;
                    fadeInput0 = hud->unk0;
                    if (fadeInput4 < fadeInput0) {
                        fd = fadeInput0;
                    } else {
                        fd = fadeInput4;
                    }
                    fc = 780.0f;
                    if (off == 0) {
                        fc = fc + fd * 400.0;
                    }
                    dl = hudDrawCountPair(0x2B0, (s32)((f32)off + fc), cnt, 0x19, dl, 0, 0.8f);
                }
            }
            break;
        case 3:
            dl = hudDrawScaledText(hudDrawScaledText(dl, 0x280, 0x74, 0.5f, D_807FC7E0[D_807FC818[D_807FC80C] + 18]), 0x280, 0x3C, 0.65, D_807FC7E0[6]);
            {
                f32 fb;
                fadeInput4 = hud->unk4;
                fadeInput0 = hud->unk0;
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
            break;
    }
    dl->words.w0 = 0xDF000000;
    dl->words.w1 = 0;
    if (D_80750530 == 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
    return ret;
}
