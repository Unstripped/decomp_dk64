// func_80697CEC (src/global/9BF30.c): stage 6: 267 vs 269 instrs; only 3 scheduling diffs + trailing nop, pervasive regalloc differs; frame now matches 0x78
typedef struct M9B_Config124 {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
} M9B_Config124;

typedef struct M9B_State2 {
    s32 unk0;
    u8 pad4[0xE];
    u8 unk12;
    u8 unk13;
} M9B_State2;

typedef struct M9B_ProjectileActor {
    u8 pad0[0x60];
    u32 unk60;
    u8 pad64[6];
    u16 unk6A;
    u8 pad6C[2];
    s16 unk6E;
    u8 pad70[0xC];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
    u8 pad88[0x30];
    f32 unkB8;
    u8 padBC[4];
    f32 unkC0;
    u8 padC4[0x2A];
    s16 unkEE;
    u8 padF0[0xC];
    u8 unkFC;
    u8 padFD[0x27];
    M9B_Config124 *unk124;
    u8 pad128[0x1C];
    u8 unk144;
    u8 pad145[0x10];
    u8 unk155;
    u8 pad156[0x1E];
    M9B_State2 *unk174;
} M9B_ProjectileActor;

extern void *D_807502C0[];
extern u8 D_8071FBA0;
extern u32 D_8076A068;
extern u8 D_807FBB85;
void func_807149FC(s32);
void func_80714998(s32);
void func_807149B8(s32);
void func_807149A8(s32);
void func_807149C8(s32, s32, s32, s32);
void func_8071498C(void (*)(void));
void func_80714950();
s32 func_80611A44(void);
void func_8066EB40(Actor *, f32);
void actorAppendModelNode(Actor *, f32, f32, f32, f32, s32);
void actorAppendModelSubNode(Actor *, f32, f32, f32, s32);
void func_8067ACB4(Actor *);
void actorApplyVelocity(Actor *);
void func_80665564(Actor *, f32);
void func_8065D254(Actor *, s32, s32, s32, s32, s32, s32, s32, s32, s32, f32);
void sfxPlayFromActorWithAltitudeCheck(void *, s32, s32, s32, s32);
void func_80714C08(void *, f32, Actor *, s32, s32);
void func_80714CC0(void *, f32, f32, f32, f32);
void func_8071F758(void);
void func_8071ABDC(void);

#define G_ACTOR ((M9B_ProjectileActor *)D_807FBB40)

void func_80697CEC(void) {
    M9B_State2 *sub;
    void *sp68[4];
    s16 var_s1;

    sub = ((M9B_ProjectileActor *)D_807FBB40)->unk174;
    if (!(G_ACTOR->unk60 & 0x10)) {
        sp68[1] = D_807502C0[0];
        sp68[2] = D_807502C0[1];
        sp68[3] = D_807502C0[2];
        G_ACTOR->unk6A &= (G_ACTOR->unk6E = -2);
        G_ACTOR->unkEE = (s16)((G_ACTOR->unk124->unk0 / 6.2831855f) * 4095.0f);
        G_ACTOR->unkB8 = G_ACTOR->unk124->unk4;
        G_ACTOR->unkC0 = G_ACTOR->unk124->unk8;
        G_ACTOR->unk144 = 0x3C;
        func_8066EB40(D_807FBB40, 40.0f);
        actorAppendModelNode(D_807FBB40, 0.0f, 0.0f, 0.0f, 30.0f, -1);
        actorAppendModelSubNode(D_807FBB40, 0.0f, 0.0f, 0.0f, -1);
        sub->unk13 = (u8)(u32)G_ACTOR->unk124->unk10;
        func_807149FC(-1);
        func_80714998(2);
        func_807149B8(1);
        func_807149A8(0x7D0);
        if (sub->unk13 == 1) {
            func_807149C8(0, 0xFF, 0, 0xC8);
        } else {
            func_807149C8(0xFF, 0xFF, 0xFF, 0xFF);
        }
        if (sub->unk13 == 3) {
            func_8071498C(func_8071F758);
        }
        func_80714C08(sp68[sub->unk13], G_ACTOR->unk124->unkC, D_807FBB40, 1, 2);
        sub->unk12 = 0;
        sub->unk0 = D_8076A068;
        G_ACTOR->unk60 |= 0x80000;
        G_ACTOR->unk155 = sub->unk13;
    }
    func_8067ACB4(D_807FBB40);
    actorApplyVelocity(D_807FBB40);
    func_80665564(D_807FBB40, 4.0f);
    func_8065D254(D_807FBB40, 0x3C8, 0x40, 0x40, 0x14, 0x14, 1, 0x96, 0x78, 0, 1.0f);
    if ((G_ACTOR->unk6A & 1) || (G_ACTOR->unkFC != 0) || (D_807FBB85 != 0)) {
        if (sub->unk13 == 3) {
            sfxPlayFromActorWithAltitudeCheck(D_807FBB40, 0x16, 0xFF, 0x7F, 0x14);
        }
        var_s1 = 0;
        if (D_807FBB85 == 0) {
            do {
                func_807149B8(1);
                func_80714950(var_s1 + 0xB000000);
                func_8071498C(func_8071ABDC);
                func_80714CC0(&D_8071FBA0, (f32)(((f64)((s32)(func_80611A44() >> 15) % 10) * 0.05) + 0.2),
                    G_ACTOR->unk7C, G_ACTOR->unk80, G_ACTOR->unk84);
                var_s1 += 2;
            } while (var_s1 < 0xC);
        }
        actorDespawn(D_807FBB40);
    }
}
