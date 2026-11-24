#include "common.h"
#include "compiler/ido/memory.h"
#include "actor.h"
#include "sched.h"
#include "render.h"
#include "proto/global/119370_effect_grid.h"
#include "proto/global/15050_heap.h"
#include "proto/global/166A0_random.h"
#include "proto/global/17800_matrix_rotation.h"
#include "proto/global/2F550_map_render.h"
#include "proto/global/35000_render_entry.h"
#include "proto/global/36880_model_slot.h"
#include "proto/global/450_main_loop.h"
#include "proto/global/55B20_map_chunk.h"
#include "proto/global/5E2F0_light.h"
#include "proto/global/69E60_actor_physics.h"
#include "proto/global/6AD90_collision.h"
#include "proto/global/70FD0_collision_geometry.h"

extern u8 gGfxBufferIndex;
extern u8 gViewportCount;
extern u8 gHiResScale;
extern PlayerStruct *gPlayerSlots;
extern Actor *gPrimaryPlayerActor;
extern u8 gRenderSetupKind;
extern void *gRenderLoadedTexture;
extern u8 gCurrentPlayerIndex;
extern s16 gScreenWidth;
extern s16 gScreenHeight;
extern Mtx D_2000000;
extern Mtx D_20000C0;
extern Mtx D_2000180;
extern Mtx D_2000200;

extern s16 sEffectScreenRotation;
extern EffectGridNode *sEffectGridHead;
extern EffectNode *sEffectListHead;
extern EffectNode *sEffectListTail;
extern u8 sEffectPendingColorR;
extern u8 sEffectPendingColorG;
extern u8 sEffectPendingColorB;
extern u8 sEffectPendingColorA;
extern s32 sEffectPendingDuration;
extern EffectCallback sEffectPendingCallback;
extern u8 sEffectPendingDepth;
extern s16 sEffectPendingStartDelay;
extern u8 sEffectPendingFrameDelay;
extern u8 sEffectPendingScreenSpace;
extern f32 sEffectPendingScaleX;
extern f32 sEffectPendingScaleY;
extern u8 sEffectPendingHasScale;
extern s32 sEffectPendingSpeed;
extern s32 sEffectPendingStartFrame;
extern u16 sEffectPendingFlags;
extern s16 sEffectPendingChunkFilter;
extern s16 sEffectPendingMaxDist;
extern s16 sEffectPendingBoundsMinX;
extern s16 sEffectPendingBoundsMinY;
extern s16 sEffectPendingBoundsMaxX;
extern s16 sEffectPendingBoundsMaxY;

