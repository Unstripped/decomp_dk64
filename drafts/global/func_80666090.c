// func_80666090 (src/global/6AD90.c): needs address caching in s0, s2, s3 for D_807F9514/18/1C
typedef struct {
    u8 pad0[4];
    u32 unk4;
    u8 pad8;
    u8 unk9;
    u8 padA[0xE];
    s16 unk18;
    s16 unk1A;
} R3P_Struct80666090;

typedef struct R1C_Struct_806688B8 {
    u32 unk0;
    u32 unk4;
    u32 unk8;
    u32 unkC;
    u32 unk10;
} R1C_Struct_806688B8;

void *func_80610FE8(s32);
s32 func_8066B0F8(s32, s32, s32, s32);
s32 func_8066B020(s32, s32);
void func_8066B424(void);
void func_8066B434(void *, s32, s32);
void gunzip(void *, void *, void *);
void heapFree(void *);

extern R1C_Struct_806688B8 *D_807F9514;
extern s32 D_807F9518;
extern u8 D_807F951C;
extern s32 D_8076A0A8;
extern u8 D_807F94B4;

void func_80666090(R3P_Struct80666090 *arg0) {
    void *sp58;
    void *sp54;
    void *sp50;
    void *sp34;
    u8 *var_s1;
    R1C_Struct_806688B8 **p514;
    u8 *p51C;
    s32 *p518;
    u8 *a3;
    u8 *a1;
    u8 *a2;
    s32 base;
    s32 i;

    p514 = &D_807F9514;
    *p514 = (R1C_Struct_806688B8 *)func_80610FE8(0x11A8);
    p518 = &D_807F9518;
    *p518 = (u32)(arg0->unk18 * arg0->unk1A);
    var_s1 = (u8 *)func_8066B0F8(3, D_8076A0A8, 1, 0);
    p51C = &D_807F951C;
    *p51C = 0;
    if (arg0->unk9 & 2) {
        sp58 = var_s1;
        var_s1 = func_80610FE8(arg0->unk4);
        sp34 = func_80610FE8(0x2400);
        sp54 = var_s1;
        sp50 = sp58;
        gunzip(&sp50, &sp54, sp34);
        heapFree(sp34);
        func_8066B424();
        func_8066B434(sp58, 0x9D, 0x3A);
        *p51C = 1;
    }
    base = func_8066B020(3, D_8076A0A8);
    a3 = var_s1 + 4;
    for (i = 0; i < *p518; i++) {
        (*p514)[i].unk8 = 0;
        a2 = a3 + 4;
        (*p514)[i].unkC = base + (a3 - var_s1) + 4;
        a1 = var_s1 + *(u32 *)a3;
        a3 = a1;
        if (*p51C) {
            (*p514)[i].unk0 = (u32)a2;
            (*p514)[i].unk4 = (u32)a1;
        } else {
            (*p514)[i].unk0 = 0;
            (*p514)[i].unk4 = 0;
        }
        (*p514)[i].unk10 = a1 - a2;
    }
    if (!*p51C) {
        func_8066B424();
        func_8066B434(var_s1, 0xC3, 0x3A);
    }
    D_807F94B4 = 0;
}
