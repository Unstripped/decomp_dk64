#include "common.h"

void *heapAlloc(s32);
void heapClearBlock(void *);
struct RaceUnknownActor;
struct RaceStruct3;
typedef struct Struct806C7C94 {
    u8 pad0[4];
    s16 unk4;
    s16 unk6;
    s16 unk8;
    s16 unkA;
} Struct806C7C94;

typedef struct RacePair {
    struct RaceUnknownActor *unk0;
    struct RaceStruct3 *unk4;
} RacePair;

typedef struct RaceUnknown174 {
    u8 unk0;
    char pad1;
    s16 unk2;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    s16 unk14;
    s16 unk16;
    s16 unk18;
    s16 unk1A;
    u16 unk1C;
    u8 unk1E;
    char pad1F[1];
    RacePair *unk20;
    u8 unk24;
    u8 unk25;
    u8 unk26;
    u8 unk27;
    u8 unk28;
    char pad29;
    u8 unk2A;
    char pad2B;
    void *unk2C;
    struct RaceUnknownActor *unk30;
    char pad34[2];
    u8 unk36;
    char pad37[0xD];
    u8 unk44;
    char pad45[3];
    Struct806C7C94 *unk48;
    char pad4C[0x88 - 0x4C];
    struct RaceUnknownActor *unk88;
} RaceUnknown174;

typedef struct Struct_Player {
    char pad0[4];
    struct RaceUnknownActor *unk4;
    char pad8[0x2F0 - 8];
} Struct_Player;
extern Struct_Player *gPlayerSlots;

typedef struct RaceStruct3 {
    char pad0[0x14];
    f32 unk14;
    f32 unk18;
    f32 unk1C;
    char pad20[0x26 - 0x20];
    u8 unk26;
    u8 unk27;
    u8 unk28;
    char pad29[0x34 - 0x29];
    u8 unk34;
    u8 unk35;
    u8 unk36;
    s8 unk37;
    char pad38[2];
    u16 unk3A;
    s16 unk3C;
    char pad3E[2];
    f32 unk40;
    char pad44[0x45 - 0x44];
    u8 unk45;
    u8 unk46;
    char pad47[1];
    s32 unk48;
} RaceStruct3;

typedef struct RaceSub4 {
    char pad0[0x4];
    f32 unk4;
    char pad8[0x34 - 0x8];
    f32 unk34[3];
} RaceSub4;

typedef struct RaceUnknownActor {
    char pad0[0x4];
    RaceSub4 *unk4;
    char pad8[0xF - 0x8];
    u8 unkF;
    u8 unk10;
    char pad11[0x58 - 0x11];
    s32 unk58;
    char pad5C[0x60 - 0x5C];
    u32 unk60;
    char pad64[0x6A - 0x64];
    u16 unk6A;
    u16 unk6C;
    char pad6E[0x7C - 0x6E];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
    char pad88[0xAC - 0x88];
    f32 unkAC;
    char padB0[0xB8 - 0xB0];
    f32 unkB8;
    char padBC[0xEE - 0xBC];
    s16 unkEE;
    char padF0[0x154 - 0xF0];
    u8 unk154;
    u8 unk155;
    char pad156[0x174 - 0x156];
    RaceUnknown174 *unk174;
    RaceUnknown174 *unk178;
    s32 *unk17C;
} RaceUnknownActor;
typedef struct RaceUnknownC {
    char pad0[0xC];
    RaceUnknownActor *unkC;
} RaceUnknownC;
typedef struct RaceUnknownDCF0 {
    char pad0[0x1C];
    RaceUnknownActor *unk1C[2];
} RaceUnknownDCF0;
typedef struct Struct_807FD63A {
    u16 unk0;
    char pad2[0x32];
} Struct_807FD63A;
extern Struct_807FD63A D_807FD63A[];




void func_8002BBD0(RaceUnknownActor *actor, s32 count) {
    RaceUnknown174 *race174;
    void *allocated;

    race174 = actor->unk174;
    allocated = heapAlloc(count * 8);
    race174->unk20 = allocated;
    heapClearBlock(allocated);
    race174->unk1E = count;
    race174->unk1C = 0xFFFF;
    actor->unk154 = 0;
}

u16 *raceGetRoute(u8);
void func_8002F36C(void *, void *);
s32 cameraFindViewportEntry(u8);
#define RaceE3 ((RaceStruct3 *)participantData)

void func_8002BC2C(RaceUnknownActor *manager, s32 slot, RaceUnknownActor *participant, RaceUnknown174 *participantData) {
    RaceUnknown174 *managerData;
    RacePair *pairs;
    RacePair *slotEntry;
    u16 *route;

    managerData = manager->unk174;
    pairs = managerData->unk20;
    slotEntry = (RacePair *)((s32)pairs + (slot * 8));
    slotEntry->unk0 = participant;
    slotEntry->unk4 = RaceE3;
    RaceE3->unk45 = 0;
    RaceE3->unk3A = 0;
    RaceE3->unk37 = 1;
    if (RaceE3->unk27 == 0) {
        route = raceGetRoute(managerData->unk26);
        if (route != NULL) {
            RaceE3->unk3C = *route - 1;
            func_8002F36C(participantData, route);
        }
        RaceE3->unk48 = cameraFindViewportEntry(RaceE3->unk28);
    }
}
#undef RaceE3

void func_8002BCB0(RaceUnknownActor *manager, s32 slot, s32 *outActor, s32 *outData) {
    RaceUnknown174 *managerData;
    RacePair *pairs;
    RacePair *slotEntry;

    managerData = manager->unk174;
    pairs = managerData->unk20;
    slotEntry = (RacePair *)((s32)pairs + (slot * 8));
    *outActor = (s32)slotEntry->unk0;
    *outData = (s32)slotEntry->unk4;
}

typedef struct RaceEBounds {
    f32 *start;
    char pad4[8];
    f32 *end;
} RaceEBounds;
extern RaceEBounds *D_807F5FD4;

