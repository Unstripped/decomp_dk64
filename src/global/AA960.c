#include "common.h"
#include "actor.h"

typedef struct SfxTableEntry {
    /* 0x0 */ u16 unk0;
    /* 0x2 */ s16 unk2;
    /* 0x4 */ u8 unk4;
    /* 0x5 */ u8 unk5;
} SfxTableEntry; /* size = 6 */

extern Actor *D_807FBB40;
extern Actor *D_807FBB4C;
extern s32 D_807FBB64;
extern u32 D_807FBB68;
extern u8 gPlayerCount;
extern SfxTableEntry D_80750400[];

extern u8 D_807204BC[];
extern u8 D_80720508[];
extern u8 D_807205C4[];
extern u8 D_807205E8[];
extern u8 D_80720710[];
extern u8 D_80720768[];
extern u8 D_807207BC[];
extern u8 D_807207E0[];
extern u8 D_807209EC[];
extern u8 D_80720A10[];
extern u8 D_80720A34[];
extern u8 D_80720A58[];
extern u8 D_807211D0[];
extern u8 D_80721378[];

void actorSpawnNodeEntryScaled(s16, f32, f32, f32, s32, s32, s32, s32);
void effectSpawnAttachedSpriteColored(void *, s32);
void func_806A6230(void);
void func_80714A08(f32, f32);
s32 func_80714C08(void *, f32, void *, s32, s32);
void sfxAllocateChannel(s32, f32);
void actorListSpawnNodeEntry(s16, f32, f32, f32, s16, f32, s32, void *);
void func_807149C8(s32, s32, s32, u8);
void func_80714998(s32);
void func_807149B8(s32);
void func_807149FC(s32);
void actorDropBounceExpireUpdate(f32);
void effectSpawnAttachedSprite(void *, void *, f32);

void sfxSpawnTableNodes(Actor *arg0) {
    s32 i;
    s32 found;
    s32 j;
    s16 step;
    s16 offset;

    i = 0;
    found = 0;
    offset = 0;
    if (gPlayerCount >= 2) {
        return;
    }
    if (D_807FBB64 & 0x4000) {
        return;
    }
    while (found == 0 && D_80750400[i].unk0 != 0) {
        if (D_80750400[i].unk0 == arg0->unk58) {
            found = 1;
        } else {
            i++;
        }
    }
    if (found == 0) {
        return;
    }
    if (D_80750400[i].unk4 != 0) {
        sfxAllocateChannel(D_80750400[i].unk4, 1.0f);
    }
    step = (s16)(0xFFF / D_80750400[i].unk5);
    for (j = 0; j < D_80750400[i].unk5; j++) {
        actorSpawnNodeEntryScaled(D_80750400[i].unk2, arg0->unk7C, arg0->unk80, arg0->unk84, offset, 1, -1, 0);
        offset = offset + step;
    }
}

void actorSpawnNodeEntryScaled(s16 arg0, f32 arg1, f32 arg2, f32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7) {
    s32 pad[6];
    f32 vec[3];
    f32 scale;

    scale = 0.15f;
    if (D_807FBB68 & 0x10) {
        scale = scale + scale;
    }
    vec[0] = (f32)(u8)arg5;
    vec[1] = (f32)(s16)arg4;
    vec[2] = (f32)(s16)arg6;
    actorListSpawnNodeEntry(arg0, arg1, arg2, arg3, 0, scale, arg7, vec);
}

void effectSpawnAttachedSprite(void *arg0, void *arg1, f32 arg2) {
    if (D_807FBB68 & 0x10) {
        arg2 = arg2 + arg2;
    }
    func_807149FC(-1);
    func_807149B8(1);
    func_80714998(2);
    *(s32 *)((u8 *)arg0 + 4) = func_80714C08(arg1, arg2 * 0.35, D_807FBB40, 1, 2);
}

void func_806A5F44(void) {
    void *temp = D_807FBB40->unk174;

    actorDropBounceExpireUpdate(4.5f);
    if (!(D_807FBB40->unk60 & 0x10)) {
        effectSpawnAttachedSprite(temp, D_80720710, 1.0f);
    }
}

void func_806A5FA4(void) {
    void *temp = D_807FBB40->unk174;

    actorDropBounceExpireUpdate(4.5f);
    if (!(D_807FBB40->unk60 & 0x10)) {
        effectSpawnAttachedSprite(temp, D_80720508, 1.0f);
    }
}

void effectSpawnAttachedSpriteColored(void *arg0, s32 arg1) {
    void *temp = D_807FBB40->unk174;

    actorDropBounceExpireUpdate(4.5f);
    if (!(D_807FBB40->unk60 & 0x10)) {
        if (arg1 != D_807FBB4C->unk58) {
            func_807149C8(0xFF, 0xFF, 0xFF, 0x64);
        }
        effectSpawnAttachedSprite(temp, arg0, 1.0f);
    }
}

