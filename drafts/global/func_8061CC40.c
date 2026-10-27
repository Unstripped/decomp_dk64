// func_8061CC40 (src/global/201B0.c): text-exact with u64 D_807476D0/D_807F5CE0 DEFINED in TU (blocked on 201B0 data/bss split)
extern CamActor *D_807F5D10;
extern u8 D_807476EC;
extern s16 D_807476F8;
extern CamPathData D_807F5BF0;
extern CamPathData D_807F5B10;
extern void *D_807F5D0C;
extern Actor *D_807FBB44;
u64 D_807476D0;
extern u8 D_807476D8;
extern s16 D_807476F0;
extern u8 D_80770DC9;
extern u8 D_807F5CF6;
extern u8 D_8074E77C;
u64 D_807F5CE0;
extern u8 D_807F5D14;
typedef struct CamC_Struct807FD580 {
    /* 0x00 */ u8 pad0[0x10];
    /* 0x10 */ s16 unk10;
} CamC_Struct807FD580;
extern CamC_Struct807FD580 *D_807FD580;

s32 actorSpawn(s32, s32);
void func_80029140(s16 *);
void currentActorClearFlag(void);
s16 func_8061C804(s16);
void setRandomSeed(s32);
s32 func_8070B318(void);

u16 func_8061CC40(void *arg0, s16 arg1, u8 arg2) {
    u16 ret = 0;

    if (D_807444EC == 1 && (D_807F5CF4 & 0x80)) {
        return 0;
    }
    if ((arg2 & 4) && D_8076A0A8 != 0) {
        D_807476FC = &D_807F5BF0;
    } else {
        D_807476FC = &D_807F5B10;
    }
    if (actorSpawn(0xAD, 0) != 0) {
        D_807F5D0C = D_807FBB44;
        D_807FBB44->unk144 = 1;
    } else {
        return 0;
    }
    if (!(arg2 & 4)) {
        if (D_807FBB64 & 1) {
            func_80029140(&arg1);
        }
    }
    if (arg0 != NULL) {
        D_807F5CE8 = arg0;
    } else {
        D_807F5CE8 = *(void **)((u8 *)D_807FC924 + 4);
    }
    D_807444EC = 1;
    if (!(arg2 & 8)) {
        D_8076A0B1 |= 0x10;
        D_8076A0B3 = 0;
    }
    D_807476D0 = osGetTime();
    D_807476F4 = arg1;
    D_807476F8 = arg1;
    D_807F5CF4 = arg2;
    D_807F5CFA = 0;
    D_807476D8 = 0;
    D_807476E4 = 0;
    D_807F5CEC = 0;
    D_807F5CF0 = 0;
    D_807F5CF2 = 0;
    D_807F5CEE = 0;
    D_807476F0 = 0;
    D_807F5CF6 = D_80770DC9;
    D_807FBB60 |= 0x2000;
    D_807FBB60 &= ~0x1001;
    D_807FBB4C->unkB8 = 0.0f;
    if (D_8074E77C == 7) {
        *(f32 *)D_807FBB4C->unkC0 = 0.0f;
    }
    D_807FBB4C->unk60 |= 0x400;
    D_807FD580->unk10 = 0;
    D_807F5D10->unkE4 = 0;
    currentActorClearFlag();
    if (D_807476EC != 0) {
        ret = func_8061C804(arg1);
    }
    D_807476EC = 0;
    if (arg1 == 0 && D_8076A0A8 == 0x99) {
        setRandomSeed(0x8E32B6F7);
        D_807F5CE0 = osGetTime();
        D_807F5D14 = 0;
    } else if (func_8070B318() == 0) {
        D_807F5CE0 = 0;
    }
    return ret;
}
