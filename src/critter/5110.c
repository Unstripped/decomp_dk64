#include "common.h"

typedef struct CritterBattleArenaState {
    s16 timer;
    u8 textGfxHandle;
    u8 pad3;
    s16 timeLimit;
} CritterBattleArenaState;

typedef struct Struct_807FBB40 {
    char pad0[0x60];
    s32 unk60;
    char pad64[0x11C - 0x64];
    struct Struct_807FBB40 *unk11C;
    char pad120[0x154 - 0x120];
    u8 unk154;
    char pad155[0x174 - 0x155];
    CritterBattleArenaState *unk174;
} Struct_807FBB40;

s32 critterBitwiseNot(s32 val) {
    return ~val;
}

extern s8 D_80029FA0;
extern u16 D_80029FA4;
extern s8 D_80029FA8;
extern u8 D_807444EC;
extern u8 D_807655F0[];
extern s32 gCurrentMap;
extern u8 D_807ECE00[];
extern Struct_807FBB40 *D_807FBB40;
extern u16 D_807FCC44;
extern u8 D_807FCC40[];

u16 camStartPath(s32, s32, s32);
void slotQueueSetShownValue(s32, s32, s32);
s32 camIsPathPaused(void);
void func_8070D8C0(void *, s32, s32);
void hudSpawnCountdownTimer(s32, s32, s32);
void camResumePath(void);
void actorSetStateTwo(void *);
void sfxAllocateChannel(s32, f32);
void flagSet(s16, s32, s32);
s32 gfxResourceCreate(s32, char *, s32, f32, f32, f32);
void sfxPlayOnFreeSlot(s32, s32, f32, f32, s32, s32);
void func_805FF800(s32 *, s32 *);
void func_805FF628(s32, s32);
void renderCallbacksRegister(void *, void *, s32);
Gfx *critterRenderCenterImage(Gfx *, Struct_807FBB40 *);

