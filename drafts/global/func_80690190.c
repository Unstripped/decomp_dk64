// func_80690190 (src/global/936B0.c): regalloc diff on global pointer and array indexing
typedef struct M93A_Struct4 {
    u8 pad0[4];
    f32 unk4;
} M93A_Struct4;

typedef struct M93A_Actor6E {
    u8 pad0[0x6E];
    s16 unk6E;
    s16 unk70;
    u8 pad72[0x80 - 0x72];
    f32 unk80;
    u8 pad84[0xAC - 0x84];
    f32 unkAC;
    u8 padB0[0xB8 - 0xB0];
    f32 unkB8;
} M93A_Actor6E;

extern s16 D_80770628[];
extern f32 D_80770B68[];
extern f32 D_80770BC0[];
u32 func_806119A0(void);

void func_80690190(M93A_Struct4 *arg0, s32 arg1) {
    M93A_Actor6E *actor = (M93A_Actor6E *)D_807FBB40;
    s16 idx1;
    s16 idx2;

    idx1 = D_80770628[actor->unk6E];
    if (actor->unk80 < actor->unkAC + 4.0f) {
        D_80770B68[idx1] = ((f64)actor->unkB8 / 300.0) + 1.0;
        D_80770BC0[idx1] = 1.0f;
    } else {
        D_80770B68[idx1] = (f64)arg0->unk4 + 1.2;
        D_80770BC0[idx1] = 5.0f;
    }

    idx2 = D_80770628[actor->unk70];
    if (actor->unk80 < actor->unkAC + 4.0f) {
        if (D_80770BC0[idx2] == 0.0f) {
            D_80770B68[idx2] = (((((f64)(u32)func_806119A0() / 4294967295.0) * 0.05) + 0.975) *
                                (0.2 + ((f64)actor->unkB8 / 300.0)));
            D_80770BC0[idx2] = 1.0f;
        }
    } else {
        D_80770B68[idx2] = ((f64)arg0->unk4 * 1.5) + 0.2;
        D_80770BC0[idx2] = 8.0f;
    }
}
