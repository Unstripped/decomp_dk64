#include "common.h"
#include "actor.h"

extern Actor *gCurrentActor;
extern Actor *gSpawnedActor;
extern Actor *D_807FBB48;
extern Actor *D_807FBB4C;
extern ActorGlobalState D_807FBB70;
extern u8 gPlayerCount;
extern u8 gCurrentPlayerIndex;
extern Struct807FD580 *gActivePlayerState;
extern s16 D_807FD584;
extern u16 D_807FD63C;

extern s16 D_807FC930[];

void collectibleCountsClear(void) {
    s16 i;

    for (i = 0; i < 0xE; i++) {
        D_807FC930[i] = 0;
    }
}

extern u8 gPlayerCharacterId[];

typedef struct G00Row {
    /* 0x0 */ s32 unk0;
    /* 0x4 */ s32 unk4;
    /* 0x8 */ s32 unk8;
    /* 0xC */ s32 unkC;
} G00Row;

extern G00Row D_8075C410[];

s32 playerGetModelAssetId(void) {
    return D_8075C410[gPlayerCharacterId[0]].unk0;
}

typedef struct G00SpawnSub {
    /* 0x0 */ s32 unk0;
    /* 0x4 */ Actor *unk4;
    /* 0x8 */ u8 unk8;
} G00SpawnSub;

s32 actorSpawn(s32, s32);
void actorCopyPoseAndScale(Actor *, Actor *, f32);

void func_806C7B50(s32 arg0, u8 arg1, Actor *arg2) {
    G00SpawnSub *sub;

    actorSpawn(arg0, 0x82);
    actorCopyPoseAndScale(gSpawnedActor, arg2, 0.15f);
    sub = gSpawnedActor->unk174;
    sub->unk4 = arg2;
    sub->unk8 = arg1;
}

void func_806C7BAC(s32 arg0, Actor *arg1) {
    G00SpawnSub *sub;

    actorSpawn(0x25, 0x8C);
    actorCopyPoseAndScale(gSpawnedActor, D_807FBB48, 0.15f);
    sub = gSpawnedActor->unk174;
    sub->unk0 = arg0;
    sub->unk4 = arg1;
}

extern u8 D_80750AB4;
extern u8 D_80750AB8;
extern u8 D_80750AC0;

typedef struct G00Sub6 {
    /* 0x0 */ s16 unk0;
    /* 0x2 */ s16 unk2;
    /* 0x4 */ s16 unk4;
} G00Sub6;

typedef struct G00Block {
    /* 0x000 */ u8 unk0;
    /* 0x001 */ u8 pad1[3];
    /* 0x004 */ Actor *unk4;
    /* 0x008 */ u8 pad8[0x208];
    /* 0x210 */ f32 unk210;
    /* 0x214 */ f32 unk214;
    /* 0x218 */ f32 unk218;
    /* 0x21C */ f32 unk21C;
    /* 0x220 */ f32 unk220;
    /* 0x224 */ f32 unk224;
    /* 0x228 */ f32 unk228;
    /* 0x22C */ f32 unk22C;
    /* 0x230 */ f32 unk230;
    /* 0x234 */ u8 pad234[0xC];
    /* 0x240 */ f32 unk240;
    /* 0x244 */ f32 unk244;
    /* 0x248 */ f32 unk248;
    /* 0x24C */ u8 pad24C[0x24];
    /* 0x270 */ s16 unk270;
    /* 0x272 */ s16 unk272;
    /* 0x274 */ s16 unk274;
    /* 0x276 */ s16 unk276;
    /* 0x278 */ s16 unk278;
    /* 0x27A */ s16 unk27A;
    /* 0x27C */ f32 unk27C;
    /* 0x280 */ f32 unk280;
    /* 0x284 */ f32 unk284;
    /* 0x288 */ f32 unk288;
    /* 0x28C */ u8 pad28C[4];
    /* 0x290 */ s16 unk290;
    /* 0x292 */ u8 pad292[2];
    /* 0x294 */ G00Sub6 *unk294;
    /* 0x298 */ s16 *unk298;
    /* 0x29C */ s16 unk29C;
    /* 0x29E */ u8 pad29E[0x22];
    /* 0x2C0 */ u8 unk2C0;
    /* 0x2C1 */ u8 unk2C1;
    /* 0x2C2 */ u8 pad2C2[0x1A];
    /* 0x2DC */ u8 unk2DC[0xE];
    /* 0x2EA */ u8 unk2EA;
    /* 0x2EB */ u8 unk2EB;
    /* 0x2EC */ u8 pad2EC[4];
} G00Block; // size = 0x2F0

extern G00Block *gPlayerSlots;

void func_806C7C10(void) {
    gPlayerCount = D_80750AC0;
    gPlayerSlots = 0;
    if (gPlayerCount >= 2) {
        switch (D_80750AB8) {
        case 0:
            D_80750AB4 = gPlayerCount;
            break;
        case 1:
            D_80750AB4 = 1;
            break;
        }
    } else {
        D_80750AB4 = 1;
        D_80750AB8 = 0;
    }
}

typedef struct G00Entry {
    /* 0x0 */ u8 unk0;
    /* 0x1 */ u8 unk1;
    /* 0x2 */ u8 unk2;
    /* 0x3 */ u8 unk3;
    /* 0x4 */ s16 unk4;
    /* 0x6 */ s16 unk6;
    /* 0x8 */ s16 unk8;
    /* 0xA */ s16 unkA;
} G00Entry;

extern G00Entry D_80750948[];
extern u8 D_80750ABC;

G00Entry *cameraFindViewportEntry(u8 arg0) {
    u8 i;
    s32 found;

    i = 0;
    found = 0;
    do {
        if (gPlayerCount == D_80750948[i].unk0 && D_80750AB8 == D_80750948[i].unk1 && arg0 == D_80750948[i].unk3 &&
            (D_80750948[i].unk2 & D_80750ABC)) {
            found = 1;
        } else {
            i++;
        }
    } while (found == 0);
    return &D_80750948[i];
}