void func_8002BCD4(RaceUnknownActor *actor) {
    RaceUnknown174 *race174;
    f32 *p;
    f32 minX;
    f32 minZ;
    f32 maxX;
    f32 maxZ;
    f32 x;
    f32 z;

    minX = 9999.0f;
    minZ = 9999.0f;
    maxX = -1.0f;
    maxZ = -1.0f;
    race174 = actor->unk174;
    for (p = D_807F5FD4->start; p < D_807F5FD4->end; p += 3) {
        x = p[0];
        if (x < minX) {
            minX = x;
        }
        z = p[2];
        if (z < minZ) {
            minZ = z;
        }
        if (maxX < x) {
            maxX = x;
        }
        if (maxZ < z) {
            maxZ = z;
        }
    }
    race174->unkC = ((maxX - minX) * 0.5f + minX) - 10.0f;
    race174->unk10 = ((maxZ - minZ) * 0.5f + minZ) - 20.0f;
    race174->unk4 = 116.48f / (maxX - minX);
    race174->unk8 = 121.6f / (maxZ - minZ);
}

Gfx *renderRotatedSprite(Gfx *, s32, s32, s32, s32, s32, s32, s32, f32, f32, s32, f32);

Gfx *func_8002BDDC(Gfx *dl, RaceUnknownActor *actor, f32 posX, f32 posZ, u8 red, u8 green, u8 blue) {
    RaceUnknown174 *race174;

    race174 = actor->unk174;
    posX = race174->unkC - posX;
    posZ = race174->unk10 - posZ;
    posX *= race174->unk4;
    posZ *= race174->unk8;
    gDPSetPrimColor(dl++, 0, 0, red, green, blue, 0xC8);
    return renderRotatedSprite(dl, 0x4A, 3, 1, 0x10, 0x10,
        (s32)(((0.5f * posX) + 50.0f) * 4.0f),
        (s32)(((0.5f * posZ) + 60.0f) * 4.0f),
        1.0f, 1.0f, 0, 0.0f);
}

#define WRITE_GFX(pkt, _w0, _w1) { Gfx *_g = (Gfx *)(pkt); _g->words.w0 = (_w0); _g->words.w1 = (_w1); }
extern Gfx D_1000118;
extern Mtx D_20000C0;
extern Mtx D_2000180;
extern u8 D_807444FC;
extern s16 D_80744490;
Gfx *gfxInit2DDisplayList(Gfx *);
s32 _sprintf(char *, const char *, ...);
void *heapFreeDeferred(void *);
void *textTableGetString(s32, s32, s32);
s32 textGetStringWidth(s32, void *);
Gfx *textDrawStringVtx(Gfx *, s32, s16, s16, void *, s32);

Gfx *func_8002BEE8(Gfx *dl, RaceUnknownActor *actor) {
    u8 alpha;
    s32 textX;
    s32 unused;
    RaceUnknown174 *race174;
    s32 countdownVal;
    void *textStr;
    f32 fadeFactor;

    alpha = 0xFF;
    textX = D_80744490 / 2;
    race174 = actor->unk174;
    if (actor->unk154 == 2 || actor->unk154 == 1) {
        if (race174->unk1C < 0x78) {
            if (race174->unk1C < 0x5A) {
                countdownVal = (0x78 - race174->unk1C) / 30;
                if (countdownVal >= 3) {
                    countdownVal = 3;
                }
                textStr = heapAlloc(4);
                heapFreeDeferred(textStr);
                _sprintf(textStr, "%d", countdownVal);
            } else {
                fadeFactor = (f32)(0x78 - race174->unk1C) * 0.033333335f;
                alpha = (u8)(u32)((f32)alpha * fadeFactor);
                textStr = textTableGetString(0x26, 9, 1);
            }
            WRITE_GFX(dl++, 0xDE000000, (u32)&D_1000118);
            WRITE_GFX(dl++, 0xE7000000, 0);
            WRITE_GFX(dl++, 0xE200001C, 0x00504240);
            WRITE_GFX(dl++, 0xFA000000, alpha & 0xFF);
            WRITE_GFX(dl++, 0xFCFF97FF, 0xFF2CFE7F);
            textX -= textGetStringWidth(1, textStr) >> 1;
            dl = textDrawStringVtx(dl, 1, (s16)(textX * 4), 0x3C, textStr, 1);
        }
    }
    return dl;
}

Gfx *func_8002C14C(Gfx *dl, RaceUnknown174 *race174) {
    Struct806C7C94 *hudPos;
    s32 screenX;
    s32 screenY;
    s32 i;
    s32 offset;
    f32 doubleX;
    s16 scaledY;
    f32 f_offset;

    hudPos = race174->unk48;
    screenX = (s32)((f64)(hudPos->unk4 + 8) + 4.0);
    screenY = hudPos->unkA - 0x22;
    WRITE_GFX(dl++, 0xFA000000, 0xFFC800B4);
    i = 0;
    if (race174->unk2A > 0) {
        offset = 0;
        doubleX = (f32)screenX + (f32)screenX;
        scaledY = (s16)(s32)(((f32)screenY + (f32)screenY) * 4.0f);
        do {
            Gfx *next;
            f_offset = offset;
            next = renderRotatedSprite(dl, 0x4A, 3, 1, 0x10, 0x10,
                (s32)((doubleX + f_offset) * 4.0f),
                scaledY, 4.0f, 4.0f, 0, 0.0f);
            i++;
            offset += 0x10;
            dl = next;
        } while (i < race174->unk2A);
    }
    if (race174->unk2A != 0) {
        WRITE_GFX(dl++, 0xDA380003, (u32)&D_2000180);
    }
    return dl;
}

u32 textGetFontHeight(s32);

