#include "common.h"
#include "actor.h"
#include "text.h"
#define PROTO_SKIP_textGetCharAdvance // FAKE: callee prototype steer
#define PROTO_SKIP_textGetStringWidth // FAKE: callee prototype steer
#include "proto/boot/3630.h"
#include "proto/global/100180.h"
#include "proto/global/1025E0.h"
#include "proto/global/15050.h"
#include "proto/global/166A0.h"
#include "proto/global/450.h"
#include "proto/global/CEAE0.h"

extern Actor *gCurrentActor;
extern Actor *gSpawnedActor;
extern Actor *gActivePlayerActor;
extern Actor *gPrimaryPlayerActor;
extern void *gPlayerSlots;
extern u8 gPlayerCount;
extern u8 gCurrentPlayerIndex;
extern u8 gPlayerInventoryTable[][0x5E];
extern s32 gCurrentMap;
extern u8 gCurrentWorldId;
extern u8 gScreenRenderFlags;
extern s16 gScreenWidth;
extern s16 gScreenHeight;
extern u8 gNextGameMode;
extern u8 gGfxBufferIndex;

extern s32 textGetStringWidth(s16, s32); // FAKE: callee prototype steer

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

extern TextObject *gGfxResourceList;
extern s16 gGfxResourceNextId;

void gfxResourceListReset(void) {
    gGfxResourceList = NULL;
    gGfxResourceNextId = 0;
}

TextObject *gfxResourceFindById(s16 resourceId) {
    TextObject *node;

    node = gGfxResourceList;
    while ((node != NULL) && (resourceId != node->id)) {
        node = node->next;
    }
    return node;
}

TextObjectElem *gfxResourceCopyEntry(TextObjectElem *dst, s16 resourceId, s16 entryIndex) {
    *dst = gfxResourceFindById(resourceId)->elems[entryIndex];
    return dst;
}

f32 func_806FDA8C(s16 resourceId) {
    return gfxResourceFindById(resourceId)->timer;
}

void func_806FDAB8(s16 resourceId, f32 timer) {
    gfxResourceFindById(resourceId)->timer = timer;
}


void gfxResourceFree(s16 resourceId) {
    TextObject *cur;
    TextObject *prev;

    cur = gGfxResourceList;
    prev = NULL;
    while ((cur != NULL) && (resourceId != cur->id)) {
        prev = cur;
        cur = cur->next;
    }
    if (prev != NULL) {
        prev->next = cur->next;
    } else {
        gGfxResourceList = cur->next;
    }
    heapFree(cur->text);
    heapFree(cur->elems);
    heapFree(cur);
}

extern u8 gHiResScale;

s16 gfxResourceCreate(s16 font, void *str, u8 mode, f32 posX, f32 posY, f32 posZ) {
    TextObject *node;
    TextObject *tail;
    TextObjectElem *entries;
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
    node->id = (s16)(gGfxResourceNextId & 0xFFFF);
    gGfxResourceNextId++;
    if (gGfxResourceNextId && gGfxResourceNextId) {
    }
    name = heapAlloc(strlen(str) + 1);
    node->text = name;
    _strcpy((s32)name, (s32)str);
    count = textCountNonSpace(str);
    node->count = count;
    entries = heapAlloc(count * sizeof(TextObjectElem));
    node->elems = entries;
    heapClearBlock(entries);
    node->font = font;
    i = 0;
    if (node->count > 0) {
        do {
            if (mode == 3) {
                node->elems[i].x = (randomNonNegative() >> 15) % 1440 - 0x50;
                node->elems[i].y = (randomNonNegative() >> 15) % 1120 - 0x50;
                node->elems[i].rotZ = (randomNonNegative() >> 15) % 6283 / 1000.0;
                node->easeRate = 0.1f;
            } else {
                node->elems[i].x = posX * 4.0f;
                node->elems[i].y = posY * 4.0f;
                node->elems[i].z = posZ * 4.0f;
                node->elems[i].scale = (gHiResScale == 2) ? 1.0 : 0.1;
                node->easeRate = 0.2f;
            }
            i++;
        } while (i < node->count);
    }
    return node->id;
}

