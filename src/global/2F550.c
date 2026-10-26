#include "common.h"
#include "actor.h"

extern u8 D_807444FC;

#pragma GLOBAL_ASM("asm/global/nonmatchings/2F550/func_8062A850.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/2F550/func_8062A944.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/2F550/func_8062AC68.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/2F550/func_8062AD28.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/2F550/func_8062B194.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/2F550/func_8062B220.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/2F550/func_8062B3C4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/2F550/func_8062B478.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/2F550/func_8062B630.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/2F550/func_8062B660.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/2F550/func_8062B840.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/2F550/func_8062B86C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/2F550/func_8062B8A4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/2F550/func_8062B8E4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/2F550/func_8062BA0C.s")

typedef struct R2F550bSrc {
    struct R2F550bSrc *unk0;
    struct R2F550bSrc *unk4;
} R2F550bSrc;

typedef struct R2F550bNode {
    u8 pad0;
    u8 unk1;
    u8 pad2[2];
    s32 unk4;
    s32 unk8;
    struct R2F550bNode *unkC;
    struct R2F550bNode *unk10;
} R2F550bNode;

void *func_80610FE8(s32);

R2F550bNode *func_8062BA74(R2F550bSrc *arg0) {
    R2F550bNode *node;

    if (arg0 == NULL) {
        return NULL;
    }
    node = func_80610FE8(0x14);
    node->unk4 = 0;
    node->unk8 = 0;
    node->unk1 = 3;
    node->unkC = func_8062BA74(arg0->unk0);
    node->unk10 = func_8062BA74(arg0->unk4);
    return node;
}

typedef struct R2F550bObj {
    struct R2F550bObj *unk0;
    struct R2F550bObj *unk4;
    u8 pad8[0xC];
    struct R2F550bObj *unk14;
    u8 pad18[6];
    s16 unk1E;
    u8 pad20[4];
    u8 unk24;
    u8 pad25[0x93];
    u8 unkB8;
} R2F550bObj;

typedef struct R2F550bTree {
    u8 unk0;
    u8 unk1;
    u8 pad2[2];
    R2F550bObj *unk4;
    s32 unk8;
    struct R2F550bTree *unkC;
    struct R2F550bTree *unk10;
} R2F550bTree;

void func_8062BB2C(R2F550bObj *, R2F550bTree *, u8);

extern R2F550bObj *D_807F5DE4;
extern R2F550bTree *D_807F5E60;

void func_8063B4A4(void);
void func_8063B758(void);
void func_80641A78(void);

