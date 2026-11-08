#include "common.h"
#include "actor.h"

extern Actor *gCurrentActor;
extern Actor *gSpawnedActor;
extern Actor *D_807FBB48;
extern void *gPlayerSlots;
extern u8 gPlayerCount;
extern u8 gCurrentPlayerIndex;
extern Struct807FD580 *gActivePlayerState;
extern s16 D_807FD584;
extern s32 gCurrentMap;
extern u8 gPlayerCharacterId[];

void func_8068A764(Actor *, u8);
void func_8068A784(Actor *, u8);
void func_806F09F0(Actor *arg0, u16 arg1) {
    switch (arg1) {
    case 0xC5:
    case 3:
        func_8068A784(arg0, 0);
        func_8068A784(arg0, 1);
        func_8068A784(arg0, 2);
        break;
    case 0xC8:
    case 6:
        func_8068A764(arg0, 0);
        func_8068A784(arg0, 1);
        break;
    case 0xC6:
    case 4:
        func_8068A764(arg0, 0);
        func_8068A784(arg0, 1);
        break;
    case 0xC7:
    case 5:
        func_8068A764(arg0, 0);
        func_8068A784(arg0, 1);
        break;
    case 0xC4:
    case 2:
        func_8068A764(arg0, 0);
        func_8068A784(arg0, 1);
        break;
    case 7:
        func_8068A764(arg0, 1);
        func_8068A784(arg0, 0);
        break;
    }
}

s32 sfxPlayFromActorWithAltitudeCheck(Actor *, s16, u8, s16, u8);

void func_806F0B34(Actor *arg0) {
    switch (gPlayerCharacterId[gCurrentPlayerIndex]) {
    case 0:
        sfxPlayFromActorWithAltitudeCheck(arg0, 0x17C, 0xFF, 0x7F, 0x19);
        break;
    case 1:
        sfxPlayFromActorWithAltitudeCheck(arg0, 0x17C, 0xC8, 0xA0, 5);
        break;
    case 2:
        sfxPlayFromActorWithAltitudeCheck(arg0, 0x17C, 0xFF, 0x7F, 5);
        break;
    case 3:
        sfxPlayFromActorWithAltitudeCheck(arg0, 0x185, 0xFF, 0x7F, 0x19);
        break;
    default:
        sfxPlayFromActorWithAltitudeCheck(arg0, 0x18F, 0xFF, 0x7F, 0x19);
        break;
    }
}

typedef struct F5N2ActorExtra {
    u8 pad0[0x8C];
    u8 unk8C;
    u8 pad8D[0x117];
    u8 unk1A4;
} F5N2ActorExtra;

s32 controllerLookupStateByHash(void);

void func_806F0C18(Actor *arg0) {
    s32 pad;
    F5N2ActorExtra *extra;

    switch (controllerLookupStateByHash()) {
    case 1:
    case 2:
    case 3:
        func_8068A784(arg0, 0);
        func_8068A784(arg0, 1);
        break;
    case 0xC:
    case 0xD:
    case 0xE:
    case 0xF:
    case 0x10:
        func_8068A764(arg0, 0);
        func_8068A784(arg0, 1);
        break;
    case 0xDB:
        func_8068A764(arg0, 1);
        func_8068A784(arg0, 0);
        break;
    case 6:
    case 7:
    case 8:
        func_8068A764(arg0, 0);
        func_8068A784(arg0, 1);
        break;
    case 9:
    case 0xA:
    case 0xB:
        func_8068A764(arg0, 0);
        func_8068A784(arg0, 1);
        break;
    case 4:
    case 5:
        func_8068A764(arg0, 0);
        func_8068A784(arg0, 1);
        break;
    }
    if (arg0->unk5C & 1) {
        extra = arg0->unk174;
        if (extra->unk8C != 0) {
            func_806F0B34(arg0);
            extra->unk8C = 0;
        }
    }
}

extern u8 D_807FC952[];
s32 func_806C8DE0(u8);
s32 func_80714608(s32);
void func_806F5A48(u8, s32, Actor *, s32);

void func_806F0D68(Actor *arg0) {
    s32 pad;
    F5N2ActorExtra *extra;

    switch (controllerLookupStateByHash()) {
    case 1:
    case 2:
        func_8068A764(arg0, 0);
        func_8068A764(arg0, 1);
        break;
    case 0xC:
    case 0xD:
    case 0xE:
    case 0xF:
    case 0x10:
        func_8068A784(arg0, 0);
        func_8068A764(arg0, 1);
        break;
    case 0xDB:
        func_8068A784(arg0, 1);
        func_8068A764(arg0, 0);
        break;
    case 6:
    case 7:
        func_8068A784(arg0, 0);
        func_8068A764(arg0, 1);
        break;
    case 9:
    case 0xA:
        func_8068A784(arg0, 0);
        func_8068A764(arg0, 1);
        break;
    case 4:
        func_8068A784(arg0, 0);
        func_8068A764(arg0, 1);
        break;
    }
    if (arg0->unk5C & 1) {
        extra = arg0->unk174;
        if (extra->unk8C == 0) {
            switch (gPlayerCharacterId[gCurrentPlayerIndex]) {
            case 0:
                sfxPlayFromActorWithAltitudeCheck(arg0, 0x186, 0xFF, 0x64, 0x19);
                sfxPlayFromActorWithAltitudeCheck(arg0, 0x17C, 0xFF, 0x64, 0x19);
                break;
            case 1:
                sfxPlayFromActorWithAltitudeCheck(arg0, 0x17C, 0xC8, 0xBE, 5);
                break;
            case 2:
                sfxPlayFromActorWithAltitudeCheck(arg0, 0x186, 0xFF, 0x7F, 0x19);
                sfxPlayFromActorWithAltitudeCheck(arg0, 0x17C, 0xFF, 0xA0, 5);
                break;
            case 3:
                sfxPlayFromActorWithAltitudeCheck(arg0, 0x185, 0xFF, 0x7F, 0x19);
                break;
            default:
                sfxPlayFromActorWithAltitudeCheck(arg0, 0x18E, 0xFF, 0x7F, 0x19);
                break;
            }
            extra->unk8C = 1;
        }
        if (func_80714608(0) != 0) {
            D_807FC952[extra->unk1A4 * 0x306 + func_806C8DE0(extra->unk1A4) * 0x5E] = 1;
            func_806F5A48(extra->unk1A4, 0, arg0, 0x8F);
        }
    }
}

typedef struct F5N2ActorState {
    u8 pad0[0x1F0];
    s32 flags;
} F5N2ActorState;

void controllerAnimFreeStateAsset(void);
void func_806C8D20(Actor *);

void func_806F1048(Actor *arg0) {
    F5N2ActorState *state = arg0->unk174;

    switch (arg0->actorType) {
    case 4:
    case 0xC6:
        state->flags &= ~0x100;
    case 3:
    case 5:
    case 6:
    case 0xC5:
    case 0xC7:
    case 0xC8:
        if (!(state->flags & 0x40)) {
            controllerAnimFreeStateAsset();
        }
        break;
    }
    func_806C8D20(gCurrentActor);
}

typedef struct F5N3ActorState {
    u8 pad0[0x58];
    u32 state;
    u8 pad5C[0x88];
    s16 unkE4;
    u8 padE6[2];
    s16 unkE8;
} F5N3ActorState;

typedef struct F5N3ActorSub10E8 {
    u8 pad0[0x38];
    f32 unk38;
} F5N3ActorSub10E8;

void func_806F0C18(Actor *);
s32 actorSpawn(s32, s32);
void actorCopyPoseAndScale(Actor *, Actor *, f32);
void controllerAnimLoadStateAsset(Actor *, s32);

