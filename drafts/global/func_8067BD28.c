// func_8067BD28 (src/global/80150.c): from .scratch/R2F/func_8067BD28_best.c
extern u8 D_807FBBA8;
void func_80689114(s32, f32, f32, f32, s32, f32, void *);

void func_8067BD28(void) {
    s32 var_v1 = 0;

    if (D_807FBBA8 != 0 && (*(s32 *)((char *)((Actor *)D_807FBB4C)->unk174 + 0x1F0) & 0x200000)) {
        var_v1 = 1;
    }
    if (!(D_807FBB40->unk60 & 0x10) || var_v1) {
        func_80689114(0x55, D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84, 0, 1.0f, D_807FBB40);
    }
}
