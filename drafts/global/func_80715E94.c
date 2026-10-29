// func_80715E94 (src/global/119370.c): stage 5: 10400/10400 bytes, frame 0x160 exact, 940/1055 insns bit-identical; remaining 57 diffs are only t-reg numbering and spill slot in vertex call / post-loop
typedef struct L119_TextureNode {
    u8 pad0[0xA];
    u8 unkA;
    u8 unkB;
    s16 unkC;
    s16 unkE;
    u8 pad10[4];
    u8 unk14;
} L119_TextureNode;

typedef struct L119_EffectView {
    u8 pad0[0x21];
    u8 unk21;
    u8 pad22[0x30E];
    L119_TextureNode *unk330;
    u8 pad334[0xC];
    f32 unk340;
    f32 unk344;
    f32 unk348;
    u8 pad34C[0x1E];
    u8 unk36A;
    u8 unk36B;
    u8 unk36C;
    u8 unk36D;
    u8 unk36E;
    u8 unk36F;
    void *unk370;
    u8 pad374[0xC];
    s32 unk380;
    u8 pad384[4];
    s16 unk388;
    s8 unk38A;
    u8 pad38B;
    u16 unk38C;
    s16 unk38E;
    s16 unk390;
    s16 unk392;
    s16 unk394;
} L119_EffectView;

#define L119_WRITE_GFX(pkt, _w0, _w1) { Gfx *_g = (pkt); _g->words.w0 = (_w0); _g->words.w1 = (u32)(_w1); }

extern Actor *D_807FBB4C;
extern s32 D_807FBB60;
extern u8 D_807F6009;
extern s32 D_807F600C;
extern u8 D_807FC929;
extern s16 D_80744490;
extern s16 D_80744494;
extern Mtx D_2000000;
extern Mtx D_20000C0;
extern Mtx D_2000180;
extern Mtx D_2000200;
Gfx *func_805FD030(Gfx *);
void func_8065C334(f32, f32, f32, s16, u8 *, u8 *, u8 *, s16);
s32 mapChunkContainsPoint(s16, s16, s16);
s32 mapChunkIsInUse(s16);