// Effect sprite sheets (124780.c), in address order.
extern EffectGridAsset D_8071FA80, D_8071FAAC, D_8071FAD8, D_8071FAF0, gEffectSpriteSparklesBlue;
extern EffectGridAsset gEffectSpriteImpactFlash, gEffectSpriteBurstOrange, D_8071FB88, gEffectSpriteDustPuffBrown, gEffectSpriteBlast;
extern EffectGridAsset gEffectSpriteRing, gEffectSpriteWaterSplash, gEffectSpriteBubble, gEffectSpriteSparklePurple, gEffectSpriteSparkleYellow;
extern EffectGridAsset gEffectSpriteSparkleGreen, D_8071FCF4, D_8071FD50, D_8071FDAC, gEffectSpriteStarBurst;
extern EffectGridAsset D_8071FE3C, gEffectSpriteBarrelDebrisDark, gEffectSpriteBarrelDebrisLight, gEffectSpriteBarrelDebrisPlank, gEffectSpriteWaterRipple;
extern EffectGridAsset sEffectImpactPuffConfig, gEffectSpriteDustPuff, gEffectSpriteStar, gEffectSpriteSleepZ, D_8071FF70;
extern EffectGridAsset D_8071FF88, sEffectSparkConfig, gEffectSpriteMelonWobble, gEffectSpriteMelonSpin, gEffectSpriteGlowRed;
extern EffectGridAsset gSparkEffectSprite, gEffectSpritePeanut, gEffectSpriteMuzzleFlash, gEffectSpritePeanutShard, gEffectSpriteFireBurst;
extern EffectGridAsset gEffectSpriteSmokePuff, D_80720180, gEffectSpritePineapple, gEffectSpriteFlame, gEffectSpriteOrangeGrenade;
extern EffectGridAsset gEffectSpriteGrape, gEffectSpriteMelonSplat, gEffectSpriteFuseSpark, gEffectSpriteExplosion, gEffectSpriteEmber;
extern EffectGridAsset gEffectSpriteCoinRed, gEffectSpriteCoinGreen, gEffectSpriteCoinBlue, gEffectSpriteCoinYellow, gEffectSpriteCoinPurple;
extern EffectGridAsset D_80720464, gEffectSpriteFilm, gEffectSpriteOrange, gEffectSpriteCrystal, gEffectSpriteGoldenBanana;
extern EffectGridAsset gEffectSpriteBananaMedal, gEffectSpriteBananaRed, gEffectSpriteBananaGreen, gEffectSpriteBananaBlue, gEffectSpriteBananaYellow;
extern EffectGridAsset gEffectSpriteBananaPurple, D_80720630, D_80720690, gEffectSpriteCoconut, gEffectSpriteCoconutShard;
extern EffectGridAsset gEffectSpriteMelonSlice, gEffectSpriteShardGold, gEffectSpriteCrate, gEffectSpriteDkCoin, gEffectSpriteBlueprintBlue;
extern EffectGridAsset gEffectSpriteCannonball, D_80720830, gEffectSpriteFeather, gEffectSpriteGuitar, gEffectSpriteBongos;
extern EffectGridAsset gEffectSpriteSaxophone, gEffectSpriteTriangle, gEffectSpriteTrombone, gEffectSpriteNotePairYellow, gEffectSpriteNoteYellow;
extern EffectGridAsset gEffectSpriteNoteGreen, gEffectSpriteNotePairPink, gEffectSpriteNotePairRed, gEffectSpriteNoteRed, gEffectSpriteNotePairPaleBlue;
extern EffectGridAsset gEffectSpriteBlueprintRed, gEffectSpriteBlueprintGreen, gEffectSpriteBlueprintYellow, gEffectSpriteBlueprintPurple, gEffectSpriteGlintYellow;
extern EffectGridAsset D_80720AA0, D_80720AB8, D_80720AD0, D_80720AE8, gEffectSpriteCloud;
extern EffectGridAsset gEffectSpriteLightningArc, gEffectSpriteWaterDroplet, D_80720B70, D_80720B88, gEffectSpriteGrapeShard;
extern EffectGridAsset gEffectSpriteGlintBlue, gEffectSpriteSmokeCloud, gControlStickSprite, D_80720C64, gEffectSpriteWaterDrip;
extern EffectGridAsset gAButtonSprite, gBButtonSprite, gZButtonSprite, gCDownButtonSprite, gCUpButtonSprite;
extern EffectGridAsset D_80720DA4, D_80720DC8, gEffectSpriteBurstGreen, gEffectSpriteTargetRing, gEffectSpriteGooGreen;
extern EffectGridAsset D_80720E44, D_80720E5C, D_80720E74, D_80720E8C, D_80720EA4;
extern EffectGridAsset gEffectSpriteBananaBunchGreen, gEffectSpriteBananaBunchRed, gEffectSpriteBananaBunchBlue, gEffectSpriteBananaBunchYellow, gEffectSpriteBananaBunchPurple;
extern EffectGridAsset gEffectSpriteBananaBalloonGreen, gEffectSpriteBananaBalloonRed, gEffectSpriteBananaBalloonYellow, gEffectSpriteBananaBalloonBlue, gEffectSpriteBananaBalloonPurple;
extern EffectGridAsset gRButtonSprite, D_80721070, gFairySprite, gEffectSpriteKey, gCrownSprite;
extern EffectGridAsset gEffectSpriteRareCoin, gEffectSpriteNintendoCoin, gEffectSpriteNoSign, gEffectSpriteHeadphones, D_80721194;
extern EffectGridAsset gStartButtonSprite, gEffectSpriteQuestionMark, gEffectSpriteCandyHead, gEffectSpriteCrankyHead, gEffectSpriteSnideHead;
extern EffectGridAsset gEffectSpriteFunkyHead, gEffectSpriteArrow, gEffectSpriteTwinkle, gEffectSpriteDebrisGrey, gEffectSpriteDebrisGreen;
extern EffectGridAsset gEffectSpriteLeaf, D_80721300, D_80721318, D_80721330, D_80721358;
extern EffectGridAsset gEffectSpriteRainbowCoin, gEffectSpriteGlowOrange, D_807213D0, D_807213F4, effectAssetPathTrail;
extern EffectGridAsset D_8072142C, gEffectSpriteBarrelEnd, D_8072145C, gEffectSpriteBananaBunchRainbow, gEffectSpriteDkHead;
extern EffectGridAsset gEffectSpriteDiddyHead, gEffectSpriteLankyHead, gEffectSpriteTinyHead, gEffectSpriteChunkyHead, gCheckMarkSprite;
extern EffectGridAsset gEffectSpriteWrinkly;