void critterBattleArenaUpdate(void) {
    s32 pad88;
    u16 tmp;
    CritterBattleArenaState *challengeState;
    s32 *alignedBuf;
    void (*dcacheFunc)(void *, s32);
    s32 pad2;
    s32 mapChallengeIdx;
    s32 rewardFlag;
    s32 dmaBuffer[6];
    s32 pad54;
    s32 dmaRomOffset;
    s32 pad40[4];
    s32 returnMap;
    s32 returnExit;
    challengeState = D_807FBB40->unk174;
    if (!(D_807FBB40->unk60 & 0x10)) {
        D_80029FA8 = 0;
        camStartPath(0, 0, 1);
        tmp = *(u16 *)&D_807FCC40[4];
        D_80029FA4 = tmp;
        D_807FCC44 = 0;
        slotQueueSetShownValue(4, 0, 0);
        switch (gCurrentMap) {
        case 0xB1:
            challengeState->timeLimit = 0x3C;
            D_80029FA0 = 1;
            break;
        case 0xB6:
            challengeState->timeLimit = 0x3C;
            D_80029FA0 = 1;
            break;
        case 0xB4:
            challengeState->timeLimit = 0x3C;
            D_80029FA0 = 5;
            break;
        case 0xB5:
            challengeState->timeLimit = 0x3C;
            D_80029FA0 = 5;
            break;
        }
        D_807FBB40->unk154 = 0;
    }

    switch (D_807FBB40->unk154) {
    case 0x0:
        if ((D_807444EC == 1) && (camIsPathPaused() != 0)) {
            switch (gCurrentMap) {
            case 0xB1:
                mapChallengeIdx = 0;
                break;
            case 0xB6:
                mapChallengeIdx = 1;
                break;
            case 0xB4:
                mapChallengeIdx = 2;
                break;
            case 0xB5:
                mapChallengeIdx = 3;
                break;
            }
            func_8070D8C0(D_807FBB40, 0x19, *(u8 *)((char *)&mapChallengeIdx + 3));
            D_807FBB40->unk154 = 1;
            hudSpawnCountdownTimer(0xDC, 0x2A, ((u8 *)challengeState)[5]);
        }
        break;
    case 0x1:
        if (!(D_807FBB40->unk60 & 0x02000000)) {
            camResumePath();
            D_807FBB40->unk154 = 2;
            actorSetStateTwo(D_807FBB40->unk11C);
            sfxAllocateChannel(8, 1.0f);
        }
        break;
    case 0x2:
        alignedBuf = dmaBuffer;
        if ((s32)alignedBuf & 7) {
            do {
                alignedBuf = (s32 *)((char *)alignedBuf + 4);
            } while ((s32)alignedBuf & 7);
        }
        dcacheFunc = (void (*)(void *, s32))critterBitwiseNot(~(s32)osWritebackDCache);
        if (D_80029FA0 <= 0) {
            D_807FBB40->unk154 = 3;
        }
        dcacheFunc(alignedBuf, 0x10);
        dmaRomOffset = critterBitwiseNot(-0xDC1);
        ((void (*)(void *, s32, s32, s32, void *, s32, void *))critterBitwiseNot(~(s32)osPiStartDma))(&D_807ECE00, 0, 0, dmaRomOffset, alignedBuf, 0x10, &D_807655F0);
        if (D_807FBB40->unk11C->unk154 == 5) {
            D_807FBB40->unk154 = 0xFF;
        }
        ((void (*)(void *, s32, s32))critterBitwiseNot(~(s32)osRecvMesg))(&D_807655F0, 0, 1);
        ((void (*)(void *, s32))critterBitwiseNot(~(s32)osInvalDCache))(alignedBuf, 0x10);
        alignedBuf[0] += alignedBuf[1];
        if (alignedBuf[0] != 0x0A78F00E) {
            flagSet((gCurrentMap == 0xB6) ? 0x184 : 0x183, 0, 0);
        }
        break;
    case 0x3:
        D_807FBB40->unk11C->unk154 = 1;
        challengeState->textGfxHandle = gfxResourceCreate(1, "WELL DONE!", 2, 160.0f, 100.0f, 0.0f);
        sfxPlayOnFreeSlot(0x143, 0x7FFF, 63.0f, 1.0f, 0, 0);
        challengeState->timer = 0x78;
        D_807FBB40->unk154 = 0xFE;
        D_80029FA8 = 1;
        break;
    case 0xFE:
        if (challengeState->timer > 0) {
            challengeState->timer--;
            if (challengeState->timer == 0) {
                if (D_80029FA8 != 0) {
                    if (gCurrentMap == 0xB4) {
                        D_80029FA4 = 0x14;
                    }
                    switch (gCurrentMap) {
                    case 0xB1:
                        rewardFlag = 0x182;
                        break;
                    case 0xB6:
                        rewardFlag = 0x183;
                        break;
                    case 0xB4:
                        rewardFlag = 0x184;
                        break;
                    case 0xB5:
                        rewardFlag = 0x185;
                        break;
                    }
                    if (rewardFlag && rewardFlag) {} // FAKE: promotes rewardFlag to a register; adds no new uninitialised read (flagSet below reads rewardFlag on every path here, incl. the original default-less switch)
                    flagSet(rewardFlag, 1, 0);
                }
                tmp = D_80029FA4;
                D_807FCC44 = tmp;
                slotQueueSetShownValue(4, 0, tmp);
                func_805FF800(&returnMap, &returnExit);
                func_805FF628(returnMap, 0);
            }
        }
        break;
    case 0xFF:
        D_80029FA8 = 0;
        challengeState->textGfxHandle = gfxResourceCreate(1, "TIME OUT!", 2, 160.0f, 100.0f, 0.0f);
        challengeState->timer = 0x78;
        D_807FBB40->unk154 = 0xFE;
        break;
    }
    renderCallbacksRegister(&critterRenderCenterImage, D_807FBB40, 3);
}

extern u8 D_1000118[];
extern u8 D_2000180[];


Gfx *textDrawAnimated(Gfx *, s32, s32, f32, f32, f32, f32);

Gfx *critterRenderCenterImage(Gfx *glistp, Struct_807FBB40 *actor) {
    CritterBattleArenaState *t1 = actor->unk174;

    gSPDisplayList(glistp++, &D_1000118);
    gDPPipeSync(glistp++);
    gDPSetPrimColor(glistp++, 0, 0, 200, 200, 200, 255);
    gDPSetCombineMode(glistp++, G_CC_MODULATEIDECALA_PRIM, G_CC_MODULATEIDECALA_PRIM);
    gDPSetRenderMode(glistp++, G_RM_OPA_SURF, G_RM_TEX_EDGE2);
    gSPMatrix(glistp++, &D_2000180, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    if (actor->unk154 == 0xFE) {
        glistp = textDrawAnimated(glistp, t1->textGfxHandle, 2, 160.0f, 100.0f, 0.0f, 1.5f);
    }
    return glistp;
}

