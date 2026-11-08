#include "common.h"
#include "actor.h"

extern Actor *gCurrentActor;
extern Actor *gSpawnedActor;
extern Actor *D_807FBB48;
extern Actor *D_807FBB4C;
extern void *gPlayerSlots;
extern u8 gPlayerCount;
extern u8 gCurrentPlayerIndex;
extern u8 D_807FC950[][0x5E];
extern s32 gCurrentMap;
extern u8 D_8076A0AB;
extern u8 D_8076A0B1;
extern s16 gScreenWidth;
extern s16 gScreenHeight;
extern u8 D_807444F8;
extern u8 gGfxBufferIndex;

extern s32 textGetStringWidth(s16, s32);
void textDrawStringVtx(s32, s16, s16, s16, s32, u8);

void textDrawStringCentered(s32 glist, s16 font, s32 str, s16 y, u8 flags) {
    s16 width;
    s16 height;

    width = (gScreenWidth - textGetStringWidth(font, str)) * 2;
    height = y * 4;
    textDrawStringVtx(glist, font, width, height, str, flags);
}

void func_806FD950(s32 glist, s16 font, s32 str, s16 y) {
    textDrawStringVtx(glist, font, 0x60, (s16)(y * 4), str, 1);
}

typedef struct GfxResourceEntry {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    f32 unk14;
    f32 unk18;
    f32 unk1C;
    f32 unk20;
    f32 unk24;
    f32 unk28;
    f32 unk2C;
    f32 unk30;
    f32 unk34;
} GfxResourceEntry;

typedef struct GfxResourceNode {
    struct GfxResourceNode *next;
    void *unk4;
    GfxResourceEntry *unk8;
    s8 unkC;
    u8 unkD;
    u8 unkE[6];
    f32 unk14;
    f32 unk18;
    s16 unk1C;
} GfxResourceNode;

extern GfxResourceNode *gGfxResourceList;
extern s16 gGfxResourceNextId;

void gfxResourceListReset(void) {
    gGfxResourceList = NULL;
    gGfxResourceNextId = 0;
}

GfxResourceNode *gfxResourceFindById(s16 resourceId) {
    GfxResourceNode *node;

    node = gGfxResourceList;
    if ((node != NULL) && (resourceId != node->unk1C)) {
loop_2:
        node = node->next;
        if ((node != NULL) && (resourceId != node->unk1C)) {
            goto loop_2;
        }
    }
    return node;
}

GfxResourceEntry *gfxResourceCopyEntry(GfxResourceEntry *dst, s16 resourceId, s16 entryIndex) {
    *dst = gfxResourceFindById(resourceId)->unk8[entryIndex];
    return dst;
}

f32 func_806FDA8C(s16 resourceId) {
    return gfxResourceFindById(resourceId)->unk18;
}

void func_806FDAB8(s16 resourceId, f32 timer) {
    gfxResourceFindById(resourceId)->unk18 = timer;
}

void heapFree(void *);

void gfxResourceFree(s16 resourceId) {
    GfxResourceNode *cur;
    GfxResourceNode *prev;

    cur = gGfxResourceList;
    prev = NULL;
    if ((cur != NULL) && (resourceId != cur->unk1C)) {
loop_2:
        prev = cur;
        cur = cur->next;
        if ((cur != NULL) && (resourceId != cur->unk1C)) {
            goto loop_2;
        }
    }
    if (prev != NULL) {
        prev->next = cur->next;
    } else {
        gGfxResourceList = cur->next;
    }
    heapFree(cur->unk4);
    heapFree(cur->unk8);
    heapFree(cur);
}

void _strcpy(s32, s32);
extern u8 D_8074450C;
s32 randomNonNegative();
s32 strlen(char *);
void *heapAlloc(s32);
void heapClearBlock(void *);
s16 textCountNonSpace(char *);

