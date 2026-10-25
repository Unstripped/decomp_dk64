// func_8070AF24 (src/global/10E1D0.c): compilable render-buffer reconstruction; register allocation and store scheduling remain
typedef struct R1F10E1D0bRenderBuffer {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    s32 unk10;
    s32 unk14;
    s32 unk18;
    s32 unk1C;
    s32 unk20;
    s32 unk24;
    s32 unk28;
} R1F10E1D0bRenderBuffer;

extern s32 D_80755068;
extern s32 D_8075506C;
extern s32 D_807FD9A4;
extern void *D_807FD9A8;
extern s32 D_807FD9AC;
extern s32 D_807FD9B0;
extern s32 D_807FD9B8;
extern u8 D_80744470;

s32 func_80610FE8(s32);
s32 func_8066B0F8();
void func_807095E4();
void func_80709890();
void func_80709ACC();
void func_8070A848();

void func_8070AF24(void) {
    s32 temp_v0;

    switch (D_807444F8) {
    case 1:
        D_80755068 = 0;
        D_8075506C = 0;
        break;
    case 2:
        D_80755068 = 0x78;
        break;
    }
    D_807FD9B8 = func_8066B0F8(0x13, 1, 1, 1);
    temp_v0 = func_80610FE8(D_80744490 * D_80744494 * 2);
    D_807FD9B0 = temp_v0;
    func_8070A848(temp_v0, *((s32 *)(&D_80744470 + (D_807444FC * 4))));
    func_80709890(D_807FD9B8, &D_807FD9A8, &D_807FD9AC, 0);
    func_80709ACC(D_807FD9A8);
    D_807FD9A4 = ((R1F10E1D0bRenderBuffer *)D_807FD9A8)->unk8;
    ((R1F10E1D0bRenderBuffer *)D_807FD9A8)->unk8 = func_80610FE8(((R1F10E1D0bRenderBuffer *)D_807FD9A8)->unk0 * 0xC);
    func_807095E4(((R1F10E1D0bRenderBuffer *)D_807FD9A8)->unk24, ((R1F10E1D0bRenderBuffer *)D_807FD9A8)->unk28, &D_807FD9A8);
}
