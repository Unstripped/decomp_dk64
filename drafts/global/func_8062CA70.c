// func_8062CA70 (src/global/2F550.c): stage 5 (frame 0x88, saved set s0-s3,f20-f24 match; needs unused local 'Gfx *sp84' to reach frame 0x88): remaining diff = fp-reg assignment (target x=f20,y=f22,z=f24; mine x=f24 since x savings 1.53 < y,z 1.64) and target hoists consts 3/1/2 into t0-t2 for type tests (mine li at), spill slot 0x54 vs 0x50. R2F550bMapView typedef must sit above it (CEA8 uses it). Tried kind switch vs if-chain, type switch vs if, permuter 240s (3245 vs 3664).
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

extern u8 D_807F6009;
Gfx *func_80630B70(Gfx *, s32, f32, f32, f32, s32, s32, s32);

typedef struct R2F550bMapView {
    u8 pad0[0x1C];
    void *unk1C[21];
    s16 unk70[12];
    s16 unk88[18];
    u8 unkAC[13];
    u8 unkB9[12];
    u8 unkC5;
} R2F550bMapView;

typedef struct R2F550bLeaf {
    u8 pad0[8];
    s32 unk8;
    s32 unkC;
    s32 unk10;
    s32 unk14;
    s32 unk18;
    u8 pad1C[0x52];
    s16 unk6E;
} R2F550bLeaf;

extern s32 D_807F5E64;
extern void *D_807F5DE8;
extern void *D_807F5DEC;
extern s32 D_807F5FFC;

Gfx *func_8062CEA8(Gfx *, R2F550bMapView *, u8);
Gfx *mapChunksRender(Gfx *, R2F550bObj *, f32, f32, f32, s32);
Gfx *fogRender(Gfx *);
Gfx *func_8062EDA8(Gfx *, u8);
Gfx *func_8063A968(Gfx *, s32);
Gfx *func_8065D994(Gfx *, s16);

#define R2F550bLEAF(o) ((R2F550bLeaf *)(o))

Gfx *func_8062CA70(Gfx *gfx, R2F550bObj *arg1, R2F550bTree *arg2, f32 arg3, f32 arg4, f32 arg5, s32 arg6) {
    Gfx *sp84;
    for (;;) {
        if (arg1 == NULL) {
            return gfx;
        }
        if (arg2->unk1 == 3) {
            return gfx;
        }
        switch (arg1->unkB8) {
            case 2:
                gfx = mapChunksRender(gfx, arg1, arg3, arg4, arg5, arg6);
                return gfx;
            case 1:
                D_807F5E64 += R2F550bLEAF(arg1)->unk6E;
                if (arg6 & 0x10) {
                    gSPSegment(gfx++, 6, osVirtualToPhysical(D_807F5DE8));
                    gSPSegment(gfx++, 7, osVirtualToPhysical(D_807F5DEC));
                    gfx = func_8062CEA8(gfx, (R2F550bMapView *)arg1, 1);
                    gfx = fogRender(gfx);
                    gfx = func_8062EDA8(gfx, 0xFF);
                    if (R2F550bLEAF(arg1)->unk8 != -1) {
                        gSPDisplayList(gfx++, osVirtualToPhysical((void *)R2F550bLEAF(arg1)->unk8));
                    }
                    if (R2F550bLEAF(arg1)->unkC != -1) {
                        gSPDisplayList(gfx++, osVirtualToPhysical((void *)R2F550bLEAF(arg1)->unkC));
                    }
                    if (R2F550bLEAF(arg1)->unk14 != -1) {
                        gSPDisplayList(gfx++, osVirtualToPhysical((void *)R2F550bLEAF(arg1)->unk14));
                    }
                    if (R2F550bLEAF(arg1)->unk10 != -1) {
                        gSPDisplayList(gfx++, osVirtualToPhysical((void *)R2F550bLEAF(arg1)->unk10));
                    }
                    if (R2F550bLEAF(arg1)->unk18 != -1) {
                        gSPDisplayList(gfx++, osVirtualToPhysical((void *)R2F550bLEAF(arg1)->unk18));
                    }
                    gfx = func_8062CEA8(gfx, (R2F550bMapView *)arg1, 2);
                }
                gfx = func_8063A968(gfx, arg2->unk8);
                gfx = func_8065D994(gfx, -1);
                D_807F6009 = 0xFF;
                gfx = func_80630B70(gfx, (s32)arg2->unk4, arg3, arg4, arg5, arg6, -1, 0);
                if (arg6 & 0x10) {
                    gSPSegment(gfx++, 6, osVirtualToPhysical(D_807F5DE8));
                    gSPSegment(gfx++, 7, osVirtualToPhysical(D_807F5DEC));
                    gfx = func_8062CEA8(gfx, (R2F550bMapView *)arg1, 3);
                    gDPPipeSync(gfx++);
                }
                gfx = func_80630B70(gfx, D_807F5FFC, arg3, arg4, arg5, arg6, -1, 0);
                return gfx;
            case 0:
                switch (arg2->unk1) {
                    case 1:
                    case 2:
                        if (arg2->unk0 == 0) {
                            arg1 = arg1->unk0;
                            arg2 = arg2->unkC;
                        } else {
                            arg1 = arg1->unk4;
                            arg2 = arg2->unk10;
                        }
                        continue;
                    case 0:
                        if (arg2->unk0 != 0) {
                            gfx = func_8062CA70(gfx, arg1->unk0, arg2->unkC, arg3, arg4, arg5, arg6);
                            arg1 = arg1->unk4;
                            arg2 = arg2->unk10;
                        } else {
                            gfx = func_8062CA70(gfx, arg1->unk4, arg2->unk10, arg3, arg4, arg5, arg6);
                            arg1 = arg1->unk0;
                            arg2 = arg2->unkC;
                        }
                        continue;
                    default:
                        return gfx;
                }
            default:
                return gfx;
        }
    }
}
