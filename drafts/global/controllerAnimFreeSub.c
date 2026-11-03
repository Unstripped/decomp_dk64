// controllerAnimFreeSub (src/global/17B90.c): Revisit 7 (Ctrl 2026-11-03): stage 5, park score 3 unchanged (floor 1 reloc-only; 2 text lines: lhu s0 vs t3 and addiu t4,s0). NEW: with D_807FBB30 declared u16 (extern s16 in the file; whole file still TEXT OK) the fake-free natural body 'D_807FBB30--; last = &D_807FB630[D_807FBB30];' (no idx var, no dead test) has the exact registers/count (120) and only 'sh t4,0(v1)' too early plus 'li a1,641' one slot late (score 5, 4 text lines): the same as1 sink as controllerAnimCacheFree (target sh sits after the first 'lhu t8,0(v0)' = ucode needs '.noalias $D,$last', i.e. last defined before the D store with E-1 shared; 'last=&T[(u16)(D-1)]; D=(u16)(D-1)' variants give 6 with a reload of D after the entry stores (alias), idx var forms 6-27). Tried: --D / D-- / D-=1 / assignment-in-index spellings (5 or 21), 250-form grid last x dec x store position (>=6).
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