// Effect asset per effect-grid id (read by A8400 and 112080).
EffectGridAsset *gEffectGridAssets[176] = {
    &D_8071FA80, &D_8071FAAC, &D_8071FAD8, &D_8071FAF0, &gEffectSpriteSparklesBlue, &gEffectSpriteImpactFlash,
    &gEffectSpriteBurstOrange, &D_8071FB88, &gEffectSpriteDustPuffBrown, &gEffectSpriteBlast, &gEffectSpriteRing, &gEffectSpriteWaterSplash,
    &gEffectSpriteBubble, &gEffectSpriteSparklePurple, &gEffectSpriteSparkleYellow, &gEffectSpriteSparkleGreen, &D_8071FCF4, &D_8071FD50,
    &D_8071FDAC, &gEffectSpriteStarBurst, &D_8071FE3C, &gEffectSpriteBarrelDebrisDark, &gEffectSpriteBarrelDebrisLight, &gEffectSpriteBarrelDebrisPlank,
    &gEffectSpriteWaterRipple, &sEffectImpactPuffConfig, &gEffectSpriteDustPuff, &gEffectSpriteStar, &gEffectSpriteSleepZ, &D_8071FF70,
    &D_8071FF88, &sEffectSparkConfig, &gEffectSpriteMelonWobble, &gEffectSpriteMelonSpin, &gEffectSpriteGlowRed, &gSparkEffectSprite,
    &gEffectSpritePeanut, &gEffectSpriteMuzzleFlash, &gEffectSpritePeanutShard, &gEffectSpriteFireBurst, &gEffectSpriteSmokePuff, &D_80720180,
    &gEffectSpritePineapple, &gEffectSpriteFlame, &gEffectSpriteOrangeGrenade, &gEffectSpriteGrape, &gEffectSpriteMelonSplat, &gEffectSpriteFuseSpark,
    &gEffectSpriteExplosion, &gEffectSpriteEmber, &gEffectSpriteCoinRed, &gEffectSpriteCoinGreen, &gEffectSpriteCoinBlue, &gEffectSpriteCoinYellow,
    &gEffectSpriteCoinPurple, &D_80720464, &gEffectSpriteFilm, &gEffectSpriteOrange, &gEffectSpriteCrystal, &gEffectSpriteGoldenBanana,
    &gEffectSpriteBananaMedal, &gEffectSpriteBananaRed, &gEffectSpriteBananaGreen, &gEffectSpriteBananaBlue, &gEffectSpriteBananaYellow, &gEffectSpriteBananaPurple,
    &D_80720630, &D_80720690, &gEffectSpriteCoconut, &gEffectSpriteCoconutShard, &gEffectSpriteMelonSlice, &gEffectSpriteShardGold,
    &gEffectSpriteCrate, &gEffectSpriteDkCoin, &gEffectSpriteBlueprintBlue, &gEffectSpriteCannonball, &D_80720830, &gEffectSpriteFeather,
    &gEffectSpriteGuitar, &gEffectSpriteBongos, &gEffectSpriteSaxophone, &gEffectSpriteTriangle, &gEffectSpriteTrombone, &gEffectSpriteNotePairYellow,
    &gEffectSpriteNoteYellow, &gEffectSpriteNoteGreen, &gEffectSpriteNotePairPink, &gEffectSpriteNotePairRed, &gEffectSpriteNoteRed, &gEffectSpriteNotePairPaleBlue,
    &gEffectSpriteBlueprintRed, &gEffectSpriteBlueprintGreen, &gEffectSpriteBlueprintYellow, &gEffectSpriteBlueprintPurple, &gEffectSpriteGlintYellow, &D_80720AA0,
    &D_80720AB8, &D_80720AD0, &D_80720AE8, &gEffectSpriteCloud, &gEffectSpriteLightningArc, &gEffectSpriteWaterDroplet,
    &D_80720B70, &D_80720B88, &gEffectSpriteGrapeShard, &gEffectSpriteGlintBlue, &gEffectSpriteSmokeCloud, &gControlStickSprite,
    &D_80720C64, &gEffectSpriteWaterDrip, &gAButtonSprite, &gBButtonSprite, &gZButtonSprite, &gCDownButtonSprite,
    &gCUpButtonSprite, &D_80720DA4, &D_80720DC8, &gEffectSpriteBurstGreen, &gEffectSpriteTargetRing, &gEffectSpriteGooGreen,
    &D_80720E44, &D_80720E5C, &D_80720E74, &D_80720E8C, &D_80720EA4, &gEffectSpriteBananaBunchGreen,
    &gEffectSpriteBananaBunchRed, &gEffectSpriteBananaBunchBlue, &gEffectSpriteBananaBunchYellow, &gEffectSpriteBananaBunchPurple, &gEffectSpriteBananaBalloonGreen, &gEffectSpriteBananaBalloonRed,
    &gEffectSpriteBananaBalloonYellow, &gEffectSpriteBananaBalloonBlue, &gEffectSpriteBananaBalloonPurple, &gRButtonSprite, &D_80721070, &gFairySprite,
    &gEffectSpriteKey, &gCrownSprite, &gEffectSpriteRareCoin, &gEffectSpriteNintendoCoin, &gEffectSpriteNoSign, &gEffectSpriteHeadphones,
    &D_80721194, &gStartButtonSprite, &gEffectSpriteQuestionMark, &gEffectSpriteCandyHead, &gEffectSpriteCrankyHead, &gEffectSpriteSnideHead,
    &gEffectSpriteFunkyHead, &gEffectSpriteArrow, &gEffectSpriteTwinkle, &gEffectSpriteDebrisGrey, &gEffectSpriteDebrisGreen, &gEffectSpriteLeaf,
    &D_80721300, &D_80721318, &D_80721330, &D_80721358, &gEffectSpriteRainbowCoin, &gEffectSpriteGlowOrange,
    &D_807213D0, &D_807213F4, &effectAssetPathTrail, &D_8072142C, &gEffectSpriteBarrelEnd, &D_8072145C,
    &gEffectSpriteBananaBunchRainbow, &gEffectSpriteDkHead, &gEffectSpriteDiddyHead, &gEffectSpriteLankyHead, &gEffectSpriteTinyHead, &gEffectSpriteChunkyHead,
    &gCheckMarkSprite, &gEffectSpriteWrinkly,
};


void effectResetLists(void) {
    sEffectGridHead = NULL;
    sEffectListHead = NULL;
    sEffectListTail = NULL;
    effectResetState();
}

EffectGridAsset *effectGridFindByTargetId(s32 targetId) {
    EffectGridNode *node = sEffectGridHead;

    while (node != NULL) {
        if (targetId == node->id) {
            return node->asset;
        }
        node = node->next;
    }
    return sEffectGridHead->asset;
}

void effectGridGetByteDimensions(EffectGridAsset *asset, u8 *outW, u8 *outH) {
    *outW = asset->width;
    *outH = asset->height;
}

void effectGridGetCellDimensions(EffectGridAsset *asset, s16 *outCellW, s16 *outCellH) {
    *outCellW = asset->cellW;
    *outCellH = asset->cellH;
}

