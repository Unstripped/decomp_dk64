#include "common.h"
#include "actor.h"

extern u8 D_807F7EF8;
extern s16 D_807F7EFA;
extern s16 D_807F7EFC;

void lightSetFlags(u8 arg0) {
    D_807F7EF8 = arg0;
}

void lightSetTargetId(s16 arg0) {
    D_807F7EFA = arg0;
}

void lightSetRadius(s16 arg0) {
    D_807F7EFC = arg0;
}

extern f32 *D_8076A0B4;
extern f32 *D_8076A0B8;
extern f32 *D_8076A0BC;

void lightGetColor(f32 *arg0, f32 *arg1, f32 *arg2, s16 arg3) {
    *arg0 = D_8076A0B4[arg3];
    *arg1 = D_8076A0B8[arg3];
    *arg2 = D_8076A0BC[arg3];
}

extern s32 gMapChunkCount;

void lightSetColor(f32 arg0, f32 arg1, f32 arg2, s16 arg3) {
    u8 count;
    s32 i;

    if (gMapChunkCount <= 0) {
        count = 1;
    } else {
        count = gMapChunkCount;
    }
    if (arg3 != -1) {
        if (arg3 < count) {
            D_8076A0B4[arg3] = (arg0 <= 1.0f) ? arg0 : 1.0f;
            D_8076A0B8[arg3] = (arg1 <= 1.0f) ? arg1 : 1.0f;
            D_8076A0BC[arg3] = (arg2 <= 1.0f) ? arg2 : 1.0f;
        }
    } else {
        for (i = 0; i < count; i++) {
            D_8076A0B4[i] = (arg0 <= 1.0f) ? arg0 : 1.0f;
            D_8076A0B8[i] = (arg1 <= 1.0f) ? arg1 : 1.0f;
            D_8076A0BC[i] = (arg2 <= 1.0f) ? arg2 : 1.0f;
        }
    }
}

extern f32 *D_8076A0C0;
extern f32 *D_8076A0C4;
extern f32 *D_8076A0C8;

void lightCopyTargetColors(s16 arg0) {
    u8 count;
    s32 i;

    if (gMapChunkCount <= 0) {
        count = 1;
    } else {
        count = gMapChunkCount;
    }

    if (arg0 != -1) {
        if (arg0 < count) {
            D_8076A0B4[arg0] = D_8076A0C0[arg0];
            D_8076A0B8[arg0] = D_8076A0C4[arg0];
            D_8076A0BC[arg0] = D_8076A0C8[arg0];
        }
    } else {
        for (i = 0; i < count; i++) {
            D_8076A0B4[i] = D_8076A0C0[i];
            D_8076A0B8[i] = D_8076A0C4[i];
            D_8076A0BC[i] = D_8076A0C8[i];
        }
    }
}

void lightSetTargetColor(f32 arg0, f32 arg1, f32 arg2, s16 arg3) {
    u8 count;
    u8 i;

    if (gMapChunkCount <= 0) {
        count = 1;
    } else {
        count = gMapChunkCount;
    }

    if (arg3 != -1) {
        if (arg0 <= 1.0f) {
            D_8076A0C0[arg3] = arg0;
        } else {
            D_8076A0C0[arg3] = 1.0f;
        }
        if (arg1 <= 1.0f) {
            D_8076A0C4[arg3] = arg1;
        } else {
            D_8076A0C4[arg3] = 1.0f;
        }
        if (arg2 <= 1.0f) {
            D_8076A0C8[arg3] = arg2;
        } else {
            D_8076A0C8[arg3] = 1.0f;
        }
    } else {
        for (i = 0; i < count; i++) {
            if (arg0 <= 1.0f) {
                D_8076A0C0[i] = arg0;
            } else {
                D_8076A0C0[i] = 1.0f;
            }
            if (arg1 <= 1.0f) {
                D_8076A0C4[i] = arg1;
            } else {
                D_8076A0C4[i] = 1.0f;
            }
            if (arg2 <= 1.0f) {
                D_8076A0C8[i] = arg2;
            } else {
                D_8076A0C8[i] = 1.0f;
            }
        }
    }
}

