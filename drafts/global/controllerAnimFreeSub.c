// controllerAnimFreeSub (src/global/17B90.c): stage 5: frame 0x40 and 7 saved regs match; u8 unk8 matched lbu/sb, (u16)D_807FBB30-1 matched lhu, &D_807FB630[32] matched 99c-9d0; remaining diff is D_807FB7B0 preheader order
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
} CtrlB_StateEntry;

extern CtrlB_StateEntry D_807FB630[];
extern s16 D_807FBB30;

void controllerAnimFreeSub(arg0, arg1)
ControllerViewB *arg0;
u8 arg1;
{
    ControllerSubB *sub;
    CtrlB_StateEntry *entry;
    ControllerCmdB *cmd;
    ControllerCmdListB *cmdList;
    CtrlB_StateEntry *last;
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
        entry = (CtrlB_StateEntry *)D_807FB630;
        do {
            if (entry->unk4 == (u32)sub) {
                break;
            }
        } while (++entry != (CtrlB_StateEntry *)&D_807FB630[32]);

        if (entry == (CtrlB_StateEntry *)D_807FB7B0) {
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
                } while (cmd != (ControllerCmdB *)cmdList);
            }

            val = (u16)D_807FBB30 - 1;
            last = (CtrlB_StateEntry *)&D_807FB630[(u16)val];
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
