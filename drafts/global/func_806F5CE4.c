// func_806F5CE4 (src/global/F9450.c): stage 3: correct blocks and comparison sequence; IDO folds the post-second-comparison local pointer into direct loads instead of target dynamic index
typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
} F9BQueueEntry;

extern s32 D_80754264;
extern s32 D_80754268;

s32 func_806F5CE4(s32 arg0) {
    F9BQueueEntry *temp_v1;

    if (arg0 == D_80754264) {
        return 1;
    }
    if (arg0 == D_80754268) {
        return 1;
    }
    temp_v1 = (F9BQueueEntry *) &(&D_80754264)[2];
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
