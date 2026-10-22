#include "common.h"

#pragma GLOBAL_ASM("asm/global/nonmatchings/90D80/func_8068C080.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/90D80/func_8068C0B4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/90D80/func_8068C12C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/90D80/func_8068C20C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/90D80/func_8068C2EC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/90D80/func_8068C2F8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/90D80/func_8068C350.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/90D80/func_8068C3A0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/90D80/func_8068C5A8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/90D80/func_8068D264.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/90D80/func_8068D8C8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/90D80/func_8068D9DC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/90D80/func_8068DAF4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/90D80/func_8068DBA4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/90D80/func_8068DC54.s")

#define Act90B_WRITE_GFX(pkt, _w0, _w1) { Gfx *_g = (Gfx *)(pkt); _g->words.w0 = (_w0); _g->words.w1 = (_w1); }

extern Gfx D_1000118;
extern Mtx D_20000C0;
extern u32 D_8076A064;
extern s32 D_807FBB64;

Gfx *func_8068C5A8(Gfx *, s32, s32, s32, s32, s32, s32, s32, f32, f32, s32, f32);

typedef struct Act90B_Actor174 {
    u8 pad[0x34];
    u8 *unk34;
} Act90B_Actor174;

typedef struct Act90B_Actor {
    u8 pad[0xE6];
    s16 unkE6;
    u8 padE8[4];
    s16 unkEC;
    u8 padEE[0x174 - 0xEE];
    Act90B_Actor174 *unk174;
} Act90B_Actor;
#define Act90B_TEX ((((D_8076A064 >> 1) % 12) + 0x83) & 0xFFFF)

Gfx *func_8068E474(Gfx *arg0, Act90B_Actor *arg1) {
    s16 unkEC = arg1->unkEC + 0x5A;

    Act90B_WRITE_GFX(arg0++, 0xDE000000, (u32)&D_1000118);
    Act90B_WRITE_GFX(arg0++, 0xFCFFFFFF, 0xFFFCF279);
    Act90B_WRITE_GFX(arg0++, 0xE200001C, 0x00504240);
    Act90B_WRITE_GFX(arg0++, 0xDA380007, (u32)&D_20000C0);

    if (D_807FBB64 & 0x80000) {
        s16 yaw = arg1->unkE6;
        Act90B_Actor174 *unk174 = arg1->unk174;
        if (yaw < 0x200 || yaw >= 0xE01 || (yaw >= 0x601 && yaw < 0xA00)) {
            if (*unk174->unk34 != 0x10 && *unk174->unk34 != 0x13) {
                arg0 = func_8068C5A8(arg0, Act90B_TEX, 0, 2, 0x20, 0x10, 0x78, 0x1E0, 4.0f, 4.0f, 0, 0.0f);
                arg0 = func_8068C5A8(arg0, Act90B_TEX, 0, 2, 0x20, 0x10, 0x488, 0x1E0, 4.0f, 4.0f, 0xB4, 0.0f);
            }
        } else {
            arg0 = func_8068C5A8(arg0, Act90B_TEX, 0, 2, 0x20, 0x10, 0x280, 0x78, 4.0f, 4.0f, 0x5A, 0.0f);
            arg0 = func_8068C5A8(arg0, Act90B_TEX, 0, 2, 0x20, 0x10, 0x280, 0x348, 4.0f, 4.0f, 0x10E, 0.0f);
        }
    } else {
        arg0 = func_8068C5A8(arg0, Act90B_TEX, 0, 2, 0x20, 0x10, 0xB4, 0xC8, 8.0f, 8.0f, unkEC, 0.0f);
    }

    return arg0;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/90D80/func_8068E7B4.s")
