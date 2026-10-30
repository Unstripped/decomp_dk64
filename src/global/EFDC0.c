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
typedef struct EfAQueuedCall {
    u8 pad0[0x29C];
    s16 unk29C;
    Actor *unk2A0;
    s32 unk2A4;
    s32 unk2A8;
    s32 unk2AC;
    s32 unk2B0;
    u8 pad2B4[0x3C];
} EfAQueuedCall;

typedef struct EfAPlayer {
    u8 pad0[4];
    f32 unk4;
    u8 pad8[2];
    s16 unkA;
    u8 padC[0x20];
    f32 unk2C;
    u8 pad30[8];
    f32 unk38;
    s16 unk3C;
    u8 pad3E[0xE];
    s16 unk4C;
    s16 unk4E;
    s16 unk50;
    u8 pad52[0x12];
    s32 unk64;
    u8 pad68[0x24];
    u8 unk8C;
    u8 pad90[0x74];
    Actor *unk104;
    u8 pad108[0x9B];
    u8 unk1A3;
    u8 unk1A4;
} EfAPlayer;

typedef struct EfAActor {
    u8 pad0[0x54];
    s32 unk54;
    u8 pad58[8];
    s32 unk60;
    u8 pad64[0x54];
    f32 unkB8;
    f32 unkBC;
    f32 unkC0;
    f32 unkC4;
    u8 padC8[0x1E];
    s16 unkE6;
    u8 padE8[0x6C];
    u8 unk154;
    u8 unk155;
    u8 pad156[0x1E];
    void *unk174;
} EfAActor;


typedef struct EfAParameters {
    s32 unk0;
    s32 unk4;
    s32 unk8;
} EfAParameters;

#define EfA_P ((EfAPlayer *)D_807FD580)
#define EfA_A40 ((EfAActor *)D_807FBB40)

extern EfAParameters D_807FD6F0;
void func_80614D48(Actor *, f32, f32);
void func_80614E78(Actor *, s32);
void actorScriptStart(Actor *, s32);
void func_80609140(s32, s32, f32, f32, s32, s32);
void func_806CFF9C(Actor *);
void slotQueueUpdate(s32, s32, s32);

s32 playerStateQueueCallback(s16 priority, void *actor, u8 player) {
    u8 playerByte;
    s32 offset;
    s32 priorityCopy;
    EfAQueuedCall *entry;

    priorityCopy = priority;
    playerByte = player;
    offset = playerByte * 0x2F0;
    entry = (EfAQueuedCall *)((u8 *)D_807FC924 + offset);
    if (entry->unk29C < priorityCopy) {
        entry->unk29C = priorityCopy;
        ((EfAQueuedCall *)((u8 *)D_807FC924 + offset))->unk2A0 = actor;
        ((EfAQueuedCall *)((u8 *)D_807FC924 + offset))->unk2A8 = D_807FD6F0.unk0;
        ((EfAQueuedCall *)((u8 *)D_807FC924 + offset))->unk2AC = D_807FD6F0.unk4;
        ((EfAQueuedCall *)((u8 *)D_807FC924 + offset))->unk2B0 = D_807FD6F0.unk8;
        if (actor != NULL) {
            ((EfAQueuedCall *)((u8 *)D_807FC924 + offset))->unk2A4 = ((EfAActor *)actor)->unk54;
        }
        return 1;
    }
    return 0;
}

void playerStateSetCallbackParameters(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    D_807FD6F0.unk0 = arg1;
    D_807FD6F0.unk4 = arg2;
    D_807FD6F0.unk8 = arg3;
}

#define EfN9_Q ((EfAQueuedCall *)D_807FC924)

extern void (*D_80752C70[])(void);
s32 actorTableContains(Actor *);

void playerStateDispatchQueuedCallback(void) {
    if (EfN9_Q[D_807FC929].unk29C >= 0) {
        if (EfN9_Q[D_807FC929].unk2A0 != NULL) {
            if ((actorTableContains(EfN9_Q[D_807FC929].unk2A0) == 0) ||
                (((EfAActor *)EfN9_Q[D_807FC929].unk2A0)->unk54 != EfN9_Q[D_807FC929].unk2A4)) {
                EfN9_Q[D_807FC929].unk2A0 = NULL;
            }
        }
        D_80752C70[EfN9_Q[D_807FC929].unk29C]();
    }
    EfN9_Q[D_807FC929].unk29C = -1;
}


void func_806CD424(s16, f32, f32);
void func_806CFECC(void);

void func_806EB2B8(void) {
    func_806CFECC();
    D_807FBB40->unk154 = 0x22;
    D_807FBB40->unk155[0] = 0;
    EfA_A40->unkC0 = 100.0f;
    EfA_P->unk50 = 0;
    EfA_P->unk2C = 100.0f;
    if (EfA_P->unk3C == 0) {
        func_806CD424(EfA_P->unkA, EfA_P->unk4, EfA_P->unk38);
    }
    EfA_P->unk2C = 10.0f;
    actorScriptStart(D_807FBB40, 0x17B);
}

void func_806EB364(void) {
    if (D_8074E77C[D_807FC929] == 6) {
        func_806CFF9C(D_807FBB48);
        return;
    }
    D_807FBB40->unk154 = 0x3D;
    D_807FBB40->unk155[0] = 0;
    if (EfA_P->unk4E == 0x22) {
        actorScriptStart(D_807FBB40, 0x131);
        return;
    }
    func_80614E78(D_807FBB40, 0xD);
}

#define EfA_Q ((EfAQueuedCall *)D_807FC924)

#ifdef NON_MATCHING
typedef struct EfASubActor {
    u8 pad0[0xD4];
    s16 unkD4;
    u8 padD6[0x11A];
    s32 unk1F0;
} EfASubActor;