Gfx *func_8002C2E8(Gfx *dl, RaceUnknown174 *race174) {
    f32 posX;
    f32 doublePosX;
    f32 posY;
    f32 halfFontHeight;
    Struct806C7C94 *hudPos;
    f32 savedHalfFontHeight;
    f32 halfWidthMult;
    f32 spriteX;
    s16 scaledSpriteY;
    s32 xOffset;
    s32 count;
    void *labelStr;
    Gfx *next;

    hudPos = race174->unk48;
    halfFontHeight = (f32)textGetFontHeight(1) * 0.5f;
    savedHalfFontHeight = halfFontHeight;
    posX = (f32)(hudPos->unk4 + 8);
    posY = (f32)(hudPos->unkA - 0x10);
    posY -= 2 * halfFontHeight;
    labelStr = textTableGetString(0x26, 0xA, 1);
    WRITE_GFX(dl++, 0xFA000000, 0xFFFFFFFF);
    dl = textDrawStringVtx(dl, 1, (s16)(s32)(2.0f * (posX * 4.0f)), (s16)(s32)(2.0f * (posY * 4.0f)), labelStr, 4);
    WRITE_GFX(dl++, 0xDA380007, (u32)&D_20000C0);
    WRITE_GFX(dl++, 0xDA380005, (u32)((u8 *)race174 + (D_807444FC << 6) + 0x50));
    halfWidthMult = 0.5f;
    posX += halfWidthMult * (f32)textGetStringWidth(1, labelStr);
    posX = (f32)((f64)posX + 8.0);
    doublePosX = posX + posX;
    posY = (f32)((f64)posY + (0.4 * (f64)savedHalfFontHeight));
    WRITE_GFX(dl++, 0xFA000000, 0xFFFF00FF);
    scaledSpriteY = (s16)(s32)((posY + posY) * 4.0f);
    for (xOffset = 0; xOffset < 0x78; xOffset += 0x18) {
        spriteX = doublePosX;
        spriteX += (f32)xOffset;
        dl = renderRotatedSprite(dl, 0x4B, 3, 1, 0x40, 0x40, (s32)(spriteX * 4.0f), scaledSpriteY, 1.5f, 1.5f, 0, 0.0f);
    }
    WRITE_GFX(dl++, 0xFA000000, 0xFF0000FF);
    count = 0;
    if ((5 - race174->unk44) > 0) {
        xOffset = 0;
        do {
            spriteX = doublePosX;
            spriteX += (f32)xOffset;
            next = renderRotatedSprite(dl, 0x45, 3, 1, 0x40, 0x40, (s32)(spriteX * 4.0f), scaledSpriteY, 1.5f, 1.5f, 0, 0.0f);
            count += 1;
            xOffset += 0x18;
            dl = next;
        } while (count < (5 - race174->unk44));
    }
    WRITE_GFX(dl++, 0xDA380003, (u32)&D_2000180);
    return dl;
}


Gfx *func_8002C63C(Gfx *dl, RaceUnknown174 *race174) {
    WRITE_GFX(dl++, 0xE7000000, 0);
    WRITE_GFX(dl++, 0xE200001C, 0x00504240);
    WRITE_GFX(dl++, 0xE3000A01, 0);
    WRITE_GFX(dl++, 0xFC119623, 0xFF2FFFFF);
    dl = gfxInit2DDisplayList(dl);
    WRITE_GFX(dl++, 0xDE000000, (u32)&D_1000118);
    WRITE_GFX(dl++, 0xDA380007, (u32)&D_20000C0);
    guScale((Mtx *)((u8 *)race174 + (D_807444FC << 6) + 0x50), 0.5f, 0.5f, 1.0f);
    WRITE_GFX(dl++, 0xDA380005, (u32)((u8 *)race174 + (D_807444FC << 6) + 0x50));
    WRITE_GFX(dl++, 0xDA380003, (u32)&D_2000180);
    return dl;
}

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
#define RaceE76C ((RaceE76CView *)race174)

Gfx *raceDrawHudText(Gfx *dl, RaceUnknown174 *race174) {
    RaceUnknown174 *parent174;
    Struct806C7C94 *hudPos;
    s32 pad6C;
    void *textBuf;
    u8 lap;
    s32 textX;
    s32 textY;
    s32 placeIdx;
    u32 fontHeight;
    s32 lapStr;
    s32 ofStr;
    s32 len;
    s32 hudFlags;
    Gfx *g0;

    hudPos = race174->unk48;
    lap = RaceE76C->unk37;
    parent174 = race174->unk30->unk174;
    textX = hudPos->unk4 + 8;
    textY = hudPos->unkA - 0x10;
    g0 = dl++;
        g0->words.w1 = 0;
        g0->words.w0 = 0xE7000000;
    WRITE_GFX(dl++, 0xFA000000, 0xFFFFFFFF);
    hudFlags = parent174->unk0;
    if (hudFlags & 4) {
        lap = (lap < parent174->unk24) ? lap : parent174->unk24;
        lap = (lap >= 2) ? lap : 1;
        lapStr = (s32)textTableGetString(0x26, 0xB, 1);
        ofStr = (s32)textTableGetString(0x26, 0xC, 1);
        len = strlen((u8 *)lapStr);
        len += strlen((u8 *)ofStr);
        textBuf = heapAlloc(len + 8);
        heapFreeDeferred(textBuf);
        _sprintf(textBuf, "%s %d %s %d", lapStr, lap, ofStr, parent174->unk24);
        dl = textDrawStringVtx(dl, 1, (s16)(s32)(2.0f * (f32)(textX * 4)), (s16)(s32)(2.0f * (f32)(textY * 4)), textBuf, 4);
        g0 = dl++;
        g0->words.w0 = 0xDA380007; g0->words.w1 = (u32)&D_20000C0; // LAYOUT: same-line stores steer the ori/addiu schedule
        g0 = dl++;
        g0->words.w0 = 0xDA380005;
        g0->words.w1 = (u32)((u8 *)race174 + (D_807444FC << 6) + 0x50);
        fontHeight = textGetFontHeight(1);
        textY = (s32)((f32)textY - (0.5f * (f32)fontHeight));
        hudFlags = parent174->unk0;
    }
    if (hudFlags & 2) {
        placeIdx = RaceE76C->unk36;
        if ((placeIdx + 1) == parent174->unk1E) {
            placeIdx = 3;
        }
        if (RaceE76C->unk45 != 0) {
            placeIdx = 4;
        }
        dl = textDrawStringVtx(dl, 1, (s16)(s32)((f32)(textX * 4) + (f32)(textX * 4)), (s16)(s32)(2.0f * (f32)(textY * 4)), textTableGetString(0x26, D_8002FCC0[placeIdx], 1), 4);
    }
    if (RaceE76C->unk34 >= 3 && RaceE76C->unk34 < 5) {
        dl = textDrawAnimated(dl, RaceE76C->unk46, 2, 160.0f, 100.0f, 0.0f, 1.5f);
    }
    return dl;
}


s32 func_807142D8(void);
Gfx *func_8002C63C(Gfx *, RaceUnknown174 *);
Gfx *func_8002C2E8(Gfx *, RaceUnknown174 *);
Gfx *func_8002C14C(Gfx *, RaceUnknown174 *);
Gfx *raceDrawHudText(Gfx *, RaceUnknown174 *);

