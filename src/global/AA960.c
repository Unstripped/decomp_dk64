#include "common.h"
#include "actor.h"

#pragma GLOBAL_ASM("asm/global/nonmatchings/AA960/func_806A5C60.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/AA960/func_806A5DF0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/AA960/func_806A5EAC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/AA960/func_806A5F44.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/AA960/func_806A5FA4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/AA960/func_806A6004.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/AA960/func_806A6094.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/AA960/func_806A60BC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/AA960/func_806A60E4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/AA960/func_806A610C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/AA960/func_806A6134.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/AA960/func_806A615C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/AA960/func_806A61D0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/AA960/func_806A6230.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/AA960/func_806A62B4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/AA960/func_806A62D4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/AA960/func_806A6348.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/AA960/func_806A63A8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/AA960/func_806A6408.s")

extern Actor *D_807FBB40;
extern Actor *D_807FBB4C;
extern u8 D_807203B0;
extern u8 D_807203D4;
extern u8 D_807203F8;
extern u8 D_8072041C;
extern u8 D_80720440;
void func_806A664C(f32);
void func_806A5EAC(void *, void *, f32);

void func_806A6468(void) {
    void *temp_v1;
    void *anim;

    temp_v1 = D_807FBB40->unk174;
    func_806A664C(4.5f);
    if (!(D_807FBB40->unk60 & 0x10)) {
        switch (D_807FBB4C->unk58) {
        case 3:
            anim = &D_807203B0;
            break;
        case 2:
            anim = &D_8072041C;
            break;
        case 4:
            anim = &D_807203F8;
            break;
        case 6:
            anim = &D_807203D4;
            break;
        case 5:
            anim = &D_80720440;
            break;
        }
        func_806A5EAC(temp_v1, anim, 1.0f);
        if (D_807FBB40->unk154 == 0x63) {
            D_807FBB40->unk154 = 1;
            D_807FBB40->unk15F = 2;
        }
    }
}

extern u8 D_80720EBC;
extern u8 D_80720EE8;
extern u8 D_80720F14;
extern u8 D_80720F40;
extern u8 D_80720F6C;