void lightLerpColors(f32 arg0, f32 arg1, f32 arg2, f32 arg3, s16 arg4) {
    u8 count;
    s32 i;

    if (gMapChunkCount <= 0) {
        count = 1;
    } else {
        count = gMapChunkCount;
    }

    if (arg4 != -1) {
        if (arg4 < count) {
            D_8076A0B4[arg4] = ((D_8076A0C0[arg4] - arg0) * arg3) + arg0;
            D_8076A0B8[arg4] = ((D_8076A0C4[arg4] - arg1) * arg3) + arg1;
            D_8076A0BC[arg4] = ((D_8076A0C8[arg4] - arg2) * arg3) + arg2;
        }
    } else {
        for (i = 0; i < count; i++) {
            D_8076A0B4[i] = ((D_8076A0C0[i] - arg0) * arg3) + arg0;
            D_8076A0B8[i] = ((D_8076A0C4[i] - arg1) * arg3) + arg1;
            D_8076A0BC[i] = ((D_8076A0C8[i] - arg2) * arg3) + arg2;
        }
    }
}

f32 cosApprox(f32);
extern s16 D_80748300;
extern f32 D_807F7ECC;
extern f32 D_807F7ED0;
extern f32 D_807F7ED4;
extern f32 D_807F7ED8;
extern f32 D_807F7EDC;
extern f32 D_807F7EE0;
extern f32 D_807F7EE4;
extern f32 D_807F7EE8;
extern s16 D_807F7EFE;

void lightInitGlobals(void) {
    D_807F7ECC = cosApprox(0.4363323152f);
    D_807F7ED0 = cosApprox(1.134464025f);
    D_807F7ED4 = 1.0f / (D_807F7ECC - D_807F7ED0);
    D_807F7ED8 = D_807F7ECC;
    D_807F7EDC = D_807F7ED0;
    D_807F7EE0 = D_807F7ED4;
    D_807F7EE4 = 25.0f;
    D_807F7EE8 = 65.0f;
    D_80748300 = 0;
    D_807F7EF8 = 0;
    D_807F7EFA = -1;
    D_807F7EFC = 700;
    D_807F7EFE = 600;
}

void lightClearCount(void) {
    D_80748300 = 0;
}

extern s16 D_807F7EC8;
void lightClearActiveCount(void) {
    D_807F7EC8 = 0;
}

void lightSetFovAngles(f32 arg0, f32 arg1) {
    D_807F7EE4 = arg0;
    D_807F7EE8 = arg1;
    D_807F7ED8 = cosApprox(arg0 * 0.017453292f);
    D_807F7EDC = cosApprox(arg1 * 0.017453292f);
    D_807F7EE0 = 1.0f / (D_807F7ED8 - D_807F7EDC);
}

void lightSetDistanceThreshold(s16 arg0) {
    D_807F7EFE = arg0;
}

typedef struct LightVolume {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 x;
    /* 0x1C */ f32 y;
    /* 0x20 */ f32 z;
    /* 0x24 */ f32 unk24;
    /* 0x28 */ f32 unk28;
    /* 0x2C */ f32 unk2C;
    /* 0x30 */ s16 unk30;
    /* 0x32 */ s16 unk32;
    /* 0x34 */ s16 unk34;
    /* 0x36 */ u8 unk36;
    /* 0x37 */ u8 unk37;
    /* 0x38 */ u8 unk38;
    /* 0x39 */ u8 unk39;
    /* 0x3A */ u8 unk3A;
    /* 0x3B */ u8 pad3B;
} LightVolume;

extern LightVolume D_807F7500[];

