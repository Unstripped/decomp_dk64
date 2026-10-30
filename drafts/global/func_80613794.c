// func_80613794 (src/global/17B90.c): stage 5: frame 0x40 and 7 saved regs match; entry switch, buffer frees, and table shift match; remaining diff is loop bound reload and cmdList comparison order
#include "common.h"

typedef struct {
    void *unk0;
    u8 pad4[0x48];
    void *unk4C;
    void *unk50;
} RvE3_ControllerView;

typedef struct {
    u16 unk0;
    u16 unk2;
    void *unk4;
    u8 unk8;
    u8 pad9[3];
} RvE3_StateEntry;

typedef struct {
    u32 unk0;
    u32 unk4;
} ControllerCommand;

typedef struct {
    ControllerCommand *start;
} ControllerCommandList;

typedef struct {
    u8 pad0[4];
    ControllerCommandList *commands;
} ControllerSub;

extern RvE3_StateEntry D_807FB630[];
extern RvE3_StateEntry D_807FB7B0[];
extern u16 D_807FBB30;

void assetFreeBuffer(u32, s32, s32);

void func_80613794(RvE3_ControllerView *arg0, u8 arg1) {
    ControllerSub *sub;
    RvE3_StateEntry *entry;
    ControllerCommand *cmd;
    ControllerCommandList *cmdList;
    RvE3_StateEntry *last;
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
            if (entry->unk4 == sub) {
                break;
            }
            entry++;
        } while (entry != D_807FB7B0);

        if (entry == D_807FB7B0) {
            return;
        }

        if (--entry->unk2 == 0) {
            cmdList = sub->commands;
            cmd = cmdList->start;
            if (cmd != (ControllerCommand *)cmdList) {
                do {
                    if ((cmd->unk0 >> 24) == (0, 0xFD)) {
                        val = cmd->unk4;
                        if ((val >= 0x80000000) && (val < 0xA0000000)) {
                            assetFreeBuffer(val ^ 0, 0x270, 0x15);
                        }
                    }
                    cmd++;
                } while ((ControllerCommand *)cmdList != cmd);
            }

            val = D_807FBB30 - 1;
            last = &D_807FB630[(u16)val];
            D_807FBB30 = val;

            entry->unk0 = last->unk0;
            entry->unk4 = last->unk4;
            entry->unk8 = last->unk8;
            entry->unk2 = last->unk2;

            last->unk0 = 0;
            last->unk4 = NULL;
            last->unk8 = 0;
            last->unk2 = 0;

            assetFreeBuffer((u32)sub, 0x281, 0x15);
        }
    }
}