typedef struct G00Player306 {
    /* 0x000 */ u8 pad0[0x2FB];
    /* 0x2FB */ s8 unk2FB;
    /* 0x2FC */ u8 pad2FC;
    /* 0x2FD */ s8 unk2FD;
    /* 0x2FE */ u8 pad2FE[8];
} G00Player306;

void *heapAlloc(s32);
void heapClearBlock(void *);
void func_806C850C(s32, u8);
void func_80708BB8(void *);
void healthRefill(u8);
void func_806C80E4(void);
extern u8 D_807FC950[][0x5E];
extern G00Sub6 D_807ECD10[];
extern s16 D_807ECD48[];
extern u32 D_8074458C[];
extern f32 D_807444C4;
extern u8 D_80750AD0;
extern s32 D_807FBB64;
extern u32 D_807FBB68;
extern u16 D_807FD570;

void func_806C7D40(s32 arg0) {
    G00Block *blk;
    s32 i;
    u8 sel;
    G00Entry *e;

    gPlayerSlots = heapAlloc(gPlayerCount * 0x2F0);
    heapClearBlock(gPlayerSlots);
    for (i = 0; i < gPlayerCount; i++) {
        blk = &gPlayerSlots[i];
        blk->unk0 = 1;
        sel = i;
        gCurrentPlayerIndex = i;
        func_806C850C(arg0++, sel);
        blk->unk4 = D_807FBB48;
        if (i == 0) {
            D_807FBB4C = D_807FBB48;
        }
        blk->unk218 = 100.0f;
        blk->unk214 = 100.0f;
        blk->unk210 = 100.0f;
        blk->unk224 = 100.0f;
        blk->unk220 = 100.0f;
        blk->unk21C = 100.0f;
        blk->unk230 = 0.0f;
        blk->unk22C = 0.0f;
        blk->unk228 = 0.0f;
        blk->unk248 = 0.0f;
        blk->unk240 = 0.0f;
        blk->unk244 = 1.0f;
        e = cameraFindViewportEntry(sel);
        blk->unk270 = e->unk4;
        blk->unk272 = e->unk6;
        blk->unk274 = e->unk8;
        blk->unk276 = e->unkA;
        if (osViGetCurrentMode() == D_8074458C[osTvType + osTvType]) {
            blk->unk270 *= 2;
            blk->unk272 *= 2;
            blk->unk274 += 1;
            blk->unk274 *= 2;
            blk->unk274 -= 1;
            blk->unk276 += 1;
            blk->unk276 *= 2;
            blk->unk276 -= 1;
        }
        blk->unk278 = blk->unk274 - blk->unk270;
        blk->unk27A = blk->unk276 - blk->unk272;
        blk->unk27C = 45.0f;
        blk->unk284 = 10.0f;
        blk->unk280 = (f32)blk->unk278 / (f32)blk->unk27A;
        blk->unk288 = D_807444C4;
        blk->unk290 = 0;
        blk->unk294 = &D_807ECD10[i];
        blk->unk298 = &D_807ECD48[i];
        blk->unk29C = -1;
        blk->unk2C0 = 1;
        blk->unk2C1 = 1;
        blk->unk2EA = 0;
        blk->unk2EB = 0;
        func_80708BB8(blk->unk2DC);
        if (((D_807FBB64 & 1) && !(D_807FBB68 & 2)) ||
            (((G00Player306 *)D_807FC950)[i].unk2FB + ((G00Player306 *)D_807FC950)[i].unk2FD <= 0)) {
            healthRefill(sel);
        }
    }
    if (D_807FD570 != 0) {
        func_806C80E4();
        D_807FD570 = 0;
    }
    if (gPlayerCount >= 2) {
        actorSpawn(0x13E, 0);
    }
    D_80750AD0 = (D_80750AB8 == 0) && (gPlayerCount >= 2);
}


typedef struct G00View1F0 {
    /* 0x000 */ u8 pad0[0x1F0];
    /* 0x1F0 */ s32 unk1F0;
} G00View1F0;

f32 func_80612790(s16);
f32 func_80612794(s16);
void actorListSpawnNodeEntryDefault(s16, f32, f32, f32, s32, f32, Actor *);

void func_806C80E4(void) {
    f32 sp34;
    f32 sp30;
    f32 sp2C;
    f32 sp28;
    f32 var2;

    if (D_807FD570 == 0x55) {
        sp28 = 20.0f;
    } else {
        sp28 = 0.0f;
    }
    sp30 = func_80612794(D_807FBB4C->yaw) * sp28;
    var2 = func_80612790(D_807FBB4C->yaw) * sp28;
    actorListSpawnNodeEntryDefault((s16)D_807FD570, D_807FBB4C->x + sp30, (f32)((f64)D_807FBB4C->y + 7.0),
                  D_807FBB4C->z + var2, 0, 1.0f, D_807FBB4C);
    ((G00View1F0 *)D_807FBB4C->unk174)->unk1F0 |= 0x01000000;
}

void cameraSetViewportYRange(s16 arg0, s16 arg1) {
    G00Block *p;

    p = gPlayerSlots;
    p->unk27A = arg1 - arg0;
    p->unk272 = arg0;
    p->unk276 = arg1;
    p->unk280 = (f32)p->unk278 / (f32)p->unk27A;
}

typedef struct G00Tbl8 {
    /* 0x00 */ f32 f[8];
} G00Tbl8;

typedef struct G00Tbl11 {
    /* 0x00 */ f32 f[11];
} G00Tbl11;

typedef struct G00Tbl4 {
    /* 0x00 */ f32 f[4];
} G00Tbl4;

typedef struct G00Vtx {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
} G00Vtx;

typedef struct G00Out {
    /* 0x000 */ f32 unk0;
    /* 0x004 */ f32 unk4;
    /* 0x008 */ f32 unk8;
    /* 0x00C */ f32 unkC;
    /* 0x010 */ f32 unk10;
    /* 0x014 */ u8 unk14;
    /* 0x015 */ u8 pad15[3];
    /* 0x018 */ s32 unk18;
    /* 0x01C */ G00Vtx unk1C[12];
} G00Out; // size = 0x13C

extern G00Tbl8 D_80750AD8;
extern G00Tbl11 D_80750AF8;
extern G00Tbl4 D_80750B24;

