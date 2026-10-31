// func_80674B90 (src/global/79890.c): func_80674B90 (src/global/79890.c): stage 5, frame 0xC8 + control flow OK, stack offsets match (0x8f/0xc4/0xa0/0x74); remaining: foundCb=1 store uses s5 (target li t2,1 late), t-scratch renumbering, blez/blezl and move s2 position after cb->count load; parked NON_MATCHING
typedef struct KaN5_Node {
    u8 pad0[0x10];
    s32 unk10;
    s32 unk14;
    s32 unk18;
    s32 unk1C;
    u8 pad20[8];
    struct KaN5_Node *next;
} KaN5_Node;

typedef struct KaN5_Sub140 {
    u8 pad0[0x8C];
    KaN5_Node *unk8C;
} KaN5_Sub140;

typedef struct KaN5_Elem {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    s32 unk10;
    s32 unk14;
    s32 unk18;
} KaN5_Elem;

typedef struct KaN5_Callback {
    s32 type;
    u8 pad4[4];
    void *actor;
    s32 count;
    KaN5_Elem *elems;
    struct KaN5_Callback *next;
} KaN5_Callback;

typedef struct KaN5_Actor {
    u8 pad0[0x64];
    u32 unk64;
    u8 pad68[0x14];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
    u8 pad88[0x6C];
    s16 unkF4;
    s16 unkF6;
    u8 padF8[4];
    u8 unkFC;
    u8 unkFD;
    u8 padFE[0x3E];
    KaN5_Callback *unk13C;
    KaN5_Sub140 *unk140;
} KaN5_Actor;

extern u8 D_807FB606;
s32 actorTableContains(void *);
void actorUpdateCollisionSpheres(void *, s32);
s32 func_80674ADC(s32, s32, s32, s32, s32, s32, s32, s32);
void func_80675478();
void func_806755A8();

u8 func_80674B90(KaN5_Actor *arg0, KaN5_Actor *arg1, f32 *arg2, f32 *arg3) {
    KaN5_Callback *cb;
    f32 posX_f;
    f32 posY_f;
    f32 posZ_f;
    s32 posX;
    s32 posY;
    s32 posZ;
    KaN5_Elem *elem;
    KaN5_Node *node;
    KaN5_Sub140 *sub140;
    s32 i;
    s32 j;
    f32 elemX_f;
    s32 pad2[1];
    u8 foundCb;
    u8 matched;

    cb = arg0->unk13C;
    matched = 0;
    foundCb = 0;
    D_807FB606 = 0;
    sub140 = arg0->unk140;
    actorUpdateCollisionSpheres(arg0, 1);
    if (!actorTableContains(arg1)) {
        return 0;
    }

    posX_f = arg1->unk7C;
    posY_f = arg1->unk80;
    posZ_f = arg1->unk84;

    if (cb != NULL) {
        do {
            if (cb->type == 0x8000 && cb->actor == arg1) {
                elem = cb->elems;
                foundCb = 1;
                for (j = 0; j < cb->count; j++, elem++) {
                    elemX_f = elem->unk0;
                    node = sub140->unk8C;
                    for (i = elem->unk14 - 1; i != 0; i--) {
                        node = node->next;
                    }
                    if (func_80674ADC((s32)(posX_f * 8.0f), (s32)(posY_f * 8.0f), (s32)(posZ_f * 8.0f), (s32)(elemX_f * 8.0f),
                                      node->unk10, node->unk14, node->unk18, node->unk1C)) {
                        matched = 1;
                        func_80675478(arg0, elem, arg2, arg3);
                    }
                    func_806755A8((s32)(posX_f * 8.0f), (s32)(posZ_f * 8.0f), node->unk10, node->unk18, (s32)&arg1->unkF4, (s32)&arg1->unkF6);
                    arg1->unkFC = 1;
                    arg1->unkFD = 1;
                }
            }
            cb = cb->next;
        } while (cb != NULL && !foundCb);
    }

    if (D_807FB606 != 0) {
        arg1->unk64 |= 0x100;
    }
    return matched;
}