void func_806F10E8(Actor *arg0) {
    switch (((F5N3ActorState *) arg0)->state) {
        case 2:
        case 0xC4:
            func_806F0C18(arg0);
            actorSpawn(0xEF, 0xA6);
            actorCopyPoseAndScale(gSpawnedActor, arg0, ((F5N3ActorSub10E8 *) arg0->unk4)->unk38 * 1.25);
            ((F5N3ActorState *) gSpawnedActor)->unkE4 = ((F5N3ActorState *) arg0)->unkE4;
            ((F5N3ActorState *) gSpawnedActor)->unkE8 = ((F5N3ActorState *) arg0)->unkE8;
            gSpawnedActor->flags |= 0x40000000;
            break;
        case 3:
        case 0xC5:
            func_806F0C18(arg0);
            controllerAnimLoadStateAsset(arg0, 2);
            break;
        case 4:
        case 0xC6:
            func_806F0C18(arg0);
            controllerAnimLoadStateAsset(arg0, 7);
            break;
        case 5:
        case 0xC7:
            func_806F0C18(arg0);
            controllerAnimLoadStateAsset(arg0, 0xA);
            break;
        case 6:
        case 0xC8:
            func_806F0C18(arg0);
            controllerAnimLoadStateAsset(arg0, 0xD);
            break;
    }
}

typedef struct F5N3ActorExtra {
    u8 pad0[0x1F0];
    s32 flags;
} F5N3ActorExtra;

void sfxPlayAtPositionPooled(f32, f32, f32, s32, s32, s32, s32, s32, f32, s32);
void sfxAllocateChannel(s32, f32);
void sfxStopChannel(s32, s32);
extern s32 D_807FBB68;

void func_806F1250(Actor *arg0) {
    F5N3ActorExtra *extra = arg0->unk174;

    if (arg0->actorType == 6) {
        controllerAnimLoadStateAsset(arg0, 0x10);
        sfxPlayAtPositionPooled(arg0->x, arg0->y, arg0->z, 0x2E2, 0xFF, 0xA0, 0, 0x32, 0.0f, 0);
        if (!(D_807FBB68 & 2)) {
            sfxAllocateChannel(0x6C, 1.0f);
        }
    }
    extra->flags |= 0x40;
}

void func_806F12FC(Actor *arg0) {
    F5N3ActorExtra *extra = arg0->unk174;

    if (arg0->actorType == 6) {
        controllerAnimFreeStateAsset();
        sfxStopChannel(0x6C, 0);
    }
    extra->flags &= ~0x40;
}

void playerFireWeapon();

void func_806F1350(s32 arg0) {
    playerFireWeapon(0, 1);
}

void func_806F1378(s32 arg0) {}

typedef struct F5AActorSub4 {
    u8 pad0[0x88];
    s32 unk88;
} F5AActorSub4;

void scriptReadU32(f32 *);

void func_806F1380(Actor *arg0) {
    f32 temp;

    scriptReadU32(&temp);
    ((F5AActorSub4 *)arg0->unk4)->unk88 = (s32)(arg0->speedXZ - temp);
}

typedef struct F5APlayerState {
    u8 pad0[0x4C];
    s16 unk4C;
} F5APlayerState;

#define F5A_PS ((F5APlayerState *)gActivePlayerState)

void scriptReadU8(u8 *);
s32 playerSelectMoveTier(Actor *, f32, f32, s16, s16);

void func_806F13C8(Actor *arg0) {
    u8 temp;

    scriptReadU8(&temp);
    ((F5AActorSub4 *)arg0->unk4)->unk88 =
        playerSelectMoveTier(arg0, arg0->speedXZ, arg0->speedXZ, F5A_PS->unk4C, D_807FD584) - temp;
}

typedef struct F5APlayerCoefficient {
    f32 value;
    u8 pad4[0x30];
} F5APlayerCoefficient;

extern F5APlayerCoefficient D_807FD618[];
void playerResumeLocomotion(void);

void func_806F142C(void) {
    f32 value;

    playerResumeLocomotion();
    value = gCurrentActor->speedXZ;
    gCurrentActor->speedXZ =
        D_807FD618[gCurrentPlayerIndex].value * (value - (value / 2)) + (value / 2);
}

void func_806D0150(Actor *);

void func_806F149C(Actor *arg0) {
    func_806D0150(arg0);
}

typedef struct F5N3ActorMeta14BC {
    u8 pad0[4];
    f32 unk4;
    u8 pad8[0x1C];
    f32 unk24;
} F5N3ActorMeta14BC;

typedef struct F5N3ActorSub14BC {
    F5N3ActorMeta14BC *meta;
    u8 pad4[0x84];
    s32 unk88;
} F5N3ActorSub14BC;

typedef struct F5N3Actor14BC {
    u8 pad0[0x4];
    F5N3ActorSub14BC *unk4;
    u8 pad8[0x62];
    u16 unk6A;
    u8 pad6C[0x14];
    f32 unk80;
    u8 pad84[0x20];
    f32 unkA4;
    u8 padA8[4];
    f32 unkAC;
    u8 padB0[4];
    f32 unkB4;
    u8 padB8[8];
    f32 unkC0;
    f32 unkC4;
    f32 unkC8;
} F5N3Actor14BC;

s32 func_806F1668(f32, f32, f32, f32);
void scriptSetActorRampTarget(Actor *, f32, f32);

#define F5N3_A ((F5N3Actor14BC *) arg0)

void func_806F14BC(Actor *arg0) {
    f32 limit;
    u8 amount;
    f64 den;
    f32 base;
    f32 value;
    f32 high;
    f32 ratio;
    s32 count;

    scriptReadU32(&limit);
    scriptReadU8(&amount);
    base = F5N3_A->unk4->meta->unk4;
    F5N3_A->unk4->unk88 = 0;
    if ((F5N3_A->unk6A & 2) && ((F5N3_A->unkAC - F5N3_A->unkA4) > 12.0f)) {
        high = (F5N3_A->unkAC < F5N3_A->unkA4) ? F5N3_A->unkA4 : F5N3_A->unkAC;
        value = F5N3_A->unk80 - high;
        if (value < 0.0f) {
            value = 0.0f;
        }
    } else {
        value = F5N3_A->unkB4;
    }
    count = func_806F1668(value * 40.0f, F5N3_A->unkC0, F5N3_A->unkC8, F5N3_A->unkC4);
    if (count == 0) {
        F5N3_A->unk4->unk88 = 1;
        return;
    }
    ratio = ((f32)(u32)amount - base) / (f32)count;
    if (ratio < 0.0f) {
        ratio = 0.01f;
    }
    den = (F5N3_A->unk4->meta->unk24 < 0.01) ? 0.01 : F5N3_A->unk4->meta->unk24;
    ratio = ratio / den;
    if (limit < ratio) {
        ratio = limit;
    }
    scriptSetActorRampTarget(arg0, ratio, 0.0f);
}

extern f32 sqrtf(f32);

s32 func_806F1668(f32 arg0, f32 arg1, f32 arg2, f32 arg3) {
    f32 quot;
    f32 val;
    f32 res;

    if ((arg0 < 0.0f) || (0.0f < arg2) || (0.0f <= arg3)) {
        return 0;
    }
    quot = (arg2 - arg1) / arg3;
    val = arg0;
    val += ((arg1 + arg2) / 2) * quot;
    if (val > 0.0f) {
        res = quot - val / arg2;
    } else {
        res = (-sqrtf((arg1 * arg1) - (2 * arg3 * arg0)) - arg1) / arg3;
    }
    return (s32)(res + 0.5);
}

typedef struct F5N3PlayerState1768 {
    u8 pad0[0x8E];
    u8 unk8E;
    u8 pad8F[2];
    u8 unk91;
} F5N3PlayerState1768;

typedef struct F5N3TableEntry1768 {
    u8 unk0;
    u8 unk1;
    s16 unk2;
    s16 unk4;
    s16 unk6;
} F5N3TableEntry1768;

#define F5N3_PLAYER_1768 ((F5N3PlayerState1768 *) gActivePlayerState)

extern u16 D_80752F20[];

