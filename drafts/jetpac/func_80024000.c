// func_80024000 (src/jetpac/0.c): from .scratch/Boss3A/func_80024000_best.c
#include "common.h"

typedef struct Boss3A_Struct_6Bytes {
    u8 bytes[6];
} Boss3A_Struct_6Bytes;

typedef struct Boss3A_Struct_80024000_BB40 {
    u8 pad0[0x7C];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
} Boss3A_Struct_80024000_BB40;

struct BossA_Struct_807FBB40;
extern struct BossA_Struct_807FBB40 *D_807FBB40;
extern Boss3A_Struct_6Bytes D_8003598C;
extern u8 D_8071E864;
extern u8 D_8071FFA0;

void func_8067E2E4(void *, u8, f32);
void func_80714950(s32);
void func_8071498C(void *);
void func_80714998(s32);
void func_807149B8(s32);
void func_807149C8(s32, s32, s32, s32);
void func_80714CC0(void *, f32, f32, f32, f32);

void func_80024000(void) {
    Boss3A_Struct_6Bytes sp48;
    s16 i;

    for (i = 0; i < 6; i++) {
        sp48 = D_8003598C;
        func_8067E2E4(D_807FBB40, sp48.bytes[i], 3.0f);
    }

    for (i = 0; i < 12; i++) {
        func_8071498C(&D_8071E864);
        func_80714950(i);
        func_807149B8(1);
        func_807149C8(0x8C, 0x8C, 0x8C, 0xFF);
        func_80714998(3);
        func_80714CC0(&D_8071FFA0, 2.5f, ((Boss3A_Struct_80024000_BB40 *)D_807FBB40)->unk7C, ((Boss3A_Struct_80024000_BB40 *)D_807FBB40)->unk80 + 40.0f, ((Boss3A_Struct_80024000_BB40 *)D_807FBB40)->unk84);
    }
}