void func_806C8220(s32 arg0, void *arg1, s32 arg2) {
    f32 pad0;
    G00Tbl8 sp74;
    G00Tbl11 sp48;
    G00Tbl4 sp38;
    f32 *tbl;
    f32 sign;
    s32 count;
    s32 n;
    s32 i;
    s32 j;
    G00Vtx *v;
    G00Vtx *new_var;
    G00Out *out;

    sp74 = D_80750AD8;
    count = 1;
    n = 4;
    sp48 = D_80750AF8;
    out = arg1;
    tbl = sp38.f;
    sp38 = D_80750B24;
    sign = 1.0f;
    switch ((u32)arg2) {
    case 3:
        count = 1;
        n = 11;
        tbl = sp48.f;
        break;
    case 5:
        count = 2;
        n = 8;
        tbl = sp74.f;
        break;
    case 2:
        count = 1;
        n = 4;
        tbl = sp38.f;
        break;
    default:
        return;
    }
    for (i = 0; i < count; i++) {
        v = out->unk1C;
        out->unk14 = 2;
        out->unk18 = arg2;
        out->unkC = 0.0f;
        out->unk8 = 0.0f;
        out->unk4 = 0.0f;
        out->unk0 = 0.0f;
        out->unk10 = -128.0f;
        do {
            for (j = 0; j < n; j++, v++) {
                v->unk4 = 0.0;
                new_var = v;
                new_var->unk0 = tbl[j] * sign;
                new_var->unk8 = 0.0;
                new_var->unk14 = 0.0f; new_var->unkC = 0.0f; new_var->unk10 = 0.0f;
            }
            out++;
        } while (0);
        sign = -sign;
    }
}


typedef struct G00Sub4 {
    /* 0x00 */ u8 pad0[0x1C];
    /* 0x1C */ u8 *unk1C;
    /* 0x20 */ u8 *unk20;
    /* 0x24 */ u8 *unk24;
} G00Sub4;

typedef struct G00ActorView {
    /* 0x000 */ u8 pad0[0xC4];
    /* 0x0C4 */ f32 unkC4;
    /* 0x0C8 */ f32 unkC8;
    /* 0x0CC */ u8 padCC[0x12];
    /* 0x0DE */ s16 unkDE;
    /* 0x0E0 */ u8 padE0[0x66];
    /* 0x146 */ s16 unk146;
    /* 0x148 */ u8 pad148[0x30];
    /* 0x178 */ G00Out *unk178;
} G00ActorView;

typedef struct G00Player {
    /* 0x000 */ u8 pad0[0x16];
    /* 0x016 */ s16 unk16;
    /* 0x018 */ u8 pad18[0xE];
    /* 0x026 */ s16 unk26;
    /* 0x028 */ u8 pad28[0xA0];
    /* 0x0C8 */ s16 unkC8;
    /* 0x0CA */ u8 unkCA;
    /* 0x0CB */ u8 padCB[9];
    /* 0x0D4 */ s16 unkD4;
    /* 0x0D6 */ u8 padD6[2];
    /* 0x0D8 */ u8 unkD8;
    /* 0x0D9 */ u8 padD9[3];
    /* 0x0DC */ u8 padDC[0x20];
    /* 0x0FC */ s32 unkFC;
    /* 0x100 */ s32 unk100;
    /* 0x104 */ Actor *unk104;
    /* 0x108 */ u8 pad108[4];
    /* 0x10C */ u8 unk10C;
    /* 0x10D */ u8 pad10D[0x11];
    /* 0x11E */ s16 unk11E;
    /* 0x120 */ s32 unk120;
    /* 0x124 */ u8 pad124[0x7C];
    /* 0x1A0 */ s16 unk1A0;
    /* 0x1A2 */ u8 pad1A2[2];
    /* 0x1A4 */ u8 unk1A4;
    /* 0x1A5 */ u8 pad1A5[7];
    /* 0x1AC */ s32 unk1AC;
    /* 0x1B0 */ s32 unk1B0;
    /* 0x1B4 */ u8 pad1B4[0xC];
    /* 0x1C0 */ f32 unk1C0;
    /* 0x1C4 */ f32 unk1C4;
    /* 0x1C8 */ f32 unk1C8;
    /* 0x1CC */ f32 unk1CC;
    /* 0x1D0 */ f32 unk1D0;
    /* 0x1D4 */ f32 unk1D4;
    /* 0x1D8 */ u8 pad1D8[0x16];
    /* 0x1EE */ s16 unk1EE;
    /* 0x1F0 */ s32 unk1F0;
    /* 0x1F4 */ u8 pad1F4[0x2A];
    /* 0x21E */ s16 unk21E;
    /* 0x220 */ u8 pad220[0x24];
    /* 0x244 */ u8 unk244;
    /* 0x245 */ u8 unk245;
    /* 0x246 */ u8 pad246;
    /* 0x247 */ s8 unk247;
    /* 0x248 */ u8 pad248[8];
    /* 0x250 */ s32 unk250;
    /* 0x254 */ u8 pad254[4];
    /* 0x258 */ f32 unk258;
    /* 0x25C */ f32 unk25C;
    /* 0x260 */ u8 pad260[4];
    /* 0x264 */ s32 unk264;
} G00Player;

typedef struct G00Slot34 {
    /* 0x00 */ u8 pad0[4];
    /* 0x04 */ f32 unk4;
    /* 0x08 */ u8 pad8[8];
    /* 0x10 */ f32 unk10[4];
    /* 0x20 */ s16 unk20[4];
    /* 0x28 */ s16 unk28;
    /* 0x2A */ u8 pad2A[0xA];
} G00Slot34;

#define G00_P ((G00Player *)gActivePlayerState)
#define G00_A48 ((G00ActorView *)D_807FBB48)

extern s32 controllerGetPort(s32);
extern s32 gCurrentMap;
extern Actor *gCamActor;
extern f32 D_80753578[];
extern f32 D_807535E8[];
extern G00Slot34 gPlayerPadState[];
void func_806E2C74(Actor *);
s32 flagGet(s32, s32);
void func_806F09F0(Actor *, u16);
void playerResumeLocomotion(Actor *);
void func_806C90C4(s32);
void func_806C8984(void);
void actorSetInteractionTimer(Actor *);