Gfx *func_8002CAC8(Gfx *dl, RaceUnknownActor *actor, RaceUnknown174 *race174) {
    RaceUnknown174 *parent174;
    RaceUnknownActor *playerActor;
    RaceUnknown174 *player174;

    parent174 = race174->unk30->unk174;
    if (race174 == NULL || func_807142D8() != 0) {
        return dl;
    }
    playerActor = gPlayerSlots[race174->unk28].unk4;
    if (playerActor == NULL) {
        return dl;
    }
    player174 = playerActor->unk174;
    if (actor != player174->unk88) {
        return dl;
    }
    dl = func_8002C63C(dl, race174);
    if (parent174->unk0 & 8) {
        dl = func_8002C2E8(dl, race174);
    } else if (parent174->unk0 & 0x10) {
        dl = func_8002C14C(dl, race174);
    }
    if (parent174->unk0 & 6) {
        dl = raceDrawHudText(dl, race174);
    }
    return dl;
}

struct RaceECB3;
typedef struct RaceECBPair {
    struct RaceUnknownActor *unk0;
    struct RaceECB3 *unk4;
} RaceECBPair;
typedef struct RaceECBView {
    u8 unk0;
    char pad1[0x13];
    u16 unk14;
    u16 unk16;
    u16 unk18;
    u16 unk1A;
    char pad1C[2];
    u8 unk1E;
    char pad1F;
    RaceECBPair *unk20;
} RaceECBView;
typedef struct RaceECB3 {
    char pad0[0x27];
    u8 unk27;
    char pad28[4];
    struct RaceUnknownActor *unk2C;
} RaceECB3;

Gfx *func_8002CBEC(Gfx *dl, RaceUnknownActor *actor) {
    RaceECBView *radarView;
    RaceECB3 *participantStruct;
    RaceUnknownActor *participantActor;
    RaceUnknownActor *targetActor;
    RaceECBPair *pairs;
    s32 i;
    int red;
    int blue;

    radarView = (RaceECBView *)actor->unk174;
    if (radarView->unk0 & 1) {
        pairs = radarView->unk20;
        WRITE_GFX(dl++, 0xE7000000, 0);
        WRITE_GFX(dl++, 0xD7000000, 0xFFFFFFFF);
        WRITE_GFX(dl++, 0xE200001C, 0x00504240);
        dl = gfxInit2DDisplayList(dl);
        WRITE_GFX(dl++, 0xFA000000, 0x3CA0);
        WRITE_GFX(dl++, 0xE3000A01, 0);
        WRITE_GFX(dl++, 0xFCFFFFFF, 0xFFFDF6FB);
        WRITE_GFX(dl++, 0xF6148170, 0x00048070);
        WRITE_GFX(dl++, 0xE7000000, 0);
        WRITE_GFX(dl++, 0xFA000000, 0x8000FF64);
        WRITE_GFX(dl++, 0xF6150070, 0x00040068);
        WRITE_GFX(dl++, 0xF6150178, 0x00040170);
        WRITE_GFX(dl++, 0xF6048170, 0x00040070);
        WRITE_GFX(dl++, 0xF6150170, 0x00148070);
        WRITE_GFX(dl++, 0xE7000000, 0);
        WRITE_GFX(dl++, 0xFA000000, 0xFFFFFFB4);
        WRITE_GFX(dl++, 0xFC119623, 0xFF2FFFFF);
        WRITE_GFX(dl++, 0xDA380003, (u32)&D_2000180);
        WRITE_GFX(dl++, 0xDA380007, (u32)&D_20000C0);
        WRITE_GFX(dl++, 0xD7000002, 0x80008000);
        dl = renderRotatedSprite(dl, radarView->unk14, 3, 1, 0x40, 0x40, 0x88, 0x130, 2.0, 2.0, 0, 0.0f);
        dl = renderRotatedSprite(dl, radarView->unk16, 3, 1, 0x40, 0x40, 0x108, 0x130, 2, 2, 0, 0.0f);
        dl = renderRotatedSprite(dl, radarView->unk18, 3, 1, 0x40, 0x40, 0x88, 0xB0, 2.0f, 2.0f, 0, 0.0f);
        dl = renderRotatedSprite(dl, radarView->unk1A, 3, 1, 0x40, 0x40, 0x108, 0xB0, 2.0f, 2.0f, 0, 0.0f);
        for (i = 0; i < radarView->unk1E; i++) {
            participantActor = pairs[i].unk0;
            if (participantActor == NULL) {
                continue;
            }
            participantStruct = pairs[i].unk4;
            if (participantStruct->unk27 == 0) {
                red = 0x80;
                blue = 0x80;
            } else if (participantStruct->unk27 == 1) {
                red = 0xFF;
                blue = 0;
            } else {
                continue;
            }
            dl = func_8002BDDC(dl, actor, participantActor->unk7C, participantActor->unk84, red, 0, blue);
            targetActor = participantStruct->unk2C;
            if (targetActor != NULL) {
                dl = func_8002BDDC(dl, actor, targetActor->unk7C, targetActor->unk84, 0xFF, 0xC8, 0);
            }
        }
    }
    return func_8002BEE8(dl, actor);
}


extern RaceUnknownActor *D_807FBB44;
void actorSpawn(s32, s32);
void raceInitParticipants(RaceUnknownActor *);
void func_800292D0(RaceUnknownActor *);
void func_8002E2C8(RaceUnknownActor *);

void func_80025E9C(RaceUnknownActor *);
void func_8002BCD4(RaceUnknownActor *);

void func_8002CFF0(void) {
    RaceUnknown174 *race174;
    RaceUnknownActor *actor;

    actorSpawn(0x132, 0);
    actor = D_807FBB44;
    func_80025E9C(actor);
    func_8002BCD4(actor);
    race174 = actor->unk174;
    race174->unk0 = 0x17;
    race174->unk14 = 0x46;
    race174->unk16 = 0x47;
    race174->unk18 = 0x48;
    race174->unk1A = 0x49;
    race174->unk24 = 2;
}


void func_8002D064(void) {
    RaceUnknown174 *race174;

    actorSpawn(0x132, 0);
    race174 = D_807FBB44->unk174;
    raceInitParticipants(D_807FBB44);
    race174->unk0 = 0xE;
    race174->unk24 = 2;
}

void func_8002D0B0(void) {
    RaceUnknown174 *race174;

    actorSpawn(0x132, 0);
    race174 = D_807FBB44->unk174;
    func_800292D0(D_807FBB44);
    race174->unk0 = 0xE;
    race174->unk24 = 2;
}

void func_8002D0FC(void) {
    RaceUnknown174 *race174;

    actorSpawn(0x132, 0);
    race174 = D_807FBB44->unk174;
    func_8002E2C8(D_807FBB44);
    race174->unk0 = 2;
    race174->unk24 = 1;
}

