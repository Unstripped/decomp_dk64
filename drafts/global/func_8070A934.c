// func_8070A934 (src/global/10E1D0.c): Near semantic reconstruction: swaps display buffers, advances/deallocates transition state, writes display lists. Compiles with a matching 0x38 frame; global pointer/register allocation remains unmatched.
typedef struct R2F10E1D0c_BufferSet {
    s32 unk0;
    s32 unk4;
    void *unk8;
    void *unkC;
    void *unk10;
    void *unk14;
} R2F10E1D0c_BufferSet;

extern u8 D_807444EC;
extern u8 D_807444F4;
extern Mtx D_80767CE8;
extern u8 *D_8076A048;
extern Gfx *D_8076A050[];
extern s32 D_8076A064;
extern s32 D_8076A088;
extern s32 D_8076A08C;
extern u8 D_8076A0A4;
extern u8 D_8076A0B2;
extern u32 D_807FBB64;
extern f32 D_807FD888;
extern R2F10E1D0c_BufferSet *D_807FD9A8;
extern s32 D_807FD9B0;
extern s32 D_807FD9B4;
extern s32 D_807FD9B8;
extern u8 D_807FD9BC;
extern u8 D_807FD9BD;

void func_805FE71C(Gfx *, u8, s32 *, u8);
void func_805FE7B4(Gfx *, s32, s32 *, u8);
void func_805FF378(s32, s32);
void func_80610044(void *, s32, s32, u8, s32, s32);
void func_8061CBCC(void);
void func_8070AC74(void *, s32 *, u8 *);
void func_8070AF24(s32 *, u8 *);
s32 func_8070B7EC(s32 *, s32, s32);
void heapFreeDeferred(void *);
void assetFreeBuffer(s32, s32, s32);

void func_8070A934(s32 arg0, s32 arg1) {
    s32 sp34;
    Gfx *sp30;
    u8 temp_t1;
    u8 temp_t5;

    func_80610044(D_8076A050[D_807444FC], D_8076A088, 3, 1, 0x4D2, 1);
    temp_t1 = D_807444FC ^ 1;
    D_807444FC = temp_t1;
    D_8076A064 += 1;
    D_8076A048 = ((temp_t1 & 0xFF) * 0x11B0) + (u8 *)&D_80767CE8;
    sp30 = (Gfx *)(D_8076A048 + 0xDB0);
    switch (D_807FD9BC) {
    case 1:
        break;
    case 0:
        D_807FD9BC = 1;
        func_8070AF24(&D_8076A064, &D_807FD9BC);
        break;
    }
    if ((D_8076A0B1 & 1) && (D_807FD888 == 31.0f)) {
        sp34 = D_8076A050[D_807444FC];
        if (D_8076A0B2 == 1) {
            D_807444EC = D_807444F4;
        }
    } else {
        func_8070AC74(D_8076A048, &sp34, &D_8076A0B1);
        if (func_8070B7EC(&sp34, D_807FD9B8, D_807FD9B0) != 0) {
            switch (D_807444F8) {
            case 1:
                osViBlack(1);
                func_805FF378(arg0, arg1);
                D_807FD888 = 31.0f;
                D_807444F8 = 2;
                break;
            case 2:
                heapFreeDeferred((void *)D_807FD9B0);
                heapFreeDeferred(D_807FD9A8->unk8);
                heapFreeDeferred((void *)D_807FD9B4);
                heapFreeDeferred(D_807FD9A8->unk10);
                heapFreeDeferred(D_807FD9A8->unk14);
                assetFreeBuffer(D_807FD9B8, 0x24B, 0x4A);
                D_807444EC = D_807444F4;
                if ((D_807444F4 == 1) && (D_807FBB64 & 1)) {
                    func_8061CBCC();
                }
                D_807444F8 = 3;
                D_807FD888 = 0.0f;
                break;
            }
        }
    }
    if (D_807FD9BD != 0) {
        temp_t5 = D_807FD9BD - 1;
        D_807FD9BD = temp_t5;
        if (!(temp_t5 & 0xFF)) {
            D_8076A0B1 |= 2;
        }
    }
    if ((D_8076A0A4 != 0) && (D_807444EC != 6)) {
        func_805FE71C(sp34, D_807444FC, &D_8076A088, 0);
        func_805FE7B4(sp30, (s32)D_8076A048, &D_8076A08C, 1);
        return;
    }
    func_805FE71C(sp34, D_807444FC, &D_8076A088, 1);
}