void lightAdd(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, u8 arg7, u8 arg8, u8 arg9, u8 arg10) {
    if (D_80748300 != 0x10) {
        D_807F7500[D_80748300].unk34 = D_807F7EFE;
        D_807F7500[D_80748300].unk3A = D_807F7EF8;
        D_807F7500[D_80748300].unk30 = D_807F7EFA;
        D_807F7500[D_80748300].unk32 = D_807F7EFC;
        D_807F7500[D_80748300].unk8 = D_807F7EE8;
        D_807F7500[D_80748300].unk0 = D_807F7EE4;
        D_807F7500[D_80748300].unkC = D_807F7EDC;
        D_807F7500[D_80748300].unk4 = D_807F7ED8;
        D_807F7500[D_80748300].unk39 = arg7;
        D_807F7500[D_80748300].x = arg0;
        D_807F7500[D_80748300].y = arg1;
        D_807F7500[D_80748300].unk10 = D_807F7EE0;
        D_807F7500[D_80748300].z = arg2;
        D_807F7500[D_80748300].unk24 = arg3;
        D_807F7500[D_80748300].unk28 = arg4;
        D_807F7500[D_80748300].unk2C = arg5;
        D_807F7500[D_80748300].unk14 = arg6;
        D_807F7500[D_80748300].unk36 = arg8;
        D_807F7500[D_80748300].unk37 = arg9;
        D_807F7500[D_80748300].unk38 = arg10;
        D_80748300++;
        D_807F7ED8 = D_807F7ECC;
        D_807F7EDC = D_807F7ED0;
        D_807F7EE0 = D_807F7ED4;
        D_807F7EE4 = 25.0f;
        D_807F7EE8 = 65.0f;
        D_807F7EF8 = 0;
        D_807F7EFA = -1;
        D_807F7EFC = 700;
        D_807F7EFE = 600;
    }
}

extern s32 D_80748304;
extern s32 D_80748308;
extern u8 gPlayerCount;
extern ActorEntry gActiveActors[];
extern u16 gActiveActorCount;
s32 lightCheckPlayerDistance(LightVolume *);


#pragma GLOBAL_ASM("asm/global/nonmatchings/5E2F0/lightApplyToActors.s")

typedef struct LightTrigger {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ s32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ f32 unk24;
    /* 0x28 */ f32 unk28;
    /* 0x2C */ f32 unk2C;
    /* 0x30 */ f32 unk30;
    /* 0x34 */ f32 unk34;
    /* 0x38 */ s16 unk38;
    /* 0x3A */ s16 unk3A;
    /* 0x3C */ s16 unk3C;
    /* 0x3E */ u8 unk3E;
    /* 0x3F */ u8 unk3F;
} LightTrigger;