extern RaceUnknownActor *D_807FBB40;
extern s32 D_8002FCD4[];
s32 gfxResourceCreate(s32, void *, s32, f32, f32, f32);

void func_8002D148(RacePair *pair, u8 newStatus) {
    RaceUnknown174 *t;
    s32 slot;

    if (pair->unk4->unk34 != newStatus) {
        pair->unk4->unk34 = newStatus;
        pair->unk4->unk35 = 0;
        if (newStatus == 3) {
            t = D_807FBB40->unk174;
            slot = pair->unk4->unk36;
            if (slot + 1 == (u32)t->unk1E || pair->unk4->unk45 != 0) {
                slot = 3;
            }
            if (pair->unk4->unk27 == 0) {
                pair->unk4->unk46 = gfxResourceCreate(1, textTableGetString(0x26, D_8002FCD4[slot], 1), 2, 160.0f, 100.0f, 0.0f);
            }
        }
    }
}

void func_8002D148(RacePair *, u8);

void func_8002D224(u8 newStatus) {
    s32 i;
    RaceUnknown174 *race174;
    RacePair *pairs;

    race174 = D_807FBB40->unk174;
    pairs = race174->unk20;
    D_807FBB40->unk154 = newStatus;
    for (i = 0; i < race174->unk1E; i++) {
        if (pairs[i].unk0 != 0) {
            func_8002D148(&pairs[i], newStatus);
        }
    }
}

f32 func_8002D2C0(RaceStruct3 *race3) {
    f32 temp;

    if (race3->unk26 >= 11 && race3->unk26 < 15 && (D_807FD63A[race3->unk28].unk0 & 0x2000)) {
        temp = race3->unk26 - 10;
        return temp * 0.2f;
    }
    return 0.0f;
}

void actorDespawn(void *, void *);

void func_8002D338(void *parent, RaceUnknownC *child) {
    RaceUnknownActor *childActor;
    RaceUnknown174 *race174;

    childActor = child->unkC;
    race174 = childActor->unk174;
    race174->unk2C = NULL;
    actorDespawn(parent, child);
}

RaceUnknownActor *raceFindNearestParticipant(RaceUnknownActor *self) {
    RaceUnknownActor *owner;
    f32 best;
    f32 d;
    RaceUnknown174 *own174;
    RaceUnknownActor *ret;
    RaceUnknownActor *o;
    RaceUnknown174 *t;
    RacePair *list;
    s32 i;

    best = 1e9f;
    own174 = self->unk174;
    owner = own174->unk30;
    t = owner->unk174;
    ret = NULL;
    list = t->unk20;
    for (i = 0; i < t->unk1E; i++) {
        o = list[i].unk0;
        if (o != NULL && o != self) {
            d = (self->unk7C - o->unk7C) * (self->unk7C - o->unk7C) + (self->unk80 - o->unk80) * (self->unk80 - o->unk80) + (self->unk84 - o->unk84) * (self->unk84 - o->unk84);
            if (d < best) {
                ret = o;
                best = d;
            }
        }
    }
    return ret;
}

void sfxAllocateChannel(s32, f32);

void racePlayResultSfx(void) {
    RaceUnknown174 *race174;
    RacePair *list;
    RaceStruct3 *s;
    s32 i;
    s32 id;

    race174 = D_807FBB40->unk174;
    id = 0;
    list = race174->unk20;
    i = race174->unk1E - 1;
    if (i >= 0) {
        do {
            s = list[i].unk4;
            if (s->unk27 == 1) {
                if (s->unk36 != 0) {
                    id = 0x56;
                } else {
                    id = 0x57;
                }
            }
            i--;
        } while (id == 0 && i >= 0);
    }
    if (id == 0) {
        id = 0x56;
    }
    sfxAllocateChannel(id, 1.0f);
}

extern s32 gCurrentMap;

void func_8002D4A0(void) {
    s32 soundId;
    f32 vol;

    vol = 1.0f;
    switch (gCurrentMap) {
    case 0xE:
        soundId = 0x13;
        vol = 0.6f;
        break;
    case 0x27:
        soundId = 0x3D;
        break;
    case 0x52:
        soundId = 0x66;
        break;
    case 0x1B:
    default:
        soundId = 0x1B;
        break;
    }
    sfxAllocateChannel(soundId, vol);
}
void racePlayResultSfx(void);

void raceUpdateStandings(void) {
    RaceUnknown174 *t;
    RacePair *base;
    RacePair *p;
    RacePair *q;
    s32 i;
    s32 j;
    RacePair tmp;
    u8 cnt;
    u8 swap;

    t = D_807FBB40->unk174;
    cnt = 0;
    base = t->unk20;
    for (i = t->unk1E - 1; i >= 0; i--) {
        for (j = 1; j <= i; j++) {
            p = &base[j - 1];
            q = &base[j];
            swap = 0;
            if (p->unk4->unk45 != 0 && q->unk4->unk45 == 0) {
                swap = 1;
            } else {
                if (p->unk4->unk37 < q->unk4->unk37) {
                    swap = 1;
                } else if (p->unk4->unk37 == q->unk4->unk37) {
                    if (p->unk4->unk3A < q->unk4->unk3A) {
                        swap = 1;
                    } else if (p->unk4->unk3A == q->unk4->unk3A && q->unk4->unk40 < p->unk4->unk40) {
                        swap = 1;
                    }
                }
            }
            if (swap != 0) {
                tmp = *p;
                *p = *q;
                *q = tmp;
            }
        }
    }
    q = base;
    for (i = 0; i < t->unk1E; i++, q++) {
        q->unk4->unk36 = i;
        if (q->unk4->unk45 != 0 || (q->unk4->unk34 == 2 && t->unk24 < q->unk4->unk37)) {
            func_8002D148(q, 3);
            cnt++;
        }
    }
    if (cnt >= t->unk1E - 1) {
        func_8002D224(3);
        racePlayResultSfx();
        t->unk1C = 0;
    }
}

void func_8002D72C(RaceUnknownActor *actor) {
    RaceUnknown174 *race174;

    if (actor != NULL && actor->unk154 == 0) {
        race174 = actor->unk174;
        race174->unk1C = 2;
    }
}

void func_8002D754(RaceUnknownActor *actor) {
    RaceUnknown174 *race174;

    if (actor != NULL && actor->unk154 == 0) {
        race174 = actor->unk174;
        race174->unk1C = 0;
    }
}

