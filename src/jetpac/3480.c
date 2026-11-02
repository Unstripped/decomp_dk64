#include "common.h"

typedef struct {
    void *frame;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    s32 unk10;
    s32 unk14;
} JetpacSprite;

typedef struct {
    JetpacSprite *sprites[2];
    f32 unk8;
    f32 unkC;
    f32 unk10;
    f32 unk14;
    u8 color[4];
    s32 unk1C;
    s32 unk20;
    s32 unk24;
    s32 unk28;
    s32 unk2C;
    s32 unk30;
    s32 unk34;
    s32 unk38;
    s32 unk3C;
    s32 unk40;
    s32 unk44;
    void (*unk48)(void *, s32);
} JetpacItem;

typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    s32 unk10;
    JetpacItem items[4];
    s32 unk144;
    JetpacItem bonus;
} JetpacPlayer;

typedef struct {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    u8 color[4];
    u8 pad14[8];
    s32 unk1C;
    s32 unk20;
    s32 unk24;
    s32 unk28;
    u8 pad2C[4];
    s32 unk30;
} JetpacLedge;

typedef struct {
    u8 pad0[0x1C];
    JetpacPlayer players[2];
    s32 active_player;
    u8 pad348[0x350 - 0x348];
    JetpacLedge ledges[4];
    u8 pad420[0x78C - 0x420];
    s32 unk78C;
} JetpacGlobal;

extern JetpacGlobal jetpacGame;

f32 jetpacRandFloat(void);
s32 jetpacCheckAabbOverlapWrapped(f32, f32, f32, f32, f32, f32, f32, f32);
void jetpacGridAddTiledSprite(void *, s32, s32, void *, s32);
extern s32 D_8002DC68[];
s32 jetpacRandSpawnX(void) {
    return (s32)((jetpacRandFloat() * 200.0f) + 90.0f);
}

s32 jetpacRandItemX(void) {
    return D_8002DC68[(s32)(jetpacRandFloat() * 13.0f) % 13];
}

s32 jetpacItemOverlapsBox(JetpacItem *arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, s32 arg5) {
    f32 fa0;
    f32 fa1;

    fa0 = arg0->unk8;
    fa1 = arg0->unkC;
    if (arg0->unk38 == 1) {
        return 0;
    }

    if (arg5 == 0) {
        fa0 += (f32)arg0->unk24;
        fa1 += (f32)arg0->unk28;
    }

    if (arg0->unk1C >= 2) {
        if (jetpacCheckAabbOverlapWrapped(fa0, fa1, arg0->unk8 + (f32)arg0->unk2C, arg0->unkC + (f32)arg0->unk30, arg1, arg2, arg3, arg4)) {
            return 1;
        }
    }

    return 0;
}

extern JetpacSprite D_8002D1A0[];
extern JetpacSprite D_8002D230[];
extern JetpacItem D_8002DC9C;
void jetpacSetRocketSpriteFrames(JetpacPlayer *arg0);

void jetpacInitRocketParts(JetpacPlayer *arg0) {
    s32 j;
    JetpacItem sp38 = D_8002DC9C;
    s32 i;

    for (i = 0; i < 3; i++) {
        arg0->items[i] = sp38;
        for (j = 0; j < 2; j++) {
            arg0->items[i].sprites[j] = &D_8002D1A0[i * 2 + j];
        }
    }

    jetpacSetRocketSpriteFrames(arg0);
    arg0->unkC = 0;
    arg0->items[2].unk8 = 168.0f;
    arg0->items[2].unkC = 168.0f;
    arg0->items[0].unk8 = 48.0f;
    arg0->items[0].unkC = 56.0f;
    arg0->items[1].unk8 = 128.0f;
    arg0->items[1].unkC = 80.0f;
}




#ifdef NON_MATCHING
s32 jetpacCheckLedgeCollision(f32, f32, f32, f32, s32);
s32 jetpacIsOverRocket(f32);
extern s32 D_8002F064;
extern f32 jetpacPlayer;
extern f32 D_8002F054;
extern f32 D_8002F058;
extern f32 D_8002F05C;
extern s32 D_8002F06C;
extern s32 D_8002F070;
extern s32 D_8002F074;
extern s32 D_8002F078;
void flagSet(s32, s32, s32);
void jetpacPlaySound(s32);
void jetpacSpawnBonusItem(JetpacPlayer *);
void jetpacSpawnFuelPod();
#endif