void func_806A6094(void) {
    effectSpawnAttachedSpriteColored(D_807209EC, 3);
}

void func_806A60BC(void) {
    effectSpawnAttachedSpriteColored(D_80720A10, 6);
}

void func_806A60E4(void) {
    effectSpawnAttachedSpriteColored(D_807207E0, 4);
}

void func_806A610C(void) {
    effectSpawnAttachedSpriteColored(D_80720A34, 2);
}

void func_806A6134(void) {
    effectSpawnAttachedSpriteColored(D_80720A58, 5);
}

void func_806A615C(void) {
    void *temp = D_807FBB40->unk174;

    actorDropBounceExpireUpdate(4.5f);
    if (!(D_807FBB40->unk60 & 0x10)) {
        func_80714A08(-0.35f, 0.35f);
        effectSpawnAttachedSprite(temp, D_80720768, 1.0f);
    }
}

void func_806A61D0(void) {
    void *temp = D_807FBB40->unk174;

    actorDropBounceExpireUpdate(4.5f);
    if (!(D_807FBB40->unk60 & 0x10)) {
        effectSpawnAttachedSprite(temp, D_807204BC, 1.0f);
    }
}

void func_806A6230(void) {
    void *temp = D_807FBB40->unk174;

    actorDropBounceExpireUpdate(4.5f);
    if (!(D_807FBB40->unk60 & 0x10)) {
        if ((D_807FBB64 & 0x80000) || (D_807FBB64 & 0x2000)) {
            D_807FBB40->unk15F = 1;
        }
        effectSpawnAttachedSprite(temp, D_807207BC, 1.0f);
    }
}

void func_806A62B4(void) {
    func_806A6230();
}

void func_806A62D4(void) {
    void *temp = D_807FBB40->unk174;

    actorDropBounceExpireUpdate(4.5f);
    if (!(D_807FBB40->unk60 & 0x10)) {
        func_807149C8(0xFF, 0xFF, 0, 0xFF);
        effectSpawnAttachedSprite(temp, D_807211D0, 1.5f);
    }
}

void func_806A6348(void) {
    void *temp = D_807FBB40->unk174;

    actorDropBounceExpireUpdate(4.5f);
    if (!(D_807FBB40->unk60 & 0x10)) {
        effectSpawnAttachedSprite(temp, D_807205C4, 1.0f);
    }
}

void func_806A63A8(void) {
    void *temp = D_807FBB40->unk174;

    actorDropBounceExpireUpdate(4.5f);
    if (!(D_807FBB40->unk60 & 0x10)) {
        effectSpawnAttachedSprite(temp, D_807205E8, 1.0f);
    }
}

void func_806A6408(void) {
    void *temp = D_807FBB40->unk174;

    actorDropBounceExpireUpdate(12.0f);
    if (!(D_807FBB40->unk60 & 0x10)) {
        effectSpawnAttachedSprite(temp, D_80721378, 2.0f);
    }
}

extern u8 D_807203B0;
extern u8 D_807203D4;
extern u8 D_807203F8;
extern u8 D_8072041C;
extern u8 D_80720440;

void func_806A6468(void) {
    void *temp_v1;
    void *anim;

    temp_v1 = D_807FBB40->unk174;
    actorDropBounceExpireUpdate(4.5f);
    if (!(D_807FBB40->unk60 & 0x10)) {
        switch (D_807FBB4C->unk58) {
        case 3:
            anim = &D_807203B0;
            break;
        case 2:
            anim = &D_8072041C;
            break;
        case 4:
            anim = &D_807203F8;
            break;
        case 6:
            anim = &D_807203D4;
            break;
        case 5:
            anim = &D_80720440;
            break;
        }
        effectSpawnAttachedSprite(temp_v1, anim, 1.0f);
        if (D_807FBB40->unk154 == 0x63) {
            D_807FBB40->unk154 = 1;
            D_807FBB40->unk15F = 2;
        }
    }
}

extern u8 D_80720EBC;
extern u8 D_80720EE8;
extern u8 D_80720F14;
extern u8 D_80720F40;
extern u8 D_80720F6C;

void func_806A6574(void) {
    void *temp_v1;
    void *anim;

    temp_v1 = D_807FBB40->unk174;
    actorDropBounceExpireUpdate(4.5f);
    if (!(D_807FBB40->unk60 & 0x10)) {
        switch (D_807FBB4C->unk58) {
        case 3:
            anim = &D_80720EE8;
            break;
        case 2:
            anim = &D_80720F40;
            break;
        case 4:
            anim = &D_80720F14;
            break;
        case 6:
            anim = &D_80720EBC;
            break;
        case 5:
            anim = &D_80720F6C;
            break;
        }
        effectSpawnAttachedSprite(temp_v1, anim, 1.0f);
    }
}

