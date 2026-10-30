// func_80024408 (src/jetpac/0.c): Stage 6: only diff is the order of the two hoisted preheader addiu (target lui s1,lui s3,addiu s1,addiu s3; ours addiu s3 then s1). C1f re-verified with correct flags (cc -c -O2 -mips2 -G 0 -non_shared -Wab,-r4300_mul on cc -S -non_shared output; PIC flags give bogus results): as1 emits lui A,lui B,addiu B,addiu A for ALL 120 orders of the 5 preheader insns, for explicit lui/addiu pairs in any order, global vs local symbols, sym offsets, with/without .loc/.livereg/.noalias, an inserted label/nop, other uses of s1/s3 in the loop head, extra insns in the block. Only a lw/use of the loaded reg in the block (o5/o6) changes it to lui A,addiu A,lui B,addiu B (also not the target). Only other unmirrored case in corpus: global sfxUpdateLevelAmbient. No source form found; needs an IL where the second la is not a plain preheader la.
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
