#include "common.h"

s32 func_805FCA64(void);
Gfx *func_8068DC54(Gfx *, s32, s32, void *, s16, void *);
Gfx *func_806FE078(Gfx *, u8, s32, f32, f32, f32, f32);
Gfx *func_8070068C(Gfx *);
extern Gfx D_1000118;
extern Gfx D_2000180;

Gfx *func_80024000(Gfx *gdl, void *arg1) {
    void *temp_s0;
    Gfx *temp_v0;

    temp_s0 = *(void **)((u8 *)arg1 + 0x178);
    if (func_805FCA64()) {
        gSPDisplayList(gdl++, &D_1000118);
        gdl = func_8070068C(gdl);
        gDPSetCombineMode(gdl++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
        gDPSetPrimColor(gdl++, 0, 0, 255, 255, 255, 255);
        gSPMatrix(gdl++, &D_2000180, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gdl = func_8068DC54(
            func_806FE078(gdl, *(u8 *)((u8 *)temp_s0 + 9), 8, 30.0f, 36.0f, 0.0f, 1.5f),
            0x26, 0x32, (u8 *)temp_s0 + 2, *(s16 *)((u8 *)temp_s0 + 4), (u8 *)temp_s0 + 8);
    }
    return gdl;
}

void spawnNodeActivateAndSetState(s32, s32, s32);
void bonusInitSounds(void) {
    spawnNodeActivateAndSetState(1, 0x40, 0);
    spawnNodeActivateAndSetState(2, 0x40, 0);
    spawnNodeActivateAndSetState(3, 0x40, 0);
    spawnNodeActivateAndSetState(4, 0x40, 0);
    spawnNodeActivateAndSetState(5, 0x40, 0);
}

#pragma GLOBAL_ASM("asm/bonus/nonmatchings/0/func_80024158.s")

Gfx *func_80024D3C(Gfx *gdl, u8 arg1) {
    gSPDisplayList(gdl++, &D_1000118);
    gDPSetCombineMode(gdl++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
    gDPSetPrimColor(gdl++, 0, 0, 255, 255, 255, 255);
    return gdl;
}

extern s32 D_8076A0A8;

s32 bonusGetSoundForMap(void) {
    switch (D_8076A0A8) {
    case 0x35:
        return 0x261;
    case 0x49:
        return 0x262;
    case 0x9B:
        return 0x263;
    case 0x9C:
        return 0x264;
    case 0x9F:
        return 0x265;
    case 0x9D:
        return 0x266;
    case 0x9E:
        return 0x267;
    case 0xA0:
        return 0x268;
    case 0xA1:
        return 0x269;
    case 0xA2:
        return 0x26A;
    default:
        return -1;
    }
}

void behaviourFrameBegin(void);
void n_alSndpPlay(s32, s32, s32, s32, f32, s32, void *);
void func_806A2A10(s32, s32, u8);
void func_8061CC30(void);
u16 func_8061CC40(s32, s32, s32);
void actorSetStateTwo(void *);
void textSpawnMarkerChecked(s32, s32, s32, s32, s32, s32, s32, s32);
s32 func_8070E750(s32, s32, s32);
void func_80726EE0(s32);
void sfxAllocateChannel(s32, f32);
void actorSpawnNodeEntryScaled(s32, f32, f32, f32, s32, s32, s32, s32);
void func_805FF898(void);
void func_806C9974(s32, s32);
void n_alSndpPostEvent(void *, s32, s16);
s32 func_80611A44(void);
void func_80609140(s32, s32, f32, f32, s32, s32);
extern s32 D_8076D1F8;
extern void *D_807FBB40;
extern void *D_807FBB4C;
extern void *D_807FD580;
extern void *D_807FDC9C;

void func_80024E38(void) {
    u8 *temp_s0;

    temp_s0 = *(u8 **)((u8 *)D_807FBB40 + 0x178);
    behaviourFrameBegin();
    if (!(*(u32 *)((u8 *)D_807FBB40 + 0x60) & 0x10)) {
        *(u16 *)temp_s0 = 0x12C;
        *(s16 *)(temp_s0 + 0xA) = 0;
        *(s16 *)(temp_s0 + 0x8) = 0;
        n_alSndpPlay(D_8076D1F8, 0x1E6, 0, 0x40, 1.0f, 0x80, temp_s0 + 4);
        func_806A2A10(0xDC, 0x2A, *(u8 *)((u8 *)D_807FDC9C + 0xB));
        spawnNodeActivateAndSetState(1, 0x40, 0x10);
        spawnNodeActivateAndSetState(2, 0x40, 0x10);
        spawnNodeActivateAndSetState(3, 0x40, 0x10);
        spawnNodeActivateAndSetState(4, 0x40, 0x10);
        *(u8 *)((u8 *)D_807FBB40 + 0x154) = 0;
        *(u8 *)((u8 *)D_807FBB40 + 0x155) = 0;
        func_8061CC30();
        *(u16 *)(temp_s0 + 0x18) = func_8061CC40(0, 0, 1);
    }
    switch (*(u8 *)((u8 *)D_807FBB40 + 0x154)) {
    case 0:
        if (*(u16 *)(temp_s0 + 0x18) != 0) {
            (*(u16 *)(temp_s0 + 0x18))--;
        } else {
            actorSetStateTwo(*(void **)((u8 *)D_807FBB40 + 0x11C));
            *(u8 *)((u8 *)D_807FBB40 + 0x154) = 1;
        }
        break;
    case 1:
        if (*(u8 *)(*(u8 **)((u8 *)D_807FBB40 + 0x11C) + 0x154) == 5) {
            textSpawnMarkerChecked(0x81, 0, 0x78, func_8070E750(0x1A, 0x15, 1), 0, 0x28, 8, 8);
            func_80726EE0(0);
            sfxAllocateChannel(0x28, 1.0f);
            actorSpawnNodeEntryScaled(0x56, 588.0f, 240.0f, 582.0f, 0, 0, bonusGetSoundForMap(), 0);
            *(u8 *)((u8 *)D_807FBB40 + 0x154) = 2;
        }
        if (*(u8 *)((u8 *)D_807FBB4C + 0x154) == 0x39) {
            func_805FF898();
            func_806C9974(0, 0x40);
            *(u8 *)((u8 *)D_807FBB40 + 0x154) = 2;
        }
        break;
    }
    {
        s32 temp_v0_3 = *(s16 *)(temp_s0 + 0x8) - 0x96;
        (*(u16 *)temp_s0)--;
        if (temp_v0_3 < 0x1F40) {
            *(s16 *)(temp_s0 + 0x8) = 0x1F40;
        } else {
            *(s16 *)(temp_s0 + 0x8) = temp_v0_3;
        }
    }
    {
        s32 temp_v1_2 = *(s16 *)(temp_s0 + 0xA) + 0x3E8;
        if (*(s16 *)(temp_s0 + 0x8) < temp_v1_2) {
            *(s16 *)(temp_s0 + 0xA) = *(s16 *)(temp_s0 + 0x8);
        } else {
            *(s16 *)(temp_s0 + 0xA) = temp_v1_2;
        }
    }
    n_alSndpPostEvent(*(void **)(temp_s0 + 4), 8, *(s16 *)(temp_s0 + 0xA));
    if (*(u32 *)((u8 *)D_807FD580 + 0x1F0) & 0xC0000) {
        if (*(u16 *)temp_s0 < 0x129) {
            *(u16 *)temp_s0 = 0x12C;
            if (*(u32 *)((u8 *)D_807FD580 + 0x1F0) & 0x40000) {
                if (((func_80611A44() >> 15) % 1000) & 1) {
                    func_80609140(0x1E7, 0x7FFF, 64.0f, 1.0f, 0x14, 0x80);
                } else {
                    func_80609140(0x1EA, 0x7FFF, 64.0f, 1.0f, 0x14, 0x80);
                }
            } else {
                func_80609140(0x1E8, 0x7FFF, 64.0f, 1.0f, 0x14, 0x80);
            }
        }
        {
            s32 temp_v0_5 = *(s16 *)(temp_s0 + 0x8) + 0x4650;
            if (temp_v0_5 >= 0x8000) {
                *(s16 *)(temp_s0 + 0x8) = 0x7FFF;
            } else {
                *(s16 *)(temp_s0 + 0x8) = temp_v0_5;
            }
        }
        *(u32 *)((u8 *)D_807FD580 + 0x1F0) &= 0xFFF3FFFF;
    }
    switch (*(u16 *)temp_s0) {
    case 0x0:
    case 0x14:
    case 0x28:
    case 0x3C:
    case 0x50:
        func_80609140(0x1E9, 0x7FFF - *(u16 *)temp_s0 * 0x96, 64.0f, 1.0f, 0xA, 0x80);
        if (*(u16 *)temp_s0 == 0) {
            *(u16 *)temp_s0 = 0xC8;
        }
        break;
    }
}