void func_806A6574(void) {
    void *temp_v1;
    void *anim;

    temp_v1 = D_807FBB40->unk174;
    func_806A664C(4.5f);
    if (!(D_807FBB40->unk60 & 0x10)) {
        switch (D_807FBB4C->unk58) {
        case 3:
            anim = &D_80720EE8;
            break;
        case 2:
            anim = &D_80720F40;
            break;
        case 4:
            anim = &D_80720F14;
            break;
        case 6:
            anim = &D_80720EBC;
            break;
        case 5:
            anim = &D_80720F6C;
            break;
        }
        func_806A5EAC(temp_v1, anim, 1.0f);
    }
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/AA960/func_806A664C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/AA960/func_806A6DB4.s")


void func_806A6DB4(u8);

void func_806A734C(void) {
    func_806A6DB4(1);
}

typedef struct AA960ActorPhysics {
    u8 pad0[0xC0];
    f32 unkC0;
    f32 unkC4;
} AA960ActorPhysics;

typedef struct AA960ActorSub174 {
    u8 pad0[0x8];
    u16 unk8;
} AA960ActorSub174;

void func_806086CC(f32, f32, f32, s32, s32, s32, s32, s32, f32, s32);
void func_8065D254(Actor *, s32, s32, s32, s32, s32, s32, s32, s32, s32, f32);
void func_80686CF8(Actor *);
void sfxAllocateChannel(s32, f32);

void func_806A736C(void) {
    AA960ActorSub174 *temp_v1;

    temp_v1 = D_807FBB40->unk174;
    if (!(D_807FBB40->unk60 & 0x10)) {
        D_807FBB40->unk64 |= 4;
        D_807FBB40->unk60 |= 0x400;
        func_80686CF8(D_807FBB40);
    }
    if (temp_v1->unk8 == 1) {
        func_806086CC(D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84, 0x73, 0xFF, 0x7F, 1, 0, 0.0f, 0);
        sfxAllocateChannel(0x3B, 0.7f);
    } else if (temp_v1->unk8 == 0xA) {
        func_806086CC(D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84, 0x19C, 0xB4, 0x7F, 1, 0, 0.0f, 0);
    }
    func_806A6DB4(0);
    if (D_807FBB40->unk80 < D_807FBB40->unkAC) {
        D_807FBB40->unkB8 = 0.0f;
        D_807FBB40->unk80 = D_807FBB40->unkAC;
        ((AA960ActorPhysics *)D_807FBB40)->unkC0 = ((AA960ActorPhysics *)D_807FBB40)->unkC4;
    }
    func_8065D254(D_807FBB40, 0x3C8, 0x40, 0x40, 0x1E, 0x1E, 1, 0x96, 0x78, 0, 1.0f);
}

void effectSpawnRingBursts(Actor *, f32, f32, s32);
void func_80665564(Actor *, f32);

void func_806A7518(void) {
    if (!(D_807FBB40->unk60 & 0x10)) {
        D_807FBB40->unk60 |= 0x400;
        effectSpawnRingBursts(D_807FBB40, 20.0f, 40.0f, 0x1E);
        D_807FBB40->unkA4 = 99999.0f;
        func_80665564(D_807FBB40, 0);
    }
    func_806A6DB4(0);
    if (D_807FBB40->unkA4 != 99999.0f) {
        func_8065D254(D_807FBB40, 0x3C8, 0x40, 0x40, 0x19, 0x19, 1, 0x96, 0x78, 0, 1.0f);
    }
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/AA960/func_806A7600.s")

extern u8 D_80720FBC;
void func_806A7600(void *);

void func_806A7B04(void) {
    func_806A7600(&D_80720FBC);
}

extern u8 D_80720F98;

void func_806A7B28(void) {
    func_806A7600(&D_80720F98);
}

extern u8 D_80721028;

void func_806A7B4C(void) {
    func_806A7600(&D_80721028);
}

extern u8 D_80721004;

void func_806A7B70(void) {
    func_806A7600(&D_80721004);
}

extern u8 D_80720FE0;

void func_806A7B94(void) {
    func_806A7600(&D_80720FE0);
}

void func_806A7BB8(void) {
    func_806A7600(&D_80721004);
}

void actorAppendModelNode(Actor *, f32, f32, f32, f32, s32);
void actorAppendModelSubNode(Actor *, f32, f32, f32, s32);
void func_8066EB40(Actor *, f32);
void actorDespawn(void *);
void func_80714998(s32);
void func_807149FC(s32);
void func_807149B8(s32);
void func_80714950(s32);
void func_807149C8(s32, s32, s32, u8);
void func_8071498C(void (*)(void));
void func_80714C08(void *, f32, void *, s32, s32);
void func_8071D28C(void);
void func_8071EB70(void);
void func_806F8BC4(s32, s32, s32);
void func_806F91B4(s32, s32, s32);

typedef struct AA960SfxTable {
    s32 unk0[7];
} AA960SfxTable;

extern u8 D_8074E77C;
extern u8 D_807FBD70;
extern u8 D_807FC954[];
extern u32 D_8076A064;
extern u8 D_80721170;
extern AA960SfxTable D_807504A4;
void func_8067ACB4(Actor *);
s32 func_80611A44(void);
s32 func_806F8EDC(s32, s32);

void func_806A7BDC(void) {
    s32 flag;
    s32 idx;
    AA960SfxTable table;

    flag = D_807FC954[D_8074E77C * 94] & 1;
    if (!(D_807FBB40->unk60 & 0x10)) {
        actorAppendModelSubNode(D_807FBB40, 0.0f, 10.0f, 0.0f, -1);
        func_8066EB40(D_807FBB40, 175.0f);
        actorAppendModelNode(D_807FBB40, 0.0f, 10.0f, 0.0f, 80.0f, -1);
        D_807FBB40->unkA4 = 99999.0f;
        func_80665564(D_807FBB40, 0);
    }
    func_8067ACB4(D_807FBB40);
    if (flag != 0) {
        if (D_807FBD70 == 4) {
            if (D_8076A064 % 5 == 0) {
                idx = (func_80611A44() >> 15) % 0xFF % 7;
                table = D_807504A4;
                func_8071498C(&func_8071D28C);
                func_807149FC(-1);
                func_807149B8(1);
                func_80714950(100);
                func_80714C08((void *)table.unk0[idx], 0.2f, D_807FBB40, 1, 0);
                sfxAllocateChannel(0x7F, 1.0f);
                func_806F8BC4(7, 0, 0);
                func_806F91B4(7, 0, (s16)func_806F8EDC(7, 0));
            }
        }
    }
    if (!(D_8076A064 & 0xF)) {
        func_807149B8(1);
        func_8071498C(&func_8071EB70);
        func_80714950(0x226);
        func_80714998(2);
        func_807149C8(0xFF, 0xFF, 0xFF, flag ? 0xFF : 0x7F);
        func_80714C08(&D_80721170, 0.4f, D_807FBB40, 1, 2);
    }
    if (D_807FBB40->unkA4 != 99999.0f) {
        func_8065D254(D_807FBB40, 0x3C8, 0x40, 0x40, 0xE, 0xE, 1, 0x96, 0x78, 0, 1.0f);
    }
}

typedef struct AA960ActorSub4 {
    u8 pad0[0x20];
    void *unk20;
} AA960ActorSub4;

typedef struct AA960SparkleSub174 {
    f32 unk0;
    s16 unk4;
} AA960SparkleSub174;

typedef struct AA960SparkleBuffer {
    u8 unk0;
    u8 unk1;
    u8 pad2[2];
    f32 unk4;
    f32 unk8;
    f32 unkC;
    u8 unk10;
} AA960SparkleBuffer;

extern u8 D_807504C8;
extern u8 D_807504CC;
extern u8 D_807504D0;
extern f32 D_807504C0;
extern f32 D_807504C4;
void *func_80610FE8(s32);
void heapClearBlock(void *);
void func_806319C4(Actor *, s32);

void func_806A7EF0(void) {
    AA960SparkleSub174 *temp_v1;
    AA960SparkleBuffer *temp_v0;

    temp_v1 = D_807FBB40->unk174;
    if (!(D_807FBB40->unk60 & 0x10)) {
        ((AA960ActorSub4 *)D_807FBB40->unk4)->unk20 = func_80610FE8(0x20);
        heapClearBlock(((AA960ActorSub4 *)D_807FBB40->unk4)->unk20);
        temp_v1->unk4 = 0;
        temp_v1->unk0 = 1.0f;
        D_807FBB40->unk60 &= ~0x8000;
        D_807FBB40->unk60 |= 0x40000000;
        D_807FBB40->unk128 = D_807504CC;
    }
    if (D_807504D0 < D_807FBB40->unk128) {
        D_807FBB40->unk128 -= D_807504D0;
    }
    temp_v1->unk4 += 1;
    if (D_807504C4 < (f32)temp_v1->unk4) {
        actorDespawn(D_807FBB40);
    } else {
        temp_v1->unk0 *= D_807504C0;
        temp_v0 = ((AA960ActorSub4 *)D_807FBB40->unk4)->unk20;
        temp_v0->unk0 = D_807504C8;
        temp_v0->unk1 = 0xFF;
        temp_v0->unk4 = temp_v1->unk0;
        temp_v0->unk8 = temp_v1->unk0;
        temp_v0->unkC = temp_v1->unk0;
        temp_v0->unk10 = 0xFF;
        func_806319C4(D_807FBB40, 0);
    }
}


void func_806A8070(void) {
    if (!(D_807FBB40->unk60 & 0x10)) {
        D_807FBB40->unk60 |= 0x40000000;
    }
    func_806319C4(D_807FBB40, 0);
}
