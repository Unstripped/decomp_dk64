#include "common.h"
#include "actor.h"

extern Actor *D_807FBB40;
extern Actor *D_807FBB44;
extern Actor *D_807FBB4C;
extern ActorGlobalState D_807FBB70;
extern void *D_807FC924;

#pragma GLOBAL_ASM("asm/global/nonmatchings/1295B0/func_807248B0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/1295B0/func_80724994.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/1295B0/func_80724A20.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/1295B0/func_80724A9C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/1295B0/func_80724B5C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/1295B0/func_80724C2C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/1295B0/func_80724C78.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/1295B0/func_80724CA4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/1295B0/func_80724D28.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/1295B0/func_80724DB0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/1295B0/func_80724E48.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/1295B0/func_807255A8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/1295B0/func_80725B38.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/1295B0/func_80725BA4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/1295B0/func_80725DC0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/1295B0/func_80725ED4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/1295B0/func_80726164.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/1295B0/func_807264B0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/1295B0/func_807266E8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/1295B0/func_80726744.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/1295B0/func_80726D7C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/1295B0/func_80726DC0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/1295B0/func_80726DEC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/1295B0/func_80726E60.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/1295B0/func_80726EE0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/1295B0/func_8072707C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/1295B0/func_807270C0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/1295B0/func_80727194.s")

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

Actor *func_807271F4(s16 arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5, s16 arg6) {
    s16 i;
    C1Node *node;
    C1SpawnEntry *entry;

    node = D_80755694->nodes;
    for (i = 0; i < D_80755694->count; i++, node++) {
        if ((arg0 == node->unk13) && (node->unk42 != 5)) {
            entry = &D_8075EB80[node->unk44];
            if (actorSpawn(entry->unk0, entry->unk2) != 0) {
                node->unk46 |= 4;
                func_80726744(D_807FBB44, node);
                if (arg1 != 0) {
                    C1ACT44->unk7C = arg1;
                    C1ACT44->unk80 = arg2;
                    C1ACT44->unk84 = arg3;
                    C1ACT44->unkEE = arg4;
                    C1ACT44->unkE6 = arg4;
                }
                C1ACT44->unkB8 = arg5;
                C1ACT44->unkC0 = arg6;
                C1ACT44->unk6A = 0;
                return D_807FBB44;
            }
        }
    }
    return 0;
}

typedef struct C1Pt {
    /* 0x0 */ s16 x;
    /* 0x2 */ s16 y;
    /* 0x4 */ s16 z;
    /* 0x6 */ u8 pad6[4];
} C1Pt; // size = 0xA

typedef struct C1Tbl98 {
    /* 0x00 */ u8 pad0[0x20];
    /* 0x20 */ u8 (*unk20)[2];
} C1Tbl98;

typedef struct C1TblA0 {
    /* 0x00 */ u8 pad0[0x14];
    /* 0x14 */ u8 *unk14;
} C1TblA0;

extern C1TblA0 *D_807FDCA0;
f32 mathAngleBetweenPointsDeg(s32, s32, s16, s16);
s32 func_80611A44(void);

#define C1PTS ((C1Pt *)D_807FDCA0->unk14)
#define C1PT(i) ((C1Pt *)(D_807FDCA0->unk14 + (i)))

#define C1IDX (((C1Tbl98 *)D_807FDC98)->unk20[arg1][0] * 0xA)

void func_807273A8(s16 arg0, u8 arg1) {
    u8 tbl;
    s16 sp34;

    tbl = ((C1Tbl98 *)D_807FDC98)->unk20[arg1][0];
    sp34 = (s16)(s32)((mathAngleBetweenPointsDeg((s32)D_807FDC94->unk7C, (s32)D_807FDC94->unk84, C1PTS[tbl].x, C1PTS[tbl].z) * 4096.0f) / 360.0f);
    if (func_807271F4(arg0, C1PTS[tbl].x, C1PTS[tbl].y, C1PTS[tbl].z, sp34, ((func_80611A44() >> 0xF) % 100) + 0x64, ((func_80611A44() >> 0xF) % 100) + 0xC8) != 0) {
        C1ACT44->unk154 = 0x17;
        C1ACT44->unk155 = 0;
    }
}

