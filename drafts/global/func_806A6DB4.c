// func_806A6DB4 (src/global/AA960.c): stage 6: size/frame/blocks/literals match; only temp-register naming differs (expected v1/t1/t2 vs built t6/t7/t9/t0 in the mathAngleArcMidpoint tail, and tN rotations after). Key fixes vs old draft: (a) the unk58-sfx call and temp_v1->unk0++ are INSIDE the if((unk6A&1)&&!(unk6C&1)) block; (b) unkB8 / 2 (integer constant, so IDO emits div.s by 2.0f; /2.0f folds to *0.5f); (c) 'temp = 0xC8;' before the switch makes uopt color the sfx-id temp (no home-slot store); temp shared with the mathAngleArcMidpoint result.
typedef struct AA960Config124 {
    f32 unk0;
    f32 unk4;
    f32 unk8;
} AA960Config124;

typedef struct AA960State174 {
    u8 unk0;
    u8 unk1;
    s8 unk2;
    u8 pad3[1];
    u16 unk4;
    s16 unk6;
    u16 unk8;
    s16 unkA;
} AA960State174;

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
void func_806086CC(f32, f32, f32, s32, s32, s32, s32, s32, f32, s32);
void actorAppendModelNode(Actor *, f32, f32, f32, f32, s32);
void actorAppendModelSubNode(Actor *, f32, f32, f32, s32);
void actorSetCollisionRadius(Actor *, f32);
void actorUpdateModelMatrix(Actor *, s32);

typedef struct AA960PhysicsActor {
    u8 pad0[0xC0];
    f32 unkC0;
    u8 padC4[0xEE - 0xC4];
    s16 unkEE;
    u8 padF0[0xFA - 0xF0];
    s16 unkFA;
} AA960PhysicsActor;

#define AA960_PHY ((AA960PhysicsActor *)D_807FBB40)

void func_806A6DB4(u8);

void func_806A6DB4(u8 arg0) {
    AA960State174 *temp_v1;
    s32 temp;

    temp_v1 = D_807FBB40->unk174;
    if (!(D_807FBB40->unk60 & 0x10)) {
        D_807FBB40->unk60 |= 0x801000;
        D_807FBB40->unk16A = 0xFF;
        D_807FBB40->unk16B = 0xFF;
        D_807FBB40->unk16C = 0xFF;
        D_807FBB40->unk60 &= ~0x8000;
        D_807FBB40->unk154 = (s32)((AA960Config124 *)D_807FBB40->unk124)->unk0;
        AA960_PHY->unkEE = ((AA960Config124 *)D_807FBB40->unk124)->unk4;
        D_807FBB40->unkE6 = AA960_PHY->unkEE;
        temp_v1->unk0 = 0;
        temp_v1->unk1 = 1;
        temp_v1->unkA = ((AA960Config124 *)D_807FBB40->unk124)->unk8;
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
        AA960_PHY->unkEE = temp + (temp - ((AA960_PHY->unkEE + 0x800) & 0xFFF));
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
                func_806086CC(D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84, 0x2A1, temp, 0x7F, 0, 0, 0.0f, 0);
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
