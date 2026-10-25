// func_80712BD4 (src/global/117190.c): m2c stage-1 recovery: init guard, scale matrix, table-driven duration and dispatch recovered; needs compilation and stage 2 block/order work.
typedef struct { u8 pad[4]; s32 unk4; } R117c5Player;
extern u8 D_807467CC, D_8076A0AB, D_8075530C, D_80755310, D_80755328, D_8075532C;
extern s16 D_80755308;
extern s32 D_807552EC;
extern u16 D_8075531C;
extern u16 D_8075E5C0[], D_8075E5C2[];
extern Mtx D_807FDAC0;
s32 func_8073110C(s32, s32); s32 func_805FF030(u8, s32); s16 func_8060B49C(s32, u8); s32 func_80712628(void);
void func_8060E1A8(void); void func_80712574(void); void func_8060DEC8(void); void actorSpawn(s32, s32);
void func_80712BD4(void) {
    u8 blocked = func_8073110C(0x302, 0); s16 duration; u16 limit; u8 next;
    D_80755334 = 0; D_80755330 = 0;
    if (D_807467CC == 0) func_8060E1A8();
    if ((func_805FF030(D_8076A0AB, 1) == 8) && !(D_807FBB68 & 2) && (D_8076A0A8 != 0xD6) && (func_80712628() == 0) && (blocked == 0)) func_80712574();
    guScale(&D_807FDAC0, 0.5f, 0.5f, 1.0f);
    switch (D_80755314) {
    case 0: D_8075531C=0x708; D_80755308=0; D_80755338=1; D_8075533C=0; break;
    case 1: D_8075531C=0x708; D_80755308=0x1000; D_80755338=1; D_8075533C=0; break;
    case 2: D_8075531C=0x1644; D_80755308=0x1000; D_80755338=1; D_8075533C=0; break;
    case 3: D_8075532C++; duration=func_8060B49C(((R117c5Player *)D_807FC924)->unk4, ((u8 *)D_8075E5C0)[D_80755328 * 4]); limit=D_8075E5C2[D_80755328 * 2]; D_8075531C=(duration < (s16)limit) ? duration : (s16)limit; next=D_80755328+1; D_80755328=next%5; D_80755308=0x1000; break;
    case 7: D_8075531C=0x410; D_80755314=9; D_80755318=9;
    case 9: D_80755308=0x9000; break;
    case 5: D_807552EC=0;
    case 6: case 12: case 13: D_8075531C=1; D_80755308=-1; D_8075530C=-1; D_80755310=-1; break;
    case 10: D_8075531C=1; D_8075530C=0; D_80755310=0; D_80755308=0; actorSpawn(0x152,0); break;
    case 14: actorSpawn(0x152,0);
    case 11: D_8075531C=0x1E; break;
    } func_8060DEC8();
}