#ifdef NON_MATCHING
void jetpacRocketItemUpdate(JetpacItem *arg0) {
    JetpacPlayer *inner = &jetpacGame.players[jetpacGame.active_player];
    f32 *new_var;
    f32 *new_var2;
    s32 *new_var3;
    s32 new_var4;

    if (arg0->unk1C == 0) {
        return;
    }
    if (inner->unkC >= 8) {
        return;
    }
    if (arg0->unk34 < 0x14) {
        arg0->unk34 = arg0->unk34 + 1;
        return;
    }
    if (arg0->unk1C == 1) {
        arg0->unk1C = 2;
    }
    new_var = &jetpacPlayer;
    new_var2 = &D_8002F054;
    new_var3 = &D_8002F06C;
    if (arg0->unk38 == 0) {
        if (arg0->unk14 > 0.0f && D_8002F064 != 4) {
            f32 x = arg0->unk8;
            s32 hit = jetpacCheckLedgeCollision((f32)arg0->unk24 + x + arg0->unk10, (f32)arg0->unk28 + arg0->unkC + arg0->unk14,
                                                (f32)arg0->unk2C + x + arg0->unk10, (f32)arg0->unk30 + arg0->unkC + arg0->unk14, 0);
            if (hit >= 0) {
                arg0->unkC = jetpacGame.ledges[hit].unk4 - 16.0f;
                arg0->unk14 = 0.0f;
            } else {
                arg0->unkC = arg0->unkC + arg0->unk14;
            }
        }
        if (D_8002F064 == 3) {
            if (jetpacCheckAabbOverlapWrapped(arg0->unk8 + (f32)arg0->unk24, arg0->unkC + (f32)arg0->unk28, arg0->unk8 + (f32)arg0->unk2C, arg0->unkC + (f32)arg0->unk30,
                              (*new_var) + (f32)D_8002F06C, (*new_var2) + (f32)D_8002F070, (*new_var) + (f32)D_8002F074,
                              (*new_var2) + (f32)D_8002F078)) {
                arg0->unk38 = 1;
                inner->unk4 += arg0->unk3C;
                jetpacPlaySound(4);
            }
        }
    }
    if (arg0->unk38 == 1) {
        if (D_8002F064 == 4) {
            arg0->unk38 = 0;
            arg0->unk14 = 0.8f;
        } else {
            new_var4 = *new_var3;
            arg0->unk8 = (jetpacPlayer - (f32)2 * D_8002F058 + (f32)new_var4) + (D_8002F074 - D_8002F06C - arg0->unk2C + arg0->unk24) * 0.5;
            arg0->unkC = D_8002F054 - D_8002F05C + (f32)D_8002F078 - (f32)arg0->unk30;
            if (jetpacIsOverRocket(arg0->unk8)) {
                arg0->unk8 = 168.0f;
                arg0->unk14 = 0.8f;
                arg0->unk38 = 2;
            }
        }
    }
    if (arg0->unk38 == 2) {
        arg0->unkC = arg0->unkC + arg0->unk14;
        if (inner->unkC < 2) {
            f32 lim = (f32)(0x98 - (inner->unkC << 4));
            if (lim <= arg0->unkC) {
                arg0->unkC = lim;
                inner->unkC = inner->unkC + 1;
                jetpacPlaySound(2);
                if (inner->unkC < 2) {
                    inner->unk10 = inner->unk10 - 1;
                } else {
                    jetpacSpawnFuelPod(inner);
                }
            }
        } else if (168.0f <= arg0->unkC) {
            inner->unkC = inner->unkC + 1;
            jetpacPlaySound(2);
            if (inner->unkC < 8) {
                jetpacSpawnFuelPod(inner);
            } else {
                arg0->unk1C = 0;
            }
        }
    }
}
#else