void func_806F1768(s32 arg0, F5N3TableEntry1768 *arg1, s32 *arg2) {
    s32 temp_v1;
    u16 temp_v0;
    temp_v0 = 7U;
    temp_v1 = F5N3_PLAYER_1768->unk8E - 0x14;
    if ((temp_v1 >= 0) && ((u32) temp_v1 < temp_v0)) {
        temp_v0 = D_80752F20[temp_v1];
        arg1[*arg2].unk0 = 0x7F;
        arg1[*arg2].unk1 = F5N3_PLAYER_1768->unk91 != 0 ? 9 : 8;
        arg1[*arg2].unk2 = 0;
        arg1[*arg2].unk4 = F5N3_PLAYER_1768->unk91 != 0 ? temp_v0 : -temp_v0;
        arg1[*arg2].unk6 = 0;
        *arg2 += 1;
    }
}

extern u16 D_80752F30[];

void func_806F1858(s32 arg0, F5N3TableEntry1768 *arg1, s32 *arg2) {
    s32 temp_v1;
    u16 temp_v0;
    temp_v0 = 4U;
    temp_v1 = F5N3_PLAYER_1768->unk8E - 0x14;
    if ((temp_v1 >= 0) && ((u32) temp_v1 < temp_v0)) {
        temp_v0 = D_80752F30[temp_v1];
        arg1[*arg2].unk0 = 0x7F;
        arg1[*arg2].unk1 = 4;
        arg1[*arg2].unk2 = 0;
        arg1[*arg2].unk4 = temp_v0;
        arg1[*arg2].unk6 = 0;
        *arg2 += 1;
    }
}

typedef struct {
    u8 unk0;
    u8 unk1;
    s16 unk2;
    s16 unk4;
    s16 unk6;
} F5BSlot;


typedef struct {
    u8 pad0[0x8E];
    u8 unk8E;
} F5BPlayerState;

typedef struct {
    u8 pad0[0x60];
    s32 unk60;
    u8 pad64[0x54];
    f32 unkB8;
    u8 padBC[0x2A];
    s16 unkE6;
    u8 padE8[6];
    s16 unkEE;
} F5BActor;

typedef struct {
    u8 pad0[0xC];
    f32 unkC;
} F5BAccel;

#define F5B_PLAYER_STATE ((F5BPlayerState *)gActivePlayerState)

extern u16 D_80752F38[];
extern u16 D_80752F40[];
extern f32 func_80612790(s16);

void func_806F18F4(s32 arg0, F5BSlot *arg1, s32 *arg2) {
    s32 tableIndex;
    u16 angle;
    s32 zero;

    angle = 0x16;
    tableIndex = F5B_PLAYER_STATE->unk8E - angle;
    if ((tableIndex >= 0) && ((u32)tableIndex < 4U)) {
        angle = D_80752F38[tableIndex];
        arg1[*arg2].unk0 = 0x7F;
        arg1[*arg2].unk1 = 1;
        if (1) {
            zero = 0;
            arg1[*arg2].unk2 = zero;
        }
        arg1[*arg2].unk4 = angle;
        arg1[*arg2].unk6 = zero;
        *arg2 += 1;
    }
}

void func_806F1990(s32 arg0, F5BSlot *arg1, s32 *arg2) {
    u16 temp_v0;

    temp_v0 = D_80752F40[F5B_PLAYER_STATE->unk8E];
    arg1[*arg2].unk0 = 0x7F;
    arg1[*arg2].unk1 = 1;
    arg1[*arg2].unk2 = temp_v0;
    arg1[*arg2].unk4 = temp_v0;
    arg1[*arg2].unk6 = 0;
    *arg2 += 1;
}

typedef struct {
    f32 unk0;
    f32 unk4;
    f32 unk8;
} F5N1Spring;

f32 cosApprox(f32);
f32 sinApprox(f32);

void func_806F1A18(f32 arg0, f32 arg1, F5N1Spring *arg2, f32 *arg3) {
    s32 pad[1];
    f32 sp20;

    sp20 = cosApprox(arg2->unk4);
    arg2->unk8 += arg0 * cosApprox(*arg3) * sp20;
    arg2->unk8 -= arg1 * sinApprox(arg2->unk4);
    arg2->unk8 = (f32)((f64)arg2->unk8 * 0.93);
    arg2->unk4 = (f32)(arg2->unk4 + arg2->unk8);
    *arg3 += arg2->unk4 + arg2->unk0;
}

f32 func_806F1AE0(F5BActor *arg0, F5BAccel *arg1, f32 arg2) {
    f32 temp_fa0;
    f32 temp_fv1;

    temp_fv1 = func_80612790((s16)(arg0->unkE6 - arg0->unkEE)) * (arg0->unkB8 * 0.0076923077f);
    temp_fa0 = temp_fv1 - arg1->unkC;
    arg1->unkC = temp_fv1;
    return (temp_fa0 + temp_fv1) * arg2;
}

typedef struct {
    u8 pad0[0x14];
    u8 unk14;
    u8 pad15[3];
    s32 unk18;
} F5N1Predicate;

s32 func_806F1B58(F5BActor *arg0, F5N1Predicate *arg1, s32 arg2) {
    s32 ret = (arg0->unk60 & 0x100) != 0;

    if (ret != 0) {
        ret = arg1->unk14 == 0;
        if (ret != 0) {
            return arg2 == arg1->unk18;
        }
    } // FAKE: no final return keeps ret in $v0 (same idiom as func_80026250)
}

f32 mathAngleRadDeltaTurns(f32 *arg0, f32 arg1) {
    f32 diff;

    diff = arg1 - *arg0;
    *arg0 = arg1;
    if (diff > 3.1415927f) {
        diff = 6.2831855f - diff;
    } else if (diff < -3.1415927f) {
        diff = -(6.2831855f + diff);
    }
    diff *= 0.15915494f;
    return diff;
}

typedef struct {
    F5N1Spring unk0;
    F5N1Spring unkC;
} F56APair;

typedef struct {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    u8 padC[4];
    f32 unk10;
    u8 unk14;
    u8 pad15[3];
    s32 unk18;
    F56APair unk1C[8];
    u8 padDC[0x60];
} F56AState;

typedef struct {
    u8 pad0[0x10];
    s16 unk10;
} F56AIdxMeta;

typedef struct {
    F56AIdxMeta *unk0;
} F56AIdxSub;

typedef struct {
    u8 pad0[0x60];
    u32 unk60;
    u8 pad64[0x114];
    F56AState *unk178;
} F56AActor;

void actorGetNodePos(Actor *, s32, f32 *, f32 *, f32 *);
f32 mathAtan2(f32, f32);

void func_806F1C04(Actor *arg0, F5BSlot *arg1, s32 *arg2) {
    F56AState *state = ((F56AActor *) arg0)->unk178;
    F56APair *pair;
    s32 pad5[1];
    f32 posB[3];
    f32 posA[3];
    s32 value = -0x80;
    f32 accel0 = 0.0f;
    f32 accel1 = 0.0f;
    f32 angle;
    s32 active;
    s32 index;
    s32 i;
    f32 ret;
    f32 sp80;
    f32 sp7C;
    s32 kind;
    s32 pad4[2];

    pair = state->unk1C;
    active = func_806F1B58((F5BActor *) arg0, (F5N1Predicate *) state, 2);
    sp80 = 0.0f;
    sp7C = 0.0f;
    index = *arg2;
    kind = 0x14;
    actorGetNodePos(arg0, 0xD, &posA[0], &posA[1], &posA[2]);
    actorGetNodePos(arg0, 0xE, &posB[0], &posB[1], &posB[2]);
    angle = mathAtan2(posA[2] - posB[2], posA[0] - posB[0]);
    if (active == 0) {
        state->unk0 = angle;
        state->unk4 = posA[1];
        if ((state->unk14 != 0) && (((F56AActor *) arg0)->unk60 & 0x100) && (state->unk18 == 2)) {
            state->unk14 -= 1;
        }
    } else {
        ret = mathAngleRadDeltaTurns(&state->unk0, angle);
        state->unk10 = state->unk10 + ((-128.0f - state->unk10) * 0.3);
        value = (s8) (s32) state->unk10;
        accel1 = 0.4f * ret;
        accel0 = func_806F1AE0((F5BActor *) arg0, (F5BAccel *) state, 0.02f);
    }
    for (i = 0; i != 4; i++) {
        if (active != 0) {
            func_806F1A18(accel0, 0.06f, &pair->unk0, &sp80);
            func_806F1A18(accel1, 0.06f, &pair->unkC, &sp7C);
        }
        arg1[index].unk0 = value;
        arg1[index].unk1 = kind;
        arg1[index].unk2 = (s32) ((pair->unk0.unk4 + pair->unk0.unk0) * 10430.218905280077);
        arg1[index].unk4 = 0;
        arg1[index].unk6 = (s32) ((pair->unkC.unk4 + pair->unkC.unk0) * 10430.218905280077);
        pair++;
        index++;
        kind++;
    }
    *arg2 = index;
}

