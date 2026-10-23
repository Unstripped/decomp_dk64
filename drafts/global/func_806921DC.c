// func_806921DC (src/global/936B0.c): actor projectile/attack particle setup and despawn checks
void actorDespawn(Actor *);
s32 func_80611A44(void);
void func_806651FC(Actor *);
void func_80665564(Actor *, f32);
void func_8066E854(Actor *, f32, f32, f32, s32);
void func_8066E8E4(Actor *, f32, f32, f32, f32, s32);
void func_8066EB40(Actor *, f32, Actor *);
void func_8067ACB4(Actor *);
void func_80714950(s32);
void func_8071498C(void *);
void func_80714998(s32);
void func_807149A8(s32);
void func_807149B8(s32);
void func_807149C8(s32, s32, s32, s32);
void func_807149FC(s32);
void func_80714C08(void *, f32, Actor *, s32, s32);
extern u8 D_80720120;
extern u8 D_80720BE8;
extern u32 D_8076A068;
extern Actor *D_807FBB40;
extern u8 D_807FBB85;
extern void func_8071C914(void);

typedef struct {
    u32 unk0;
    char pad4[0xE];
    u8 unk12;
    s8 unk13;
} M93B_ActorState2C;

typedef struct {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    s32 unk10;
} M93B_ConfigSub124;

void func_806921DC(u8 arg0) {
    M93B_ActorState2C *sp2C;
    Actor *temp_a2;
    M93B_ConfigSub124 *sub124;

    temp_a2 = D_807FBB40;
    sp2C = (M93B_ActorState2C *)temp_a2->unk174;
    if (!(temp_a2->unk60 & 0x10)) {
        sub124 = (M93B_ConfigSub124 *)D_807FBB40->unk124;
        temp_a2->unk6E = -2;
        D_807FBB40->unk6A = (u16)(D_807FBB40->unk6A & ~1);
        D_807FBB40->unkEE = (s16)(s32)((sub124->unk0 / 6.2831855f) * 4095.0f);
        D_807FBB40->unkB8 = sub124->unk4;
        D_807FBB40->unkC0 = sub124->unk8;
        D_807FBB40->unk144 = 0x3C;
        func_8066EB40(D_807FBB40, 40.0f, D_807FBB40);
        func_8066E8E4(D_807FBB40, 0.0f, 0.0f, 0.0f, 30.0f, -1);
        func_8066E854(D_807FBB40, 0.0f, 0.0f, 0.0f, -1);
        func_807149FC(1);
        func_80714998(2);
        func_807149B8(1);
        func_8071498C(func_8071C914);
        func_80714950((s32)(func_80611A44() >> 15) % 360);
        func_807149A8(2000);
        switch (arg0) {
        case 0:
            func_807149C8(0xFF, 0xD7, 0x58, 0xFF);
            func_80714C08(&D_80720120, sub124->unkC, D_807FBB40, 1, 2);
            break;
        case 1:
            func_807149C8(0xC8, 0xC8, 0xFA, 0x9B);
            func_80714C08(&D_80720BE8, sub124->unkC, D_807FBB40, 1, 2);
            break;
        }
        sp2C->unk13 = (s8)sub124->unk10;
        sp2C->unk12 = 0;
        sp2C->unk0 = D_8076A068;
        D_807FBB40->unk60 |= 0x80000;
    }
    func_8067ACB4(temp_a2);
    func_806651FC(D_807FBB40);
    func_80665564(D_807FBB40, 4.0f);
    if ((D_807FBB40->unk6A & 1) || (D_807FBB40->unkFC != 0) || (D_807FBB85 != 0) || ((u32)(sp2C->unk0 + 24) < D_8076A068)) {
        actorDespawn(D_807FBB40);
    }
}