void effectGridGetScaledDimensions(EffectGridAsset *asset, s16 *outScaledW, s16 *outScaledH) {
    s16 pad0;
    s16 pad1;
    u8 byteW;
    u8 byteH;

    effectGridGetByteDimensions(asset, &byteW, &byteH);
    effectGridGetCellDimensions(asset, outScaledW, outScaledH);
    *outScaledW *= byteW;
    *outScaledH *= byteH;
}

void effectGridRegister(EffectGridAsset *asset) {
    EffectGridNode *last;
    EffectGridNode *node;
    s32 pad;
    s32 count;
    s32 i;

    last = NULL;
    for (node = sEffectGridHead; node != NULL; node = node->next) {
        last = node;
        if (asset == node->asset) {
            return;
        }
    }

    node = heapAlloc(sizeof(EffectGridNode));
    node->next = NULL;
    node->asset = asset;
    node->id = asset->id;
    effectGridGetByteDimensions(asset, &node->width, &node->height);
    node->format = asset->format;
    node->size = asset->size;
    node->red = asset->red;
    node->green = asset->green;
    node->blue = asset->blue;
    node->alpha = asset->alpha;
    node->unlit = asset->unlit;
    node->altCategory = asset->altCategory;
    effectGridGetCellDimensions(asset, &node->cellW, &node->cellH);
    node->frameCount = asset->frameCount;
    node->lastUsedFrame = -1;

    if (sEffectGridHead != NULL) {
        last->next = node;
    } else {
        sEffectGridHead = node;
    }

    count = node->width * node->height * node->frameCount;
    node->slots = heapAlloc(count * sizeof(EffectGridSlot));
    for (i = 0; i < count; i++) {
        node->slots[i].frame = -1;
    }
    node->data = asset->data;
}

void effectSetStartFrame(s32 param) {
    sEffectPendingStartFrame = param;
}

void effectSetSpeed(s32 initSpeed) {
    sEffectPendingSpeed = initSpeed;
}

void effectSetScreenSpace(void) {
    sEffectPendingScreenSpace = 1;
}

void effectSetStartDelay(s16 delay) {
    sEffectPendingStartDelay = delay;
}

void effectSetScreenRotation(s16 degrees) {
    sEffectScreenRotation = degrees;
}

void effectSetCallback(void *callback) {
    sEffectPendingCallback = (EffectCallback)callback;
}

void effectSetFrameDelay(u8 frameDelay) {
    sEffectPendingFrameDelay = frameDelay;
}

void effectSetMaxDistance(s16 maxDistance) {
    sEffectPendingMaxDist = maxDistance;
}

void effectSetDepth(u8 depth) {
    sEffectPendingDepth = depth;
}

void effectSetColor(u8 r, u8 g, u8 b, u8 a) {
    sEffectPendingColorR = r;
    sEffectPendingColorG = g;
    sEffectPendingColorB = b;
    sEffectPendingColorA = a;
}

void effectSetDuration(s32 duration) {
    sEffectPendingDuration = duration;
}

void effectSetScale(f32 scaleX, f32 scaleY) {
    sEffectPendingScaleX = scaleX;
    sEffectPendingScaleY = scaleY;
    sEffectPendingHasScale = 1;
}

void effectSetFlags(s16 flags) {
    sEffectPendingFlags = flags;
}

void effectFlagsOr(u8 flagBits) {
    sEffectPendingFlags |= flagBits;
}

void effectSetChunkFilter(s16 chunk) {
    sEffectPendingChunkFilter = chunk;
}

void effectSetBounds(s16 minX, s16 minY, s16 maxX, s16 maxY) {
    sEffectPendingBoundsMinX = minX;
    sEffectPendingBoundsMinY = minY;
    sEffectPendingBoundsMaxX = maxX;
    sEffectPendingBoundsMaxY = maxY;
}

void effectResetState(void) {
    s32 minBound;

    sEffectPendingColorA = 0;
    sEffectPendingDuration = 1;
    sEffectPendingCallback = NULL;
    sEffectPendingDepth = 0;
    sEffectPendingFrameDelay = 1;
    sEffectPendingStartDelay = 0;
    sEffectPendingScreenSpace = 0;
    sEffectPendingHasScale = 0;
    minBound = gHiResScale * 10;
    sEffectPendingSpeed = 0;
    sEffectPendingStartFrame = 0;
    sEffectPendingFlags = 0;
    sEffectPendingChunkFilter = -1;
    sEffectPendingBoundsMinX = minBound;
    sEffectPendingBoundsMinY = minBound;
    sEffectPendingBoundsMaxX = gHiResScale * 309;
    sEffectPendingBoundsMaxY = gHiResScale * 229;
    sEffectPendingMaxDist = 600;
}


void effectCreateAtModelNode(void *asset, f32 scale, s32 modelSlot, s32 nodeIndex, u8 anchorType) {
    f32 nodeX;
    f32 nodeY;
    f32 nodeZ;

    modelSlotGetNodePos(modelSlot, 1, nodeIndex, &nodeX, &nodeY, &nodeZ);
    effectCreate(asset, scale, nodeX, nodeY, nodeZ, NULL, modelSlot, nodeIndex, anchorType);
}


