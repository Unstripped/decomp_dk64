// func_8002A638 (src/menu/3E10.c): stage 4 (frame 0x190, s0-s7,f20-f30): fs const order, s16 ang copy pattern, D_80033F28 ptr reg, 0xFA000000 const in s4 w/ store order w1,w0 differ
extern s32 *D_80033F28;
extern s8 D_80744538;
extern s32 D_807FBB60;
int _sprintf(char *, const char *, ...);
Gfx *hudDrawScaledText(Gfx *, s16, s16, f32, char *);
s32 func_800317E8(void *, f32, f32, f32 *, f32 *, s32, s8, f32);
typedef struct Menu3A_Struct174 {
    f32 unk0;
    f32 unk4;
    char pad[0xB];
    s8 unk13;
    char pad2[2];
    s8 unk16;
    s8 unk17;
} Menu3A_Struct174;
s32 func_806FC530(s32, s16, s16, s16, void *, s32);
Gfx *func_8068C5A8(Gfx *, s32, s32, s32, s32, s32, s32, s32, f32, f32, s32, f32);
f32 func_80612790(s16);
f32 func_80612794(s16);

void func_8002A638(void *arg0, Gfx *arg1) {
    Menu3A_Struct174 *temp_s2 = *(Menu3A_Struct174 **)((u8 *)arg0 + 0x174);
    s32 idx;
    s32 i;
    s32 id;
    s16 ang;
    s32 pad0;
    f32 sp174;
    f32 sp170;
    char sp98[0xD8];
    s32 pad1;
    s32 pad2;

    D_807FBB60 &= ~0x10;
    arg1->words.w0 = 0xFA000000;
    arg1->words.w1 = -1;
    idx = func_800317E8(temp_s2, 160.0f, 20.0f, &sp174, &sp170, 2, 1, 0.7f);
    arg1 += 1;
    arg1 = (Gfx *)func_806FC530((s32)arg1, 1, (s16)(sp174 * 4.0f), (s16)(sp170 * 4.0f), (void *)D_80033F28[idx + 12], 0x81);
    if (idx == 0) {
        _sprintf(sp98, "%s %d", (char *)D_80033F28[14], D_80744538 + 1);
        func_800317E8(temp_s2, 160.0f, 207.0f, &sp174, &sp170, 2, 0, 0.7f);
        arg1 = hudDrawScaledText(arg1, (s16)(sp174 * 4.0f), (s16)(sp170 * 4.0f), 0.6f, sp98);
    }
    arg1->words.w0 = 0xFA000000;
    arg1->words.w1 = -1;
    arg1++;
    i = 0;
    do {
        ang = (i - (temp_s2->unk17 << 11)) - (s32)((f64)temp_s2->unk4 * 2048.0);
        sp174 = 160.0 - (f64)func_80612794(ang) * 50.0;
        sp170 = 120.0 - (f64)func_80612790(ang) * 50.0;
        func_800317E8(temp_s2, sp174, sp170, &sp174, &sp170, 2, 0, 1.5f);
        sp174 = (f32)((f64)sp174 + 12.0) * 4.0f;
        sp170 = (f32)((f64)sp170 + 28.0) * 4.0f;
        if (i == 0) {
            id = D_80744538 + 0xB2;
        } else {
            id = 0xB1;
        }
        i += 0x800;
        arg1 = func_8068C5A8(
            func_8068C5A8(arg1, (u16)id, 0, 2, 0x20, 0x40, (s32)((f64)sp174 - 96.0), (s32)sp170, 3.0f, -3.0f, 0, 0.0f),
            (u16)(id + 4), 0, 2, 0x20, 0x40, (s32)sp174, (s32)sp170, 3.0f, -3.0f, 0, 0.0f);
    } while (i != 0x1000);
}
