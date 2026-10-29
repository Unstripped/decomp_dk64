// func_8067C71C (src/global/80150.c): Stage 4 park (frame 0xF8 matches, callee-saved {s0,s1,s2} matches, 0 opcode diffs, 78/78 segments matched in length, regalloc only)
// Best draft of func_8067C71C
// Frame size matches (0xF8), 1367 of 1386 instructions (~98.6% complete, -19 insns diff).

typedef f32 KaL9_MtxF[4][4];

typedef struct KaL9_Actor174 {
    /* 0x00 */ struct Actor *unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ u8 unk18;
    /* 0x19 */ u8 unk19;
    /* 0x1A */ u16 unk1A;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ s32 unk20;
    /* 0x24 */ f32 unk24;
    /* 0x28 */ f32 unk28;
    /* 0x2C */ s32 unk2C;
    /* 0x30 */ u8 unk30;
    /* 0x31 */ u8 pad31[3];
    /* 0x34 */ f32 unk34;
    /* 0x38 */ u8 unk38;
    /* 0x39 */ u8 unk39;
    /* 0x3A */ u8 unk3A;
} KaL9_Actor174;

typedef struct KaL9_ActorSub118 {
    u8 pad0[0xC];
    u8 unkC;
    u8 padD;
    s16 unkE;
    s16 unk10;
} KaL9_ActorSub118;

typedef struct KaL9_Actor {
    /* 0x000 */ u8 pad0[0x4];
    /* 0x004 */ ActorSub4 *unk4;
    /* 0x008 */ u8 pad8[0x50];
    /* 0x058 */ s32 unk58;
    /* 0x05C */ u16 unk5C;
    /* 0x05E */ u8 unk5E[2];
    /* 0x060 */ u32 unk60;
    /* 0x064 */ u8 pad64[4];
    /* 0x068 */ u16 unk68;
    /* 0x06A */ u16 unk6A;
    /* 0x06C */ u16 unk6C;
    /* 0x06E */ u8 pad6E[0xE];
    /* 0x07C */ f32 unk7C;
    /* 0x080 */ f32 unk80;
    /* 0x084 */ f32 unk84;
    /* 0x088 */ f32 unk88;
    /* 0x08C */ f32 unk8C;
    /* 0x090 */ f32 unk90;
    /* 0x094 */ u8 pad94[8];
    /* 0x09C */ f32 unk9C;
    /* 0x0A0 */ f32 unkA0;
    /* 0x0A4 */ f32 unkA4;
    /* 0x0A8 */ u8 padA8[4];
    /* 0x0AC */ f32 unkAC;
    /* 0x0B0 */ u8 padB0[4];
    /* 0x0B4 */ f32 unkB4;
    /* 0x0B8 */ f32 unkB8;
    /* 0x0BC */ f32 unkBC;
    /* 0x0C0 */ f32 unkC0;
    /* 0x0C4 */ u8 padC4[0x18];
    /* 0x0DC */ s16 unkDC;
    /* 0x0DE */ s16 unkDE;
    /* 0x0E0 */ u8 padE0[6];
    /* 0x0E6 */ s16 unkE6;
    /* 0x0E8 */ u8 padE8[6];
    /* 0x0EE */ s16 unkEE;
    /* 0x0F0 */ u8 padF0[2];
    /* 0x0F2 */ s16 unkF2;
    /* 0x0F4 */ s16 unkF4;
    /* 0x0F6 */ s16 unkF6;
    /* 0x0F8 */ u8 padF8[2];
    /* 0x0FA */ s16 unkFA;
    /* 0x0FC */ u8 unkFC;
    /* 0x0FD */ u8 padFD[0x13];
    /* 0x110 */ u8 unk110;
    /* 0x111 */ u8 pad111[7];
    /* 0x118 */ KaL9_ActorSub118 *unk118;
    /* 0x11C */ s32 unk11C;
    /* 0x120 */ u8 pad120[8];
    /* 0x128 */ s16 unk128;
    /* 0x12A */ s16 unk12A;
    /* 0x12C */ u8 pad12C[0x18];
    /* 0x144 */ u8 unk144;
    /* 0x145 */ u8 pad145[0xF];
    /* 0x154 */ u8 unk154;
    /* 0x155 */ u8 pad155[0x1F];
    /* 0x174 */ KaL9_Actor174 *unk174;
} KaL9_Actor;

