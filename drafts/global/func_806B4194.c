// func_806B4194 (src/global/B7490.c): Stage 3: switch(2,1,0,default) with u8 c[4]/c[2] (gives 0x2E slot) and f32 f spills at defs like target; remaining: IDO puts default 'move v0,zero' block right after the compare chain (beql/b) whereas target has bnel+delay move v0,zero and the dead default block after case 0; temps t7/t8/t9 vs a0/t7; arg a1/a2 andi pattern ok. sp2E needs c[]-array form (plain u8 local gets reg-allocated/sb late).
typedef struct M6ActorX {
    /* 0x000 */ u8 pad0[0x6E];
    /* 0x06E */ s16 unk6E;
    /* 0x070 */ u8 pad70[0x50];
    /* 0x0C0 */ f32 unkC0;
    /* 0x0C4 */ f32 unkC4;
    /* 0x0C8 */ u8 padC8[0x1E];
    /* 0x0E6 */ s16 unkE6;
    /* 0x0E8 */ s16 unkE8;
    /* 0x0EA */ u8 padEA[2];
    /* 0x0EC */ s16 unkEC;
    /* 0x0EE */ u8 padEE[0x46];
    /* 0x134 */ s16 unk134;
    /* 0x136 */ u8 pad136[0x1E];
    /* 0x154 */ u8 unk154;
    /* 0x155 */ u8 unk155;
    /* 0x156 */ u8 pad156[0x22];
    /* 0x178 */ s16 *unk178;
} M6ActorX;

extern Actor *D_807FBB40;
extern u32 D_8076A064;
void func_80714998(s32);
void func_807149C8(s32, s32, u8, u8);
void effectSpawnBoneDefault(void *, s16, f32, f32, f32, f32, s32);

void func_806B4194(void) {
    u8 c[4];
    f32 f;
    u32 var_v0;

    switch (*(s16 *) &D_807FBB40->unk134) {
    case 2:
        c[2] = 0xC8;
        var_v0 = 0x20;
        f = 0.5f;
        break;
    case 1:
        var_v0 = 0x18;
        c[2] = 0x64;
        f = 1.0f;
        break;
    case 0:
        var_v0 = 8;
        c[2] = 0x32;
        f = 1.5f;
        break;
    default:
        var_v0 = 0;
        break;
    }
    if ((var_v0 != 0) && ((D_8076A064 % var_v0) == 0)) {
        func_80714998(3);
        func_807149C8(c[2], c[2], c[2] & 0xFF, *(u8 *) ((u8 *) D_807FBB40 + 0x129));
        effectSpawnBoneDefault(D_807FBB40, 1, f, 0.0f, 0.0f, 0.0f, -0x50);
    }
}