s16 mathAngleBetweenPoints2D(f32, f32, f32, f32);

void func_8072752C(s16 arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5, s16 arg6, s16 arg7, s16 arg8) {
    s16 sp46;
    f32 sp40;
    s32 dx;
    s32 dy;
    s32 dz;

    dx = arg4 - arg1;
    dy = arg5 - arg2;
    dz = arg6 - arg3;
    sp46 = mathAngleBetweenPoints2D((f32)arg4, (f32)arg6, (f32)arg1, (f32)arg3);
    sp40 = sqrtf((f32)((dx * dx) + (dy * dy) + (dz * dz)));
    dy = (s32)(sqrtf((f32)((dx * dx) + (dz * dz))) / (sp40 / (f32)arg7));
    if (func_807271F4(arg0, arg1, arg2, arg3, sp46, dy, arg8) != 0) {
        C1ACT44->unk154 = 0x17;
        C1ACT44->unk155 = 0;
    }
}

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

extern u8 D_80755698[];
extern Struct807FD580 *D_807FD580;

void func_807278C0(C1Node *arg0) {
    u8 temp_v0;

    if ((D_8076A0A8 == 0x30) && (D_807FD580->unk1F0 & 0x100000) && (temp_v0 = arg0->unk0, (D_80755698[temp_v0] != 0xA))) {
        switch (temp_v0) {
            case 28:
                arg0->unk44 = 0x63;
                return;
            case 9:
                arg0->unk44 = 0x54;
                return;
            case 44:
                arg0->unk44 = 0x67;
                return;
        }
    } else {
        arg0->unk44 = arg0->unk0;
    }
}

typedef struct C1State90 {
    /* 0x00 */ u8 pad0[4];
    /* 0x04 */ C1ActorView *unk4;
    /* 0x08 */ u8 pad8[0x10];
    /* 0x18 */ u16 unk18;
} C1State90;

typedef struct C1Sub174 {
    /* 0x00 */ u8 pad0[0xD4];
    /* 0xD4 */ s16 unkD4;
} C1Sub174;

typedef struct C1PlayerView {
    /* 0x000 */ u8 pad0[4];
    /* 0x004 */ C1ActorView *unk4;
    /* 0x008 */ u8 pad8[0x2E8];
} C1PlayerView; // size = 0x2F0

#define C1S90 ((C1State90 *)D_807FDC90)
#define C1PLAYERS ((C1PlayerView *)D_807FC924)
#define C1ACT40 ((C1ActorView *)D_807FBB40)

extern s16 D_8076A0AA;
extern s32 D_807FBB64;
extern u8 D_807FC928;
void actorDeregisterActive(void *);
void actorDespawn(void *);
void actorRegisterActive(void *);
void func_8061CFCC(void *);
s16 func_806531B8(f32, f32, f32, s32);
s32 func_80727F20(void *, s32);
s32 func_80728004(void *, s32);
s32 func_807280C8(void *, s32);
s32 func_8072818C(void *, s32);
void sfxStopChannel(s32, s32);
void sfxStopSlotSound(void *, s32);

