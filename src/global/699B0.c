#include "common.h"
#include "actor.h"


typedef struct {
    u8 unk0;
    u8 pad[0x1F];
} ParticlePathHeader;

extern ParticlePathHeader D_80748BA0[];
extern u8 D_807F9440[];
extern s32 D_807F9448;

void particleFindPathIndices(arg0)
s16 arg0;
{
    s32 limit;
    u8 *ptr;
    s32 i;

    limit = 13;
    D_807F9448 = 0;
    for (i = 0, ptr = (u8 *)D_80748BA0; i < limit; i++, ptr += 0x20) {
        if (arg0 == *ptr) {
            if (D_807F9448 != 8) {
                D_807F9440[D_807F9448++] = i;
            }
        }
    }
}

typedef struct ParticlePathNode {
    u8 pad0[2];
    s16 unk2;
    s16 unk4;
    s16 unk6;
    s16 unk8;
    s16 unkA;
    s16 unkC;
    u8 padE[2];
    f32 unk10;
    s16 unk14;
    u8 pad16[2];
    f32 unk18;
    f32 unk1C;
} ParticlePathNode;

typedef struct {
    char pad[0x21C];
    f32 unk21C;
    f32 unk220;
    f32 unk224;
} ParticlePlayerPosition;

extern ParticlePlayerPosition *D_807FC924;
extern u8 D_807FC928;
extern u32 D_8076A064;
extern s32 D_8072140C;
extern s32 D_8071FF18;

s32 func_80611A44(void);
void func_80714944(s32);
void func_80714950(s32);
void func_8071498C(void (*)(void));
void func_80714998(s32);
void func_807149A8(s32);
void func_807149B8(s32);
void func_807149C8(s32, s32, s32, s32);
void func_807149FC(s32);
void func_80714A28(s32);
void func_80714CC0(void *, f32, f32, f32, f32);
void func_80717B64(void);
void func_80717D4C(void);

void particleSpawnPathTrail(void) {
    s32 i;
    u8 idx;
    ParticlePathNode *node;
    ParticlePlayerPosition *player;
    f32 dz;
    f32 dx;
    f32 dy;
    f32 t;
    f32 factor;

    if (D_807FC928 < 2) {
        for (i = 0; i < D_807F9448; i++) {
            idx = D_807F9440[i];
            player = D_807FC924;
            node = (ParticlePathNode *)((u8 *)D_80748BA0 + (idx << 5));
                dz = player->unk224 - (f32)node->unk6;
                dx = player->unk21C - (f32)node->unk2;
                dy = player->unk220 - (f32)node->unk4;
                if (sqrtf((dz * dz) + ((dx * dx) + (dy * dy))) < (f32)node->unk14) {
                    if ((D_8076A064 % 18) == 0) {
                        for (t = 0.0f; (f64)t <= 1.0; t += node->unk10) {
                            func_807149B8(1);
                            func_80714998(3);
                            func_807149C8(0xFF, 0xFF, 0xFF, 0x96);
                            func_80714A28(4);
                            func_8071498C(func_80717B64);
                            func_807149FC(2);
                            func_80714944((func_80611A44() % 10000) % 6);
                            func_807149A8(node->unk14);
                            func_80714CC0(&D_8072140C, node->unk18,
                                          (f32)(node->unk8 - node->unk2) * t + (f32)node->unk2,
                                          (f32)(node->unkA - node->unk4) * t + (f32)node->unk4,
                                          (f32)(node->unkC - node->unk6) * t + (f32)node->unk6);
                        }
                    }
                    if ((D_8076A064 % 10) == 0) {
                        func_807149B8(1);
                        func_80714998(3);
                        func_807149C8(0xFF, 0xFF, 0xFF, 0x96);
                        func_80714A28(4);
                        func_8071498C(func_80717D4C);
                        func_80714950(-0xAA);
                        func_807149A8(node->unk14);
                        factor = (f32)((f64)((func_80611A44() % 10000) % 1000) / 1000.0);
                        func_80714CC0(&D_8071FF18, node->unk1C,
                                      (f32)(node->unk8 - node->unk2) * factor + (f32)node->unk2,
                                      (f32)(node->unkA - node->unk4) * factor + (f32)node->unk4,
                                      (f32)(node->unkC - node->unk6) * factor + (f32)node->unk6);
                    }
                }
            }
    }
}
