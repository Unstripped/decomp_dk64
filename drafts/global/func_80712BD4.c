// func_80712BD4 (src/global/117190.c): stage 4: exact 0x304-byte frame/block layout; remaining register allocation and table-address scheduling (D_8075531C pointer and D_8075E5C2 label)
// func_80712BD4 stage 4: correct frame/block order; remaining differences are register allocation and table-address scheduling.
typedef struct R117iPlayerView {
    s32 unk0;
    s32 unk4;
} R117iPlayerView;

extern u8 D_807467CC;
extern u8 D_8076A0AB;
extern u8 D_8075532C;
extern s32 D_80755334;
extern s32 D_807552EC;
extern Mtx D_807FDAC0;
s32 func_8073110C(s32, s32);
s32 func_805FF030(u8, s32);
s16 func_8060B49C(s32, u8);
void func_8060E1A8(void);
void func_80712574(void);
void func_8060DEC8(void);
void actorSpawn(s32, s32);

void func_80712BD4(void) {
    u8 blocked;
    u8 index;
    s16 duration;
    u16 limit;
    u8 next;

    blocked = func_8073110C(0x302, 0);
    D_80755334 = 0;
    D_80755330 = 0;
    if (D_807467CC == 0) {
        func_8060E1A8();
    }
    if (func_805FF030(D_8076A0AB, 1) == 8) {
        if ((D_807FBB68 & 2) == 0) {
            if (D_8076A0A8 != 0xD6) {
                if (func_80712628() == 0) {
                    if (blocked == 0) {
                        func_80712574();
                    }
                }
            }
        }
    }
    guScale(&D_807FDAC0, 0.5f, 0.5f, 1.0f);
    switch (D_80755314) {
    case 0:
        D_8075531C = 0x708;
        D_80755308 = 0;
        D_80755338 = 1;
        D_8075533C = 0;
        break;
    case 1:
        D_8075531C = 0x708;
        D_80755308 = 0x1000;
        D_80755338 = 1;
        D_8075533C = 0;
        break;
    case 2:
        D_8075531C = 0x1644;
        D_80755308 = 0x1000;
        D_80755338 = 1;
        D_8075533C = 0;
        break;
    case 3:
        index = D_80755328;
        D_8075532C += 1;
        duration = func_8060B49C(((R117iPlayerView *)D_807FC924)->unk4, D_8075E5C0[index * 4]);
        D_8075531C = duration;
        limit = *(u16 *)&D_8075E5C0[(D_80755328 * 4) + 2];
        next = D_80755328 + 1;
        if ((u16)duration < limit) {
            D_8075531C = duration;
        } else {
            D_8075531C = limit;
        }
        D_80755328 = next;
        D_80755328 = (u8)(((u32)next) % 5U);
        D_80755308 = 0x1000;
        break;
    case 7:
        D_8075531C = 0x410;
        D_80755314 = 9;
        D_80755318 = 9;
    case 9:
        D_80755308 = 0x9000;
        break;
    case 5:
        D_807552EC = 0;
    case 6:
    case 12:
    case 13:
        D_8075531C = 1;
        D_80755308 = 0xFFFF;
        D_8075530C = 0xFF;
        D_80755310 = 0xFF;
        break;
    case 10:
        D_8075531C = 1;
        D_8075530C = 0;
        D_80755310 = 0;
        D_80755308 = 0;
        actorSpawn(0x152, 0);
        break;
    case 14:
        actorSpawn(0x152, 0);
    case 11:
        D_8075531C = 0x1E;
        break;
    }
    func_8060DEC8();
}
