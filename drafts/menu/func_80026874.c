// func_80026874 (src/menu/1AF0.c): NON_MATCHING parked, stage 6. K&R def (arg1 only, a2 unused: file decl changed to 'void func_80026874();'). Only diff: D_807FBB60 address temp a0 (mine v1) and player ptr v1 (mine v0); jtbl relocs expected. Tried p var, ordering, sel var, line joins, dead stmts.
typedef struct {
    char pad0[4];
    Struct_BB40_58 *unk4;
} MenuM1b_C924;
#define M1B_C924 ((MenuM1b_C924 *)D_807FC924)
extern s32 D_807FBB60;
s32 func_806F8EDC(s32, s32);

void renderCallbacksRegister(void *, void *, s32);
void slotQueueCancel(s32, s32);
s32 actorSpawn(s32, s32);
void func_80614E78(void *, s32);

void func_80026874(arg0, arg1)
Struct_80025D14 *arg0;
void *arg1;
{
    s32 sp24;
    s32 sp20;

    switch (arg0->unkE) {
    case 0:
        if (currentActorTestClearFlag() != 0) {
            currentActorClearFlag();
            arg0->unkE++;
        }
        break;
    case 1:
    case 5:
        renderCallbacksRegister(func_80025B64, D_807FBB40, 3);
        break;
    case 10:
        if (func_80026250(arg0) == 0) {
            slotQueueCancel(1, 0);
            slotQueueCancel(0xE, 0);
            func_80025E04(arg0, (s32)arg1);
            switch (arg0->unkB) {
            case 0:
            case 1:
                playerStateQueueCallback(0x52, 0, 0);
                D_807FBB60 &= 0xFFFEFFCF;
                M1B_C924->unk4->unk60 |= 0x40000000;
                break;
            case 4:
                actorSpawn(0x144, 0);
                playerStateQueueCallback(0x53, 0, 0);
                break;
            case 2:
            case 3:
                actorSpawn(0x144, 0);
                func_80614E78(M1B_C924->unk4, 0x85);
                break;
            }
            camStartPath((s32)M1B_C924->unk4, 2, 1);
            arg0->unkD = 2;
            arg0->unkE = 0;
        } else {
            camStartPath(0, 0xA, 1);
            flagSet(0x61, 1, 2);
            arg0->unkE++;
        }
        break;
    case 15:
        sp24 = -1;
        switch (D_807FBB40->unk58) {
        case 0xBD:
            sp24 = 8;
            if (func_80026250(arg0) != 0) {
                arg0->unkA = 1;
                menuTransitionToSubmenu(arg0, arg1);
                return;
            }
            sp20 = 0xA;
            goto done;
        case 0xBF:
            sp24 = 9;
            sp20 = 0x11;
            goto done;
        case 0xBE:
            sp24 = 7;
            sp20 = 0x10;
        default:
        done:
            slotQueueCancel(1, 0);
            slotQueueCancel(0xE, 0);
            camStartPath((s32)M1B_C924->unk4, 3, 1);
            arg0->unkD = 3;
            arg0->unkE = 0;
            func_8070D8C0(D_807FBB40, sp24, sp20);
            break;
        }
        break;
    }
}