void func_806C850C(s32 arg0, u8 arg1) {
    G00Row *row;
    u32 sel;
    s32 i;

    sel = arg1;
    if (gPlayerCount >= 2) {
        gPlayerCharacterId[sel] = gPlayerCharacterId[controllerGetPort(sel)];
    }
    if (sel == 0 && gCurrentMap == 0x50) {
        gPlayerCharacterId[0] = 0;
    }
    row = &D_8075C410[gPlayerCharacterId[sel]];
    actorSpawn(row->unk0, row->unk8);
    gSpawnedActor->flags &= ~0x1000;
    gSpawnedActor->flags |= row->unkC;
    gSpawnedActor->unk16E[0] = 0x42;
    gSpawnedActor->unk16E[1] = 0x42;
    gSpawnedActor->flags |= 0x01000000;
    if (gPlayerCount >= 2) {
        gSpawnedActor->renderFlags |= 0x200;
    }
    gSpawnedActor->flags2 |= 0xC0;
    ((G00Sub4 *)gSpawnedActor->unk4)->unk1C = heapAlloc(0x100);
    *((G00Sub4 *)gSpawnedActor->unk4)->unk1C = 0;
    ((G00Sub4 *)gSpawnedActor->unk4)->unk20 = heapAlloc(0x200);
    *((G00Sub4 *)gSpawnedActor->unk4)->unk20 = 0xFF;
    ((G00Sub4 *)gSpawnedActor->unk4)->unk24 = heapAlloc(0x200);
    *((G00Sub4 *)gSpawnedActor->unk4)->unk24 = 0xFF;
    D_807FBB48 = gSpawnedActor;
    gActivePlayerState = D_807FBB48->unk174;
    G00_P->unk247 = -1;
    G00_P->unk1A4 = sel;
    G00_P->unk11E = -1;
    G00_P->unk244 = 0;
    G00_P->unk120 = -0x64;
    D_807FD584 = row->unk4;
    G00_P->unk1EE = gSpawnedActor->actorType;
    func_806E2C74(D_807FBB48);
    actorSpawn(0xBC, 0);
    G00_P->unk104 = gSpawnedActor;
    if (sel == 0) {
        gCamActor = gSpawnedActor;
    }
    gSpawnedActor->flags |= 0x100000;
    actorSetInteractionTimer(D_807FBB48);
    G00_P->unk26 = 0x64;
    G00_A48->unkC4 = D_80753578[D_807FD584];
    G00_A48->unkC8 = D_807535E8[D_807FD584];
    G00_P->unk250 = 0x78;
    G00_P->unkD4 = 0;
    G00_P->unkD8 = 0;
    G00_P->unkFC = 0;
    G00_P->unk100 = 0;
    G00_P->unk16 = 0;
    G00_P->unk10C = 0;
    G00_P->unk1A0 = 0;
    G00_P->unk1C0 = 0.15f;
    G00_P->unk1C4 = 0.15f;
    G00_P->unk1C8 = 0.15f;
    G00_P->unk1CC = 0.15f;
    G00_P->unk1D0 = 0.15f;
    G00_P->unk1D4 = 0.15f;
    G00_P->unk245 = 0;
    G00_P->unk21E = 0x1E;
    G00_P->unkC8 = -1;
    G00_P->unkCA = 0;
    G00_P->unkC8 = -1;
    G00_P->unk264 = -1;
    G00_P->unk258 = 1.0f;
    G00_P->unk25C = 1.0f;
    if (flagGet(0xCE, 0) != 0) {
        G00_P->unk1F0 |= 0x100000;
    }
    func_806C8220(1, G00_A48->unk178, D_807FBB48->actorType);
    G00_A48->unk146 = 0;
    func_806F09F0(D_807FBB48, *(u16 *)((u8 *)D_807FBB48 + 0x5A));
    G00_A48->unkDE = 0x400;
    G00_P->unk1B0 = 0;
    G00_P->unk1AC = 0;
    for (i = 0; i < 4; i++) {
        gPlayerPadState[sel].unk20[i] = gPlayerPadState[sel].unk28;
        gPlayerPadState[sel].unk10[i] = gPlayerPadState[sel].unk4;
    }
    playerResumeLocomotion(D_807FBB48);
    func_806C90C4(arg0);
    func_806C8984();
}

extern s32 gCurrentMap;
extern s16 D_80753354[];

typedef struct L6C8984View {
    /* 0x00 */ u8 pad0[0x48];
    /* 0x48 */ s16 unk48;
    /* 0x4A */ u8 pad4A[0x3E];
    /* 0x88 */ Actor *unk88;
} L6C8984View;

#define L6V ((L6C8984View *)gActivePlayerState)

void actorScriptStart(Actor *, s32);
void actorScriptStartByIndex(Actor *, s32);
void func_80613C48(Actor *, s32, f32, f32);
void playerSetBaseGravity(void);
void func_806F0D68(Actor *);
void commandSetFlags(s32, s32);
void commandSetColor(s32, s32, s32);
void commandSetParameters(s32, s32, s32, s32, s32, s32);
void func_80028840(void);
void actorSpawnChildActor(Actor *);
void func_806C7B50(s32, u8, Actor *);

