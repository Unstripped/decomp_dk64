// func_80726EE0 (src/global/1295B0.c): func_80726EE0 (src/global/1295B0.c): near miss. target keeps arg0 in s3 (andi at entry) with `move s1,s3` per iteration and consts 5,1,2,-3,6 in s4-s8; ours hoists 7 too and reloads arg0 from the stack (arg0 candidate 'not colored (-ve save)'). Same frame.
#include "common.h"
#include "actor.h"

extern ActorGlobalState D_807FBB70;

typedef struct C1SpawnEntry {
    /* 0x00 */ u16 unk0;
    /* 0x02 */ u16 unk2;
    /* 0x04 */ u8 pad4[0xA];
    /* 0x0E */ u8 unkE;
    /* 0x0F */ u8 padF[9];
} C1SpawnEntry; // size = 0x18

typedef struct C1ActorView {
    /* 0x000 */ u8 pad0[0x58];
    /* 0x058 */ s32 unk58;
    /* 0x05C */ u16 unk5C;
    /* 0x05E */ u8 pad5E[0xC];
    /* 0x06A */ u16 unk6A;
    /* 0x06C */ u8 pad6C[0x10];
    /* 0x07C */ f32 unk7C;
    /* 0x080 */ f32 unk80;
    /* 0x084 */ f32 unk84;
    /* 0x088 */ u8 pad88[0x30];
    /* 0x0B8 */ f32 unkB8;
    /* 0x0BC */ u8 padBC[4];
    /* 0x0C0 */ f32 unkC0;
    /* 0x0C4 */ u8 padC4[0x22];
    /* 0x0E6 */ s16 unkE6;
    /* 0x0E8 */ u8 padE8[6];
    /* 0x0EE */ s16 unkEE;
    /* 0x0F0 */ u8 padF0[0x3C];
    /* 0x12C */ s16 unk12C;
    /* 0x12E */ u8 pad12E[0x26];
    /* 0x154 */ u8 unk154;
    /* 0x155 */ u8 unk155;
    /* 0x156 */ u8 pad156[0x1E];
    /* 0x174 */ void *unk174;
} C1ActorView;

typedef struct C1Link {
    /* 0x00 */ u8 pad0[0x1C];
    /* 0x1C */ C1ActorView *unk1C;
} C1Link;

typedef struct C1Node {
    /* 0x00 */ u8 unk0;
    /* 0x01 */ u8 pad1[3];
    /* 0x04 */ s16 unk4;
    /* 0x06 */ s16 unk6;
    /* 0x08 */ s16 unk8;
    /* 0x0A */ u8 padA[8];
    /* 0x12 */ u8 unk12;
    /* 0x13 */ u8 unk13;
    /* 0x14 */ u8 unk14;
    /* 0x15 */ u8 pad15[3];
    /* 0x18 */ C1ActorView *unk18;
    /* 0x1C */ C1Link *unk1C;
    /* 0x20 */ u8 pad20[4];
    /* 0x24 */ s16 unk24;
    /* 0x26 */ u8 pad26[0x1A];
    /* 0x40 */ s16 unk40;
    /* 0x42 */ u8 unk42;
    /* 0x43 */ u8 unk43;
    /* 0x44 */ u8 unk44;
    /* 0x45 */ u8 pad45;
    /* 0x46 */ u16 unk46;
} C1Node; // size = 0x48

typedef struct C1NodeList {
    /* 0x0 */ s16 count;
    /* 0x2 */ u8 pad2[2];
    /* 0x4 */ C1Node *nodes;
} C1NodeList;

extern C1NodeList *D_80755694;

void actorDespawn(void *);
void actorQueueDelayedCallback(void *, s32, s32, s32, s32, s32, s32);
void func_8061CFCC(void *);

void func_80726EE0(u8 arg0) {
    s16 i;
    C1Node *node;
    s32 mode;
    u32 sel;

    mode = arg0;
    node = D_80755694->nodes;
    for (i = 0; i < D_80755694->count; i++, node++) {
        if (node->unk46 & 0x80) {
            continue;
        }
        sel = mode;
        if ((node->unk42 == 5) && (node->unk18->unk5C & 2)) {
            actorQueueDelayedCallback(node->unk18, 0, 8, 0, 0, 0, 1);
        } else if ((node->unk42 == 6) && (node->unk18->unk5C & 2)) {
            node->unk42 = 7;
            node->unk24 = node->unk14 * 0x1E;
            func_8061CFCC(node->unk18);
            actorDespawn(node->unk18);
        }
        switch (sel) {
            case 0:
            case 1:
                node->unk46 |= 2;
                break;
            case 2:
                node->unk46 &= ~2;
                break;
        }
    }
}
