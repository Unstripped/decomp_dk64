// func_80031AA0 (src/boss/C920.c): stage 4 (W2BossL revisit): 1051 vs 1050 insns (1 insn diff: move v0,t3 after andi sp5C). (f32)0 spelling merged float zero webs into f2 matching 1710-1770; j=D_80035B70+1 before s->unk10=0 aligned 1ce4-1cf0; k=s->unk14 before if(sp5C<0) put lb in delay slot matching 1fe0-1ffc; s32 return on func_805FF378 cut deadsweep score 540->415.
typedef struct BossModelInfo {
    u8 pad0[0x34];
    f32 unk34;
    f32 unk38;
    f32 unk3C;
} BossModelInfo;

typedef struct BossSpawnState {
    void *unk0;
    s8 unk4;
    s8 unk5;
} BossSpawnState;

typedef struct BossSpawnerState {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    s16 unkC;
    s16 unkE;
    s16 unk10;
    s8 unk12;
    s8 unk13;
    s8 unk14;
    s8 unk15;
    s8 unk16;
    s8 unk17;
} BossSpawnerState;

typedef struct BossSpawnerActor {
    u8 pad0[4];
    BossModelInfo *unk4;
    u8 pad8[0x60 - 8];
    s32 unk60;
    u8 pad64[0x7C - 0x64];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
    u8 pad88[0xA4 - 0x88];
    u8 unkA4;
    u8 padA5[0xE6 - 0xA5];
    s16 unkE6;
    u8 padE8[0x128 - 0xE8];
    s16 unk128;
    s16 unk12A;
    u8 pad12C[0x144 - 0x12C];
    u8 unk144;
    u8 pad145;
    s16 unk146;
    u8 pad148[0x154 - 0x148];
    u8 unk154;
    u8 unk155;
    u8 pad156[0x174 - 0x156];
    BossSpawnerState *unk174;
} BossSpawnerActor;

typedef struct BossSpawnedActor {
    u8 pad0[4];
    BossModelInfo *unk4;
    u8 pad8[0x60 - 8];
    s32 unk60;
    u8 pad64[0x80 - 0x64];
    f32 unk80;
    u8 pad84[0x174 - 0x84];
    BossSpawnState *unk174;
} BossSpawnedActor;

extern BossSpawnedActor *D_807FBB44;
extern u8 D_807FBDC4;
extern s16 D_80035B00[];
extern s16 D_80035B08[];
extern s8 D_80035B28;
extern s16 D_80035B2C;
extern s8 D_80035B30[];
extern s8 D_80035B34;
extern u8 D_80035B38;
extern f32 D_80035B3C;
extern s8 D_80035B40;
extern s8 D_80035B44[];
extern s16 D_80035B4C[];
extern u8 D_80035B58[];
extern s16 D_80035B60[];
extern s8 D_80035B68;
extern s8 D_80035B6C;
extern s16 D_80035B70;
extern s8 D_80036DC0;
extern f32 D_80036DC4;

s32 actorSpawn(s32, s32);
void *actorListFindActorById(s16);
void actorDespawn(void *);
s32 func_805FF378(s32, s32);
void collisionCheckActorFloor(void *, f32, f32, f32, void *);
void func_8068A764(void *, u8);
void func_806C8E58(s16);
void func_806F09F0(void *, u16);
void func_8067AAB8(void *, void *, s32, f32, s32);
void sfxPlayOnFreeSlot();
void camPausePath(void);
void camResumePath(void);
void func_80724994(s32, s32, s32, s32, s32);
s32 randomLcgNext(void);
f32 randomFloat(void);
s32 sfxAllocateChannel();
void bossSpawnParticleRing(s32, s16, s16, s16, s32, s32);
void lightAdd(f32, f32, f32, f32, f32, f32, f32, s32, s32, s32, s32);
void lightSetColor(f32, f32, f32, s32);
void func_8068B80C(void);

#define SPAWNER_ACTOR ((BossSpawnerActor *)D_807FBB40)
#define SPAWNER_PLAYER ((BossSpawnerActor *)D_807FBB4C)

