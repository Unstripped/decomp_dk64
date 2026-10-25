// func_8070E2AC (src/global/112080.c): stage 6: exact instructions except arg0/arg2 callee-saved allocation swapped (s3/s4)
extern s32 func_8070DED4(s32, s32, u16);
extern u8 D_807550C8;

typedef struct R112cDrawCommand {
    s32 unk0;
    u16 unk4;
} R112cDrawCommand;

typedef struct R112cDrawList {
    u8 count;
    u8 pad1[3];
    void *commands;
} R112cDrawList;

typedef struct R112cDrawListContainer {
    u8 pad0[8];
    R112cDrawList *list;
} R112cDrawListContainer;

typedef struct R112cDrawContext {
    u8 pad0[0xC];
    s32 unkC;
} R112cDrawContext;

void func_8070E2AC(s32 arg0, void *arg1, void *arg2) {
    s32 var_s0;
    s32 var_s1;
    R112cDrawList *temp_s2;
    R112cDrawCommand *temp_v0;

    temp_s2 = (R112cDrawList *) ((u8 *) ((R112cDrawListContainer *) arg1)->list + (D_807550C8 * 8));
    var_s0 = 0;
    var_s1 = 0;
    if (temp_s2->count > 0) {
        do {
            temp_v0 = (R112cDrawCommand *) ((u8 *) temp_s2->commands + var_s1);
            func_8070DED4(arg0, temp_v0->unk0 + ((R112cDrawContext *) arg2)->unkC, temp_v0->unk4);
            var_s0 += 1;
            var_s1 += 8;
        } while (var_s0 < temp_s2->count);
    }
}