typedef struct RaceFActorView {
    char pad0[4];
    RaceSub4 *unk4;
    char pad8[0x60 - 8];
    u32 unk60;
    char pad64[0xE4 - 0x64];
    s16 unkE4;
    char padE6[2];
    s16 unkE8;
    char padEA[0x128 - 0xEA];
    s16 unk128;
} RaceFActorView;
void sfxPlayOnFreeSlot(s16, s32, f32, f32, s32, s32);
void raceUpdateWaypointActivation(RaceUnknown174 *);

void raceUpdateStandings(void);

void func_8002D778(void) {
    void renderCallbacksRegister(void *, RaceUnknownActor *, s32);
    RaceUnknown174 *t;
    u16 sound;
    u8 i;
    RaceStruct3 *s;
    f32 scale;
    RaceFActorView *pa;
    s32 k;
    RacePair *list;

    t = D_807FBB40->unk174;
    if (!(D_807FBB40->unk60 & 0x10)) {
        t->unk1C = 0x1E;
    }
    switch (D_807FBB40->unk154) {
    case 0:
        if (t->unk1C != 0) {
            t->unk1C = (u32)t->unk1C - 1;
        } else {
            func_8002D224(1);
        }
        break;
    case 1:
        if (t->unk1C < 0x5B) {
            if (t->unk1C % 30 == 0) {
                sound = 0x75;
                if (t->unk1C == 0x5A) {
                    func_8002D224(2);
                    sound = 0x74;
                    func_8002D4A0();
                }
                sfxPlayOnFreeSlot(sound, 0x7FFF, 64.0f, 1.0, 0, 0x80);
            }
            t->unk1C = (u32)t->unk1C + 1;
        }
        break;
    case 2:
        if (t->unk1C < 0x78) {
            t->unk1C = (u32)t->unk1C + 1;
        }
        raceUpdateStandings();
        break;
    case 3:
        if (gCurrentMap == 0xE || gCurrentMap == 0x52) {
            func_8002D224(4);
            t->unk1C = 0x32;
        } else {
            t->unk1C = t->unk1C + 1;
            if (t->unk1C >= 0x78) {
                if (t->unk25 == 1) {
                    func_8002D224(4);
                    t->unk1C = 0x32;
                } else {
                    func_8002D224(6);
                }
            }
        }
        break;
    case 4:
        if (t->unk1C != 0) {
            t->unk1C = t->unk1C - 1;
        } else {
            list = t->unk20;
            for (i = 0; i < t->unk1E; i++) {
                s = list[i].unk4;
                if (s->unk27 == 0) {
                    pa = (RaceFActorView *)gPlayerSlots[s->unk28].unk4;
                    scale = 1.0f;
                    pa->unk128 = 0xFF;
                    pa->unk60 |= 0x8000;
                    if (gCurrentMap == 0xB9) {
                        scale = 0.3f;
                    }
                    for (k = 0; k < 3; k++) {
                        pa->unk4->unk34[k] = scale * 0.15;
                    }
                    pa->unkE8 = 0;
                    pa->unkE4 = 0;
                }
            }
            if (!t->unk1C && !t->unk1C && !t->unk1C) { // FAKE: empty guard steers regalloc
            }
            func_8002D224(5);
        }
        break;
    }
    raceUpdateWaypointActivation(t);
    if (func_807142D8() == 0) {
        if (D_807FBB40->unk154 > 0 && D_807FBB40->unk154 < 5) {
            renderCallbacksRegister((void *)func_8002CBEC, D_807FBB40, 3);
        }
    }
}

f32 func_80612794(s16);

void func_8002DA68(RaceUnknown174 *race174) {
    s16 angle;
    f32 scale;
    f32 scaleCopy;

    switch (D_807FBB40->unk154) {
    case 0:
        angle = race174->unk2;
        if (((s16)(angle % 2048) >= 0x81) && ((0x800 - (s16)(angle % 2048)) >= 0x81)) {
            race174->unk2 = angle + 0x80;
            angle = race174->unk2;
        }
        break;
    case 1:
        race174->unk2 += 0x80;
        angle = race174->unk2;
        break;
    default:
        angle = race174->unk2;
        break;
    }
    race174->unk2 = angle & 0xFFF;
    scale = (((func_80612794(race174->unk2) + 1.0f) * 1.5) + 1.0) * race174->unk4;
    D_807FBB40->unk4->unk34[2] = scale;
    scaleCopy = D_807FBB40->unk4->unk34[2];
    D_807FBB40->unk4->unk34[1] = scaleCopy;
    D_807FBB40->unk4->unk34[0] = scaleCopy;
}
void animSetSpeed(RaceUnknownActor *, s32, f32);
void animSetLoopLimit(RaceUnknownActor *, s32, s32);
void animSetFinished(RaceUnknownActor *, s32, s32);
s32 animIsPlaying(RaceUnknownActor *, s32);

void func_8002DB90() {
    if (D_807FBB40->unk154 != 0) {
        if (D_807FBB40->unk154 == 1) {
            if (animIsPlaying(D_807FBB40, 0) == 0) {
                animSetSpeed(D_807FBB40, 0, 1.0f);
                animSetLoopLimit(D_807FBB40, 0, -1);
            }
        }
    } else {
        if (animIsPlaying(D_807FBB40, 0) != 0) {
            animSetFinished(D_807FBB40, 0, 1);
        }
    }
}

void actorUpdateFloorContactAndTilt(RaceUnknownActor *, f32);
void actorUpdateModelMatrix(RaceUnknownActor *, s32);

void func_8002DC24(void) {
    RaceUnknown174 *race174 = D_807FBB40->unk174;

    if (!(D_807FBB40->unk60 & 0x10)) {
        race174->unk4 = D_807FBB40->unk4->unk34[1];
    }
    switch (race174->unk0) {
    case 2:
        func_8002DB90(race174);
        break;
    case 1:
        func_8002DB90(race174);
        actorUpdateFloorContactAndTilt(D_807FBB40, 0.0f);
        D_807FBB40->unk80 = D_807FBB40->unkAC;
        D_807FBB40->unk6A |= 4;
        D_807FBB40->unk6C |= 4;
        break;
    default:
        func_8002DA68(race174);
        break;
    }
    actorUpdateModelMatrix(D_807FBB40, 0);
}

typedef struct RaceFView8 {
    char pad0[8];
    u8 unk8;
} RaceFView8;