typedef struct BehaviourState {
    /* 0x0 */ u8 unk0;
    /* 0x1 */ u8 unk1;
    /* 0x2 */ u8 pad2[2];
    /* 0x4 */ u8 *unk4;
    /* 0x8 */ u16 unk8;
    /* 0xA */ s16 unkA;
} BehaviourState;

typedef struct BehaviourConfig {
    /* 0x0 */ f32 unk0;
    /* 0x4 */ f32 unk4;
    /* 0x8 */ f32 unk8;
} BehaviourConfig;

extern ActorGlobalState D_807FBB70;
extern s16 D_8075038C;
void func_8067ACB4(Actor *);
s32 actorAngleInArc(Actor *, s16);
s16 mathAngleArcMidpoint(s16, s16);
void actorApplyVelocity(Actor *);
void actorUpdateFloorContactAndTilt(Actor *, f32);
void actorAppendModelNode(Actor *, f32, f32, f32, f32, s32);
void actorAppendModelSubNode(Actor *, f32, f32, f32, s32);
void actorSetCollisionRadius(Actor *, f32);
u32 randomLcgNext(void);
s32 camIsCutsceneActive(void);
s32 actorTypeIsRespawnPickup(s32);
void func_806F5F2C(s32, s32, s16, s16, s32);
s32 sfxPlayFromActorWithAltitudeCheck(Actor *, s16, u8, s16, u8);
void actorDespawn(void *);

void actorDropBounceExpireUpdate(f32 arg0) {
    BehaviourState *state;
    s32 v;

    state = (BehaviourState *)D_807FBB40->unk174;
    if (D_807FBB68 & 0x10) {
        arg0 *= 2.0f;
    }
    if (!(D_807FBB40->unk60 & 0x10)) {
        D_807FBB40->unk154 = (u8)(s32)((BehaviourConfig *)D_807FBB40->unk124)->unk0;
        *(s16 *)((u8 *)D_807FBB40 + 0xEE) = (s16)(s32)((BehaviourConfig *)D_807FBB40->unk124)->unk4;
        D_807FBB40->unkE6 = *(s16 *)((u8 *)D_807FBB40 + 0xEE);
        actorAppendModelSubNode(D_807FBB40, 0.0f, 0.0f, 0.0f, -1);
        state->unk0 = 0;
        state->unk1 = 0;
        state->unkA = (s16)(s32)((BehaviourConfig *)D_807FBB40->unk124)->unk8;
        *(s16 *)((u8 *)D_807FBB40 + 0xFA) = 0x270F;
    }
    if (D_807FBB70.unk0 != 0) {
        D_807FBB40->unk154 = D_807FBB70.unk1[0];
    }
    func_8067ACB4(D_807FBB40);
    if (D_807FBB40->unkFC != 0) {
        if (actorAngleInArc(D_807FBB40, *(s16 *)((u8 *)D_807FBB40 + 0xEE)) == 0) {
            s16 temp;
            s16 b;
            s16 c;

            temp = mathAngleArcMidpoint(D_807FBB40->unkF4, D_807FBB40->unkF6);
            b = (*(s16 *)((u8 *)D_807FBB40 + 0xEE) + 0x800) & 0xFFF;
            c = temp - b;
            *(s16 *)((u8 *)D_807FBB40 + 0xEE) = temp + c;
        }
    }
    switch (D_807FBB40->unk154) {
    case 0:
        break;
    case 1:
        D_807FBB40->unk144 = 0x1C;
        actorSetCollisionRadius(D_807FBB40, 60.0f);
        actorAppendModelNode(D_807FBB40, 0.0f, 0.0f, 0.0f, 50.0f, -1);
        actorAppendModelSubNode(D_807FBB40, 0.0f, 0.0f, 0.0f, -1);
        *(f32 *)((u8 *)D_807FBB40 + 0xC0) = (f32)((f64)((randomLcgNext() / 10000) % 200) * 0.5 + 220.0 - 50.0);
        if (!(D_807FBB64 & 0x4000) && (((u32)D_807FBB40->unk58 < 0x4B) || ((u32)D_807FBB40->unk58 >= 0x50))) {
            D_807FBB40->unkB8 = 30.0f;
        }
        D_807FBB40->unk154++;
    case 2:
        actorApplyVelocity(D_807FBB40);
        actorUpdateFloorContactAndTilt(D_807FBB40, arg0);
        *(f32 *)((u8 *)D_807FBB40 + 0xC0) -= 20.0f;
        if (*(f32 *)((u8 *)D_807FBB40 + 0xC0) < (f32)D_8075038C) {
            *(f32 *)((u8 *)D_807FBB40 + 0xC0) = (f32)D_8075038C;
        }
        if ((D_807FBB40->unk6A & 1) && !(D_807FBB40->unk6C & 1)) {
            switch (state->unk0) {
            case 0:
                if (D_807FBB40->unk15F != 1) {
                    state->unk1 = 1;
                }
                *(f32 *)((u8 *)D_807FBB40 + 0xC0) = 150.0f;
                break;
            case 1:
                *(f32 *)((u8 *)D_807FBB40 + 0xC0) = 100.0f;
                break;
            case 2:
                *(f32 *)((u8 *)D_807FBB40 + 0xC0) = 50.0f;
                break;
            case 3:
                D_807FBB40->unkB8 = 0.0f;
                *(f32 *)((u8 *)D_807FBB40 + 0xC0) = 0.0f;
                if (D_807FBB40->unk58 == 0x8C) {
                    state->unk1 = 1;
                }
                if (D_807FBB40->unk58 != 0x6E && D_807FBB40->unk58 != 0x8C && !(D_807FBB64 & 0x4000) && D_807FBB40->unk15F != 2) {
                    state->unk8 = 0x64;
                    D_807FBB40->unk154 = 3;
                } else {
                    D_807FBB40->unk154 = 0x64;
                }
                break;
            }
            switch (D_807FBB40->unk58) {
            case 0x34:
                sfxPlayFromActorWithAltitudeCheck(D_807FBB40, 0xF5, (*(f32 *)((u8 *)D_807FBB40 + 0xC0) + 105.0f), 0x7F, 0x1E);
                break;
            case 0x36:
                if (state->unk0 == 0) {
                    sfxPlayFromActorWithAltitudeCheck(D_807FBB40, 0x1D1, 0xFF, 0x7F, 0xA);
                }
                break;
            default:
                sfxPlayFromActorWithAltitudeCheck(D_807FBB40, 1, (*(f32 *)((u8 *)D_807FBB40 + 0xC0) + 105.0f), 0x7F, 0x14);
                break;
            }
            state->unk0++;
        }
        break;
    case 3:
        if (camIsCutsceneActive() == 0) {
            state->unk8--;
        }
        if (state->unk8 == 0) {
            D_807FBB40->unk154 = 4;
        }
        break;
    case 4:
        state->unk4[0x36D] -= 5;
        if ((s32)state->unk4[0x36D] < 0xA) {
            if ((D_807FBB64 & 0x10000) && actorTypeIsRespawnPickup(D_807FBB40->unk58) != 0) {
                func_806F5F2C(D_807FBB40->unk58, 0x258, (s16)(s32)D_807FBB40->unk7C, (s16)(s32)D_807FBB40->unk80, (s32)D_807FBB40->unk84);
            }
            actorDespawn(D_807FBB40);
        }
        break;
    case 25:
        state->unk8 = 0x64;
        D_807FBB40->unk154 = 3;
        state->unk1 = 1;
        break;
    }
}

