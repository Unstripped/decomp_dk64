// func_807105D4 (src/global/114270.c): Stage 6: three-case gDPLoadTextureBlock reconstruction; only remaining mismatch is the target's early sw a1,0x74(sp). K&R, u8/s16 formal, address-taking, and parameter reassignment variants did not reproduce it.
typedef struct L105D4TextureDescriptor {
    u8 unk0[8];
    u8 format;
    u8 type;
    u8 unkA[0xA];
} L105D4TextureDescriptor;

extern u8 D_80755264;
extern u32 D_807FD9F0[];
extern u8 D_807FDA18;
extern u8 D_807FDA19;
extern u8 D_807FDA1C;

#define L105D4_TEXTURE ((L105D4TextureDescriptor *)((u8 *)&D_80755264 + (D_807FDA1C * 0x14)))

Gfx *func_807105D4(Gfx *arg0, s32 arg1) {
    arg1 &= 0xFF;
    switch (L105D4_TEXTURE->type) {
    case 1:
        gDPLoadTextureBlock(arg0++, D_807FD9F0[arg1], L105D4_TEXTURE->format, G_IM_SIZ_8b, D_807FDA18, D_807FDA19, 0, G_TX_CLAMP, G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
        break;
    case 2:
        gDPLoadTextureBlock(arg0++, D_807FD9F0[arg1], L105D4_TEXTURE->format, G_IM_SIZ_16b, D_807FDA18, D_807FDA19, 0, G_TX_CLAMP, G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
        break;
    case 3:
        gDPLoadTextureBlock(arg0++, D_807FD9F0[arg1], L105D4_TEXTURE->format, G_IM_SIZ_32b, D_807FDA18, D_807FDA19, 0, G_TX_CLAMP, G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
        break;
    }
    return arg0;
}

#undef L105D4_TEXTURE
