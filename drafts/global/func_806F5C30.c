// func_806F5C30 (src/global/F9450.c): stage 4: exact blocks/frame absent; scalar globals plus dynamic post-third-comparison pointer got target first three branches but compiler folded remaining pointer access
typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
} F9BQueueEntry;

extern s32 D_80754248;
extern s32 D_8075424C;
extern s32 D_80754250;

s32 func_806F5C30(s32 arg0) {
    s32 temp_v0;
    F9BQueueEntry *temp_v1;

    if (arg0 == D_80754248) {
        return 1;
    }
    if (arg0 == D_8075424C) {
        return 1;
    }
    if (arg0 == D_80754250) {
        return 1;
    }
    temp_v0 = 3;
    temp_v1 = (F9BQueueEntry *) (&D_80754248 + temp_v0);
    if (arg0 == temp_v1->unk0) {
        return 1;
    }
    if (arg0 == temp_v1->unk4) {
        return 1;
    }
    if (arg0 == temp_v1->unk8) {
        return 1;
    }
    if (arg0 == temp_v1->unkC) {
        return 1;
    }
    return 0;
}
