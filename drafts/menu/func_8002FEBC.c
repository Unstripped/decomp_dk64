// func_8002FEBC (src/menu/3E10.c): text-identical, reloc only: expected uses D_8076A0DD for loop end, C emits D_8076A0D1+12 (jtbl/double relocs normal). Includes trailing static stub func_8003026C (jr ra;nop at end of the asm).
typedef struct MenuM9_Vec {
    char pad[0x34];
    f32 unk34;
    f32 unk38;
    f32 unk3C;
} MenuM9_Vec;

typedef struct MenuM9_Actor {
    char pad0[4];
    MenuM9_Vec *unk4;
    char pad8[0x60 - 8];
    u32 unk60;
    char pad64[0x7C - 0x64];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
    char pad88[0xE6 - 0x88];
    s16 unkE6;
    char padE8[0x154 - 0xE8];
    u8 unk154;
    u8 unk155;
    char pad156[0x174 - 0x156];
    void *unk174;
} MenuM9_Actor;

typedef struct MenuM9_Sub174 {
    f32 unk0;
    f32 unk4;
    char pad8[4];
    s16 unkC;
    s16 unkE;
    s16 unk10;
    s8 unk12;
    char pad13[3];
    s8 unk16;
    s8 unk17;
} MenuM9_Sub174;

struct Menu3B_Struct_BB40;
extern struct Menu3B_Struct_BB40 *D_807FBB40;
extern MenuM9_Actor *D_807FBB44;
extern u8 D_80744514;
extern u8 D_8076A0D0[];
extern u8 D_8076A0D1[];
extern u8 D_8076A0DD[];
extern s8 D_80033738;
extern s8 D_80033F50;
extern s8 D_80033F60;
extern s8 D_800339A8;
extern f32 D_8003369C;
extern f32 D_80033F3C;
extern void *D_80033F34;
extern s8 D_80033F30;
s32 actorSpawn(s32, s32);
void actorScriptStart(void *, s32);
void func_8061B650(s32);
void func_8060CB9C(void);
void menuLoadTextTable(void);
void menuInsertHighScore(void);
void renderCallbacksRegister(void *, void *, s32);
void *func_80610FE8(s32);
void menuInitGfxState(Gfx *, s32);

#define MenuM9_A ((MenuM9_Actor *)D_807FBB4C)

void func_8002FEBC(void) {
    MenuM9_Sub174 *sub = ((MenuM9_Actor *)D_807FBB40)->unk174;
    u8 *sp20 = MenuM9_A->unk174;
    s32 i;

    if (!(((MenuM9_Actor *)D_807FBB40)->unk60 & 0x10)) {
        D_807FBB60 |= 0x10;
        menuLoadTextTable();
        menuLoadHighScores();
        if (D_80744514 == 0) {
            for (D_8076A0D0[0] = 0, i = 0; i < 12; i += 4) {
                D_8076A0D1[i] = 0;
                D_8076A0D1[i + 1] = 0;
                D_8076A0D1[i + 2] = 0;
                D_8076A0D1[i + 3] = 0;
            }
        } else {
            MenuM9_A->unk7C = 700.0f;
            MenuM9_A->unk80 = 0.0f;
            MenuM9_A->unk84 = 70.0f;
        }
        D_80033F50 = 0;
        D_80033738 = 0;
        D_80033F60 = -1;
        D_8003369C = 0.0f;
        actorSpawn(0x14D, 0xD7);
        D_807FBB44->unk7C = MenuM9_A->unk7C;
        D_807FBB44->unk80 = MenuM9_A->unk80;
        D_807FBB44->unk84 = MenuM9_A->unk84;
        D_807FBB44->unkE6 = MenuM9_A->unkE6;
        if (D_80744514 != 0) {
            D_80033738 = 0x15;
            MenuM9_A->unk154 = 0x85;
            MenuM9_A->unk155 = 0;
            actorScriptStart(MenuM9_A, 0x347);
            MenuM9_A->unk155 = 6;
            func_8061B650(gCamActor);
            D_80033F3C = 1.0f;
            *(s16 *)(sp20 + 0x23C) = 0x50;
        }
        switch (D_80744514) {
        case 1:
            sub->unk12 = 1;
            break;
        case 2:
            sub->unk12 = 0xB;
            break;
        case 3:
        case 4:
        case 5:
            sub->unk12 = 0xA;
            break;
        case 6:
        case 7:
            sub->unk12 = 0xC;
            D_800339A8 = D_80744514 - 6;
            menuInsertHighScore();
            break;
        default:
            actorScriptStart(D_807FBB44, 0x349);
            MenuM9_A->unk154 = 0x86;
            MenuM9_A->unk155 = 0;
            sub->unk12 = 0;
            break;
        }
        MenuM9_A->unk4->unk34 = MenuM9_A->unk4->unk34 * 0.8;
        MenuM9_A->unk4->unk38 = MenuM9_A->unk4->unk38 * 0.8;
        MenuM9_A->unk4->unk3C = MenuM9_A->unk4->unk3C * 0.8;
        sub->unk17 = 0;
        sub->unkC = 0;
        sub->unkE = 0;
        sub->unk16 = 1;
        sub->unk10 = 0;
        sub->unk0 = 1.0f;
        sub->unk4 = 0.0f;
        D_80033F34 = func_80610FE8(0x80);
        D_80033F30 = 0;
        func_80030340(D_807FBB40, 0, 0, 0);
        D_80744514 = 0;
        controllerSetActiveMask(0xFF);
        func_8060CB9C();
    }
    func_80030340(D_807FBB40, 2, 0, 0);
    renderCallbacksRegister(menuInitGfxState, D_807FBB40, 3);
}

static void func_8003026C(void) {
}