extern s8 D_80752CBF[];

void func_806F1EB0(Actor *arg0, F5BSlot *arg1, s32 *arg2) {
    F56AState *state = ((F56AActor *) arg0)->unk178;
    F56APair *pair;
    F5BSlot *slot;
    f32 spE0;
    s32 index;
    s32 kind;
    s32 value;
    s32 i;
    s32 k;
    f32 spC8;
    f32 spC4;
    f32 ret;
    f32 angle;
    f32 pos[2][3];
    f32 y;
    f32 newvel;
    f32 delta;
    F56AState *cur;
    s32 active;
    f32 boost;
    f32 accel0;
    f32 accel1;

    index = *arg2;
    ret = 0;
    kind = 0x16;
    cur = state;
    active = func_806F1B58((F5BActor *) arg0, (F5N1Predicate *) state, 5);
    value = -0x80;
    actorGetNodePos(arg0, 0xD, &pos[0][0], &pos[0][1], &pos[0][2]);
    actorGetNodePos(arg0, 0xE, &pos[1][0], &pos[1][1], &pos[1][2]);
    angle = mathAtan2(pos[0][2] - pos[1][2], pos[0][0] - pos[1][0]);
    if (active == 0) {
        for (k = 0; k != 2; k++) {
            cur[k].unk0 = angle;
            cur[k].unk4 = pos[k][1];
        }
        if (k == 0) {}  // FAKE: dead use of k after loop 1 (index in s7, arg1 in s2)
        if ((state->unk14 != 0) && (((F56AActor *) arg0)->unk60 & 0x100) && (state->unk18 == 5)) {
            state->unk14 -= 1;
        }
    } else {
        s16 idx = ((F56AIdxSub *) arg0->unk4)->unk0->unk10;

        if (idx >= 0) {
            newvel = D_80752CBF[idx];
        } else {
            newvel = -128.0f;
        }
        state->unk10 = state->unk10 + ((newvel - state->unk10) * 0.3);
        value = (s8) (s32) state->unk10;
        ret = mathAngleRadDeltaTurns(&state->unk0, angle);
        spE0 = func_806F1AE0((F5BActor *) arg0, (F5BAccel *) state, 0.02f);
    }
    slot = arg1; slot += index; k = 0; do { // LAYOUT: one source line lets as1 schedule the loop preheader
        accel1 = 0.0f;
        accel0 = 0.0f;
        spC8 = 0.0f;
        spC4 = 0.0f;
        pair = cur->unk1C;
        if (active != 0) {
            y = pos[k][1];
            newvel = y - cur->unk4;
            delta = newvel - cur->unk8;
            cur->unk4 = y;
            cur->unk8 = newvel;
            boost = 0.4f * ret;
            y = (0 < ret) ? ret : -ret;
            if (k != 0) {
                accel0 = -spE0;
                accel1 = -((y * 0.3f) + (-0.015f * delta - 0.0008f * newvel));
            } else {
                accel0 = spE0;
                accel1 = (y * 0.3f) + (-0.015f * delta - 0.0008f * newvel);
            }
            accel0 += boost;
        }
        i = 0;
        do {
            if (active != 0) {
                func_806F1A18(accel1, 0.06f, &pair->unk0, &spC8);
                func_806F1A18(accel0, 0.06f, &pair->unkC, &spC4);
            }
            slot->unk0 = value;
            slot->unk1 = kind;
            slot->unk2 = 0;
            slot->unk4 = (s32) ((pair->unkC.unk4 + pair->unkC.unk0) * 10430.218905280077);
            slot->unk6 = (s32) ((pair->unk0.unk4 + pair->unk0.unk0) * 10430.218905280077);
            i++;
            pair++;
            index++;
            slot++;
            kind++;
        } while (i != 8);
        k++; cur++; // LAYOUT: one source line orders the k/cur reload-increment-store tail
    } while (k != 2);
    *arg2 = index;
}

s32 randomNonNegative(void);
extern s8 D_80752D4E[];
extern f32 D_80752F4C;

void func_806F22A8(Actor *arg0, F5BSlot *arg1, s32 *arg2) {
    F56AState *state;
    F56APair *pair;
    s32 index;
    s32 kind;
    s32 active;
    s32 i;
    s32 pad;
    f32 spB0;
    f32 spAC;
    f32 spA8;
    f32 spA4;
    f32 fs3;
    f32 fs2;
    f32 fs1;
    f32 fs0;
    f32 z;
    f32 y;
    f32 x;
    s8 value[4];
    f32 target;
    f32 dz;
    f32 result;
    f64 pad2;

    state = ((F56AActor *) arg0)->unk178;
    index = *arg2;
    kind = 0x1A;
    pair = state->unk1C;
    spAC = 0.0f;
    spB0 = 0.0f;
    fs3 = 0.0f;
    fs2 = 0.0f;
    spA8 = 0.0003f;
    spA4 = 1.0f;
    fs1 = 0.06f;
    active = func_806F1B58((F5BActor *) arg0, (F5N1Predicate *) state, 3);
    value[3] = -0x80;
    actorGetNodePos(arg0, 5, &x, &y, &z);
    if (active == 0) {
        state->unk0 = (f32) arg0->yaw;
        state->unk4 = y;
        D_80752F4C = 0.0f;
        if ((state->unk14 != 0) && (((F56AActor *) arg0)->unk60 & 0x100) && (state->unk18 == 3)) {
            state->unk14 -= 1;
        }
    } else {
        fs2 = y - state->unk4;
        dz = fs2 - state->unk8;
        fs0 = state->unk0 - (f32) arg0->yaw;
        if (((F56AIdxSub *) arg0->unk4)->unk0->unk10 >= 0) {
            target = (f32) D_80752D4E[((F56AIdxSub *) arg0->unk4)->unk0->unk10];
        } else {
            target = -128.0f;
        }
        state->unk0 = (f32) arg0->yaw;
        state->unk10 = (f32) ((f64) state->unk10 + ((f64) (target - state->unk10) * 0.3));
        value[3] = (s8) state->unk10;
        if (arg0->state == 0x4F) {
            fs1 = 0.01f;
            spA8 = 0.0001f;
            spA4 = 0.4f;
        }
        result = func_806F1AE0((F5BActor *) arg0, (F5BAccel *) state, 0.011f);
        state->unk4 = y;
        state->unk8 = fs2;
        fs3 = (-result - ((0.005f * dz) + (0.0008f * fs2))) * spA4;
        if ((32.0f + ((1.0f - spA4) * 8.0f)) < (f32) ((randomNonNegative() >> 15) % 40)) {
            D_80752F4C = (f32) (0x14 - ((randomNonNegative() >> 15) % 40)) * spA8;
        }
        if (fs0 > 2048.0f) {
            fs0 = 4096.0f - fs0;
        } else if (fs0 < -2048.0f) {
            fs0 = -(4096.0f + fs0);
        }
        fs2 = (f32) ((f64) ((1.0f - (arg0->speedXZ / 130.0f)) * D_80752F4C) + (2e-05 * (f64) fs0));
    }
    for (i = 0; i != 11; i++) {
        if (active != 0) {
            func_806F1A18(fs3, fs1, &pair->unk0, &spB0);
            func_806F1A18(fs2, fs1, &pair->unkC, &spAC);
        }
        arg1[index].unk0 = value[3];
        arg1[index].unk1 = kind;
        if (kind == 0) {}  // FAKE: extra use raises kind's uopt priority above the hoisted loop addresses (kind in s3)

        arg1[index].unk2 = (s16) (s32) ((f64) (pair->unk0.unk4 + pair->unk0.unk0) * 10430.218905280077);
        arg1[index].unk4 = (s16) (s32) ((f64) (pair->unkC.unk4 + pair->unkC.unk0) * 10430.218905280077);
        arg1[index].unk6 = 0;
        pair++;
        index++;
        kind++;
    }
    *arg2 = index;
}

