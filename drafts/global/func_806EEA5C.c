// func_806EEA5C (src/global/EFDC0.c): stage 6: exact frame and data flow; original direct form differs only branch idiom/register allocation around 1-versus-2 action
typedef struct {
    u8 pad0[0x58];
    s32 unk58;
} EfDA5CObject;

typedef struct {
    u8 pad0[0xDC];
    EfDA5CObject *unkDC;
} EfDA5CState;

#define EfDA5CPS ((EfDA5CState *)D_807FD580)

void func_806EEA5C(void) {
    if (func_806EB400(D_807FBB48) != 0) {
        EfDA5CPS->unkDC = (EfDA5CObject *)EfDPlayer[D_807FC929].unk2A0;
        if ((EfDA5CPS->unkDC != NULL) && (EfDA5CPS->unkDC->unk58 == 0x123)) {
            func_806EEAF8(2);
        } else {
            func_806EEAF8(1);
        }
    }
}
