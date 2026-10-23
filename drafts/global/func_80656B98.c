// func_80656B98 (src/global/55B20.c): stage 6: full-size match; target reloads arg2 via lbu 0x4b(sp) (param home slot) and hoists move s1,s0 into dispatch delay slots; mine keeps arg2 in a register (andi) and emits per-case move v0,s3. Tried: K&R vs prototyped u8, if/else vs continue, entry/slot locals vs full expressions, decl orders, permuter (K&R unsupported).
// a register (&andi s8) where the target reloads lbu 0x4b(sp) from the parameter home slot,
// and the target hoists `move s1,s0` into the dispatch delay slots (mine emits a per-case
// `move v0,s3`). Search loop/emit block structure matches (if/else + do/while, single return).
#include "common.h"

typedef struct {
    /* 0x000 */ u8 unk0;
    /* 0x001 */ u8 unk1;
    /* 0x002 */ u8 unk2;
    /* 0x003 */ u8 unk3;
    /* 0x004 */ u8 unk4;
    /* 0x005 */ u8 pad5[0x1];
    /* 0x006 */ u8 unk6;
    /* 0x007 */ u8 unk7;
    /* 0x008 */ u8 pad8[0xC];
    /* 0x014 */ s32 unk14;
    /* 0x018 */ u8 pad18[0x4];
    /* 0x01C */ s32 unk1C;
    /* 0x020 */ u8 pad20[0x4];
    /* 0x024 */ s32 unk24;
    /* 0x028 */ u8 pad28[0x40];
    /* 0x068 */ s32 unk68;
    /* 0x06C */ s32 unk6C;
    /* 0x070 */ s32 unk70;
    /* 0x074 */ s32 unk74;
    /* 0x078 */ u32 unk78;
    /* 0x07C */ u32 unk7C;
    /* 0x080 */ s16 unk80;
    /* 0x082 */ s16 unk82;
    /* 0x084 */ s16 unk84;
    /* 0x086 */ s16 unk86;
    /* 0x088 */ u8 pad88[0x140];
} M55P3EffectBuf;

extern M55P3EffectBuf *D_807F6C18;
struct M55P2SearchEntry;
extern struct M55P2SearchEntry *D_807F70B0;
extern u32 osVirtualToPhysical(void *);

typedef struct {
    /* 0x000 */ u8 pad0[0x5];
    /* 0x005 */ u8 unk5;
    /* 0x006 */ u8 pad6[0x26];
    /* 0x02C */ s32 unk2C;
    /* 0x030 */ s32 unk30;
    /* 0x034 */ s32 unk34;
    /* 0x038 */ s32 unk38;
    /* 0x03C */ u8 pad3C[0x10];
    /* 0x04C */ u8 *unk4C;
    /* 0x050 */ s32 unk50;
    /* 0x054 */ u8 pad54[0x174];
} M55P5EffectSlot;

typedef struct {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ u8 unk2;
    /* 0x03 */ u8 pad3[0x1];
    /* 0x04 */ s32 unk4[4];
    /* 0x14 */ s32 unk14[4];
} M55P5EffectEntry;

typedef struct {
    /* 0x00 */ u8 pad0[0x2];
    /* 0x02 */ s16 unk2;
    /* 0x04 */ u8 pad4[0x14];
    /* 0x18 */ u8 unk18;
    /* 0x19 */ u8 pad19[0x3];
} M55P5SearchEntry;


#define R2P5_WRITE_GFX(pkt, _w0, _w1) { Gfx *_g = (Gfx *)(pkt); _g->words.w0 = (_w0); _g->words.w1 = (u32)(_w1); }

s32 func_80656B98(arg0, arg1, arg2)
u32 *arg0;
s32 arg1;
u8 arg2;
{
    M55P5EffectEntry *entry;
    M55P5SearchEntry *node;
    Gfx *gfx;
    s32 i;
    s32 found;

    gfx = (Gfx *)arg0;
    R2P5_WRITE_GFX(gfx++, 0xE7000000, 0);
    if (((M55P5EffectSlot *)D_807F6C18)[arg1].unk5 != 2) {
        switch (arg2) {
        case 0:
            R2P5_WRITE_GFX(gfx++, 0xDE000000, osVirtualToPhysical((void *)((M55P5EffectSlot *)D_807F6C18)[arg1].unk2C));
            break;
        case 1:
            R2P5_WRITE_GFX(gfx++, 0xDE000000, osVirtualToPhysical((void *)((M55P5EffectSlot *)D_807F6C18)[arg1].unk30));
            break;
        case 2:
            R2P5_WRITE_GFX(gfx++, 0xDE000000, osVirtualToPhysical((void *)((M55P5EffectSlot *)D_807F6C18)[arg1].unk34));
            break;
        case 3:
            R2P5_WRITE_GFX(gfx++, 0xDE000000, osVirtualToPhysical((void *)((M55P5EffectSlot *)D_807F6C18)[arg1].unk38));
            break;
        }
    } else {
        for (i = 0; i < ((M55P5EffectSlot *)D_807F6C18)[arg1].unk50; i++) {
            if (((M55P5EffectEntry *)((M55P5EffectSlot *)D_807F6C18)[arg1].unk4C)[i].unk4[arg2] == -1) {
                continue;
            }
            found = 0;
            node = (M55P5SearchEntry *)D_807F70B0;
            do {
                if (node->unk2 == ((M55P5EffectEntry *)((M55P5EffectSlot *)D_807F6C18)[arg1].unk4C)[i].unk0) {
                    found = 1;
                } else {
                    node++;
                }
            } while (found == 0);
            if (node->unk18 == 0) {
                continue;
            }
            if ((((M55P5EffectEntry *)((M55P5EffectSlot *)D_807F6C18)[arg1].unk4C)[i].unk2 & (1 << arg2)) == 0) {
                continue;
            }
            R2P5_WRITE_GFX(gfx++, 0xDB060018, osVirtualToPhysical((void *)((M55P5EffectEntry *)((M55P5EffectSlot *)D_807F6C18)[arg1].unk4C)[i].unk14[arg2]));
            R2P5_WRITE_GFX(gfx++, 0xE7000000, 0);
            R2P5_WRITE_GFX(gfx++, 0xDE000000, osVirtualToPhysical((void *)((M55P5EffectEntry *)((M55P5EffectSlot *)D_807F6C18)[arg1].unk4C)[i].unk4[arg2]));
            R2P5_WRITE_GFX(gfx++, 0xE7000000, 0);
        }
    }
    return (s32)gfx;
}