typedef struct F5N5PathSample {
    u8 pad0[0x210];
    f32 x0;
    f32 z0;
    f32 y0;
    u8 pad21C[0x228 - 0x21C];
    f32 x1;
    f32 z1;
    f32 y1;
    u8 pad234[0x2F0 - 0x234];
} F5N5PathSample;

typedef struct F5N5Chain3 {
    u8 pad0[0xB2];
    s16 unkB2;
} F5N5Chain3;

typedef struct F5N5Chain2 {
    u8 pad0[0x174];
    F5N5Chain3 *unk174;
} F5N5Chain2;

typedef struct F5N5Chain1 {
    u8 pad0[0x104];
    F5N5Chain2 *unk104;
} F5N5Chain1;

typedef struct F5N5CameraActor {
    u8 pad0[0xE6];
    s16 unkE6;
    u8 padE8[0x174 - 0xE8];
    F5N5Chain1 *unk174;
} F5N5CameraActor;

typedef struct F5N5CameraEntry {
    s8 unk0;
    u8 unk1;
    s16 unk2;
    s16 unk4;
    s16 unk6;
} F5N5CameraEntry;

extern f32 mathAtan2(f32, f32);
#define F5N5_PATH_SAMPLE ((F5N5PathSample *)gPlayerSlots + gCurrentPlayerIndex)

void func_806F2754(F5N5CameraActor *arg0, F5N5CameraEntry *arg1, s32 *arg2) {
    f32 x;
    s16 delta;
    F5N5Chain3 *chain;
    f32 y;
    f32 planarAngle;
    chain = arg0->unk174->unk104->unk174;
    delta = (chain->unkB2 - arg0->unkE6) - 0x800;
    x = F5N5_PATH_SAMPLE->y0 - F5N5_PATH_SAMPLE->y1;
    y = F5N5_PATH_SAMPLE->x0 - F5N5_PATH_SAMPLE->x1;
    planarAngle = mathAtan2(F5N5_PATH_SAMPLE->z0 - F5N5_PATH_SAMPLE->z1, sqrtf((x * x) + (y * y)));
    delta &= 0xFFF;
    if ((delta < 0xC00) && (delta >= 0x801)) {
        arg0->unkE6 = (arg0->unkE6 + delta) - 0xC00;
        delta = 0xC00;
    } else if ((delta >= 0x401) && (delta < 0x800)) {
        arg0->unkE6 = (arg0->unkE6 + delta) - 0x400;
        delta = 0x400;
    }
    arg1[*arg2].unk0 = -128;
    arg1[*arg2].unk1 = 2;
    arg1[*arg2].unk4 = (s16)(u32)(((f64)delta / 4095.0) * 65535.0);
    arg1[*arg2].unk2 = (s16)(u32)((f64)(planarAngle / 6.2831855f) * 65535.0);
    arg1[*arg2].unk6 = 0;
    *arg2 += 1;
}


typedef struct F5CPlayerState {
    u8 pad0[0x21E];
    u16 unk21E;
    u8 pad220[0x38];
    f32 unk258;
    f32 unk25C;
} F5CPlayerState;
typedef struct F5CPlayerActor {
    u8 pad0[0x60];
    u32 unk60;
    u8 pad64[0x128 - 0x64];
    s16 unk128;
    u8 pad12A[0x154 - 0x12A];
    u8 unk154;
} F5CPlayerActor;
typedef struct F5COutput {
    u8 unk0;
    u8 unk1;
    u8 pad2[2];
    f32 unk4;
    f32 unk8;
    f32 unkC;
} F5COutput;
#define F5C_PS ((F5CPlayerState *)gActivePlayerState)
void func_806F2A40(F5CPlayerActor *arg0, F5COutput *arg1, s32 *arg2) {
    f32 temp_fv0;
    f32 var_fa0;
    f32 var_fv1;
    u16 temp_v1;
    s32 adj;
    s32 inc;
    s32 sel;
    if (gActivePlayerState && gActivePlayerState) {}  // FAKE: dead global test steers uopt (ps in v0, u16 in v1)
    temp_v1 = F5C_PS->unk21E;
    temp_fv0 = (f32)temp_v1 * 0.03333333507f;
    if ((f64)temp_fv0 < 1e-05) temp_fv0 = 0.000009999999747f;
    sel = arg0->unk154;
    if ((sel == 0x34) || (sel == 0x84)) {
        if ((f64)F5C_PS->unk25C > 0.01) {
            F5C_PS->unk258 = (f32)((f64)F5C_PS->unk258 * 1.07);
            F5C_PS->unk25C = (f32)((f64)F5C_PS->unk25C * 0.7);
        } else {
            arg0->unk60 &= ~0x8000;
            if (F5C_PS->unk21E != 0) F5C_PS->unk21E -= 1;
            arg0->unk128 = (s16)(255.0f * temp_fv0);
        }
        var_fv1 = F5C_PS->unk258;
        var_fa0 = F5C_PS->unk25C;
    } else {
        var_fa0 = temp_fv0;
        var_fv1 = temp_fv0;
        if (temp_v1 < 0x1E) {
            arg0->unk60 |= 0x8000;
            adj = 0x1E - F5C_PS->unk21E;
            if (temp_v1 == 0) {}  // FAKE: dead use steers uopt priority
            inc = (adj >= 3) ? 2 : adj;
            F5C_PS->unk21E += inc;
            F5C_PS->unk258 = 1.0f;
            F5C_PS->unk25C = F5C_PS->unk258;
        }
    }
    if (arg1 && arg1) {}  // FAKE: dead use of arg1 raises its uopt priority (arg1 in s0, arg2 stays in a2)
    arg1[*arg2].unk0 = 0;
    arg1[*arg2].unk1 = 0xFF;
    arg1[*arg2].unk4 = var_fv1;
    arg1[*arg2].unk8 = var_fa0;
    arg1[*arg2].unkC = var_fv1;
    *arg2 += 1;
}

typedef struct F5CState16 { u8 pad0[0x16]; s16 unk16; } F5CState16;
typedef struct F5CTurnActor { u8 pad0[0x6A]; u16 unk6A; u8 pad6C[0xDC - 0x6C]; s16 unkDC; s16 unkDE; u8 padE0[6]; s16 unkE6; } F5CTurnActor;
typedef struct F5CTurnEntry { s8 unk0; u8 unk1; s16 unk2; s16 unk4; s16 unk6; } F5CTurnEntry;
#define F5C_S16 ((F5CState16 *)gActivePlayerState)
s16 mathAngleSignedDistance(s16, s16);
extern f32 func_80612794(s16);
void func_806F2C48(F5CTurnActor *arg0, F5CTurnEntry *arg1, s32 *arg2) {
    s32 entry_index;
    s8 v;
    u16 angle;
    u16 yaw;
    u16 scaled;
    f32 amplitude;
    f32 cosine;
    entry_index = *arg2;
    if (arg0->unk6A & 1) {
        F5C_S16->unk16 += 2;
        if (F5C_S16->unk16 >= 0x80) F5C_S16->unk16 = 0x7F;
    } else {
        F5C_S16->unk16 -= 2;
        if (F5C_S16->unk16 < 0) F5C_S16->unk16 = 0;
    }
    if (F5C_S16->unk16 != 0) {
        yaw = (arg0->unkDC - 0x800) & 0xFFF;
        scaled = (0x400 - arg0->unkDE) & 0xFFF;
        if (scaled >= 0x156) scaled = 0x155;
        scaled = scaled * 0x10;
        angle = mathAngleSignedDistance(arg0->unkE6, yaw);
        amplitude = func_80612790(angle) * (f32)scaled;
        cosine = func_80612794(angle);
        v = (s8)((F5C_S16->unk16 * 6) / 10);
        if (v != 0) {
            arg1[entry_index].unk1 = 1;
            arg1[entry_index].unk4 = 0;
            arg1[entry_index].unk0 = v;
            arg1[entry_index].unk2 = (s16)amplitude;
            arg1[entry_index].unk6 = (s16)((-cosine) * (f32)scaled);
            entry_index += 1;
        }
        v = (s8)((F5C_S16->unk16 * 3) / 10);
        if (v != 0) {
            arg1[entry_index].unk1 = 2;
            arg1[entry_index].unk4 = 0;
            arg1[entry_index].unk0 = v;
            arg1[entry_index].unk2 = (s16)amplitude;
            arg1[entry_index].unk6 = (s16)((-cosine) * (f32)scaled);
            entry_index += 1;
        }
    }
    *arg2 = entry_index;
}
typedef struct F5CEntry {
    u8 unk0;
    u8 unk1;
    u8 pad2[2];
    f32 unk4;
    f32 unk8;
    f32 unkC;
} F5CEntry;