typedef struct ActorConfig {
    f32 unk0;
    f32 unk4;
    f32 unk8;
} ActorConfig;

typedef struct EffectState {
    u8 unk0;
    u8 unk1;
    s8 unk2;
    u8 pad3[1];
    u16 unk4;
    s16 unk6;
    u16 unk8;
    s16 unkA;
} EffectState;

extern ActorGlobalState D_807FBB70;
extern s16 D_80750384;
extern s16 D_8075038C;
extern f32 D_80750388;
void func_806C9974(s32, s32);
void func_8067ACB4(Actor *);
s32 actorAngleInArc(Actor *, s16);
s16 mathAngleArcMidpoint(s16, s16);
void actorApplyVelocity(Actor *);
void actorUpdateFloorContactAndTilt(Actor *, f32);
void sfxPlayAtPositionPooled(f32, f32, f32, s32, s32, s32, s32, s32, f32, s32);
void actorAppendModelNode(Actor *, f32, f32, f32, f32, s32);
void actorAppendModelSubNode(Actor *, f32, f32, f32, s32);
void actorSetCollisionRadius(Actor *, f32);
void actorUpdateModelMatrix(Actor *, s32);

typedef struct PhysicsActor {
    u8 pad0[0xC0];
    f32 unkC0;
    u8 padC4[0xEE - 0xC4];
    s16 unkEE;
    u8 padF0[0xFA - 0xF0];
    s16 unkFA;
} PhysicsActor;

#define AA960_PHY ((PhysicsActor *)D_807FBB40)

void actorBounceFadeInSpinUpdate(u8);

