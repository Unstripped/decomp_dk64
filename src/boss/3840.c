#include "common.h"

typedef struct {
    char pad[0x20];
    u8 *unk20;
} BossB_Struct_DC98;

typedef struct {
    char pad[0x11];
    u8 unk11;
} BossB_Struct_DC9C;

extern BossB_Struct_DC98 *D_807FDC98;
extern BossB_Struct_DC9C *D_807FDC9C;

void heapFree(void *);
void *func_80610FE8(s32);

void func_80027840(u8 *arg0) {
    s16 i;
    u8 *dst;

    if (D_807FDC98->unk20 != NULL) {
        heapFree(D_807FDC98->unk20);
    }
    D_807FDC9C->unk11 = *arg0;
    D_807FDC98->unk20 = func_80610FE8(*arg0 * 2);
    dst = D_807FDC98->unk20;
    for (i = 0; i < *arg0; i++) {
        dst[0] = arg0[i + 1];
        dst[1] = 0;
        dst += 2;
    }
}

typedef struct {
    char pad0[8];
    f32 unk8;
    f32 unkC;
} BossB_Struct_800278F4;

void bossLerpCoords(BossB_Struct_800278F4 *arg0, f32 arg1, s16 arg2, s16 arg3) {
    arg0->unkC += ((f32)arg2 - arg0->unkC) * arg1;
    arg0->unk8 += ((f32)arg3 - arg0->unk8) * arg1;
}

typedef struct {
    char pad0[0x15];
    u8 unk15;
} BossB_Struct_80027950;

typedef struct {
    char pad0[0x25];
    u8 unk25;
} BossB_Struct_DC90;

extern BossB_Struct_DC90 *D_807FDC90;

s32 randomNonNegative(void);

void func_80027950(BossB_Struct_80027950 *arg0, u8 *arg1) {
    u8 prev = D_807FDC90->unk25;
    do {
        s32 rand = randomNonNegative() >> 15;
        u8 offset = arg0->unk15;
        D_807FDC90->unk25 = arg1[offset] + ((rand % 65536) % (arg1[offset + 1] - arg1[offset] + 1));
    } while (D_807FDC90->unk25 == prev);
    arg0->unk15 += 2;
}

typedef struct BossWaypoint {
    s16 x;
    s16 y;
    s16 z;
    s16 pad6[2];
} BossWaypoint;

typedef struct BossWaypointList {
    char pad0[0x14];
    BossWaypoint *points;
} BossWaypointList;

typedef struct BossActorPos {
    char pad0[0x7C];
    f32 x;
    f32 y;
    f32 z;
} BossActorPos;

typedef struct {
    char pad0[0x11C];
    s32 unk11C;
} BossB_Struct_807FBB40;

extern BossB_Struct_807FBB40 *D_807FBB40;
extern BossWaypointList *D_807FDCA0;

void bossPickFarthestWaypoint(void *arg0, u8 *arg1) {
    s16 i;
    s32 max_dist = 0;

    for (i = arg1[((BossB_Struct_80027950 *)arg0)->unk15]; i <= arg1[((BossB_Struct_80027950 *)arg0)->unk15 + 1]; i++) {
        u8 idx = D_807FDC98->unk20[i * 2];
        BossActorPos *actor = (BossActorPos *)D_807FBB40;
        BossWaypoint *pt = &D_807FDCA0->points[idx];
        f32 dz = actor->z - (f32)pt->z;
        f32 dx = actor->x - (f32)pt->x;
        f32 dy = actor->y - (f32)pt->y;
        s32 dist = (s32)sqrtf((dz * dz) + ((dx * dx) + (dy * dy)));

        if (dist > max_dist) {
            max_dist = dist;
            D_807FDC90->unk25 = i;
        }
    }
    ((BossB_Struct_80027950 *)arg0)->unk15 += 2;
}


