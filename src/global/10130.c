#include "common.h"
#include "compiler/ido/memory.h"
#include "actor.h"
#include "proto/global/10130.h"
#include "proto/global/15050.h"
#include "proto/global/6AD90.h"

// One frame of a demo input recording (asset table 0x11).
typedef struct InputRecord {
    s16 camYawFlags; // bits 0-14: camera yaw (4096 per turn); bit 15: the next button word applies from this frame
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
    u8 kongIndex;
    u8 pad11;
    KongInventory inventory;
} PositionRecord;

s16 sDemoButtonCount = 0;
s32 D_807463A4 = 0; // unreferenced
InputRecord *sDemoInputBuffer = NULL;
s16 sDemoFrameIndex = 0;
s16 sDemoFrameCount = 0;
u16 sDemoButtons = 0;
u8 gDemoPlaybackState = 0;

void func_8060B430(Actor *target, PositionRecord *record) {
    target->x = record->x;
    target->y = record->y;
    target->z = record->z;
    target->yaw = record->yaw;
    memcpy(&gPlayerInventoryTable[0].kong[record->kongIndex], &record->inventory, sizeof(KongInventory));
}

extern PositionRecord sDemoStartRecord;

s16 demoPlaybackStart(Actor *target, s32 unused) {
    gDemoPlaybackState = 2;
    func_8060B430(target, &sDemoStartRecord);
    return sDemoFrameCount;
}

extern u16 *sDemoButtonCursor;
extern InputRecord *sDemoInputCursor;

void demoPlaybackReadPad(OSContPad *pad) {
    if (sDemoFrameIndex < (sDemoFrameCount - 1)) {
        pad->stick_x = sDemoInputCursor->stickX;
        pad->stick_y = sDemoInputCursor->stickY;
        if (sDemoInputCursor->camYawFlags & 0x8000) {
            sDemoButtons = *sDemoButtonCursor;
            sDemoButtonCursor++;
        }
        pad->button = sDemoButtons & 0xEFFF;
    }
}

void demoPlaybackReadCamYaw(s16 *outCamYaw) {
    if (sDemoFrameIndex < (sDemoFrameCount - 1)) {
        *outCamYaw = sDemoInputCursor->camYawFlags & 0x7FFF;
        sDemoInputCursor++;
        sDemoFrameIndex++;
    } else {
        gDemoPlaybackState = 0;
    }
}

extern u16 *sDemoButtonBuffer;



void recordInitPositionBuffers(u8 *src) {
    s32 byteCount;

    if (sDemoInputBuffer == NULL) {
        sDemoInputBuffer = heapAlloc(1800 * sizeof(InputRecord));
    }
    sDemoInputCursor = sDemoInputBuffer;
    if (sDemoButtonBuffer == NULL) {
        sDemoButtonBuffer = heapAlloc(1800 * sizeof(u16));
    }
    sDemoButtonCursor = sDemoButtonBuffer;
    byteCount = sizeof(sDemoFrameCount);
    memcpy(&sDemoFrameCount, src, byteCount);
    src += byteCount;
    byteCount = sDemoFrameCount * sizeof(InputRecord);
    memcpy(sDemoInputBuffer, src, byteCount);
    src += byteCount;
    byteCount = sizeof(sDemoButtonCount);
    memcpy(&sDemoButtonCount, src, byteCount);
    src += byteCount;
    byteCount = sDemoButtonCount * sizeof(u16);
    memcpy(sDemoButtonBuffer, src, byteCount);
    src += byteCount;
    byteCount = sizeof(sDemoStartRecord);
    memcpy(&sDemoStartRecord, src, byteCount);
}


void demoPlaybackReset(void) {
    sDemoInputBuffer = NULL;
    sDemoButtonBuffer = NULL;
    sDemoFrameIndex = 0;
    sDemoFrameCount = 0;
    sDemoButtonCount = 0;
    gDemoPlaybackState = 0;
}


void demoPlaybackFree(void) {
    if (sDemoInputBuffer != NULL) {
        heapFree(sDemoInputBuffer);
    }
    if (sDemoButtonBuffer != NULL) {
        heapFree(sDemoButtonBuffer);
    }
    demoPlaybackReset();
}


void demoPlaybackLoad(s32 assetIndex) {
    void *assetData;

    assetData = assetLoad(0x11, assetIndex, 1, 1);
    recordInitPositionBuffers(assetData);
    assetFreeBuffer(assetData, 0xF8, 0x33);
    sDemoInputCursor = sDemoInputBuffer;
    sDemoButtonCursor = sDemoButtonBuffer;
    sDemoFrameIndex = 0;
    sDemoButtons = 0;
}


u8 func_8060B7C4(void) {
    return sDemoStartRecord.kongIndex;
}


void func_8060B7D0(s32 *outMap, s32 *outExit) {
    *outMap = sDemoStartRecord.map;
    *outExit = sDemoStartRecord.exit;
}