EffectNode *effectCreateAtActorBone(void *asset, f32 scale, Actor *actor, s32 boneIndex, u8 anchorType) {
    f32 boneX;
    f32 boneY;
    f32 boneZ;

    actorGetNodePos(actor, boneIndex, &boneX, &boneY, &boneZ);
    if (!(actor->flags & 0x200) && actor->sub4 != NULL && (sEffectPendingFlags & 0x80)) {
        effectFlagsOr(0x40);
    }
    return effectCreate(asset, scale, boneX, boneY, boneZ, actor, 0, boneIndex, anchorType);
}

EffectNode *effectCreateAtPosition(void *asset, f32 scale, f32 x, f32 y, f32 z) {
    return effectCreate(asset, scale, x, y, z, NULL, 0, 0, 0);
}

EffectNode *effectCreate(EffectGridAsset *asset, f32 scale, f32 posX, f32 posY, f32 posZ, Actor *owner, s32 modelSlot, s32 nodeIndex, u8 anchorType) {
    EffectNode *effect;
    EffectGridNode *node;
    s32 found;
    s32 i;

    effectGridRegister(asset);
    node = sEffectGridHead;
    found = 0;
    while (!found && node != NULL) {
        if (node->asset == asset) {
            found = 1;
        } else {
            node = node->next;
        }
    }
    if (!found) {
        effectResetState();
        return NULL;
    }
    effect = heapAlloc(sizeof(EffectNode));
    if (sEffectListHead != NULL) {
        sEffectListTail->next = effect;
        effect->previous = sEffectListTail;
    } else {
        sEffectListHead = effect;
        effect->previous = NULL;
    }
    sEffectListTail = effect;
    if (sEffectPendingScreenSpace != 0) {
        posX *= 4.0f;
        posY *= 4.0f;
        posZ *= 4.0f;
        scale *= 4.0f;
        sEffectPendingScaleX *= 4.0f;
        sEffectPendingScaleY *= 4.0f;
    }
    effect->x = posX;
    effect->y = posY;
    effect->z = posZ;
    if (sEffectPendingHasScale != 0) {
        effect->scaleX = sEffectPendingScaleX;
        effect->scaleY = sEffectPendingScaleY;
    } else {
        effect->scaleX = scale;
        effect->scaleY = scale;
    }
    if (sEffectPendingColorA != 0) {
        effect->red = sEffectPendingColorR;
        effect->green = sEffectPendingColorG;
        effect->blue = sEffectPendingColorB;
        effect->alpha = sEffectPendingColorA;
    } else {
        effect->red = node->red;
        effect->green = node->green;
        effect->blue = node->blue;
        effect->alpha = node->alpha;
    }
    effect->depth = sEffectPendingDepth;
    effect->mode = sEffectPendingScreenSpace;
    effect->startDelay = sEffectPendingStartDelay;
    effect->frameCount = node->width * node->height;
    effect->anchorType = anchorType;
    effect->owner = owner;
    effect->boneIndex = modelSlot;
    effect->subIndex = nodeIndex;
    effect->param = sEffectPendingStartFrame;
    effect->frameDelay = sEffectPendingFrameDelay;
    effect->frameTimer = 0;
    effect->duration = sEffectPendingDuration;
    effect->durationTimer = 0;
    effect->speed = sEffectPendingSpeed;
    if (gGlobalOverlayFlags & 0x100) {
        effect->maxDistance = 2000;
    } else {
        effect->maxDistance = sEffectPendingMaxDist;
    }
    effect->grid = node;
    effect->next = NULL;
    effect->callback = sEffectPendingCallback;
    effect->allocation = NULL;
    effect->chunkFilter = sEffectPendingChunkFilter;
    effect->chunk = -1;
    effect->flags = sEffectPendingFlags;
    effect->minX = sEffectPendingBoundsMinX;
    effect->minY = sEffectPendingBoundsMinY;
    effect->maxX = sEffectPendingBoundsMaxX;
    effect->maxY = sEffectPendingBoundsMaxY;
    for (i = 0; i < gViewportCount; i++) {
        effect->displayLists[i][0] = heapAlloc(0x200);
        effect->displayLists[i][1] = heapAlloc(0x200);
    }
    effect->viewportCount = gViewportCount;
    effectBuildGridVertices(effect);
    effectResetState();
    return effect;
}


void effectBuildGridVertices(EffectNode *effect) {
    EffectGridNode *node;
    Vtx *vertex;
    s32 column;
    s32 row;
    s32 vertexIndex;
    s32 startX;
    s32 x;
    s32 y;

    node = effect->grid;
    vertexIndex = 0;
    if (node->width == 0 || node->height == 0) {} // FAKE: numbers the width then height ucvt webs first (a1, a2)
    node = effect->grid; // FAKE: kill splits the width/height webs so they reload in the arms
    x = -(node->width * node->cellW) / 2;
    startX = x; // FAKE: redundant alias of x; numbers the width ucvt ahead of startX (Q1426)
    if (effect->mode == 0) {
        y = -(node->height * node->cellH) / 2;
    } else {
        y = (node->height * node->cellH) / 2;
    }
    for (row = 0; row < node->height; row++) {
        x = startX;
        column = 0;
        if (node->width > 0) {
            vertex = effect->vertices + vertexIndex;
            do {
                vertex->v.ob[0] = x;
                vertex->v.ob[1] = y;
                vertex->v.ob[2] = 0;
                vertex->v.tc[0] = 0;
                vertex->v.tc[1] = 0;
                vertexIndex++;
                vertex++;
                vertex->v.ob[0] = x + node->cellW;
                vertex->v.ob[1] = y;
                vertex->v.ob[2] = 0;
                vertex->v.tc[0] = node->cellW << 5;
                vertex->v.tc[1] = 0;
                vertexIndex++;
                vertex++;
                vertex->v.ob[0] = x;
                if (effect->mode == 0) {
                    vertex->v.ob[1] = y + node->cellH;
                } else {
                    vertex->v.ob[1] = y - node->cellH;
                }
                vertex->v.ob[2] = 0;
                vertex->v.tc[0] = 0;
                vertex->v.tc[1] = node->cellH << 5;
                vertexIndex++;
                vertex++;
                vertex->v.ob[0] = x + node->cellW;
                if (effect->mode == 0) {
                    vertex->v.ob[1] = y + node->cellH;
                } else {
                    vertex->v.ob[1] = y - node->cellH;
                }
                vertex->v.ob[2] = 0;
                vertex->v.tc[0] = node->cellW << 5;
                vertex->v.tc[1] = node->cellH << 5;
                vertexIndex++;
                vertex++;
                x += node->cellW;
                column++;
            } while (column < node->width);
        }
        if (effect->mode == 0) {
            y += node->cellH;
        } else {
            y -= node->cellH;
        }
    }
}

