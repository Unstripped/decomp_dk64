#include "common.h"
#include "actor.h"

s32 actorSpawn(s32, s32);
void func_8072E868(void);
void func_80727678(void);
void func_80727958(void);

void actorSpawnInitialSet(void) {
    actorSpawn(0xA, 0);
    actorSpawn(0xB, 0);
    actorSpawn(0xC, 0);
    actorSpawn(0xD, 0);
    actorSpawn(0xE, 0);
    actorSpawn(0xF, 0);
}

void func_8068A810(void) {
    func_8072E868();
}

void func_8068A830(void) {
    func_80727678();
    func_80727958();
}
#pragma GLOBAL_ASM("asm/global/nonmatchings/8F4B0/func_8068A858.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/8F4B0/func_8068ABE0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/8F4B0/func_8068AD7C.s")

extern u8 D_807FC620;
extern u8 D_807FC621;
extern u8 D_807FC622;

void func_8068B80C(void) {
    D_807FC620 = 1;
}

void func_8068B81C(void) {
    D_807FC621 = 0;
    D_807FC622 = 0;
}
typedef struct {
    /* 0x00 */ u8 unk0;
    /* 0x01 */ u8 unk1[3];
    /* 0x04 */ f32 unk4;
    /* 0x08 */ s16 unk8;
    /* 0x0A */ s16 unkA;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ u8 unk18;
    /* 0x19 */ u8 unk19[3];
    /* 0x1C */ s16 unk1C;
    /* 0x1E */ s16 unk1E;
} Actor174;

void func_8072E7DC(s32, void *);

void func_8068B830(s16 arg0, s16 arg1, s16 arg2) {
    Actor *sp1C;
    Actor174 *temp_v0;

    func_8072E7DC(0xC, &sp1C);
    temp_v0 = (Actor174 *)sp1C->unk174;
    temp_v0->unk0 = arg0;
    temp_v0->unk4 = (f64)(f32)arg1 / 100.0;
    temp_v0->unk8 = arg2;
}

void func_8068B8A4(f32 arg0) {
    Actor *sp1C;
    Actor174 *temp_v0;

    func_8072E7DC(0xC, &sp1C);
    temp_v0 = (Actor174 *)sp1C->unk174;
    temp_v0->unkC = arg0;
    temp_v0->unk10 = arg0;
    temp_v0->unk14 = arg0;
    if (temp_v0->unk18 == 0) {
        temp_v0->unk1C = 1;
        temp_v0->unk1E = temp_v0->unk1C;
    }
}

void func_8068B8FC(void) {
    Actor *sp1C;
    u8 *ptr;

    func_8072E7DC(0xC, &sp1C);
    ptr = sp1C->unk174;
    *ptr = 0xFF;
}

extern ActorGlobalState D_807FBB70;
extern u8 D_807FBDC4;
void func_8063DA40(s16, s16);
void func_8062BAE4(void);
void actorListDispatchEvent(s16, void *);

void func_8068B930(void) {
    s32 i;
    s16 *ptr;

    for (i = 0; i < D_807FBDC4; i++) {
        ptr = D_807FBB70.unk278[i];
        if (D_807FBB70.unk258[i] == 1) {
            func_8063DA40(ptr[0], ptr[1]);
        }
    }
    func_8062BAE4();
}

void func_8068B9B4(void) {
    s32 i;
    s16 *ptr;

    for (i = 0; i < D_807FBDC4; i++) {
        ptr = D_807FBB70.unk278[i];
        if (D_807FBB70.unk258[i] == 1) {
            actorListDispatchEvent(ptr[1], ptr);
        }
    }
}

typedef struct {
    char pad[0xAC];
    u32 unkAC;
} ActorSub174;

typedef struct {
    char pad[0x104];
    Actor *unk104;
    char pad108[0x1F0 - 0x108];
    u32 unk1F0;
} Actor174Player;

typedef struct {
    char pad[0x210];
    f32 unk210;
    f32 unk214;
    f32 unk218;
    char pad21C[0xC];
    f32 unk228;
    f32 unk22C;
    f32 unk230;
} ActorPlayerPos;

extern Actor *D_807FBB48;
extern ActorPlayerPos *D_807FC924;
void func_8061CC40(s32, s32, u8);
void func_8072167C(s16, s16, s16, s16);
void lightAdd(f32, f32, f32, f32, f32, f32, f32, s32, s32, s32, s32);

void func_8068BA2C(void) {
    s32 pad;
    ActorSub174 *sp58;
    Actor174Player *s1;
    s32 var_s3;
    s16 i;
    s16 *ptr;
    s32 var_v0;

    s1 = D_807FBB48->unk174;
    var_s3 = 0;
    sp58 = ((Actor *)s1->unk104)->unk174;
    for (i = 0; i < D_807FBB70.unk254; i++) {
        ptr = D_807FBB70.unk278[i];
        switch ((u32)D_807FBB70.unk258[i]) {
        case 1:
            var_v0 = (ptr[1] != 0) ? 4 : 0;
            func_8061CC40(0, ptr[0], var_v0 | 1);
            break;
        case 2:
            func_8072167C(ptr[0], ptr[1], ptr[2], ptr[3]);
            break;
        case 3:
            var_s3 = 1;
            if (!(s1->unk1F0 & 0x04000000)) {
                s1->unk1F0 |= 0x04000000;
            }
            break;
        }
    }
    if (var_s3 == 0) {
        s1->unk1F0 &= ~0x04000000;
    }
    if (sp58->unkAC & 1) {
        lightAdd(D_807FC924->unk210, D_807FC924->unk214, D_807FC924->unk218, D_807FC924->unk228, D_807FC924->unk22C, D_807FC924->unk230, 0.0f, 1, 0xFF, 0xFF, 0xFF);
    }
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/8F4B0/func_8068BBF8.s")
