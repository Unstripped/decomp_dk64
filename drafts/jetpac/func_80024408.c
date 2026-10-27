// func_80024408 (src/jetpac/0.c): Stage 6: text identical except the order of the two hoisted loop-prologue addiu (s1=&D_8002EC4C before s3="%d!" expected; C gives s3 then s1). Needs unused 3rd local (s32 pad/JetpacPlayer *p) for spill slots 0x4C/0x50, buf[0x50]. Tried lives temp, ptr induction, continue/do-while, permuter 150s: no change.
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