extern f32 func_80612794(s16);


void func_806F2EDC(s32 arg0, F5CEntry *arg1, s32 *arg2, u8 arg3, u8 arg4, f32 arg5, f32 arg6) {
    f32 angle;

    angle = func_80612794((s16)(arg5 * 2048.0f));
    arg1[*arg2].unk0 = arg3;
    arg1[*arg2].unk1 = arg4;
    arg1[*arg2].unk4 = 1.0f;
    arg1[*arg2].unk8 = ((f32)angle * arg6) + 1.0;
    arg1[*arg2].unkC = 1.0f;
    *arg2 += 1;
}


typedef struct F5N5EffectState {
    u8 pad0[0x8E];
    u8 unk8E;
    u8 unk8F;
    u8 unk90;
    u8 unk91;
} F5N5EffectState;

void effectSpawnBoneWhite(Actor *, s16, f32, f32, f32, f32, s32);

void func_806F2FC0(Actor *arg0, F5N5EffectState *arg1, u16 arg2) {
    u8 state0;
    u8 state2;
    u16 bone;
    s32 selector;
    s32 shouldSpawn;

    selector = arg2;
    switch (selector) {
    case 0:
        state0 = arg1->unk8E;
        if (state0 != 0) {
            if ((state0 == 0x10) && ((s32)arg1->unk8F < 4)) {
                arg1->unk8F = 0;
                return;
            }
        } else {
            if ((s32)arg1->unk8F >= 4) {
                effectSpawnBoneWhite(arg0, 0xA, 0.3f, 0.0f, 0.0f, 0.0f, -10);
                return;
            }
            return;
        }
        break;
    case 1:
        selector = arg1->unk8E;
        shouldSpawn = 0;
        if ((selector != 0) && (selector != 3)) {
            if ((selector == 0x10) && ((s32)arg1->unk8F < 6)) {
                arg1->unk8F = 0;
            }
        } else if ((s32)arg1->unk8F >= 6) {
            shouldSpawn = 1;
        }
        if (shouldSpawn != 0) {
            if (arg1->unk8E != 0) {
                bone = arg1->unk90 + 9;
            } else {
                bone = arg1->unk91 + 9;
            }
            effectSpawnBoneWhite(arg0, bone, 0.2f, 0.0f, 0.0f, 0.0f, -10);
            return;
        }
        break;
    case 4:
    case 5:
        state2 = arg1->unk8E;
        if (state2 != 0) {
            if ((state2 == 0x10) && ((s32)arg1->unk8F < 3)) {
                arg1->unk8F = 0;
                return;
            }
        } else if ((s32)arg1->unk8F >= 3) {
            effectSpawnBoneWhite(arg0, 0xA, 0.6f, 0.0f, 0.0f, 0.0f, -10);
        }
        break;
    }
}


typedef struct {
    s16 unk0;
    u8 pad2[2];
    void *unk4;
} F5DListEntry;

extern u8 gWaypointFlags;

typedef struct {
    u8 pad0[4];
    f32 unk4;
} F56CHead;

typedef struct {
    u8 pad0[0x1C];
    void *unk1C;
    void *unk20;
    u8 *unk24;
} F56CSub;

typedef struct {
    u8 pad0[0x8C];
    u8 unk8C;
    u8 pad8D;
    u8 unk8E;
    u8 unk8F;
    u8 pad90[0x21E - 0x90];
    u16 unk21E;
} F56CExtra;

void func_806F1EB0();
void func_806F22A8();
void func_806F2A40();

void func_806F3190(Actor *arg0, u16 arg1) {
    F56CExtra *sp74;
    s32 sp70;
    s32 sp6C;
    F56CSub *sub;
    F5N3TableEntry1768 *sp64;
    F5CEntry *sp60;
    u8 *sp5C;
    f32 sp58;
    f32 t;
    f32 v;

    sp74 = arg0->unk174;
    if ((arg0->state != 0x77) && (arg0->flags & 4)) {
        sub = (F56CSub *)arg0->unk4;
        sp64 = sub->unk1C;
        sp60 = sub->unk20;
        sp5C = sub->unk24;
        sp70 = 0;
        sp6C = 0;
        if ((func_80714608(0) != 0) && ((sp74->unk21E != 0x1E) || (arg0->state == 0x34))) {
            func_806F2A40((s32)arg0, sp60, &sp6C);
        }
        switch (arg1) {
        case 0:
            func_806F2C48((F5CTurnActor *)arg0, (F5CTurnEntry *)sp64, &sp70);
            func_806F1C04(arg0, (F5BSlot *)sp64, &sp70);
            if (sp74->unk8E != 0) {
                func_806F1858((s32)arg0, sp64, &sp70);
            }
            break;
        case 1:
            switch (arg0->state) {
            case 7:
            case 8:
            case 9:
            case 10:
            case 11:
                break;
            case 2:
                func_806F2754((F5N5CameraActor *)arg0, (F5N5CameraEntry *)sp64, &sp70);
                break;
            default:
            case 3:
            case 4:
            case 5:
            case 6:
                func_806F2C48((F5CTurnActor *)arg0, (F5CTurnEntry *)sp64, &sp70);
                break;
            }
            func_806F22A8((s32)arg0, sp64, &sp70);
            if (sp74->unk8E != 0) {
                func_806F1768((s32)arg0, sp64, &sp70);
            }
            break;
        case 2:
            switch (arg0->state) {
            case 0x26:
                if (arg0->unk155[0] != 0) {
                    t = (*(F56CHead **)arg0->unk4)->unk4;
                    if (t < 6.0f) {
                        v = 0.0f;
                    } else {
                        v = t - 6.0f;
                    }
                    sp58 = (f64)v / 17.0 > 1.0 ? 1.0 : (f64)v / 17.0;
                    func_806F2EDC((s32)arg0, sp60, &sp6C, 0xA, 0xB, sp58, (f32)(gCurrentMap == 0xCD ? 17.0 : 2.5));
                }
                break;
            case 0x27: {
                t = (*(F56CHead **)arg0->unk4)->unk4;
                if (t < 6.0f) {
                    v = 0.0f;
                } else {
                    v = t - 6.0f;
                }
                sp58 = (f64)v / 17.0 > 1.0 ? 1.0 : (f64)v / 17.0;
                func_806F2EDC((s32)arg0, sp60, &sp6C, 5, 6, sp58, (f32)(gCurrentMap == 0xCD ? 17.0 : 2.5));
                break;
            }
            case 0x28: {
                t = (*(F56CHead **)arg0->unk4)->unk4;
                if (t < 7.0f) {
                    v = 0.0f;
                } else {
                    v = t - 7.0f;
                }
                sp58 = (f64)v / 14.0 > 1.0 ? 1.0 : (f64)v / 14.0;
                func_806F2EDC((s32)arg0, sp60, &sp6C, 9, 0xB, sp58, 1.8f);
                func_806F2EDC((s32)arg0, sp60, &sp6C, 4, 6, sp58, 1.8f);
                break;
            }
            case 0x29: {
                t = (*(F56CHead **)arg0->unk4)->unk4;
                if (t < 4.0f) {
                    v = 0.0f;
                } else {
                    v = t - 4.0f;
                }
                sp58 = (f64)v / 6.0 > 1.0 ? 1.0 : (f64)v / 6.0;
                func_806F2EDC((s32)arg0, sp60, &sp6C, 9, 0xB, sp58, 1.3f);
                func_806F2EDC((s32)arg0, sp60, &sp6C, 4, 6, sp58, 1.3f);
                break;
            }
            }
            break;
        case 3:
            func_806F1EB0((s32)arg0, sp64, &sp70);
            if (sp74->unk8E != 0) {
                func_806F1990((s32)arg0, (F5BSlot *)sp64, &sp70);
            }
            break;
        case 4:
        case 5:
            if (sp74->unk8E != 0) {
                func_806F18F4((s32)arg0, (F5BSlot *)sp64, &sp70);
            }
            break;
        case 6:
            break;
        }
        sp64[sp70].unk0 = 0;
        sp60[sp6C].unk0 = 0xFF;
        *sp5C = 0xFF;
        if (sp74->unk8E != 0) {
            sp74->unk8E -= 1;
            if (sp74->unk8C != 0) {
                func_806F2FC0(arg0, (F5N5EffectState *)sp74, arg1);
            }
        }
        if (sp74->unk8E == 0) {
            sp74->unk8F = 0;
        }
    }
}


