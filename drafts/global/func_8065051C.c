// func_8065051C (src/global/54150.c): M54B:  func_8065051C (src/global/54150.c) — closest diff: only the two address  * candidates' registers are swapped (expected end-pointer=v0, start=v1; this  * gives start=v0, end=v1). Everything else (12 insns, no frame) is identical.  
/* func_8065051C (src/global/54150.c) — closest diff: only the two address
 * candidates' registers are swapped (expected end-pointer=v0, start=v1; this
 * gives start=v0, end=v1). Everything else (12 insns, no frame) is identical. */
typedef struct M54B_ClearGroup {
    s32 unk0;
    u8 pad04[0xC];
    s32 unk10;
    u8 pad14[0xC];
    s32 unk20;
    u8 pad24[0xC];
    s32 unk30;
    u8 pad34[0xC];
} M54B_ClearGroup;

extern M54B_ClearGroup D_807F6960[];
extern u32 D_807F6BE0;

void func_8065051C(void) {
    M54B_ClearGroup *group = (M54B_ClearGroup *)D_807F6960;

    for (;;) {
        group->unk10 = 0;
        group->unk20 = 0;
        group->unk30 = 0;
        group->unk0 = 0;
        group++;
        if (group == (M54B_ClearGroup *)&D_807F6BE0) {
            break;
        }
    }
}
