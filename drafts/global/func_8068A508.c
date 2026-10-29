// func_8068A508 (src/global/8F050.c): Stage 5, score 120 (frame 0x88, saved regs match, minor addiu hoisting and regalloc for entry pointer and unk174)
typedef struct KaF_PlayerC924 {
    u8 pad[0x210];
    f32 unk210;
    f32 unk214;
    f32 unk218;
} KaF_PlayerC924;

typedef struct KaF_Sub174 {
    u8 pad[0x1A4];
    u8 unk1A4;
} KaF_Sub174;

typedef struct KaF_ActorAll {
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
    KaF_Sub174 *unk174;
} KaF_ActorAll;

typedef struct KaF_ActorEntry {
    KaF_ActorAll *actor;
    u32 unk4;
} KaF_ActorEntry;

extern u16 gActiveActorCount;
extern KaF_ActorEntry gActiveActors[];
extern KaF_PlayerC924 *D_807FC924;
extern u8 D_807FC928;
extern s32 D_807552F4[];

void func_80613794(void *, u32);
f32 renderScaleDistanceByFov(f32);

void func_8068A508(void) {
    s32 pad;
    s32 sp80;
    s32 pad2[3];
    s32 var_s1;
    KaF_ActorEntry *entry_ptr;
    KaF_ActorAll *actor;
    ActorConfig8F050 *entry;
    f32 dist_sq;
    f32 r;
    s32 a2;

    var_s1 = 0;
    if ((s32)gActiveActorCount > 0) {
        entry_ptr = gActiveActors;
        do {
            actor = entry_ptr->actor;
            if (!(actor->unk60 & 0x2000) && (actor->unk60 & 0x100)) {
                dist_sq = ((actor->unk84 - D_807FC924->unk218) * (actor->unk84 - D_807FC924->unk218)) +
                          (((actor->unk7C - D_807FC924->unk210) * (actor->unk7C - D_807FC924->unk210)) +
                           ((actor->unk80 - D_807FC924->unk214) * (actor->unk80 - D_807FC924->unk214)));
                if (func_8068A3A0(actor->unk58, &sp80) != 0) {
                    r = renderScaleDistanceByFov(((ActorConfig8F050 *)((u8 *)D_80750100 + sp80 * 20))->unk4);
                    entry = (ActorConfig8F050 *)((u8 *)D_80750100 + sp80 * 20);
                    switch (entry->unk8) {
                    case 0:
                        if (D_807FC928 >= 2) {
                            pad = actor->unk174->unk1A4;
                            a2 = D_807552F4[pad];
                            if (a2 >= 0) {
                                func_8068A404((Actor4C *)actor, sp80, a2);
                            }
                        }
                        break;
                    case 1:
                        if (r * r < dist_sq) {
                            if (actor->unk4C == 0) {
                                actor->unk4C = func_80612E90(actor, entry->unk2, 0);
                            }
                        } else if (actor->unk4C != 0) {
                            func_80613794(actor, 1);
                        }
                        break;
                    case 2:
                        if (dist_sq < r * r) {
                            if (actor->unk4C == 0) {
                                actor->unk4C = func_80612E90(actor, entry->unk2, 0);
                            }
                        } else if (actor->unk4C != 0) {
                            func_80613794(actor, 1);
                        }
                        break;
                    }
                }
            }
            var_s1++;
            entry_ptr++;
        } while (var_s1 < (s32)gActiveActorCount);
    }
}