typedef struct KaL9_ActorGlobalState {
    /* 0x000 */ u8 pad0[0x15];
    /* 0x015 */ u8 unk15;
    /* 0x016 */ u8 pad16[0xE];
    /* 0x024 */ u8 unk24;
    /* 0x025 */ u8 unk25;
    /* 0x026 */ u8 pad26[2];
    /* 0x028 */ Actor *unk28;
    /* 0x02C */ u8 unk2C;
    /* 0x02D */ u8 pad2D[3];
    /* 0x030 */ f32 unk30;
    /* 0x034 */ s16 unk34;
    /* 0x036 */ s16 unk36;
    /* 0x038 */ u8 pad38[0x1C8];
    /* 0x200 */ u8 unk200;
} KaL9_ActorGlobalState;

#define KaL9_ACTOR ((KaL9_Actor *)D_807FBB40)
#define KaL9_STATE ((KaL9_ActorGlobalState *)&D_807FBB70)
#define KaL9_ACTOR44 ((KaL9_Actor *)D_807FBB44)
#define KaL9_ACTOR4C ((KaL9_Actor *)D_807FBB4C)

extern Actor *D_807FBB44;
extern s32 D_807FBB64;
extern u8 D_807FBBA9;
extern f32 D_807FBC60;
extern f32 D_807FBC64;
extern s16 D_807FD584;
extern s32 D_8076A064;
extern s8 D_80029FA0;
extern u8 D_8071FC40;
extern u8 D_8072030C;
extern s16 D_807502D0;
extern f32 D_807502E4;
extern s16 D_80753444[];

void func_80608528(Actor *, s32, s32, s32, s32);
u32 func_806119A0(void);
f32 func_80612D1C(f32);
s32 func_8061CB50(void);
void func_8061EF4C(s32, s32, s32, f32, f32, f32, f32, f32);
void func_8065A708(f32, f32, f32, f32, f32, f32, f32, s32, s32, s32, s32);
void func_8065D254(Actor *, s32, s32, s32, s32, s32, s32, s32, s32, s32, f32);
void func_806651FC(Actor *);
void func_8066E6C8(Actor *, s32, s32);
void func_8066EA64(Actor *, s32);
void func_8066EA90(Actor *, s32);
s32 actorAngleInArc(Actor *, s16);
void mathAngleClampToArc(s16, s16, s16, s16, s16 *);
s32 func_80672BD4(Actor *);
void func_80677FA8(s32, s32);
void func_806791DC(Actor *, s32);
void func_806791EC(Actor *, s32);
void func_8067A170(Actor *, s32);
void func_8067ACB4(Actor *);
void func_8067B238(Actor *, Actor *, f32);
void func_8067E278();
void func_806CF4B8(Actor *);
void func_807149A8(s32);
void func_80714C08(void *, f32, Actor *, s32, s32);
void func_80718BF4(void);
void func_807245F0(Actor *, s32);
void animationOwnerFreeBuffer(Actor *);