void effectUpdateAll(u8 paused) {
    EffectNode *effect;
    u8 isDone;
    EffectGridNode *grid;
    s32 i;

    for (effect = sEffectListHead; effect != NULL; effect = effect->next) {
        if (effect->startDelay == 0) {
            effect->state = 0;
            effect->freePending = 0;
            effect->displayListIndex = 0;
            effect->grid->lastUsedFrame = gFrameCounter;
            effect->flags &= ~0x10;
            switch (effect->anchorType) {
            case 1:
                modelSlotGetNodePos(effect->boneIndex, 1, effect->subIndex, &effect->x, &effect->y, &effect->z);
                break;
            case 2:
                if ((effect->owner->flags & 0x200) != 0 || effect->owner->sub4 == NULL) {
                    actorGetNodePos(effect->owner, effect->subIndex, &effect->x, &effect->y, &effect->z);
                } else {
                    effect->flags |= 0x10;
                }
                break;
            }
            isDone = 0;
            if (!paused || (effect->flags & 1)) {
                if (effect->callback != NULL) {
                    effect->callback(effect, &isDone);
                }
            } else if (effect->callback != NULL) {
                for (i = 0; i < gViewportCount; i++) {
                    if (gPlayerSlots[i].active != 0) {
                        memcpy(&effect->matrices[i][gGfxBufferIndex], &effect->matrices[i][gGfxBufferIndex ^ 1], sizeof(Mtx));
                    }
                }
                effect->state = 3;
            }
            if (effect->param == effect->grid->frameCount) {
                effect->param = 0;
                effect->durationTimer++;
                if (effect->durationTimer == effect->duration && effect->duration != -1) {
                    effect->freePending = 1;
                }
            }
            if (isDone != 0) {
                effect->freePending = 1;
            }
            if (effect->freePending != 0) {
                effectFreeAndUnlink(effect);
            } else {
                for (i = 1; i < gViewportCount; i++) {
                    if (gPlayerSlots[i].active != 0) {
                        memcpy(&effect->matrices[i][gGfxBufferIndex], &effect->matrices[0][gGfxBufferIndex], sizeof(Mtx));
                    }
                }
                if (effect->state != 3) {
                    for (i = 0; i < gViewportCount; i++) {
                        if (gPlayerSlots[i].active != 0) {
                            effectComputeTransformMatrix(&effect->matrices[i][gGfxBufferIndex], effect->state,
                                                         effect->scaleX, effect->scaleY,
                                                         gPlayerSlots[i].eyeX, gPlayerSlots[i].eyeY, gPlayerSlots[i].eyeZ,
                                                         effect->x, effect->y, effect->z, effect->mode);
                        }
                    }
                    effect->state = 3;
                }
                if (effect->mode == 0) {
                    s32 listIndex;
                    if (effect->flags & 4) {
                        listIndex = 4;
                        if (!(effect->flags & 8)) {
                            effect->chunk = mapChunkFindByPosition(effect->x, effect->y, effect->z, 0);
                        }
                    } else {
                        listIndex = 1;
                    }
                    renderEntryAddOrUpdate(0, 5, effect, effect->x, effect->y, effect->z, effect->maxDistance, 0, 1, -1, listIndex);
                } else {
                    renderEntryAddOrUpdate(0, 5, effect, effect->x, effect->y, effect->z, 0, 0, 1, -1, 3);
                }
                effectLoadFrameAssets(effect->grid->data, effect->grid->altCategory, effect->grid->slots,
                                      effect->frameCount, effect->param, effect->frames);
                if (!paused || (effect->flags & 1)) {
                    effect->frameTimer++;
                    if (effect->frameTimer == effect->frameDelay) {
                        effect->param++;
                        effect->frameTimer = 0;
                    }
                }
            }
            effect->flags |= 8;
        } else if (!paused || (effect->flags & 1)) {
            effect->startDelay--;
        }
    }
    for (grid = sEffectGridHead; grid != NULL; grid = grid->next) {
        if (gFrameCounter - grid->lastUsedFrame <= 10 && grid->lastUsedFrame != -1) {
            for (i = 0; i < grid->frameCount * grid->width * grid->height; i++) {
                if (grid->slots[i].frame != -1) {
                    if (gFrameCounter - grid->lastUsedFrame == 10) {
                        assetFreeBuffer(grid->slots[i].buffer, 0x319, 0x1F);
                        grid->slots[i].frame = -1;
                    }
                }
            }
        }
    }
}