void func_806C8984(void) {
    f32 scale;

    scale = -1.0f;
    switch (gCurrentMap) {
    case 0x50:
        actorSpawn(0x146, 0);
        return;
    case 0xF:
        actorSpawn(0x14F, 0);
        return;
    case 0xB1:
    case 0xB4:
    case 0xB5:
    case 0xB6:
        actorSpawn(0x150, 0);
        return;
    case 0xB8:
    case 0xBF:
        actorSpawn(0x153, 0);
        return;
    case 0x27:
        if (scale < 0.0f) {
            scale = 0.8f;
        }
    case 0x5:
        if (scale < 0.0f) {
            scale = 1.8f;
        }
    case 0x1:
        if (scale < 0.0f) {
            scale = 1.6f;
        }
        D_807FBB48->unk4->unk34 = D_807FBB48->unk4->unk34 * scale;
        D_807FBB48->unk4->unk38 = D_807FBB48->unk4->unk38 * scale;
        D_807FBB48->unk4->unk3C = D_807FBB48->unk4->unk3C * scale;
        return;
    case 0x68:
    case 0x88:
    case 0x89:
        playerSetBaseGravity();
        actorScriptStart(D_807FBB48, 0);
        func_80613C48(D_807FBB48, 0, 0.0f, 0.0f);
        D_807FBB48->state = 0x7D;
        D_807FBB48->unk155[0] = 0;
        D_807FBB48->flags &= 0xFFFF7FFF;
        D_807FBB48->unk128 = 0;
        actorSpawn(0x11A, 0x21);
        actorScriptStart(gSpawnedActor, 0x232);
        gSpawnedActor->unk11C = (s32)D_807FBB48;
        L6V->unk88 = gSpawnedActor;
        return;
    case 0x6:
        func_806C7B50(0x1D, 0, D_807FBB48);
        return;
    case 0x20:
    case 0x79:
    case 0x7A:
    case 0x7B:
        actorSpawn(0xDA, 0x94);
        L6V->unk88 = gSpawnedActor;
        return;
    case 0x4C:
        commandSetFlags(0, 0);
        commandSetColor(0x6B, 0x30, 0x50);
        commandSetParameters(0x320, 0x82, 0, 0xFF, 0xFF, 0xFF);
        func_80028840();
    case 0x28:
    case 0x51:
        D_807FBB48->state = 0x77;
        D_807FBB48->unk155[0] = 0;
        return;
    case 0x4E:
    case 0x4F:
    case 0x83:
        func_806F0D68(D_807FBB48);
        L6V->unk48 = D_80753354[D_807FD584];
        D_807FBB48->state = 0x62;
        D_807FBB48->unk155[0] = 0;
        actorScriptStartByIndex(D_807FBB48, 0x52);
        return;
    case 0xD3:
        D_807FBB48->state = 0x5F;
        D_807FBB48->unk155[0] = 0;
        actorScriptStartByIndex(D_807FBB48, 0x4B);
        return;
    case 0x53:
    case 0x99:
    case 0xC5:
    case 0xD0:
    case 0xD5:
        D_807FBB48->state = 0x77;
        D_807FBB48->unk155[0] = 0;
        return;
    case 0x6F:
        actorSpawnChildActor(D_807FBB48);
        return;
    }
}

void actorSetInteractionTimer(Actor *arg0) {
    arg0->unk144 = 0x3C;
}

extern f32 D_8075C4B0;
extern u8 D_8075C417;
extern s32 D_8075C420;
extern u8 D_8075C427;
extern G00Row D_8075C430[];

u8 playerLookupKongByActorType(s16 arg0) {
    G00Row *p;

    if (arg0 == D_8075C410[0].unk0) {
        return D_8075C417;
    }
    p = D_8075C430;
    if (arg0 == D_8075C420) {
        return D_8075C427;
    }
loop:
    if (arg0 == p[0].unk0) {
        return *((u8 *)&p[0].unk4 + 3);
    }
    if (arg0 == p[1].unk0) {
        return *((u8 *)&p[1].unk4 + 3);
    }
    if (arg0 == p[2].unk0) {
        return *((u8 *)&p[2].unk4 + 3);
    }
    if (arg0 == p[3].unk0) {
        return *((u8 *)&p[3].unk4 + 3);
    }
    p += 4;
    if (p != (G00Row *)&D_8075C4B0) {
        goto loop;
    }
    return 0;
}

typedef struct G00View1EE {
    /* 0x000 */ u8 pad0[0x1EE];
    /* 0x1EE */ s16 unk1EE;
} G00View1EE;

s32 playerGetResolvedKongId(s32 arg0) {
    s32 var_v1;
    Actor *p;
    G00View1EE *q;

    var_v1 = gPlayerCharacterId[arg0];
    if (var_v1 == 6 || var_v1 == 7) {
        p = gPlayerSlots[arg0].unk4;
        q = ((G00View1EE **)&p->unk174)[arg0];
        var_v1 = playerLookupKongByActorType(q->unk1EE);
    }
    return var_v1;
}

void func_806C8F8C(void *);

void playerSetKongByActorType(s16 arg0) {
    s32 found;
    u8 i;

    found = 0;
    i = gPlayerCharacterId[gCurrentPlayerIndex] = 0;
    do {
        if (arg0 == D_8075C410[i].unk0) {
            found = 1;
        } else {
            gPlayerCharacterId[gCurrentPlayerIndex] = i + 1; i = gPlayerCharacterId[gCurrentPlayerIndex];
        }
    } while (found == 0);
    func_806C8F8C(&D_8075C410[i]);
}

typedef struct G00View8C {
    /* 0x00 */ u8 pad0[0x8C];
    /* 0x8C */ u8 unk8C;
} G00View8C;

void func_806C9C80();
void timerQueueAdd(void *, s32, s32, s32, s32);

void func_806C8EE8(void) {
    gPlayerCharacterId[gCurrentPlayerIndex]++;
    gPlayerCharacterId[gCurrentPlayerIndex] %= 8;
    ((G00View8C *)gActivePlayerState)->unk8C = 0;
    func_806C8F8C(&D_8075C410[gPlayerCharacterId[gCurrentPlayerIndex]]);
    timerQueueAdd(func_806C9C80, 0x14, gCurrentPlayerIndex, 0, 0);
}

typedef struct G01Sub4 {
    /* 0x00 */ u8 pad0[0x1C];
    /* 0x1C */ u8 *unk1C;
    /* 0x20 */ u8 *unk20;
    /* 0x24 */ u8 *unk24;
} G01Sub4;

typedef struct G01Sub104 {
    /* 0x000 */ u8 pad0[0x15F];
    /* 0x15F */ u8 unk15F;
} G01Sub104;