void playerWaypointPathsParse(void *);

void playerWaypointPathsLoad(s16 arg0) {
    s32 sp1C;
    s32 temp_v0;

    temp_v0 = assetLoad(0x15, arg0, 1, 0);
    sp1C = temp_v0;
    playerWaypointPathsParse((void *)temp_v0);
    if (sp1C != 0) {
        assetFreeBuffer(sp1C, 0x4C, 0x56);
    }
}

typedef struct {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    u8 pad6[0xC];
    s16 unk12;
    u8 pad14[2];
    s16 unk16;
} F5N4Coord;

typedef struct {
    u8 pad0[0xE6];
    s16 unkE6;
    u8 padE8[6];
    s16 unkEE;
} F5N4ActorView;

void actorClearMovementFlags(void *);
s16 mathAngleBetweenPoints2D(f32, f32, f32, f32);

void actorSetPositionAndFacingAngle(Actor *arg0, F5N4Coord *arg1) {
    s16 angle;

    actorClearMovementFlags(arg0);
    arg0->x = arg1->unk0;
    arg0->y = arg1->unk2;
    arg0->z = arg1->unk4;
    angle = mathAngleBetweenPoints2D(arg1->unk12, arg1->unk16, arg1->unk0, arg1->unk4);
    ((F5N4ActorView *)arg0)->unkEE = angle;
    ((F5N4ActorView *)arg0)->unkE6 = angle;
}

typedef struct {
    s16 unk0;
    u8 pad2[2];
    void *unk4;
} F5N4ListEntry;

typedef struct {
    s16 unk0;
    u8 pad2[2];
    F5N4ListEntry *unk4;
} F5N4List;

typedef struct {
    u8 pad0[0x1F0];
    s32 unk1F0;
} F5N4ActorExtra;

extern u8 D_807463B8;
extern F5N4List *gWaypointPaths;
extern u8 D_8076A0B1;
extern F5N4ListEntry *gWaypointPathEntry;
extern F5N4Coord *gWaypointCursor;
extern s32 gWaypointActor;
extern s16 gWaypointIndex;
extern s16 gWaypointCallbackId;
extern s32 gWaypointCallbackParam;

void playerWaypointPathStart(u8 arg0, s32 arg1, s32 arg2, s16 arg3, u8 arg4) {
    F5N4ActorExtra *temp_v0;

    temp_v0 = (F5N4ActorExtra *)((Actor *)arg1)->unk174;
    if (gWaypointPaths->unk0 >= arg0) {
        D_807463B8 = 3;
        D_8076A0B1 |= 0x10;
        gWaypointActor = arg1;
        temp_v0->unk1F0 &= ~1;
        gWaypointIndex = 0;
        gWaypointPathEntry = gWaypointPaths->unk4 + arg0;
        gWaypointCursor = gWaypointPathEntry->unk4;
        gWaypointCallbackId = arg3;
        gWaypointCallbackParam = arg2;
        if (arg4 == 0) {
            actorSetPositionAndFacingAngle((Actor *)arg1, gWaypointCursor);
        }
    }
}


typedef struct {
    s16 unk0;
    u8 pad2[2];
    void *unk4;
} F5DDeferredEntry;

void heapFreeDeferred(void *);

void deferredEntryFree(F5DDeferredEntry *arg0) {
    heapFreeDeferred(arg0->unk4);
    arg0->unk0 = 0;
}


void playerWaypointPathStart(u8, s32, s32, s16, u8);

void playerWaypointPathStartPacked(s32 arg0, s32 arg1, s16 arg2, s16 arg3) {
    s32 var_v0;

    if (arg2 & 0x8000) {
        var_v0 = 1;
    } else {
        var_v0 = 0;
    }
    arg2 &= 0x7FFF;
    playerWaypointPathStart((u8) arg2, arg0, arg1, arg3, var_v0);
    gWaypointFlags = 0;
}

typedef struct {
    s16 x;
    s16 y;
    s16 z;
    u8 pad6[3];
    u8 unk9;
    u8 pad10[8];
} F5N6Point;

typedef struct {
    s16 unk0;
    u8 pad2[2];
    F5N6Point *unk4;
} F56CEnt;

extern void *heapAlloc(s32);
extern void heapClearBlock(void *);
extern s32 D_807FBB60;


typedef struct {
    s16 x;
    s16 y;
    s16 z;
    u8 unk6;
} F5N6Input;

void playerWaypointPathStartLineFromPoint(arg0, arg1, arg2)
Actor *arg0;
F5N6Input *arg1;
u8 arg2;
{
    F5N6Point *p;
    F5N6Point *q;
    F56CEnt *entry;

    entry = (F56CEnt *)&gWaypointPaths->unk4[gWaypointPaths->unk0];
    entry->unk0 = 2;
    entry->unk4 = heapAlloc(0x24);
    heapClearBlock(entry->unk4);
    q = entry->unk4 + 1;
    p = entry->unk4;
    p->x = arg1->x;
    p->y = arg1->y;
    p->z = arg1->z;
    p->unk9 = 0x32;
    q->x = func_80612794((s16)((arg1->unk6 / 255.0) * 4095.0)) * arg2 + arg1->x;
    q->y = arg1->y;
    q->z = func_80612790((s16)((arg1->unk6 / 255.0) * 4095.0)) * arg2 + arg1->z;
    q->unk9 = 0x32;
    playerWaypointPathStart(*((u8 *)gWaypointPaths + 1), (s32)arg0, 0, 0, 0);
    gWaypointFlags = 0;
    D_807FBB60 |= 0x400;
}


void playerWaypointPathStartLineFromActor(arg0, arg1, arg2, arg3)
Actor *arg0;
s16 arg1;
s16 arg2;
u8 arg3;
{
    F5N6Point *p;
    s16 angle;
    F5N6Point *q;
    F56CEnt *entry;

    angle = mathAngleBetweenPoints2D((f32)arg1, (f32)arg2, arg0->x, arg0->z);
    entry = (F56CEnt *)&gWaypointPaths->unk4[gWaypointPaths->unk0];
    if (arg0->state != 0x44) {
        entry->unk0 = 2;
        entry->unk4 = heapAlloc(0x24);
        heapClearBlock(entry->unk4);
        q = entry->unk4 + 1;
        p = entry->unk4;
        p->x = arg0->x;
        p->y = arg0->y;
        p->z = arg0->z;
        p->unk9 = 0x28;
        q->x = func_80612794(angle) * arg3 + arg0->x;
        q->y = arg0->y;
        q->z = func_80612790(angle) * arg3 + arg0->z;
        q->unk9 = 0x28;
        playerWaypointPathStart(*((u8 *)gWaypointPaths + 1), (s32)arg0, 0, 0, 0);
        gWaypointFlags = 0;
        D_807FBB60 |= 0x400;
    }
}