void actorBounceFadeInSpinUpdate(u8 arg0) {
    EffectState *temp_v1;
    s16 temp;

    temp_v1 = D_807FBB40->unk174;
    if (!(D_807FBB40->unk60 & 0x10)) {
        D_807FBB40->unk60 |= 0x801000;
        D_807FBB40->unk16A = 0xFF;
        D_807FBB40->unk16B = 0xFF;
        D_807FBB40->unk16C = 0xFF;
        D_807FBB40->unk60 &= ~0x8000;
        D_807FBB40->unk154 = (s32)((ActorConfig *)D_807FBB40->unk124)->unk0;
        AA960_PHY->unkEE = ((ActorConfig *)D_807FBB40->unk124)->unk4;
        D_807FBB40->unkE6 = AA960_PHY->unkEE;
        temp_v1->unk0 = 0;
        temp_v1->unk1 = 1;
        temp_v1->unkA = ((ActorConfig *)D_807FBB40->unk124)->unk8;
        AA960_PHY->unkFA = 0x270F;
        func_806C9974(0, 0x40);
    }
    if ((f32)temp_v1->unk8 < 30.0f) {
        temp_v1->unk8++;
    }
    D_807FBB40->unk128 = temp_v1->unk8 * 0.033333335f * 255.0f;
    if (D_807FBB70.unk0 != 0) {
        D_807FBB40->unk154 = D_807FBB70.unk1[0];
    }
    func_8067ACB4(D_807FBB40);
    if (D_807FBB40->unkFC != 0 && actorAngleInArc(D_807FBB40, AA960_PHY->unkEE) == 0) {
        temp = mathAngleArcMidpoint(D_807FBB40->unkF4, D_807FBB40->unkF6);
        {
            s16 b = (AA960_PHY->unkEE + 0x800) & 0xFFF;
            s16 c = temp - b;

            AA960_PHY->unkEE = temp + c;
        }
    }
    if (D_807FBB40->unk154 == 1 || D_807FBB40->unk154 == 2 || D_807FBB40->unk154 == 4
        || D_807FBB40->unk154 == 5 || D_807FBB40->unk154 == 6) {
        D_807FBB40->unk144 = 0x1C;
        actorSetCollisionRadius(D_807FBB40, 60.0f);
        actorAppendModelNode(D_807FBB40, 0.0f, 0.0f, 0.0f, 50.0f, -1);
        actorAppendModelSubNode(D_807FBB40, 0.0f, 0.0f, 0.0f, -1);
        switch (D_807FBB40->unk154) {
        case 1:
            D_807FBB40->unkB8 = D_80750384;
            AA960_PHY->unkC0 = 0.0f;
            break;
        case 2:
            AA960_PHY->unkC0 = 2000.0f;
            break;
        case 4:
            D_807FBB40->unkB8 = 1500.0f;
            AA960_PHY->unkC0 = 4000.0f;
            break;
        case 5:
            D_807FBB40->unkB8 = 200.0f;
            AA960_PHY->unkC0 = 2000.0f;
            break;
        case 6:
            D_807FBB40->unkB8 = 1000.0f;
            AA960_PHY->unkC0 = 2000.0f;
            break;
        }
        D_807FBB40->unk154 = 3;
    }
    switch (D_807FBB40->unk154) {
    case 0:
        break;
    case 3:
        actorApplyVelocity(D_807FBB40);
        actorUpdateFloorContactAndTilt(D_807FBB40, 0.0f);
        AA960_PHY->unkC0 += D_80750388;
        if (AA960_PHY->unkC0 < (f32)D_8075038C) {
            AA960_PHY->unkC0 = (f32)D_8075038C;
        }
        if ((D_807FBB40->unk6A & 1) && !(D_807FBB40->unk6C & 1)) {
            temp = 0xC8;
            switch (temp_v1->unk0) {
            case 0:
                AA960_PHY->unkC0 = 1600.0f;
                D_807FBB40->unkB8 = D_807FBB40->unkB8 / 2;
                temp = 0xC8;
                break;
            case 1:
                AA960_PHY->unkC0 = 1200.0f;
                D_807FBB40->unkB8 = D_807FBB40->unkB8 / 2;
                temp = 0x64;
                break;
            case 2:
                AA960_PHY->unkC0 = 800.0f;
                D_807FBB40->unkB8 = D_807FBB40->unkB8 / 2;
                temp = 0x46;
                break;
            case 3:
                D_807FBB40->unkB8 = 0.0f;
                AA960_PHY->unkC0 = 0.0f;
                temp = 0x1E;
                if (arg0 != 0) {
                    D_807FBB40->unk154 = 0x64;
                }
                break;
            }
            if (D_807FBB40->unk58 == 0x48) {
                sfxPlayAtPositionPooled(D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84, 0x2A1, temp, 0x7F, 0, 0, 0.0f, 0);
            }
            temp_v1->unk0++;
        }
        break;
    case 0x64:
        break;
    }
    D_807FBB40->unkE6 += 0x72;
    actorUpdateModelMatrix(D_807FBB40, 0);
}

