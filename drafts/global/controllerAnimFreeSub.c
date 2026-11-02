// controllerAnimFreeSub (src/global/17B90.c): controllerAnimFreeSub (src/global/17B90.c): stage 5; frame 0x40 + s0-s6 match; score 3 (down from 7, scored with func_806138B0 tail joined): index loop for (i = 0; i < 32; i++) over D_807FB630[i].unk4 + if (i == 32) return + entry = &D_807FB630[i] reproduces the D_807FB7B0 bound and its separate compare; remaining: lui s1 HI16 reloc names D_807FB7B0 not D_807FB630 (reloc only), lhu temp s0 vs t3 (idx not a candidate in target: without the dead idx test idx is v1 and the global addr a3; with local-free (u16)G-1 form regs match but sh t4 store/li a1 schedule 4 lines worse)
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
    s32 i;
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
        for (i = 0; i < 32; i++) {
            if (D_807FB630[i].unk4 == (u32)sub) {
                break;
            }
        }
        if (i == 32) {
            return;
        }
        entry = (AnimStateSlot *)&D_807FB630[i];
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
