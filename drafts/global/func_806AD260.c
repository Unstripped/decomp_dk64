// func_806AD260 (src/global/B1F60.c): stage 5 (OlR2e revisit): frame 0x20 ok, structure matches (per-arm E2 'lbu a0,0x154(t); b; move v0,a0' arm tails) once EVERY unk154 read is the global expr D_807FBB40->unk154 (first switch selector + M1/M2 args), actor local only for unk6A/unk155/sfx/unk154=0x40, and case1 unk155++ is 'actor = D_807FBB40; actor->unk155++' (a2). Dead ifs 'if (D_807FBB40) {}' after the two actorMoveWithinZone(0x37..) arms + 'if (D_807FBB40->unk154) {}' before 2nd switch. Remaining 31 insns: switch-temp candidate (883|0 ucvt of unk154 load) gets a3 (forbidden v0..a2 because P-load candidate 689|0 is coloured v0 over arm tails) instead of v0, so arm tails are 'lbu a3,0x154(t)' with no move and sub-case arms load P via v0; ring t temps follow. Fix idea: make P (D_807FBB40 value) not a candidate across the arms (expected loads it into plain t temps). K&R base: permuter cannot parse it; deadsweep needs --body with a GLOBAL_ASM-pragma copy.
#include "actor.h"

typedef struct B1F60Actor {
    /* 0x000 */ u8 pad0[0xC0];
    /* 0x0C0 */ f32 unkC0;
    /* 0x0C4 */ u8 padC4[0x91];
    /* 0x155 */ u8 unk155;
} B1F60Actor;

typedef struct B1F60View98 {
    /* 0x00 */ u8 pad0[0x28];
    /* 0x28 */ s16 unk28;
    /* 0x2A */ s16 unk2A;
} B1F60View98;

#define B1F60A ((B1F60Actor *)D_807FBB40)

extern Actor *D_807FBB40;
extern ActorGlobalState D_807FBB70;
void sfxSpawnTableNodes(Actor *);
u32 actorMoveWithinZone(u8, f32, f32, u16, f32);
void func_8072B7CC(s32);
void func_8072C918(s32, s32, s32);
void patrolPathStep(s32, s32);
void func_8072D714();
void func_8072DC7C(s32);
void func_806AD260();

void func_806AD260(arg0, arg1, arg2)
s16 arg0;
u8 arg1;
u16 arg2;
{
    Actor *actor;

    if (arg0 != 0 && (D_807FBB70.unk200 == 9 || D_807FBB70.unk15 != 0)) {
        actor = D_807FBB40;
        if (actor->unk154 != 0x37) {
            ((B1F60Actor *)actor)->unkC0 = 200.0f;
            func_8072D714(D_807FBB70.unk1FC, arg0, actor);
        }
    }
    actor = D_807FBB40;
    switch (D_807FBB40->unk154) {
        case 1:
        case 0x10:
        case 0x15:
        case 0x23:
            actorMoveWithinZone(D_807FBB40->unk154, D_807FDC94->unk7C, D_807FDC94->unk84, (actor->unk6A & 1) ? arg2 : (arg2 | 2), 0.0f);
            break;
        case 2:
        case 3:
        case 7:
        case 0x35:
            actorMoveWithinZone(D_807FBB40->unk154, (f32)D_807FDC90->unkA, (f32)D_807FDC90->unkE, arg2, 0.0f);
            break;
        case 0x37:
            switch (((B1F60Actor *)actor)->unk155) {
                case 0:
                    actorMoveWithinZone(0x37, 0.0f, 0.0f, (arg2 | 0x4200) & 0xFFFF, 0.0f);
                    if (D_807FBB40) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                    break;
                case 1:
                    sfxSpawnTableNodes(actor);
                    if (arg1 != 0) {
                        B1F60A->unk155 = 2;
                        break;
                    }
                    B1F60A->unkC0 = 100.0f;
                    actor = D_807FBB40;
                    ((B1F60Actor *)actor)->unk155++;
                case 2:
                    actorMoveWithinZone(0x37, 0.0f, 0.0f, (arg2 | 0x4200) & 0xFFFF, 0.0f);
                    if (D_807FBB40) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                    break;
                case 3:
                    func_8072DC7C(0xA);
                    break;
                case 4:
                    actor->unk154 = 0x40;
                    break;
            }
            break;
        default:
            func_8072B7CC(((B1F60View98 *)D_807FDC98)->unk28);
            break;
    }
    if (D_807FBB40->unk154) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
    switch (D_807FBB40->unk154) {
        case 2:
        case 3:
            patrolPathStep(D_807FBB40->unk154, 1);
        default:
            func_8072C918(0x4C90, ((B1F60View98 *)D_807FDC98)->unk28, ((B1F60View98 *)D_807FDC98)->unk2A);
        case 0x37:
        case 0x40:
            break;
    }
}
