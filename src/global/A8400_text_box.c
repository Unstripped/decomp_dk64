#include "common.h"
#include "actor.h"
#include "resqueue.h"
#include "sched.h"
#include "proto/global/100180_text_font.h"
#include "proto/global/103AB0_view_effects.h"
#include "proto/global/112080_resource_parse.h"
#include "proto/global/119370_effect_grid.h"
#include "proto/global/15050_heap.h"
#include "proto/global/166A0_random.h"
#include "proto/global/17B90_anim_controller.h"
#include "proto/global/201B0_camera.h"
#include "proto/global/70FD0_collision_geometry.h"
#include "proto/global/90D80_render_callbacks.h"
#include "proto/global/A8400_text_box.h"

// This TU's .data (0x807503F0-0x807503F1 + 15-byte TU pad).
u8 sTextBoxStartAlpha = 0xB4;

void textBoxRowStartHook(Actor *key, void *data) {
}

extern u8 gGfxBufferIndex;
extern const u16 sTextBoxGlyphStrInit[];


void textBoxRenderNode(Gfx **gdl, ResQueueActorState *state, ResRow *row, ResGlyph *glyph) {
    union { u16 h; u8 b; u8 text[8]; } str;
    f32 mtx[4][4];
    f32 tmp[4][4];
    f32 angle;
    f32 halfW;
    f32 halfH;
    Gfx *dl;
    ResGlyphText *text;
    f32 scale;

    dl = *gdl;
    str.h = sTextBoxGlyphStrInit[0];
    text = &glyph->text;
    guMtxIdentF(mtx);
    if ((text->attr != 0) && (glyph->fade != 0)) {
        halfW = glyph->width * 0.5f * 4.0f;
        halfH = row->height * 0.5f * 4.0f;
        guTranslateF(tmp, -halfW, -halfH, 0.0f);
        guMtxCatF(mtx, tmp, mtx);
        text->animPhase += 0.418879032135009766;
        if ((text->attr & 8) != 0) {
            angle = text->animPhase * 0.5;
            if (angle <= 6.2831855f) {
                guRotateF(tmp, angle * 57.295776f, 0.0f, 0.0f, 1.0f);
                guMtxCatF(mtx, tmp, mtx);
            }
        }
        if ((text->attr & 4) != 0) {
            angle = text->animPhase;
            if (angle <= 6.2831855f) {
                scale = sinApprox(angle - 1.5707964f) + 1.0f;
                scale = 0.25f * scale + 1.0f;
            } else {
                scale = 1.0f;
            }
            guScaleF(tmp, scale, scale, 1.0f);
            guMtxCatF(mtx, tmp, mtx);
        }
        if ((text->attr & 2) != 0) {
            f32 jitterX;
            f32 jitterY;
            jitterX = (4.0f * sinApprox(text->animPhase)) * ((20.0f - ((randomNonNegative() >> 15) % 40)) / 20.0f);
            jitterY = (4.0f * sinApprox(text->animPhase)) * ((20.0f - ((randomNonNegative() >> 15) % 40)) / 20.0f);
            guTranslateF(tmp, jitterX, jitterY, 0.0f);
            guMtxCatF(mtx, tmp, mtx);
        }
        guTranslateF(tmp, halfW, halfH, 0.0f);
        guMtxCatF(mtx, tmp, mtx);
    }
    guScaleF(tmp, 1.0, 1.0, 1.0);
    guMtxCatF(mtx, tmp, mtx);
    guTranslateF(tmp, ((f64) state->box[0] + glyph->x) * 4.0, ((f64) state->box[1] + glyph->y) * 4.0, 0.0f);
    guMtxCatF(mtx, tmp, mtx);
    guMtxF2L(mtx, (Mtx *) text->mtx[gGfxBufferIndex]);
    gSPMatrix(dl++, text->mtx[gGfxBufferIndex], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gDPPipeSync(dl++);
    gDPSetPrimColor(dl++, 0, 0, 0x28, 0x28, 0xFF, glyph->alpha);
    str.b = text->code;
    *gdl = textDrawStringVtx(dl, 6, 0, 0, str.text, 0);
}


void renderAppendNodeChain(Gfx **gdl, ResQueueActorState *state, ResRow *row, u8 isLast, u8 *stop) {
    Gfx *dl;
    s32 i;
    ResGlyph *glyph;

    dl = *gdl;
    glyph = row->glyphs;
    i = 0;
    while (glyph != NULL && *stop == 0) {
        if (isLast && (i == state->glyphCursor)) {
            *stop = 1;
        }
        if (row->kind & 1) {
            textBoxRenderNode(&dl, state, row, glyph);
        }
        glyph = glyph->next;
        i++;
    }
    *gdl = dl;
}

Gfx *renderTextureSprite(Gfx *dl, Mtx *mtx, u8 alpha, s32 frame) {
    void *tex;

    tex = texCacheFindOrLoad(frame + 0x52);
    gDPPipeSync(dl++);
    gDPSetPrimColor(dl++, 0, 0, 0xFF, 0xFF, 0xFF, alpha);
    gSPMatrix(dl++, mtx, G_MTX_PUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gfxDrawTexturedTileGridSimple(&dl, tex, 3, 0x60, 0x40, 0x20, 0x20, 0.0f, 0.0f, 96.0f, 64.0f, 0.0f, 0.0f, 1, 8);
    gSPPopMatrix(dl++, G_MTX_MODELVIEW);
    gDPPipeSync(dl++);
    return dl;
}


void mathAddWaveOffset(f32 *x, f32 *y, f32 t, f32 amp, ResQueueActorState *state) {
    *x += (t * amp) * 24.0f * mathSinF((s16) (state->waveAngleX + t * 3000.0f) & 0xFFF);
    *y += (t * amp) * 16.0f * mathCosF((s16) (state->waveAngleY + t * 3000.0f) & 0xFFF);
}

Gfx *textBoxRenderTail(Gfx *dl, ResQueueActorState *state, s32 frame) {
    f32 mtx[4][4];
    f32 step[4][4];
    f32 x;
    f32 y;
    u8 count;
    u8 i;

    count = ((state->openProgress < 0.32) ? state->openProgress : 0.32) * 12.5;
    for (i = 1; i <= count; i++) {
        x = (state->targetX - state->anchorX) * (i * 0.08) + state->anchorX;
        y = (state->targetY - state->anchorY) * (i * 0.08) + state->anchorY;
        guTranslateF(mtx, -48.0f, -32.0f, 0);
        guScaleF(step, i * 0.08 * 1.9f * 4.0 * 0.5, i * 0.08 * 1.9f * 4.0 * 0.5, 1.0f);
        guMtxCatF(mtx, step, mtx);
        mathAddWaveOffset(&x, &y, i * 0.08, 1.0f, state);
        guTranslateF(step, x * 4.0f, y * 4.0f, 0.0f);
        guMtxCatF(mtx, step, mtx);
        guMtxF2L(mtx, &state->mtxBuf[i * 2 + gGfxBufferIndex]);
        dl = renderTextureSprite(dl, &state->mtxBuf[i * 2 + gGfxBufferIndex], ((i * 300 * 0.08) > 150.0) ? 150.0 : (i * 300 * 0.08), frame);
    }
    return dl;
}

extern PlayerStruct *gPlayerSlots;
extern u8 gCurrentPlayerIndex;
extern Gfx D_1000118;
extern Mtx D_20000C0;

Gfx *textBoxRender(Gfx *gdl, Actor *actor) {
    /* pad* are unused slots above the live locals; with scale/alpha/isLast
       (register-allocated, kept above dl so they cost no below-dl slot) they
       reproduce the original stack frame (0x148, dl 0x98, start 0x94, tmp 0xA0,
       mtx 0xE0, frame 0x132, stop 0x13B). */
    s32 padA;
    f32 alpha;
    f32 padH;
    u8 stop;
    s16 padC;
    f32 scale;
    s16 frame;
    f64 padE;
    Gfx *padF;
    u8 isLast;
    f32 mtx[4][4];
    f32 tmp[4][4];
    s32 padN;
    Gfx *dl;
    Gfx *start;
    ResQueueActorState *state;
    ResRow *row;
    s32 i;

    state = actor->customState;
    row = state->rows;
    stop = 0;
    dl = heapAlloc(0x4000);
    heapFreeDeferred(dl);
    start = dl;
    gSPDisplayList(dl++, &D_1000118);
    gSPMatrix(dl++, &D_20000C0, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
    gDPPipeSync(dl++);
    gSPSetOtherMode(dl++, G_SETOTHERMODE_L, G_MDSFT_RENDERMODE, 29, 0x504240);
    gDPSetCycleType(dl++, G_CYC_1CYCLE);
    gDPSetCombine(dl++, 0x119623, 0xFF2FFFFF);
    gSPClearGeometryMode(dl++, 0xFFFFFFFF);
    gSPSetGeometryMode(dl++, G_SHADE | G_SHADING_SMOOTH);
    frame = state->animFrame / 2;
    scale = (1.0 - state->waveAmp * 0.5) * state->openProgress * 1.9f * 4.0;
    guTranslateF(mtx, -48.0f, -32.0f, 0.0f);
    guScaleF(tmp, scale, scale, 1.0f);
    guMtxCatF(mtx, tmp, mtx);
    guTranslateF(tmp, actor->x * 4.0f, actor->y * 4.0f, 0.0f);
    guMtxCatF(mtx, tmp, mtx);
    guMtxF2L(mtx, &state->mtxBuf[gGfxBufferIndex]);
    gDPPipeSync(dl++);
    gDPSetScissor(dl++, G_SC_NON_INTERLACE, gPlayerSlots->rect[0], gPlayerSlots->rect[1], gPlayerSlots->rect[2], gPlayerSlots->rect[3]);
    dl = textBoxRenderTail(dl, state, frame);
    alpha = (state->openProgress * 150.0f * 2 > 150.0f) ? 150.0f : state->openProgress * 150.0f * 2;
    dl = renderTextureSprite(dl, &state->mtxBuf[gGfxBufferIndex], alpha, frame);
    if (state->textAlpha != 0) {
        gDPPipeSync(dl++);
        gDPSetScissor(dl++, G_SC_NON_INTERLACE, state->box[0], state->box[1], state->box[2], state->box[3]);
    }
    i = 0;
    while ((state->rowState >= i) && (row != NULL) && (stop == 0)) {
        isLast = (i == state->rowState);
        gDPPipeSync(dl++);
        renderAppendNodeChain(&dl, state, row, isLast, &stop);
        if (!stop) {
            row = row->next;
        }
        i++;
    }
    gDPPipeSync(dl++);
    if (state->textAlpha != 0) {
        gDPSetScissor(dl++, G_SC_NON_INTERLACE, gPlayerSlots[gCurrentPlayerIndex].rect[0], gPlayerSlots[gCurrentPlayerIndex].rect[1],
                      gPlayerSlots[gCurrentPlayerIndex].rect[2], gPlayerSlots[gCurrentPlayerIndex].rect[3]);
    }
    state->animFrame++;
    state->animFrame %= 16;
    gSPEndDisplayList(dl++);
    gSPDisplayList(gdl++, start);
    return gdl;
}

extern EffectGridAsset *gEffectGridAssets[];

void textBoxRowUpdateIcon(ResGlyph *glyph, ResRow *row, ResQueueActorState *state) {
    ResGlyphCell *cell = &glyph->cell;
    f32 halfW = glyph->width * 0.5f;
    f32 x = glyph->x;
    f32 y = glyph->y;

    if (cell->effect == NULL) {
        effectSetDuration(-1);
        effectSetDepth(0);
        effectSetScreenSpace();
        effectSetFrameDelay(2);
        effectSetBounds(state->box[0], state->box[1], state->box[2], state->box[3]);
        cell->effect = effectCreateAtPosition(gEffectGridAssets[cell->effectId], 1.0f, state->box[0], state->box[1], 1);
        if (cell->flip != 0) {
            cell->effect->scaleX *= -1.0f;
        }
    }
    x += halfW;
    cell->effect->x = ((f64) state->box[0] + x) * 4.0;
    cell->effect->y = ((f64) state->box[1] + (y + row->height * 0.5f)) * 4.0;
    cell->effect->alpha = glyph->alpha;
    cell->effect->minX = state->box[0];
    cell->effect->minY = state->box[1];
    cell->effect->maxX = state->box[2];
    cell->effect->maxY = state->box[3];
}

void textBoxRowUpdateGlyphs(f32 y, Actor *actor, ResQueueActorState *state, ResRow *row, u8 isLast, u8 *stop) {
    f32 x;
    s32 step;
    s32 i;
    u8 alpha;
    u8 fade;
    ResGlyph *glyph;

    glyph = row->glyphs;
    i = 0;
    x = ((f64) 136.8f - row->width) / 2.0;
    while (glyph != NULL && *stop == 0) {
        if (isLast && i == state->glyphCursor) {
            if (!(state->inputFlags & 4)) {
                *stop = 1;
            }
            if (actor->state == 1) {
                if (i == 0 && glyph->fade == 0) {
                    textBoxRowStartHook(state->key, row->data);
                }
                fade = glyph->fade;
                if (fade != 0xFF) {
                    step = 0x96;
                    if (state->inputFlags & 2) {
                        step *= 0.5;
                    }
                    if (!(state->inputFlags & 4) && (step < (0xFF - glyph->fade))) { // FAKE: re-reads glyph->fade (here and in the += below) while fade holds it: one lbu at 0x157c kept in v1; reading fade here, or no fade local, changes regalloc (fdiff 1)
                        glyph->fade += step;
                    } else {
                        glyph->fade = 0xFF;
                        if (glyph->next != NULL) {
                            state->glyphCursor++;
                        } else {
                            state->glyphCursor = 0;
                            state->rowState++;
                            *stop = 1;
                            if (row->timer != 0) {
                                actor->state = 3;
                                state->holdTimer = row->timer;
                            }
                        }
                    }
                }
            }
        }
        if (state->textAlpha < glyph->fade) {
            alpha = state->textAlpha;
        } else {
            alpha = glyph->fade;
        }
        glyph->x = x;
        glyph->y = y;
        glyph->alpha = alpha;
        if (row->kind & 2) {
            textBoxRowUpdateIcon(glyph, row, state);
        }
        x += glyph->width;
        glyph = glyph->next;
        i++;
    }
}




void textBoxUpdateRows(Actor *actor) {
    ResQueueActorState *state;
    ResRow *row;
    ResRow *cur;
    u8 stop;
    u8 pad[0x90];
    f32 rowY;
    f32 rowHeight;
    f32 amp;
    s16 mode;
    u8 isLast;
    s32 i;

    state = actor->customState;
    row = state->rows;
    stop = 0;
    amp = (1.0f - state->openProgress) * 1.47058823529411775;
    if (amp > 1.0f) {
        amp = 1.0f;
    }
    state->waveAmp = amp;
    mathAddWaveOffset(&actor->x, &actor->y, state->openProgress, amp, state);
    state->box[0] = actor->x - (state->openProgress * 136.8f) * 0.5;
    state->box[1] = actor->y - (state->openProgress * 79.799995f) * 0.5;
    state->box[2] = actor->x + (state->openProgress * 136.8f) * 0.5;
    state->box[3] = actor->y + (state->openProgress * 79.799995f) * 0.5;
    state->box[0] = (gPlayerSlots->rect[0] < state->box[0]) ? state->box[0] : gPlayerSlots->rect[0];
    state->box[1] = (gPlayerSlots->rect[1] < state->box[1]) ? state->box[1] : gPlayerSlots->rect[1];
    state->box[2] = (state->box[2] < gPlayerSlots->rect[2]) ? state->box[2] : gPlayerSlots->rect[2];
    state->box[3] = (state->box[3] < gPlayerSlots->rect[3]) ? state->box[3] : gPlayerSlots->rect[3];
    rowY = state->scrollY;
    i = 0;
    while ((state->rowState >= i) && (row != NULL) && (stop == 0)) {
        isLast = (i == state->rowState);
        rowHeight = row->height;
        if ((rowY + rowHeight > 73.79999542236328) && (actor->state == 1)) {
            actor->state = 2;
            state->scrollLeft = rowY + rowHeight - 73.79999542236328;
            stop = 1;
        } else if ((rowY + rowHeight < 0.0f) && (actor->state == 2)) {
            state->scrollY += rowHeight;
            state->rows = row->next;
            state->rowState--;
            i--;
            rowY += rowHeight;
            cur = row;
            row = row->next;
            resNodeFree(cur);
        } else {
            textBoxRowUpdateGlyphs(rowY, actor, state, row, isLast, &stop);
            if (stop == 0) {
                row = row->next;
                rowY += rowHeight;
            }
        }
        i++;
    }
    mode = actor->state;
    switch (mode) {
        case 3:
            if (state->holdTimer != 0) {
                state->holdTimer--;
                mode = actor->state; // ORIG: the target reloads actor->state in this arm only (lbu v0,340(s3) at +0x350, after the holdTimer sb at +0x348); the else arm uses the stored 1 (andi at +0x33c)
            } else {
                mode = actor->state = 1;
            }
            break;
    }
    if ((mode == 1) && (row == NULL)) {
        resQueueProcessNext(actor, state->key);
    }
}

extern s16 gScreenWidth;

#define CLAMP_TO_BOUNDS(x, l, h) ((x) < (l) ? (l) : ((h) < (x) ? (h) : (x)))

void textBoxUpdatePosition(Actor *actor, ResQueueActorState *state, f32 step) {
    f32 screenX, screenY;
    s32 nodeIndex;
    ScriptedActorState *script;
    s32 pad;
    f32 posX, posY, posZ;

    nodeIndex = 0;
    switch (state->key->actorType) {
    case 0x22:
    case 0x2E:
    case 0x7C:
    case 0x7D:
    case 0x7E:
    case 0x7F:
    case 0xDA:
    case 0x100:
        state->anchorFixed = 1;
        state->anchorX = gPlayerSlots[gCurrentPlayerIndex].rect[2];
        state->anchorY = gPlayerSlots[gCurrentPlayerIndex].rect[3];
        break;
    case 0xFE:
        script = ((ScriptedActor *)state->key)->scriptState;
        nodeIndex = script->anchorNode;
        break;
    default:
        if (state->key->animState != NULL) {
            switch (controllerLookupModelAssetId(state->key)) {
            case 0x11:
            case 0x12:
            case 0x1D:
            case 0x1F:
            case 0x2E:
            case 0x3D:
            case 0x45:
            case 0x5E:
            case 0x62:
                nodeIndex = 1;
                break;
            case 0x13:
            case 0x17:
            case 0x3E:
            case 0x56:
            case 0x65:
                nodeIndex = 2;
                break;
            case 0x35:
                nodeIndex = 3;
                break;
            case 0x1:
            case 0x2:
            case 0x3:
            case 0x4:
            case 0x5:
            case 0x6:
            case 0x7:
            case 0x8:
            case 0xA:
            case 0xB:
            case 0xC:
            case 0xD:
            case 0xE:
            case 0xF:
            case 0x10:
                nodeIndex = 6;
                break;
            case 0x18:
                nodeIndex = 9;
                break;
            }
        }
        break;
    }
    if ((state->key->animState == NULL) && (state->anchorFixed == 0)) {
        state->anchorFixed = 1;
        state->anchorX = gPlayerSlots[gCurrentPlayerIndex].rect[0];
        state->anchorY = gPlayerSlots[gCurrentPlayerIndex].rect[1];
    }
    if (state->anchorFixed == 0) {
        if (nodeIndex == 0) {
            posX = state->key->x;
            posY = state->key->y + 1.5 * state->key->eyeHeight;
            posZ = state->key->z;
        } else {
            actorGetNodePos(state->key, nodeIndex, &posX, &posY, &posZ);
        }
        if (camProjectToScreen(posX, posY, posZ, &screenX, &screenY, 0, 1.0f, gCurrentPlayerIndex) != 0) {
            screenX = state->anchorX;
            screenY = state->anchorY;
        }
        screenX = CLAMP_TO_BOUNDS(screenX, gPlayerSlots[gCurrentPlayerIndex].rect[0] - 0x64, gPlayerSlots[gCurrentPlayerIndex].rect[2] + 0x64);
        screenY = CLAMP_TO_BOUNDS(screenY, gPlayerSlots[gCurrentPlayerIndex].rect[1] - 0x64, gPlayerSlots[gCurrentPlayerIndex].rect[3] + 0x64);
        state->anchorX = screenX;
        state->anchorY = screenY;
    }
    screenX = state->anchorX;
    screenY = state->anchorY;
    if ((gScreenWidth * 0.5f) < screenX) {
        screenX -= 131.1999969482421875;
    } else {
        screenX += 131.1999969482421875;
    }
    if (screenY > 60.7999992370605469) {
        screenY -= 60.7999992370605469;
    }
    screenX = CLAMP_TO_BOUNDS(screenX, gPlayerSlots[gCurrentPlayerIndex].rect[0] + 91.1999969482421875 + 5.0,
                              gPlayerSlots[gCurrentPlayerIndex].rect[2] - 96.1999969482421875);
    screenY = CLAMP_TO_BOUNDS(screenY, gPlayerSlots[gCurrentPlayerIndex].rect[1] + 60.7999992370605469 + 5.0,
                              gPlayerSlots[gCurrentPlayerIndex].rect[3] - 65.7999992370605469);
    state->targetX = ((screenX - state->targetX) * step) + state->targetX;
    state->targetY = ((screenY - state->targetY) * step) + state->targetY;
    actor->x = (((state->targetX - state->anchorX) * state->openProgress) + state->anchorX);
    actor->y = (((state->targetY - state->anchorY) * state->openProgress) + state->anchorY);
}

void renderCalcChainCenterOffset(ResQueueActorState *state) {
    ResRow *row;
    s32 total;

    total = 0;
    row = state->rows;
    if (row == NULL) {
        return;
    }
    if (row->glyphs->fade != 0) {
        return;
    }
    while (row != NULL) {
        total += row->height;
        row = row->next;
    }
    if (total < 79.7999954223632812) {
        state->scrollY = (79.7999954223632812 - total) * 0.5;
    } else {
        state->scrollY = 6.0f;
    }
}

extern Actor *gCurrentActor;
extern u16 gButtonsPressed;


void textBoxUpdate(void) {
    ResQueueActorState *state;
    f32 stepSize;
    f32 speed;

    state = gCurrentActor->customState;
    stepSize = 0.05f;
    if (!(gCurrentActor->flags & 0x10)) {
        stepSize = 1.0f;
        state->mtxBuf = heapAlloc(0x280);
        state->inputFlags = 0;
    } else if (!(state->inputFlags & 1) && gCurrentActor->state != 4 && gCurrentActor->state != 5 && state->openTimer > 15.0) {
        if (gButtonsPressed & 0x4000) {
            state->inputFlags |= 1;
        }
        if (gContPadCur.button & 0x2000) {
            state->inputFlags |= 2;
        } else {
            state->inputFlags &= ~2;
        }
        if (!(state->inputFlags & 2) && gContPadCur.button == 0x8000) {
            state->inputFlags |= 4;
        } else {
            state->inputFlags &= ~4;
        }
        if (state->inputFlags & 1) {
            camResumePath();
            gCurrentActor->state = 5;
        }
    }
    state->waveAngleX += 0x14;
    state->waveAngleY += 0x32;
    switch (gCurrentActor->state) {
    case 0:
        if (state->openTimer < 0x1E) {
            state->openTimer++;
        } else {
            gCurrentActor->state = 1;
            state->textAlpha = sTextBoxStartAlpha;
            resQueueProcessNext(gCurrentActor, state->key);
            renderCalcChainCenterOffset(state);
        }
        break;
    case 2:
        speed = 2.0f;
        if (state->inputFlags & 4) {
            speed *= 3.0f;
        } else if (state->inputFlags & 2) {
            speed *= 0.5f;
        }
        if (!(speed < state->scrollLeft)) {
            speed = state->scrollLeft;
        }
        state->scrollY -= speed;
        state->scrollLeft -= speed;
        if (state->scrollLeft < 0.0001) {
            gCurrentActor->state = 1;
        }
        break;
    case 4:
        if (state->textAlpha) {
            state->textAlpha -= (state->textAlpha >= 0x34) ? 0x33 : state->textAlpha;
        } else if (state->openTimer != 0) {
            if (state->rows != NULL) {
                resNodeListFree(state);
            }
            state->openTimer--;
        } else {
            gCurrentActor->state = 5;
        }
        break;
    case 5:
        resQueueRemove(state->key);
        break;
    }
    if (gCurrentActor->state != 5) {
        state->openProgress = state->openTimer * 0.033333335f;
        textBoxUpdatePosition(gCurrentActor, state, stepSize);
        if (state->openTimer != 0) {
            textBoxUpdateRows(gCurrentActor);
            renderCallbacksRegister(textBoxRender, gCurrentActor, 3);
        }
    }
}

const u16 sTextBoxGlyphStrInit[4] = { 0 };