extern LightTrigger D_807F78C0[];
extern LightTrigger D_807F7BC8[];
extern s16 D_807F7BC0;
void lightAddDedupEntry(s16);
s32 lightCheckVolumeBounds(LightVolume *, f32, f32, f32, s16, s16, s16, s16, s16, s16, s32);
s16 lightCollectVolumesInBounds(f32 arg0, f32 arg1, f32 arg2, s16 arg3, s16 arg4, s16 arg5, s16 arg6, s16 arg7, s16 arg8, s32 arg9, s8 *arg10) {
    f32 diff[6];
    f32 temp_fa0;
    f32 dist;
    f32 temp_ft4;
    f32 temp_ft5;
    f32 temp_fa1;
    s32 i;
    f32 three;
    s16 a3 = arg3;
    s16 a4 = arg4;
    s16 a5 = arg5;
    s16 a6 = arg6;

    *arg10 = 0;
    D_807F7BC0 = 0;
    three = 3;
    for (i = 0; i < D_80748300; i++) {
        if (lightCheckVolumeBounds(&D_807F7500[i], arg0, arg1, arg2, a3, a4, a5, a6, arg7, arg8, arg9)) {
            if (D_807F7BC0 < 12) {
                if (D_807F7500[i].unk3A & 1) {
                    *arg10 = 1;
                }
                D_807F78C0[D_807F7BC0].unk3F = i;
                D_807F78C0[D_807F7BC0].unk38 = D_807F7500[i].x * 3.0f;
                D_807F78C0[D_807F7BC0].unk3A = D_807F7500[i].y * 3.0f;
                D_807F78C0[D_807F7BC0].unk3C = D_807F7500[i].z * 3.0f;
                D_807F78C0[D_807F7BC0].unk2C = (f64)(u32)D_807F7500[i].unk36 / 255.0;
                D_807F78C0[D_807F7BC0].unk30 = (f64)(u32)D_807F7500[i].unk37 / 255.0;
                D_807F78C0[D_807F7BC0].unk34 = (f64)(u32)D_807F7500[i].unk38 / 255.0;
                D_807F78C0[D_807F7BC0].unk3E = D_807F7500[i].unk39;
                switch ((u32)D_807F7500[i].unk39) {
                case 1:
                    diff[0] = D_807F7500[i].unk24 - D_807F7500[i].x;
                    diff[1] = D_807F7500[i].unk28 - D_807F7500[i].y;
                    diff[2] = D_807F7500[i].unk2C - D_807F7500[i].z;
                    dist = sqrtf((diff[0] * diff[0] + diff[1] * diff[1]) + diff[2] * diff[2]);
                    if (dist == 0.0f) {
                        dist = 0.1f;
                    }
                    D_807F78C0[D_807F7BC0].unkC = diff[0] / dist;
                    D_807F78C0[D_807F7BC0].unk10 = diff[1] / dist;
                    D_807F78C0[D_807F7BC0].unk14 = diff[2] / dist;
                    D_807F78C0[D_807F7BC0].unk4 = D_807F7500[i].unk4;
                    D_807F78C0[D_807F7BC0].unk18 = 0x127690;
                    D_807F78C0[D_807F7BC0].unk0 = D_807F7500[i].unkC;
                    D_807F78C0[D_807F7BC0].unk8 = D_807F7500[i].unk10;
                    break;
                case 0:
                    if (D_807F7500[i].unk14 == 0.0f) {
                        D_807F7500[i].unk14 = 0.1f;
                    }
                    temp_fa0 = D_807F7500[i].unk14 * 3.0f;  // FAKE: separate local for dist*dist (own FP web, steers colours)
                    D_807F78C0[D_807F7BC0].unk18 = (s32)(temp_fa0 * temp_fa0);
                    dist = D_807F7500[i].unk14 * 3.0f;
                    temp_fa1 = (D_807F7500[i].unk14 / three) * 3.0f;
                    D_807F78C0[D_807F7BC0].unk1C = 1.0f / (dist - temp_fa1);
                    D_807F78C0[D_807F7BC0].unk20 = temp_fa1;
                    D_807F78C0[D_807F7BC0].unk28 = ((D_807F7500[i].unk14 * 1.3f) / three) * 3.0f;
                    temp_ft4 = D_807F7500[i].unk14 * 1.3f;  // FAKE: named copies of the repeated 1.3 products (own FP webs, steer colours)
                    temp_ft5 = ((D_807F7500[i].unk14 * 1.3f) / three) * 3.0f;
                    D_807F78C0[D_807F7BC0].unk24 = 1.0f / ((temp_ft4) * 3.0f - temp_ft5);
                    break;
                }
                lightAddDedupEntry(D_807F7BC0);
                D_807F7BC0++;
            }
        }
    }
    if (D_807F7BC0 > 0.0f) {}  // FAKE: steers FP temp colours (random search)
    if (arg10 && arg10) {}  // FAKE: deadsweep: arg10 priority above a3..a6 (s4)
    return D_807F7BC0;
}
void *memcpy(void *, const void *, unsigned int);

void lightAddDedupEntry(s16 arg0) {
    s32 i;
    u8 val;

    if (D_807F7EC8 != 12) {
        val = D_807F78C0[arg0].unk3F;
        for (i = 0; i < D_807F7EC8; i++) {
            if (val == D_807F7BC8[i].unk3F) {
                return;
            }
        }
        memcpy(&D_807F7BC8[D_807F7EC8++], &D_807F78C0[arg0], sizeof(LightTrigger));
    }
}