void func_80727958(void) {
    s16 i;
    C1Node *node;
    s32 dist;
    u8 active;
    s32 best;
    s16 p;
    C1SpawnEntry *entry;
    C1ActorView *pa;
    f32 dz;
    f32 dx;
    s32 d;
    C1Sub174 *sub;

    node = D_80755694->nodes;
    for (i = 0; i < D_80755694->count; i++, node++) {
        active = (node->unk42 >= 5) && (node->unk42 < 7);
        if (active) {
            D_807FDC90 = (Struct807FDC90 *)node->unk18->unk174;
        }
        dist = D_8075EB80[node->unk44].unkE * 0x64;
        dist = dist * dist;
        if (active) {
            node->unk40 = node->unk18->unk12C;
        }
        if ((dist == 0) || (node->unk46 & 4) || (D_807FBB64 & 0x100)) {
            dist = 0x7FFFFFFF;
        }
        if (active && (node->unk18->unk154 == 0x3B)) {
            func_8061CFCC(node->unk18);
            actorDespawn(node->unk18);
            node->unk42 = 0;
        } else if (active && (node->unk18->unk154 == 0x3C)) {
            func_8061CFCC(node->unk18);
            actorDespawn(node->unk18);
            node->unk42 = node->unk12;
            node->unk46 &= 0xFFFB;
        } else if ((node->unk42 == 7) && (node->unk24 != 0)) {
            if (!(node->unk46 & 2)) {
                node->unk24 -= 1;
                if (node->unk24 == 0) {
                    node->unk43 += 1;
                    node->unk42 = node->unk12;
                    node->unk40 = func_806531B8((f32)node->unk4, (f32)node->unk6, (f32)node->unk8, 0);
                    func_807278C0(node);
                    entry = &D_8075EB80[node->unk44];
                    if (actorSpawn(entry->unk0, entry->unk2) != 0) {
                        func_80726744(D_807FBB44, node);
                        C1ACT44->unk154 = 0x36;
                        node->unk46 |= 1;
                    }
                }
            }
        } else if (node->unk42 == 2) {
            if ((func_80727F20(node, dist) != 0) && (func_807317FC(D_8076A0AA, node->unk13) != 0)) {
                func_807278C0(node);
                entry = &D_8075EB80[node->unk44];
                if (actorSpawn(entry->unk0, entry->unk2) != 0) {
                    func_80726744(D_807FBB44, node);
                }
            }
        } else if (active && (node->unk18->unk154 == 0x40)) {
            node->unk42 = 7;
            node->unk24 = node->unk14 * 0x1E;
            if (node->unk1C->unk1C == node->unk18) {
                node->unk1C->unk1C = 0;
            }
            func_8061CFCC(node->unk18);
            actorDespawn(node->unk18);
        } else if (active) {
            best = 0xF423F;
            if ((C1S90->unk4->unk5C & 1) && (C1S90->unk4->unk154 == 0x67)) {
                if ((node->unk18->unk5C & 2) && (node->unk42 == 5)) {
                    if ((node->unk18->unk154 != 0x16) && (node->unk18->unk154 != 0x37) && !(node->unk46 & 0x40)) {
                        node->unk18->unk154 = 0x16;
                        node->unk18->unk155 = 0;
                    }
                }
            }
            if (D_807FC928 >= 2) {
                for (p = 0; p < D_807FC928; p++) {
                    sub = (C1Sub174 *)C1PLAYERS[0].unk4->unk174;
                    dz = C1ACT40->unk84 - C1PLAYERS[p].unk4->unk84;
                    dx = C1ACT40->unk7C - C1PLAYERS[p].unk4->unk7C;
                    d = (s32)((dz * dz) + (dx * dx));
                    if ((d < best) || (sub->unkD4 != 0)) {
                        pa = C1PLAYERS[p].unk4;
                        best = d;
                        C1S90->unk4 = pa;
                    }
                }
            }
            if (node->unk42 == 6) {
                if (func_8072818C(node, dist) != 0) {
                    actorDespawn(node->unk18);
                    node->unk42 = node->unk12;
                } else if (func_80728004(node, dist) != 0) {
                    actorRegisterActive(node->unk18);
                    node->unk42 = 5;
                    node->unk46 |= 0x8000;
                }
            } else if ((node->unk42 == 5) && (func_807280C8(node, dist) != 0)) {
                if ((node->unk18->unk154 != 0x16) && (node->unk18->unk154 != 0x37)) {
                    if (node->unk18->unk58 == 0xF8) {
                        sfxStopChannel(0x42, 0);
                    }
                    sfxStopSlotSound(node->unk18, 0);
                    sfxStopSlotSound(node->unk18, 1);
                    actorDeregisterActive(node->unk18);
                    node->unk42 = 6;
                    C1S90->unk18 = 0;
                }
            }
        }
    }
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/1295B0/func_80727F20.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/1295B0/func_80728004.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/1295B0/func_807280C8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/1295B0/func_8072818C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/1295B0/func_8072827C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/1295B0/func_80728300.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/1295B0/func_8072881C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/1295B0/func_80728950.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/1295B0/func_807289B0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/1295B0/func_807289E8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/1295B0/func_80729AA4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/1295B0/D_8075EB80.s")
