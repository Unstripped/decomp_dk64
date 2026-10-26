#include "common.h"
#include "actor.h"

extern Actor *D_807FBB40;
extern Actor *D_807FBB44;
extern Actor *D_807FBB48;
extern void *D_807FC924;
extern u8 D_807FC928;
extern u8 D_807FC929;
extern Struct807FD580 *D_807FD580;
extern s16 D_807FD584;
extern s32 D_8076A0A8;
extern u8 D_8074E77C[];

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
    switch (D_8074E77C[D_807FC929]) {
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

s32 func_80613448(void);

void func_806F0C18(Actor *arg0) {
    s32 pad;
    F5N2ActorExtra *extra;

    switch (func_80613448()) {
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

    switch (func_80613448()) {
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
            switch (D_8074E77C[D_807FC929]) {
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

void func_80613214(void);
void func_806C8D20(Actor *);

void func_806F1048(Actor *arg0) {
    F5N2ActorState *state = arg0->unk174;

    switch (arg0->unk58) {
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
            func_80613214();
        }
        break;
    }
    func_806C8D20(D_807FBB40);
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
void func_8067B238(Actor *, Actor *, f32);
void func_80613194(Actor *, s32);

void func_806F10E8(Actor *arg0) {
    switch (((F5N3ActorState *) arg0)->state) {
        case 2:
        case 0xC4:
            func_806F0C18(arg0);
            actorSpawn(0xEF, 0xA6);
            func_8067B238(D_807FBB44, arg0, ((F5N3ActorSub10E8 *) arg0->unk4)->unk38 * 1.25);
            ((F5N3ActorState *) D_807FBB44)->unkE4 = ((F5N3ActorState *) arg0)->unkE4;
            ((F5N3ActorState *) D_807FBB44)->unkE8 = ((F5N3ActorState *) arg0)->unkE8;
            D_807FBB44->unk60 |= 0x40000000;
            break;
        case 3:
        case 0xC5:
            func_806F0C18(arg0);
            func_80613194(arg0, 2);
            break;
        case 4:
        case 0xC6:
            func_806F0C18(arg0);
            func_80613194(arg0, 7);
            break;
        case 5:
        case 0xC7:
            func_806F0C18(arg0);
            func_80613194(arg0, 0xA);
            break;
        case 6:
        case 0xC8:
            func_806F0C18(arg0);
            func_80613194(arg0, 0xD);
            break;
    }
}

typedef struct F5N3ActorExtra {
    u8 pad0[0x1F0];
    s32 flags;
} F5N3ActorExtra;

void func_806086CC(f32, f32, f32, s32, s32, s32, s32, s32, f32, s32);
void sfxAllocateChannel(s32, f32);
void sfxStopChannel(s32, s32);
extern s32 D_807FBB68;

void func_806F1250(Actor *arg0) {
    F5N3ActorExtra *extra = arg0->unk174;

    if (arg0->unk58 == 6) {
        func_80613194(arg0, 0x10);
        func_806086CC(arg0->unk7C, arg0->unk80, arg0->unk84, 0x2E2, 0xFF, 0xA0, 0, 0x32, 0.0f, 0);
        if (!(D_807FBB68 & 2)) {
            sfxAllocateChannel(0x6C, 1.0f);
        }
    }
    extra->flags |= 0x40;
}

void func_806F12FC(Actor *arg0) {
    F5N3ActorExtra *extra = arg0->unk174;

    if (arg0->unk58 == 6) {
        func_80613214();
        sfxStopChannel(0x6C, 0);
    }
    extra->flags &= ~0x40;
}

void func_806E225C();

void func_806F1350(s32 arg0) {
    func_806E225C(0, 1);
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
    ((F5AActorSub4 *)arg0->unk4)->unk88 = (s32)(arg0->unkB8 - temp);
}

typedef struct F5APlayerState {
    u8 pad0[0x4C];
    s16 unk4C;
} F5APlayerState;

#define F5A_PS ((F5APlayerState *)D_807FD580)

void scriptReadU8(u8 *);
s32 func_806CD9A0(Actor *, f32, f32, s16, s16);

void func_806F13C8(Actor *arg0) {
    u8 temp;

    scriptReadU8(&temp);
    ((F5AActorSub4 *)arg0->unk4)->unk88 =
        func_806CD9A0(arg0, arg0->unkB8, arg0->unkB8, F5A_PS->unk4C, D_807FD584) - temp;
}

typedef struct F5APlayerCoefficient {
    f32 value;
    u8 pad4[0x30];
} F5APlayerCoefficient;

extern F5APlayerCoefficient D_807FD618[];
void func_806CFF9C(void);

void func_806F142C(void) {
    f32 value;

    func_806CFF9C();
    value = D_807FBB40->unkB8;
    D_807FBB40->unkB8 =
        D_807FD618[D_807FC929].value * (value - (value / 2)) + (value / 2);
}

void func_806D0150(Actor *);

void func_806F149C(Actor *arg0) {
    func_806D0150(arg0);
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/F56F0/func_806F14BC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/F56F0/func_806F1668.s")

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

#define F5N3_PLAYER_1768 ((F5N3PlayerState1768 *) D_807FD580)

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

#define F5B_PLAYER_STATE ((F5BPlayerState *)D_807FD580)

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

#pragma GLOBAL_ASM("asm/global/nonmatchings/F56F0/func_806F1A18.s")

f32 func_806F1AE0(F5BActor *arg0, F5BAccel *arg1, f32 arg2) {
    f32 temp_fa0;
    f32 temp_fv1;

    temp_fv1 = func_80612790((s16)(arg0->unkE6 - arg0->unkEE)) * (arg0->unkB8 * 0.0076923077f);
    temp_fa0 = temp_fv1 - arg1->unkC;
    arg1->unkC = temp_fv1;
    return (temp_fa0 + temp_fv1) * arg2;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/F56F0/func_806F1B58.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/F56F0/func_806F1B90.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/F56F0/func_806F1C04.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/F56F0/func_806F1EB0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/F56F0/func_806F22A8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/F56F0/func_806F2754.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/F56F0/func_806F2A40.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/F56F0/func_806F2C48.s")
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


#pragma GLOBAL_ASM("asm/global/nonmatchings/F56F0/func_806F2FC0.s")

typedef struct {
    s16 unk0;
    u8 pad2[2];
    void *unk4;
} F5DListEntry;

extern u8 D_807FD716;

#pragma GLOBAL_ASM("asm/global/nonmatchings/F56F0/func_806F3190.s")

void func_806F4528(void *);

void func_806F3760(s16 arg0) {
    s32 sp1C;
    s32 temp_v0;

    temp_v0 = func_8066B0F8(0x15, arg0, 1, 0);
    sp1C = temp_v0;
    func_806F4528((void *)temp_v0);
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
    arg0->unk7C = arg1->unk0;
    arg0->unk80 = arg1->unk2;
    arg0->unk84 = arg1->unk4;
    angle = mathAngleBetweenPoints2D(arg1->unk12, arg1->unk16, arg1->unk0, arg1->unk4);
    ((F5N4ActorView *)arg0)->unkEE = angle;
    ((F5N4ActorView *)arg0)->unkE6 = angle;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/F56F0/func_806F386C.s")

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


void func_806F386C(u8, s32, s32, s16, s32);

void func_806F397C(s32 arg0, s32 arg1, s16 arg2, s16 arg3) {
    s32 var_v0;

    if (arg2 & 0x8000) {
        var_v0 = 1;
    } else {
        var_v0 = 0;
    }
    arg2 &= 0x7FFF;
    func_806F386C((u8) arg2, arg0, arg1, arg3, var_v0);
    D_807FD716 = 0;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/F56F0/func_806F39E8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/F56F0/func_806F3BEC.s")

void func_806F3DB0(void) {
    D_807FD716 |= 2;
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

#pragma GLOBAL_ASM("asm/global/nonmatchings/F56F0/func_806F3E0C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/F56F0/func_806F4528.s")
