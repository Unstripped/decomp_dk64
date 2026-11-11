#include "common.h"
#include "compiler/ido/memory.h"
#include "actor.h"
#include "proto/global/10130.h"
#include "proto/global/15050.h"
#include "proto/global/6AD90.h"

typedef struct InputRecord {
    s16 durationFlags;
    s8 stickX;
    s8 stickY;
} InputRecord;

typedef struct PositionRecord {
    f32 x;
    f32 y;
    f32 z;
    s16 yaw;
    u8 map;
    u8 exit;
    u8 playerIndex;
    u8 pad11;
    u8 inventory[];
} PositionRecord;

extern u8 gPlayerInventoryTable[];

void func_8060B430(Actor *target, PositionRecord *record) {
    target->x = record->x;
    target->y = record->y;
    target->z = record->z;
    target->yaw = record->yaw;
    memcpy(&gPlayerInventoryTable[record->playerIndex * 0x5E], record->inventory, 0x5E);
}

extern s16 D_807463B0;
extern s8 D_807463B8;
extern PositionRecord D_807ECE20;

s16 func_8060B49C(Actor *target, s32 unused) {
    D_807463B8 = 2;
    func_8060B430(target, &D_807ECE20);
    return D_807463B0;
}

extern s16 D_807463AC;
extern u16 D_807463B4;
extern u16 *D_807ECE94;
extern InputRecord *D_807ECE98;

void func_8060B4D4(OSContPad *pad) {
    if (D_807463AC < (D_807463B0 - 1)) {
        pad->stick_x = D_807ECE98->stickX;
        pad->stick_y = D_807ECE98->stickY;
        if (D_807ECE98->durationFlags & 0x8000) {
            D_807463B4 = *D_807ECE94;
            D_807ECE94++;
        }
        pad->button = D_807463B4 & 0xEFFF;
    }
}

void func_8060B55C(s16 *outDuration) {
    if (D_807463AC < (D_807463B0 - 1)) {
        *outDuration = D_807ECE98->durationFlags & 0x7FFF;
        D_807ECE98++;
        D_807463AC++;
    } else {
        D_807463B8 = 0;
    }
}

extern s16 D_807463A0;
extern InputRecord *D_807463A8;
extern u16 *D_807ECE90;



void recordInitPositionBuffers(s32 src) {
    s32 byteCount;

    if (D_807463A8 == NULL) {
        D_807463A8 = heapAlloc(0x1C20);
    }
    D_807ECE98 = D_807463A8;
    if (D_807ECE90 == NULL) {
        D_807ECE90 = heapAlloc(0xE10);
    }
    D_807ECE94 = D_807ECE90;
    memcpy(&D_807463B0, (void *)src, 2);
    src += 2;
    byteCount = D_807463B0 * 4;
    memcpy(D_807463A8, (void *)src, byteCount);
    src += byteCount;
    memcpy(&D_807463A0, (void *)src, 2);
    src += 2;
    byteCount = D_807463A0 * 2;
    memcpy(D_807ECE90, (void *)src, byteCount);
    byteCount = src + byteCount; // FAKE: count local reused for the end address keeps src in $s1, byteCount in $s0
    memcpy(&D_807ECE20, (void *)byteCount, 0x70);
}


void func_8060B6CC(void) {
    D_807463A8 = NULL;
    D_807ECE90 = NULL;
    D_807463AC = 0;
    D_807463B0 = 0;
    D_807463A0 = 0;
    D_807463B8 = 0;
}


void func_8060B700(void) {
    if (D_807463A8 != NULL) {
        heapFree(D_807463A8);
    }
    if (D_807ECE90 != NULL) {
        heapFree(D_807ECE90);
    }
    func_8060B6CC();
}


void func_8060B750(s32 assetIndex) {
    s32 assetData;

    assetData = assetLoad(0x11, assetIndex, 1, 1);
    recordInitPositionBuffers(assetData);
    assetFreeBuffer(assetData, 0xF8, 0x33);
    D_807ECE98 = D_807463A8;
    D_807ECE94 = D_807ECE90;
    D_807463AC = 0;
    D_807463B4 = 0;
}


u8 func_8060B7C4(void) {
    return D_807ECE20.playerIndex;
}


void func_8060B7D0(s32 *outMap, s32 *outExit) {
    *outMap = D_807ECE20.map;
    *outExit = D_807ECE20.exit;
}
