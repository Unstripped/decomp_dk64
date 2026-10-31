// func_8069E774 (src/global/A2F10.c): stage 4: frame 0x90 and sp60@0x60 / IV spill@0x50 / f32 spill@0x48 match (padB0/padB1 words, no sp50/sp48 locals, (f32)sp8E inline, temp_v0 reused for D_807FBB4C->unk174, if (unk154 == unk168), (s16)sp60 cast); remaining: sp7F load is CSE'd into the loop (target reloads lbu 0x7F per iteration, no spill at 0x4C), loop tail shape (target beql s0 +1 delay and v0 count web), FP reg numbering f4/f8, ring t-numbering; deadsweep best ~79
typedef struct QA2Node {
    /* 0x000 */ f32 unk0;
    /* 0x004 */ u8 pad4[8];
    /* 0x00C */ u16 unkC;
    /* 0x00E */ u8 padE[2];
    /* 0x010 */ u8 unk10;
    /* 0x011 */ u8 unk11;
    /* 0x012 */ u8 unk12;
    /* 0x013 */ u8 pad13[0xF1];
    /* 0x104 */ void *unk104;
    /* 0x108 */ u8 pad108[0x9C];
    /* 0x1A4 */ u8 unk1A4;
    /* 0x1A5 */ u8 pad1A5[0x4B];
    /* 0x1F0 */ u32 unk1F0;
} QA2Node;

typedef struct QA2ActorEntry {
    /* 0x000 */ u8 pad0[4];
    /* 0x004 */ Actor *actor;
    /* 0x008 */ u8 pad8[0x2E8];
} QA2ActorEntry;

typedef struct QA2ActorS16 {
    /* 0x000 */ u8 pad0[0xEE];
    /* 0x0EE */ s16 unkEE;
} QA2ActorS16;

typedef struct QA2ActorF64 {
    /* 0x000 */ u8 pad0[0x160];
    /* 0x160 */ f64 unk160;
} QA2ActorF64;

extern u8 D_80750AB8;
extern s32 D_8076A0A8;
extern u8 D_807FC928;
extern QA2ActorEntry *D_807FC924;

void animSetLoopLimit(void *, s32, s32);
void animSetSpeed(void *, s32, f32);
void animSetFinished(void *, s32, s32);
s32 animIsPlaying(void *, s32);
s32 controllerLookupStateByHash(Actor *);
s32 camIsCutsceneActive(void);
void camStartShake(void *, s32, s32);
f32 func_80612794(s16);
void actorSetCollisionRadius(Actor *, f32);
void playerStateQueueCallback(s32, void *, s32);
s32 func_80714608(s32);
void actorAppendModelNode(Actor *, f32, f32, f32, f32, s32);
void actorGetOrSetNodeScale(void *, s32, f32);
void actorOrNodeFlags(void *, s32, s32);
s32 actorDespawn(Actor *);
void actorUpdateModelMatrix(void *, s32);
void lightSetFlags(s32);
void lightAdd(f32, f32, f32, f32, f32, f32, f32, s32, u32, u32, u32);

