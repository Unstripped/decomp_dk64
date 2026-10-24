// func_806AFA60 (src/global/B2CE0.c): text-identical, reloc only: ldc1 of 0.15 double uses .rodata+632 vs expected D_8075B098 label. for(i=0;i<7;i++) (not do-while) puts move s0,zero in the right slot; u8 arg0.
#include "actor.h"
typedef struct M3Actor {
    /* 0x000 */ u8 pad0[4];
    /* 0x004 */ ActorSub4 *unk4;
    /* 0x008 */ u8 pad8[4];
    /* 0x00C */ f32 unkC[4][4];
    /* 0x04C */ u8 pad4C[0x14];
    /* 0x060 */ u32 unk60;
    /* 0x064 */ u32 unk64;
    /* 0x068 */ u8 pad68[2];
    /* 0x06A */ u16 unk6A;
    /* 0x06C */ u16 unk6C;
    /* 0x06E */ u8 pad6E[0xE];
    /* 0x07C */ f32 unk7C;
    /* 0x080 */ f32 unk80;
    /* 0x084 */ f32 unk84;
    /* 0x088 */ u8 pad88[0x1C];
    /* 0x0A4 */ f32 unkA4;
    /* 0x0A8 */ u8 padA8[0x10];
    /* 0x0B8 */ f32 unkB8;
    /* 0x0BC */ u8 padBC[4];
    /* 0x0C0 */ f32 unkC0;
    /* 0x0C4 */ f32 unkC4;
    /* 0x0C8 */ f32 unkC8;
    /* 0x0CC */ u8 padCC[0x1A];
    /* 0x0E6 */ s16 unkE6;
    /* 0x0E8 */ u8 padE8[6];
    /* 0x0EE */ s16 unkEE;
    /* 0x0F0 */ u8 padF0[0x42];
    /* 0x132 */ s16 unk132;
    /* 0x134 */ u8 pad134[0x20];
    /* 0x154 */ u8 unk154;
    /* 0x155 */ u8 unk155;
    /* 0x156 */ u8 pad156[9];
    /* 0x15F */ u8 unk15F;
    /* 0x160 */ u8 pad160[8];
    /* 0x168 */ s16 unk168;
} M3Actor;

extern M3Actor *D_807FBB40;
void func_807149B8(s32);
void func_807149FC(s32);
void func_8071498C(void (*)());
void func_80714998(s32);
void func_80714950(s32);
void func_80714C08(void *, f32, M3Actor *, s32, s32);
void func_8071910C();
extern u8 D_8072073C;

void func_806AFA60(u8 arg0) {
    s16 i;
    f32 temp;

    for (i = 0; i < 7; i++) {
        temp = D_807FBB40->unk4->unk38 / 0.15;
        func_807149B8(1);
        func_807149FC(10);
        func_8071498C(func_8071910C);
        func_80714998(2);
        func_80714950(0);
        func_80714C08(&D_8072073C, temp * 0.15, D_807FBB40, arg0, 0);
    }
}
