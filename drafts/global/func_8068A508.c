// func_8068A508 (src/global/8F050.c): Closest diff: stack frame size and registers match; float temporaries cause spill
#include "common.h"

typedef struct Act8CA_Struct_8F050 {
    s16 unk0;
    s16 unk2;
    f32 unk4;
    u8 unk8;
    u8 unk9;
    s16 unkA;
    s32 unkC[2];
} Act8CA_Struct_8F050;

typedef struct Act8CA_PlayerC924 {
    u8 pad[0x210];
    f32 unk210;
    f32 unk214;
    f32 unk218;
} Act8CA_PlayerC924;

typedef struct Act8CA_Sub174 {
    u8 pad[0x1A4];
    u8 unk1A4;
} Act8CA_Sub174;

typedef struct Act8CA_ActorAll {
    u8 pad0[0x4C];
    s32 unk4C;
    u8 pad50[0x8];
    s32 unk58;
    u8 pad5C[0x4];
    s32 unk60;
    u8 pad64[0x18];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
    u8 pad88[0xEC];
    Act8CA_Sub174 *unk174;
} Act8CA_ActorAll;

typedef struct Act8CA_ActorEntry {
    Act8CA_ActorAll *actor;
    u32 unk4;
} Act8CA_ActorEntry;

typedef struct Act8CA_Actor4C {
    u8 pad[0x4C];
    s32 unk4C;
} Act8CA_Actor4C;

extern u16 D_807FBB34;
extern Act8CA_ActorEntry D_807FB930[];
extern Act8CA_PlayerC924 *D_807FC924;
extern u8 D_807FC928;
extern s32 D_807552F4[];
extern Act8CA_Struct_8F050 D_80750100[];

s32 func_80612E90(void *, s32, s32);
void func_80613794(void *, s32);
f32 func_8065D0FC(f32);
s32 func_8068A3A0(s32, s32 *);
void func_8068A404(Act8CA_Actor4C *, s32, s32);

void func_8068A508(void) {
    s32 sp80;
    s32 var_s1;
    Act8CA_ActorEntry *entry_ptr;
    Act8CA_ActorAll *actor;
    Act8CA_Struct_8F050 *entry;
    f32 dist_sq;
    s32 a2;
    s32 one = 1;
    s32 two = 2;
    s32 sz = 20;

    var_s1 = 0;
    if ((s32)D_807FBB34 > 0) {
        entry_ptr = D_807FB930;
        do {
            actor = entry_ptr->actor;
            if (!(actor->unk60 & 0x2000) && (actor->unk60 & 0x100)) {
                dist_sq = ((actor->unk84 - D_807FC924->unk218) * (actor->unk84 - D_807FC924->unk218)) +
                          (((actor->unk7C - D_807FC924->unk210) * (actor->unk7C - D_807FC924->unk210)) +
                           ((actor->unk80 - D_807FC924->unk214) * (actor->unk80 - D_807FC924->unk214)));
                if (func_8068A3A0(actor->unk58, &sp80) != 0) {
                    entry = (Act8CA_Struct_8F050 *)((u8 *)D_80750100 + sp80 * sz);
                    switch (entry->unk8) {
                    case 0:
                        if (D_807FC928 >= two) {
                            a2 = D_807552F4[actor->unk174->unk1A4];
                            if (a2 >= 0) {
                                func_8068A404((Act8CA_Actor4C *)actor, sp80, a2);
                            }
                        }
                        break;
                    case 1: {
                        f32 r = func_8065D0FC(entry->unk4);
                        if (r * r < dist_sq) {
                            if (actor->unk4C == 0) {
                                actor->unk4C = func_80612E90(actor, entry->unk2, 0);
                            }
                        } else if (actor->unk4C != 0) {
                            func_80613794(actor, one);
                        }
                        break;
                    }
                    case 2: {
                        f32 r = func_8065D0FC(entry->unk4);
                        if (dist_sq < r * r) {
                            if (actor->unk4C == 0) {
                                actor->unk4C = func_80612E90(actor, entry->unk2, 0);
                            }
                        } else if (actor->unk4C != 0) {
                            func_80613794(actor, one);
                        }
                        break;
                    }
                    }
                }
            }
            var_s1++;
            entry_ptr++;
        } while (var_s1 < (s32)D_807FBB34);
    }
}
