// func_80715E94 (src/global/119370.c): stage 2: behavior reconstruction; loop now preserves arg0 for vertex and post-loop fields while advancing the 4-byte texture cursor, matching the target ownership; target-style duplicate division guards; latest compiled trial before cursor correction was 9888 versus 10400 bytes
typedef struct L1TextureNode {
    u8 pad0[0xA];
    u8 unkA;
    u8 unkB;
    s16 unkC;
    s16 unkE;
    u8 pad10[4];
    u8 unk14;
} L1TextureNode;

typedef struct L1EffectView {
    u8 pad0[0x21];
    u8 unk21;
    u8 pad22[0x30E];
    L1TextureNode *unk330;
    u8 pad334[0xC];
    f32 unk340;
    f32 unk344;
    s32 unk348;
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
    s16 unk38A;
    u16 unk38C;
    s16 unk38E;
    s16 unk390;
    s16 unk392;
    s16 unk394;
} L1EffectView;

#define L1_WRITE_GFX(pkt, _w0, _w1) { Gfx *_g = (pkt); _g->words.w0 = (_w0); _g->words.w1 = (u32)(_w1); }

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
s32 func_8065C334(f32, f32, s32, s32, u8 *, u8 *, u8 *, s32);
s32 mapChunkContainsPoint(s16, s16, s16);
s32 mapChunkIsInUse(s16);