void playerWaypointSnapInput(void) {
    gWaypointFlags |= 2;
}

void timerDecrementOrSetFlag(u16 *arg0, s16 *arg1, u8 *arg2, u16 arg3) {
    s16 temp_v0;
    u8 temp_v0_2;

    temp_v0 = *arg1;
    if (temp_v0 != 0) {
        *arg1 = temp_v0 - 1;
        return;
    }
    temp_v0_2 = *arg2;
    if (temp_v0_2 != 0) {
        *arg2 = temp_v0_2 - 1;
        *arg0 |= arg3;
    }
}


typedef struct F5L1Control {
    u16 flags;
    s8 yaw;
    s8 pitch;
} F5L1Control;

typedef struct F5L1Waypoint {
    s16 x;
    s16 y;
    s16 z;
    u8 timer0;
    u8 timer1;
    u8 timer2;
    u8 speed;
    s16 timer3;
    s16 timer4;
    s16 timer5;
    s16 delay;
} F5L1Waypoint;

typedef struct F5L1Target {
    u8 pad0[0x1F0];
    s32 flags;
} F5L1Target;

typedef struct F5L1CamBlock {
    u8 pad0[0x210];
    f32 x;
    u8 pad214[4];
    f32 z;
    u8 pad21C[0xC];
    f32 targetX;
    u8 pad22C[4];
    f32 targetZ;
} F5L1CamBlock;

#define F5L1Cam ((F5L1CamBlock *)gPlayerSlots)
#define F5L1_MAX(a, b) ((a) > (b) ? (a) : (b))
#define F5L1_MIN(a, b) ((a) < (b) ? (a) : (b))
#define F5L1_CLAMP(x) F5L1_MIN(F5L1_MAX(x, -128.0f), 127.0f)

void playerInitMoveParams(void);
s32 playerStateQueueCallback();
f32 mathAngleBetweenPointsDeg(s32, s32, s32, s32);
f32 mathCalculatePitchAngle(f32, f32, f32, f32, f32, f32, s32);
extern u8 D_807444EC;
extern u8 D_8076A0B3;
#define F5L1_B8 (*(s8 *)&D_807463B8)
#define F5L1_WP (*(F5L1Waypoint **)&gWaypointCursor)
#define F5L1_TGTA (*(Actor **)&gWaypointActor)

void playerStateWaypointAimUpdate(F5L1Control *arg0, s32 arg1) {
    F5L1Target *tgt;
    f32 ang;
    f32 camAng;
    f32 pitch;
    F5L1Waypoint *cur;
    F5L1Waypoint *next;
    f32 blend;
    f32 speed;
    s16 yawT;
    s32 eq;
    f32 dx;
    f32 dz;
    u8 close;
    u8 flags;
    s16 pitchT;

    cur = F5L1_WP;
    tgt = F5L1_TGTA->unk174;
    blend = 0.2f;
    next = F5L1_WP + 1;
    speed = (u32)cur->speed * 0.7;
    dx = F5L1_TGTA->x - next->x;
    dz = F5L1_TGTA->z - next->z;
    close = dx * dx + dz * dz < 100.0f;
    if (close) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
    flags = gWaypointFlags;
    if (gWaypointCallbackParam && gWaypointCallbackParam) {}  // FAKE: dead test
    if ((flags == 0) & 1) {
        if (gWaypointCursor != 0) {}  // FAKE: dead test at block start
        gWaypointFlags |= 1;
        arg0->yaw = 0;
        arg0->pitch = 0;
    }
    if (gWaypointFlags || gWaypointCallbackParam) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
    if (close) {
        eq = gWaypointIndex + 2 == gWaypointPathEntry->unk0; // FAKE: bool temp
        if (flags == 0) {}  // FAKE: dead test
        if (eq) {
            F5L1_B8 = 0;
            if (D_807444EC == 0) {
                D_8076A0B1 &= 0xFFEF;
                D_8076A0B3 = 0xFF;
            }
            if (gWaypointCallbackId != 0) {
                if (gWaypointFlags != 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                playerStateQueueCallback(gWaypointCallbackId, gWaypointCallbackParam, 0, &F5L1_WP); // FAKE: 4th arg keeps &F5L1_WP hoisted in $a3
                if (gWaypointCursor == 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
            }
            tgt->flags |= 1;
            D_807FBB60 &= ~0x400;
            playerInitMoveParams();
        } else {
            gWaypointIndex += 1;
            F5L1_WP++;
            cur = F5L1_WP;
            next = cur + 1;
            if (gWaypointIndex || gWaypointFlags) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
        }
    }
    arg0->flags = 0;
    timerDecrementOrSetFlag(&arg0->flags, &cur->timer3, &cur->timer0, 0x8000);
    timerDecrementOrSetFlag(&arg0->flags, &cur->timer4, &cur->timer1, 0x4000);
    timerDecrementOrSetFlag(&arg0->flags, &cur->timer5, &cur->timer2, 0x2000);
    pitchT = 0;
    if (cur->delay != 0) {
        cur->delay = cur->delay - 1;
        yawT = 0;
    } else {
        if (gWaypointFlags & 2) {
            blend = 1.0f;
            gWaypointFlags &= 0xFFFD;
        }
        if (F5L1_TGTA->state == 0x4F) {
            ang = mathAngleBetweenPointsDeg(next->x, next->z, (s32)F5L1_TGTA->x, (s32)F5L1_TGTA->z) * 0.017453292f - (F5L1_TGTA->yaw * 3.1415927f) * 0.00048828125;
            pitch = mathCalculatePitchAngle(next->x, next->y, next->z, F5L1_TGTA->x, F5L1_TGTA->y, F5L1_TGTA->z, 0);
            arg0->flags |= 0x4000;
            yawT = ang;
            pitchT = F5L1_CLAMP(sinApprox(pitch) * speed);
        } else {
            camAng = mathAngleBetweenPointsDeg((s32)F5L1Cam->targetX, (s32)F5L1Cam->targetZ, (s32)F5L1Cam->x, (s32)F5L1Cam->z);
            ang = mathAngleBetweenPointsDeg(next->x, next->z, (s32)F5L1_TGTA->x, (s32)F5L1_TGTA->z) * 0.017453292f - camAng * 0.017453292f;
            yawT = F5L1_CLAMP(sinApprox(ang) * speed);
            pitchT = F5L1_CLAMP(cosApprox(ang) * speed);
        }
    }
    arg0->yaw = arg0->yaw + (yawT - arg0->yaw) * blend;
    arg0->pitch = arg0->pitch + (pitchT - arg0->pitch) * blend;
}

typedef struct {
    s16 halves[9];
} F5N4RawEntry;

void playerWaypointPathsParse(void *arg0) {
    u8 *next;
    u8 *destination;
    u8 *source;
    F5N4ListEntry *entry;
    s16 outer;
    s16 inner;

    if (arg0 != NULL) {
        gWaypointPaths->unk0 = *(s16 *)arg0;
        source = (u8 *)arg0 + 2;
        gWaypointPaths->unk4 = heapAlloc((gWaypointPaths->unk0 * 8) + 8);
        entry = gWaypointPaths->unk4;
        for (outer = 0; outer < gWaypointPaths->unk0; outer++) {
            entry->unk0 = *(s16 *)source;
            next = source + 2;
            for (inner = 0; inner < entry->unk0; inner++) {
                if (inner == 0) {
                    entry->unk4 = heapAlloc(entry->unk0 * 0x12);
                    destination = entry->unk4;
                } else {
                    destination += 0x12;
                }
                *(F5N4RawEntry *)destination = *(F5N4RawEntry *)next;
                next += 0x12;
            }
            source = next;
            entry++;
        }
    } else {
        gWaypointPaths->unk0 = 0;
    }
}