void effectFreeByOwner(Actor *owner) {
    EffectNode *effect;

    for (effect = sEffectListHead; effect != NULL; effect = effect->next) {
        if (owner == effect->owner) {
            effectFreeAndUnlink(effect);
        }
    }
}

void effectFreeAll(void) {
    EffectNode *effect;
    EffectNode *next;

    effect = sEffectListHead;
    while (effect != NULL) {
        next = effect->next;
        effectFreeAndUnlink(effect);
        effect = next;
    }
}


void effectFreeAndUnlink(EffectNode *effect) {
    void *allocation;
    s32 i;
    u8 found;
    EffectNode *previous;
    EffectNode *next;

    if (effect->mode == 0) {
        if (effect->flags & 4) {
            renderEntryRemove(NULL, effect, 4, &found);
        } else {
            renderEntryPurgeObject(effect);
        }
    } else {
        renderEntryRemove(NULL, effect, 3, &found);
    }
    allocation = effect->allocation;
    if (allocation != NULL) {
        heapFreeDeferred(allocation);
    }
    for (i = 0; i < effect->viewportCount; i++) {
        heapFreeDeferred(effect->displayLists[i][0]);
        heapFreeDeferred(effect->displayLists[i][1]);
    }
    if (osCicId != 6105) { // not the cartridge's CIC-NUS-6105: scramble the OS clock
        osSetTime((s32)randomLcgNext());
    }
    previous = effect->previous;
    next = effect->next;
    heapFreeDeferred(effect);
    if (previous != NULL) {
        previous->next = next;
    } else {
        sEffectListHead = next;
    }
    if (next != NULL) {
        next->previous = previous;
    } else {
        sEffectListTail = previous;
    }
}

void effectLoadFrameAssets(s16 *assetIds, u8 altCategory, EffectGridSlot *slots, s32 count, s32 frame, void **outFrames) {
    u8 category;
    s32 i;
    s32 index;
    void *buffer;

    index = count * frame;
    for (i = 0; i < count; i++) {
        if (slots[index + i].frame == -1) {
            if (altCategory) {
                category = 0x19;
            } else {
                category = 7;
            }
            buffer = assetLoad(category, assetIds[index + i], 0, 0);
            outFrames[i] = buffer;
            slots[index + i].buffer = buffer;
        } else {
            outFrames[i] = slots[index + i].buffer;
        }
        slots[index + i].frame = frame;
    }
}


void effectComputeTransformMatrix(Mtx *dst, u8 state, f32 scaleX, f32 scaleY, f32 camX, f32 camY, f32 camZ, f32 x, f32 y, f32 z, u8 mode) {
    f32 sine;
    f32 yaw;
    f32 distance;
    f32 divisor;
    f32 absSine;
    s32 angle;
    s32 asinAngle;
    f32 matrix[4][4];
    f32 transform[4][4];
    Mtx mtx;

    if (mode == 0) {
        distance = distance3D(camX, camY, camZ, x, y, z);
        divisor = distance;
        if (distance < 0.1) {
            divisor = 1.0f;
        }
        sine = (camY - y) / divisor;
        if (sine > 0.0f) {
            absSine = sine;
        } else {
            absSine = -sine;
        }
        asinAngle = mathAsinFixed(absSine * 65536.0) >> 4;
        angle = asinAngle;
        if (sine >= 0.0f) {
            angle = 0xFFF - asinAngle;
        }
        if (state != 2) {
            guScaleF(matrix, scaleX, scaleY, 0.0f);
        } else {
            guScaleF(matrix, 1.0f, 1.0f, 1.0f);
        }
        guRotateF(transform, angle / 4095.0 * 360.0, 1.0f, 0.0f, 0.0f);
        guMtxCatF(matrix, transform, matrix);
        yaw = mathAngleBetweenPointsRad(camX, camZ, x, z);
        guRotateF(transform, yaw * 57.295776f, 0.0f, 1.0f, 0.0f);
        guMtxCatF(matrix, transform, matrix);
        guTranslateF(transform, x, y, z);
        guMtxCatF(matrix, transform, matrix);
    } else {
        if (state != 2) {
            guScaleF(matrix, scaleX, scaleY, 0.0f);
        } else {
            guScaleF(matrix, 1.0f, 1.0f, 1.0f);
        }
        matrixMakeRotationZ(transform, sEffectScreenRotation);
        guMtxCatF(matrix, transform, matrix);
        guTranslateF(transform, x, y, z);
        guMtxCatF(matrix, transform, matrix);
    }
    if (state == 1 || state == 2) {
        guMtxF2L(matrix, &mtx);
        guMtxCatL(dst, &mtx, dst);
    } else {
        guMtxF2L(matrix, dst);
    }
}

f32 distance3D(f32 x1, f32 y1, f32 z1, f32 x2, f32 y2, f32 z2) {
    f32 x;
    f32 y;
    f32 z;

    x = x1 - x2;
    y = y1 - y2;
    z = z1 - z2;
    return sqrtf((x * x) + (y * y) + (z * z));
}

