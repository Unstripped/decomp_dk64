#include "common.h"
#include "compiler/ido/memory.h"
#include "proto/global/10130.h"
#include "proto/global/15050.h"
#include "proto/global/6AD90.h"

typedef struct RecordTargetView {
    u8 unk0[0x7C];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
    u8 unk88[0x5E];
    s16 unkE6;
} RecordTargetView;

typedef struct PositionRecord {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    s16 unkC;
    u8 unkE[2];
    u8 unk10;
    u8 unk11;
    u8 unk12[];
} PositionRecord;

extern u8 gPlayerInventoryTable[];

void func_8060B430(RecordTargetView *target, PositionRecord *record) {
    target->unk7C = record->unk0;
    target->unk80 = record->unk4;
    target->unk84 = record->unk8;
    target->unkE6 = record->unkC;
    memcpy(&gPlayerInventoryTable[record->unk10 * 0x5E], record->unk12, 0x5E);
}

extern s16 D_807463B0;
extern s8 D_807463B8;
extern PositionRecord D_807ECE20;

s16 func_8060B49C(RecordTargetView *target, s32 unused) {
    D_807463B8 = 2;
    func_8060B430(target, &D_807ECE20);
    return D_807463B0;
}

extern s16 D_807463AC;
extern u16 D_807463B4;
extern u16 *D_807ECE94;
extern s16 *D_807ECE98;

void func_8060B4D4(u8 *controllerData) {
    if (D_807463AC < (D_807463B0 - 1)) {
        controllerData[2] = ((s8 *) D_807ECE98)[2];
        controllerData[3] = ((s8 *) D_807ECE98)[3];
        if (*D_807ECE98 & 0x8000) {
            D_807463B4 = *D_807ECE94;
            D_807ECE94++;
        }
        *(s16 *) controllerData = D_807463B4 & 0xEFFF;
    }
}

void func_8060B55C(s16 *outDuration) {
    if (D_807463AC < (D_807463B0 - 1)) {
        *outDuration = *D_807ECE98 & 0x7FFF;
        D_807ECE98 += 2;
        D_807463AC++;
    } else {
        D_807463B8 = 0;
    }
}

extern s16 D_807463A0;
extern s16 *D_807463A8;
extern s16 *D_807ECE90;



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
    byteCount = src + byteCount;
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
    return D_807ECE20.unk10;
}


void func_8060B7D0(s32 *outMap, s32 *outExit) {
    *outMap = ((u8 *) &D_807ECE20)[0xE];
    *outExit = ((u8 *) &D_807ECE20)[0xF];
}