Gfx *func_80715E94(L119_EffectView *arg0, Gfx *arg1, s16 arg2) {
    s32 i;
    u8 red;
    u8 green;
    u8 blue;
    f32 colorRed = 1.0f;
    f32 colorGreen = 1.0f;
    f32 colorBlue = 1.0f;
    Gfx *glist;
    L119_EffectView *cursor;

    if (arg0->unk38C & 0x50) {
        return arg1;
    }
    if ((((D_807FBB4C->unk154 == 0x83) || (D_807FBB4C->unk154 == 0x67)) && !(arg0->unk38C & 0x20)) || (((D_807FBB60 & 0x100002) == 0x100002) && !(arg0->unk38C & 0x100))) {
        return arg1;
    }
    if (arg2 == -1) {
        arg2 = arg0->unk38A;
    }
    if (arg0->unk388 != -1) {
        if (arg0->unk36F != 0) {
            if (mapChunkContainsPoint((s16)((f64)arg0->unk340 * 0.25), (s16)((f64)arg0->unk344 * 0.25), arg0->unk388) == 0) {
                return arg1;
            }
        } else if (arg2 != arg0->unk388) {
            return arg1;
        }
    }

    glist = ((Gfx *(*)[2])arg0)[arg0->unk21][D_807444FC];
    arg0->unk21++;
    L119_WRITE_GFX(arg1++, 0xDE000000, osVirtualToPhysical(glist));
    L119_WRITE_GFX(glist++, 0xE7000000, 0);
    L119_WRITE_GFX(glist++, 0xE3000A01, 0);
    L119_WRITE_GFX(glist++, 0xD9000000, 0);
    L119_WRITE_GFX(glist++, 0xE3001801, 0xC0);
    if (arg0->unk36E != 0) {
        L119_WRITE_GFX(glist++, 0xD9FFFFFF, 0x200005);
        L119_WRITE_GFX(glist++, 0xE200001C, 0x504B50);
    } else {
        L119_WRITE_GFX(glist++, 0xD9FFFFFF, 0x200004);
        L119_WRITE_GFX(glist++, 0xE200001C, 0x504240);
    }
    L119_WRITE_GFX(glist++, 0xD7000002, 0xFFFFFFFF);
    L119_WRITE_GFX(glist++, 0xFC119623, 0xFF2FFFFF);

    if (arg0->unk330->unk14 == 0 && mapChunkIsInUse(arg2)) {
        func_8065C334(arg0->unk340, arg0->unk344, arg0->unk348, 0, &red, &green, &blue, arg2);
        colorRed = (f32)((f64)red / 255.0);
        colorGreen = (f32)((f64)green / 255.0);
        colorBlue = (f32)((f64)blue / 255.0);
    }
    gDPSetPrimColor(glist++, 0, 0, (u32)((f32)arg0->unk36A * colorRed), (u32)((f32)arg0->unk36B * colorGreen), (u32)((f32)arg0->unk36C * colorBlue), arg0->unk36D);
    if (arg0->unk36F != 0) {
        L119_WRITE_GFX(glist++, 0xDA380007, &D_20000C0);
        L119_WRITE_GFX(glist++, 0xDA380003, &D_2000180);
        glist = func_805FD030(glist);
        if (arg0->unk388 == -1) {
            L119_WRITE_GFX(glist++, 0xED000000 | (((s32)((f32)arg0->unk38E * 4.0f) & 0xFFF) << 12) | ((s32)((f32)arg0->unk390 * 4.0f) & 0xFFF), (((s32)((f32)arg0->unk392 * 4.0f) & 0xFFF) << 12) | ((s32)((f32)arg0->unk394 * 4.0f) & 0xFFF));
        }
    }
    L119_WRITE_GFX(glist++, 0xDA380000, osVirtualToPhysical((u8 *)arg0 + (D_807FC929 << 7) + (D_807444FC << 6) + 0x128));

    for (i = 0, cursor = arg0; i < arg0->unk380; i++) {
        if (D_807F6009 != 5 || D_807F600C != (s32)cursor->unk370) {
            L119_WRITE_GFX(glist++, 0xE7000000, 0);
            switch (arg0->unk330->unkB) {
                case 0:
                    gDPLoadTextureBlock_4b(glist++, cursor->unk370, arg0->unk330->unkA, arg0->unk330->unkC, arg0->unk330->unkE, 0, G_TX_CLAMP, G_TX_CLAMP, 0, 0, 0, 0);
                    break;
                case 1:
                    gDPLoadTextureBlock(glist++, cursor->unk370, arg0->unk330->unkA, G_IM_SIZ_8b, arg0->unk330->unkC, arg0->unk330->unkE, 0, G_TX_CLAMP, G_TX_CLAMP, 0, 0, 0, 0);
                    break;
                case 2:
                    gDPLoadTextureBlock(glist++, cursor->unk370, arg0->unk330->unkA, G_IM_SIZ_16b, arg0->unk330->unkC, arg0->unk330->unkE, 0, G_TX_CLAMP, G_TX_CLAMP, 0, 0, 0, 0);
                    break;
                case 3:
                    gDPLoadTextureBlock(glist++, cursor->unk370, arg0->unk330->unkA, G_IM_SIZ_32b, arg0->unk330->unkC, arg0->unk330->unkE, 0, G_TX_CLAMP, G_TX_CLAMP, 0, 0, 0, 0);
                    break;
            }
            D_807F600C = (s32)cursor->unk370;
        }
        L119_WRITE_GFX(glist++, 0x01004008, osVirtualToPhysical((u8 *)arg0 + (i << 6) + 0x28));
        L119_WRITE_GFX(glist++, 0x06000206, 0x406);
        cursor = (L119_EffectView *)((u8 *)cursor + 4);
    }
    L119_WRITE_GFX(glist++, 0xD8380002, 0x40);
    L119_WRITE_GFX(glist++, 0xE7000000, 0);
    L119_WRITE_GFX(glist++, 0xE3001801, 0);
    if (arg0->unk36F != 0) {
        L119_WRITE_GFX(glist++, 0xDA380007, &D_2000000);
        L119_WRITE_GFX(glist++, 0xDA380005, &D_2000200);
        if (arg0->unk388 == -1) {
            L119_WRITE_GFX(glist++, 0xED000000, ((((s32)((f32)D_80744490 * 4.0f) & 0xFFF) << 12) | ((s32)((f32)D_80744494 * 4.0f) & 0xFFF)));
        }
    }
    L119_WRITE_GFX(glist++, 0xE7000000, 0);
    L119_WRITE_GFX(glist++, 0xDF000000, 0);
    D_807F6009 = 5;
    return arg1;
}