typedef struct BossScriptState {
    char pad0[4];
    s16 unk4;
    char pad6[2];
    s16 unk8[5];
    u16 unk12;
    u8 unk14;
    u8 unk15;
    u8 unk16;
    u8 pad17;
    u8 unk18[8];
} BossScriptState;

typedef struct BossActor {
    char pad0[0x58];
    s32 unk58;
    char pad5C[4];
    s32 unk60;
    char pad64[6];
    u16 unk6A;
    char pad6C[0x10];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
    char pad88[0x94];
    struct BossActor *unk11C;
    char pad120[8];
    s16 unk128;
    char pad12A[0x2A];
    u8 unk154;
    u8 unk155;
    char pad156[0x22];
    BossScriptState *unk178;
    u8 *unk17C;
} BossActor;

typedef struct BossPlayerData {
    char pad0[0x104];
    s32 unk104;
    char pad108[0xE8];
    s32 unk1F0;
} BossPlayerData;

typedef struct BossPlayerActor {
    char pad0[0x7C];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
    char pad88[0xCC];
    u8 unk154;
    char pad155[0x1F];
    BossPlayerData *unk174;
} BossPlayerActor;

typedef struct BossWorkState {
    char pad0[4];
    BossPlayerActor *unk4;
    char pad8[2];
    s16 unkA;
    char padC[2];
    s16 unkE;
    char pad10[0xA];
    u16 unk1A;
    char pad1C[9];
    u8 unk25;
    char pad26[6];
    s16 unk2C;
} BossWorkState;

typedef struct BossConfig {
    char pad0[0xC];
    u8 unkC;
    u8 unkD;
} BossConfig;

extern BossPlayerActor *D_807FBB4C;
extern u8 D_807444EC;
extern u8 D_8076A0B1;
extern s8 D_8076A0B3;

void camEndPath(s32);
void currentActorClearFlag();
s32 currentActorTestClearFlag(void);
void actorSetTargetSpeed(void *, s32);
void func_8070D8C0(void *, s32, s32);
s32 func_8072D13C(s32, s32);
void actorMoveWithinZone(s32, f32, f32, s32, f32);
void actorScriptStart(void *, s32);
void bossPickFarthestWaypoint(void *, u8 *);

#define BA40 ((BossActor *)D_807FBB40)
#define DC90 ((BossWorkState *)D_807FDC90)
#define DC9C ((BossConfig *)D_807FDC9C)