void func_806A734C(void) {
    actorBounceFadeInSpinUpdate(1);
}

typedef struct ActorPhysics {
    u8 pad0[0xC0];
    f32 unkC0;
    f32 unkC4;
} ActorPhysics;

typedef struct EffectCounter {
    u8 pad0[0x8];
    u16 unk8;
} EffectCounter;

void billboardSubmit(Actor *, s32, s32, s32, s32, s32, s32, s32, s32, s32, f32);
void func_80686CF8(Actor *);

void actorUpdateSfxAndGround(void) {
    EffectCounter *temp_v1;

    temp_v1 = D_807FBB40->unk174;
    if (!(D_807FBB40->unk60 & 0x10)) {
        D_807FBB40->unk64 |= 4;
        D_807FBB40->unk60 |= 0x400;
        func_80686CF8(D_807FBB40);
    }
    if (temp_v1->unk8 == 1) {
        sfxPlayAtPositionPooled(D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84, 0x73, 0xFF, 0x7F, 1, 0, 0.0f, 0);
        sfxAllocateChannel(0x3B, 0.7f);
    } else if (temp_v1->unk8 == 0xA) {
        sfxPlayAtPositionPooled(D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84, 0x19C, 0xB4, 0x7F, 1, 0, 0.0f, 0);
    }
    actorBounceFadeInSpinUpdate(0);
    if (D_807FBB40->unk80 < D_807FBB40->unkAC) {
        D_807FBB40->unkB8 = 0.0f;
        D_807FBB40->unk80 = D_807FBB40->unkAC;
        ((ActorPhysics *)D_807FBB40)->unkC0 = ((ActorPhysics *)D_807FBB40)->unkC4;
    }
    billboardSubmit(D_807FBB40, 0x3C8, 0x40, 0x40, 0x1E, 0x1E, 1, 0x96, 0x78, 0, 1.0f);
}

void effectSpawnRingBursts(Actor *, f32, f32, s32);

void actorSpawnRingBurstAndUpdate(void) {
    if (!(D_807FBB40->unk60 & 0x10)) {
        D_807FBB40->unk60 |= 0x400;
        effectSpawnRingBursts(D_807FBB40, 20.0f, 40.0f, 0x1E);
        D_807FBB40->unkA4 = 99999.0f;
        actorUpdateFloorContactAndTilt(D_807FBB40, 0);
    }
    actorBounceFadeInSpinUpdate(0);
    if (D_807FBB40->unkA4 != 99999.0f) {
        billboardSubmit(D_807FBB40, 0x3C8, 0x40, 0x40, 0x19, 0x19, 1, 0x96, 0x78, 0, 1.0f);
    }
}

void actorDespawn(void *);
void func_80714950(s32);
void func_8071498C(void (*)(void));
void effectOrbitSourceUpdate(void);
void effectProximityFadeUpdate(void);
void slotQueueUpdate(s32, s32, s32);
void slotQueueAddValue(s32, s32, s32);

void actorPathCollectibleUpdate(void *);

typedef struct AA960ConfigInt {
    s32 unk0;
    s32 unk4;
} AA960ConfigInt;

extern u8 D_807FBD70;
extern u32 D_8076A068;
s32 actorListFindIdByActor(Actor *);
s32 actorListLookupEntry(s32);
s32 flagGet(s32, s32);
void flagSet(s32, s32, s32);
s32 pathPlaybackStart(void *, s32, s32, f32, f32, f32, s32);
void func_807232B8(s32, s32);
void func_80723284(s32, s32);
void func_80723320(s32, s32);
void func_8072334C(s32, s32);
void pathPlaybackAdvance(s32);
void pathPlaybackGetPosition(s32, f32 *, f32 *, f32 *);
void func_80724994(s32, s32, s32, s32, s32);
f32 func_80612794(s16);
void func_80714A28(s32);