void func_8069E774(void) {
    u16 sp8E;
    f32 sp88;
    u8 sp87;
    QA2Node *sp80;
    u8 sp7F;
    Actor *sp78;
    u32 *sp74;
    QA2Node *node;
    Actor *temp_v0;
    s32 padB0;
    s32 padB1;
    s32 sp60;
    s32 i;
    Actor *target;


    sp8E = 0x12C;
    sp87 = 0;
    sp7F = 0;
    temp_v0 = (Actor *)D_807FBB40->unk11C;
    node = (QA2Node *)D_807FBB40->unk174;
    if (temp_v0 != NULL && (temp_v0->unk5C & 1)) {
        sp78 = temp_v0;
        sp7F = 1;
    } else {
        sp78 = D_807FBB4C;
    }
    sp80 = (QA2Node *)sp78->unk174;
    if (D_807FC928 >= 2 && D_80750AB8 == 1) {
        temp_v0 = (Actor *)D_807FBB4C->unk174;
        sp74 = &((QA2Node *)temp_v0)->unk1F0;
    } else {
        sp74 = &sp80->unk1F0;
    }
    if (!(D_807FBB40->unk60 & 0x10)) {
        node->unkC = (u16)sp78->unk140->unk14;
        D_807FBB40->unk12A = 0x3E8;
        D_807FBB40->unk60 |= 0x400;
        animSetLoopLimit(D_807FBB40, 0, 1);
        animSetSpeed(D_807FBB40, 0, 1.0f);
        animSetFinished(D_807FBB40, 0, 1);
        *sp74 |= 0x02000000;
        D_807FBB40->unk60 |= 0x800000;
        D_807FBB40->unk16A = 0xFF;
        D_807FBB40->unk16B = 0xFF;
        D_807FBB40->unk16C = 0xFF;
        switch (controllerLookupStateByHash(D_807FBB40)) {
        case 0xAD:
            node->unk10 = 0xFF;
            node->unk11 = 0xFF;
            node->unk12 = 0x32;
            break;
        case 0xAE:
            node->unk10 = 0xFF;
            node->unk11 = 0x32;
            node->unk12 = 0x32;
            break;
        case 0xCF:
            node->unk10 = 0x32;
            node->unk11 = 0xFF;
            node->unk12 = 0x32;
            break;
        case 0xD0:
            node->unk10 = 0;
            node->unk11 = 0x96;
            node->unk12 = 0xFF;
            break;
        case 0xD1:
            node->unk10 = 0xCA;
            node->unk11 = 0x5B;
            node->unk12 = 0xFF;
            break;
        }
        if (sp7F != 0) {
            node->unk0 = 2.0f;
        } else {
            node->unk0 = 1.5f;
        }
        if (D_807FBB40->unk15F != 0) {
            actorAppendModelNode(D_807FBB40, 0.0f, 0.0f, 0.0f, 1.0f, 0);
        }
    }
    if (camIsCutsceneActive() != 0) {
        camStartShake(sp80->unk104, 0xA, 0xA);
    }
    D_807FBB40->unk4->unk34 =
        D_807FBB40->unk4->unk34 * ((QA2ActorF64 *)D_807FBB40)->unk160;
    D_807FBB40->unk4->unk3C = D_807FBB40->unk4->unk34;
    D_807FBB40->unk4->unk38 = D_807FBB40->unk4->unk38 * 1.04;
    D_807FBB40->unk4->unk38 = D_807FBB40->unk4->unk38 +
                              0.01 * (f64)func_80612794(((QA2ActorS16 *)D_807FBB40)->unkEE);
    ((QA2ActorS16 *)D_807FBB40)->unkEE += 0x1F4;
    D_807FBB40->unkE6 += 0x32;
    D_807FBB40->unk154++;
    if (D_807FBB40->unk154 == D_807FBB40->unk168) {
        animSetFinished(D_807FBB40, 0, 0);
    } else if (D_807FBB40->unk168 < D_807FBB40->unk154) {
        sp8E = 0x12C - (D_807FBB40->unk154 - D_807FBB40->unk168) * 0x28;
        if (animIsPlaying(D_807FBB40, 0) == 0) {
            sp87 = 1;
            *sp74 &= 0xFDFFFFFF;
            actorSetCollisionRadius(sp78, (f32)node->unkC);
            actorGetOrSetNodeScale(sp78, func_8069E724(sp78->unk58), 0.0f);
            actorDespawn(D_807FBB40);
        }
    }
    lightSetFlags(1);
    lightAdd(D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84, 0.0f,
             0.0f, 0.0f, D_807FBB40->unk4->unk34 * (f32)sp8E * node->unk0, 0,
             node->unk10, node->unk11, node->unk12);
    if (D_8076A0A8 != 0x4C) {
        if (sp7F == 0 || D_807FBB40->unk15F != 0) {
            sp60 = 0x2E;
            if (func_80714608(0) != 0) {
                sp60 = 0xE;
            }
            sp88 = D_807FBB40->unk4->unk34 * (f32)sp8E;
            sp88 = sp88 * sp88;
            for (i = 0; i < D_807FC928; i++) {
                target = D_807FC924[i].actor;
                if (sp7F == 0 ||
                    (i != sp80->unk1A4 && target->unk154 != 0x84)) {
                    if (actorIsTargetInRange(target, (f32)target->unk15E, sp88) !=
                        0) {
                        playerStateQueueCallback((s16)sp60, D_807FBB40, i & 0xFF);
                    }
                }
            }
            if (D_807FBB40->unk15F != 0) {
                actorSetCollisionRadius(
                    D_807FBB40,
                    (f32)(2.0 * ((f64)(D_807FBB40->unk4->unk34 * (f32)sp8E) *
                                 6.66666667)));
                actorGetOrSetNodeScale(
                    D_807FBB40, 1,
                    (f32)((f64)(D_807FBB40->unk4->unk34 * (f32)sp8E) *
                          6.66666667));
            }
        } else if (sp87 == 0) {
            actorSetCollisionRadius((Actor *)D_807FBB40->unk11C,
                          (f32)(2.0 * ((f64)(D_807FBB40->unk4->unk34 * (f32)sp8E) *
                                       6.66666667)));
            actorGetOrSetNodeScale(
                (Actor *)D_807FBB40->unk11C, func_8069E724(sp78->unk58),
                (f32)((f64)(D_807FBB40->unk4->unk34 * (f32)sp8E) * 6.66666667));
            actorOrNodeFlags(sp78, func_8069E724(sp78->unk58), 3);
        }
    }
    actorUpdateModelMatrix(D_807FBB40, 0);
}
