// func_80662838 (src/global/63EC0.c): 159/159 insns matching; exact stack frame 0x38 and identical instruction opcodes/immediates, only minor regalloc difference in tail commands
#include "common.h"
#include "actor.h"

typedef struct R1E63EC0_Struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    s32 unk10;
    s32 unk14;
} R1E63EC0_Struct;
extern R1E63EC0_Struct D_80748A90[];
extern s32 D_80748B68;

#define R1E63EC0_WRITE_GFX(pkt, _w0, _w1) { Gfx *_g = (Gfx *)(pkt); _g->words.w0 = (_w0); _g->words.w1 = (_w1); }

Gfx *func_80662838(Gfx *glist, u8 *arg1, u8 arg2) {
    gDPPipeSync(glist++);
    gDPLoadTextureBlock(glist++, D_80748A90[arg2].unkC, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32, 0, G_TX_WRAP, G_TX_WRAP, 5, 5, 14, 14);
    gDPLoadMultiBlock(glist++, D_80748A90[arg2].unk10, 256, 1, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32, 0, G_TX_WRAP, G_TX_WRAP, 5, 5, D_80748B68, D_80748B68);

    R1E63EC0_WRITE_GFX(glist++, 0xFA000000 | arg1[0x4B], -0x9C);
    R1E63EC0_WRITE_GFX(glist++, 0xFC272C03, 0x1FFC93FB);
    R1E63EC0_WRITE_GFX(glist++, 0xE3000A01, 0x00100000);
    R1E63EC0_WRITE_GFX(glist++, 0xD9000000, 0);
    R1E63EC0_WRITE_GFX(glist++, 0xD9FFFFFF, 0x00200005);
    R1E63EC0_WRITE_GFX(glist++, 0xE3000F00, 0);
    R1E63EC0_WRITE_GFX(glist++, 0xD7000802, 0xFFFFFFFF);
    R1E63EC0_WRITE_GFX(glist++, 0xE200001C, 0x0C184A50);

    return glist;
}
