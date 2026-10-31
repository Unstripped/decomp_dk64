// controllerAnimFreeSub (src/global/17B90.c): stage 5: frame 0x40 and 7 saved regs match; parked NON_MATCHING; loop bound reload into t8 vs v0 reuse and cmdList comparison order
#include "common.h"

typedef struct {
    void *unk0;
    u8 pad4[0x48];
    void *unk4C;
    void *unk50;
} ControllerViewB;

typedef struct {
    u16 unk0;
    u16 unk2;
    u32 unk4;
    u32 unk8;
} ControllerStateEntry;

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

struct AnimCacheEntry {
    s32 id;
    s32 refCount;
    void *asset;
};
extern struct AnimCacheEntry D_807FB7B0[];
extern ControllerStateEntry D_807FB630[];
extern s16 D_807FBB30;

void assetFreeBuffer(void *, s32, s32);

void controllerAnimFreeSub(arg0, arg1)
ControllerViewB *arg0;
u8 arg1;
{
    ControllerSubB *sub;
    ControllerStateEntry *entry;
    ControllerCmdB *cmd;
    ControllerCmdListB *cmdList;
    ControllerStateEntry *last;
    u32 val;

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
        entry = D_807FB630;
        do {
            if (entry->unk4 == (u32)sub) {
                break;
            }
        } while (++entry != (ControllerStateEntry *)D_807FB7B0);

        if (entry == (ControllerStateEntry *)D_807FB7B0) {
            return;
        }

        if (--entry->unk2 == 0) {
            cmdList = sub->commands;
            cmd = cmdList->start;
            if (cmd != (ControllerCmdB *)cmdList) {
                do {
                    if ((cmd->unk0 >> 24) == (0, 0xFD)) {
                        val = cmd->unk4;
                        if ((val >= 0x80000000) && (val < 0xA0000000)) {
                            assetFreeBuffer((void *)(val ^ 0), 0x270, 0x15);
                        }
                    }
                    cmd++;
                } while ((ControllerCmdB *)cmdList != cmd);
            }

            val = D_807FBB30 - 1;
            last = &D_807FB630[(u16)val];
            D_807FBB30 = val;

            entry->unk0 = last->unk0;
            entry->unk4 = last->unk4;
            entry->unk8 = last->unk8;
            entry->unk2 = last->unk2;

            last->unk0 = 0;
            last->unk4 = 0;
            last->unk8 = 0;
            last->unk2 = 0;

            assetFreeBuffer((void *)sub, 0x281, 0x15);
        }
    }
}
