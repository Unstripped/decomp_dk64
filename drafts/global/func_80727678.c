// func_80727678 (src/global/1295B0.c): text-identical, reloc only: all instructions match; only the preheader lui/lbu of D_807FBB70.unk254 relocs against D_807FBB70 instead of D_807FBDC4 (same address). Needs s32 pad local declared first (frame slot of sp4A).
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

#define C1ACT44 ((C1ActorView *)D_807FBB44)

extern C1NodeList *D_80755694;
extern C1SpawnEntry D_8075EB80[];
s32 actorSpawn(s32, s32);
void func_80726744(void *, void *);

extern s32 D_8076A0A8;
s32 func_807317FC(s16, s16);
void func_8067AB20(void *, void *, s32, s32, s16 *, s32);

void func_80727678(void) {
    s32 pad;
    s16 sp4A;
    C1Node *node;
    s16 j;
    s16 *ptr;
    C1SpawnEntry *entry;

    node = D_80755694->nodes;
    for (sp4A = 0; sp4A < D_80755694->count; sp4A++, node++) {
        for (j = 0; j < D_807FBB70.unk254; j++) {
            ptr = D_807FBB70.unk278[j];
            if (node->unk13 == *ptr) {
                switch (D_807FBB70.unk258[j]) {
                    case 1:
                        if ((node->unk42 == 0) && (func_807317FC(((s16 *)&D_8076A0A8)[1], node->unk13) != 0) && (entry = &D_8075EB80[node->unk44], actorSpawn(entry->unk0, entry->unk2) != 0)) {
                            func_80726744(D_807FBB44, node);
                        } else if ((node->unk42 == 3) && (func_807317FC(((s16 *)&D_8076A0A8)[1], node->unk13) != 0)) {
                            entry = &D_8075EB80[node->unk44];
                            if (actorSpawn(entry->unk0, entry->unk2) != 0) {
                                func_80726744(D_807FBB44, node);
                                C1ACT44->unk154 = 0x36;
                            }
                        }
                        break;
                    case 2:
                        if (node->unk42 == 7) {
                            node->unk42 = node->unk12;
                        }
                        break;
                    case 3:
                    case 4:
                        if (node->unk42 == 5) {
                            func_8067AB20(D_807FBB40, node->unk18, 0x01000000, D_807FBB70.unk258[j] & 0xFF, ptr, 0);
                        }
                        break;
                }
            }
        }
    }
}