u8 bossScriptStep(u8 *arg0, u16 arg1, f32 arg2) {
    BossPlayerData *sp34;
    BossScriptState *s0;
    u8 var_t1;
    u8 sp2E;
    u8 tmp;

    sp34 = D_807FBB4C->unk174;
    s0 = BA40->unk178;
    sp2E = 0;
    var_t1 = 1;
    switch (BA40->unk154) {
    case 0x54:
        var_t1 = 0;
        if (BA40->unk155 != 0) {
            if (currentActorTestClearFlag() != 0) {
                var_t1 = 1;
            }
        } else {
            currentActorClearFlag();
            BA40->unk155 = 1;
        }
        break;
    case 0x5F:
        camStartPath(D_807FBB40, arg0[s0->unk15++], 1);
        break;
    case 0x5E:
        if (D_807444EC == 1) {
            camEndPath(sp34->unk104);
        }
        D_8076A0B3 = 0;
        BA40->unk60 &= ~4;
        D_8076A0B1 |= 0x10;
        s0->unk4 = arg0[s0->unk15++] * 30;
        break;
    case 0x5D:
        actorSetTargetSpeed(D_807FBB40, arg0[s0->unk15++]);
        break;
    case 0x5C:
        {
            u8 *p = BA40->unk17C;
            *p = arg0[s0->unk15];
            s0->unk15++;
        }
        break;
    case 0x5A:
        func_8070D8C0(D_807FBB40, arg0[s0->unk15], arg0[s0->unk15 + 1]);
        s0->unk15 += 2;
        break;
    case 0x42:
block_16:
        actorMoveWithinZone(0x42, DC90->unkA, DC90->unkE, arg1, arg2);
        if (func_8072D13C(BA40->unk154, 0) == 0) {
            var_t1 = 0;
        }
        break;
    case 0x69:
        DC90->unk1A |= 0x20;
        break;
    case 0x58:
        BA40->unk60 |= 4;
        break;
    case 0x59:
        BA40->unk60 &= ~4;
        break;
    case 0x51:
        actorScriptStart(D_807FBB40, (arg0[s0->unk15] << 8) + arg0[s0->unk15 + 1]);
        s0->unk15 += 2;
        break;
    case 0x55:
        var_t1 = 0;
        if (BA40->unk155 == 0) {
            tmp = s0->unk15;
            s0->unk8[0] = (arg0[tmp] << 8) + arg0[tmp + 1];
            s0->unk15 = tmp + 2;
            BA40->unk155 = 1;
        } else {
            s0->unk8[0] -= 1;
            if (s0->unk8[0] == 0) {
                var_t1 = 1;
            }
        }
        break;
    case 0x23:
        var_t1 = 0;
        if (BA40->unk155 == 0) {
            tmp = s0->unk15;
            s0->unk8[0] = arg0[tmp];
            s0->unk15 = tmp + 1;
            BA40->unk155 = 1;
            actorSetTargetSpeed(D_807FBB40, DC9C->unkD);
        } else {
            actorMoveWithinZone(0x23, DC90->unk4->unk7C, DC90->unk4->unk84, arg1, arg2);
            s0->unk8[0] -= 1;
            if ((s0->unk8[0] == 0) || (sp34->unk1F0 & 0x80000)) {
                sp34->unk1F0 &= ~0x80000;
                var_t1 = 1;
                actorSetTargetSpeed(D_807FBB40, DC9C->unkC);
            }
        }
        break;
    case 0x52:
        if (!(BA40->unk6A & 1)) {
            var_t1 = 0;
        }
        break;
    case 0x53:
        if (BA40->unk155 == 0) {
            var_t1 = 0;
        }
        break;
    case 0x4F:
        s0->unk16 = s0->unk15;
        break;
    case 0x50:
        s0->unk15 = s0->unk16;
        break;
    case 0x66:
        if (DC90->unk1A & 8) {
            s0->unk15 = s0->unk16;
        }
        break;
    case 0x63:
        tmp = s0->unk15;
        if (s0->unk8[arg0[tmp]] != 0) {
            s0->unk8[arg0[tmp]] -= 1;
            var_t1 = 0;
        } else {
            s0->unk15 = tmp + 1;
        }
        break;
    case 0x62:
        s0->unk8[arg0[s0->unk15]] = arg0[s0->unk15 + 1];
        s0->unk15 += 2;
        sp2E = 1;
        break;
    case 0x64:
        s0->unk18[arg0[s0->unk15]] = arg0[s0->unk15 + 1];
        s0->unk15 += 2;
        sp2E = 1;
        break;
    case 0x68:
        DC90->unk1A &= 0xFFEF;
        sp2E = 1;
        break;
    case 0x65:
        DC90->unk2C = arg0[s0->unk15];
        s0->unk15++;
        sp2E = 1;
        break;
    case 0x67:
        func_80027950((BossB_Struct_80027950 *)s0, arg0);
        var_t1 = 0;
        BA40->unk154 = 0x42;
        BA40->unk155 = 0;
        goto block_16;
    case 0x4C:
        bossPickFarthestWaypoint(s0, arg0);
        var_t1 = 0;
        BA40->unk154 = 0x42;
        BA40->unk155 = 0;
        goto block_16;
    case 0x4B:
        DC90->unk25++;
        if (arg0[s0->unk15 + 1] < DC90->unk25) {
            DC90->unk25 = arg0[s0->unk15];
        }
        s0->unk15 += 2;
        var_t1 = 0;
        BA40->unk154 = 0x42;
        BA40->unk155 = 0;
        goto block_16;
    case 0x41:
        DC90->unk25 = arg0[s0->unk15];
        s0->unk15++;
        var_t1 = 0;
        BA40->unk154 = 0x42;
        BA40->unk155 = 0;
        goto block_16;
    case 0x49:
    case 0x4A:
        var_t1 = 0;
        switch (BA40->unk155) {
        case 0:
            BA40->unk128 -= 0xA;
            if (BA40->unk128 < 0) {
                BA40->unk128 = 0;
                BA40->unk155++;
            }
            break;
        case 1:
            if (BA40->unk154 == 0x49) {
                DC90->unk25 = arg0[s0->unk15];
                s0->unk15++;
            } else {
                func_80027950((BossB_Struct_80027950 *)s0, arg0);
            }
            func_8072D13C(0x49, 0);
            BA40->unk7C = DC90->unkA;
            BA40->unk84 = DC90->unkE;
            BA40->unk155++;
            break;
        case 2:
            BA40->unk128 += 0xA;
            if (BA40->unk128 >= 0x100) {
                BA40->unk128 = 0xFF;
                var_t1 = 1;
            }
            break;
        }
        break;
    case 0x6D:
        break;
    default:
        var_t1 = 0;
        break;
    }
    if (var_t1 != 0) {
        BA40->unk154 = arg0[s0->unk15];
        s0->unk15++;
        BA40->unk155 = 0;
    }
    return sp2E;
}