#pragma GLOBAL_ASM("asm/jetpac/nonmatchings/3480/jetpacRocketItemUpdate.s")
#endif


typedef struct {
    u8 r;
    u8 g;
    u8 b;
    u8 a;
} J3Color;

extern J3Color D_8002DCE8;
extern s32 D_8002F3C0;
f32 jetpacRoundFloat(f32);

void jetpacDrawItem(JetpacItem *arg0, s32 arg1) {
    s32 x;
    s32 y;
    JetpacPlayer *inner;
    J3Color sp58;
    s32 i;

    sp58 = D_8002DCE8;
    inner = &jetpacGame.players[jetpacGame.active_player];
    if (D_8002F3C0) { // FAKE: empty guard steers regalloc
    }
    if (arg0->unk1C >= 2) {
        x = (s32)arg0->unk8;
        y = (s32)jetpacRoundFloat(arg0->unkC);
        if (arg1 < 3) {
            for (i = 0; i < 2; i++, y += 8) {
                if ((inner->unkC < 8 && inner->unkC + arg1 * 2 + i >= 8) || (inner->unkC == 8 && (D_8002F3C0 & 0x10))) {
                    sp58.g = 0;
                }
                if (arg0->sprites[i] != NULL) {
                    jetpacGridAddTiledSprite(arg0->sprites[i], x, y, &sp58, arg0->unk20);
                }
            }
        } else {
            jetpacGridAddTiledSprite(arg0->sprites[0], x, y, arg0->color, arg0->unk20);
        }
    }
}


s32 flagGet(s32, s32);
extern u8 D_8002F3C8;
extern JetpacSprite D_8002D968[];
extern JetpacItem D_8002DCEC;

void jetpacSpawnBonusItem(JetpacPlayer *arg0) {
    JetpacItem sp24 = D_8002DCEC;
    JetpacItem *item;
    s32 count = 5;

    if (D_8002F3C8 != 0 && arg0->unk4 >= 5000 && flagGet(0x17B, 0) == 0 && flagGet(0x62, 2) == 0) {
        count = 6;
        sp24.unk40 = count;
    } else {
        sp24.unk40 = (s32)(jetpacRandFloat() * count) + 1;
    }

    item = &arg0->bonus;
    sp24.sprites[0] = &D_8002D968[sp24.unk40];
    *item = sp24;
    item->unk8 = (f32)jetpacRandItemX();
    arg0->unk144 = jetpacRandSpawnX();
}