typedef struct G01Ctl {
    /* 0x000 */ u8 pad0[4];
    /* 0x004 */ f32 unk4;
    /* 0x008 */ u8 pad8[0x48];
    /* 0x050 */ s16 unk50;
    /* 0x052 */ u8 pad52[0xB2];
    /* 0x104 */ G01Sub104 *unk104;
    /* 0x108 */ u8 pad108[0x9C];
    /* 0x1A4 */ u8 unk1A4;
    /* 0x1A5 */ u8 pad1A5[0x1B];
    /* 0x1C0 */ f32 unk1C0[3];
    /* 0x1CC */ f32 unk1CC[3];
    /* 0x1D8 */ u8 pad1D8[0x18];
    /* 0x1F0 */ u32 unk1F0;
    /* 0x1F4 */ u8 pad1F4[0xC];
    /* 0x200 */ s16 unk200;
    /* 0x202 */ u8 pad202[0x4E];
    /* 0x250 */ s32 unk250;
} G01Ctl;

typedef struct G01Act {
    /* 0x000 */ u8 pad0[4];
    /* 0x004 */ G01Sub4 *unk4;
    /* 0x008 */ u8 pad8[0x50];
    /* 0x058 */ s32 unk58;
    /* 0x05C */ u8 pad5C[4];
    /* 0x060 */ u32 unk60;
    /* 0x064 */ u8 pad64[6];
    /* 0x06A */ u16 unk6A;
    /* 0x06C */ u8 pad6C[0x10];
    /* 0x07C */ f32 unk7C;
    /* 0x080 */ f32 unk80;
    /* 0x084 */ f32 unk84;
    /* 0x088 */ u8 pad88[0x18];
    /* 0x0A0 */ f32 unkA0;
    /* 0x0A4 */ u8 padA4[8];
    /* 0x0AC */ f32 unkAC;
    /* 0x0B0 */ u8 padB0[8];
    /* 0x0B8 */ f32 unkB8;
    /* 0x0BC */ u8 padBC[0x28];
    /* 0x0E4 */ s16 unkE4;
    /* 0x0E6 */ s16 unkE6;
    /* 0x0E8 */ s16 unkE8;
    /* 0x0EA */ u8 padEA[4];
    /* 0x0EE */ s16 unkEE;
    /* 0x0F0 */ u8 padF0[0x50];
    /* 0x140 */ ActorSub140 *unk140;
    /* 0x144 */ u8 pad144[0x10];
    /* 0x154 */ u8 unk154;
    /* 0x155 */ u8 unk155;
    /* 0x156 */ u8 pad156[0x1E];
    /* 0x174 */ G01Ctl *unk174;
    /* 0x178 */ void *unk178;
} G01Act;

typedef struct G01Pos {
    /* 0x0 */ s16 unk0;
    /* 0x2 */ s16 unk2;
    /* 0x4 */ s16 unk4;
    /* 0x6 */ u8 unk6;
    /* 0x7 */ u8 unk7;
    /* 0x8 */ u8 unk8;
    /* 0x9 */ u8 unk9;
} G01Pos;

#define G01A ((G01Act *)D_807FBB48)

void func_806C8220(s32, void *, s32);
void slotQueueInit(s32);

typedef struct G01Arg8F8C {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ u8 pad8[2];
    /* 0x0A */ u16 unkA;
    /* 0x0C */ u32 unkC;
} G01Arg8F8C;

void controllerAnimFree(Actor *, void *);
void actorSub140Free(ActorSub140 *);
void controllerAnimInit(Actor *, u16);
ActorSub140 *actorSub140CreateFromModel(Actor *);

void func_806C8F8C(void *arg) {
    G01Arg8F8C *arg0 = arg;

    G01A->unk58 = arg0->unk0;
    D_807FD584 = arg0->unk4;
    controllerAnimFree(D_807FBB48, arg0);
    actorSub140Free(G01A->unk140);
    controllerAnimInit(D_807FBB48, arg0->unkA);
    G01A->unk140 = actorSub140CreateFromModel(D_807FBB48);
    G01A->unk60 &= ~0x1000;
    G01A->unk60 |= arg0->unkC;
    G01A->unk4->unk1C = heapAlloc(0x100);
    *G01A->unk4->unk1C = 0;
    G01A->unk4->unk20 = heapAlloc(0x100);
    if (1) {}
    if (1) {}
    if (1) {}
    if (1) {}
    if (1) {}
    *G01A->unk4->unk20 = 0xFF;
    G01A->unk4->unk24 = heapAlloc(0x100);
    *G01A->unk4->unk24 = 0xFF;
    func_806C8220(1, G01A->unk178, G01A->unk58);
    slotQueueInit(0);
}

extern s16 D_8076AEE2;
extern s32 D_807FBB60;
extern s8 D_80770DC9;
G01Pos *func_806C96C4(s32);
void scriptSetActorRampTarget(Actor *, f32, f32);
void func_8067ACB4(Actor *);
void playerWaypointPathStartLineFromPoint(Actor *, void *, s32);

void func_806C90C4(s32 arg0) {
    G01Ctl *sp24 = G01A->unk174;
    G01Pos *p = func_806C96C4(arg0);

    D_8076AEE2 = 0;
    D_807FBB60 &= ~0x400;
    switch (p->unk8) {
    case 2:
        G01A->unk154 = 0x4F;
        G01A->unk155 = 3;
        scriptSetActorRampTarget(D_807FBB48, 0.5f, 0.0f);
        sp24->unk50 = 1;
        G01A->unk6A |= 4;
        func_8067ACB4(D_807FBB48);
        actorScriptStartByIndex(D_807FBB48, 0x34);
        /* fallthrough */
    case 0:
        G01A->unkAC = -10000.0f;
        G01A->unk7C = p->unk0;
        G01A->unk80 = G01A->unkA0 = p->unk2;
        G01A->unk84 = p->unk4;
        G01A->unkE6 = (p->unk6 / 255.0) * 4095.0;
        G01A->unkEE = G01A->unkE6;
        break;
    case 1:
        playerWaypointPathStartLineFromPoint(D_807FBB48, p, 0x32);
        break;
    }
    G01A->unk6A &= 0xFDFF;
    sp24->unk104->unk15F = ((s32)p->unk7 <= 0) ? 1 : p->unk7;
    if (p->unk9 & 1) {
        D_80770DC9 = 1;
    }
}