s16 gfxResourceCreate(s16 font, char *str, u8 mode, f32 posX, f32 posY, f32 posZ) {
    GfxResourceNode *node;
    GfxResourceNode *tail;
    GfxResourceEntry *entries;
    void *name;
    u8 count;
    s16 i;

    textGetStringWidth(font, (s32)str);
    node = heapAlloc(0x20);
    heapClearBlock(node);
    if (gGfxResourceList == NULL) {
        gGfxResourceList = node;
        node->next = NULL;
        gGfxResourceNextId = 0;
    } else {
        tail = gGfxResourceList;
        while (tail->next != NULL) {
            tail = tail->next;
        }
        tail->next = node;
        node->next = NULL;
    }
    node->unk1C = (s16)(gGfxResourceNextId & 0xFFFF);
    gGfxResourceNextId++;
    if (gGfxResourceNextId && gGfxResourceNextId) {
    }
    name = heapAlloc(strlen(str) + 1);
    node->unk4 = name;
    _strcpy((s32)name, (s32)str);
    count = textCountNonSpace(str);
    node->unkD = count;
    entries = heapAlloc(count * sizeof(GfxResourceEntry));
    node->unk8 = entries;
    heapClearBlock(entries);
    node->unkC = font;
    i = 0;
    if (node->unkD > 0) {
        do {
            if (mode == 3) {
                node->unk8[i].unk0 = (randomNonNegative() >> 15) % 1440 - 0x50;
                node->unk8[i].unk4 = (randomNonNegative() >> 15) % 1120 - 0x50;
                node->unk8[i].unk20 = (randomNonNegative() >> 15) % 6283 / 1000.0;
                node->unk14 = 0.1f;
            } else {
                node->unk8[i].unk0 = posX * 4.0f;
                node->unk8[i].unk4 = posY * 4.0f;
                node->unk8[i].unk8 = posZ * 4.0f;
                node->unk8[i].unk30 = (D_8074450C == 2) ? 1.0 : 0.1;
                node->unk14 = 0.2f;
            }
            i++;
        } while (i < node->unkD);
    }
    return node->unk1C;
}

void gfxResourceSetString(s16 resourceId, s32 str) {
    _strcpy((s32)gfxResourceFindById(resourceId)->unk4, str);
}

s16 mathAngleEaseToward(s16, s16, f32);

void func_806FDF54(f32 *pAngle, f32 *pTarget) {
    if (*pTarget < 0.0f) {
        do {
            *pTarget += 6.2831855f;
        } while (*pTarget < 0.0f);
    }
    if (*pTarget >= 6.2831855f) {
        do {
            *pTarget -= 6.2831855f;
        } while (*pTarget >= 6.2831855f);
    }
    *pAngle = (f32)((f64)((f32)mathAngleEaseToward((s16)(s32)(((f64)*pAngle * 2048.0) / 3.1415927410125732), (s16)(s32)(((f64)*pTarget * 2048.0) / 3.1415927410125732), 5.0f) * 3.1415927410125732f) * 0.00048828125);
}

typedef struct GfxResourceNodeView {
    struct GfxResourceNodeView *next;
    u8 *unk4;
    GfxResourceEntry *unk8;
    u8 unkC;
    u8 unkD;
    u8 padE[2];
    f32 unk10;
    f32 unk14;
    f32 unk18;
    s16 unk1C;
} GfxResourceNodeView;

extern u8 D_80754A37[];
extern s32 hudCanRender();
extern s16 textGetCharAdvance(s16, s32);
extern Gfx *textObjectDrawFlat(Gfx *, GfxResourceNodeView *);
extern Gfx *textObjectDrawRotated(Gfx *, GfxResourceNodeView *);
f32 sinApprox(f32);
f32 cosApprox(f32);

