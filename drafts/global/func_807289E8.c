// func_807289E8 (src/global/1295B0.c): Stage 5: 1071/1071 insns, frame 0xE8, saved set and all stack offsets match; diffs are t-register numbering (case 6 lh a0/a1 temps etc.) and case-5 actorSpawn delay slot (or a1 vs mtc1). Permuter 280s from this base found nothing below 885. Tricks: distinct locals per case, 'case 7: break;', volatile u8 sel6, u8 idx6[2] copied via *(A2BytePair{u16 w} *) struct assign so &idx6 is a hoisted pointer, gap locals for slot offsets, s32 func_80714CC0 proto
typedef struct A2PtrPair {
    void *p[2];
} A2PtrPair;

typedef struct A2BytePair {
    u16 w;
} A2BytePair;

typedef struct A2B44 {
    /* 0x00 */ u8 pad0[0x7C];
    /* 0x7C */ f32 unk7C;
    /* 0x80 */ f32 unk80;
    /* 0x84 */ u8 pad84[0xDB];
    /* 0x15F */ u8 unk15F;
    /* 0x160 */ f64 unk160;
} A2B44;

extern A2PtrPair D_80755794;
extern u16 D_8075579C;
extern u8 D_8071FB34[];
extern u8 D_8071FB54[];
extern u8 D_8071FC0C[];
extern u8 D_8071FC40[];
extern u8 D_8071FC58[];
extern u8 D_8071FFA0[];
extern void *D_8074E880[];
extern s32 D_807F5D10;
#define A2B44V ((A2B44 *)D_807FBB44)

u32 func_806119A0(void);
void func_80609140(s32, s32, f32, f32, s32, s32);
void func_80614EBC(void *, s32);
void func_8061F0B0(s32, s32, s32);
void func_8067DF44(f32, f32, f32, f32, u8, u8);
void effectSpawnDebrisParticles(void *, f32, f32, f32, f32);
void func_8068B80C(s16);
void func_8071495C(void);
void func_80714950(s32);
void func_8071496C(s16);
void func_8071498C(void *);
void func_80714998(u8);
void func_807149A8(s32);
void func_807149B8(s32);
void func_807149C8(s32, s32, s32, s32);
void func_807149FC(s32);
void func_80714A28(s32);
s32 func_80714CC0(void *, f32, f32, f32, f32);
void func_8071720C(void);
void func_80717404(void);
void func_80717D4C(void);
void func_80718BF4(void);
void actorSpawnEffectChild(f32, f32, f32, f32, f32, void *, u8);
void effectSpawnBoneDefault(void *, s16, f32, f32, f32, f32, s32);
void effectSpawnMultiTierRing(f32, s32, f32, f32, f32);