void func_8002DCF0(RaceUnknownDCF0 *holder, s32 state) {
    u8 i;
    RaceUnknownActor *a;
    RaceFView8 *p;

    for (i = 0; i < 2; i++) {
        a = holder->unk1C[i];
        if (a != NULL) {
            p = (RaceFView8 *)a->unk174;
            if (state == 1) {
                if (p->unk8 == 0) {
                    a->unk154 = state;
                }
                p->unk8 = p->unk8 + 1;
            } else {
                if (p->unk8 != 0) {
                    p->unk8 = p->unk8 - 1;
                }
                if (p->unk8 == 0) {
                    a->unk154 = state;
                }
            }
        }
    }
}

f32 raceLerp(f32 t, f32 x0, f32 y0, f32 x1, f32 y1) {
    return ((y1 - y0) * ((t - x0) / (x1 - x0))) + y0;
}

typedef struct RaceCurvePoint {
    f32 x;
    f32 y;
} RaceCurvePoint;

typedef struct RaceVec3f {
    f32 x;
    f32 y;
    f32 z;
} RaceVec3f;

f32 func_8002DDA0(f32 targetX, RaceCurvePoint *points) {
    u8 i;
    f32 ret;
    s32 found;

    found = 0;
    i = 1;
    if (targetX < points[0].x) {
        ret = points[0].y;
        found = 1;
    }
    if (found == 0) {
        do {
            f32 x = points[i].x;
            if (targetX < x) {
                ret = raceLerp(targetX, points[i - 1].x, points[i - 1].y, x, points[i].y);
                found = 1;
            }
            i++;
        } while (i < 6 && found == 0);
    }
    if (found == 0) {
        ret = points[5].y;
    }
    return ret;
}

void func_8002DE78(RaceUnknownActor *actor, u8 mode, RaceCurvePoint *points, RaceVec3f *values) {
    switch (mode) {
    case 0:
    case 1:
        points[0].y = values->x;
        points[1].y = values->y;
        points[2].y = values->y;
        points[3].y = values->y;
        points[4].y = values->y;
        points[5].y = values->z;
        break;
    case 2:
    case 3:
        points[3].y = values->z;
        points[4].y = values->z;
        points[5].y = values->z;
        break;
    case 5:
        points[0].y = values->x;
        points[1].y = values->z;
        points[2].y = values->z;
        points[3].y = values->z;
        points[4].y = values->z;
        points[5].y = values->z;
        break;
    }
    D_807FBB40->unk155 = 0;
    actor->unkF = mode;
}

s32 randomLcgNext(void);

f32 func_8002DF38(RaceUnknownActor *actor, f32 t, RaceCurvePoint *points, RaceVec3f *values) {
    f32 ret;
    f32 lim;
    RaceSub4 *sub;

    switch (actor->unkF) {
    case 0:
        ret = func_8002DDA0(t, points);
        break;
    case 1:
        ret = func_8002DDA0(t, points);
        if (actor->unk10 != 0) {
            if (points[4].x < t) {
                if ((u32)randomLcgNext() % 0xFF < 0xA) {
                    func_8002DE78(actor, 2, points, values);
                }
            }
        }
        break;
    case 2:
    case 3:
    case 4:
        if (actor->unkF == 3 || actor->unkF == 4 || actor->unk10 != 0) {
            sub = actor->unk4;
            lim = sub->unk4;
            points[0].y = lim < values->x ? lim : values->x;
            points[1].y = lim < values->y ? lim : values->y;
            if (actor->unkF == 4) {
                points[2].y = lim;
            } else {
                points[2].y = values->z;
            }
            ret = func_8002DDA0(t, points);
            if (actor->unkF == 2) {
                if (t < points[3].x) {
                    func_8002DE78(actor, 3, points, values);
                }
            }
            if (actor->unkF == 3) {
                if (t < points[2].x) {
                    func_8002DE78(actor, 4, points, values);
                }
            }
        } else if (actor->unkF == 2) {
            ret = values->y;
            func_8002DE78(actor, 1, points, values);
        }
        break;
    case 5:
        ret = func_8002DDA0(t, points);
        if (t < points[1].x) {
            func_8002DE78(actor, 1, points, values);
        }
        break;
    default:
        ret = 0.0f;
        break;
    }
    return ret;
}

f32 func_8002E1C8(RaceUnknownActor *actor, f32 t, RaceCurvePoint *points, RaceVec3f *values) {
    f32 ret;

    switch (actor->unkF) {
    case 0:
        ret = func_8002DDA0(t, points);
        break;
    case 1:
        ret = func_8002DDA0(t, points);
        if (actor->unk10 != 0) {
            if (points[4].x < t) {
                func_8002DE78(actor, 5, points, values);
            }
        }
        break;
    case 5:
        ret = func_8002DDA0(t, points);
        if (t < points[1].x) {
            func_8002DE78(actor, 1, points, values);
        }
        break;
    default:
        ret = 0.0f;
        break;
    }
    return ret;
}

extern u8 gPlayerCount;
RaceUnknownActor *spawnNodeSpawnById(s32, s32, s32, s32, s32, s32, s32);
void func_8002BC2C(RaceUnknownActor *, s32, RaceUnknownActor *, RaceUnknown174 *);

void func_8002E2C8(RaceUnknownActor *raceManager) {
    RaceUnknown174 *managerData;
    RaceUnknown174 *participantData;
    RaceUnknownActor *participantActor;
    s32 slotIndex;
    s32 playerIdx;
    s32 participantCount;

    participantCount = gPlayerCount;
    slotIndex = 0;
    managerData = raceManager->unk174;
    if (participantCount == 1) {
        participantCount++;
    }
    func_8002BBD0(raceManager, participantCount);
    if (gPlayerCount == 1) {
        participantActor = spawnNodeSpawnById(1, 0, 0, 0, 0, 0, 0);
        participantData = participantActor->unk178;
        participantData->unk27 = 1;
        func_8002BC2C(raceManager, 0, participantActor, participantData);
        slotIndex = 1;
        func_8002BCB0(raceManager, 0, participantActor->unk17C, participantActor->unk17C + 1);
        managerData->unk25 = 1;
    } else {
        managerData->unk25 = 0;
    }
    for (playerIdx = 0; playerIdx < gPlayerCount; playerIdx++) {
        actorSpawn(0x13B, 0);
        participantActor = D_807FBB44;
        participantData = participantActor->unk174;
        participantData->unk27 = 0;
        func_8002BC2C(raceManager, slotIndex, participantActor, participantData);
        slotIndex++;
        participantData->unk28 = playerIdx;
    }
    playerIdx = 0;
    if (participantCount > 0) {
        do {
            func_8002BCB0(raceManager, playerIdx, (s32 *)&participantActor, (s32 *)&participantData);
            participantData->unk36 = playerIdx;
            playerIdx++;
            participantData->unk30 = raceManager;
        } while (playerIdx != participantCount);
    }
    managerData->unk26 = 0;
}


