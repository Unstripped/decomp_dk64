// func_80651C2C (src/global/55B20.c): stage 5: reversed declaration order (a2v,a1v,a0v,b2v,b1v,b0v) reproduces target stack slots 0x88/0x90/0x98 and 0x70/0x78/0x80; remaining: the grid element pointer D_807F6C14[arg0] is colored to s0 (target a2, recomputed per use), pushing the output pointer to s1 and the frame to 0xa8 vs 0xa0.
typedef struct R2P1bGridSrc {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ u8 padC[0x4];
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ u8 pad1C[0x4];
    /* 0x20 */ f32 unk20;
    /* 0x24 */ f32 unk24;
    /* 0x28 */ f32 unk28;
    /* 0x2C */ u8 pad2C[0x4];
} R2P1bGridSrc;

typedef struct R2P1bCross {
    /* 0x00 */ s64 unk0;
    /* 0x08 */ s64 unk8;
    /* 0x10 */ s64 unk10;
    /* 0x18 */ s64 unk18;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ f32 unk24;
    /* 0x28 */ u8 unk28;
} R2P1bCross;

void func_80651C2C(s32 arg0, void *arg1p) {
    s64 a2v;
    s64 a1v;
    s64 a0v;
    s64 b2v;
    s64 b1v;
    s64 b0v;
    s64 dot;
    s64 x;
    s64 y;
    s64 z;
    f32 f0;
    f32 f8;
    f32 len;

    a0v = (s64)(((R2P1bGridSrc *)D_807F6C14)[arg0].unk0 - ((R2P1bGridSrc *)D_807F6C14)[arg0].unk4);
    a1v = (s64)(((R2P1bGridSrc *)D_807F6C14)[arg0].unk10 - ((R2P1bGridSrc *)D_807F6C14)[arg0].unk14);
    a2v = (s64)(((R2P1bGridSrc *)D_807F6C14)[arg0].unk20 - ((R2P1bGridSrc *)D_807F6C14)[arg0].unk24);
    b0v = (s64)(((R2P1bGridSrc *)D_807F6C14)[arg0].unk0 - ((R2P1bGridSrc *)D_807F6C14)[arg0].unk8);
    b1v = (s64)(((R2P1bGridSrc *)D_807F6C14)[arg0].unk10 - ((R2P1bGridSrc *)D_807F6C14)[arg0].unk18);
    b2v = (s64)(((R2P1bGridSrc *)D_807F6C14)[arg0].unk20 - ((R2P1bGridSrc *)D_807F6C14)[arg0].unk28);
    ((R2P1bCross *)arg1p)->unk0 = a1v * b2v - a2v * b1v;
    ((R2P1bCross *)arg1p)->unk8 = a2v * b0v - a0v * b2v;
    ((R2P1bCross *)arg1p)->unk10 = a0v * b1v - a1v * b0v;
    f8 = (f32)((R2P1bCross *)arg1p)->unk8;
    f0 = (f32)((R2P1bCross *)arg1p)->unk0;
    ((R2P1bCross *)arg1p)->unk18 = (s64)-(((R2P1bGridSrc *)D_807F6C14)[arg0].unk24 * (f32)((R2P1bCross *)arg1p)->unk10 + (f0 * ((R2P1bGridSrc *)D_807F6C14)[arg0].unk4 + f8 * ((R2P1bGridSrc *)D_807F6C14)[arg0].unk14));
    dot = ((R2P1bCross *)arg1p)->unk8 * ((R2P1bCross *)arg1p)->unk8 + ((R2P1bCross *)arg1p)->unk0 * ((R2P1bCross *)arg1p)->unk0 + ((R2P1bCross *)arg1p)->unk10 * ((R2P1bCross *)arg1p)->unk10;
    len = (f32)dot;
    ((R2P1bCross *)arg1p)->unk24 = len;
    ((R2P1bCross *)arg1p)->unk20 = sqrtf(len);
    x = ((R2P1bCross *)arg1p)->unk0;
    if (x < 0) {
        x = -x;
    }
    y = ((R2P1bCross *)arg1p)->unk8;
    if (y < 0) {
        y = -y;
    }
    z = ((R2P1bCross *)arg1p)->unk10;
    if (z < 0) {
        z = -z;
    }
    if ((z >= x) && (z >= y)) {
        ((R2P1bCross *)arg1p)->unk28 = 0;
    }
    if ((y >= x) && (y >= z)) {
        ((R2P1bCross *)arg1p)->unk28 = 1;
    }
    if ((x >= y) && (x >= z)) {
        ((R2P1bCross *)arg1p)->unk28 = 2;
    }
}
