#include "common.h"

extern Gfx D_1000118;
extern Mtx D_2000080;
extern Mtx D_2000180;
Gfx *func_806FE078(Gfx *, u8, s32, f32, f32, f32, f32);
Gfx *func_8068DC54(Gfx *, s32, s32, void *, s16, void *);

Gfx *func_800252A0(Gfx *gdl, void *arg1) {
    void *temp_t0 = *(void **)((u8 *)arg1 + 0x174);

    gDPPipeSync(gdl++);
    gDPSetPrimColor(gdl++, 0, 0, 200, 200, 200, 255);
    gDPSetCombineMode(gdl++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
    gDPSetRenderMode(gdl++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
    gSPDisplayList(gdl++, &D_1000118);
    gSPMatrix(gdl++, &D_2000080, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
    gSPMatrix(gdl++, &D_2000180, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    return func_8068DC54(
        func_806FE078(gdl, *(u8 *)((u8 *)temp_t0 + 0x19), 8, 30.0f, 36.0f, 0.0f, 1.5f),
        0x26, 0x32, (u8 *)temp_t0 + 0x14, *(s16 *)((u8 *)temp_t0 + 0x16), (u8 *)temp_t0 + 0x18);
}

s32 actorSpawn(s32, s32);
extern void *D_807FBB40;
extern void *D_807FBB44;

void *func_800253E4(s32 arg0, s16 arg1, s16 arg2, s16 arg3) {
    if (actorSpawn(0xDB, arg0) != 0) {
        void **ptr = *(void ***)((u8 *)D_807FBB44 + 0x174);
        *(f32 *)((u8 *)D_807FBB44 + 0x7C) = (f32)arg1;
        *(f32 *)((u8 *)D_807FBB44 + 0x80) = (f32)arg2;
        *(f32 *)((u8 *)D_807FBB44 + 0x84) = (f32)arg3;
        *ptr = D_807FBB40;
    }
    return D_807FBB44;
}

extern u8 *D_8002D8B0[];

u8 func_80025480(u8 **arg0, u8 arg1) {
    s32 idx = arg1;
    return D_8002D8B0[idx][arg0[idx][0x15F]];
}

#pragma GLOBAL_ASM("asm/bonus/nonmatchings/12A0/func_800254B0.s")

void func_8061C464(void *, void *, s32, s32, s32, s32, s32, s32, s32, s32, f32);
extern void *D_807FBB4C;

void func_8002563C(s32 arg0) {
    void *temp_v0 = *(void **)((u8 *)D_807FBB4C + 0x174);
    func_8061C464(*(void **)((u8 *)temp_v0 + 0x104), D_807FBB4C, 4, 0, 0xAA, 0, 0, 0, 0, 0, 0.09f);
    *(u8 *)((u8 *)D_807FBB40 + 0x154) = 3;
    *(u8 *)((u8 *)D_807FBB40 + 0x155) = 1;
    *(s16 *)((u8 *)D_807FBB40 + 0x168) = 0;
}

void bonusInitActors(u8 **arg0, u8 arg1) {
    u8 i = 0;
    do {
        arg0[i][0x154]++;
        *(s16 *)(arg0[i] + 0xF0) = arg1;
    } while (++i < 4);
}

#pragma GLOBAL_ASM("asm/bonus/nonmatchings/12A0/D_8002DC90.s")

#pragma GLOBAL_ASM("asm/bonus/nonmatchings/12A0/D_8002DC98.s")

#pragma GLOBAL_ASM("asm/bonus/nonmatchings/12A0/D_8002DCA0.s")

#pragma GLOBAL_ASM("asm/bonus/nonmatchings/12A0/D_8002DCA8.s")

#pragma GLOBAL_ASM("asm/bonus/nonmatchings/12A0/func_8002570C.s")

#pragma GLOBAL_ASM("asm/bonus/nonmatchings/12A0/func_800261B8.s")
void func_80609140(s32, s32, f32, f32, s32, s32);
void textSpawnMarkerChecked(s32, s32, s32, s32, s32, s32, s32, s32);
void sfxAllocateChannel(s32, f32);
s32 playerStateQueueCallback(s32, s32, s32);
void func_80627948(void *, s32, s32, s32);
s32 func_8070E750(s32, s32, s32);

void func_800264E0(u8 arg0, u8 arg1) {
    func_80609140(0x143, 0x7FFF, 63.0f, 1.0f, 0, 0);
    textSpawnMarkerChecked(0x81, 0, 0x78, func_8070E750(0x1A, arg1, 1), 0, 0x28, 8, 8);
    *(u8 *)((u8 *)*(void **)((u8 *)D_807FBB40 + 0x11C) + 0x154) = 0;
    sfxAllocateChannel(0x28, 1.0f);
    playerStateQueueCallback(0x44, 0, 0);
    *(u8 *)((u8 *)D_807FBB40 + 0x154) += 1;
    if (arg0 != 0) {
        func_80627948(D_807FBB4C, 5, 0x21, 5);
    }
}

void func_800265C0(u8 arg0, u8 arg1) {
    *(u8 *)((u8 *)*(void **)((u8 *)D_807FBB40 + 0x11C) + 0x154) = 0;
    textSpawnMarkerChecked(0x81, 0, 0x78, func_8070E750(0x1A, arg1, 1), 0, 0x28, 8, 8);
    sfxAllocateChannel(0x57, 1.0f);
    playerStateQueueCallback(0x43, 0, 0);
    *(u8 *)((u8 *)D_807FBB40 + 0x154) += 1;
    if (arg0 != 0) {
        func_80627948(D_807FBB4C, 5, 0x21, 5);
    }
}
