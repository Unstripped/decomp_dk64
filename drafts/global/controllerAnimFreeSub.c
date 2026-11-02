// controllerAnimFreeSub (src/global/17B90.c): controllerAnimFreeSub (src/global/17B90.c): stage 5; frame 0x40 + s0-s6 match; score ~7 (down from 35, scored with the func_806138B0 tail joined): `val = cmd->unk0; if ((val >> 24) == 0xFD)` reuse of val (v0), `cmd = sub->commands->start` before cmdList, `++cmd != cmdList` latch, s16 idx + dead idx test; remaining: preheader addiu order (needs reloc D_807FB7B0 vs &D_807FB630[32]), lhu temp s0 vs t3
#include "common.h"

typedef struct {
    void *unk0;
    u8 pad4[0x48];
    void *unk4C;
    void *unk50;
} ControllerViewB;

typedef struct {
    u32 unk0;
    u32 unk4;
} ControllerCmdB;

typedef struct {
    ControllerCmdB *start;
} ControllerCmdListB;

typedef struct {
    u8 pad0[4];
    ControllerCmdListB *commands;
} ControllerSubB;

void assetFreeBuffer(void *, s32, s32);

struct AnimCacheEntry {
    s32 id;
    s32 refCount;
    void *asset;
};
extern struct AnimCacheEntry D_807FB7B0[];
typedef struct {
    u16 unk0;
    u16 unk2;
    u32 unk4;
    u8 unk8;
} AnimStateSlot;

extern AnimStateSlot D_807FB630[];
extern s16 D_807FBB30;

void controllerAnimFreeSub(arg0, arg1)
ControllerViewB *arg0;
u8 arg1;
{
    ControllerSubB *sub;
    AnimStateSlot *entry;
    ControllerCmdB *cmd;
    ControllerCmdListB *cmdList;
    AnimStateSlot *last;
    u32 val;
    s16 idx;
    switch (arg1) {
    case 0:
        sub = arg0->unk0;
        arg0->unk0 = NULL;
        break;
    case 1:
        sub = arg0->unk4C;
        arg0->unk4C = NULL;
        break;
    case 2:
        sub = arg0->unk50;
        arg0->unk50 = NULL;
        break;
    }

    if (sub != NULL) {
        entry = (AnimStateSlot *)D_807FB630;
        do {
            if (entry->unk4 == (u32)sub) {
                break;
            }
        } while (++entry != (AnimStateSlot *)&D_807FB630[32]);

        if (entry == (AnimStateSlot *)D_807FB7B0) {
            return;
        }

        if (--entry->unk2 == 0) {
            cmd = sub->commands->start;
            cmdList = sub->commands;
            if (cmd != (ControllerCmdB *)cmdList) {
                do {
                    val = cmd->unk0;
                    if ((val >> 24) == (0, 0xFD)) {
                        val = cmd->unk4;
                        if ((val >= 0x80000000) && (val < 0xA0000000)) {
                            assetFreeBuffer((void *)(val ^ 0), 0x270, 0x15);
                        }
                    }
                } while (++cmd != (ControllerCmdB *)cmdList);
            }

            idx = (u16)D_807FBB30 - 1;
            last = (AnimStateSlot *)&D_807FB630[(u16)idx];
            D_807FBB30 = idx;

            entry->unk0 = last->unk0;
            entry->unk4 = last->unk4;
            entry->unk8 = last->unk8;
            entry->unk2 = last->unk2;

            last->unk0 = 0;
            last->unk4 = 0;
            last->unk8 = 0;
            last->unk2 = 0;

            assetFreeBuffer((void *)sub, 0x281, 0x15);
            if (idx != 0) {} // FAKE: dead test, keeps idx referenced (colours the lhu temp)
        }
    }
}