#ifdef NON_MATCHING
void jetpacBonusItemUpdate(JetpacItem *arg0) {
    JetpacPlayer *inner = &jetpacGame.players[jetpacGame.active_player];
    s32 v;
    s32 v1;
    s32 v34;
    f32 *new_var;
    f32 *new_var2;

    if (inner->unkC == 0) {
        return;
    }
    if (inner->unk144 == 2) {} // FAKE: empty block boundary + const-2 web in the compare block (as1 delay slot / li hoist)
    if (arg0->unk34 < inner->unk144) {
        arg0->unk34 = arg0->unk34 + 1;
        return;
    }
    if (inner->unk4 && inner->unk4) {} // FAKE: steers uopt candidate priority
    if (arg0->unk1C == 1) {
        arg0->unk1C = 2;
    }
    if (inner->unk4) {} // FAKE: steers uopt candidate priority
    new_var = &jetpacPlayer;
    new_var2 = &D_8002F054;
    if (arg0->unk38 == 0) {
        if (arg0->unk14 > 0.0f) {
            f32 x = arg0->unk8;
            s32 hit = jetpacCheckLedgeCollision((f32)arg0->unk24 + x + arg0->unk10, (f32)arg0->unk28 + arg0->unkC + arg0->unk14,
                                                (f32)arg0->unk2C + x + arg0->unk10, (f32)arg0->unk30 + arg0->unkC + arg0->unk14, 0);
            if (hit >= 0) {
                arg0->unkC = jetpacGame.ledges[hit].unk4 - 16.0f;
                arg0->unk14 = 0.0f;
            } else {
                arg0->unkC = arg0->unkC + arg0->unk14;
            }
        }
        if (jetpacGame.unk78C == 2U && D_8002F064 == 3) {
            if (jetpacCheckAabbOverlapWrapped(arg0->unk8 + (f32)arg0->unk24, arg0->unkC + (f32)arg0->unk28, arg0->unk8 + (f32)arg0->unk2C, arg0->unkC + (f32)arg0->unk30,
                              (*new_var) + (f32)D_8002F06C, (*new_var2) + (f32)D_8002F070, (*new_var) + (f32)D_8002F074,
                              (*new_var2) + (f32)D_8002F078)) {
                if (arg0->unk40 == 6) {
                    flagSet(0x62, 1, 2);
                }
                inner->unk4 += arg0->unk3C;
                jetpacPlaySound(3);
                jetpacSpawnBonusItem(inner);
                return;
            }
        }
    }

    switch (arg0->unk40) {
    case 6:
        arg0->unk34++;
        v = arg0->unk34 - inner->unk144;
        if (v >= 0x97) {
            jetpacSpawnBonusItem(inner);
            return;
        }
        v = v % 24;
        if (v < 12) {
            arg0->color[2] = 0xFF;
            arg0->color[0] = 0;
            arg0->color[1] = 0;
        } else if (v < 24) {
            arg0->color[0] = 0xFF;
            arg0->color[1] = 0xFF;
            arg0->color[2] = 0;
        }
        break;
    case 1:
        arg0->unk34++;
        v1 = arg0->unk34 - inner->unk144;
        if (v1 >= 0x1C) {
            v1 -= 0x1C;
            arg0->unk34 = inner->unk144;
        }
        if (v1 < 0x1C) {
            v1 = v1 / 4 + 1;
            if (v1 & 1) {
                arg0->color[2] = 0xFF;
            } else {
                arg0->color[2] = 0;
            }
            if (v1 & 2) {
                arg0->color[0] = 0xFF;
            } else {
                arg0->color[0] = 0;
            }
            if (v1 & 4) {
                arg0->color[1] = 0xFF;
            } else {
                arg0->color[1] = 0;
            }
        }
        break;
    case 2:
        arg0->color[0] = 0xFF;
        arg0->color[1] = 0xFF;
        arg0->color[2] = 0;
        break;
    case 5:
        arg0->color[1] = 0xFF;
        arg0->color[0] = 0;
        arg0->color[2] = 0;
        break;
    case 3:
    case 4:
        arg0->unk34++;
        if (arg0->unk34 && arg0->unk34) {} // FAKE: raises the unk34 candidate priority (base address -> v1)
        v34 = arg0->unk34 - inner->unk144;
        if (v34 >= 0x18) {
            v34 -= 0x18;
            arg0->unk34 = inner->unk144;
        }
        if (v34 < 12) {
            arg0->color[0] = 0;
            arg0->color[1] = 0;
            arg0->color[2] = 0;
        } else if (v34 < 24) {
            arg0->color[0] = 0;
            arg0->color[1] = 0xFF;
            arg0->color[2] = 0xFF;
        }
        break;
    }
}
#else

#pragma GLOBAL_ASM("asm/jetpac/nonmatchings/3480/jetpacBonusItemUpdate.s")
#endif



extern JetpacItem D_8002DD38;

void jetpacSpawnFuelPod(JetpacPlayer *arg0) {
    JetpacItem sp1C = D_8002DD38;
    sp1C.unk8 = (f32)jetpacRandItemX();
    arg0->items[3] = sp1C;
    arg0->unk10 = 3;
}