void gfxResourceSetString(s16 resourceId, s32 str) {
    _strcpy((s32)gfxResourceFindById(resourceId)->text, str);
}


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

extern TextFontInfo gTextFonts[];
extern s16 textGetCharAdvance(s16, s32); // FAKE: callee prototype steer
f32 sinApprox(f32);
f32 cosApprox(f32);

Gfx *textDrawAnimated(Gfx *glist, s16 resourceId, s32 animMode, f32 baseX, f32 baseY, f32 baseZ, f32 scale) {
    TextObject *node;
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
    node = gfxResourceFindById(resourceId);
    charIndex = 0;
    centeredX = (gScreenWidth - textGetStringWidth(node->font, (s32)node->text) * scale) / 2 + -3;
    waveRadius = gScreenWidth >> 3;
    phase = node->phase;
    phaseStep = 6.2831855f / node->count;
    interpolatePos = 1;
    interpolateScale = 1;
    strPos = 1;
    ch = node->text[0];
    while (ch != 0) {
        if (ch != 0x20) {
            u8 glyphAdv;
            u8 halfAdv;

            glyphAdv = textGetCharAdvance(node->font, ch) * scale;
            halfAdv = glyphAdv / 2;
            switch (animMode) {
                case 8:
                    node->elems[charIndex].targetX = (halfAdv + curX) * 4.0f;
                    node->elems[charIndex].targetY = baseY * 4.0f;
                    curX += glyphAdv;
                    node->elems[charIndex].targetScale = sinApprox(node->timer) * 0.5 + scale;
                    if (node->timer > 0.0f) {
                        node->timer -= 0.1;
                    } else {
                        node->timer = 0.0f;
                    }
                    break;
                case 6:
                    interpolatePos = 0;
                    interpolateScale = 0;
                    node->elems[charIndex].x = (curX + 20.0f) * 4.0f;
                    node->elems[charIndex].y = baseY * 4.0f;
                    curX += 28.0f;
                    node->elems[charIndex].rotZ = sinApprox(node->timer) * 0.35;
                    node->elems[charIndex].scale = 1.5f;
                    break;
                case 5:
                    interpolatePos = 0;
                    interpolateScale = 0;
                    node->elems[charIndex].x = (halfAdv + centeredX) * 4.0f;
                    node->elems[charIndex].y = baseY * 4.0f;
                    centeredX += glyphAdv;
                    node->elems[charIndex].rotZ = 0.0f;
                    node->elems[charIndex].scale = sinApprox(phase) * 0.05 + 1.0;
                    phase += phaseStep;
                    node->phase += 0.1;
                    break;
                case 4:
                    node->elems[charIndex].targetX = (halfAdv + centeredX) * 4.0f;
                    node->elems[charIndex].targetY = baseY * 4.0f;
                    centeredX += glyphAdv;
                    node->elems[charIndex].targetScale = 1.0f;
                    break;
                case 3:
                    node->elems[charIndex].targetX = (halfAdv + centeredX) * 4.0f;
                    node->elems[charIndex].targetY = baseY * 4.0f;
                    centeredX += glyphAdv;
                    node->elems[charIndex].targetRotZ = 0.0f;
                    node->elems[charIndex].targetScale = sinApprox(phase) * 0.3 + 1.2;
                    phase += phaseStep;
                    node->phase += 0.04;
                    break;
                case 1:
                    phase -= halfAdv * 0.013f;
                    node->elems[charIndex].targetX = (sinApprox(phase) * waveRadius + curX) * 4.0f;
                    node->elems[charIndex].targetY = (cosApprox(phase) * waveRadius + baseY) * 4.0f;
                    node->elems[charIndex].targetRotZ = 3.1415927f - phase;
                    phase -= glyphAdv * 0.013f;
                    break;
                case 2:
                    node->elems[charIndex].targetX = (halfAdv + centeredX) * 4.0f;
                    node->elems[charIndex].targetY = (sinApprox(phase * 2) * 5.0 + baseY) * 4.0;
                    centeredX += glyphAdv;
                    phase += phaseStep;
                    node->elems[charIndex].rotZ = sinApprox(phase * 2) * 0.5;
                    node->phase -= 0.01;
                    node->elems[charIndex].targetScale = scale;
                    break;
                case 9:
                    node->elems[charIndex].targetX = curX - halfAdv * 4;
                    node->elems[charIndex].targetY = baseY;
                    node->elems[charIndex].targetZ = baseZ;
                    curX -= glyphAdv * 4;
                    phase += phaseStep;
                    node->elems[charIndex].targetScale = sinApprox(phase) * (0.2 * scale) + scale;
                    node->elems[charIndex].targetRotZ = 3.1415927f;
                    node->phase -= 0.08;
                    break;
                case 10:
                    node->elems[charIndex].targetX = curX;
                    node->elems[charIndex].targetY = baseY;
                    node->elems[charIndex].targetZ = glyphAdv + baseZ;
                    baseZ += glyphAdv * 4;
                    phase += phaseStep;
                    node->elems[charIndex].targetScale = sinApprox(phase) * (0.2 * scale) + scale;
                    node->elems[charIndex].targetRotX = 1.5707964f;
                    node->elems[charIndex].targetRotY = -1.5707964f;
                    node->elems[charIndex].targetRotZ = 0.0f;
                    node->phase -= 0.08;
                    break;
            }
            if (interpolatePos != 0) {
                node->elems[charIndex].x = node->elems[charIndex].x + (node->elems[charIndex].targetX - node->elems[charIndex].x) * node->easeRate;
                node->elems[charIndex].y = node->elems[charIndex].y + (node->elems[charIndex].targetY - node->elems[charIndex].y) * node->easeRate;
                node->elems[charIndex].z = node->elems[charIndex].z + (node->elems[charIndex].targetZ - node->elems[charIndex].z) * node->easeRate;
                func_806FDF54(&node->elems[charIndex].rotX, &node->elems[charIndex].targetRotX);
                func_806FDF54(&node->elems[charIndex].rotY, &node->elems[charIndex].targetRotY);
                func_806FDF54(&node->elems[charIndex].rotZ, &node->elems[charIndex].targetRotZ);
            }
            if (interpolateScale != 0) {
                node->elems[charIndex].scale = node->elems[charIndex].scale + (node->elems[charIndex].targetScale - node->elems[charIndex].scale) * node->easeRate;
            }
            charIndex += 1;
        } else {
            switch (animMode) {
                case 1:
                    phase -= gTextFonts[node->font].spaceWidth * 0.013f;
                    break;
                case 2:
                case 3:
                case 4:
                case 5:
                case 8:
                    centeredX += gTextFonts[node->font].spaceWidth;
                    break;
                case 6:
                    curX += 32.0f;
                    break;
                case 10:
                    baseZ += gTextFonts[node->font].spaceWidth;
                    break;
                default:
                    curX += gTextFonts[node->font].spaceWidth;
                    break;
            }
            phase -= gTextFonts[node->font].spaceWidth * 0.019;
        }
        if (phase < 0.0f) { phase += 6.2831855f; } ch = *(strPos + node->text); strPos += 1; // FAKE: index-first spelling keeps the addu operand order
    }
    gDPPipeSync(glist++);
    gSPSetOtherMode(glist++, G_SETOTHERMODE_L, G_MDSFT_RENDERMODE, 29, 0x00504240);
    switch (animMode) {
        case 9:
        case 10:
            return textObjectDrawRotated(glist, node);
        case 0xFF:
            node->phase += 0.04;
            return textObjectDrawRotated(glist, node);
        case 8:
            if (hudCanRender() == 0) {
                return glist;
            }
            break;
        case 1:
            node->phase += 0.02;
            break;
    }
    node->phase += 0.04;
    return textObjectDrawFlat(glist, node);
}