void func_8002E464(void *gfx, RaceUnknownActor *actor) {
    func_8002CAC8(gfx, actor, actor->unk174);
}

void playerStateQueueCallback(s32, RaceUnknownActor *, u8, RaceUnknownActor *);
void func_8002F490(RaceStruct3 *);
void renderCallbacksRegister(void *, RaceUnknownActor *, s32);

void func_8002E484(void) {
    RaceUnknownActor *playerActor;
    RaceUnknownActor *raceActor;
    RaceStruct3 *raceData;
    f32 curMax;
    f32 diff;

    raceActor = D_807FBB40;
    raceData = (RaceStruct3 *)raceActor->unk174;
    playerActor = gPlayerSlots[raceData->unk28].unk4;
    if (!(raceActor->unk60 & 0x10)) {
        playerStateQueueCallback(0x4E, raceActor, raceData->unk28, playerActor);
        D_807FBB40->unk154 = 0;
        D_807FBB40->unk155 = 0;
        raceActor = D_807FBB40;
    }
    if ((raceData->unk34 == 2) && (raceActor->unk154 == 0)) {
        playerStateQueueCallback(0x57, NULL, raceData->unk28, playerActor);
        raceActor = D_807FBB40;
        raceActor->unk154++;
        raceActor = D_807FBB40;
    }
    raceActor->unk7C = playerActor->unk7C;
    D_807FBB40->unk80 = playerActor->unk80;
    D_807FBB40->unk84 = playerActor->unk84;
    if (raceData->unk34 == 2) {
        func_8002F490(raceData);
        raceActor = D_807FBB40;
    }
    if ((raceData->unk34 > 0) && (raceData->unk34 < 5)) {
        renderCallbacksRegister((void *)func_8002E464, D_807FBB40, 3);
    }
    raceData->unk1C = (raceData->unk40 < raceData->unk1C) ? raceData->unk1C : raceData->unk40;
    curMax = raceData->unk18;
    diff = (f32)(raceData->unk3A * 3000) - raceData->unk40;
    raceData->unk14 = diff;
    if (diff < curMax) {
        raceData->unk18 = curMax;
        return;
    }
    raceData->unk18 = raceData->unk14;
}

typedef struct RaceFE644Arg {
    RaceUnknownActor *unk0;
    char pad4[0xA];
    u8 unkE;
    u8 unkF;
    char pad10[4];
    f32 unk14;
} RaceFE644Arg;
extern u8 D_807FBD70;
s16 mathAngleBetweenPoints2D(f32, f32, f32, f32);
s32 mathAngleDistance(s16, s16);
f32 func_80611BB4(f32, f32);
f32 func_80612790(s16);
void sfxPlayAtPositionPooled(f32, f32, f32, s32, s32, s32, s32, s32, f32, s32);

void func_8002E644(RaceFE644Arg *collision) {
    f32 distSq;
    f32 unused_pad;
    f32 velX;
    f32 velZ;
    f32 playerVel;
    s16 diffAnglePlayer;
    s16 diffAngleActor;
    s16 targetAngle;
    f32 bounceScale;
    s32 sfxId;
    RaceUnknownActor *actor;

    actor = collision->unk0;
    distSq = (actor->unk7C - D_807FBB40->unk7C) * (actor->unk7C - D_807FBB40->unk7C) + (actor->unk84 - D_807FBB40->unk84) * (actor->unk84 - D_807FBB40->unk84);
    if (D_807FBD70 == 4 && distSq < collision->unk14 && (collision->unkF == 1 || collision->unkF == 0 || collision->unkF == 4 || (D_807FBB40->unk58 == 0x143 && collision->unkF == 5))) {
        targetAngle = mathAngleBetweenPoints2D(D_807FBB40->unk7C, D_807FBB40->unk84, actor->unk7C, actor->unk84);
        bounceScale = 1.0f;
        if (mathAngleDistance(actor->unkEE, targetAngle) < 0x200) {
            bounceScale = 4.0f;
        }
        diffAngleActor = (s16)(actor->unkEE - targetAngle) & 0xFFF;
        diffAnglePlayer = (s16)(D_807FBB40->unkEE - targetAngle);
        diffAnglePlayer = diffAnglePlayer & 0xFFF;
        velX = func_80612794(diffAngleActor) * actor->unkB8;
        velZ = func_80612790(diffAngleActor) * actor->unkB8;
        playerVel = func_80612790(diffAnglePlayer) * D_807FBB40->unkB8;
        velZ = (playerVel - velZ) * bounceScale + playerVel;
        actor->unkB8 = sqrtf(velX * velX + velZ * velZ);
        actor->unkEE = (s16)(s32)(((f64)func_80611BB4(velX, velZ) * 4096.0) / 6.2831854820251465);
        actor->unkEE = actor->unkEE + targetAngle;
        actor->unkEE = actor->unkEE & 0xFFF;
        if (collision->unkE == 0) {
            switch (D_807FBB40->unk58) {
            case 0x134:
                sfxId = 0x1F9;
                break;
            case 0x143:
                sfxId = 0x18A;
                break;
            }
            sfxPlayAtPositionPooled(D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84, (s16)sfxId, 0xFF, 0x7F, 0, 0, 0.0f, 0);
            collision->unkE = 0x14;
        }
    }
    collision->unk14 = distSq;
    if (collision->unkE > 0) {
        collision->unkE = collision->unkE - 1;
    }
}

s32 slotQueueGetValue(s32, s32);
s32 func_8002E8EC(RaceStruct3 *race3_0, RaceStruct3 *race3_1, s32 threshold) {
    s32 ret;

    if (race3_1->unk45 != 0) {
        ret = 0;
    } else if (race3_0->unk36 != 0) {
        if (slotQueueGetValue(11, 0) >= threshold) {
            ret = 1;
        } else {
            ret = 3;
        }
    } else {
        ret = 2;
    }
    return ret;
}
