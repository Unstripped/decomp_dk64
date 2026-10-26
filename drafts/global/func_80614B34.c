// func_80614B34 (src/global/17B90.c): stage 4; 5 fdiff attempts. Frame/save set exact with f64 padding. Command behavior/types resolved; closest remaining diff is stack-pointer lifetime around two osVirtualToPhysical calls and loop pointer/constant allocation. Tried reduced locals, f64 padding, explicit sp24/sp20/next pointers (frame became 0x40), early pointer increments, and separate output/command locals.
typedef struct {
    void *unk0;
    u32 *unk4;
    u8 pad8[0x19];
    u8 unk21;
} P17c2DrawDisplay;

typedef struct {
    P17c2DrawDisplay *unk0;
    u8 pad4[4];
    void *unk8;
    u8 padC[0x40];
    P17c2DrawDisplay *unk4C;
    P17c2DrawDisplay *unk50;
} P17c2DrawActor;

u32 *animSetSegments(u32 *, P17c2DrawActor *);
u32 *func_80614C38();

u32 *func_80614B34(u32 *arg0, P17c2DrawActor *arg1) {
    f64 pad;
    P17c2DrawDisplay *display;
    u32 *temp;
    u32 *var_a2;
    u32 command;
    s32 i;
    s32 offset;

    display = arg1->unk0;
    if (arg1->unk4C != NULL) {
        display = arg1->unk4C;
    }
    if (arg1->unk50 != NULL) {
        display = arg1->unk50;
    }
    arg0 = animSetSegments(arg0, arg1);
    arg0 = func_80614C38(arg0, arg1, display);
    temp = arg0;
    temp[0] = 0xDB060010;
    arg0 = temp + 2;
    temp[1] = osVirtualToPhysical(arg1->unk8);
    temp = arg0;
    temp[0] = 0xDB06000C;
    arg0 = temp + 2;
    temp[1] = osVirtualToPhysical(display->unk0);
    var_a2 = arg0;
    command = 0xDE000000;
    i = 0;
    offset = 0;
    if ((s32) display->unk21 > 0) {
        do {
            var_a2[0] = command;
            var_a2[1] = *(u32 *) ((u8 *) display->unk4 + offset);
            i++;
            offset += 4;
            var_a2 += 2;
        } while (i < (s32) display->unk21);
    }
    return var_a2;
}
