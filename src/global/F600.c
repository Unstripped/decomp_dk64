#include "common.h"

extern volatile u8 D_807467C4;
extern s8 D_80746834;
extern OSContStatus D_807ECCD0[4];
extern OSMesg D_807ECCE0[4];
extern OSMesgQueue D_807ECCF0;
extern u8 D_807ECD08;
extern u8 D_807ECD09;
extern OSContPad D_807ECD10[4];
extern OSContPad D_807ECD28[4];
extern s16 D_807ECD40[4];
extern s16 D_807ECD48[4];
extern s16 D_807ECD50[4];
extern OSContPad D_807ECD58;
extern s16 D_807ECD68[4][16];
extern OSContPad *D_807ECDE8;
extern OSContPad *D_807ECDF4;
extern u8 D_807ECDF8;
extern u8 D_807ECDFC[4];

void controllerWaitRead(void);
void controllerSetActiveMask(u8 mask);
void func_8060E958(void);

u8 controllerInit(void) {
    osCreateMesgQueue(&D_807ECCF0, D_807ECCE0, 4);
    osSetEventMesg(OS_EVENT_SI, &D_807ECCF0, NULL);
    osContInit(&D_807ECCF0, &D_807ECD09, D_807ECCD0);
    osContSetCh(4);
    if (!(D_807ECD09 & 1)) {
        D_807ECD09 = 0;
    }
    D_807ECD08 = 0;
    D_807ECDE8 = D_807ECD10;
    D_807ECDF4 = D_807ECD28;
    controllerSetActiveMask(0xFF);
    func_8060E958();
    return D_807ECD09;
}

void controllerStartRead(void) {
    controllerWaitRead();
    if (D_807467C4 == 0) {
        D_807ECD08 = 1;
        osContStartReadData(&D_807ECCF0);
    }
}

void controllerWaitRead(void) {
    if (D_807ECD08 != 0) {
        D_80746834 = 2;
        osRecvMesg(&D_807ECCF0, NULL, OS_MESG_BLOCK);
        D_80746834 = 0;
        D_807ECD08 = 0;
    }
}

void controllerSetActiveMask(u8 mask) {
    u8 count;
    s32 i;
    s32 j;

    count = 0;
    D_807ECDF8 = D_807ECD09 & mask;
    for (i = 0; i < 4; i++) {
        D_807ECD48[i] = 0;
        D_807ECD40[i] = 0;
        D_807ECD50[i] = 0;
        D_807ECDFC[i] = 0;
        for (j = 0; j < 16; j++) {
            D_807ECD68[i][j] = 0;
        }
        if (D_807ECDF8 & (1 << i)) {
            D_807ECDFC[count] = i;
            count++;
        }
    }
}

u8 controllerGetPort(s32 arg0) {
    return D_807ECDFC[arg0];
}

void controllerCompactPads(OSContPad *pads) {
    s32 i;
    s32 dst;

    dst = 0;
    for (i = 0; i < 4; i++) {
        if (D_807ECDF8 & (1 << i)) {
            if (dst != i) {
                pads[dst] = pads[i];
            }
            dst++;
        }
    }
}

u8 controllerGetActiveMask(void) {
    return D_807ECDF8;
}

void controllerGetReadData(OSContPad *pad) {
    if (D_807467C4 == 0 && D_807ECD08 != 0) {
        osContGetReadData(pad);
    }
    D_807ECD08 = 0;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/F600/controllerUpdate.s")

void controllerLatchPad(OSContPad *pad) {
    D_807ECD58.button = pad->button;
    D_807ECD58.stick_x = pad->stick_x;
    D_807ECD58.stick_y = pad->stick_y;
}