void func_8062BAE4(void) {
    func_8063B4A4();
    func_8062BB2C(D_807F5DE4, D_807F5E60, 1);
    func_8063B758();
    func_80641A78();
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/2F550/func_8062BB2C.s")

extern R2F550bObj *D_807F5FF4;

u8 func_8062BDB0(void *, R2F550bObj *, R2F550bTree *, f32, f32, f32, s32);
s32 func_80668E9C(void *, s16, f32, f32, f32, s32);

u8 func_8062BCC8(void *arg0, f32 arg1, f32 arg2, f32 arg3, s32 arg4) {
    u8 result;
    R2F550bObj *item;

    result = func_8062BDB0(arg0, D_807F5DE4, D_807F5E60, arg1, arg2, arg3, arg4);
    item = D_807F5FF4;
    while (item != NULL) {
        if (item->unk24 == 1) {
            result |= func_80668E9C(arg0, item->unk1E, arg1, arg2, arg3, arg4);
        }
        item = item->unk14;
    }
    return result;
}

u8 func_80652BC8(void *, f32, f32, f32, s32);

u8 func_8062BDB0(void *arg0, R2F550bObj *arg1, R2F550bTree *arg2, f32 arg3, f32 arg4, f32 arg5, s32 arg6) {
    u8 result;
    s32 other;
    R2F550bObj *item;

    result = 0;
    switch (arg1->unkB8) {
        case 2:
            return func_80652BC8(arg0, arg3, arg4, arg5, arg6);
        case 1:
            item = arg2->unk4;
            while (item != NULL) {
                if (item->unk24 == 1) {
                    result |= func_80668E9C(arg0, item->unk1E, arg3, arg4, arg5, arg6);
                }
                item = item->unk14;
            }
            return result;
        case 0:
            result = func_8062BDB0(arg0, arg1->unk0, arg2->unkC, arg3, arg4, arg5, arg6);
            other = func_8062BDB0(arg0, arg1->unk4, arg2->unk10, arg3, arg4, arg5, arg6);
            return result | other;
    }
    return 0;
}

typedef struct R2F550bCamera {
    u8 pad0[0x129];
    u8 unk129;
} R2F550bCamera;

typedef struct R2F550bViewport {
    u8 pad0[4];
    s16 unk4;
    s16 unk6;
    s16 unk8;
    s16 unkA;
} R2F550bViewport;

typedef struct R2F550bPlayer {
    u8 unk0;
    u8 pad1[3];
    R2F550bCamera *unk4;
    u8 pad8[0x214];
    s32 unk21C;
    s32 unk220;
    s32 unk224;
    u8 pad228[0xC];
    f32 unk234;
    f32 unk238;
    f32 unk23C;
    u8 pad240[0x40];
    f32 unk280;
    u8 pad284[4];
    f32 unk288;
    f32 unk28C;
    u8 pad290[0x5A];
    u8 unk2EA;
    u8 pad2EB[5];
} R2F550bPlayer;

#define R2F550bPLAYER(i) (((R2F550bPlayer *)D_807FC924)[i])

extern Gfx D_1000118;
extern u8 D_80750AB4;
extern u8 D_807F5FEC;
extern u8 D_807F5FED;
extern u8 D_807FC929;
extern void *D_807FC924;

void func_8062C1C0(s32);
void func_8062C22C(void);
f32 func_8062A850(void);
Gfx *func_8062C29C(Gfx *, s32, s32, s32, f32, f32, f32, f32, f32, f32);
R2F550bViewport *cameraFindViewportEntry(u8);

Gfx *func_8062BF24(Gfx *gfx, s32 arg1) {
    s32 i;
    u8 alpha;
    R2F550bViewport *vp;

    func_8062C1C0(arg1);
    gDPPipeSync(gfx++);
    if (D_807F5FED != 0) {
        gSPSetOtherMode(gfx++, G_SETOTHERMODE_H, G_MDSFT_PIPELINE, 1, G_PM_1PRIMITIVE);
    } else {
        gSPSetOtherMode(gfx++, G_SETOTHERMODE_H, G_MDSFT_PIPELINE, 1, G_PM_NPRIMITIVE);
    }
    for (i = 0; i < D_80750AB4; i++) {
        if (R2F550bPLAYER(i).unk0 != 0) {
            D_807FC929 = i;
            gfx = func_8062C29C(gfx, R2F550bPLAYER(i).unk21C, R2F550bPLAYER(i).unk220, R2F550bPLAYER(i).unk224,
                                R2F550bPLAYER(i).unk234, R2F550bPLAYER(i).unk238, R2F550bPLAYER(i).unk23C,
                                R2F550bPLAYER(i).unk28C, R2F550bPLAYER(i).unk280 * func_8062A850(),
                                R2F550bPLAYER(i).unk288);
            D_807F5FEC = 0;
        }
        if (R2F550bPLAYER(i).unk0 == 0 || R2F550bPLAYER(i).unk2EA != 0) {
            alpha = R2F550bPLAYER(i).unk4->unk129;
            vp = cameraFindViewportEntry(i);
            gSPDisplayList(gfx++, &D_1000118);
            gSPTexture(gfx++, 0xFFFF, 0xFFFF, 0, 0, G_OFF);
            gDPPipeSync(gfx++);
            gDPSetPrimColor(gfx++, 0, 0, 0, 0, 0, 0xFF - alpha);
            gDPSetCombineMode(gfx++, G_CC_PRIMITIVE, G_CC_PRIMITIVE);
            gDPFillRectangle(gfx++, vp->unk4, vp->unk6, vp->unk8, vp->unkA);
            gDPPipeSync(gfx++);
        }
    }
    func_8062C22C();
    gDPPipeSync(gfx++);
    return gfx;
}

extern s32 D_807F6C28;

void func_8065EFF0(void);
void func_8062D3E4(R2F550bObj *);
void func_8063039C(void);
void func_8062EE48(u8);
void mapChunkResetFlags(void);
void func_8065A884(void);
void effectUpdateNodes(void);

void func_8062C1C0(s32 arg0) {
    func_8065EFF0();
    func_8062D3E4(D_807F5FF4);
    func_8063039C();
    if (D_807F6C28 == 0) {
        func_8062EE48(0xFF);
    }
    mapChunkResetFlags();
    func_8065A884();
    effectUpdateNodes();
    D_807F5FEC = 1;
}

void mapChunkReleaseAndAdvance(void);
void func_8062EFA0(void);
void mapChunkFreeIdleBuffers(void);
void func_80653FA4(void);
void mapChunkSetIndexOverride(s8);
void func_8063C450(void);
void func_8062B660(void);
void func_80636C00(void);
void func_806364C4(void);

void func_8062C22C(void) {
    if (D_807F6C28 != 0) {
        mapChunkReleaseAndAdvance();
        func_8062EFA0();
        mapChunkFreeIdleBuffers();
        func_80653FA4();
        mapChunkSetIndexOverride(0);
    }
    func_8063C450();
    func_8062B660();
    func_80636C00();
    func_806364C4();
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/2F550/func_8062C29C.s")

void func_8062C99C(s16 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    arg0[0] = (arg3 - arg1) * 2;
    arg0[1] = (arg4 - arg2) * 2;
    arg0[2] = 0x1FF;
    arg0[3] = 0;
    arg0[4] = ((arg1 + arg3) / 2) * 4;
    arg0[5] = ((arg2 + arg4) / 2) * 4;
    arg0[6] = 0x1FF;
    arg0[7] = 0;
}

extern s32 D_807F5FF8;
extern u8 D_807F6009;

Gfx *func_80630B70(Gfx *, s32, f32, f32, f32, s32, s32, s32);

void func_8062CA0C(Gfx *arg0, f32 arg1, f32 arg2, f32 arg3) {
    D_807F6009 = 0xFF;
    func_80630B70(arg0, D_807F5FF8, arg1, arg2, arg3, 0x30030, -1, 0);
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/2F550/func_8062CA70.s")

typedef struct R2F550bMapView {
    u8 pad0[0x1C];
    void *unk1C[21];
    s16 unk70[12];
    s16 unk88[18];
    u8 unkAC[13];
    u8 unkB9[12];
    u8 unkC5;
} R2F550bMapView;

typedef struct R2F550bSlot {
    u8 pad0[0x80];
    f32 unk80;
    u8 pad84[8];
    u8 unk8C;
    u8 pad8D[3];
} R2F550bSlot;

extern R2F550bSlot *D_807F5FB8;

s32 mapChunkIsActive(s16);
Gfx *func_8063C418(Gfx *, s16);

Gfx *func_8062CEA8(Gfx *gfx, R2F550bMapView *arg1, u8 arg2) {
    s32 i;
    u8 idx;

    for (i = 0; i < arg1->unkC5; i++) {
        if (arg2 == arg1->unkB9[i] && (arg1->unk88[i] == -1 || mapChunkIsActive(arg1->unk88[i]) != 0)) {
            gfx = func_8063C418(gfx, arg1->unk70[i]);
            gSPClearGeometryMode(gfx++, G_CULL_BACK);
            idx = arg1->unkAC[i];
            if (D_807F5FB8[idx].unk80 != 0.0 && D_807F5FB8[idx].unk8C != 0) {
                gSPMatrix(gfx++, osVirtualToPhysical((u8 *)D_807F5FB8 + idx * 0x90 + (D_807444FC << 6)),
                          G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_PUSH);
                gSPDisplayList(gfx++, osVirtualToPhysical(arg1->unk1C[i]));
                gSPPopMatrix(gfx++, G_MTX_MODELVIEW);
            } else {
                gSPDisplayList(gfx++, osVirtualToPhysical(arg1->unk1C[i]));
            }
            gDPPipeSync(gfx++);
        }
    }
    return gfx;
}

u8 func_8062D0CC(R2F550bObj *, R2F550bTree *, s32, u8);

void func_8062D094(s32 arg0, u8 arg1) {
    func_8062D0CC(D_807F5DE4, D_807F5E60, arg0, arg1);
}

void func_806524A0(s32, u8);
void func_806307CC(R2F550bObj *, s32, s32, u8, u8 *);

u8 func_8062D0CC(R2F550bObj *arg0, R2F550bTree *arg1, s32 arg2, u8 arg3) {
    u8 unused;
    u8 sp26;

    sp26 = 0;
    if (arg0 == NULL) {
        return 0;
    }
    switch (arg0->unkB8) {
        case 2:
            func_806524A0(arg2, arg3);
            return 1;
        case 1:
            func_806307CC(arg1->unk4, arg2, 0, arg3, &sp26);
            return sp26;
        case 0:
            if (func_8062D0CC(arg0->unk0, arg1->unkC, arg2, arg3) != 0) {
                return 1;
            }
            return func_8062D0CC(arg0->unk4, arg1->unk10, arg2, arg3);
    }
}

s32 func_807142D8(void);
void func_8062D1E0(R2F550bObj *, R2F550bTree *);

void func_8062D1A8(void) {
    if (func_807142D8() == 0) {
        func_8062D1E0(D_807F5DE4, D_807F5E60);
    }
}

void func_806323C0(R2F550bObj *);
void mapChunkResolveNodeAssets(void);

void func_8062D1E0(R2F550bObj *arg0, R2F550bTree *arg1) {
    for (;;) {
        if (arg0 == NULL) {
            return;
        }
        switch (arg0->unkB8) {
            case 2:
                mapChunkResolveNodeAssets();
                return;
            case 1:
                func_806323C0(arg1->unk4);
                return;
            case 0:
                func_8062D1E0(arg0->unk0, arg1->unkC);
                arg0 = arg0->unk4;
                arg1 = arg1->unk10;
                break;
            default:
                return;
        }
    }
}

R2F550bObj *func_80630588(R2F550bObj *, s32, s32, u8 *);
void func_8062D2AC(s32, s16 *, u8);

void func_8062D26C(s32 arg0) {
    u8 sp1F;
    s16 sp1C;

    func_80630588(NULL, arg0, 1, &sp1F);
    func_8062D2AC(arg0, &sp1C, 1);
}

u8 func_8062D2F0(R2F550bObj *, R2F550bTree *, s32, s16 *, u8);

void func_8062D2AC(s32 arg0, s16 *arg1, u8 arg2) {
    func_8062D2F0(D_807F5DE4, D_807F5E60, arg0, arg1, arg2);
}

u8 mapChunkPurgeNodeList(s32, s16 *, u8);

u8 func_8062D2F0(R2F550bObj *arg0, R2F550bTree *arg1, s32 arg2, s16 *arg3, u8 arg4) {
    u8 sp27;

    if (arg0 == NULL) {
        return 0;
    }
    switch (arg0->unkB8) {
        case 2:
            return mapChunkPurgeNodeList(arg2, arg3, arg4);
        case 1:
            arg1->unk4 = func_80630588(arg1->unk4, arg2, 0, &sp27);
            return sp27;
        case 0:
            if (func_8062D2F0(arg0->unk0, arg1->unkC, arg2, arg3, arg4) != 0 && arg4 == 0) {
                return 1;
            }
            return func_8062D2F0(arg0->unk4, arg1->unk10, arg2, arg3, arg4);
    }
    return 0;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/2F550/func_8062D3E4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/2F550/func_8062D414.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/2F550/func_8062D620.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/2F550/func_8062DAF4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/2F550/func_8062DB70.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/2F550/func_8062DBDC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/2F550/func_8062E040.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/2F550/func_8062E1F8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/2F550/func_8062E3B4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/2F550/func_8062E548.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/2F550/func_8062E608.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/2F550/func_8062E67C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/2F550/func_8062E898.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/2F550/func_8062EBB8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/2F550/func_8062EDA8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/2F550/func_8062EE48.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/2F550/func_8062EFA0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/2F550/func_8062F050.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/2F550/func_8062F318.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/2F550/func_8062F328.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/2F550/func_8062F388.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/2F550/func_8062F3A0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/2F550/func_8062F420.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/2F550/func_8062F538.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/2F550/func_8062F640.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/2F550/func_8062F998.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/2F550/func_8062FBC8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/2F550/func_8062FF10.s")