void func_805FF8F8(void);

void func_80028458(void) {
    func_805FF8F8();
}

typedef struct {
    char pad[0x7C];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
    char pad88[0x15E - 0x88];
    u8 unk15E;
} Boss3C_Struct_8478;

void sfxAllocateChannel(s32, f32);
void actorSpawnNodeEntryScaled(s32, f32, f32, f32, s32, s32, s32, s32);
void func_80714950(void *);
void func_8071498C(void *);
void func_807149B8(s32);
void func_807149FC(s32);
void func_80714CC0(s32, f32, f32, f32, f32);
s32 flagGet(s16, s32);
void effectWispHomeUpdate(void);

extern s32 D_8074E880[];
extern Boss3C_Struct_8478 *D_807FDC94;

void bossSpawnParticleRing(arg0, arg1, arg2, arg3, arg4, arg5)
u16 arg0;
s16 arg1;
s16 arg2;
s16 arg3;
s16 arg4;
u8 arg5;
{
    s16 s0;

    sfxAllocateChannel(0x36, 1.0f);
    if (flagGet((s16)arg0, 0) != 0) {
        func_80028458();
        return;
    }
    for (s0 = 0; s0 < 6; s0++) {
        func_8071498C(effectWispHomeUpdate);
        func_807149FC(-1);
        func_807149B8(1);
        func_80714950(D_807FDC94);
        func_80714CC0(D_8074E880[((randomNonNegative() >> 15) % 1000) % 3], 1.8f, D_807FDC94->unk7C, D_807FDC94->unk80 + (f32)D_807FDC94->unk15E, D_807FDC94->unk84);
    }
    actorSpawnNodeEntryScaled(0x48, (f32)arg1, (f32)arg2, (f32)arg3, (s32)arg4, (s32)arg5, (s16)arg0, 0);
}

void func_806A2A10(s32, s32, s32);
void actorSetStateTwo(s32);

void func_80028680(void) {
    func_806A2A10(-0x7F83, 0xD2, 0xB4);
    actorSetStateTwo(D_807FBB40->unk11C);
}

#define Boss2C_WRITE_GFX(pkt, _w0, _w1) { Gfx *_g = (Gfx *)(pkt); _g->words.w0 = (_w0); _g->words.w1 = (_w1); }

typedef float Boss2C_MtxF[4][4];