void func_807289E8(s16 arg0, s16 arg1, s16 arg2, s16 arg3) {
    Zone *group;
    s16 x;
    s16 y;
    s16 z;
    s16 i;
    f32 ox0;
    f32 oy0;
    f32 oz0;
    A2PtrPair fx6;
    s16 gap6;
    u8 idx6[2];
    volatile u8 sel6;
    s16 gapA;
    s16 gapB;
    s16 ang6;
    f32 scale8;
    f32 kx8;
    f32 kz8;
    s32 gapD;
    f32 ox10;
    f32 oy10;
    s8 jx;
    s8 jy;
    s8 jz;
    f32 kx14;
    f32 ky14;
    f32 kz14;

    group = D_80755690->unk4;
    x = group->unk14[arg1].unk0;
    y = group->unk14[arg1].unk2;
    z = group->unk14[arg1].unk4;
    switch (arg0) {
        case 0:
            for (i = 0; i < arg3; i++) {
                ox0 = (f32)((func_80611A44() >> 0xF) % 0x8000 % 40 - 20.0);
                oy0 = (f32)((func_80611A44() >> 0xF) % 0x8000 % 20);
                oz0 = (f32)((func_80611A44() >> 0xF) % 0x8000 % 40 - 20.0);
                func_807149C8(0xE6, 0xE6, 0xE6, 0xC8);
                func_8071498C(func_80717D4C);
                func_80714950(-(i * 20));
                func_807149B8(1);
                func_80714998(arg2);
                func_80714CC0(D_8071FFA0, 1.5f, (f32)x + ox0, (f32)y + oy0, (f32)z + oz0);
            }
            return;
        case 7:
            break;
        case 1:
            effectSpawnMultiTierRing(0.36f, 1, (f32)x, (f32)(y + 5), (f32)z);
            func_8061F0B0(D_807F5D10, 0x14, 0xF);
            return;
        case 2:
            func_8068B80C(arg0);
            return;
        case 3:
            actorSpawnEffectChild((f32)x, (f32)y, (f32)z, arg2 * 0.01, arg3 * 0.01, NULL, 0);
            return;
        case 4:
            func_8067DF44((f32)x, (f32)y, (f32)z, arg2 * 0.01, 0, 0);
            return;
        case 5:
            if (arg2 != 0x14) {
                actorSpawn(0x104, 0);
                A2B44V->unk160 = arg3;
            }
            switch (arg2) {
                case 0:
                    A2B44V->unk7C = 450.0f;
                    A2B44V->unk80 = 500.0f;
                    A2B44V->unk15F = 0x14;
                    break;
                case 1:
                    A2B44V->unk7C = 820.0f;
                    A2B44V->unk80 = 500.0f;
                    A2B44V->unk15F = 0x15;
                    break;
                case 10:
                    func_80609140(0x3F3, 0x7FFF, 63.0f, 1.0f, 0, 0);
                    A2B44V->unk15F = 0;
                    A2B44V->unk7C = 500.0f;
                    A2B44V->unk80 = 80.0f;
                    break;
                case 11:
                    func_80609140(0x3F4, 0x7FFF, 63.0f, 1.0f, 0, 0);
                    A2B44V->unk15F = 0x89;
                    A2B44V->unk7C = 600.0f;
                    A2B44V->unk80 = 80.0f;
                    break;
                case 12:
                    func_80609140(0x3F4, 0x7FFF, 63.0f, 1.0f, 0, 0);
                    A2B44V->unk15F = 0x47;
                    A2B44V->unk7C = 600.0f;
                    A2B44V->unk80 = 80.0f;
                    break;
                case 13:
                    A2B44V->unk15F = 0x23;
                    A2B44V->unk7C = 600.0f;
                    A2B44V->unk80 = 80.0f;
                    break;
                case 20:
                    actorSpawn(0x92, 0x73);
                    func_80614EBC(D_807FBB44, 0x42A);
                    return;
                case 30:
                case 31:
                case 32:
                case 33:
                case 34:
                case 35:
                    A2B44V->unk15F = arg2;
                    A2B44V->unk7C = 500.0f;
                    A2B44V->unk80 = 80.0f;
                    break;
            }
            break;
        case 15:
            actorSpawn(0x92, 0x73);
            func_80614EBC(D_807FBB44, 0x42A);
            return;
        case 6:
            for (i = 0; i < arg3; i++) {
                fx6 = D_80755794;
                *(A2BytePair *)idx6 = *(A2BytePair *)&D_8075579C;
                sel6 = (func_80611A44() >> 0xF) % 2;
                ang6 = mathAngleBetweenPoints2D((f32)((ZoneEntry *)(group->unk14 + arg2))->unk0, (f32)((ZoneEntry *)(group->unk14 + arg2))->unk4, (f32)x, (f32)z);
                func_807149B8(1);
                func_807149FC(idx6[sel6]);
                func_8071498C(func_80717404);
                func_80714950((ang6 << 16) + 3);
                func_80714CC0(((void **)&fx6)[sel6], (f32)((func_80611A44() >> 0xF) % 1000 * 0.0005 + 0.2), (f32)x, (f32)(y + 10), (f32)z);
            }
            return;
        case 12:
            func_807149A8(0x7D0);
            func_80714998(1);
            func_80714CC0(D_8071FC0C, arg2 * 0.01, (f32)x, (f32)y, (f32)z);
            return;
        case 8:
            scale8 = arg2 * 0.01;
            for (i = 0; i < arg3; i++) {
                kx8 = ((func_80611A44() >> 0xF) % 0x8000 % 40 - 20.0) * scale8;
                kz8 = ((func_80611A44() >> 0xF) % 0x8000 % 40 - 20.0) * scale8;
                func_807149A8(0x7D0);
                func_807149B8(1);
                func_80714CC0(D_8071FB54, scale8 * 1.3, (f32)x + kx8, (f32)y, (f32)z + kz8);
                func_807149C8(0xD2, 0xD2, 0xD2, 0xC8);
                effectSpawnBoneDefault(NULL, 0, scale8 * 1.2, (f32)x + kx8, (f32)y, (f32)z + kz8, -0xB4);
            }
            return;
        case 9:
            for (i = 0; i < arg2; i++) {
                func_80714998(2);
                func_8071498C(func_8071720C);
                func_807149B8(1);
                func_80714950(1);
                func_8071496C(i * 3);
                func_80714CC0(D_8074E880[(func_80611A44() >> 0xF) % 1000 % 3], arg3 * 0.01, (f32)x, (f32)y, (f32)z);
            }
            return;
        case 10:
            for (i = 0; i < arg2; i++) {
                ox10 = (f32)((func_80611A44() >> 0xF) % 300);
                oy10 = (f32)((func_80611A44() >> 0xF) % 200);
                func_8071495C();
                func_80714CC0(D_8071FB34, arg3 * 0.01, ox10, oy10, -10.0f);
            }
            return;
        case 11:
            for (i = 0; i < arg2; i++) {
                jx = (func_806119A0() / 10000 % 200) / 10.0 - 10.0;
                jy = (func_806119A0() / 10000 % 200) / 10.0 - 7.0;
                jz = (func_806119A0() / 10000 % 200) / 10.0 - 10.0;
                func_807149B8(1);
                func_807149FC(2);
                func_80714950(0x64);
                func_8071498C(func_80717D4C);
                func_8071496C(i / 7);
                func_80714CC0(D_8071FC58, arg3 * 0.01, (f32)(x + jx), (f32)(y + jy), (f32)(z + jz));
            }
            return;
        case 13:
            effectSpawnDebrisParticles(NULL, arg2 * 0.01, (f32)x, (f32)y, (f32)z);
            return;
        case 14:
            for (i = 0; i < arg2; i++) {
                kx14 = (f32)(func_806119A0() / 10000 % 200) / 10.0 - 5.0;
                ky14 = (f32)(func_806119A0() / 10000 % 200) / 10.0 - 5.0;
                kz14 = (f32)(func_806119A0() / 10000 % 200) / 10.0 - 5.0;
                func_807149B8(1);
                func_80714950(2);
                func_807149FC(-1);
                func_8071498C(func_80718BF4);
                func_80714A28(4);
                func_80714CC0(D_8071FC40, 0.0f, (f32)x + kx14, (f32)y + ky14, (f32)z + kz14);
            }
            break;
    }
}