void frustumCalculateCornerRays(f32, f32, f32);
void frustumCornersTransformByInverse(Mtx *);
void frustumOrientPolyNormals(f32, f32, f32, void *, void *);
void planeFromTwoPoints(f32, f32, f32, f32, f32, f32);
s32 mapBspBoxInFrustum(s16, s16, s16, s16, s32, s32, f32, f32, f32, f32, void *);
extern u8 D_807F5E20[];
extern u8 D_807F5E68[];

s32 lightCheckVolumeBounds(LightVolume *arg0, f32 arg1, f32 arg2, f32 arg3, s16 arg4, s16 arg5, s16 arg6, s16 arg7, s16 arg8, s16 arg9, s32 arg10) {
    Mtx sp60;
    f32 dx, dy;

    if ((arg0->unk3A & 2) && (arg10 != arg0->unk30) && (arg4 != -0x8000)) {
        return 0;
    }

    dx = arg0->x - arg1;
    dy = arg0->y - arg2;
    if (sqrtf((dx * dx) + (dy * dy) + ((arg0->z - arg3) * (arg0->z - arg3))) < (f32)arg0->unk32) {
        if (arg4 == -0x8000) {
            return 1;
        }
        switch (arg0->unk39) {
        case 0:
            if ((arg0->x < (f32)arg4 - arg0->unk14) ||
                (arg0->y < (f32)arg5 - arg0->unk14) ||
                (arg0->z < (f32)arg6 - arg0->unk14) ||
                ((f32)arg7 + arg0->unk14 < arg0->x) ||
                ((f32)arg8 + arg0->unk14 < arg0->y) ||
                ((f32)arg9 + arg0->unk14 < arg0->z)) {
                return 0;
            }
            return 1;
        case 1:
            guLookAt(&sp60, arg0->x, arg0->y, arg0->z, (arg0->x == arg0->unk24) ? (arg0->unk24 + 0.2f) : arg0->unk24, arg0->unk28, arg0->unk2C, 0.0f, 1.0f, 0.0f);
            frustumCalculateCornerRays(arg0->unk8 * 2, 1.0f, (f32)arg0->unk34);
            frustumCornersTransformByInverse(&sp60);
            frustumOrientPolyNormals(arg0->x, arg0->y, arg0->z, &D_807F5E68, &D_807F5E20);
            planeFromTwoPoints(arg0->x, arg0->y, arg0->z, arg0->unk24, arg0->unk28, arg0->unk2C);
            return mapBspBoxInFrustum(arg4, arg5, arg6, arg7, arg8, arg9, arg0->x, arg0->y, arg0->z, (f32)arg0->unk34, &D_807F5E68);
        }
        return 0;
    }
    return 0;
}

typedef struct LightPlayer {
    u8 unk0;
    u8 pad1[0x20F];
    f32 x;
    f32 y;
    f32 z;
    u8 pad21C[0xD4];
} LightPlayer;


extern LightPlayer *gPlayerSlots;
extern u8 D_80750AB4;
#define SQ(x) ((x) * (x))

s32 lightCheckPlayerDistance(LightVolume *arg0) {
    s32 i;
    LightPlayer *player;

    for (i = 0; i < D_80750AB4; i++) {
        player = (LightPlayer *)((u8 *)gPlayerSlots + (i * sizeof(LightPlayer)));
        if (player->unk0 != 0) {
            if (sqrtf(SQ(arg0->z - player->z) + (SQ(arg0->x - player->x) + SQ(arg0->y - player->y))) < (f32)arg0->unk32) {
                return 1;
            }
        }
    }
    return 0;
}

s32 mapChunkIsInUse(s16);



#pragma GLOBAL_ASM("asm/global/nonmatchings/5E2F0/lightSampleColorAtPosition.s")