s32 jetpacBoxOverlapsItems(f32 arg0, f32 arg1, f32 arg2, f32 arg3) {
    JetpacPlayer *inner = &jetpacGame.players[jetpacGame.active_player];
    s32 unkC = inner->unkC;
    s32 i;
    JetpacItem *item;

    if (unkC < 2) {
        item = inner->items;
        i = 0;
        if (2 - unkC > 0) {
            do {
                if (jetpacItemOverlapsBox(item, arg0, arg1, arg2, arg3, 1)) {
                    return 1;
                }
                i++;
                item++;
            } while (i < 2 - inner->unkC);
        }
    }

    if (jetpacItemOverlapsBox(&inner->items[3], arg0, arg1, arg2, arg3, 0)) {
        return 1;
    }
    if (jetpacItemOverlapsBox(&inner->bonus, arg0, arg1, arg2, arg3, 0)) {
        return 1;
    }

    return 0;
}
void jetpacItemsUpdate(void) {
    JetpacPlayer *player = &jetpacGame.players[jetpacGame.active_player];
    JetpacItem *item = player->items;
    s32 i = 0;
    s32 count = 4;

    do {
        if (item->unk1C >= 2 && item->unk48 != NULL) {
            item->unk48(item, i);
        }
        i++;
        item++;
    } while (i != count);
}
void func_800285DC(void) {
    JetpacPlayer *inner = &jetpacGame.players[jetpacGame.active_player];
    inner->bonus.unk48(&inner->bonus, 5);
}

void jetpacPlaceRocketOnPad(void) {
    JetpacPlayer *inner = &jetpacGame.players[jetpacGame.active_player];
    JetpacItem *item = inner->items;
    s32 i;

    inner->unkC = 8;
    for (i = 0; i < 3; i++, item++) {
        item->unk8 = 168.0f;
        item->unkC = (f32)(i * 16) + 136.0f;
    }
}

extern s32 D_80770DF8[];
void jetpacPlaySound(s32);
void jetpacSetSoundPitch(s32, f32);
void jetpacStopSound(s32);
void jetpacSetState(s32);
void jetpacStartStage(void);

void jetpacUpdateRocketFlight(void) {
    s32 i;
    JetpacItem *item;
    f32 spd;
    f32 y;
    f32 t;

    item = jetpacGame.players[jetpacGame.active_player].items;

    y = item->unkC; t = (y - -8.0f) / 144.0f; t = (t < 0.0f) ? 0.0f : ((t > 1.0f) ? 1.0f : t);
    if (jetpacGame.unk78C == 1) {
        if (D_80770DF8[1] == 0) {
            jetpacPlaySound(1);
        }
        t = t * 0.059466f;
        t = 1.0f - t;
        jetpacSetSoundPitch(1, t);
        y = item->unkC;
        if (y >= 136.0f) {
            for (i = 0; i < 3; i++, item++) {
                item->unk8 = 168.0f;
                item->unkC = (f32)(i * 16) + 136.0f;
            }
            jetpacStopSound(1);
            jetpacSetState(2);
            return;
        }
        spd = 0.4f;
    } else if (jetpacGame.unk78C == 4) {
        if (D_80770DF8[0] == 0) {
            jetpacPlaySound(0);
        }
        t = 1.0f - t;
        t = t * 0.059466f;
        t = t + 1.0f;
        jetpacSetSoundPitch(0, t);
        y = item->unkC;
        if (y < -8.0f) {
            jetpacStopSound(0);
            jetpacStartStage();
            return;
        }
        spd = -0.4f;
    }

    t = y + spd;
    for (i = 0; i < 3; i++) {
        item->unkC = t;
        t += 16.0f;
        if (!t) { // FAKE: empty guard steers regalloc
        }
        item++;
    }
}


void jetpacPlaceRocketAboveScreen(void) {
    JetpacPlayer *inner = &jetpacGame.players[jetpacGame.active_player];
    JetpacItem *item = inner->items;
    s32 i;

    inner->unkC = 2;
    for (i = 0; i < 3; i++, item++) {
        item->unk8 = 168.0f;
        item->unkC = (f32)(i * 16) + -8.0f;
    }
}

extern s32 D_8002DD88;
typedef struct {
    s32 v;
} J3Word;
extern JetpacSprite D_8002DC38[];
void func_800289EC(void) {
    JetpacItem *item;
    s32 pad;
    J3Word sp44;
    s32 i;

    item = jetpacGame.players[jetpacGame.active_player].items;
    sp44 = *(J3Word *)&D_8002DD88;
    if (116.0f > item->unkC) {
        s32 mod = ((s32)item->unkC / 3) % 2;
        s32 idx = (mod > 0) ? mod : -mod;

        jetpacGridAddTiledSprite(&D_8002DC38[idx], (s32)item->unk8, (s32)((item->unkC + 48.0f) + 4.0f), &sp44, 0);
    }

    i = 0;
    do {
        item->unk48(item, i);
        i++;
        item++;
    } while (i != 3);
}