void actorPathCollectibleUpdate(void *arg0) {
    EffectState *temp_v1;
    s32 temp;
    s32 cond;
    s32 flag;

    temp_v1 = D_807FBB40->unk174;
    if (!(D_807FBB40->unk60 & 0x10)) {
        if (D_807FBB40->unk58 == 0x93) {
            temp_v1->unk6 = -1;
        } else {
            temp_v1->unk6 = actorListLookupEntry(actorListFindIdByActor(D_807FBB40) & 0xFFFF);
        }
        if (temp_v1->unk6 != -1 && flagGet(temp_v1->unk6, 0) != 0) {
            actorDespawn(D_807FBB40);
            return;
        }
        actorAppendModelSubNode(D_807FBB40, 0.0f, 0.0f, 0.0f, -1);
        actorSetCollisionRadius(D_807FBB40, 175.0f);
        actorAppendModelNode(D_807FBB40, 0.0f, 12.0f, 0.0f, 80.0f, -1);
        temp_v1->unk0 = ((AA960ConfigInt *)D_807FBB40->unk124)->unk0;
        temp_v1->unk1 = ((AA960ConfigInt *)D_807FBB40->unk124)->unk4;
        temp_v1->unk2 = pathPlaybackStart(D_807FBB40, temp_v1->unk0, 0, 0.0f, 0.0f, 0.0f, 0);
        if (temp_v1->unk2 != -1) {
            func_807232B8(temp_v1->unk2, 1);
            func_80723284(temp_v1->unk2, temp_v1->unk1);
            func_80723320(temp_v1->unk2, -1);
            func_8072334C(temp_v1->unk2, 1);
        }
        temp_v1->unk4 = 0;
    } else {
        if (temp_v1->unk2 != -1) {
            pathPlaybackAdvance(temp_v1->unk2);
            pathPlaybackGetPosition(temp_v1->unk2, &D_807FBB40->unk7C, &D_807FBB40->unk80, &D_807FBB40->unk84);
        }
        D_807FBB40->unk80 += 5.0 * func_80612794(temp_v1->unk4);
        temp_v1->unk4 = (temp_v1->unk4 + 0x50) & 0xFFF;
        if (D_8076A068 % 0x18 == 0) {
            switch (D_807FBB40->unk58) {
            case 0x5B:
                temp = 6;
                break;
            case 0x6F:
                temp = 0x75;
                break;
            case 0x70:
                temp = 0x42;
                break;
            case 0x71:
                temp = 0x46;
                break;
            default:
                temp = -1;
                break;
            }
            flag = (temp == -1 || flagGet(temp, 0) != 0) ? 1 : 0;
            if (flag != 0) {
                func_807149B8(1);
                cond = 1;
                if (D_807FBB40->unk58 == 0x93) {
                    cond = 0;
                } else if (D_807FBB4C->unk58 == 3 && D_807FBB40->unk58 == 0x5B) {
                    cond = 0;
                } else if (D_807FBB4C->unk58 == 6 && D_807FBB40->unk58 == 0x6F) {
                    cond = 0;
                } else if (D_807FBB4C->unk58 == 5 && D_807FBB40->unk58 == 0x70) {
                    cond = 0;
                } else if (D_807FBB4C->unk58 == 4 && D_807FBB40->unk58 == 0x71) {
                    cond = 0;
                } else if (D_807FBB4C->unk58 == 2 && D_807FBB40->unk58 == 0x72) {
                    cond = 0;
                }
                if (cond != 0) {
                    func_807149C8(0xFF, 0xFF, 0xFF, 0x96);
                } else {
                    func_8071498C(&effectProximityFadeUpdate);
                    func_80714950(0x226);
                }
                func_80714A28(4);
                func_80714998(3);
                func_80714C08(arg0, 0.8f, D_807FBB40, 1, 2);
                D_807FBB40->unk144 = 2;
            } else {
                D_807FBB40->unk144 = 1;
            }
        }
        if (D_807FBD70 == 4) {
            func_80686CF8(D_807FBB40);
            sfxPlayAtPositionPooled(D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84, 0x2BF, 0xFF, 0x7F, 0x1E, 0, 0.0f, 0);
            actorDespawn(D_807FBB40);
            if (D_807FBB40->unk58 == 0x93) {
                func_80724994(3, 1, 0x27, 0, 0);
            } else {
                if (temp_v1->unk6 != -1) {
                    flagSet(temp_v1->unk6, 1, 0);
                }
                slotQueueUpdate(0, 0, 0);
                slotQueueAddValue(0, 0, 0xA);
            }
        }
    }
}

extern u8 D_80720FBC;
void func_806A7B04(void) {
    actorPathCollectibleUpdate(&D_80720FBC);
}

extern u8 D_80720F98;

void func_806A7B28(void) {
    actorPathCollectibleUpdate(&D_80720F98);
}

extern u8 D_80721028;

void func_806A7B4C(void) {
    actorPathCollectibleUpdate(&D_80721028);
}

extern u8 D_80721004;

void func_806A7B70(void) {
    actorPathCollectibleUpdate(&D_80721004);
}

extern u8 D_80720FE0;

void func_806A7B94(void) {
    actorPathCollectibleUpdate(&D_80720FE0);
}

void func_806A7BB8(void) {
    actorPathCollectibleUpdate(&D_80721004);
}


typedef struct SfxTable {
    s32 unk0[7];
} SfxTable;