void func_806C9434(s32);
void actorClearMovementFlags(void *);

void playerRespawnResetPhysics(s32 arg0) {
    actorClearMovementFlags(D_807FBB48);
    func_806C9434(arg0);
    D_807FBB48->peakY = D_807FBB48->y;
}

typedef struct G01Player {
    /* 0x000 */ u8 pad0[0x210];
    /* 0x210 */ f32 unk210;
    /* 0x214 */ f32 unk214;
    /* 0x218 */ f32 unk218;
    /* 0x21C */ f32 unk21C;
    /* 0x220 */ f32 unk220;
    /* 0x224 */ f32 unk224;
    /* 0x228 */ f32 unk228;
    /* 0x22C */ f32 unk22C;
    /* 0x230 */ f32 unk230;
    /* 0x234 */ f32 unk234;
    /* 0x238 */ f32 unk238;
    /* 0x23C */ f32 unk23C;
    /* 0x240 */ u8 pad240[0x60];
    /* 0x2A0 */ Actor *unk2A0;
    /* 0x2A4 */ u8 pad2A4[0x1C];
    /* 0x2C0 */ u8 unk2C0;
    /* 0x2C1 */ u8 pad2C1[0x2F];
} G01Player;

typedef struct G01Sub4f {
    /* 0x00 */ u8 pad0[0x34];
    /* 0x34 */ f32 unk34[3];
} G01Sub4f;

void playerSetSizeMode(void *, s32, void *, void *);

void func_806C9304(Actor *arg0, G01Ctl *arg1) {
    s32 i;

    if (((G01Player *)gPlayerSlots)[arg1->unk1A4].unk2C0 != 1) {
        playerSetSizeMode(D_807FBB48, 1, arg0, arg1);
    }
    if (((G01Sub4f *)arg0->unk4)->unk34[0] != arg1->unk1C0[0]) {
        for (i = 0; i < 3; i++) {
            arg1->unk1CC[i] = arg1->unk1C0[i];
            ((G01Sub4f *)arg0->unk4)->unk34[i] = arg1->unk1C0[i];
        }
    }
}

void playerTransformAnimalEndSfx(void);

void func_806C93E4(Actor *arg0, Struct807FD580 *arg1) {
    playerTransformAnimalEndSfx();
    arg1->stateFlags &= ~0x30;
    arg0->flags |= 0x8000;
    arg0->unk128 = 0xFF;
}

void func_800268DC(Actor *, void *, void *); /* mpResetPlayerOnRespawn (multiplayer) */
void sfxStopSlotSound(Actor *, u8);
s32 camIsCutsceneActive(void);
void camResetAllPlayers(void);
void camResetPlayer(Actor *, u8);
void actorSetInteractionTimer(Actor *);
void playerResumeLocomotion(Actor *);
void func_806C90C4(s32);

void func_806C9434(s32 arg0) {
    G01Ctl *ctl = G01A->unk174;
    s32 pad[1];
    void *sp34 = G01A->unk178;
    s32 pad2[1];
    void *sp2C;
    u8 i;

    playerGetResolvedKongId(ctl->unk1A4);
    sp2C = &D_807FC950[0][ctl->unk1A4 * 0x306];
    ctl->unk250 = 0x78;
    i = 0;
    do {
        sfxStopSlotSound(D_807FBB48, i);
        i++;
    } while (i < 2);
    func_806C90C4(arg0);
    func_806C8220(0, sp34, G01A->unk58);
    healthRefill(ctl->unk1A4);
    G01A->unkB8 = 0.0f;
    ctl->unk1F0 &= 0xF7FFFF5F;
    ctl->unk200 = 0;
    ctl->unk4 = 0.0f;
    if (gPlayerCount >= 2) {
        func_800268DC(D_807FBB48, ctl, sp2C); /* mpResetPlayerOnRespawn */
    }
    func_806C9304(D_807FBB48, ctl);
    if (camIsCutsceneActive() == 0) {
        if (gPlayerCount >= 2 && D_80750AB8 == 1) {
            camResetAllPlayers();
        } else {
            camResetPlayer(D_807FBB48, ctl->unk1A4);
        }
    }
    actorSetInteractionTimer(D_807FBB48);
    playerResumeLocomotion(D_807FBB48);
    G01A->unkE8 = 0;
    G01A->unkE4 = 0;
}

extern G01Pos *D_807FC900;
extern u8 D_807FC904;
extern G01Pos D_807FC908;
extern G01Pos D_807FD574;
void *assetLoad(s32, s32, s32, s32);
u32 assetGetCachedSizeOrResolve(s32, s32);
void playerCheckSpawnerFlagFixup(s32);

void func_806C95D0(s32 arg0) {
    D_807FC900 = assetLoad(0x17, arg0, 1, 1);
    D_807FC904 = assetGetCachedSizeOrResolve(0x17, arg0) / 10U;
    playerCheckSpawnerFlagFixup(arg0);
    D_807FC908.unk6 = 0;
    D_807FC908.unk0 = D_807FD574.unk0;
    D_807FC908.unk2 = D_807FD574.unk2;
    D_807FC908.unk4 = D_807FD574.unk4;
}

s32 flagGet(s32, s32);

void playerCheckSpawnerFlagFixup(s32 arg0) {
    if (arg0 == 0x1E) {
        if (flagGet(0xA0, 0) != 0) {
            D_807FC900[18].unk2 = 0x65D;
            D_807FC900[23].unk2 = 0x65D;
        } else {
            D_807FC900[18].unk2 = 0x626;
            D_807FC900[23].unk2 = 0x626;
        }
    }
}

extern f32 D_8076AEE4;
extern f32 D_8076AEE8;
extern f32 D_8076AEEC;
extern s16 D_8076AEF0;
extern G01Pos D_807FC918;

G01Pos *func_806C96C4(s32 arg0) {
    if (D_8076AEE2 & 1) {
        D_807FC918.unk0 = D_8076AEE4;
        D_807FC918.unk2 = D_8076AEE8;
        D_807FC918.unk4 = D_8076AEEC;
        D_807FC918.unk6 = (D_8076AEF0 / 4095.0) * 360.0;
        return &D_807FC918;
    }
    if (D_807FC904 == 0) {
        return &D_807FC908;
    }
    if (arg0 >= D_807FC904) {
        return D_807FC900;
    }
    return &D_807FC900[arg0];
}

