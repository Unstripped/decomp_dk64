// func_80715270 (src/global/119370.c): func_80715270 stage 6: text identical except second loop (free-buffer loop) uses node2=s2/offset=s1 where expected has node2=s1/offset=s2 (23 diff lines, all that swap). Tried: loop form variants, separate i/offset vars, 1-2 dead-stmt sweeps, permuter 540s, callee return toggles. Notes: switch(type){case1,case2} + 'else renderArg=1' + '!arg0' + no Actor local + unk1C needed.
// func_80715270 stage 6: text identical except second loop (free-buffer loop) uses node2=s2/offset=s1 where expected has node2=s1/offset=s2 (23 diff lines, all that swap). Tried: loop form variants, separate i/offset vars, 1-2 dead-stmt sweeps, permuter 540s, callee return toggles. Notes: switch(type){case1,case2} + 'else renderArg=1' + '!arg0' + no Actor local + unk1C needed.
#include "common.h"
#include "actor.h"

// needs EffectNode/EffectGridNode from src/global/119370.c head
#define UA1_D08_FIELD(type, effect, offset) (*(type *)((u8 *)(effect) + (offset)))
extern u32 D_8076A064;
extern s32 D_807FC924;
void assetFreeBuffer(s32, s32, s32);
s16 mapChunkFindByPosition(f32, f32, f32, s32);
s32 renderEntryAddOrUpdate(s32, u8, void *, f32, f32, f32, s32, s32, s32, s32, s32);
void func_80715A3C(s16 *, u8, u8 *, s32, s32, s32 *);
void effectFreeAndUnlink(EffectNode *);
void effectComputeTransformMatrix(Mtx *, u8, f32, f32, f32, f32, f32, f32, f32, f32, u8);

void func_80715270(u8 arg0) {
    EffectNode *effect;
    u8 sp7B;
    EffectGridNode *node2;
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
            switch (UA1_D08_FIELD(u8, effect, 0x334)) {
            case 1:
                modelSlotGetNodePos(UA1_D08_FIELD(s16, effect, 0x33C), 1, UA1_D08_FIELD(u8, effect, 0x33E),
                                    (f32 *)((u8 *)effect + 0x340), (f32 *)((u8 *)effect + 0x344),
                                    (f32 *)((u8 *)effect + 0x348));
                break;
            case 2: {
                if ((UA1_D08_FIELD(Actor *, effect, 0x338)->unk60 & 0x200) != 0 || UA1_D08_FIELD(Actor *, effect, 0x338)->unk4 == NULL) {
                    actorGetNodePos(UA1_D08_FIELD(Actor *, effect, 0x338), UA1_D08_FIELD(u8, effect, 0x33E), (f32 *)((u8 *)effect + 0x340),
                                    (f32 *)((u8 *)effect + 0x344), (f32 *)((u8 *)effect + 0x348));
                } else {
                    effect->flags |= 0x10;
                }
                break;
            }
            }
            sp7B = 0;
            if (!arg0 || (effect->flags & 1)) {
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
                                effectComputeTransformMatrix((Mtx *)((u8 *)effect + i * 0x80 + D_807444FC * 0x40 + 0x128),
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
                    s32 renderArg;
                    if (effect->flags & 4) {
                        renderArg = 4;
                        if (!(effect->flags & 8)) {
                            UA1_D08_FIELD(s8, effect, 0x38A) = mapChunkFindByPosition(
                                UA1_D08_FIELD(f32, effect, 0x340), UA1_D08_FIELD(f32, effect, 0x344),
                                UA1_D08_FIELD(f32, effect, 0x348), 0);
                        }
                    } else {
                        renderArg = 1;
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
                if (!arg0 || (effect->flags & 1)) {
                    UA1_D08_FIELD(u8, effect, 0x351) = UA1_D08_FIELD(u8, effect, 0x351) + 1;
                    if (UA1_D08_FIELD(u8, effect, 0x350) == UA1_D08_FIELD(u8, effect, 0x351)) {
                        UA1_D08_FIELD(s16, effect, 0x34E) = UA1_D08_FIELD(s16, effect, 0x34E) + 1;
                        UA1_D08_FIELD(u8, effect, 0x351) = 0;
                    }
                }
            }
            effect->flags |= 8;
        } else {
            if (!arg0 || (effect->flags & 1)) {
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
                if (((s32 *)((u8 *)node2->unk1C + offset))[1] != -1) {
                    if (D_8076A064 - node2->unk18 == 0xA) {
                        assetFreeBuffer(((s32 *)((u8 *)node2->unk1C + offset))[0], 0x319, 0x1F);
                        ((s32 *)((u8 *)node2->unk1C + offset))[1] = -1;
                    }
                }
                i++;
                offset += 8;
            } while (i < node2->unk16 * node2->unk8 * node2->unk9);
        }
    }
}
#undef UA1_D08_FIELD
