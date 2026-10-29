// func_80674B90 (src/global/79890.c): from .scratch/Beh7984A/func_80674B90_best.c
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
    u8 pad0[0x8C];
    Beh7984A_Node *unk8C;
} Beh7984A_Sub140;

typedef struct Beh7984A_Elem {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    s32 unk10;
    s32 unk14;
    s32 unk18;
} Beh7984A_Elem;

typedef struct Beh7984A_Callback {
    s32 type;
    u8 pad4[4];
    void *actor;
    s32 count;
    Beh7984A_Elem *elems;
    struct Beh7984A_Callback *next;
} Beh7984A_Callback;

typedef struct Beh7984A_Actor {
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
    Beh7984A_Callback *unk13C;
    Beh7984A_Sub140 *unk140;
} Beh7984A_Actor;

extern u8 D_807FB606;
s32 actorTableContains(void *);
void actorUpdateCollisionSpheres(void *, s32);
s32 func_80674ADC(s32, s32, s32, s32, s32, s32, s32, s32);
void func_80675478(void *, void *, f32 *, f32 *);
void func_806755A8(s32, s32, s32, s32, s32, s32);

u8 func_80674B90(Beh7984A_Actor *arg0, Beh7984A_Actor *arg1, f32 *arg2, f32 *arg3) {
    Beh7984A_Callback *cb;
    Beh7984A_Sub140 *sub140;
    u8 pad;
    u8 foundCb;
    u8 matched;
    s32 pad2[2];
    s16 *anglePitch;
    Beh7984A_Elem *elem;
    Beh7984A_Node *node;
    s32 i;
    s32 j;
    f32 posX_f;
    f32 posY_f;
    f32 posZ_f;
    s32 posZ;
    s32 posX;
    s32 posY;
    s16 *angleYaw;

    matched = 0;
    foundCb = 0;
    D_807FB606 = 0;
    cb = arg0->unk13C;
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
                if (cb->count > 0) {
                    anglePitch = &arg1->unkF6;
                    angleYaw = &arg1->unkF4;
                    posX = (s32)(posX_f * 8.0f);
                    posY = (s32)(posY_f * 8.0f);
                    posZ = (s32)(posZ_f * 8.0f);
                    for (j = 0; j < cb->count; j++, elem++) {
                        node = sub140->unk8C;
                        for (i = elem->unk14 - 1; i != 0; i--) {
                            node = node->next;
                        }
                        if (func_80674ADC(posX, posY, posZ, (s32)(elem->unk0 * 8.0f),
                                          node->unk10, node->unk14, node->unk18, node->unk1C)) {
                            matched = 1;
                            func_80675478(arg0, elem, arg2, arg3);
                        }
                        func_806755A8(posX, posZ, node->unk10, node->unk18, (s32)angleYaw, (s32)anglePitch);
                        arg1->unkFC = 1;
                        arg1->unkFD = 1;
                    }
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
