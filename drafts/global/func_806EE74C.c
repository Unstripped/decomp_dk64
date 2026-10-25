// func_806EE74C (src/global/EFDC0.c): stage 6: exact blocks/frame; four-register assignment differs only in final pointer store
typedef struct {
    u8 pad0[0x88];
    Actor *unk88;
} EfDPlayerState;

#define EfDPS ((EfDPlayerState *)D_807FD580)

extern s32 func_806EB400(Actor *);
extern void func_806EEAF8(s16);

void func_806EE74C(void) {
    Actor *actor;
    u8 value;

    if (func_806EB400(D_807FBB48) != 0) {
        if ((D_8076A0A8 != 0x52) && (D_8076A0A8 != 0xE)) {
            func_806EEAF8(0x40);
            return;
        }
        value = 1;
        actor = EfDPS->unk88;
        ((u8 *)actor->unk174)[0x45] = value;
    }
}