void func_80031AA0(void) {
    f32 dx;
    f32 dz;
    s32 k;
    s32 i;
    BossSpawnerState *s;
    s8 sp6B;
    s8 sp6A;
    s8 sp69;
    s8 sp68;
    s8 sp67;
    BossSpawnState *st;
    s32 sp5C;
    f32 lx;
    f32 lz;
    s16 j;

    s = SPAWNER_ACTOR->unk174;
    sp67 = 0;
    sp68 = 0;
    sp6A = 0;
    if (!(SPAWNER_ACTOR->unk60 & 0x10)) {
        D_80035B28 = 0xF;
        D_80035B34 = 0;
        D_80035B3C = 0.0f;
        s->unkC = 0x1E;
        s->unkE = 1;
        s->unk0 = SPAWNER_ACTOR->unk80;
        s->unk14 = 0;
        D_80035B6C = 0;
        s->unk12 = 0;
        D_80035B70 = 5;
        for (i = 0; i != 8; i++) {
            if (actorSpawn(0xA6, D_80035B60[i >> 1]) != 0) {
                st = D_807FBB44->unk174;
                st->unk0 = SPAWNER_ACTOR;
                st->unk4 = i >> 1;
                st->unk5 = i & 1;
                D_807FBB44->unk80 = SPAWNER_ACTOR->unk80 + 50.0f;
                D_807FBB44->unk4->unk34 = 0.1f;
                D_807FBB44->unk4->unk38 = 0.1f;
                D_807FBB44->unk4->unk3C = 0.1f;
                D_807FBB44->unk60 |= 0x400;
            }
        }
        D_80036DC4 = 160000.0f;
        D_80036DC0 = 0;
        if (D_807FBB4C != NULL) {
            SPAWNER_PLAYER->unk154 = 0x77;
            SPAWNER_PLAYER->unk155 = 0;
        }
        SPAWNER_ACTOR->unk12A = 0x7D0;
        collisionCheckActorFloor(SPAWNER_ACTOR, SPAWNER_ACTOR->unk7C, SPAWNER_ACTOR->unk80, SPAWNER_ACTOR->unk84, &SPAWNER_ACTOR->unkA4);
        SPAWNER_ACTOR->unk154 = 2;
        camStartPath(0, 3, 1);
    }
    switch (SPAWNER_ACTOR->unk154) {
    case 0:
        SPAWNER_PLAYER->unk7C = SPAWNER_ACTOR->unk7C;
        SPAWNER_PLAYER->unk80 = SPAWNER_ACTOR->unk80;
        SPAWNER_PLAYER->unk84 = SPAWNER_ACTOR->unk84;
        if (D_80035B38 == -1) {
            D_80035B38 = SPAWNER_PLAYER->unk144;
        }
        SPAWNER_PLAYER->unk60 &= ~4;
        SPAWNER_PLAYER->unk144 = 1;
        if (D_807FBDC4 != 0) {
            sp5C = D_80035B44[D_80036DC0];
            SPAWNER_ACTOR->unk146 = 0;
            for (i = 4; D_80036DC0 < i; i--) {
                func_8068A764(D_807FBB40, D_80035B58[D_80035B44[i]]);
            }
            D_80036DC0++;
            sp5C = D_80035B4C[sp5C];
            func_806C8E58(sp5C);
            func_806F09F0(D_807FBB4C, sp5C);
            SPAWNER_PLAYER->unk154 = 0xC;
            SPAWNER_PLAYER->unk155 = 0;
            func_8067AAB8(D_807FBB40, D_807FBB4C, 0, 180.0f, 0x46);
            SPAWNER_ACTOR->unk154 = 1;
            SPAWNER_PLAYER->unk144 = D_80035B38;
        }
        break;
    case 1:
        SPAWNER_PLAYER->unk60 |= 4;
        dx = SPAWNER_PLAYER->unk7C - SPAWNER_ACTOR->unk7C;
        dz = SPAWNER_PLAYER->unk84 - SPAWNER_ACTOR->unk84;
        if (dx > 700.0 || dx < -700.0 || dz > 700.0 || dz < -700.0) {
            if (D_80036DC0 < 5) {
                SPAWNER_ACTOR->unk154 = 0;
                camStartPath(0, 2, 1);
            } else {
                func_805FF378(0x2A, 2);
                SPAWNER_ACTOR->unk154 = 3;
            }
        }
        break;
    case 2:
        s->unkE--;
        if (s->unkE < 0) {
            SPAWNER_ACTOR->unk154 = 0;
            func_806C8E58(4);
            func_806F09F0(D_807FBB4C, 4);
            s->unk13 = 1;
        }
        break;
    case 3:
        break;
    }
    SPAWNER_ACTOR->unkE6 += 0x32;
    SPAWNER_ACTOR->unkE6 &= 0xFFF;
    SPAWNER_ACTOR->unk80 = func_80612794(SPAWNER_ACTOR->unkE6) * 5.0 + s->unk0;
    if (SPAWNER_PLAYER->unk154 == 0x45 && SPAWNER_PLAYER->unk155 >= 2 && D_80036DC4 < 10000.0) {
        sp6A = 1;
    }
    sp69 = 0;
    s->unk4 += s->unk8;
    dx = 1.0f;
    if (s->unk4 > dx) {
        s->unk4 = dx;
        sp69 = 1;
    }
    if (s->unk4 < (f32)0) {
        s->unk4 = (f32)0;
        sp69 = -1;
    }
    if (sp69 != 0 && camIsCutsceneActive() == 0) {
        s->unk10++;
    }
    s->unk17 = 0;
    sp6B = s->unk13;
    switch (s->unk13) {
    case 0:
        i = 5;
        if (s->unk12 == 2) {
            j = 0xC;
            s->unk8 = -0.2f;
        } else {
            i = 0x3C;
            j = 4;
            s->unk8 = -0.1f;
        }
        if (i < s->unk10) {
            s->unk15++;
            if (s->unk15 < j) {
                s->unk13 = 1;
                sfxPlayOnFreeSlot(0x37D, 0x7D00, 0x427C0000, 0x3F800000, 0, 0);
                if (s->unk12 == 2) {
                    sfxPlayOnFreeSlot(0x381, 0x7D00, 0x427C0000, 0x3F800000, 0, 0);
                } else {
                    sfxPlayOnFreeSlot(0x37F, 0x7D00, 0x427C0000, 0x3F800000, 0, 0);
                }
            } else {
                s->unk13 = 2;
                s->unk15 = 0;
            }
        }
        if (sp69 != 0 && D_80035B40 == 0) {
            sp68 = 1;
            D_80035B2C = 0;
        }
        break;
    case 1:
        switch (s->unk12) {
        case 2:
            i = 0xA;
            s->unk8 = 0.2f;
            break;
        case 3:
            i = 0x3C;
            s->unk8 = 0.1f;
            break;
        default:
            i = 0xB4;
            s->unk8 = 0.1f;
            break;
        }
        if (sp69 == 1) {
            sp67 = 1;
            if (i < s->unk10) {
                s->unk13 = 0;
                s->unk15++;
                sfxPlayOnFreeSlot(0x17D, 0x3E80, 0x427C0000, 0x3F800000, 0, 0);
            }
            if (sp6A != 0) {
                sfxPlayOnFreeSlot(0x97, 0x7D00, 0x427C0000, 0x3F800000, 0, 0);
                s->unk16++;
                s->unk15 = 0;
                s->unk13 = 2;
                if (s->unk16 == 3) {
                    sfxPlayOnFreeSlot(0x385, 0x7D00, 0x427C0000, 0x3F800000, 0, 0);
                    s->unk16 = 0;
                    camPausePath();
                    s->unk13 = 4;
                } else {
                    sfxPlayOnFreeSlot(0x38E, 0x7D00, 0x427C0000, 0x3F800000, 0, 0);
                    sfxPlayOnFreeSlot(0x383, 0x7D00, 0x427C0000, 0x3F800000, 0, 0);
                }
            }
        }
        break;
    case 2:
        s->unk8 = -0.1f;
        if (s->unk10 >= 0x5B) {
            s->unk15++;
            if (s->unk15 < 3) {
                s->unk13 = 3;
                sfxPlayOnFreeSlot(0x37D, 0x7D00, 0x427C0000, 0x3F800000, 0, 0);
                sfxPlayOnFreeSlot(0x380, 0x7D00, 0x427C0000, 0x3F800000, 0, 0);
            } else {
                s->unk13 = 0;
                s->unk15 = 0;
            }
        }
        if (sp69 != 0 && D_80035B40 == 0) {
            sp68 = 1;
        }
        break;
    case 3:
        s->unk8 = 0.1f;
        if (s->unk10 >= 0x1F) {
            s->unk13 = 2;
            sfxPlayOnFreeSlot(0x17D, 0x3E80, 0x427C0000, 0x3F800000, 0, 0);
        }
        if (sp69 != 0) {
            s->unk17 = 1;
        }
        break;
    case 4:
        D_80035B3C += 1.0;
        if (D_80035B3C > 24.0) {
            D_80035B3C = 24.0f;
            s->unk10++;
            D_80035B2C = func_80612794(s->unk10 << 5) * 200.0f;
            if (s->unk10 == 0x3F) {
                D_80035B3C = 0.0f;
                D_80035B2C = 0;
                D_80035B28 = D_80035B30[D_80035B34];
                D_80035B34 += 1;
                s->unk13 = 5;
            }
        }
        break;
    case 5:
        s->unk10++;
        if (s->unk10 >= 0x3D) {
            s->unk8 = -0.1f;
            camResumePath();
            s->unk13 = 0;
            s->unk12++;
            if (s->unk12 == 1) {
                func_80724994(1, 7, 0, 0, 0);
            }
            if (s->unk12 == 3) {
                s->unk13 = 7;
            }
        }
        break;
    case 6:
        s->unk8 = -0.1f;
        if (sp69 == -1) {
            sp67 = 1;
            if (D_80035B70 < s->unk10) {
                sfxPlayOnFreeSlot(0x17D, 0x3E80, 0x427C0000, 0x3F800000, 0, 0);
                j = D_80035B70 + 1;
                s->unk10 = 0;
                if (j >= 0x10) {
                    j += 1;
                }
                D_80035B70 = j;
                if (j >= 0x1A) {
                    j = randomLcgNext();
                    s->unk13 = 1;
                    s->unk15++;
                    D_80035B70 = (j & 3) + 4;
                    sfxPlayOnFreeSlot(0x37F, 0x7D00, 0x427C0000, 0x3F800000, 0, 0);
                    sfxPlayOnFreeSlot(0x381, 0x7D00, 0x427C0000, 0x3F800000, 0, 0);
                }
                sp68 = 1;
            }
            D_80035B68 = 0x1E;
        }
        break;
    case 7:
        s->unk10++;
        s->unk8 = -0.1f;
        if (s->unk10 >= 0x10) {
            for (j = 0; j < 4; j++) {
                actorDespawn(actorListFindActorById(j));
            }
            SPAWNER_ACTOR->unk60 &= ~0x8000;
            SPAWNER_ACTOR->unk128 = 0;
            camStartPath(0, 4, 1);
            s->unk13 = 8;
        }
        break;
    case 8:
        s->unk8 = -0.1f;
        if (D_807FBDC4 != 0) {
            sfxAllocateChannel(0x35, 0x3F800000);
            bossSpawnParticleRing(0x13D, SPAWNER_ACTOR->unk7C, SPAWNER_ACTOR->unk80 + 200.0f, SPAWNER_ACTOR->unk84 + 40.0f, 0x800, 1);
            s->unk13 = 9;
        }
        break;
    case 9:
        break;
    }
    if (s->unk12 == 3 && s->unk13 == 0) {
        if (s->unk15 < 2) {
            s->unk13 = 6;
        } else {
            s->unk15 = 0x14;
        }
    }
    if (sp6B != s->unk13) {
        s->unk10 = 0;
    }
    if (sp68 != 0) {
        if (s->unk12 == 2 || s->unk12 == 3) {
            s->unk14++;
        } else {
            s->unk14 += (s32)(randomFloat() * 2.99f) + 1;
        }
        if (s->unk14 >= 4) {
            s->unk14 -= 4;
        }
    }
    i = D_80035B68 + 1; // FAKE: i as temp lets the increment forward across the sp67 branch (D_80035B68++ reloads)
    D_80035B68 = i;
    if (sp67 != 0) {
        sp5C = (i & 0x1F) - 0x10;
        i = sp5C;
        k = s->unk14;
        if (sp5C < 0) {
            i = -sp5C;
        }
        if (i >= 0x10) {
            i = 0xF;
        }
        sp5C = (i << 4) & 0xFF;
        lx = (f32)((f64)D_80035B00[k] * 0.33 + (f64)SPAWNER_ACTOR->unk7C);
        lz = (f32)((f64)D_80035B08[k] * 0.33 + (f64)SPAWNER_ACTOR->unk84);
        lightAdd(lx, 400.0f, lz, lx, 300.0f, lz, 200.0f, 0, sp5C, sp5C, sp5C);
        if (s->unk12 == 1) {
            k = s->unk14 + 2;
            if (k >= 4) {
                k -= 4;
            }
            lx = (f32)((f64)D_80035B00[k] * 0.33 + (f64)SPAWNER_ACTOR->unk7C);
            lz = (f32)((f64)D_80035B08[k] * 0.33 + (f64)SPAWNER_ACTOR->unk84);
            lightAdd(lx, 400.0f, lz, lx, 300.0f, lz, 200.0f, 0, sp5C, sp5C, sp5C);
        }
    }
    s->unkC--;
    if (s->unkC < 0) {
        s->unkC = (randomLcgNext() & 0x7F) + 0x5A;
        lightSetColor(0.5f, 0.5f, 0.5f, -1);
        func_8068B80C();
    }
    D_80035B40 = sp69;
    actorUpdateModelMatrix(D_807FBB40, 0);
}