extern u8 gPlayerCharacterId;
extern u8 D_807FBD70;
extern u8 D_807FC954[];
extern u32 gFrameCounter;
extern u8 D_80721170;
extern SfxTable D_807504A4;
s32 randomNonNegative(void);
s32 slotQueueGetMaxValue(s32, s32);

void effectActorSparkleTick(void) {
    s32 flag;
    s32 idx;
    SfxTable table;

    flag = D_807FC954[gPlayerCharacterId * 94] & 1;
    if (!(D_807FBB40->unk60 & 0x10)) {
        actorAppendModelSubNode(D_807FBB40, 0.0f, 10.0f, 0.0f, -1);
        actorSetCollisionRadius(D_807FBB40, 175.0f);
        actorAppendModelNode(D_807FBB40, 0.0f, 10.0f, 0.0f, 80.0f, -1);
        D_807FBB40->unkA4 = 99999.0f;
        actorUpdateFloorContactAndTilt(D_807FBB40, 0);
    }
    func_8067ACB4(D_807FBB40);
    if (flag != 0) {
        if (D_807FBD70 == 4) {
            if (gFrameCounter % 5 == 0) {
                idx = (randomNonNegative() >> 15) % 0xFF % 7;
                table = D_807504A4;
                func_8071498C(&effectOrbitSourceUpdate);
                func_807149FC(-1);
                func_807149B8(1);
                func_80714950(100);
                func_80714C08((void *)table.unk0[idx], 0.2f, D_807FBB40, 1, 0);
                sfxAllocateChannel(0x7F, 1.0f);
                slotQueueUpdate(7, 0, 0);
                slotQueueAddValue(7, 0, (s16)slotQueueGetMaxValue(7, 0));
            }
        }
    }
    if (!(gFrameCounter & 0xF)) {
        func_807149B8(1);
        func_8071498C(&effectProximityFadeUpdate);
        func_80714950(0x226);
        func_80714998(2);
        func_807149C8(0xFF, 0xFF, 0xFF, flag ? 0xFF : 0x7F);
        func_80714C08(&D_80721170, 0.4f, D_807FBB40, 1, 2);
    }
    if (D_807FBB40->unkA4 != 99999.0f) {
        billboardSubmit(D_807FBB40, 0x3C8, 0x40, 0x40, 0xE, 0xE, 1, 0x96, 0x78, 0, 1.0f);
    }
}

typedef struct ActorDrawBuffer {
    u8 pad0[0x20];
    void *unk20;
} ActorDrawBuffer;

typedef struct SparkleState {
    f32 unk0;
    s16 unk4;
} SparkleState;

typedef struct SparkleBuffer {
    u8 unk0;
    u8 unk1;
    u8 pad2[2];
    f32 unk4;
    f32 unk8;
    f32 unkC;
    u8 unk10;
} SparkleBuffer;

extern u8 D_807504C8;
extern u8 D_807504CC;
extern u8 D_807504D0;
extern f32 D_807504C0;
extern f32 D_807504C4;
void *heapAlloc(s32);
void heapClearBlock(void *);

void effectActorShrinkTick(void) {
    SparkleState *temp_v1;
    SparkleBuffer *temp_v0;

    temp_v1 = D_807FBB40->unk174;
    if (!(D_807FBB40->unk60 & 0x10)) {
        ((ActorDrawBuffer *)D_807FBB40->unk4)->unk20 = heapAlloc(0x20);
        heapClearBlock(((ActorDrawBuffer *)D_807FBB40->unk4)->unk20);
        temp_v1->unk4 = 0;
        temp_v1->unk0 = 1.0f;
        D_807FBB40->unk60 &= ~0x8000;
        D_807FBB40->unk60 |= 0x40000000;
        D_807FBB40->unk128 = D_807504CC;
    }
    if (D_807504D0 < D_807FBB40->unk128) {
        D_807FBB40->unk128 -= D_807504D0;
    }
    temp_v1->unk4 += 1;
    if (D_807504C4 < (f32)temp_v1->unk4) {
        actorDespawn(D_807FBB40);
    } else {
        temp_v1->unk0 *= D_807504C0;
        temp_v0 = ((ActorDrawBuffer *)D_807FBB40->unk4)->unk20;
        temp_v0->unk0 = D_807504C8;
        temp_v0->unk1 = 0xFF;
        temp_v0->unk4 = temp_v1->unk0;
        temp_v0->unk8 = temp_v1->unk0;
        temp_v0->unkC = temp_v1->unk0;
        temp_v0->unk10 = 0xFF;
        actorUpdateModelMatrix(D_807FBB40, 0);
    }
}


void func_806A8070(void) {
    if (!(D_807FBB40->unk60 & 0x10)) {
        D_807FBB40->unk60 |= 0x40000000;
    }
    actorUpdateModelMatrix(D_807FBB40, 0);
}