Gfx *effectGridBuildDisplayList(EffectNode *effect, Gfx *inGlist, s16 chunk) {
    s32 i;
    u8 red;
    u8 green;
    u8 blue;
    f32 colorRed = 1.0f;
    f32 colorGreen = 1.0f;
    f32 colorBlue = 1.0f;
    Gfx *glist;

    if (effect->flags & 0x50) {
        return inGlist;
    }
    if (((gPrimaryPlayerActor->state == 0x83 || gPrimaryPlayerActor->state == 0x67) && !(effect->flags & 0x20)) ||
        ((gGlobalPauseFlags & 0x100002) == 0x100002 && !(effect->flags & 0x100))) {
        return inGlist;
    }
    if (chunk == -1) {
        chunk = effect->chunk;
    }
    if (effect->chunkFilter != -1) {
        if (effect->mode != 0) {
            if (mapChunkContainsPoint(effect->x * 0.25, effect->y * 0.25, effect->chunkFilter) == 0) {
                return inGlist;
            }
        } else if (chunk != effect->chunkFilter) {
            return inGlist;
        }
    }
    glist = effect->displayLists[effect->displayListIndex][gGfxBufferIndex];
    effect->displayListIndex++;
    gSPDisplayList(inGlist++, osVirtualToPhysical(glist));
    gDPPipeSync(glist++);
    gDPSetCycleType(glist++, G_CYC_1CYCLE);
    gSPClearGeometryMode(glist++, 0xFFFFFFFF);
    gDPSetColorDither(glist++, G_CD_DISABLE);
    if (effect->depth != 0) {
        gSPSetGeometryMode(glist++, G_ZBUFFER | G_SHADE | G_SHADING_SMOOTH);
        gSPSetOtherMode(glist++, G_SETOTHERMODE_L, G_MDSFT_RENDERMODE, 29, 0x504B50);
    } else {
        gSPSetGeometryMode(glist++, G_SHADE | G_SHADING_SMOOTH);
        gSPSetOtherMode(glist++, G_SETOTHERMODE_L, G_MDSFT_RENDERMODE, 29, 0x504240);
    }
    gSPTexture(glist++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON);
    gDPSetCombine(glist++, 0x119623, 0xFF2FFFFF);

    if (effect->grid->unlit == 0 && mapChunkIsInUse(chunk)) {
        lightSampleColorAtPosition(effect->x, effect->y, effect->z, 0, &red, &green, &blue, chunk);
        colorRed = red / 255.0;
        colorGreen = green / 255.0;
        colorBlue = blue / 255.0;
    }
    gDPSetPrimColor(glist++, 0, 0, effect->red * colorRed, effect->green * colorGreen, effect->blue * colorBlue, effect->alpha);
    if (effect->mode != 0) {
        gSPMatrix(glist++, &D_20000C0, G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH);
        gSPMatrix(glist++, &D_2000180, G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
        glist = gfxInit2DDisplayList(glist);
        if (effect->chunkFilter == -1) {
            gDPSetScissorFrac(glist++, G_SC_NON_INTERLACE, effect->minX * 4.0f, effect->minY * 4.0f, effect->maxX * 4.0f, effect->maxY * 4.0f);
        }
    }
    gSPMatrix(glist++, osVirtualToPhysical(&effect->matrices[gCurrentPlayerIndex][gGfxBufferIndex]), G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_PUSH);

    for (i = 0; i < effect->frameCount; i++) {
        if (gRenderSetupKind != 5 || gRenderLoadedTexture != effect->frames[i]) {
            gDPPipeSync(glist++);
            switch (effect->grid->size) {
                case 0:
                    gDPLoadTextureBlock_4b(glist++, effect->frames[i], effect->grid->format, effect->grid->cellW, effect->grid->cellH, 0, G_TX_CLAMP, G_TX_CLAMP, 0, 0, 0, 0);
                    break;
                case 1:
                    gDPLoadTextureBlock(glist++, effect->frames[i], effect->grid->format, G_IM_SIZ_8b, effect->grid->cellW, effect->grid->cellH, 0, G_TX_CLAMP, G_TX_CLAMP, 0, 0, 0, 0);
                    break;
                case 2:
                    gDPLoadTextureBlock(glist++, effect->frames[i], effect->grid->format, G_IM_SIZ_16b, effect->grid->cellW, effect->grid->cellH, 0, G_TX_CLAMP, G_TX_CLAMP, 0, 0, 0, 0);
                    break;
                case 3:
                    gDPLoadTextureBlock(glist++, effect->frames[i], effect->grid->format, G_IM_SIZ_32b, effect->grid->cellW, effect->grid->cellH, 0, G_TX_CLAMP, G_TX_CLAMP, 0, 0, 0, 0);
                    break;
            }
            gRenderLoadedTexture = effect->frames[i];
        }
        gSPVertex(glist++, osVirtualToPhysical(effect->vertices + (i << 2)), 4, 0);
        gSP2Triangles(glist++, 0, 1, 3, 0, 0, 2, 3, 0);
    }
    gSPPopMatrix(glist++, G_MTX_MODELVIEW);
    gDPPipeSync(glist++);
    gDPSetColorDither(glist++, G_CD_MAGICSQ);
    if (effect->mode != 0) {
        gSPMatrix(glist++, &D_2000000, G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH);
        gSPMatrix(glist++, &D_2000200, G_MTX_PROJECTION | G_MTX_MUL | G_MTX_NOPUSH);
        if (effect->chunkFilter == -1) {
            gDPSetScissorFrac(glist++, G_SC_NON_INTERLACE, 0, 0, gScreenWidth * 4.0f, gScreenHeight * 4.0f);
        }
    }
    gDPPipeSync(glist++);
    gSPEndDisplayList(glist++);
    gRenderSetupKind = 5;
    return inGlist;
}