typedef struct {
    char pad0[0x276];
    s16 unk276;
} Boss2C_Struct_807FC924;

extern Boss2C_Struct_807FC924 *D_807FC924;
extern u8 D_80750AD4;
extern Gfx D_1000118;

void heapFreeDeferred(void *);
void *func_8070068C(Gfx *);
void textDrawStringVtx(void *, s32, s32, s32, char *, s32);

void bossDrawRoundText(Gfx *arg0, s32 arg1) {
    Boss2C_MtxF sp90;
    Boss2C_MtxF sp50;
    Mtx *sp4C;
    char sp3C[16];

    sp4C = func_80610FE8(sizeof(Mtx));
    heapFreeDeferred(sp4C);
    guScaleF(sp90, 0.6f, 0.6f, 1.0f);
    guTranslateF(sp50, 100.0f, (f32)(D_807FC924->unk276 * 4 - 0x3C), 0.0f);
    guMtxCatF(sp90, sp50, sp90);
    guMtxF2L(sp90, sp4C);
    Boss2C_WRITE_GFX(arg0++, 0xDA380003, (u32)sp4C);
    _sprintf(sp3C, "ROUND %d", D_80750AD4);
    Boss2C_WRITE_GFX(arg0++, 0xDE000000, (u32)&D_1000118);
    Boss2C_WRITE_GFX(arg0++, 0xE7000000, 0);
    Boss2C_WRITE_GFX(arg0++, 0xFC119623, 0xFF2FFFFF);
    Boss2C_WRITE_GFX(arg0++, 0xFA000000, 0xFFFFFFFF);
    arg0 = func_8070068C(arg0);
    textDrawStringVtx(arg0, 1, 0, 0, sp3C, 0);
}

static void func_80028818(void) {}

void flagSet(s16, s32, s32);

void bossResetAudioChannels(void) {
    flagSet(0x51, 0, 2);
    flagSet(0x52, 0, 2);
    flagSet(0x53, 0, 2);
    flagSet(0x54, 0, 2);
}

typedef struct BossSoundState {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    u8 unkC;
    u8 unkD;
    s16 unkE;
    s16 unk10;
} BossSoundState;

extern BossPlayerActor *D_807FBB48;
extern s16 D_800359A0[];
extern s16 D_800359AC[];
extern s16 D_800359B8[];
extern s16 D_800359C4[];
extern u8 D_8071FE08[];
extern s32 D_8076D1F8;
extern u32 D_80767CC0;
extern s32 D_8076A0A8;

void slotQueueSetDisplayMode(s32, s32, s32);
void healthRefill(u8);
void sfxStopChannel(s32, s32);
void func_80712524(s32, s32);
void n_alSndpPlay(s32, s32, s32, s32, f32, s32, void *);
void n_alSndpPostEvent(s32, s32, s16);
void func_80724A20(void);
void actorSetStateOne(void *);
void actorSetStateThree(void *);
s32 func_8071441C(void);
f32 sfxGetChannelVolume(s32);
s32 func_805FCA64(void);
void renderCallbacksRegister(void *, void *, s32);
void func_80609140(s32, s32, f32, f32, s32, s32);


