// func_8067B4C8 (src/global/80150.c): stage 3: frame 0x40 matches, s0/s1 match, fixed unk14/unk15 split and case 3 decrement, s2 spilled to stack slot 0x38
typedef struct KaS2_ActorSub4_1C {
    u8 unk0;
    u8 unk1;
    s16 unk2;
    s16 unk4;
    s16 unk6;
    u8 unk8;
} KaS2_ActorSub4_1C;

typedef struct KaS2_ActorSub4 {
    u8 pad0[0x1C];
    KaS2_ActorSub4_1C *unk1C;
} KaS2_ActorSub4;

typedef struct KaS2_SpawnArgs {
    f32 yaw;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    u8 unk14;
    u8 pad15[3];
    s32 unk18;
} KaS2_SpawnArgs;

typedef struct KaS2_8067B4C8 {
    Actor *unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    u8 unk14;
    u8 unk15;
    u8 pad16[2];
} KaS2_8067B4C8;

typedef struct KaS2_ActorSub174_B4C8 {
    u8 pad0[0xB0];
    f32 unkB0;
    f32 unkB4;
    f32 unkB8;
} KaS2_ActorSub174_B4C8;

extern u8 D_8071FBC8;
void *func_80610FE8(s32);
void sfxAllocateChannel(s32, f32);
void actorAppendCallback(Actor *, s32, s32, u8, s32, void *);
void actorQueueDelayedCallback(Actor *, Actor *, s32, s32, s32, s32, s32);
void func_8067AAB8(s32, Actor *, s16, f32, s16);
void func_80714C08(void *, f32, void *, s32, s32);

void func_8067B4C8(void) {
    Actor *temp_s0;
    register KaS2_8067B4C8 *temp_s2;
    s32 i;

    temp_s0 = D_807FBB40;
    temp_s2 = (KaS2_8067B4C8 *)temp_s0->unk174;
    if (!(D_807FBB40->unk60 & 0x10)) {
        ((KaS2_ActorSub4 *)D_807FBB40->unk4)->unk1C = (KaS2_ActorSub4_1C *)func_80610FE8(0x10);
        ((KaS2_ActorSub4 *)D_807FBB40->unk4)->unk1C->unk0 = 0x7F;
        ((KaS2_ActorSub4 *)D_807FBB40->unk4)->unk1C->unk1 = 2;
        ((KaS2_ActorSub4 *)D_807FBB40->unk4)->unk1C->unk2 = (s16)(u32)((((KaS2_SpawnArgs *)D_807FBB40->unk124)->yaw * 65536.0f) / 360.0f);
        ((KaS2_ActorSub4 *)D_807FBB40->unk4)->unk1C->unk4 = 0;
        ((KaS2_ActorSub4 *)D_807FBB40->unk4)->unk1C->unk6 = 0;
        ((KaS2_ActorSub4 *)D_807FBB40->unk4)->unk1C->unk8 = 0;
        temp_s2->unk4 = ((KaS2_SpawnArgs *)D_807FBB40->unk124)->unk4;
        temp_s2->unk8 = ((KaS2_SpawnArgs *)D_807FBB40->unk124)->unk8;
        temp_s2->unkC = ((KaS2_SpawnArgs *)D_807FBB40->unk124)->unkC;
        temp_s2->unk10 = ((KaS2_SpawnArgs *)D_807FBB40->unk124)->unk10;
        temp_s2->unk15 = ((KaS2_SpawnArgs *)D_807FBB40->unk124)->unk14;
        if (((KaS2_SpawnArgs *)D_807FBB40->unk124)->unk18 == 1 && func_8067B450(D_807FBB40) == 0) {
            D_807FBB40->unk154 = 0x14;
            D_807FBB40->unk144 = 1;
            D_807FBB40->unk60 &= ~0x8000;
            D_807FBB40->unk128 = 0;
        }
        if (D_8076A0A8 == 0x22) {
            D_807FBB40->unk60 |= 0x400;
        }
        if (D_8076A0A8 == 0xC7) {
            D_807FBB40->unk12A = 0x226;
        }
    }
    if (D_807FBB70.unk200 == 4) {
        temp_s2->unk0 = (Actor *)D_807FBB70.unk1FC;
        D_807FBB40->unk154 = 1;
        temp_s2->unk14 = 0xA;
        D_807FBB40->unk144 = 1;
        temp_s2->unk0->unkE6 = D_807FBB40->unkE6;
        camStartPath(0, temp_s2->unk15, 1);
    }
    switch (D_807FBB40->unk154) {
    case 1:
        if (--temp_s2->unk14 == 6) {
            sfxAllocateChannel(0x2C, 1.0f);
        }
        if (temp_s2->unk14 == 0) {
            D_807FBB40->unk154 = 2;
        }
        break;
    case 2:
        actorAppendCallback(temp_s2->unk0, (s32)D_807FBB40, 0x40, 1, 0, 0);
        ((KaS2_ActorSub174_B4C8 *)temp_s2->unk0->unk174)->unkB0 = temp_s2->unk8;
        ((KaS2_ActorSub174_B4C8 *)temp_s2->unk0->unk174)->unkB4 = temp_s2->unkC;
        ((KaS2_ActorSub174_B4C8 *)temp_s2->unk0->unk174)->unkB8 = temp_s2->unk10;
        func_8067AAB8((s32)D_807FBB40, temp_s2->unk0, D_807FBB40->unkE6, 0.0f, temp_s2->unk4);
        actorQueueDelayedCallback(D_807FBB40, D_807FBB40, 0x800, 2, 0, 0, 0xA);
        func_80714998(2);
        func_807149B8(1);
        func_80714C08(&D_8071FBC8, 2.0f, D_807FBB40, 1, 2);
        func_806086CC(D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84, 0x17, 0xFF, 0x7F, 0x19, 0x1E, 0.3f, 0);
        D_807FBB40->unk154++;
        temp_s2->unk14 = 4;
        break;
    case 3:
        if (temp_s2->unk14 != 0) {
            temp_s2->unk14--;
        } else {
            D_807FBB40->unk154 = 0;
        }
        break;
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
    case 12:
    case 13:
    case 14:
    case 15:
    case 16:
    case 17:
    case 18:
    case 19:
        break;
    case 20:
        if (D_807FBB70.unk254 > 0) {
            i = 0;
            do {
                if (D_807FBB70.unk258[i++] == 1) {
                    D_807FBB40->unk144 = 2;
                    D_807FBB40->unk154 = 0x15;
                }
            } while (i < D_807FBB70.unk254);
        }
        if (func_8067B450(D_807FBB40) != 0) {
            D_807FBB40->unk128 = 0xFF;
            D_807FBB40->unk60 |= 0x8000;
            D_807FBB40->unk154 = 0;
        }
        break;
    case 21:
        D_807FBB40->unk128 += 10;
        if (D_807FBB40->unk128 >= 0xF1) {
            D_807FBB40->unk60 |= 0x8000;
            D_807FBB40->unk154 = 0;
        }
        break;
    }
    actorUpdateModelMatrix(D_807FBB40, 0);
}
