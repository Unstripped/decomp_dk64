// func_800297B8 (src/menu/3E10.c): stage 4 (frame 0x80, s0-s6+f20 match; parked NON_MATCHING in copy): tail div/mod via x-(x/60)*60 matches; loop1 ptr/index form and loop2 s0/s1 + D_80033804 address hoist differ
extern u8 D_80720CF0;
extern u8 D_80720D14;
extern u8 D_8072052C;
extern u8 D_807211D0;
extern void *D_80750518[];
extern s16 D_807505B2;
extern u32 D_80750AB0;
extern u8 D_807FC950[][0x5E];
extern s8 D_80033804;
extern s8 D_80033805;
extern s8 D_80033809;
extern s32 D_8003380C;
extern s32 D_80033810;
extern u32 D_80033814;
extern s8 D_80033F48;
extern f32 D_80033F4C;
extern s8 D_80033F51;
extern u32 D_80671880;
typedef struct Menu3A_Struct174 {
    f32 unk0;
    f32 unk4;
    char pad[0xB];
    s8 unk13;
    char pad2[2];
    s8 unk16;
    s8 unk17;
} Menu3A_Struct174;
s32 func_800297A8(s32 arg0);
void func_80030894(void *, void *, s32, s32, f32, s32, s32);
void func_8060DC3C(s32, s32);
s32 flagGet(s32, s32);
s32 menuCalculateGamePercentage(void);
int osPiReadIo(u32, u32 *);

void func_800297B8(void *arg0, s32 arg1) {
    Menu3A_Struct174 *temp_s6 = *(Menu3A_Struct174 **)((u8 *)arg0 + 0x174);
    u8 *row = D_807FC950[0];
    s8 *p;
    s16 *q;
    s8 *p2;
    void *a1;
    u32 sp64;
    s32 i;
    s32 k;
    s32 j;

    func_80030894(temp_s6, &D_80720CF0, 0x122, 0xD2, 0.75f, 2, 0);
    func_80030894(temp_s6, &D_80720D14, 0x23, 0xD2, 0.75f, 2, 0);
    func_80030894(temp_s6, &D_8072052C, 0x76, 0x91, 0.6f, 2, 9);
    D_80033F4C = 1600.0f;
    func_8060DC3C((u8)D_80033F48, 0);
    D_80033804 = 1;
    for (i = 0; i < 4; i++) {
        (&D_80033805)[i] = flagGet((&D_807505B2)[i - 1], 0);
    }
    p2 = &D_80033804;
    for (i = 0; i != 5; i++) {
        if (*p2 != 0) {
            a1 = D_80750518[i];
        } else {
            a1 = &D_807211D0;
        }
        func_80030894(temp_s6, a1, i, i, 0.8f, 2, 0xF);
        p2++;
    }
    osPiReadIo(func_800297A8(0xAFFE1464), &sp64);
    if (sp64 != func_800297A8(0x0107183B)) {
        D_80671880 = 0x03E00008;
    }
    D_8003380C = 0;
    for (k = 0; k != 5; k++) {
        for (j = 0; j != 8; j++) {
            D_8003380C += *(u16 *)(row + 0x42 + j * 2);
        }
        row += 0x5E;
    }
    D_80033814 = D_80750AB0 / 60;
    D_80033810 = (s32)D_80033814 / 60;
    D_80033814 = D_80033814 - D_80033810 * 60;
    D_80033F51 = menuCalculateGamePercentage();
}
