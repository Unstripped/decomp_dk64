// func_8067B4C8 (src/global/80150.c): from .scratch/R2H/func_8067B4C8_best.c
typedef struct R2H_ActorSub4_1C {
    u8 unk0;
    u8 unk1;
    s16 unk2;
    s16 unk4;
    s16 unk6;
    u8 unk8;
} R2H_ActorSub4_1C;

typedef struct R2H_ActorSub4 {
    u8 pad0[0x1C];
    R2H_ActorSub4_1C *unk1C;
} R2H_ActorSub4;

typedef struct R2H_SpawnArgs {
    f32 yaw;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    u8 unk14;
    u8 pad15[3];
    s32 unk18;
} R2H_SpawnArgs;

typedef struct R2H_8067B4C8 {
    Actor *unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    u8 unk14;
    u8 unk15;
} R2H_8067B4C8;

typedef struct R2H_ActorSub174_B4C8 {
    u8 pad0[0xB0];
    f32 unkB0;
    f32 unkB4;
    f32 unkB8;
} R2H_ActorSub174_B4C8;

extern u8 D_8071FBC8;

void *func_80610FE8(s32);
void func_80602A94(s32, f32);
void func_80679200(Actor *, s32, s32, u8, s32, void *);
void func_80679290(Actor *, Actor *, s32, s32, s32, s32, s32);
void func_8067AAB8(Actor *, Actor *, s16, f32, s16);
void func_80714C08(void *, f32, void *, s32, s32);

void func_8067B4C8(void) {
    Actor *temp_s0;
    R2H_8067B4C8 *temp_s2;
    s32 i;

    temp_s0 = D_807FBB40;
    temp_s2 = (R2H_8067B4C8 *)temp_s0->unk174;
    if (!(D_807FBB40->unk60 & 0x10)) {
        ((R2H_ActorSub4 *)D_807FBB40->unk4)->unk1C = (R2H_ActorSub4_1C *)func_80610FE8(0x10);
        ((R2H_ActorSub4 *)D_807FBB40->unk4)->unk1C->unk0 = 0x7F;
        ((R2H_ActorSub4 *)D_807FBB40->unk4)->unk1C->unk1 = 2;
        ((R2H_ActorSub4 *)D_807FBB40->unk4)->unk1C->unk2 = (s16)(u32)((((R2H_SpawnArgs *)D_807FBB40->unk124)->yaw * 65536.0f) / 360.0f);
        ((R2H_ActorSub4 *)D_807FBB40->unk4)->unk1C->unk4 = 0;
        ((R2H_ActorSub4 *)D_807FBB40->unk4)->unk1C->unk6 = 0;
        ((R2H_ActorSub4 *)D_807FBB40->unk4)->unk1C->unk8 = 0;
        temp_s2->unk4 = ((R2H_SpawnArgs *)D_807FBB40->unk124)->unk4;
        temp_s2->unk8 = ((R2H_SpawnArgs *)D_807FBB40->unk124)->unk8;
        temp_s2->unkC = ((R2H_SpawnArgs *)D_807FBB40->unk124)->unkC;
        temp_s2->unk10 = ((R2H_SpawnArgs *)D_807FBB40->unk124)->unk10;
        temp_s2->unk15 = ((R2H_SpawnArgs *)D_807FBB40->unk124)->unk14;
        if (((R2H_SpawnArgs *)D_807FBB40->unk124)->unk18 == 1 && func_8067B450(D_807FBB40) == 0) {
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
        func_8061CC40(0, temp_s2->unk15, 1);
    }
    switch (D_807FBB40->unk154) {
    case 1:
        if (--temp_s2->unk14 == 6) {
            func_80602A94(0x2C, 1.0f);
        }
        if (temp_s2->unk14 == 0) {
            D_807FBB40->unk154 = 2;
        }
        break;
    case 2:
        func_80679200(temp_s2->unk0, (s32)D_807FBB40, 0x40, 1, 0, 0);
        ((R2H_ActorSub174_B4C8 *)temp_s2->unk0->unk174)->unkB0 = temp_s2->unk8;
        ((R2H_ActorSub174_B4C8 *)temp_s2->unk0->unk174)->unkB4 = temp_s2->unkC;
        ((R2H_ActorSub174_B4C8 *)temp_s2->unk0->unk174)->unkB8 = temp_s2->unk10;
        func_8067AAB8(D_807FBB40, temp_s2->unk0, D_807FBB40->unkE6, 0.0f, temp_s2->unk4);
        func_80679290(D_807FBB40, D_807FBB40, 0x800, 2, 0, 0, 0xA);
        func_80714998(2);
        func_807149B8(1);
        func_80714C08(&D_8071FBC8, 2.0f, D_807FBB40, 1, 2);
        func_806086CC(D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84, 0x17, 0xFF, 0x7F, 0x19, 0x1E, 0.3f, 0);
        D_807FBB40->unk154++;
        temp_s2->unk14 = 4;
        break;
    case 3:
        if (temp_s2->unk14-- == 0) {
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
