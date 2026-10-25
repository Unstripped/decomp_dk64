// func_806ECDD4 (src/global/EFDC0.c): stage 4: behavior reconstructed; only branch-likely scheduling differs (target beqz/nop/redundant branch versus current beqzl delay-slot conversion)
s32 func_806EB400(Actor *);
void func_806EEAF8(s16);
extern s32 D_807FBB68;

void func_806ECDD4(void) {
    s32 value;

    if (func_806EB400(D_807FBB48) != 0) {
        value = 1;
        if (D_807FBB68 & 2) {
            value = 0;
        }
        func_806EEAF8((s16)value);
    }
}
