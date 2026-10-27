// func_80635EF0 (src/global/36880.c): stage 6: FP regs/frame/callee-saved f20-f24 match, only ~46 diff lines of int reg naming (target arg4=v0,arg5=v1,i=a0,n=a1,a=a2,p=t0,arg6=t1; ours i=v0,n=v1,p=a0,a=a1,arg6=a2,arg5=t1,arg4=t0). 'b = a' copy for first uses (permuter hint) fixed FP allocation; permuter 10min no zero; b-copy before i++ scored 40
typedef struct R36880dActorBox {
    /* 0x00 */ u8 pad0[0x5C];
    /* 0x5C */ u16 unk5C;
    /* 0x5E */ u8 pad5E[0x1E];
    /* 0x7C */ f32 unk7C;
    /* 0x80 */ f32 unk80;
    /* 0x84 */ f32 unk84;
} R36880dActorBox;

typedef struct R36880dActorRef {
    /* 0x0 */ R36880dActorBox *actor;
    /* 0x4 */ s32 unk4;
} R36880dActorRef;

extern R36880dActorRef gActiveActors[];
extern u16 gActiveActorCount;

s32 func_80635EF0(f32 arg0, f32 arg1, f32 arg2, s16 arg3, s16 arg4, s16 arg5, u16 arg6) {
    s32 i;
    R36880dActorBox *b;
    R36880dActorRef *p;
    R36880dActorBox *a;

    i = 0;
    if (gActiveActorCount > 0) {
        p = gActiveActors;
        do {
            a = p->actor;
            i++;
            b = a;
            if (b->unk5C & arg6) {
                if (arg0 - arg3 <= b->unk7C && arg1 - arg4 <= b->unk80 && arg2 - arg5 <= b->unk84 &&
                    a->unk7C <= arg3 + arg0 && a->unk80 <= arg4 + arg1 && a->unk84 <= arg5 + arg2) {
                    return 1;
                }
            }
            p++;
        } while (i < gActiveActorCount);
    }
    return 0;
}
