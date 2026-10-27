// func_80024408 (src/jetpac/0.c): Stage 6: text identical except order of the two hoisted loop-prologue addiu (target lui s1,lui s3,addiu s1,addiu s3; C lui s1,lui s3,addiu s3,addiu s1). Verified with raw IDO asm: as1's scheduler gives only the mirrored order (first la -> addiu last) for ALL 1260 orderings of {move,lui/addiu(EC4C),lui/addiu(%d!),addu,li} in the preheader, with or without a following lw: the target stream needs another shape. Tried (fdiff-measured): fmt local before/in loop, pointer local, IV pointer, lives local, 0<x, != 2 bound, one-line if, operand swaps, early dead use of D_8002EC4C: no change.
extern JetpacPlayer D_8002EC4C[];
extern s32 D_8002BA6C;
extern s32 D_8002EF74;
extern s32 D_8002EC50;
extern s32 D_8002EDE4;
s32 func_80026FE0(void);
void func_8002AE00(s32);
void func_8002AE94(s32, s32, s32, s32);
void func_8002AEFC(s32, char *, s32, s32, s32);
s32 _sprintf(char *, char *, ...);

void func_80024408(s32 arg0) {
    char buf[0x50];
    s32 mask;
    s32 i;
    s32 pad;

    mask = func_80026FE0() & D_8002BA6C;
    func_8002AE00(arg0);
    func_8002AE94(0xFF, 0xFF, 0xFF, 0xFF);
    func_8002AEFC(arg0, "1UP", 0x38, 0x18, mask != 0 && D_8002EF74 == 0);
    for (i = 0; i < 2; i++) {
        if (D_8002EC4C[i].lives > 0) {
            _sprintf(buf, "%d!", D_8002EC4C[i].lives);
            func_8002AEFC(arg0, buf, i * 0x70 + 0x60, 0x18, 0);
        }
    }
    func_8002AEFC(arg0, "2UP", 0xF8, 0x18, mask != 0 && D_8002EF74 == 1);
    func_8002AE94(0, 0xFF, 0xFF, 0xFF);
    func_8002AEFC(arg0, "HI", 0x98, 0x18, 0);
    func_8002AE94(0xFF, 0xFF, 0, 0xFF);
    _sprintf(buf, "%06d", D_8002EC50);
    func_8002AEFC(arg0, buf, 0x28, 0x20, 0);
    _sprintf(buf, "%06d", D_8002EC48);
    func_8002AEFC(arg0, buf, 0x88, 0x20, 0);
    _sprintf(buf, "%06d", D_8002EDE4);
    func_8002AEFC(arg0, buf, 0xE8, 0x20, 0);
}