void func_800268C0();

/* K&R `s8 arg0` + `v = arg0; arg0 = 0;` gives the entry sll/sra/move and the dead home store. Reading `q->unk5C` at
 * each test (no flags local) and keeping `q = pl->unk2A0` as a separate copy variable leaves the `move v0,a0`. */
s8 func_806C9830(arg0, arg1)
    s8 arg0;
    Actor *arg1;
{
    s8 v;
    G01Ctl *c;
    G01Player *pl;
    Actor *q;

    v = arg0;
    arg0 = 0;

    if (gPlayerCount >= 2) {
        c = ((G01Act *)arg1)->unk174; pl = c->unk1A4 + (G01Player *)gPlayerSlots;
        if (pl->unk2A0 != NULL) {
            q = pl->unk2A0;
            if (q->collisionFlags & 1) {
                v = -1;
                if (D_807FBB64 & 0x04000000) {
                    func_800268C0(1, arg1);
                }
            } else if (q->collisionFlags & 4) {
                if (q->actorType == 0x29 || q->actorType == 0xAB) {
                    v = -3;
                    if (D_807FBB64 & 0x04000000) {
                        func_800268C0(2, arg1);
                    }
                } else {
                    v = -2;
                    if (D_807FBB64 & 0x04000000) {
                        func_800268C0(1, arg1);
                    }
                }
            } else if (D_807FBB64 & 0x04000000) {
                func_800268C0(1, arg1);
            }
        }
    }
    return v;
}

typedef struct G01Ent {
    /* 0x00 */ u8 unk0;
    /* 0x01 */ u8 unk1;
    /* 0x02 */ u8 unk2;
    /* 0x03 */ u8 pad3[0x5B];
} G01Ent;

typedef struct G01Slot {
    /* 0x000 */ G01Ent ent[6];
    /* 0x234 */ u8 pad234[0xC7];
    /* 0x2FB */ s8 unk2FB;
    /* 0x2FC */ u8 unk2FC;
    /* 0x2FD */ s8 unk2FD;
    /* 0x2FE */ u8 pad2FE[8];
} G01Slot;

typedef struct G01PlayerFlags {
    /* 0x000 */ u8 pad0[0x2E2];
    /* 0x2E2 */ u16 unk2E2;
} G01PlayerFlags;

extern s32 D_807552EC;
void func_80026E20(u8, s8);
void rumbleRequest(u8, s32, s32, s8);

s32 func_806C9974(arg0, arg1)
u8 arg0;
s8 arg1;
{
    G01PlayerFlags *pl;

    pl = (G01PlayerFlags *)&gPlayerSlots[arg0];
    pl->unk2E2 |= 0x11;
    if (gPlayerCount >= 2 && arg1 < 0 && D_807552EC == 1) {
        func_80026E20(arg0, arg1);
    }
    if (arg1 < 0) {
        rumbleRequest(arg0, 0xFF, 5, arg1);
    }
    if (!(D_807FBB64 & 0x800)) {
        ((G01Slot *)D_807FC950)[arg0].unk2FD += arg1;
    }
    if (((G01Slot *)D_807FC950)[arg0].unk2FD + ((G01Slot *)D_807FC950)[arg0].unk2FB <= 0) {
        pl->unk2E2 |= 0xC0;
        return 1;
    }
    return 0;
}

extern s32 D_807552E4;
extern s8 D_80750ACC;
extern s32 D_807FD56C;
void collectibleCountsClear();

void func_806C9AE0(void) {
    G01Slot *p = (G01Slot *)D_807FC950;
    s32 i;
    s32 j;

    for (i = 0; i < 4; i++) {
        bzero(p, 0x306);
        if (D_80750AC0 >= 2) {
            if (D_807552E4 == 1) {
                for (j = 0; j < 6; j++) {
                    p->ent[j].unk2 = 7;
                }
            }
            for (j = 0; j < 6; j++) {
                p->ent[j].unk1 = 1;
            }
            p->unk2FC = 1;
        } else {
            p->unk2FC = 1;
        }
        healthRefill(i);
        p++;
    }
    collectibleCountsClear();
    D_80750ACC = 0;
    D_807FD56C = 0;
}

void func_806C9C1C(s32);

extern s32 D_80750B34[];
void slotQueueAddValue(s32, u8, s32);

void func_806C9C1C(s32 arg0) {
    s32 i;

    for (i = 0; i < 5; i++) {
        slotQueueAddValue(D_80750B34[i], arg0, 0x270F);
    }
    slotQueueInit(0);
}

void flagSet(s32, s32, s32);

void func_806C9C80(s32 arg0, s32 arg1, s32 arg2) {
    s32 idx = playerGetResolvedKongId(arg0);
    u8 *p = &D_807FC950[0][arg0 * 0x306 + idx * 0x5E];

    p[2] = 7;
    p[4] = 0xF;
    p[1] = 3;
    p[0] = 3;
    flagSet(0x179, 1, 0);
    func_806C9C1C(arg0);
}

void func_806C9D20(u8 arg0) {
    G01Player *p = (G01Player *)&gPlayerSlots[arg0];

    p->unk21C = p->unk210;
    p->unk220 = p->unk214;
    p->unk224 = p->unk218;
    p->unk234 = p->unk228;
    p->unk238 = p->unk22C;
    p->unk23C = p->unk230;
}

typedef struct G01Row {
    /* 0x00 */ u8 pad0[0x42];
    /* 0x42 */ u16 unk42[8];
    /* 0x52 */ u8 pad52[0xC];
} G01Row;

s32 func_806C9D7C(void) {
    G01Row *row = (G01Row *)D_807FC950[gPlayerCharacterId[0]];
    s32 i;
    s32 v;

    v = 0;
    for (i = 0; i < 8 && !v; i++) {
        v = row->unk42[i] > 0;
    }
    return v;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/CC800/D_8075C410.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CC800/D_8075C414.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CC800/D_8075C420.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CC800/D_8075C430.s")