Gfx *textDrawAnimated(Gfx *glist, s16 resourceId, s32 animMode, f32 baseX, f32 baseY, f32 baseZ, f32 scale) {
    GfxResourceNodeView *node;
    f32 phase;
    f32 curX;
    f32 centeredX;
    f32 waveRadius;
    s16 charIndex;
    s16 strPos;
    s32 interpolatePos;
    f32 phaseStep;
    s32 interpolateScale;
    s32 ch;

    strPos = 0;
    curX = baseX;
    node = (GfxResourceNodeView *)gfxResourceFindById(resourceId);
    charIndex = 0;
    centeredX = ((f32)gScreenWidth - ((f32)textGetStringWidth(node->unkC, (s32)node->unk4) * scale)) / 2 + -3;
    waveRadius = (f32)(gScreenWidth >> 3);
    phase = node->unk10;
    phaseStep = 6.2831855f / (f32)node->unkD;
    interpolatePos = 1;
    interpolateScale = 1;
    strPos = 1;
    ch = node->unk4[0];
    while (ch != 0) {
        if (ch != 0x20) {
            u32 glyph;
            u8 glyphAdv;
            u8 glyphAdvFull;
            s32 halfAdv;
            u8 halfAdvByte;

            glyph = textGetCharAdvance(node->unkC, ch) * scale;
            glyphAdv = glyph;
            glyphAdvFull = glyph;
            halfAdv = glyphAdv / 2;
            halfAdvByte = halfAdv;
            switch (animMode) {
                case 8:
                    node->unk8[charIndex].unkC = ((f32)halfAdvByte + curX) * 4.0f;
                    node->unk8[charIndex].unk10 = baseY * 4.0f;
                    curX += (f32)glyphAdvFull;
                    node->unk8[charIndex].unk34 = (f32)((f64)sinApprox(node->unk18) * 0.5 + scale);
                    if (node->unk18 > 0.0f) {
                        node->unk18 = (f32)((f64)node->unk18 - 0.1);
                    } else {
                        node->unk18 = 0.0f;
                    }
                    break;
                case 6:
                    interpolatePos = 0;
                    interpolateScale = 0;
                    node->unk8[charIndex].unk0 = (curX + 20.0f) * 4.0f;
                    node->unk8[charIndex].unk4 = baseY * 4.0f;
                    curX += 28.0f;
                    node->unk8[charIndex].unk20 = (f32)((f64)sinApprox(node->unk18) * 0.35);
                    node->unk8[charIndex].unk30 = 1.5f;
                    break;
                case 5:
                    interpolatePos = 0;
                    interpolateScale = 0;
                    node->unk8[charIndex].unk0 = ((f32)halfAdvByte + centeredX) * 4.0f;
                    node->unk8[charIndex].unk4 = baseY * 4.0f;
                    centeredX += (f32)glyphAdvFull;
                    node->unk8[charIndex].unk20 = 0.0f;
                    node->unk8[charIndex].unk30 = (f32)((f64)sinApprox(phase) * 0.05 + 1.0);
                    phase += phaseStep;
                    node->unk10 = (f32)((f64)node->unk10 + 0.1);
                    break;
                case 4:
                    node->unk8[charIndex].unkC = ((f32)(u8)halfAdv + centeredX) * 4.0f;
                    node->unk8[charIndex].unk10 = baseY * 4.0f;
                    centeredX += (f32)glyphAdv;
                    node->unk8[charIndex].unk34 = 1.0f;
                    break;
                case 3:
                    node->unk8[charIndex].unkC = ((f32)halfAdvByte + centeredX) * 4.0f;
                    node->unk8[charIndex].unk10 = baseY * 4.0f;
                    centeredX += (f32)glyphAdvFull;
                    node->unk8[charIndex].unk2C = 0.0f;
                    node->unk8[charIndex].unk34 = (f32)((f64)sinApprox(phase) * 0.3 + 1.2);
                    phase += phaseStep;
                    node->unk10 = (f32)((f64)node->unk10 + 0.04);
                    break;
                case 1:
                    phase -= (f32)halfAdvByte * 0.013f;
                    node->unk8[charIndex].unkC = (sinApprox(phase) * waveRadius + curX) * 4.0f;
                    node->unk8[charIndex].unk10 = (cosApprox(phase) * waveRadius + baseY) * 4.0f;
                    node->unk8[charIndex].unk2C = 3.1415927f - phase;
                    phase -= (f32)glyphAdvFull * 0.013f;
                    break;
                case 2:
                    node->unk8[charIndex].unkC = ((f32)halfAdvByte + centeredX) * 4.0f;
                    node->unk8[charIndex].unk10 = (f32)(((f64)sinApprox(phase * 2) * 5.0 + baseY) * 4.0);
                    centeredX += (f32)glyphAdvFull;
                    phase += phaseStep;
                    node->unk8[charIndex].unk20 = (f32)((f64)sinApprox(phase * 2) * 0.5);
                    node->unk10 = (f32)((f64)node->unk10 - 0.01);
                    node->unk8[charIndex].unk34 = scale;
                    break;
                case 9:
                    node->unk8[charIndex].unkC = curX - (f32)(halfAdvByte * 4);
                    node->unk8[charIndex].unk10 = baseY;
                    node->unk8[charIndex].unk14 = baseZ;
                    curX -= (f32)(glyphAdvFull * 4);
                    phase += phaseStep;
                    node->unk8[charIndex].unk34 = (f32)((f64)sinApprox(phase) * (0.2 * scale) + scale);
                    node->unk8[charIndex].unk2C = 3.1415927f;
                    node->unk10 = (f32)((f64)node->unk10 - 0.08);
                    break;
                case 10:
                    node->unk8[charIndex].unkC = curX;
                    node->unk8[charIndex].unk10 = baseY;
                    node->unk8[charIndex].unk14 = (f32)glyphAdvFull + baseZ;
                    baseZ += (f32)(glyphAdvFull * 4);
                    phase += phaseStep;
                    node->unk8[charIndex].unk34 = (f32)((f64)sinApprox(phase) * (0.2 * scale) + scale);
                    node->unk8[charIndex].unk24 = 1.5707964f;
                    node->unk8[charIndex].unk28 = -1.5707964f;
                    node->unk8[charIndex].unk2C = 0.0f;
                    node->unk10 = (f32)((f64)node->unk10 - 0.08);
                    break;
            }
            if (interpolatePos != 0) {
                node->unk8[charIndex].unk0 = node->unk8[charIndex].unk0 + (node->unk8[charIndex].unkC - node->unk8[charIndex].unk0) * node->unk14;
                node->unk8[charIndex].unk4 = node->unk8[charIndex].unk4 + (node->unk8[charIndex].unk10 - node->unk8[charIndex].unk4) * node->unk14;
                node->unk8[charIndex].unk8 = node->unk8[charIndex].unk8 + (node->unk8[charIndex].unk14 - node->unk8[charIndex].unk8) * node->unk14;
                func_806FDF54(&node->unk8[charIndex].unk18, &node->unk8[charIndex].unk24);
                func_806FDF54(&node->unk8[charIndex].unk1C, &node->unk8[charIndex].unk28);
                func_806FDF54(&node->unk8[charIndex].unk20, &node->unk8[charIndex].unk2C);
            }
            if (interpolateScale != 0) {
                node->unk8[charIndex].unk30 = node->unk8[charIndex].unk30 + (node->unk8[charIndex].unk34 - node->unk8[charIndex].unk30) * node->unk14;
            }
            charIndex += 1;
        } else {
            switch (animMode) {
                case 1:
                    phase -= (f32)D_80754A37[node->unkC * 6] * 0.013f;
                    break;
                case 2:
                case 3:
                case 4:
                case 5:
                case 8:
                    centeredX += (f32)D_80754A37[node->unkC * 6];
                    break;
                case 6:
                    curX += 32.0f;
                    break;
                case 10:
                    baseZ += (f32)D_80754A37[node->unkC * 6];
                    break;
                default:
                    curX += (f32)D_80754A37[node->unkC * 6];
                    break;
            }
            phase = (f32)((f64)phase - (f64)D_80754A37[node->unkC * 6] * 0.019);
        }
        if (phase < 0.0f) { phase += 6.2831855f; } ch = *(u8 *)(strPos + node->unk4); strPos += 1;
    }
    gDPPipeSync(glist++);
    gSPSetOtherMode(glist++, G_SETOTHERMODE_L, G_MDSFT_RENDERMODE, 29, 0x00504240);
    switch (animMode) {
        case 9:
        case 10:
            return textObjectDrawRotated(glist, node);
        case 0xFF:
            node->unk10 = (f32)((f64)node->unk10 + 0.04);
            return textObjectDrawRotated(glist, node);
        case 8:
            if (hudCanRender() == 0) {
                return glist;
            }
            break;
        case 1:
            node->unk10 = (f32)((f64)node->unk10 + 0.02);
            break;
    }
    node->unk10 = (f32)((f64)node->unk10 + 0.04);
    return textObjectDrawFlat(glist, node);
}
