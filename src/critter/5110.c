#include "common.h"

typedef struct Struct_807FBB40_174 {
    s16 unk0;
    u8 unk2;
    u8 pad3;
    s16 unk4;
    u8 unk5;
} Struct_807FBB40_174;

typedef struct Struct_807FBB40 {
    char pad0[0x60];
    s32 unk60;
    char pad64[0x11C - 0x64];
    struct Struct_807FBB40 *unk11C;
    char pad120[0x154 - 0x120];
    u8 unk154;
    char pad155[0x174 - 0x155];
    Struct_807FBB40_174 *unk174;
} Struct_807FBB40;

s32 critterBitwiseNot(s32 arg0) {
    return ~arg0;
}

extern s8 D_80029FA0;
extern u16 D_80029FA4;
extern s8 D_80029FA8;
extern u8 D_807444EC;
extern u8 D_807655F0[];
extern s32 D_8076A0A8;
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

void func_80029118(void) {
    s32 pad88;
    u16 tmp;
    Struct_807FBB40_174 *temp_s0;
    s32 *var_s0;
    void (*temp_v1)(void *, s32);
    s32 temp_t3;
    s32 sp74;
    s32 sp70;
    s32 sp58[6];
    s32 pad54;
    s32 sp50;
    s32 pad40[4];
    s32 sp3C;
    s32 sp38;
    temp_s0 = D_807FBB40->unk174;
    if (!(D_807FBB40->unk60 & 0x10)) {
        D_80029FA8 = 0;
        camStartPath(0, 0, 1);
        tmp = *(u16 *)&D_807FCC40[4];
        D_80029FA4 = tmp;
        D_807FCC44 = 0;
        slotQueueSetShownValue(4, 0, 0);
        switch (D_8076A0A8) {
        case 0xB1:
            temp_s0->unk4 = 0x3C;
            D_80029FA0 = 1;
            break;
        case 0xB6:
            temp_s0->unk4 = 0x3C;
            D_80029FA0 = 1;
            break;
        case 0xB4:
            temp_s0->unk4 = 0x3C;
            D_80029FA0 = 5;
            break;
        case 0xB5:
            temp_s0->unk4 = 0x3C;
            D_80029FA0 = 5;
            break;
        }
        D_807FBB40->unk154 = 0;
    }

    switch (D_807FBB40->unk154) {
    case 0x0:
        if ((D_807444EC == 1) && (camIsPathPaused() != 0)) {
            switch (D_8076A0A8) {
            case 0xB1:
                sp74 = 0;
                break;
            case 0xB6:
                sp74 = 1;
                break;
            case 0xB4:
                sp74 = 2;
                break;
            case 0xB5:
                sp74 = 3;
                break;
            }
            func_8070D8C0(D_807FBB40, 0x19, *(u8 *)((char *)&sp74 + 3));
            D_807FBB40->unk154 = 1;
            hudSpawnCountdownTimer(0xDC, 0x2A, ((u8 *)temp_s0)[5]);
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
        var_s0 = sp58;
        if ((s32)var_s0 & 7) {
            do {
                var_s0 = (s32 *)((char *)var_s0 + 4);
            } while ((s32)var_s0 & 7);
        }
        temp_v1 = (void (*)(void *, s32))critterBitwiseNot(~(s32)osWritebackDCache);
        if (D_80029FA0 <= 0) {
            D_807FBB40->unk154 = 3;
        }
        temp_v1(var_s0, 0x10);
        sp50 = critterBitwiseNot(-0xDC1);
        ((void (*)(void *, s32, s32, s32, void *, s32, void *))critterBitwiseNot(~(s32)osPiStartDma))(&D_807ECE00, 0, 0, sp50, var_s0, 0x10, &D_807655F0);
        if (D_807FBB40->unk11C->unk154 == 5) {
            D_807FBB40->unk154 = 0xFF;
        }
        ((void (*)(void *, s32, s32))critterBitwiseNot(~(s32)osRecvMesg))(&D_807655F0, 0, 1);
        ((void (*)(void *, s32))critterBitwiseNot(~(s32)osInvalDCache))(var_s0, 0x10);
        var_s0[0] += var_s0[1];
        if (var_s0[0] != 0x0A78F00E) {
            flagSet((D_8076A0A8 == 0xB6) ? 0x184 : 0x183, 0, 0);
        }
        break;
    case 0x3:
        D_807FBB40->unk11C->unk154 = 1;
        temp_s0->unk2 = gfxResourceCreate(1, "WELL DONE!", 2, 160.0f, 100.0f, 0.0f);
        sfxPlayOnFreeSlot(0x143, 0x7FFF, 63.0f, 1.0f, 0, 0);
        temp_s0->unk0 = 0x78;
        D_807FBB40->unk154 = 0xFE;
        D_80029FA8 = 1;
        break;
    case 0xFE:
        if (temp_s0->unk0 > 0) {
            temp_s0->unk0--;
            if (temp_s0->unk0 == 0) {
                if (D_80029FA8 != 0) {
                    if (D_8076A0A8 == 0xB4) {
                        D_80029FA4 = 0x14;
                    }
                    switch (D_8076A0A8) {
                    case 0xB1:
                        sp70 = 0x182;
                        break;
                    case 0xB6:
                        sp70 = 0x183;
                        break;
                    case 0xB4:
                        sp70 = 0x184;
                        break;
                    case 0xB5:
                        sp70 = 0x185;
                        break;
                    }
                    if (sp70 && sp70) {} // FAKE: promotes sp70 to a register (default arm reloads its home)
                    flagSet(sp70, 1, 0);
                }
                tmp = D_80029FA4;
                D_807FCC44 = tmp;
                slotQueueSetShownValue(4, 0, tmp);
                func_805FF800(&sp3C, &sp38);
                func_805FF628(sp3C, 0);
            }
        }
        break;
    case 0xFF:
        D_80029FA8 = 0;
        temp_s0->unk2 = gfxResourceCreate(1, "TIME OUT!", 2, 160.0f, 100.0f, 0.0f);
        temp_s0->unk0 = 0x78;
        D_807FBB40->unk154 = 0xFE;
        break;
    }
    renderCallbacksRegister(&critterRenderCenterImage, D_807FBB40, 3);
}

extern u8 D_1000118[];
extern u8 D_2000180[];


Gfx *textDrawAnimated(Gfx *, s32, s32, f32, f32, f32, f32);

Gfx *critterRenderCenterImage(Gfx *glistp, Struct_807FBB40 *arg1) {
    Struct_807FBB40_174 *t1 = arg1->unk174;

    gSPDisplayList(glistp++, &D_1000118);
    gDPPipeSync(glistp++);
    gDPSetPrimColor(glistp++, 0, 0, 200, 200, 200, 255);
    gDPSetCombineMode(glistp++, G_CC_MODULATEIDECALA_PRIM, G_CC_MODULATEIDECALA_PRIM);
    gDPSetRenderMode(glistp++, G_RM_OPA_SURF, G_RM_TEX_EDGE2);
    gSPMatrix(glistp++, &D_2000180, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    if (arg1->unk154 == 0xFE) {
        glistp = textDrawAnimated(glistp, t1->unk2, 2, 160.0f, 100.0f, 0.0f, 1.5f);
    }
    return glistp;
}

