// func_80032024 (src/menu/3E10.c): stage 3-4: frame 0x68 vs target 0x78 (target has 8 extra register-only local slots: nodes at sp5C..sp70, pos sp74, obj sp34, screen xy sp50/54); m2c-literal locals (c10c) worse; 58 diff lines of ~172
typedef struct Menu10_Sub174 {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    char padC[0x23C - 0xC];
    u16 unk23C;
} Menu10_Sub174;

typedef struct Menu10_Actor {
    char pad0[0x60];
    s32 unk60;
    char pad64[0x7C - 0x64];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
    char pad88[0xE6 - 0x88];
    s16 unkE6;
    s16 unkE8;
    char padEA[0x155 - 0xEA];
    u8 unk155;
    char pad156[0x174 - 0x156];
    Menu10_Sub174 *unk174;
} Menu10_Actor;

#define Menu10_A ((Menu10_Actor *)D_807FBB40)

extern f32 D_80033678[];
extern s16 D_80754CE0;
extern u8 D_8071FE64;
typedef struct Menu10_Node {
    char pad0[0x34];
    f32 unk34;
    f32 unk38;
    f32 unk3C;
} Menu10_Node;

typedef struct Menu10_Link {
    char pad0[4];
    Menu10_Node *unk4;
} Menu10_Link;

extern f32 D_8003378C[];
void actorDespawn(void *);
s32 actorSpawn(s32, s32);
void actorGetNodePos(void *, s32, f32 *, f32 *, f32 *);
s32 camProjectToScreen(f32, f32, f32, f32 *, f32 *, s32, f32, s32);

void func_80032024(void) {
    Menu10_Sub174 *pos;
    f32 x[2];
    f32 y[2];
    f32 z[2];
    f32 s[2];
    Menu3A_Actor *obj;

    pos = Menu10_A->unk174;
    obj = D_807FBB4C;
    if (*(u8 *)((u8 *)obj + 0x155) < 6) {
        if (D_80033738 == 0x14) {
            actorDespawn(D_807FBB40);
            D_80033738 += 1;
            actorSpawn(0x14D, 0xD7);
            ((Menu10_Link *)D_807FBB44)->unk4->unk34 = 0.14f;
            ((Menu10_Link *)D_807FBB44)->unk4->unk38 = 0.14f;
            ((Menu10_Link *)D_807FBB44)->unk4->unk3C = 0.14f;
        } else if (D_80033738 == 0x15) {
            actorGetNodePos(obj, 2, &x[0], &y[0], &z[0]);
            actorGetNodePos(D_807FBB4C, 3, &x[1], &y[1], &z[1]);
            Menu10_A->unk7C = (x[1] + x[0]) * 0.5f;
            Menu10_A->unk80 = y[0];
            Menu10_A->unk84 = (z[1] + z[0]) * 0.5f;
            pos->unk0 = Menu10_A->unk7C;
            pos->unk4 = Menu10_A->unk80;
            pos->unk8 = Menu10_A->unk84;
            Menu10_A->unkE6 = 0;
            Menu10_A->unkE8 = 0x400;
            camProjectToScreen(Menu10_A->unk7C, Menu10_A->unk80, Menu10_A->unk84, &s[1], &s[0], 0, 1.0f, 0);
            s[0] = s[0] - 120.0f;
            if (s[0] < -35.0f) {
                if (s[0] > -75.0f) {
                    D_8003378C[0] = s[0];
                    D_8003378C[0x11] = s[0];
                }
            }
        }
    } else {
        Menu10_A->unk7C = pos->unk0;
        Menu10_A->unk80 = pos->unk4 - (D_80033F3C * 19.0f);
        Menu10_A->unk84 = pos->unk8 - (D_80033F3C * 50.0f);
    }
    actorUpdateModelMatrix(D_807FBB40, 0);
    if (D_80033698 != 0) {
        Menu10_A->unk60 &= ~4;
    } else {
        Menu10_A->unk60 |= 4;
    }
}
