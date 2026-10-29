// func_80715270 (src/global/119370.c): stage 5: full structure reconstructed; remaining: (1) ==1/==2 branch layout/block ordering at 0xc94; (2) prologue andi a0,0xff register assignment
#include "common.h"

#define UA1_D08_FIELD(type, effect, offset) (*(type *)((u8 *)(effect) + (offset)))

extern u8 D_807444FC;
extern u32 D_8076A064;
extern s32 D_807FC924;
extern EffectGridNode *D_807FDB00;
extern EffectNode *D_807FDB04;
extern u8 D_80750AB4;

void modelSlotGetNodePos(s32, s32, s32, f32 *, f32 *, f32 *);
void actorGetNodePos(void *, s32, f32 *, f32 *, f32 *);
void assetFreeBuffer(s32, s32, s32);
s16 func_806531B8(f32, f32, f32, s32);
s32 renderEntryAddOrUpdate(s32, u8, void *, f32, f32, f32, s32, s32, s32, s32, s32);
void func_80715A3C(s16 *, u8, u8 *, s32, s32, s32 *);
void effectFreeAndUnlink(EffectNode *);
void func_80715B30(Mtx *, u8, f32, f32, f32, f32, f32, f32, f32, f32, u8);

void func_80715270(u8 arg0) {
    EffectNode *effect;
    EffectGridNode *node2;
    u8 sp7B;
    s32 i;
    s32 offset;

    effect = D_807FDB04;
    for (; effect != NULL; effect = effect->next) {
        if (UA1_D08_FIELD(s16, effect, 0x368) == 0) {
            UA1_D08_FIELD(u8, effect, 0x32C) = 0;
            UA1_D08_FIELD(u8, effect, 0x32D) = 0;
            UA1_D08_FIELD(u8, effect, 0x21) = 0;
            UA1_D08_FIELD(s32, UA1_D08_FIELD(EffectGridNode *, effect, 0x330), 0x18) = D_8076A064;
            effect->flags &= 0xFFEF;
            if (UA1_D08_FIELD(u8, effect, 0x334) == 1) {
                goto model_slot;
            }
            if (UA1_D08_FIELD(u8, effect, 0x334) == 2) {
                Actor *actor = UA1_D08_FIELD(Actor *, effect, 0x338);
                if ((actor->unk60 & 0x200) != 0 || actor->unk4 == NULL) {
                    actorGetNodePos(actor, UA1_D08_FIELD(u8, effect, 0x33E), (f32 *)((u8 *)effect + 0x340),
                                    (f32 *)((u8 *)effect + 0x344), (f32 *)((u8 *)effect + 0x348));
                } else {
                    effect->flags |= 0x10;
                }
            }
            goto after_model_slot;
model_slot:
            modelSlotGetNodePos(UA1_D08_FIELD(s16, effect, 0x33C), 1, UA1_D08_FIELD(u8, effect, 0x33E),
                                (f32 *)((u8 *)effect + 0x340), (f32 *)((u8 *)effect + 0x344),
                                (f32 *)((u8 *)effect + 0x348));
after_model_slot:
            sp7B = 0;
            if (arg0 == 0 || (effect->flags & 1)) {
                if (UA1_D08_FIELD(void *, effect, 0x328) != NULL) {
                    ((void (*)(void *, u8 *))UA1_D08_FIELD(void *, effect, 0x328))(effect, &sp7B);
                }
            } else if (UA1_D08_FIELD(void *, effect, 0x328) != NULL) {
                if (D_80750AB4 > 0) {
                    i = 0;
                    offset = 0;
                    do {
                        if (((u8 *)D_807FC924)[offset] != 0) {
                            memcpy((u8 *)effect + i * 0x80 + D_807444FC * 0x40 + 0x128,
                                   (u8 *)effect + i * 0x80 + (D_807444FC ^ 1) * 0x40 + 0x128, 0x40);
                        }
                        i++;
                        offset += 0x2F0;
                    } while (i < D_80750AB4);
                }
                UA1_D08_FIELD(u8, effect, 0x32C) = 3;
            }
            if (UA1_D08_FIELD(s16, UA1_D08_FIELD(EffectGridNode *, effect, 0x330), 0x16) ==
                UA1_D08_FIELD(s16, effect, 0x34E)) {
                UA1_D08_FIELD(s16, effect, 0x34E) = 0;
                UA1_D08_FIELD(s32, effect, 0x358) = UA1_D08_FIELD(s32, effect, 0x358) + 1;
                if (UA1_D08_FIELD(s32, effect, 0x354) == UA1_D08_FIELD(s32, effect, 0x358) &&
                    -1 != UA1_D08_FIELD(s32, effect, 0x354)) {
                    UA1_D08_FIELD(u8, effect, 0x32D) = 1;
                }
            }
            if (sp7B != 0) {
                UA1_D08_FIELD(u8, effect, 0x32D) = 1;
            }
            if (UA1_D08_FIELD(u8, effect, 0x32D) != 0) {
                effectFreeAndUnlink(effect);
            } else {
                if (D_80750AB4 >= 2) {
                    i = 1;
                    offset = 0x2F0;
                    do {
                        if (((u8 *)D_807FC924)[offset] != 0) {
                            memcpy((u8 *)effect + i * 0x80 + D_807444FC * 0x40 + 0x128,
                                   (u8 *)effect + D_807444FC * 0x40 + 0x128, 0x40);
                        }
                        i++;
                        offset += 0x2F0;
                    } while (i < D_80750AB4);
                }
                if (UA1_D08_FIELD(u8, effect, 0x32C) != 3) {
                    if (D_80750AB4 > 0) {
                        i = 0;
                        offset = 0;
                        do {
                            if (((u8 *)D_807FC924)[offset] != 0) {
                                func_80715B30((Mtx *)((u8 *)effect + i * 0x80 + D_807444FC * 0x40 + 0x128),
                                              UA1_D08_FIELD(u8, effect, 0x32C),
                                              UA1_D08_FIELD(f32, effect, 0x360),
                                              UA1_D08_FIELD(f32, effect, 0x364),
                                              UA1_D08_FIELD(f32, (u8 *)D_807FC924 + offset, 0x21C),
                                              UA1_D08_FIELD(f32, (u8 *)D_807FC924 + offset, 0x220),
                                              UA1_D08_FIELD(f32, (u8 *)D_807FC924 + offset, 0x224),
                                              UA1_D08_FIELD(f32, effect, 0x340),
                                              UA1_D08_FIELD(f32, effect, 0x344),
                                              UA1_D08_FIELD(f32, effect, 0x348), effect->mode);
                            }
                            i++;
                            offset += 0x2F0;
                        } while (i < D_80750AB4);
                    }
                    UA1_D08_FIELD(u8, effect, 0x32C) = 3;
                }
                if (effect->mode == 0) {
                    s32 renderArg = 1;
                    if (effect->flags & 4) {
                        renderArg = 4;
                        if (!(effect->flags & 8)) {
                            UA1_D08_FIELD(s8, effect, 0x38A) = func_806531B8(
                                UA1_D08_FIELD(f32, effect, 0x340), UA1_D08_FIELD(f32, effect, 0x344),
                                UA1_D08_FIELD(f32, effect, 0x348), 0);
                        }
                    }
                    renderEntryAddOrUpdate(0, 5, effect, UA1_D08_FIELD(f32, effect, 0x340),
                                           UA1_D08_FIELD(f32, effect, 0x344),
                                           UA1_D08_FIELD(f32, effect, 0x348),
                                           UA1_D08_FIELD(s16, effect, 0x34C), 0, 1, -1, renderArg);
                } else {
                    renderEntryAddOrUpdate(0, 5, effect, UA1_D08_FIELD(f32, effect, 0x340),
                                           UA1_D08_FIELD(f32, effect, 0x344),
                                           UA1_D08_FIELD(f32, effect, 0x348), 0, 0, 1, -1, 3);
                }
                func_80715A3C((s16 *)UA1_D08_FIELD(void *, UA1_D08_FIELD(EffectGridNode *, effect, 0x330), 0x20),
                              UA1_D08_FIELD(u8, UA1_D08_FIELD(EffectGridNode *, effect, 0x330), 0x15),
                              (u8 *)UA1_D08_FIELD(void *, UA1_D08_FIELD(EffectGridNode *, effect, 0x330), 0x1C),
                              UA1_D08_FIELD(s32, effect, 0x380), UA1_D08_FIELD(s16, effect, 0x34E),
                              &UA1_D08_FIELD(s32, effect, 0x370));
                if (arg0 == 0 || (effect->flags & 1)) {
                    UA1_D08_FIELD(u8, effect, 0x351) = UA1_D08_FIELD(u8, effect, 0x351) + 1;
                    if (UA1_D08_FIELD(u8, effect, 0x350) ==
                        (UA1_D08_FIELD(u8, effect, 0x351) & 0xFF)) {
                        UA1_D08_FIELD(s16, effect, 0x34E) = UA1_D08_FIELD(s16, effect, 0x34E) + 1;
                        UA1_D08_FIELD(u8, effect, 0x351) = 0;
                    }
                }
            }
            effect->flags |= 8;
        } else {
            if (arg0 == 0 || (effect->flags & 1)) {
                UA1_D08_FIELD(s16, effect, 0x368) = UA1_D08_FIELD(s16, effect, 0x368) - 1;
            }
        }
    }
    for (node2 = D_807FDB00; node2 != NULL; node2 = node2->unk24) {
        if (D_8076A064 - node2->unk18 >= 0xB) {
            continue;
        }
        if (node2->unk18 == -1) {
            continue;
        }
        if (node2->unk16 * node2->unk8 * node2->unk9 > 0) {
            i = 0;
            offset = 0;
            do {
                if (((s32 *)((u8 *)node2->unk20 + offset))[1] != -1) {
                    if (D_8076A064 - node2->unk18 == 0xA) {
                        assetFreeBuffer(((s32 *)((u8 *)node2->unk20 + offset))[0], 0x319, 0x1F);
                        ((s32 *)((u8 *)node2->unk20 + offset))[1] = -1;
                    }
                }
                i++;
                offset += 8;
            } while (i < node2->unk16 * node2->unk8 * node2->unk9);
        }
    }
}