void bossRoundFrame(u8 *arg0) {
    BossScriptState *sp44;
    u8 sp43;
    s16 sp30;
    BossSoundState *s0;

    sp44 = BA40->unk178;
    sp43 = D_8076A0A8 - 0xCB;
    s0 = (BossSoundState *)BA40->unk17C;
    if (D_807FBB4C->unk80 < 30.0f) {
        D_807FBB4C->unk7C = 780.0f;
        D_807FBB4C->unk80 = 50.0f;
        D_807FBB4C->unk84 = 750.0f;
        func_80714CC0((s32)D_8071FE08, 1.0f, D_807FBB4C->unk7C, D_807FBB4C->unk80, D_807FBB4C->unk84);
    }
    if (!(BA40->unk60 & 0x10)) {
        slotQueueSetDisplayMode(5, 0, 1);
        slotQueueSetDisplayMode(2, 0, 1);
        BA40->unk60 &= 0xFFFDFFFF;
        if ((sp44->unk14 == 0) || (BA40->unk58 != 0x126)) {
            if (flagGet(0x5A, 2) == 0) {
                healthRefill(0);
            }
            D_80750AD4++;
            if (D_80750AD4 >= 0xD) {
                sfxStopChannel(0x2B, 0);
                healthRefill(0);
                flagSet(0x55, 0, 2);
                func_80712524(0xD7, 0);
                D_80750AD4 = 0;
                BA40->unk154 = 0x6A;
                BA40->unk155 = 0;
            }
        }
        n_alSndpPlay(D_8076D1F8, 0x1E6, 0, 0x40, 1.0f, 0x80, &s0->unk4);
        n_alSndpPlay(D_8076D1F8, 0x119, 0, 0x40, 1.0f, 0x80, &s0->unk8);
    }
    func_80724A20();
    switch (BA40->unk154) {
    case 0x37:
        if (BA40->unk155 == 0) {
            actorSetStateOne(BA40->unk11C);
        }
        break;
    case 0x6A:
        if (BA40->unk155 == 0) {
            actorScriptStart(D_807FBB40, 0);
            BA40->unk155++;
        }
        break;
    case 0x6C:
        sp44->unk12 |= 1;
        func_80028680();
        if ((sp44->unk14 != 0) && (BA40->unk58 == 0x126)) {
            actorSetStateThree(BA40->unk11C);
        }
        BA40->unk154 = arg0[sp44->unk15];
        sp44->unk15++;
        BA40->unk155 = 0;
        break;
    default:
        if ((BA40->unk11C != NULL) && (BA40->unk11C->unk154 == 5)) {
            bossResetAudioChannels();
            BA40->unk154 = 0x6A;
            BA40->unk155 = 0;
            camStartPath(D_807FBB40, D_800359C4[sp43], 1);
            flagSet(0x5A, 1, 2);
        }
        break;
    }
    if (!(BA40->unk60 & 0x10)) {
        if (func_8071441C() != 0) {
            flagSet(0x55, 0, 2);
        }
        if ((flagGet(0x5D, 2) == 0) || (flagGet(0x5C, 2) != 0)) {
            bossResetAudioChannels();
            D_80750AD4 = 1;
            if (flagGet(0x5D, 2) == 0) {
                camStartPath(D_807FBB40, 0x19, 1);
                flagSet(0x5D, 1, 2);
            } else {
                camStartPath(D_807FBB40, D_800359A0[0], 1);
            }
            flagSet(0x5C, 0, 2);
            flagSet(0x55, 1, 2);
        } else {
            sp30 = sp43 + 0x55;
            if (flagGet(sp30, 2) == 0) {
                camStartPath(D_807FBB40, D_800359A0[sp43], 1);
                flagSet(sp30, 1, 2);
            } else if (flagGet(0x5A, 2) != 0) {
                if (flagGet(0x5B, 2) != 0) {
                    camStartPath(D_807FBB40, D_800359AC[sp43], 1);
                    flagSet(0x5A, 0, 2);
                } else {
                    sfxStopChannel(0x2B, 0);
                    BA40->unk154 = 0x6A;
                    BA40->unk155 = 0;
                    flagSet(0x5B, 1, 2);
                    func_80712524(0xD7, 1);
                    D_80750AD4 -= 1;
                }
            } else {
                camStartPath(D_807FBB40, D_800359B8[sp43], 1);
            }
        }
    }
    if ((D_807FBB48->unk154 == 0x67) || (sfxGetChannelVolume(0xF) > 0.1)) {
        s0->unkE = 0x1D4C;
        if (s0->unk10 - 0x3E8 < 0x1D4C) {
            s0->unk10 = 0x1D4C;
        } else {
            s0->unk10 = s0->unk10 - 0x3E8;
        }
    } else {
        if (s0->unkE - 0x64 < 0x1F40) {
            s0->unkE = 0x1F40;
        } else {
            s0->unkE = s0->unkE - 0x64;
        }
        if (s0->unkE < s0->unk10 + 0x3E8) {
            s0->unk10 = s0->unkE;
        } else {
            s0->unk10 = s0->unk10 + 0x3E8;
        }
    }
    n_alSndpPostEvent(s0->unk4, 8, s0->unk10);
    n_alSndpPostEvent(s0->unk8, 8, s0->unk10);
    if (s0->unkD & 0x17) {
        s32 snd = 0x1E8;
        if ((D_80767CC0 - s0->unk0) >= 6U) {
            s0->unk0 = D_80767CC0;
            s0->unkC = 0;
            if (s0->unkD & 0x10) {
                snd = 0x42B;
            } else if (s0->unkD & 4) {
                snd = 0x1EA;
            } else if (s0->unkD & 2) {
                snd = 0x1E7;
            }
            func_80609140(snd, 0x58EF, 64.0f, 1.0f, 0x14, 0x80);
        }
        if (s0->unkE + 0x4650 >= 0x8000) {
            s0->unkE = 0x7FFF;
        } else {
            s0->unkE = s0->unkE + 0x4650;
        }
        s0->unkD &= 0xFFE0;
    }
    if (s0->unkD & 8) {
        if ((D_80767CC0 - s0->unk0) >= 6U) {
            if (s0->unkC == 0) {
                s0->unk0 = D_80767CC0;
            }
            s0->unkC++;
            switch (s0->unkC) {
            case 0x3E:
                s0->unkC = 0;
                s0->unkD &= 0xFFF7;
            case 1:
            case 0x10:
            case 0x1D:
            case 0x29:
            case 0x34:
                func_80609140(0x1E9, 0x58EF, 64.0f, 1.0f, 0, 0x80);
                break;
            }
        }
        if (s0->unkE + 0x4650 >= 0x8000) {
            s0->unkE = 0x7FFF;
        } else {
            s0->unkE = s0->unkE + 0x4650;
        }
    }
    if ((sp44->unk12 & 1) && (func_805FCA64() != 0)) {
        renderCallbacksRegister(bossDrawRoundText, D_807FBB40, 3);
    }
}