Gfx *func_80715E94(Ua1Effect *arg0, Gfx *arg1, s16 arg2) {
    L1EffectView *effect = (L1EffectView *)arg0;
    L1EffectView *cursor;
    Gfx *glist;
    s32 i;
    s32 tile;
    s32 rows;
    s32 divisor;
    s32 divisor2;
    s16 chunk;
    u8 red;
    u8 green;
    u8 blue;
    f32 colorRed = 1.0f;
    f32 colorGreen = 1.0f;
    f32 colorBlue = 1.0f;

    if (effect->unk38C & 0x50) {
        return arg1;
    }
    if ((((u8 *)D_807FBB4C)[0x154] == 0x83 || ((u8 *)D_807FBB4C)[0x154] == 0x67) && !(effect->unk38C & 0x20)) {
        return arg1;
    }
    if ((D_807FBB60 & 0x100002) == 0x100002 && !(effect->unk38C & 0x100)) {
        return arg1;
    }
    chunk = arg2;
    if (chunk == -1) {
        chunk = effect->unk38A;
    }
    if (effect->unk388 != -1) {
        if (effect->unk36F != 0) {
            if (mapChunkContainsPoint((s16)((f64)effect->unk340 * 0.25), (s16)((f64)effect->unk344 * 0.25), effect->unk388) == 0) {
                return arg1;
            }
        } else if (chunk != effect->unk388) {
            return arg1;
        }
    }

    glist = ((Gfx **)effect)[(effect->unk21 * 2) + D_807444FC];
    effect->unk21++;
    L1_WRITE_GFX(arg1++, 0xDE000000, osVirtualToPhysical(glist));
    L1_WRITE_GFX(glist++, 0xE7000000, 0);
    L1_WRITE_GFX(glist++, 0xE3000A01, 0);
    L1_WRITE_GFX(glist++, 0xD9000000, 0);
    L1_WRITE_GFX(glist++, 0xE3001801, 0xC0);
    if (effect->unk36E != 0) {
        L1_WRITE_GFX(glist++, 0xD9FFFFFF, 0x200005);
        L1_WRITE_GFX(glist++, 0xE200001C, 0x504B50);
    } else {
        L1_WRITE_GFX(glist++, 0xD9FFFFFF, 0x200004);
        L1_WRITE_GFX(glist++, 0xE200001C, 0x504240);
    }
    L1_WRITE_GFX(glist++, 0xD7000002, 0xFFFFFFFF);
    L1_WRITE_GFX(glist++, 0xFC119623, 0xFF2FFFFF);

    node = effect->unk330;
    if (node->unk14 == 0 && mapChunkIsInUse(chunk)) {
        func_8065C334(effect->unk340, effect->unk344, effect->unk348, 0, &red, &green, &blue, chunk);
        colorRed = (f32)((f64)red / 255.0);
        colorGreen = (f32)((f64)green / 255.0);
        colorBlue = (f32)((f64)blue / 255.0);
    }
    L1_WRITE_GFX(glist++, 0xFA000000, ((s32)((f32)effect->unk36A * colorRed) << 24) | (((s32)((f32)effect->unk36B * colorGreen) & 0xFF) << 16) | (((s32)((f32)effect->unk36C * colorBlue) & 0xFF) << 8) | effect->unk36D);
    if (effect->unk36F != 0) {
        L1_WRITE_GFX(glist++, 0xDA380007, &D_20000C0);
        L1_WRITE_GFX(glist++, 0xDA380003, &D_2000180);
        glist = func_805FD030(glist);
        if (effect->unk388 == -1) {
            L1_WRITE_GFX(glist++, 0xED000000 | (((s32)((f32)effect->unk38E * 4.0f) & 0xFFF) << 12) | ((s32)((f32)effect->unk390 * 4.0f) & 0xFFF), (((s32)((f32)effect->unk392 * 4.0f) & 0xFFF) << 12) | ((s32)((f32)effect->unk394 * 4.0f) & 0xFFF));
        }
    }
    L1_WRITE_GFX(glist++, 0xDA380000, osVirtualToPhysical((u8 *)effect + (D_807FC929 << 7) + (D_807444FC << 6) + 0x128));

    cursor = effect;
    for (i = 0; i < effect->unk380; i++) {
        node = effect->unk330;
        if (D_807F6009 != 5 || D_807F600C != (s32)cursor->unk370) {
            L1_WRITE_GFX(glist++, 0xE7000000, 0);
            switch (node->unkB) {
                case 0:
                    tile = (((node->unkC * node->unkE) + 3) >> 2) - 1;
                    if (tile >= 0x7FF) {
                        tile = 0x7FF;
                    }
                    divisor = node->unkC / 16;
                    rows = divisor;
                    if (divisor <= 0) {
                        rows = 1;
                    }
                    divisor2 = divisor;
                    if (divisor <= 0) {
                        divisor2 = 1;
                    }
                    rows = (rows + 0x7FF) / divisor2;
                    L1_WRITE_GFX(glist++, 0xFD100000 | ((node->unkA & 7) << 21), cursor->unk370);
                    L1_WRITE_GFX(glist++, 0xF5100000 | ((node->unkA & 7) << 21), 0x07080200);
                    L1_WRITE_GFX(glist++, 0xE6000000, 0);
                    L1_WRITE_GFX(glist++, 0xF3000000, 0x07000000 | rows | (tile << 12));
                    L1_WRITE_GFX(glist++, 0xE7000000, 0);
                    L1_WRITE_GFX(glist++, 0xF5000000 | ((node->unkA & 7) << 21) | ((((node->unkC / 2) + 7) >> 3) << 9), 0x80200);
                    L1_WRITE_GFX(glist++, 0xF2000000, ((((node->unkC - 1) * 4) & 0xFFF) << 12) | (((node->unkE - 1) * 4) & 0xFFF));
                    break;
                case 1:
                    tile = (((node->unkC * node->unkE) + 1) >> 1) - 1;
                    if (tile >= 0x7FF) {
                        tile = 0x7FF;
                    }
                    divisor = node->unkC / 8;
                    rows = divisor;
                    if (divisor <= 0) {
                        rows = 1;
                    }
                    divisor2 = divisor;
                    if (divisor <= 0) {
                        divisor2 = 1;
                    }
                    rows = (rows + 0x7FF) / divisor2;
                    L1_WRITE_GFX(glist++, 0xFD100000 | ((node->unkA & 7) << 21), cursor->unk370);
                    L1_WRITE_GFX(glist++, 0xF5100000 | ((node->unkA & 7) << 21), 0x07080200);
                    L1_WRITE_GFX(glist++, 0xE6000000, 0);
                    L1_WRITE_GFX(glist++, 0xF3000000, 0x07000000 | rows | (tile << 12));
                    L1_WRITE_GFX(glist++, 0xE7000000, 0);
                    L1_WRITE_GFX(glist++, 0xF5000000 | ((node->unkA & 7) << 21) | 0x80000 | ((((node->unkC + 7) >> 3) & 0x1FF) << 9), 0x80200);
                    L1_WRITE_GFX(glist++, 0xF2000000, ((((node->unkC - 1) * 4) & 0xFFF) << 12) | (((node->unkE - 1) * 4) & 0xFFF));
                    break;
                case 2:
                    tile = (node->unkC * node->unkE) - 1;
                    if (tile >= 0x7FF) {
                        tile = 0x7FF;
                    }
                    divisor = (node->unkC * 2) / 8;
                    rows = divisor;
                    if (divisor <= 0) {
                        rows = 1;
                    }
                    divisor2 = divisor;
                    if (divisor <= 0) {
                        divisor2 = 1;
                    }
                    rows = (rows + 0x7FF) / divisor2;
                    L1_WRITE_GFX(glist++, 0xFD100000 | ((node->unkA & 7) << 21), cursor->unk370);
                    L1_WRITE_GFX(glist++, 0xF5100000 | ((node->unkA & 7) << 21), 0x07080200);
                    L1_WRITE_GFX(glist++, 0xE6000000, 0);
                    L1_WRITE_GFX(glist++, 0xF3000000, 0x07000000 | rows | (tile << 12));
                    L1_WRITE_GFX(glist++, 0xE7000000, 0);
                    L1_WRITE_GFX(glist++, 0xF5000000 | ((node->unkA & 7) << 21) | 0x100000 | (((((node->unkC * 2) + 7) >> 3) & 0x1FF) << 9), 0x80200);
                    L1_WRITE_GFX(glist++, 0xF2000000, ((((node->unkC - 1) * 4) & 0xFFF) << 12) | (((node->unkE - 1) * 4) & 0xFFF));
                    break;
                case 3:
                    tile = (node->unkC * node->unkE) - 1;
                    if (tile >= 0x7FF) {
                        tile = 0x7FF;
                    }
                    divisor = (node->unkC * 4) / 8;
                    rows = divisor;
                    if (divisor <= 0) {
                        rows = 1;
                    }
                    divisor2 = divisor;
                    if (divisor <= 0) {
                        divisor2 = 1;
                    }
                    rows = (rows + 0x7FF) / divisor2;
                    L1_WRITE_GFX(glist++, 0xFD180000 | ((node->unkA & 7) << 21), cursor->unk370);
                    L1_WRITE_GFX(glist++, 0xF5180000 | ((node->unkA & 7) << 21), 0x07080200);
                    L1_WRITE_GFX(glist++, 0xE6000000, 0);
                    L1_WRITE_GFX(glist++, 0xF3000000, 0x07000000 | rows | (tile << 12));
                    L1_WRITE_GFX(glist++, 0xE7000000, 0);
                    L1_WRITE_GFX(glist++, 0xF5000000 | ((node->unkA & 7) << 21) | 0x180000 | (((((node->unkC * 2) + 7) >> 3) & 0x1FF) << 9), 0x80200);
                    L1_WRITE_GFX(glist++, 0xF2000000, ((((node->unkC - 1) * 4) & 0xFFF) << 12) | (((node->unkE - 1) * 4) & 0xFFF));
                    break;
            }
            D_807F600C = (s32)cursor->unk370;
        }
        L1_WRITE_GFX(glist++, 0x01004008, osVirtualToPhysical((u8 *)effect + (i << 6) + 0x28));
        L1_WRITE_GFX(glist++, 0x06000206, 0x406);
        cursor = (L1EffectView *)((u8 *)cursor + 4);
    }
    L1_WRITE_GFX(glist++, 0xD8380002, 0x40);
    L1_WRITE_GFX(glist++, 0xE7000000, 0);
    L1_WRITE_GFX(glist++, 0xE3001801, 0);
    if (effect->unk36F != 0) {
        L1_WRITE_GFX(glist++, 0xDA380007, &D_2000000);
        L1_WRITE_GFX(glist++, 0xDA380005, &D_2000200);
        if (effect->unk388 == -1) {
            L1_WRITE_GFX(glist++, 0xED000000, ((((s32)((f32)D_80744490 * 4.0f) & 0xFFF) << 12) | ((s32)((f32)D_80744494 * 4.0f) & 0xFFF)));
        }
    }
    L1_WRITE_GFX(glist++, 0xE7000000, 0);
    L1_WRITE_GFX(glist++, 0xDF000000, 0);
    D_807F6009 = 5;
    return arg1;
}