s32 func_806EB400(Actor *arg0) {
    s32 pred;
    EfASubActor *sub;

    sub = (EfASubActor *)arg0->unk174;
    pred = (sub->unkD4 == 0) || (EfA_Q[D_807FC929].unk29C == 0x3F);
    if ((D_8074E77C[D_807FC929] == 7) || (sub->unk1F0 & 0x8000)) {
        return 0;
    }
    return ((arg0->unk154 == 0x34) || (arg0->unk154 == 0x36)) ? 0 : (pred & 1);
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/EFDC0/func_806EB400.s")
#endif

void func_806EB4B4(void) {
    D_807FBB40->unk154 = 0x23;
    D_807FBB40->unk155[0] = 0;
    actorScriptStart(D_807FBB48, 0x3BC);
}

void func_806EB4F8(void) {
    D_807FBB40->unk154 = 0x5F;
    D_807FBB40->unk155[0] = 0;
    EfA_P->unk1A3 = 0;
    func_80614E78(D_807FBB40, 0x4A);
}

extern s32 slotQueueGetValue(s32, u8);

void func_806EB544(void) {
    s32 selector;
    f32 unused;

    selector = 2;
    if (slotQueueGetValue(3, EfA_P->unk1A4) != 0) {
        selector = 3;
    }
    slotQueueUpdate(selector, 0, 0);
    D_807FBB40->unk154 = 0x60;
    D_807FBB40->unk155[0] = 0;
    EfA_P->unk1A3 = 0;
    func_80614E78(D_807FBB40, 0x4B);
}

typedef struct EfN2Player {
    u8 pad0[0x64];
    s16 unk64;
    u8 pad66[0x62];
    s16 unkC8;
} EfN2Player;

void func_806EB5C8(void) {
    switch (D_8074E77C[D_807FC929]) {
    case 0:
    case 1:
    case 2:
        EfA_A40->unkC0 = 50.0f;
        EfA_A40->unkC4 = -2.5f;
        break;
    case 3:
        EfA_A40->unkC0 = 140.0f;
        EfA_A40->unkC4 = -20.0f;
        break;
    case 4:
    case 5:
        EfA_A40->unkC0 = 40.0f;
        EfA_A40->unkC4 = -7.0f;
        break;
    }
    EfA_A40->unk154 = 0x2A;
    EfA_A40->unk155 = 0;
    func_80614E78(D_807FBB40, 0x43);
    ((EfN2Player *)D_807FD580)->unk64 = 0;
    ((EfN2Player *)D_807FD580)->unkC8 = 0x32;
}

void func_806EB6D8(void) {
    EfA_P->unk4C = -1;
    EfA_P->unk38 = 170.0f;
    D_807FBB40->unk154 = 0x3F;
    D_807FBB40->unk155[0] = 0;
    EfA_P->unk4E = 0;
    actorScriptStart(D_807FBB40, 0x14F);
}

typedef struct EfN2SubActor {
    u8 pad0[0xB2];
    s16 unkB2;
    f32 unkB4;
    f32 unkB8;
    s16 unkBC;
    u8 padBE[0x31];
    u8 unkEF;
    u8 unkF0;
    u8 padF1[2];
    s8 unkF3;
} EfN2SubActor;

typedef struct EfN2TargetActor {
    u8 pad0[0xB4];
    f32 unkB4;
} EfN2TargetActor;

void camSaveYaw(void *);
void camSetZoomLevel(void *, s32);
void func_806F0D68(Actor *);
void sfxStopSlotSound(Actor *, u8);

void func_806EB744(void) {
    Actor *actor;
    s16 speed;
    s32 state;
    s16 state2;
    EfN2SubActor *subactor;
    u8 type;

    actor = EfA_P->unk104;
    subactor = actor->unk174;
    if (D_807FC924 && D_807FC924) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
    type = subactor->unkEF;
    speed = subactor->unkB8;
    if (type != 0) {
        subactor->unkF0 = type;
        speed = 0x80;
    }
    camSaveYaw(EfA_P->unk104);
    camSetZoomLevel(EfA_P->unk104, 0);
    state = EfA_Q[D_807FC929].unk2A8;
    state2 = state;
    subactor->unkF3 = state2;
    if ((u8)state2 == 3) {
        sfxStopSlotSound(D_807FBB48, 0);
        func_80609140(0x26, 0x7FFF, 63.0f, 1.0f, 0, 0);
        if (EfA_Q[D_807FC929].unk2AC != 0) {
            func_806F0D68(D_807FBB48);
        }
    }
    subactor->unkBC = 0x80;
    ((EfN2TargetActor *)EfA_P->unk104)->unkB4 = speed;
    subactor->unkB8 = speed;
    subactor->unkB2 = D_807FBB48->unkE6 + 0x800;
    D_807FBB48->unkB8 = 0.0f;
    D_807FBB48->unk6A |= 0x2000;
}

void func_806EB8CC(void) {
    func_806EB744();
    D_807FBB48->unk154 = 2;
    D_807FBB48->unk155[0] = 0;
    D_807FBB48->unk155[0] = 0xA;
    if (EfA_P->unk8C != 0) {
        actorScriptStart(D_807FBB48, 0x23);
    } else {
        actorScriptStart(D_807FBB48, 0x13);
    }
    EfA_P->unk50 = 0;
    EfA_P->unk38 = 0.0f;
}

void func_806EB964(void) {
    func_80609140(0x1B9, 0x7FFF, 63.0f, 1.0f, 0xA, 0);
    func_806EB744();
    D_807FBB48->unk154 = 4;
    D_807FBB48->unk155[0] = 0;
    D_807FBB48->unk155[0] = 0xA;
    actorScriptStart(D_807FBB48, 0x13);
    EfA_P->unk50 = 0;
    EfA_P->unk38 = 0.0f;
    slotQueueUpdate(6, 1, 0);
}

void func_806EBA04(void) {
    func_806EB744();
    D_807FBB48->unk154 = 3;
    D_807FBB48->unk155[0] = 0;
    D_807FBB48->unk155[0] = 0xA;
    actorScriptStart(D_807FBB48, 0);
    EfA_P->unk50 = 0;
    EfA_P->unk38 = 0.0f;
}

void func_806EBA74(void) {
    func_806EB744();
    D_807FBB48->unk154 = 5;
    D_807FBB48->unk155[0] = 0;
    D_807FBB48->unk155[0] = 0xA;
    actorScriptStart(D_807FBB48, 0);
    EfA_P->unk50 = 0;
    EfA_P->unk38 = 0.0f;
    slotQueueUpdate(6, 1, 0);
}

void func_806EBAF4(void) {
    D_807FBB40->unk154 = 0x4F;
    D_807FBB40->unk155[0] = 2;
    func_80614E78(D_807FBB40, 0x34);
    EfA_P->unk50 = 0;
}

void func_806EBB44(void) {
    extern u32 D_807FBB60;

    D_807FBB60 |= 0x4000;
    D_807FBB48->unk154 = 1;
    D_807FBB48->unk155[0] = 0;
    actorScriptStart(D_807FBB48, 0);
    func_80614D48(D_807FBB48, 0, 0);
    EfA_P->unk50 = 0;
    EfA_P->unk4C = -1;
}

void func_806EBBD0(void) {
    D_807FBB48->unk154 = 6;
    D_807FBB48->unk155[0] = 0;
    actorScriptStart(D_807FBB48, 0);
    func_80614D48(D_807FBB48, 0, 0);
    EfA_P->unk50 = 0;
    EfA_P->unk4C = -1;
    *(s32 *)((u8 *)D_807FBB48 + 0x60) &= ~4;
}

void func_806EBC60(void) {
    D_807FBB48->unk154 = 0x6B;
    D_807FBB48->unk155[0] = 0;
    actorScriptStart(D_807FBB48, 0);
    func_80614D48(D_807FBB48, 0, 0);
    EfA_P->unk50 = 0;
    EfA_P->unk4C = -1;
    *(s32 *)((u8 *)D_807FBB48 + 0x60) &= ~4;
}


typedef struct EfBActor {
    u8 pad0[0x60];
    u32 unk60;
    u8 pad64[0x54];
    f32 unkB8;
    u8 padBC[4];
    f32 unkC0;
    u8 padC4[0x90];
    u8 unk154;
    u8 unk155;
    u8 pad156[0x22];
    s32 unk178;
} EfBActor;

typedef struct EfBPlayer {
    u8 pad0[0x4C];
    s16 unk4C;
    u8 pad4E[2];
    s16 unk50;
    u8 pad52[0x36];
    EfBActor *unk88;
    u8 pad8C[0x3C];
    s16 unkC8;
    u8 padCA[0x126];
    s32 unk1F0;
    u8 pad1F4[0xA];
    s16 unk1FE;
} EfBPlayer;
typedef struct EfBCamera {
    u8 pad0[0x2A0];
    s32 unk2A0;
    u8 pad2A4[4];
    s32 unk2A8;
    u8 pad2AC[0x44];
} EfBCamera;

#define EFB_C ((EfBCamera *)D_807FC924)


#define EFB_P ((EfBPlayer *)D_807FD580)

void func_806CF42C(Actor *);
void func_8072DB68(s32);
void func_80026004();
void func_806F1250(Actor *);

void func_806EBCF0(void) {
    ((EfBActor *)D_807FBB48)->unk154 = 7;
    ((EfBActor *)D_807FBB48)->unk155 = 0;
    func_80614E78(D_807FBB48, 0x7A);
    EFB_P->unk50 = 0;
    EFB_P->unk4C = -1;
    EFB_P->unk88 = (EfBActor *)EFB_C[D_807FC929].unk2A0;
    D_807FBB48->unk60 &= 0xFFFBFFFF;
    ((EfBActor *)D_807FBB48)->unkB8 = 0.0f;
}

void func_806EBDAC(void) {
    D_807FD580->unk1F0 |= 8;
}

void func_806EBDC4(void) {
    ((EfBActor *)D_807FBB48)->unk154 = 0x69;
    ((EfBActor *)D_807FBB48)->unk155 = 0;
    actorScriptStart(D_807FBB48, 0);
    func_80614D48(D_807FBB48, 0.0f, 0.0f);
    EFB_P->unk50 = 0;
    EFB_P->unk4C = -1;
    D_807FBB48->unk60 &= 0xFEFFFFFF;
    EFB_P->unk88 = (EfBActor *)EFB_C[D_807FC929].unk2A0;
}

void func_806EBE8C(void) {
    EfBActor *actor;
    s32 arg;

    actor = EFB_P->unk88;
    arg = actor->unk178;
    if (actor->unk154 < 3) {
        func_80026004(arg, 0x1E, 0x3F800000);
    }
}

void func_806EBED0(void) {
    EfBActor *actor;

    actor = EFB_P->unk88;
    actor->unkC0 += 200.0f;
    actor = EFB_P->unk88;
    if (actor->unkC0 > 200.0f) {
        actor->unkC0 = 200.0f;
    }
    func_8072DB68(3);
}

void func_806EBF34(void) {
    EfBActor *actor;

    actor = EFB_P->unk88;
    actor->unkC0 += 300.0f;
    func_8072DB68(3);
}

void func_806EBF74(void) {
    func_806F1250(D_807FBB48);
    EFB_P->unk1FE = EFB_C[D_807FC929].unk2A8;
}

void func_806EBFD0(void) {
    actorScriptStart(D_807FBB48, 0x1A);
    ((EfBActor *)D_807FBB48)->unk154 = 0x78;
    ((EfBActor *)D_807FBB48)->unk155 = 0;
}

void func_806EC014(void) {
    func_806CF42C(D_807FBB40);
    func_806CFF9C(D_807FBB40);
}

typedef struct EfN2ModelSlot {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    u8 padC[0x84];
} EfN2ModelSlot;

typedef struct EfN2PlayerState {
    u8 pad0[0x10];
    s16 unk10;
    s16 unk12;
    s16 unk14;
} EfN2PlayerState;

extern EfN2ModelSlot *D_807F6000;
extern s16 D_807539DC[];
extern s16 D_807539EC[];
void func_80614D00(Actor *, f32, f32);
void func_806F0C18(void *);
void actorClearMovementFlags(void *);
s32 hashTableLookup(s32);
void camStartPath(Actor *, s32, s32);
void func_80613C48(Actor *, s32, f32, f32);
void func_8067B238(Actor *, Actor *, f32);
void func_80613AF8(Actor *, s32, f32, f32);

void func_806EC044(void) {
    f32 speed;

    speed = 1.0f;
    func_806F0C18(D_807FBB40);
    D_807FBB48->unk154 = 0x6C;
    D_807FBB48->unk155[0] = 0;
    actorScriptStart(D_807FBB48, 0x3B);
    if (D_8074E77C[0] == 0) {
        speed = 0.5f;
    }
    func_80614D00(D_807FBB48, speed, 0.0f);
    actorClearMovementFlags(D_807FBB48);
    D_807FBB48->unk7C = D_807F6000[hashTableLookup(D_807FBB48->unk10C)].unk0;
    D_807FBB48->unk80 = D_807F6000[hashTableLookup(D_807FBB48->unk10C)].unk4 + 5.0f;
    D_807FBB48->unk84 = D_807F6000[hashTableLookup(D_807FBB48->unk10C)].unk8;
    *(s16 *)((u8 *)D_807FBB48 + 0xE4) = 0;
    *(s16 *)((u8 *)D_807FBB48 + 0xE8) = 0;
    camStartPath(D_807FBB48, 0, 1);
    slotQueueUpdate(0, 1, 0);
}

void func_806EC1A8(void) {
    s32 animation;

    *(u32 *)((u8 *)EfA_P->unk104->unk174 + 0xAC) |= 4;
    D_807FBB48->unk154 = 0x6D;
    D_807FBB48->unk155[0] = 0;
    actorScriptStart(D_807FBB48, 0);
    EFB_P->unk50 = 0;
    EFB_P->unk4C = -1;
    D_807FBB48->unk60 &= ~1;
    if (D_8076A0A8 == 0x27) {
        D_807FBB48->unk144 = 1;
    }
    EFB_P->unk88 = (EfBActor *)EFB_C[D_807FC929].unk2A0;
    if (D_807FBB48->unk58 == 2) { animation = 0x53; } else { animation = 0x1C7; } func_80613C48(D_807FBB48, (s16)animation, 0.0f, 0.0f); // FAKE: one source line steers the scheduler (li at,2 after mfc1)
}

void func_806EC2CC(void) {
    Actor *actor;

    D_807FBB48->unk154 = 0x75;
    D_807FBB48->unk155[0] = 0;
    actorScriptStart(D_807FBB48, 0);
    EFB_P->unk50 = 0;
    EFB_P->unk4C = -1;
    D_807FBB48->unk60 &= ~1;
    EFB_P->unk88 = (EfBActor *)EFB_C[D_807FC929].unk2A0;
    actor = (Actor *)EFB_P->unk88;
    func_8067B238(D_807FBB48, actor, actor->unk4->unk34);
    D_807FBB48->unk144 = 1;
    func_80613C48(D_807FBB48, 0x22A, 0.0f, 0.0f);
}

void func_806EC3BC(void) {
    ((EfN2PlayerState *)D_807FD580)->unk12 = D_807539EC[D_807FD584];
    ((EfN2PlayerState *)D_807FD580)->unk14 = D_807FBB40->unkE6;
    ((EfN2PlayerState *)D_807FD580)->unk10 = D_807539DC[D_807FD584];
    D_807FBB40->unk154 = 0x4F;
    D_807FBB40->unk155[0] = 1;
    if (D_807FBB40->unkC0 > 0.0f) {
        D_807FBB40->unkC0 = 0.0f;
    }
    func_80614E78(D_807FBB40, 0x36);
    func_80613AF8(D_807FBB40, 0x31, 0.0f, 8.0f);
    func_80614D00(D_807FBB40, 0.5f, 0.0f);
}

typedef struct EfN3PlayerState {
    u8 pad0[0x10];
    s16 unk10;
    u8 pad12[0xA];
    f32 unk1C;
    u8 pad20[0xC];
    f32 unk2C;
    f32 unk30;
    u8 pad34[4];
    f32 unk38;
    u8 pad3C[0xC];
    s16 unk48;
    s16 unk4A;
    s16 unk4C;
    s16 unk4E;
    s16 unk50;
    f32 unk54;
    s32 unk58;
    u8 pad5C[0x94];
    f32 unkF0;
    u8 padF4[0x18];
    s8 unk10C;
    u8 pad10D[0xA3];
    u8 pad1B0[8];
} EfN3PlayerState;

typedef struct EfN3Actor {
    u8 pad0[0x58];
    s32 unk58;
    u8 pad5C[0x24];
    f32 unk80;
    u8 pad84[0x1C];
    f32 unkA0;
    u8 padA4[8];
    f32 unkAC;
    u8 padB0[8];
    f32 unkB8;
    u8 padBC[4];
    f32 unkC0;
    u8 padC4[0x2A];
    s16 unkEE;
    u8 padF0[4];
    s16 unkF4;
    u8 padF6[0x5E];
    u8 unk154;
    u8 unk155;
} EfN3Actor;


typedef struct EfN3Camera {
    u8 pad0[0x2C0];
    u8 unk2C0;
    u8 pad2C1[0x2F];
} EfN3Camera;

#define EFN3_P ((EfN3PlayerState *)D_807FD580)
#define EFN3_A40 ((EfN3Actor *)D_807FBB40)
#define EFN3_A48 ((EfN3Actor *)D_807FBB48)
#define EFN3_C ((EfN3Camera *)D_807FC924)

extern f32 D_807531C4[];
extern f32 D_807531FC[];
extern f32 D_807534E4[];
extern f32 D_80753500[];
extern s16 D_8075351C[];
extern f32 D_80753908[];
extern f32 D_80753924[];
extern f32 D_80753940[];
extern f32 D_80753D70[];
extern f32 D_80753D8C[];
extern s32 D_80767CC0;
extern f32 D_80753250[];
extern s16 D_8075388C[];
extern s16 D_807538D8[];
extern s16 D_807538E8[];
extern s16 D_807538F8[];
extern f32 D_80753988[];
extern s16 D_807539FC[];
extern f32 D_80753A5C[];
void func_806CF398(Actor *);

void func_806EC4AC(void) {
    f32 temp_fa0;
    f32 temp_ft4;
    f32 temp_fv0;
    f32 temp_fv0_2;
    f32 temp_fv0_3;
    f32 temp_fv1;
    f32 var_fa1;
    f32 var_fs0;
    f32 var_ft5;
    f32 var_ft5b;

    func_806CF398(D_807FBB48);
    temp_fv0 = D_80753A5C[D_807FD584];
    if (temp_fv0 > 0.0f) {
        var_fs0 = temp_fv0;
    } else {
        var_fs0 = -temp_fv0;
    }
    temp_ft4 = EFN3_A48->unkAC;
    temp_fv0_2 = D_807538D8[D_807FD584];
    var_ft5 = EFN3_A48->unkA0 - temp_ft4;
    if (temp_fv0_2 < var_ft5) {
        var_ft5 = temp_fv0_2;
    }
    temp_fa0 = D_807538E8[D_807FD584] + ((D_807538F8[D_807FD584] - D_807538E8[D_807FD584]) * (var_ft5 / temp_fv0_2));
    temp_fa0 -= (temp_ft4 - D_8075388C[D_807FD584]) - EFN3_A48->unk80;
    temp_fa0 *= 40.0f;
    var_ft5 *= 40.0f;
    temp_fv0_2 *= 40.0f;
    if (temp_fa0 > 0.0f) {
        var_fa1 = EFN3_A48->unkC0;
        var_fa1 = (f32)((f64)var_fa1 * (0.5 + (f64)(var_ft5 / (2 * temp_fv0_2))));
        var_ft5b = (var_fa1 * var_fa1) / (2 * temp_fa0);
        if (var_ft5b < var_fs0) {
            var_ft5b = var_fs0;
        }
    } else {
        var_fa1 = 0.0f;
        var_ft5b = var_fs0;
    }
    EFN3_A48->unkC0 = var_fa1;
    EFN3_P->unk1C = var_ft5b;
    EFN3_P->unk10 = 0;
    EFN3_P->unk30 = D_80753250[D_807FD584];
    temp_fv0_3 = EFN3_A40->unkB8;
    temp_fv1 = D_80753988[D_807FD584];
    if (temp_fv0_3 < temp_fv1) {
        EFN3_A40->unkB8 = temp_fv0_3;
    } else {
        EFN3_A40->unkB8 = temp_fv1;
    }
    EFN3_A48->unk154 = 0x4E;
    EFN3_A48->unk155 = 0;
    func_80614E78(D_807FBB40, 0x35);
    EFN3_P->unk48 = D_807539FC[D_807FD584];
}


void func_806EC708(void) {
    EFN3_A48->unk154 = 0x51;
    EFN3_A48->unk155 = 0;
    EFN3_P->unk54 = D_80753908[D_807FD584];
    EFN3_P->unk50 = 0;
    EFN3_P->unk38 = D_807531FC[D_807FD584];
    EFN3_P->unk2C = D_80753924[D_807FD584];
    EFN3_P->unk30 = D_80753940[D_807FD584];
    func_80614E78(D_807FBB48, 0x3E);
    func_80614D00(D_807FBB40, 1.0f, 0.0f);
    EFN3_P->unk58 = D_80767CC0 - 0x1E;
}

void func_806EC800(void) {
    f32 current;
    f32 limit;

    EFN3_A48->unk154 = 0x50;
    EFN3_A48->unk155 = 0;
    EFN3_A40->unkC0 = -10.0f;
    EFN3_P->unk50 = 0;
    current = EFN3_A40->unkB8;
    limit = D_807531C4[D_807FD584];
    if (current < limit) {
        EFN3_A40->unkB8 = current;
    } else {
        EFN3_A40->unkB8 = limit;
    }
    EFN3_P->unk38 = D_807531FC[D_807FD584];
    func_80614E78(D_807FBB48, 0x3C);
}

typedef struct EfN3bTarget {
    u8 pad0[0x54];
    s32 unk54;
    s32 unk58;
} EfN3bTarget;

typedef struct EfN3bPlayerState {
    u8 pad0[0x1B0];
    EfN3bTarget *unk1B0;
    s32 unk1B4;
} EfN3bPlayerState;

#define EFN3B_P ((EfN3bPlayerState *)D_807FD580)

extern Actor *D_807FBB90;

void func_806EC8C4(void) {
    EFN3B_P->unk1B0 = (EfN3bTarget *)D_807FBB90;
    EFN3B_P->unk1B4 = EFN3B_P->unk1B0->unk54;
    switch ((u32)EFN3B_P->unk1B0->unk58) {
    case 0x3D:
    case 0x3F:
    case 0x40:
    case 0x41:
    case 0x42:
    case 0x55:
    case 0x82:
        actorScriptStart(D_807FBB48, 0x1C8);
        break;
    default:
        func_80614E78(D_807FBB48, 0x2B);
        break;
    }
    EFN3_A48->unk154 = 0x47;
    EFN3_A48->unk155 = 0;
}

void func_806EC994(void) {
    func_80614E78(D_807FBB48, 8);
    func_80614D00(D_807FBB48, 1.0f, 0.0f);
    func_80613AF8(D_807FBB48, 0x2E, 0.0f, 6.0f);
    EFN3_A48->unk154 = 0x46;
    EFN3_A48->unk155 = 0;
    EFN3_P->unk38 = D_807534E4[D_807FD584];
    EFN3_P->unk2C = D_80753500[D_807FD584];
    EFN3_P->unk48 = D_8075351C[D_807FD584];
    EFN3_P->unk4C = -1;
}

void func_806ECA74(void) {
    ((EfBActor *)D_807FBB40)->unk154 = 0x24;
    ((EfBActor *)D_807FBB40)->unk155 = 0;
    actorScriptStart(D_807FBB40, 0x1B2);
    EFB_P->unkC8 = 0x32;
}

void func_80614D90(Actor *);

void func_806ECAC4(void) {
    f32 value;

    if (EFN3_C[D_807FC929].unk2C0 == 1) {
        value = D_80753D70[D_807FD584];
    } else {
        value = D_80753D8C[D_807FD584];
    }
    EFN3_A48->unk154 = 0x5B;
    EFN3_A48->unk155 = 0;
    EFN3_P->unk10C = (s8)value;
    EFN3_A48->unk80 = EFN3_P->unkF0 - EFN3_P->unk10C;
    EFN3_A48->unkEE = EFN3_A48->unkF4 + 0x14;
    EFN3_A48->unkC0 = 0.0f;
    func_80614E78(D_807FBB48, 0x75);
    func_80614D90(D_807FBB48);
}


void func_806ECBD4(void) {
    D_807FBB48->unk6A |= 0x40;
    D_807FBB48->unk64 &= ~0x2000;
    D_807FBB48->unk154 = 0x57;
    D_807FBB48->unk155[0] = 0;
    func_80614E78(D_807FBB48, 0x69);
    func_80614D90(D_807FBB48);
}

typedef struct EfN4PlayerState {
    u8 pad0[0x3C];
    s16 unk3C;
    u8 pad3E[0xA];
    s16 unk48;
    u8 pad4A[6];
    s16 unk50;
    u8 pad52[2];
    f32 unk54;
    u8 pad58[0xC];
    s16 unk64;
    u8 pad66[2];
    f32 unk68;
    u8 pad6C[0x20];
    u8 unk8C;
    u8 pad8D[0x2F];
    s16 unkBC;
    s16 unkBE;
    u8 padC0[0x44];
    Actor *unk104;
    u8 pad108[0x1C];
    f32 unk124;
} EfN4PlayerState;

typedef struct EfN4Cam {
    u8 pad0[0x2A0];
    Actor *unk2A0;
    u8 pad2A4[0x1C];
    u8 unk2C0;
    u8 pad2C1[0x2F];
} EfN4Cam;

#define EfN4PS ((EfN4PlayerState *)D_807FD580)
#define EfN4CamBlocks ((EfN4Cam *)D_807FC924)

typedef struct EfN4ActorC0 {
    u8 pad0[0xC0];
    f32 unkC0;
} EfN4ActorC0;

extern s32 D_807FBB68;
extern f32 D_807535CC[];
extern s16 D_8075380C[];
void camStartBlendRamp(void *, s32);
s16 actorListFindIdByActor(Actor *);
void func_806CFE7C(void);
void func_806CA2AC(void);



void func_806ECC48(void) {
    void *callback;

    callback = EfN4PS->unk104->unk174;
    D_807FBB48->unk6A |= 0x40;
    D_807FBB48->unk64 &= ~0x2000;
    D_807FBB48->unk154 = 0x59;
    D_807FBB48->unk155[0] = 0;
    func_80614E78(D_807FBB48, 0x70);
    func_80614D90(D_807FBB48);
    camStartBlendRamp(callback, 0x14);
}

void func_806ECCDC(void) {
    void *callback;

    callback = EfN4PS->unk104->unk174;
    D_807FBB40->unk154 = 0x17;
    D_807FBB40->unk155[0] = 0;
    if (D_807FBB68 & 2) {
        EfN4PS->unk54 = D_807535CC[D_807FD584] * 1.3;
    } else {
        EfN4PS->unk54 = D_807535CC[D_807FD584];
    }
    D_807FBB48->unkB8 = EfN4PS->unk124;
    EfN4PS->unk50 = 0;
    EfN4PS->unk3C = 0xA;
    func_80614E78(D_807FBB40, 0x10);
    camStartBlendRamp(callback, 0x14);
}


s32 func_806EB400(Actor *);
void func_806EEAF8(s16);

void func_806ECDD4(void) {
    s32 value;

    if (func_806EB400(D_807FBB48) != 0) {
        value = 1;
        if (D_807FBB68 & 2) {
            value = 0;
        } else {
            value = 1;
        }
        func_806EEAF8((s16)value);
    }
}

void func_806ECE2C(void) {
    if ((D_807FC928 >= 2) || (D_807FBB48->unk58 != 6) || (EfN4CamBlocks[D_807FC929].unk2C0 == 1)) {
        ((EfN4ActorC0 *)D_807FBB48)->unkC0 = 260.0f;
        func_806CFE7C();
        EfN4PS->unk50 = 0;
        EfN4PS->unk48 = 0x64;
        func_80614E78(D_807FBB48, 0x1F);
        func_80614D00(D_807FBB48, 1.0f, 0.0f);
        D_807FBB48->unk154 = 0x30;
        D_807FBB48->unk155[0] = 0;
        func_806CF42C(D_807FBB48);
    }
}


typedef struct EfCActorC0 {
    u8 pad0[0xC0];
    f32 unkC0;
} EfCActorC0;

typedef struct EfCPlayer48 {
    u8 pad0[0x50];
    s16 unk50;
} EfCPlayer48;


void func_806ECF1C(void) {
    ((EfCActorC0 *)D_807FBB48)->unkC0 = 260.0f;
    func_806CFE7C();
    ((EfCPlayer48 *)D_807FD580)->unk50 = 0;
    func_80614E78(D_807FBB48, 0x20);
    func_80614D00(D_807FBB48, 1.0f, 0.0f);
    D_807FBB48->unk154 = 0x30;
    D_807FBB48->unk155[0] = 0;
    func_806CF42C(D_807FBB48);
}

typedef struct EfCPlayer68 {
    u8 pad0[0x50];
    s16 unk50;
    u8 pad52[0x16];
    f32 unk68;
} EfCPlayer68;

extern s16 D_807537FC[];
extern s16 D_8075383C[];
extern s16 D_8075384C[];

void func_806ECF9C(void) {
    ((EfCPlayer68 *)D_807FD580)->unk50 = D_807537FC[D_807FD584];
    ((EfCPlayer68 *)D_807FD580)->unk68 += D_8075383C[D_807FD584];
    if (D_8075384C[D_807FD584] < ((EfCPlayer68 *)D_807FD580)->unk68) {
        ((EfCPlayer68 *)D_807FD580)->unk68 = D_8075384C[D_807FD584];
    }
    ((EfCActorC0 *)D_807FBB48)->unkC0 = 0.0f;
    ((EfCPlayer68 *)D_807FD580)->unk50 = 0;
}

void func_806ED050(void) {
    if ((D_807FBB40->unk154 != 2) && (D_8074E77C[D_807FC929] == 6)) {
        D_807FBB40->unk154 = 0x29;
        D_807FBB40->unk155[0] = 0;
        func_80614E78(D_807FBB40, 0x3F);
        EfN4PS->unk64 = 0;
        EfN4PS->unk68 = D_8075380C[D_807FD584];
    }
}


void func_806ED0FC(void) {
    Actor *target;

    func_806CA2AC();
    func_806CF398(D_807FBB48);
    EfN4PS->unk8C = 0;
    func_806F0C18(D_807FBB40);
    sfxStopSlotSound(D_807FBB40, 0);
    sfxStopSlotSound(D_807FBB40, 1);
    func_80614E78(D_807FBB48, 0x21);
    target = EfN4CamBlocks[D_807FC929].unk2A0;
    if (target != NULL) {
        EfN4PS->unkBC = target->unk58;
        EfN4PS->unkBE = actorListFindIdByActor(EfN4CamBlocks[D_807FC929].unk2A0);
    } else {
        EfN4PS->unkBC = 0;
        EfN4PS->unkBE = -1;
    }
    if (D_807FBB40->unk6A & 4) {
        D_807FBB48->unk154 = 0x43;
        D_807FBB48->unk155[0] = 0;
        return;
    }
    D_807FBB48->unk154 = 0x42;
    D_807FBB48->unk155[0] = 0;
}

typedef struct EfN8PlayerD4 {
    u8 pad0[0xD4];
    s16 unkD4;
} EfN8PlayerD4;
extern s16 D_807530B0[];
s32 sfxPlayFromActorWithAltitudeCheck(Actor *, s16, u8, s16, u8);

typedef struct EfdAPlayer {
    u8 pad0[0x88];
    Actor *unk88;
} EfdAPlayer;

void func_806ED244(void) {
    Actor *camTarget;
    Actor *target;
    f32 zero;
    f32 v;

    target = ((EfdAPlayer *)D_807FD580)->unk88;
    zero = 0.0f;
    if (target->unkB8 >= zero) {
        func_8072DB68(3);
        target = ((EfdAPlayer *)D_807FD580)->unk88;
    }
    camTarget = ((EfAQueuedCall *)D_807FC924)[D_807FC929].unk2A0;
    if (camTarget != NULL) {
        if (camTarget->unkB8 != zero) {
            v = camTarget->unkB8 > zero ? camTarget->unkB8 : -camTarget->unkB8;
            target->unkB8 = (f32)(2.0 * (f64)v);
        } else {
            v = target->unkB8 > zero ? target->unkB8 : -target->unkB8;
            target->unkB8 = v < 50.0f ? -50.0f : -(target->unkB8 > zero ? target->unkB8 : -target->unkB8);
        }
    } else {
        v = target->unkB8 > zero ? target->unkB8 : -target->unkB8;
        target->unkB8 = v < 50.0f ? -50.0f : -(target->unkB8 > zero ? target->unkB8 : -target->unkB8);
    }
    actorScriptStart(((EfdAPlayer *)D_807FD580)->unk88, 0x292);
    if (D_807FD580 && D_807FD580) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
    if (D_807FBB48->unk154 != 9) {
        func_80614E78(D_807FBB48, 0x83);
    }
}


void func_806ED420(void) {
    f32 divisor;
    u8 character;

    if (((EfN8PlayerD4 *)D_807FD580)->unkD4 == 0) {
        func_806CA2AC();
        func_8072DB68(3);
        character = D_8074E77C[D_807FC929];
        divisor = 2.0f;
        if (character != 2) {
            if (character == 3) {
                sfxPlayFromActorWithAltitudeCheck(D_807FBB48, 0xB9, 0xFF, 0x7F, 0x14);
            }
        } else {
            sfxPlayFromActorWithAltitudeCheck(D_807FBB48, 0xD2, 0xFF, 0x7F, 0x14);
        }
        ((EfN8PlayerD4 *)D_807FD580)->unkD4 = D_807530B0[D_807FD584];
        D_807FBB48->unkB8 = D_807FBB48->unkB8 / divisor;
    }
}

s32 flagGet(s16, s32);
void flagSet(s16, s32, s32);

void func_806ED508(u16 arg0) {
    u16 ev;
    s16 anim;

    switch (arg0) {
    case 0x12:
        ev = 0x16D;
        anim = 0x23;
        break;
    case 0x81:
        ev = 0x16E;
        anim = 0x24;
        break;
    }
    if (flagGet(ev, 0) == 0) {
        if (arg0 == 0x81) {
            D_807FBB48->unkB8 = 0.0f;
        }
        camStartPath(NULL, anim, 5);
        flagSet(ev, 1, 0);
    }
}

void func_806ED5C0(Actor *arg0) {
    s16 id;
    u16 state;
    s32 ev;

    state = arg0->unk58;
    id = actorListFindIdByActor(arg0);
    switch (D_8076A0A8) {
    case 26:
        if (id == 0x11) {
            return;
        }
        break;
    case 48:
        if (id == 0x17) {
            return;
        }
        break;
    }
    switch (state) {
    case 0x19:
        ev = 0x169;
        break;
    case 0x28:
        ev = 0x168;
        break;
    case 0x39:
        ev = 0x16B;
        break;
    case 0x38:
        ev = 0x16A;
        break;
    default:
        return;
    }
    if (flagGet(ev, 0) == 0) {
        camStartPath(NULL, 0x16, 5);
        flagSet(ev, 1, 0);
    }
}

typedef struct EfL1PlayerState {
    u8 pad0[0x10];
    s16 unk10;
    s16 unk12;
    s16 unk14;
    u8 pad16[0x22];
    f32 unk38;
    u8 pad3C[0x14];
    s16 unk50;
    u8 pad52[0x1A];
    f32 unk6C;
    s16 unk70;
    u8 pad72[2];
    f32 unk74;
    u8 pad78[0x14];
    u8 unk8C;
    u8 pad8D[0x161];
    s16 unk1EE;
    s32 unk1F0;
    s32 unk1F4;
} EfL1PlayerState;

typedef struct EfL1Actor {
    u8 pad0[0x58];
    u32 unk58;
    u8 pad5C[4];
    s32 unk60;
    u8 pad64[6];
    u16 unk6A;
    u8 pad6C[0x14];
    f32 unk80;
    u8 pad84[0x28];
    f32 unkAC;
    u8 padB0[8];
    f32 unkB8;
    f32 unkBC;
    f32 unkC0;
    u8 padC4[0x22];
    s16 unkE6;
    u8 padE8[6];
    s16 unkEE;
    u8 padF0[0x38];
    s16 unk128;
    u8 pad12A[0x2A];
    u8 unk154;
    u8 unk155;
} EfL1Actor;

typedef struct EfL1CamBlock {
    u8 pad0[0x2A0];
    EfL1Actor *unk2A0;
    u8 pad2A4[0x4C];
} EfL1CamBlock;

typedef struct EfL1Global568 {
    u8 pad0[2];
    u8 unk2;
} EfL1Global568;

#define EfL1PS ((EfL1PlayerState *)D_807FD580)
#define EfL1Cam ((EfL1CamBlock *)D_807FC924)
#define EfL1G568 ((EfL1Global568 *)D_807FD568)
#define EfL1A40 ((EfL1Actor *)D_807FBB40)
#define EfL1A48 ((EfL1Actor *)D_807FBB48)

extern void *D_807FD568;
Actor *actorFindByType(s32);
void actorSpawnChildActor(Actor *);
void func_8068696C(Actor *);
void func_806C8D20(Actor *);
s32 func_806C8DE0(s32);
void func_806C8E58(s16);
void func_806CFF1C(Actor *);
void func_806D0468(Actor *, s32);
void func_806ED508(u16);
void func_806ED5C0(Actor *);

void func_806ED6B0(void) {
    u8 flag;
    s32 selector;
    s32 value;

    flag = 0;
    EfL1A48->unkB8 = EfL1PS->unk6C;
    EfL1A48->unkEE = EfL1PS->unk70;
    EfL1A48->unkE6 = EfL1PS->unk70;
    EfL1A48->unkC0 = EfL1PS->unk74;
    func_80614D00(D_807FBB48, 1.0f, 0.0f);
    if (EfL1Cam[D_807FC929].unk2A0 == NULL) {
        EfL1A48->unk154 = 0x44;
        EfL1A48->unk155 = 0;
        func_80614E78(D_807FBB48, 0x22);
        EfL1PS->unk50 = 0x14;
        func_806CFE7C();
    } else {
        switch (EfL1Cam[D_807FC929].unk2A0->unk58) {
        case 0x17:
        case 0xA7:
            EfL1A48->unk154 = 0x45;
            EfL1A48->unk155 = 0;
            func_80614E78(D_807FBB48, 0x22);
            EfL1PS->unk50 = 0x14;
            func_806CFE7C();
            break;
        case 0x11:
            EfL1A48->unk154 = 0x44;
            EfL1A48->unk155 = 0;
            func_80614E78(D_807FBB48, 0x22);
            EfL1PS->unk50 = 0x14;
            func_806CFE7C();
            break;
        case 0x1C:
        case 0x6B:
        case 0x86:
            if (actorFindByType(0x25) != NULL) {
                EfL1A48->unk154 = 0x63;
                EfL1A48->unk155 = 0;
                actorScriptStart(D_807FBB48, 0x7D);
                EfL1A48->unkB8 = 0.0f;
                EfL1PS->unk38 = 300.0f;
                flag = 1;
                slotQueueUpdate(5, 1, 0);
                break;
            }
        case 0x62:
        case 0x88:
        case 0x89:
            func_806C8D20(D_807FBB48);
            func_806CFF1C(D_807FBB40);
            func_806CFE7C();
            break;
        case 0x19:
        case 0x28:
        case 0x60:
            if (EfL1Cam[D_807FC929].unk2A0->unk58 == 0x28) {
                selector = 0;
            } else {
                selector = 2;
            }
            func_806D0468(D_807FBB48, selector & 0xFF);
            if (EfL1A48->unk58 == 6) {
                EfL1A48->unk60 &= 0xFFFF7FFF;
            } else {
                EfL1A48->unk60 |= 0x8000;
            }
            func_806CFF9C(D_807FBB48);
            break;
        case 0x39:
            EfL1PS->unk1F0 |= 0x10;
            EfL1A48->unk60 &= 0xFFFF7FFF;
            EfL1A48->unk128 = 0x7F;
            func_8068696C(D_807FBB48);
            func_806CFF1C(D_807FBB40);
            func_806CFE7C();
            break;
        case 0x38:
            EfL1PS->unk1F0 |= 0x20;
            EfL1A48->unk154 = 0x41;
            EfL1A48->unk155 = 0;
            actorScriptStart(D_807FBB48, 0x156);
            EfL1A48->unkB8 = 0.0f;
            EfL1PS->unk50 = 4;
            func_806CFECC();
            break;
        case 0x31:
            EfL1A48->unk154 = 0x63;
            EfL1A48->unk155 = 0;
            actorScriptStart(D_807FBB48, 0x7D);
            EfL1A48->unkB8 = 0.0f;
            EfL1PS->unk38 = 300.0f;
            break;
        case 0x12:
        case 0x81:
            EfL1PS->unk1EE = EfL1A48->unk58;
            if (EfL1Cam[D_807FC929].unk2A0->unk58 == 0x12) {
                func_806C8E58(8);
                EfL1A48->unk154 = 0xC;
                EfL1A48->unk155 = 0;
                func_80614E78(D_807FBB48, 9);
                EfL1A48->unkB8 = 0.0f;
            } else {
                func_806C8E58(9);
                if (EfL1A48->unkAC < EfL1A48->unk80) {
                    EfL1A48->unk154 = 0x82;
                    EfL1A48->unk155 = 0;
                } else {
                    EfL1A48->unk154 = 0x7F;
                    EfL1A48->unk155 = 0;
                }
                actorScriptStart(D_807FBB48, 0x317);
                EfL1A48->unkB8 = 100.0f;
            }
            EfL1PS->unk50 = 4;
            func_806CFECC();
            func_806ED508(*(u16 *)((u8 *)EfL1Cam[D_807FC929].unk2A0 + 0x5A));
            break;
        case 0x84:
            value = func_806C8DE0(D_807FC929);
            if (value != D_8074E77C[D_807FC929]) {
                func_806C8E58((s16)(value + 2));
            }
            actorSpawnChildActor(D_807FBB48);
            break;
        }
    }
    if (((EfL1Cam[D_807FC929].unk2A0 != NULL) && (EfL1Cam[D_807FC929].unk2A0->unk58 == 0x31)) || (flag != 0)) {
        if (EfL1G568->unk2 & 1) {
            if (EfL1PS->unk8C != 0) {
                EfL1PS->unk1F4 |= 4;
            } else {
                EfL1PS->unk1F4 &= ~4;
            }
            EfL1PS->unk8C = 1;
            func_806F0D68(D_807FBB48);
        }
    } else {
        func_806F0C18(D_807FBB40);
    }
    if (EfL1Cam[D_807FC929].unk2A0 != NULL) {
        func_806ED5C0((Actor *)EfL1Cam[D_807FC929].unk2A0);
    }
    if ((EfL1A48->unk6A & 4) && (EfL1Cam[D_807FC929].unk2A0->unk58 != 0x81)) {
        EfL1PS->unk12 = D_807539EC[D_807FD584];
        EfL1PS->unk14 = EfL1A40->unkE6;
        EfL1PS->unk10 = (s16)((f64)D_807539DC[D_807FD584] * 0.5);
        EfL1A40->unk154 = 0x4F;
        EfL1A40->unk155 = 1;
        if (EfL1A40->unkC0 > 0.0f) {
            EfL1A40->unkC0 = 0.0f;
        }
        func_80614E78(D_807FBB40, 0x36);
        func_80613AF8(D_807FBB40, 0x31, 0.0f, 8.0f);
        func_80614D00(D_807FBB40, 0.5f, 0.0f);
    }
}


typedef struct EfCPlayerState {
    u8 pad0[0x1EE];
    s16 unk1EE;
} EfCPlayerState;

void func_806C8E58(s16);

void func_806EDFF8(void) {
    func_806C8E58(((EfCPlayerState *)D_807FD580)->unk1EE);
    func_806CFF9C(D_807FBB48);
}


void func_806EE02C(void) {
    func_806CF398(D_807FBB48);
    D_807FBB48->unk154 = 0x55;
    D_807FBB48->unk155[0] = 0;
}

typedef struct EfCPlayerState06 {
    u8 pad0[0x38];
    f32 unk38;
    u8 pad3C[0x14];
    s16 unk50;
    u8 pad52[0x36];
    Actor *unk88;
} EfCPlayerState06;

typedef struct EfCCamBlock {
    u8 pad0[0x2A0];
    Actor *unk2A0;
    u8 pad2A4[0x4C];
} EfCCamBlock;

#define EfCCam ((EfCCamBlock *)D_807FC924)

void func_806EE06C(void) {
    func_806CF398(D_807FBB48);
    D_807FBB48->unk154 = 0x56;
    D_807FBB48->unk155[0] = 0;
    func_80614E78(D_807FBB48, 0x87);
    ((EfCPlayerState06 *)D_807FD580)->unk50 = 0;
    ((EfCPlayerState06 *)D_807FD580)->unk38 = 0.0f;
    ((EfCPlayerState06 *)D_807FD580)->unk88 = EfCCam[D_807FC929].unk2A0;
}

typedef struct EfCPlayerD4 {
    u8 pad0[0xD4];
    s16 unkD4;
} EfCPlayerD4;

s32 func_806C9974(u8, s8);

void func_806EE10C(void) {
    if (func_806EB400(D_807FBB48) != 0) {
        func_806CA2AC();
        if (func_806C9974(D_807FC929, -1) != 0) {
            if (D_807FBB48->unk6A & 4) {
                func_80614E78(D_807FBB48, 0x29);
            } else {
                func_80614E78(D_807FBB48, 0x27);
            }
            D_807FBB48->unk154 = 0x36;
            D_807FBB48->unk155[0] = 0;
        }
        ((EfCPlayerD4 *)D_807FD580)->unkD4 = D_807530B0[D_807FD584];
    }
}

typedef struct EfCPlayer1AC {
    u8 pad0[0x1AC];
    s32 unk1AC;
    s32 unk1B0;
} EfCPlayer1AC;

typedef struct EfCActorC0S32 {
    u8 pad0[0xC0];
    s32 unkC0;
} EfCActorC0S32;

void func_8067A784(Actor *, s32, s16, s32, s32);

void func_806EE1C4(void) {
    s32 value = ((EfCPlayer1AC *)D_807FD580)->unk1AC;

    if (value != 0) {
        func_8067A784(D_807FBB40, value, D_807FBB48->unkE6,
                      ((EfCActorC0S32 *)D_807FBB40)->unkC0, (s32)D_807FBB40->unkB8);
        ((EfCPlayer1AC *)D_807FD580)->unk1AC = 0;
        ((EfCPlayer1AC *)D_807FD580)->unk1B0 = 0;
    }
    func_806CA2AC();
    func_80614E78(D_807FBB40, 0x1C);
    D_807FBB48->unk154 = 0x20;
    D_807FBB48->unk155[0] = 0;
}


void func_806EE26C(void) {
    func_806CA2AC();
    func_80614E78(D_807FBB40, 0x1C);
    D_807FBB48->unk154 = 0x21;
    D_807FBB48->unk155[0] = 0;
}

typedef struct EfCPlayer104 {
    u8 pad0[0x104];
    void *unk104;
} EfCPlayer104;


void func_806EE2B8(void) {
    s32 value = 1;
    s8 selector;
    Actor *target;

    if (func_806EB400(D_807FBB48) != 0) {
        selector = -1;
        func_806CA2AC();
        target = EfCCam[D_807FC929].unk2A0;
        if ((target != NULL) && (target->unk58 == 0x123)) {
            selector = -2;
        }
        if (func_806C9974(D_807FC929, selector) != 0) {
            value = 0;
            if (D_807FBB48->unk6A & 4) {
                func_80614E78(D_807FBB48, 0x29);
            } else {
                func_80614E78(D_807FBB48, 0x27);
            }
            D_807FBB48->unk154 = 0x36;
            D_807FBB48->unk155[0] = 0;
        } else {
            sfxPlayFromActorWithAltitudeCheck(D_807FBB40, 0x16, 0xFF, 0x7F, 0);
            func_80614E78(D_807FBB40, 0x1E);
            D_807FBB40->unk154 = 0x20;
            D_807FBB40->unk155[0] = 1;
        }
    }
    if ((((EfCPlayerD4 *)D_807FD580)->unkD4 == 0) && (D_807FC928 < 2)) {
        ((EfCPlayerD4 *)D_807FD580)->unkD4 = D_807530B0[D_807FD584];
    }
    if (value != 0) {
        camStartShake(((EfCPlayer104 *)D_807FD580)->unk104, 0x14, 0x14);
    }
}

void func_806EE454(void) {
    s32 shouldNotify = 1;

    func_806CA2AC();
    if ((func_806EB400(D_807FBB48) != 0) && (func_806C9974(D_807FC929, -1) != 0)) {
        shouldNotify = 0;
        if ((D_807FBB48->unk6A & 4) != 0) {
            func_80614E78(D_807FBB48, 0x29);
        } else {
            func_80614E78(D_807FBB48, 0x27);
        }
        D_807FBB48->unk154 = 0x36;
        D_807FBB48->unk155[0] = 0;
    } else {
        sfxPlayFromActorWithAltitudeCheck(D_807FBB40, 0x16, 0xFF, 0x7F, 0);
        func_80614E78(D_807FBB40, 0x1E);
        D_807FBB40->unk154 = 0x20;
        D_807FBB40->unk155[0] = 1;
    }
    if ((((EfCPlayerD4 *)D_807FD580)->unkD4 == 0) && (D_807FC928 < 2)) {
        ((EfCPlayerD4 *)D_807FD580)->unkD4 = D_807530B0[D_807FD584];
    }
    if (shouldNotify != 0) {
        camStartShake(((EfCPlayer104 *)D_807FD580)->unk104, 0x14, 0x14);
    }
}

typedef struct {
    u8 pad0[0x2A8];
    s32 unk2A8;
    u8 pad2AC[0x44];
} EfDE5Player;

extern void func_806CA2AC(void);
extern void func_80614E78(Actor *, s32);
extern void sfxStopChannel(s32, s32);

void func_806EE5A4(void) {
    func_806CA2AC();
    sfxStopChannel(0x6B, 0);
    D_807FBB40->unk168 = ((EfDE5Player *)D_807FC924)[D_807FC929].unk2A8;
    func_80614E78(D_807FBB40, 0x1D);
    D_807FBB48->unk154 = 0x6F;
    D_807FBB48->unk155[0] = 0;
}

extern void func_806CFE7C(void);
extern void func_806CFF1C(Actor *);

void func_806EE634(void) {
    func_806CFE7C();
    func_806CFF1C(D_807FBB40);
}

extern void func_806CF398(Actor *);
extern void func_806CFF9C(Actor *);

void func_806EE660(void) {
    func_806CF398(D_807FBB48);
    func_80614E78(D_807FBB48, 0x32);
    D_807FBB48->unk154 = 0x52;
    D_807FBB48->unk155[0] = 0;
}

void func_806EE6B0(void) {
    func_806CF398(D_807FBB48);
    func_80614E78(D_807FBB48, 0x86);
    D_807FBB48->unk154 = 0x53;
    D_807FBB48->unk155[0] = 0;
}

void func_806EE700(void) {
    func_806CF398(D_807FBB48);
    func_806CFF9C(D_807FBB48);
    D_807FBB48->unk154 = 0x54;
    D_807FBB48->unk155[0] = 0;
}

extern s32 func_806EB400(Actor *);
extern s16 D_807FD6F2;
extern void func_806EEAF8(s16);

typedef struct EfN7TransitionState {
    u8 pad0[0x88];
    Actor *unk88;
} EfN7TransitionState;
void func_806EE74C(void) {
    void *new_var;

    if (func_806EB400(D_807FBB48) != 0) {
        if ((D_8076A0A8 != 0x52) && (D_8076A0A8 != 0xE)) {
            func_806EEAF8(0x40);
            return;
        }
        new_var = ((EfN7TransitionState *)D_807FD580)->unk88->unk174;
        ((u8 *)new_var)[0x45] = 1;
    }
}

void func_806EE7B8(void) {
    if (func_806EB400(D_807FBB48) != 0) {
        func_806EEAF8(D_807FD6F2);
        func_806CFE7C();
    }
}

extern void func_806F1048(Actor *);
extern s32 camIsCutsceneActive(void);

void func_806EE7F4(void) {
    if ((D_807FBB68 & 2) != 0) {
        func_806F1048(D_807FBB48);
        sfxStopChannel(0xC, 0);
    }
    if (func_806EB400(D_807FBB48) != 0) {
        if (((D_807FBB68 & 2) != 0) && (camIsCutsceneActive() != 0)) {
            return;
        }
        func_806EEAF8(1);
        func_806CFE7C();
    }
}

typedef struct {
    u8 pad0[0xDC];
    s32 unkDC;
} EfDPlayerStateDc;

typedef struct {
    u8 pad0[0x2A0];
    s32 unk2A0;
    u8 pad2A4[0x4C];
} EfDPlayerBlock;

#define EfDStateDc ((EfDPlayerStateDc *)D_807FD580)
#define EfDPlayer ((EfDPlayerBlock *)D_807FC924)
extern void actorSpawnAttachment(Actor *, f32);
extern void actorAppendActiveCallback8(void);

void func_806EE878(void) {
    if (func_806EB400(D_807FBB48) != 0) {
        EfDStateDc->unkDC = EfDPlayer[D_807FC929].unk2A0;
        if (EfDPlayer[D_807FC929].unk2A0 == 0) {
            actorSpawnAttachment(D_807FBB48, 3.2f);
        }
        func_806EEAF8(1);
        func_806CFE7C();
        actorAppendActiveCallback8();
    }
}


void func_806EE924(void) {
    if (func_806EB400(D_807FBB48) != 0) {
        EfDStateDc->unkDC = EfDPlayer[D_807FC929].unk2A0;
        func_806EEAF8(1);
        func_806CFE7C();
    }
}

extern void actorScriptStart(Actor *, s32);
extern void func_80614D00(Actor *, f32, f32);

void func_806EE994(void) {
    if (func_806EB400(D_807FBB40) != 0) {
        EfDStateDc->unkDC = EfDPlayer[D_807FC929].unk2A0;
        D_807FBB40->unk144 = 1;
        D_807FBB40->unk154 = 0x34;
        D_807FBB40->unk155[0] = 0;
        actorScriptStart(D_807FBB40, 0);
        func_806C9974(D_807FC929, -0x40);
        func_806CFE7C();
        func_80614D00(D_807FBB40, 0.0f, 0.0f);
    }
}

typedef struct EfN7ActionObject {
    u8 pad0[0x58];
    s32 unk58;
} EfN7ActionObject;

typedef struct EfN7ActionState {
    u8 pad0[0xDC];
    EfN7ActionObject *unkDC;
} EfN7ActionState;

void func_806EEA5C(void) {
    if (func_806EB400(D_807FBB48) != 0) {
        s32 action = 1;

        ((EfN7ActionState *)D_807FD580)->unkDC = (EfN7ActionObject *)EfDPlayer[D_807FC929].unk2A0;
        if ((((EfN7ActionState *)D_807FD580)->unkDC != NULL) &&
            (((EfN7ActionState *)D_807FD580)->unkDC->unk58 == 0x123)) {
            action = 2;
        }
        func_806EEAF8((s16)action);
    }
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/EFDC0/func_806EEAF8.s")

void func_806EF830(void) {
    void *new_var;
    if ((D_807FBB48->unk154 == 0x36) || (D_807FBB48->unk154 == 0x39) ||
        (D_807FBB48->unk154 == 0x3A) || (D_807FBB48->unk154 == 0x71) ||
        (D_807FBB48->unk154 == 0x73) || (D_807FBB48->unk154 == 0x74)) {
        return;
    }
    func_806CA2AC();
    D_807FBB48->unk60 &= 0xFFFF7FFF;
    func_80614E78(D_807FBB48, 0x27);
    D_807FBB48->unk154 = 0x39;
    D_807FBB48->unk155[0] = 0;
    ((u8 *)D_807FD580)[0x11C] = 0x19;
    func_8061B610(((void **)D_807FD580)[0x41]);
    if ((D_8076A0A8 != 0x52) && (D_8076A0A8 != 0xE)) {
        func_806C9974(D_807FC929, -0x40);
    } else {
        new_var = ((EfN7TransitionState *)D_807FD580)->unk88->unk174;
        ((u8 *)new_var)[0x45] = 1;
    }
}

extern void func_806CF42C(Actor *);
extern void camStartPath(Actor *, s32, s32);

void func_806EF944(void) {
    if (func_806EB400(D_807FBB48) != 0) {
        if (D_807FBB48->unk154 != 0x3B) {
            if (camIsCutsceneActive() == 0) {
                func_806CA2AC();
                func_806CF42C(D_807FBB48);
                D_807FBB48->unk144 = 1;
                func_80614E78(D_807FBB48, 0x2A);
                D_807FBB48->unk154 = 0x3B;
                D_807FBB48->unk155[0] = 0;
                func_806C9974(D_807FC929, -0x40);
                camStartPath(D_807FBB48, 0xB, 0x85);
                D_807FBB48->unkB8 = 0.0f;
            }
        }
    }
}

void func_806EFA08(void) {
    ((u8 *)D_807FD580)[0x1FC] = 1;
}

void func_806EFA1C(void) {
    D_807FBB40->unk154 = 0x6A;
    D_807FBB40->unk155[0] = 0;
}

typedef struct EfN7SpawnParams {
    u16 values[5];
} EfN7SpawnParams;

extern EfN7SpawnParams D_8075D380;
extern void actorSpawn(s32, s32);

void func_806EFA3C(void) {
    EfN7SpawnParams spawnParams;
    s32 pad;
    f32 height;

    spawnParams = D_8075D380;
    height = D_807FBB48->unk4->unk34;
    actorSpawn(0x140, 0xB9);
    if (D_807FBB48->unk58 == 2) {
        height *= 1.25;
    }
    func_8067B238(D_807FBB44, D_807FBB48, height);
    actorScriptStart(D_807FBB44, ((u16 *)&spawnParams)[D_8074E77C[((u8 *)D_807FD580)[0x1A4]]]);
    D_807FBB44->unk60 |= 0x40000000;
    func_80614E78(D_807FBB48, 0x88);
    D_807FBB40->unk154 = 0x79;
    D_807FBB40->unk155[0] = 0;
}


typedef struct {
    u8 pad0[0x210];
    f32 unk210;
    u8 pad214[4];
    f32 unk218;
    u8 pad21C[0xD4];
} EfDNavigationPlayer;

extern void func_806C9F74(Actor *);
extern s16 mathAngleArcMidpoint(s16, s16);
extern s16 mathAngleBetweenPoints2D(f32, f32, f32, f32);
extern void camStartPathNearWall(Actor *, s32, s32, s32);

void func_806EFB4C(void) {
    sfxStopChannel(0x6B, 0);
    func_806CA2AC();
    func_806C9F74(D_807FBB48);
    func_806CF42C(D_807FBB48);
    func_80614E78(D_807FBB48, 0x5B);
    D_807FBB48->unk154 = 0x70;
    D_807FBB48->unk155[0] = 0;
    if (D_807FBB48->unkFC != 0) {
        D_807FBB48->unkE6 = mathAngleArcMidpoint(D_807FBB48->unkF4, D_807FBB48->unkF6);
    } else {
        D_807FBB48->unkE6 = mathAngleBetweenPoints2D(
            ((EfDNavigationPlayer *)D_807FC924)[D_807FC929].unk210,
            ((EfDNavigationPlayer *)D_807FC924)[D_807FC929].unk218,
            D_807FBB48->unk7C,
            D_807FBB48->unk84);
    }
    camStartPathNearWall(D_807FBB48, 0x15, 0x1F, 5);
}

void func_806EFC38(void) {
    func_806CA2AC();
    func_806CF42C(D_807FBB48);
    func_806C9F74(D_807FBB48);
    if (D_807FBB48->unk154 != 0x6D) {
        func_80614E78(D_807FBB48, 0x5B);
        D_807FBB48->unk154 = 0x71;
        D_807FBB48->unk155[0] = 0;
    }
    D_807FBB48->unkE6 = mathAngleBetweenPoints2D(
        ((EfDNavigationPlayer *)D_807FC924)[D_807FC929].unk210,
        ((EfDNavigationPlayer *)D_807FC924)[D_807FC929].unk218,
        D_807FBB48->unk7C,
        D_807FBB48->unk84);
    if (D_8076A0A8 == 8) {
        camStartPath(D_807FBB48, 2, 1);
        D_807FBB48->unk155[0] = 0xFF;
        ((u16 *)D_807FD580)[0x11E] = 0xFFFF;
    } else {
        camStartPath(D_807FBB48, 5, 5);
        ((s16 *)D_807FD580)[0x11E] = 100;
    }
}

typedef struct EfEPlayerState {
    /* 0x000 */ u8 pad0[0x30];
    /* 0x030 */ f32 unk30;
    /* 0x034 */ u8 pad34[4];
    /* 0x038 */ f32 unk38;
    /* 0x03C */ u8 pad3C[0x10];
    /* 0x04C */ s16 unk4C;
    /* 0x04E */ u8 pad4E[2];
    /* 0x050 */ s16 unk50;
    /* 0x052 */ u8 pad52[2];
    /* 0x054 */ f32 unk54;
    /* 0x058 */ u8 pad58[0x30];
    /* 0x088 */ void *unk88;
    /* 0x08C */ u8 pad8C[0x162];
    /* 0x1EE */ s16 unk1EE;
    /* 0x1F0 */ s32 unk1F0;
    /* 0x1F4 */ s32 unk1F4;
    /* 0x1F8 */ u8 pad1F8[0x34];
    /* 0x22C */ f32 unk22C;
    /* 0x230 */ f32 unk230;
    /* 0x234 */ f32 unk234;
    /* 0x238 */ u8 pad238[4];
    /* 0x23C */ s16 unk23C;
} EfEPlayerState;

#define EfEPS ((EfEPlayerState *)D_807FD580)
typedef struct EfECamBlock {
    /* 0x000 */ u8 pad0[0x210];
    /* 0x210 */ f32 unk210;
    /* 0x214 */ u8 pad214[4];
    /* 0x218 */ f32 unk218;
    /* 0x21C */ u8 pad21C[0x84];
    /* 0x2A0 */ void *unk2A0;
    /* 0x2A4 */ u8 pad2A4[0x1C];
    /* 0x2C0 */ u8 unk2C0;
    /* 0x2C4 */ u8 pad2C4[0x2C];
} EfECamBlock;

#define EfECam ((EfECamBlock *)D_807FC924)
s16 mathAngleBetweenPoints2D(f32, f32, f32, f32);

void func_806EFD50(void) {
    func_806CA2AC();
    func_806CF42C(D_807FBB48);
    func_80614E78(D_807FBB48, 0x5B);
    D_807FBB48->unk154 = 0x72;
    D_807FBB48->unk155[0] = 0;
    D_807FBB48->unkE6 = mathAngleBetweenPoints2D(EfECam[D_807FC929].unk210, EfECam[D_807FC929].unk218,
                                                  D_807FBB48->unk7C, D_807FBB48->unk84);
    camStartPath(D_807FBB48, 0x15, 5);
}

typedef struct EfEActorC0 {
    u8 pad0[0xC0];
    f32 unkC0;
} EfEActorC0;

void func_806EFDFC(void) {
    func_806C8E58(EfEPS->unk1EE);
    func_806CF42C(D_807FBB48);
    func_806CA2AC();
    D_807FBB48->unk144 = 1;
    if (D_807FBB48->unk154 != 0x7D) {
        if (D_807FBB48->unk6A & 4) {
            func_80614E78(D_807FBB48, 0x34);
        } else if (!(D_807FBB48->unk6A & 2)) {
            func_80614E78(D_807FBB48, 0x5D);
        }
    }
    D_807FBB48->unk154 = 0x73;
    D_807FBB48->unk155[0] = 0;
    if ((EfEPS->unk88 == NULL) || (((Actor *)EfEPS->unk88)->unk58 != 0x57)) {
        D_807FBB48->unkE6 = mathAngleBetweenPoints2D(EfECam[D_807FC929].unk210, EfECam[D_807FC929].unk218,
                                                      D_807FBB48->unk7C, D_807FBB48->unk84);
    }
    ((EfEActorC0 *)D_807FBB48)->unkC0 = 0.0f;
    EfEPS->unk23C = 0x5A;
    func_806CFE7C();
}

void func_806EFF34(void) {
    func_806C8E58(EfEPS->unk1EE);
    func_806CF42C(D_807FBB48);
    func_806CA2AC();
    D_807FBB48->unk144 = 1;
    if (D_807FBB48->unk154 != 0x7D) {
        if (D_807FBB48->unk6A & 4) {
            func_80614E78(D_807FBB48, 0x34);
        } else if (!(D_807FBB48->unk6A & 2)) {
            func_80614E78(D_807FBB48, 0x5C);
        }
    }
    D_807FBB48->unk154 = 0x74;
    D_807FBB48->unk155[0] = 0;
    if ((EfEPS->unk88 == NULL) || (((Actor *)EfEPS->unk88)->unk58 != 0x57)) {
        D_807FBB48->unkE6 = mathAngleBetweenPoints2D(EfECam[D_807FC929].unk210, EfECam[D_807FC929].unk218,
                                                      D_807FBB48->unk7C, D_807FBB48->unk84);
    }
    ((EfEActorC0 *)D_807FBB48)->unkC0 = 0.0f;
    EfEPS->unk23C = 0x5A;
    func_806CFE7C();
}

void func_806F006C(void) {
}

void func_806F0074(void) {
}


void func_806F007C(void) {
    D_807FBB40->unk154 = 0x84;
    D_807FBB40->unk155[0] = 0;
    actorScriptStart(D_807FBB40, 0);
}


void func_806F00BC(void) {
    func_806CA2AC();
    EfEPS->unk1F0 &= ~0x20;
    D_807FBB48->unk132 = 2;
    EfEPS->unk4C = -1;
    EfEPS->unk30 = D_80753250[D_807FD584];
    D_807FBB48->unk154 = 0x7A;
    D_807FBB48->unk155[0] = 0;
}



void func_806F014C(void) {
    EfEPS->unk1F4 |= 8;
    func_806CFF9C(D_807FBB48);
}


void func_806F0184(void) {
    func_806CA2AC();
    EfEPS->unk1F0 &= ~0x20;
    D_807FBB48->unk154 = 0x7B;
    D_807FBB48->unk155[0] = 0;
}


void func_806F01D8(void) {
    func_806CA2AC();
    func_806F00BC();
    EfEPS->unk88 = EfECam[D_807FC929].unk2A0;
}


void func_806F0238(void) {
    func_80614E78(D_807FBB48, 9);
    D_807FBB48->unk154 = 0xC;
    D_807FBB48->unk155[0] = 0;
}

void actorSpawn(s32, s32);
void func_806C8D20(Actor *);

void func_806F027C(void) {
    EfEPS->unk4C = -1;
    EfEPS->unk30 = D_80753250[D_807FD584];
    func_806CFE7C();
    if (D_807FBB48->unk154 != 0x7C) {
        func_806CA2AC();
        D_807FBB48->unk154 = 0x7C;
        D_807FBB48->unk155[0] = 0;
        actorScriptStart(D_807FBB48, 0x13);
        actorSpawn(0x117, 0xC5);
        D_807FBB44->unk11C = (s32)D_807FBB48;
        func_806C8D20(D_807FBB48);
    }
}


void func_806F0344(void) {
    func_806CFE7C();
    D_807FBB48->unk154 = 0x7D;
    D_807FBB48->unk155[0] = 0;
    D_807FBB48->unk60 &= ~4;
    actorSpawn(0x11A, 0x21);
    actorScriptStart(D_807FBB44, 0x232);
    D_807FBB44->unk11C = (s32)D_807FBB48;
}

#ifdef NON_MATCHING
void func_806F03C4(void) {
    s32 ev;
    EfECamBlock *camera;

    switch (D_807FBB48->unk58) {
    case 2:
        if (D_807FD580 && D_807FD580) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
        ev = 7;
        camera = &EfECam[D_807FC929];
        break;
    case 3:
        ev = 0;
        camera = &EfECam[D_807FC929];
        break;
    case 4:
        EfEPS->unk1F0 |= 0x100;
        ev = 4;
        camera = &EfECam[D_807FC929];
        break;
    case 5:
        camera = &EfECam[D_807FC929];
        if (camera->unk2C0 == 1) {
            ev = 8;
        } else {
            ev = 0x1F;
        }
        break;
    case 6:
        ev = 9;
        camera = &EfECam[D_807FC929];
        break;
    default:
        camera = &EfECam[D_807FC929];
        break;
    }
    D_807FBB48->unkE6 = mathAngleBetweenPoints2D(camera->unk210, camera->unk218,
                                                  D_807FBB48->unk7C, D_807FBB48->unk84);
    if (D_807FBB68 & 2) {
        EfEPS->unk1F0 &= ~0x100;
        actorScriptStart(D_807FBB48, 0x165);
    } else {
        if (D_807FBB48->unk154 != 0x56) {
            camStartPath(D_807FBB48, (s16)ev, 5);
        }
        func_80614E78(D_807FBB48, 0x5A);
    }
    D_807FBB48->unk154 = 0x67;
    D_807FBB48->unk155[0] = 0;
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/EFDC0/func_806F03C4.s")
#endif

void func_806E9964(EfEPlayerState *);

void func_806F0624(void) {
    EfEPS->unk1F4 |= 0x10;
    func_806E9964(EfEPS);
    D_807FBB48->unk154 = 0x83;
    D_807FBB48->unk155[0] = 0;
    D_807FBB48->unk60 |= 0x40000004;
    D_807FBB48->unk60 &= ~1;
}

void func_806F06A4(void) {
    D_807FBB48->unk154 = 0x87;
    D_807FBB48->unk155[0] = 0;
    actorScriptStart(D_807FBB48, 0);
    EfEPS->unk50 = 0;
    EfEPS->unk4C = -1;
}

typedef struct EfEActorE4 {
    /* 0x000 */ u8 pad0[0xE4];
    /* 0x0E4 */ s16 unkE4;
} EfEActorE4;

void func_806F0700(void) {
    D_807FBB48->unk154 = 0x88;
    D_807FBB48->unk155[0] = 0;
    actorScriptStart(D_807FBB48, 0);
    D_807FBB48->unk7C = EfEPS->unk22C;
    D_807FBB48->unk80 = EfEPS->unk230;
    D_807FBB48->unk84 = EfEPS->unk234;
    ((EfEActorE4 *)D_807FBB48)->unkE4 = -0x3E6;
    D_807FBB48->unk4->unk34 = 0.01f;
    D_807FBB48->unk4->unk38 = 0.01f;
    D_807FBB48->unk4->unk3C = 0.01f;
    EfEPS->unk50 = 0;
    EfEPS->unk4C = -1;
}


void func_806F07CC(void) {
    sfxPlayFromActorWithAltitudeCheck(D_807FBB48, 0xF3, 0xFF, 0x7F, 0x19);
    D_807FBB48->unk154 = 0x19;
    D_807FBB48->unk155[0] = 0;
    EfEPS->unk54 = D_807535CC[D_807FD584] * 2.6;
    EfEPS->unk50 = 0xC;
    func_80614E78(D_807FBB48, 0x10);
}

typedef struct EfEActor78 {
    /* 0x000 */ u8 pad0[0x78];
    /* 0x078 */ u8 unk78;
} EfEActor78;

#define EfEActor ((EfEActor78 *)D_807FBB48)


void func_806F0878(void) {
    if (EfEActor->unk78 == 0xC) {
        sfxPlayFromActorWithAltitudeCheck(D_807FBB48, 0x76, 0x64, 0x7F, 0);
    }
    EfEPS->unk38 = D_807531FC[D_807FD584];
    func_806CF398(D_807FBB48);
    D_807FBB48->unk154 = 0x15;
    D_807FBB48->unk155[0] = 0;
    func_80614E78(D_807FBB48, 6);
    D_807FBB48->unk6A |= 0x20;
    func_80614D90(D_807FBB48);
}

void func_806F0930(void) {
    if (EfEActor->unk78 == 0xC) {
        sfxPlayFromActorWithAltitudeCheck(D_807FBB48, 0x76, 0xFF, 0x7F, 0);
    }
    EfEPS->unk38 = D_807531FC[D_807FD584];
    func_806CF398(D_807FBB48);
    D_807FBB48->unk154 = 0x16;
    D_807FBB48->unk155[0] = 0;
    func_80614E78(D_807FBB48, 7);
    D_807FBB48->unk6A |= 0x20;
    func_80614D90(D_807FBB48);
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/EFDC0/D_8075D380.s")