void actorSetNodeFlag(void *, s32);
void actorClearNodeFlag(void *, s32);

void func_800290D4(arg0)
u8 arg0;
{
    if (arg0) {
        actorSetNodeFlag(D_807FBB40, 2);
        actorSetNodeFlag(D_807FBB40, 3);
    } else {
        actorClearNodeFlag(D_807FBB40, 2);
        actorClearNodeFlag(D_807FBB40, 3);
    }
}

typedef struct {
    u8 unk0;
    u8 unk1;
    s16 unk2;
    u8 unk4;
    u8 unk5;
} BossB_Struct_800359D0;

extern BossB_Struct_800359D0 D_800359D0[];

s32 flagGet(s16, s32);

void bossUpdateStageState(s16 *arg0) {
    s16 i = 0;
    while (D_800359D0[i].unk0 != 0 && D_8076A0A8 != D_800359D0[i].unk0) {
        i++;
    }
    if (D_800359D0[i].unk0 != 0 && D_800359D0[i].unk4 == *arg0) {
        if (flagGet(D_800359D0[i].unk2, 2) != 0) {
            *arg0 = D_800359D0[i].unk5;
        }
    }
}

void bossPlayStageMusic(void) {
    s16 i = 0;
    while (D_800359D0[i].unk0 != 0 && D_8076A0A8 != D_800359D0[i].unk0) {
        i++;
    }
    if (D_800359D0[i].unk0 != 0) {
        flagSet(D_800359D0[i].unk2, 1, 2);
    }
}