extern void *D_8002D190[];

void jetpacSetRocketSpriteFrames(JetpacPlayer *arg0) {
    s32 x = arg0->unk0 / 4;
    s32 i;

    for (i = 0; i < 6; i++) {
        D_8002D1A0[i].frame = D_8002D190[x % 4];
    }
}

void jetpacInitLedge(JetpacLedge *arg0, s32 arg1, s32 arg2, s32 arg3, u8 arg4, u8 arg5, u8 arg6) {
    arg0->unk30 = arg3;
    arg0->unk8 = 0.0f;
    arg0->unkC = 0.0f;
    arg0->unk0 = (f32)arg1;
    arg0->unk4 = (f32)arg2;
    arg0->color[0] = arg4;
    arg0->color[1] = arg5;
    arg0->color[2] = arg6;
    arg0->color[3] = 0xFF;
    arg0->unk20 = arg2;
    arg0->unk1C = arg1;
    arg0->unk28 = (arg0->unk24 = (arg3 * 8) + arg1 + 16, arg2 + 12);
}
extern JetpacLedge jetpacLedges[];
extern JetpacLedge D_8002EFB4[];
extern JetpacLedge D_8002EFE8[];
extern JetpacLedge D_8002F01C[];

void jetpacInitLedges(void) {
    jetpacInitLedge(jetpacLedges, 0xC0, 0x30, 4, 0, 0xBE, 0);
    jetpacInitLedge(D_8002EFB4, 0x20, 0x48, 4, 0, 0xBE, 0);
    jetpacInitLedge(D_8002EFE8, 0x78, 0x60, 2, 0, 0xBE, 0);
    jetpacInitLedge(D_8002F01C, 0, 0xB8, 0x1E, 0xBE, 0xBE, 0);
}
s32 jetpacCheckLedgeCollision(f32 arg0, f32 arg1, f32 arg2, f32 arg3, s32 arg4) {
    JetpacLedge *ledge = jetpacLedges;
    s32 i;

    for (i = 0; i < 4; i++, ledge++) {
        f32 fv0 = ledge->unk28;
        if (arg4 == 0) {
            fv0 -= 4.0f;
        }
        if (jetpacCheckAabbOverlapWrapped(arg0, arg1, arg2, arg3, ledge->unk1C, ledge->unk20, ledge->unk24, fv0)) {
            return i;
        }
    }
    return -1;
}

s32 jetpacCheckLedgeEdge(s32 arg0, s32 arg1, s32 arg2) {
    JetpacLedge *l = jetpacGame.ledges + arg0;

    if (arg1 < l->unk1C) {
        if (arg2 < l->unk1C) {
            return -2;
        }
        return -1;
    }
    if (l->unk24 < arg2) {
        if (l->unk24 < arg1) {
            return 2;
        }
        return 1;
    }
    return 0;
}


void jetpacGridAddTiledSprite(void *, s32, s32, void *, s32);
extern void *D_8002DE68;
extern void *D_8002DE80;
extern void *D_8002DE98;
extern u8 D_8002EF90[];

void jetpacDrawLedges(void) {
    s32 i;
    s32 j;
    s32 x;
    s32 y;
    JetpacLedge *l;

    for (i = 0; i < 4; i++) {
        x = (s32)jetpacGame.ledges[i].unk0;
        y = (s32)jetpacGame.ledges[i].unk4;
        l = &jetpacLedges[i];
        jetpacGridAddTiledSprite(&D_8002DE68, x, y, &D_8002EF90[i * 0x34], 0);
        x += 8;
        for (j = 0; j < l->unk30; j++) {
            jetpacGridAddTiledSprite(&D_8002DE80, x, y, D_8002EF90 + i * 0x34, 0);
            x += 8;
        }
        jetpacGridAddTiledSprite(&D_8002DE98, x, y, D_8002EF90 + i * 0x34, 0);
    }
}

