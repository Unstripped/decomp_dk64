// func_80674E14 (src/global/79890.c): from .scratch/Beh7984A/func_80674E14_best.c
typedef struct Beh7984A_Node {
    u8 pad0[0x10];
    s32 unk10;
    s32 unk14;
    s32 unk18;
    s32 unk1C;
    u8 pad20[8];
    struct Beh7984A_Node *next;
} Beh7984A_Node;

typedef struct Beh7984A_Sub140 {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    u8 pad10[0x7C];
    Beh7984A_Node *unk8C;
} Beh7984A_Sub140;

typedef struct Beh7984A_Actor {
    u8 pad0[0x54];
    s32 unk54;
    u8 pad58[4];
    u16 unk5C;
    u8 pad5E[2];
    u32 unk60;
    u8 pad64[0x18];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
    u8 pad88[0x8C];
    void *unk114;
    u8 pad118[0x28];
    Beh7984A_Sub140 *unk140;
    u8 unk144;
} Beh7984A_Actor;

typedef struct Beh7984A_ActorEntry {
    Beh7984A_Actor *actor;
} Beh7984A_ActorEntry;

extern u16 D_807FBB34;
extern Beh7984A_ActorEntry D_807FB930[];
extern void *D_807FB620;
extern void *D_807FB624;
extern s32 D_807FB628;

s32 func_80679010(void *, void *);
s32 func_80674ADC(s32, s32, s32, s32, s32, s32, s32, s32);
void func_80671880(void *, s32);
f32 func_80675234(s32, s32, s32, s32, s32, s32, s32);
void func_80675180(void *, f32, f32, f32, void *, f32 *, f32 *, f32 *);
void func_806752D4(s32, f32, f32, f32, f32, s32, s32);
void func_80675380(s32, void *);

void func_80674E14(Beh7984A_Actor *arg0) {
    s32 i;
    Beh7984A_Actor *actor;
    Beh7984A_Sub140 *actor_sub140;
    s32 sub_unk0;
    s32 sub_unk4;
    s32 sub_unk8;
    s32 sub_unkC;
    Beh7984A_Node *node1;
    Beh7984A_Node *node2;
    s32 var_s4;
    s32 var_s2;
    Beh7984A_Sub140 *sub140;
    f32 dist;
    f32 sp70;
    f32 sp6C;
    f32 sp68;
    s32 s0;
    u16 mask1;
    u16 mask2;
    Beh7984A_ActorEntry *entry;

    sub140 = arg0->unk140;
    sub_unk0 = sub140->unk0;
    sub_unk4 = sub140->unk4;
    sub_unk8 = sub140->unk8;
    sub_unkC = sub140->unkC;
    i = 0;
    if (D_807FBB34 > 0) {
        entry = D_807FB930;
        do {
            D_807FB620 = NULL;
            D_807FB624 = NULL;
            D_807FB628 = 0;
            actor = entry->actor;
            s0 = 0;
            if (actor->unk114 != NULL && (actor_sub140 = actor->unk140, (actor->unk60 & 0x40) && func_80679010(actor, arg0))) {
                s0 = 1;
            }
            if ((arg0->unk60 & 0x80) && func_80679010(arg0, actor)) {
                s0 = 1;
            }
            if ((actor->unk60 & 0x2000) == 0 &&
                actor_sub140 != sub140 &&
                actor->unk144 != 1 &&
                (actor->unk60 & 0x10) &&
                s0 == 0 &&
                func_80674ADC(sub_unk0, sub_unk4, sub_unk8, sub_unkC,
                              actor_sub140->unk0, actor_sub140->unk4, actor_sub140->unk8, actor_sub140->unkC)) {
                func_80671880(arg0, 0);
                func_80671880(actor, 0);
                var_s4 = 1;
                node1 = sub140->unk8C;
                if (node1 != NULL) {
                    while (node1->unk26 != 0 && (node1->unk27 & 8) == 0) {
                        node2 = actor_sub140->unk8C;
                        var_s2 = 1;
                        if (node2 != NULL) {
                            while (node2->unk26 != 0 && (node2->unk27 & 8) == 0) {
                                if (func_80674ADC(node1->unk10, node1->unk14, node1->unk18, node1->unk1C,
                                                  node2->unk10, node2->unk14, node2->unk18, node2->unk1C)) {
                                    mask1 = ~node1->unk24;
                                    mask2 = ~node2->unk24;
                                    if ((mask1 & actor->unk5C) && (mask2 & arg0->unk5C)) {
                                        dist = func_80675234(sub_unk0, sub_unk4, sub_unk8,
                                                             node2->unk10, node2->unk14, node2->unk18, node2->unk1C);
                                        func_80675180((void *)actor_sub140, arg0->unk7C, arg0->unk80, arg0->unk84, (void *)node2,
                                                      &sp70, &sp6C, &sp68);
                                        func_806752D4(arg0->unk54, dist, sp70, sp6C, sp68, var_s4, var_s2);
                                    }
                                }
                                node2 = node2->next;
                                var_s2++;
                                if (node2 == NULL) break;
                            }
                        }
                        node1 = node1->next;
                        var_s4++;
                        if (node1 == NULL) break;
                    }
                }
            }
            if (D_807FB620 != NULL) {
                func_80675380((s32)arg0, actor);
            }
            i++;
            entry++;
        } while (i < D_807FBB34);
    }
}