void func_8067C71C(void) {
    KaL9_Actor174 *temp_s1 = KaL9_ACTOR->unk174;
    KaL9_MtxF spB4;
    KaL9_MtxF sp74;
    f32 var_fv0;
    s16 temp_a0;
    s32 pad[2];

    temp_s1 = KaL9_ACTOR->unk174;
    if (!(KaL9_ACTOR->unk60 & 0x10)) {
        KaL9_ACTOR->unkFA = 0x270F;
        temp_s1->unk38 = 0;
        temp_s1->unk39 = 0;
        if (KaL9_ACTOR->unk58 == 0x1A) {
            KaL9_ACTOR->unk60 |= 0x1000;
            func_807149B8(1);
            func_807149FC(-1);
            func_807149A8((s16)((f64)KaL9_ACTOR->unk12A * 0.75));
            func_80714C08(&D_8072030C, 0.14f, D_807FBB40, 1, 2);
            func_8066EA90(D_807FBB40, 3);
        }
        KaL9_ACTOR->unkA4 = 99999.0f;
        actorUpdateFloorContactAndTilt(D_807FBB40, 0.0f);
        if (func_80672BD4(D_807FBB40)) {
            KaL9_ACTOR->unk154 = 2;
            KaL9_ACTOR->unk68 |= 1;
            temp_s1->unkC = 0x1E;
            KaL9_ACTOR->unk144 = 2;
            temp_s1->unk8 = 360.0f;
            temp_s1->unk14 = 0.0f;
        }
        KaL9_ACTOR->unk68 |= 0x40;
    }

    if (KaL9_STATE->unk24 != 0) {
        if (temp_s1->unk39 == 0) {
            temp_s1->unk0 = (Actor *)KaL9_STATE->unk28;
            KaL9_ACTOR->unk154 = 1;
            temp_s1->unk8 = 360.0f;
            func_806791EC(D_807FBB40, 0x8000);
            func_8067A170(temp_s1->unk0, 1);
            KaL9_ACTOR->unk144 = 0x2C;
            animationOwnerFreeBuffer(D_807FBB40);
        } else {
            func_806CF4B8(D_807FBB40);
        }
    }

    if (KaL9_STATE->unk25 != 0) {
        KaL9_ACTOR->unk154 = 2;
        temp_s1->unkC = 0x1E;
        KaL9_ACTOR->unk144 = 0x3C;
        func_806791DC(D_807FBB40, 0x8000);
    }

    if (((KaL9_STATE->unk15 != 0) || (KaL9_STATE->unk200 == 9)) && (temp_s1->unk39 == 0)) {
        KaL9_ACTOR->unk154 = 4;
        func_806CF4B8(D_807FBB40);
    }

    if (temp_s1->unk39 != 0 && (KaL9_STATE->unk15 != 0 || KaL9_STATE->unk200 == 9)) {
        KaL9_ACTOR->unk144 = 1;
    }

    if (KaL9_STATE->unk2C != 0) {
        KaL9_ACTOR->unk154 = 3;
        KaL9_ACTOR->unk144 = 0x3C;
        func_806791DC(D_807FBB40, 0x8000);
        KaL9_ACTOR->unkE6 = KaL9_STATE->unk36;
        KaL9_ACTOR->unkEE = KaL9_STATE->unk36;
        KaL9_ACTOR->unkC0 = KaL9_STATE->unk30;
        temp_s1->unk4 = D_8076A064;
        temp_s1->unk18 = 0;
        temp_s1->unk1A = 0;
        KaL9_ACTOR->unkB8 = KaL9_STATE->unk34;
        func_8067A170(temp_s1->unk0, 1);
    }

    func_8067ACB4(D_807FBB40);
    switch (KaL9_ACTOR->unk154) {
    case 0:
        KaL9_ACTOR->unk144 = 2;
        temp_s1->unk8 = 360.0f;
        temp_s1->unk14 = 0.0f;
        func_8066E6C8(D_807FBB40, 0, 1);
        func_8066E6C8(D_807FBB40, 1, 0);
        KaL9_ACTOR->unk68 |= 1;
        break;
    case 1:
        func_8066E6C8(D_807FBB40, 0, 0);
        func_8066E6C8(D_807FBB40, 1, 0);
        temp_s1->unk8 = *(f32 *)((u8 *)temp_s1->unk0->unk174 + 0x1BC);
        if (temp_s1->unk8 < 0.0) {
            temp_s1->unk8 += 360.0;
        }
        temp_s1->unk10 = ((f64)temp_s1->unk0->unkE6 / 4095.0) * 360.0;
        KaL9_ACTOR->unk68 &= ~1;
        break;
    case 2:
        func_8066E6C8(D_807FBB40, 0, 1);
        func_8066E6C8(D_807FBB40, 1, 0);
        if (--temp_s1->unkC == 0) {
            KaL9_ACTOR->unk154 = 0;
        } else if (func_80672BD4(D_807FBB40)) {
            temp_s1->unkC = 0x1E;
        }
        temp_s1->unk8 += 16.0;
        if (temp_s1->unk8 > 360.0) {
            temp_s1->unk8 = 360.0f;
        }
        KaL9_ACTOR->unkC0 = -200.0f;
        KaL9_ACTOR->unkB8 = 0.0f;
        KaL9_ACTOR->unk68 |= 1;
        break;
    case 3:
        func_8066E6C8(D_807FBB40, 0, 1);
        func_8066E6C8(D_807FBB40, 1, 1);
        KaL9_ACTOR->unkC0 += D_807502E4;
        if (KaL9_ACTOR->unkC0 < (f32)D_807502D0) {
            KaL9_ACTOR->unkC0 = (f32)D_807502D0;
        }
        temp_s1->unk14 -= 10.0f;
        if (KaL9_ACTOR->unkFC != 0 && actorAngleInArc(D_807FBB40, KaL9_ACTOR->unkE6) == 0) {
            func_80608528(D_807FBB40, 0x23, 0xFF, 0x7F, 1);
            func_80608528(D_807FBB40, 0x17, 0xFF, 0x7F, 1);
            KaL9_ACTOR->unk154 = 8;
        }
        KaL9_ACTOR->unk68 &= ~1;
        break;
    case 4:
        temp_s1->unk39 = 1;
        KaL9_ACTOR->unk154 = 8;
        break;
    case 5:
        func_8066E6C8(D_807FBB40, 0, 1);
        func_8066E6C8(D_807FBB40, 1, 1);
        temp_s1->unk28 -= 3.0;
        if (temp_s1->unk28 < 270.0) {
            temp_s1->unk28 = 270.0f;
        }
        KaL9_ACTOR->unk80 = temp_s1->unk1C + (f32)(func_80612D1C((f32)temp_s1->unk20 / 12.6) * 1.5);
        temp_s1->unk8 = temp_s1->unk28 + func_80612D1C((f32)temp_s1->unk20 / 9.34) * 7.0f;
        temp_s1->unk20++;
        var_fv0 = (f32) (-5.0 - temp_s1->unk24);
        var_fv0 = (f32) (var_fv0 / -5.0);
        var_fv0 = (f32) (var_fv0 * -0.5);
        if (D_807FBBA9 == 0) {
            var_fv0 = (f32) (-0.5 - var_fv0);
            var_fv0 = (f32) (0.0 - var_fv0);
        }
        temp_s1->unk24 += var_fv0;
        KaL9_ACTOR->unk80 += temp_s1->unk24;
        if (--temp_s1->unk2C == 0 || temp_s1->unk2C == 5 || temp_s1->unk2C == 10 ||
            temp_s1->unk2C == 15 || temp_s1->unk2C == 20 || temp_s1->unk2C == 26) {
            func_80608528(D_807FBB40, 0x55, 0xFF, (s16)(0xA7 - temp_s1->unk2C * 2), 0);
        }
        if (temp_s1->unk2C == 0 || KaL9_ACTOR->unkAC < KaL9_ACTOR->unkA4) {
            KaL9_ACTOR->unk154 = 6;
            if (func_80612D1C((f32)temp_s1->unk20 / 9.34) > 0.0) {
                temp_s1->unk30 = 1;
            } else {
                temp_s1->unk30 = 0;
            }
            temp_s1->unk34 = 0.1f;
        }
        KaL9_ACTOR->unkC0 = 0.0f;
        KaL9_ACTOR->unkB8 = 35.0f;
        KaL9_ACTOR->unk68 |= 1;
        func_807245F0(D_807FBB40, 0);
        if (KaL9_ACTOR->unk118->unkC == 0) {
            KaL9_ACTOR->unkEE = KaL9_ACTOR->unk118->unkE;
            KaL9_ACTOR->unkB8 = (f32)KaL9_ACTOR->unk118->unk10;
        } else {
            KaL9_ACTOR->unkB8 = 0.0f;
        }
        if (KaL9_ACTOR->unkFC != 0) {
            temp_a0 = KaL9_ACTOR->unkEE;
            mathAngleClampToArc(temp_a0, temp_a0, KaL9_ACTOR->unkF4, KaL9_ACTOR->unkF6, (s16 *)&KaL9_ACTOR->unkF2);
            KaL9_ACTOR->unkEE = KaL9_ACTOR->unkF2;
        }
        break;
    case 6:
        if (((func_806119A0() / 100000) % 3) == 0) {
            func_807149B8(1);
            func_807149FC(-1);
            func_8071498C(func_80718BF4);
            func_80714CC0(&D_8071FC40, 0.0f, KaL9_ACTOR->unk7C, KaL9_ACTOR->unk80, KaL9_ACTOR->unk84);
        }
        if (temp_s1->unk30 != 0) {
            if (temp_s1->unk30 == 1) {
                temp_s1->unk8 += 1.5;
                if (temp_s1->unk8 > 360.0) {
                    temp_s1->unk8 = 360.0f;
                }
            }
        } else {
            temp_s1->unk8 -= 1.5;
            if (temp_s1->unk8 < 0.0) {
                temp_s1->unk8 = 0.0f;
            }
        }
        temp_s1->unk2C++;
        if ((temp_s1->unk2C & 3) == 0 && (u32)temp_s1->unk2C < 29) {
            func_80608528(D_807FBB40, 0x55, (0xC0 - temp_s1->unk2C * 6) & 0xFF, (s16)(temp_s1->unk2C * 2 + 0x50), 0);
        }
        temp_s1->unk34 += 2.0;
        if (temp_s1->unk34 > 40.0) {
            temp_s1->unk34 = 40.0f;
        }
        KaL9_ACTOR->unkC0 = -temp_s1->unk34;
        KaL9_ACTOR->unkB8 = 0.0f;
        if ((f64)KaL9_ACTOR->unkB4 < 0.5) {
            KaL9_ACTOR->unk154 = 7;
            temp_s1->unk2C = 0x78;
        }
        KaL9_ACTOR->unk68 &= ~1;
        break;
    case 7:
        KaL9_ACTOR->unk80 -= 0.15;
        if (--temp_s1->unk2C == 0) {
            KaL9_ACTOR->unk154 = 4;
        }
        KaL9_ACTOR->unk68 &= ~1;
        break;
    case 8:
        if ((D_807FBB64 & 1) && func_8061CB50()) {
            func_806782C0(D_807FBB40);
        } else {
            switch (KaL9_ACTOR->unk58) {
            case 0x1A:
                func_8067E278(1, 1);
                KaL9_ACTOR->unk60 &= ~0x8000;
                KaL9_ACTOR->unk128 = 0;
                KaL9_ACTOR->unk154 = 9;
                temp_s1->unk3A = 0x14;
                if (!(D_807FBB64 & 1)) {
                    func_8066EA64(D_807FBB40, 3);
                }
                func_8066EA90(D_807FBB40, 1);
                func_8066EA90(D_807FBB40, 2);
                break;
            case 0x95:
                func_80677FA8(0xDE, 0xE5);
                func_8067B238(D_807FBB44, D_807FBB40, 0.15f);
                KaL9_ACTOR44->unk11C = KaL9_ACTOR->unk11C;
                KaL9_ACTOR->unk11C = 0;
                KaL9_ACTOR44->unk80 = KaL9_ACTOR->unkA4;
                goto block_despawn;
            case 0x85:
                D_80029FA0--;
            default:
            block_despawn:
                func_8067DCC0();
                func_806782C0(D_807FBB40);
                break;
            }
        }
        break;
    case 9:
        if (temp_s1->unk3A == 0) {
            func_806782C0(D_807FBB40);
        } else {
            temp_s1->unk3A--;
        }
        var_fv0 = ((f32)temp_s1->unk3A / 20.0f) * 200.0;
        if (var_fv0 > 130.0) {
            var_fv0 = 200.0f;
        }
        func_8065A708(KaL9_ACTOR->unk7C, KaL9_ACTOR->unk80, KaL9_ACTOR->unk84, 0.0f, 0.0f, 0.0f, var_fv0, 0, 0xFF, 0xFF, 0xFF);
        func_8061EF4C(*(s32 *)((u8 *)KaL9_ACTOR4C->unk174 + 0x104), 5, 10, KaL9_ACTOR->unk7C, KaL9_ACTOR->unk80, KaL9_ACTOR->unk84, 200.0f, 400.0f);
        break;
    }

    if (KaL9_ACTOR->unk154 == 2 || KaL9_ACTOR->unk154 == 3 || KaL9_ACTOR->unk154 == 5 || KaL9_ACTOR->unk154 == 6) {
        if (KaL9_ACTOR->unk154 != 5) {
            KaL9_ACTOR->unkEE = KaL9_ACTOR->unkE6;
        }
        func_806651FC(D_807FBB40);
        actorUpdateFloorContactAndTilt(D_807FBB40, 7.0f);
        if (KaL9_ACTOR->unk154 == 2 && temp_s1->unk8 == 360.0f && (KaL9_ACTOR->unk80 - KaL9_ACTOR->unk8C) < -2.0f && (D_807FBB64 & 1)) {
            func_806CF4B8(D_807FBB40);
            KaL9_ACTOR->unk154 = 4;
            temp_s1->unk39 = 1;
        }
        if (KaL9_ACTOR->unk154 == 3 && KaL9_ACTOR->unk58 == 0x1A && (u32)D_80753444[D_807FD584] < (u32)(D_8076A064 - temp_s1->unk4)) {
            KaL9_ACTOR->unk154 = 4;
        }
        if (KaL9_ACTOR->unk154 == 3 && (KaL9_ACTOR->unk6A & 1) && !(KaL9_ACTOR->unk6C & 1)) {
            KaL9_ACTOR->unkC0 = 140.0f;
            temp_s1->unk1A++;
            if ((KaL9_ACTOR->unk58 == 0x1A && temp_s1->unk1A == 4) || (KaL9_ACTOR->unk58 == 0x95 && temp_s1->unk1A == 2)) {
                KaL9_ACTOR->unk154 = 4;
            }
            func_80608528(D_807FBB40, 0x32, 0xFF, 0x7F, 1);
        }
        if (KaL9_ACTOR->unk154 == 2 && (KaL9_ACTOR->unk6A & 4)) {
            KaL9_ACTOR->unk154 = 5;
            KaL9_ACTOR->unk80 = KaL9_ACTOR->unkAC;
            temp_s1->unk2C = 1000;
            temp_s1->unk1C = KaL9_ACTOR->unk80 - 1.5;
            temp_s1->unk20 = 0;
            temp_s1->unk28 = temp_s1->unk8;
        }
        if (KaL9_ACTOR->unk154 == 5) {
            temp_s1->unk1C = KaL9_ACTOR->unkAC;
        }
        if (KaL9_ACTOR->unk154 == 3 && (KaL9_ACTOR->unk6A & 4) && temp_s1->unk19 == 0) {
            switch (temp_s1->unk18) {
            case 0:
                KaL9_ACTOR->unkC0 = 180.0f;
                break;
            case 1:
                KaL9_ACTOR->unkC0 = 140.0f;
                break;
            case 2:
                KaL9_ACTOR->unkC0 = 100.0f;
                break;
            default:
                KaL9_ACTOR->unk154 = 5;
                KaL9_ACTOR->unk80 = KaL9_ACTOR->unkAC;
                temp_s1->unk2C = 1000;
                temp_s1->unk1C = KaL9_ACTOR->unk80 - 1.5;
                temp_s1->unk20 = 0;
                temp_s1->unk28 = temp_s1->unk8;
                break;
            }
            temp_s1->unk19 = 3;
            temp_s1->unk18++;
            KaL9_ACTOR->unkB8 -= 20.0;
        } else if (temp_s1->unk19 != 0) {
            temp_s1->unk19--;
        }
        KaL9_ACTOR->unkDC = 0x3FF;
        KaL9_ACTOR->unkDE = 0x3FF;
    } else {
        KaL9_ACTOR->unk110 = 0;
        KaL9_ACTOR->unk6A &= ~0x408;
    }

    temp_s1->unk38 = KaL9_ACTOR->unk154;
    if (KaL9_ACTOR->unk154 != 9) {
        func_8065D254(D_807FBB40, 0x3C8, 0x40, 0x40, 0xC, 0xC, 1, 0x64, 0x78, 0, 1.0f);
    }
    guScaleF(spB4, KaL9_ACTOR->unk4->unk34, KaL9_ACTOR->unk4->unk38, KaL9_ACTOR->unk4->unk3C);
    guRotateF(sp74, temp_s1->unk14, 0.0f, 1.0f, 0.0f);
    guMtxCatF(spB4, sp74, spB4);
    guRotateF(sp74, ((f64)KaL9_ACTOR->unkE6 / 4095.0) * 360.0, 0.0f, 1.0f, 0.0f);
    guMtxCatF(spB4, sp74, spB4);
    guRotateF(sp74, temp_s1->unk8 - D_807FBC60, 1.0f, 0.0f, 0.0f);
    guMtxCatF(spB4, sp74, spB4);
    guRotateF(sp74, (temp_s1->unk10 + 90.0f) - D_807FBC64, 0.0f, 1.0f, 0.0f);
    guMtxCatF(spB4, sp74, spB4);

    if (KaL9_ACTOR->unk154 == 3) {
        if (KaL9_ACTOR->unkDE < 1000) {
            guRotateF(sp74, -(((f64)KaL9_ACTOR->unkDC / 4095.0) * 360.0), 0.0f, 1.0f, 0.0f);
            guMtxCatF(spB4, sp74, spB4);
        }
        guRotateF(sp74, 90.0 - ((f64)KaL9_ACTOR->unkDE / 4095.0) * 360.0, 1.0f, 0.0f, 0.0f);
        guMtxCatF(spB4, sp74, spB4);
        if (KaL9_ACTOR->unkDE < 1000) {
            guRotateF(sp74, ((f64)KaL9_ACTOR->unkDC / 4095.0) * 360.0, 0.0f, 1.0f, 0.0f);
            guMtxCatF(spB4, sp74, spB4);
        }
    }
    guTranslateF(sp74, KaL9_ACTOR->unk7C, KaL9_ACTOR->unk80, KaL9_ACTOR->unk84);
    guMtxCatF(spB4, sp74, (float (*)[4])((u8 *)D_807FBB40 + 0xC));
}
