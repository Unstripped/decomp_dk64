// func_8069E774 (src/global/A2F10.c): stage 3/4 — 506 vs 503 insns, frame 0x90 matches, callee-saved set matches, whole function instruction-for-instruction aligned except: (1) stack slots sp60->0x60 (ours 0x6C), sp50->0x50 (ours 0x4C), sp48->0x48 (ours 0x64): target lays out sp60 then three unused 4-byte locals (0x5C,0x58,0x54), sp50, one more (0x4C), sp48; our declaration order after sp74 needs padding locals to reproduce it; (2) lightAdd argument setup order: target loads unk7C/unk80/unk84 + the zero args first and computes the node->unk0 product last, ours computes it first; (3) `if (unk168 == unk154)` must be written `if (unk154 == unk168)` (target loads lh 0x168 before lbu 0x154); (4) 3 extra insns come from the lightAdd region; also unk11C temp/`id` locals add slots. unkC conv is u16 (unsigned int conv).
typedef struct A2R2Node {
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
} A2R2Node;

typedef struct A2R2ActorEntry {
    /* 0x000 */ u8 pad0[4];
    /* 0x004 */ Actor *actor;
    /* 0x008 */ u8 pad8[0x2E8];
} A2R2ActorEntry;

typedef struct A2R2ActorS16 {
    /* 0x000 */ u8 pad0[0xEE];
    /* 0x0EE */ s16 unkEE;
} A2R2ActorS16;

typedef struct A2R2ActorF64 {
    /* 0x000 */ u8 pad0[0x160];
    /* 0x160 */ f64 unk160;
} A2R2ActorF64;

extern u8 D_80750AB8;
extern s32 D_8076A0A8;
extern u8 D_807FC928;
extern A2R2ActorEntry *D_807FC924;

void animSetLoopLimit(void *, s32, s32);
void animSetSpeed(void *, s32, f32);
void animSetFinished(void *, s32, s32);
s32 animIsPlaying(void *, s32, s32);
s32 func_80613448(Actor *);
s32 func_8061CB50(void);
void func_8061F0B0(void *, s32, s32);
f32 func_80612794(s16);
void func_8066EB40(void *, f32);
void func_806EB0C0(s16, Actor *, s32);
s32 func_80714608(s32);
void actorAppendModelNode(Actor *, f32, f32, f32, f32, s32);
void actorGetOrSetNodeScale(void *, s32, f32);
void actorOrNodeFlags(void *, s32, s32);
void actorDespawn(Actor *);
void func_806319C4(void *, s32);
void lightSetFlags(s32);
void lightAdd(f32, f32, f32, f32, f32, f32, f32, s32, s32, s32, s32);

void func_8069E774(void) {
    u16 sp8E;
    f32 sp88;
    u8 sp87;
    A2R2Node *sp80;
    u8 sp7F;
    Actor *sp78;
    u32 *sp74;
    A2R2Node *node;
    s32 sp60;
    A2R2ActorEntry *sp50;
    f32 sp48;
    Actor *temp_v0;
    s32 id;
    s32 i;
    Actor *target;

    sp8E = 0x12C;
    sp87 = 0;
    sp7F = 0;
    temp_v0 = (Actor *)D_807FBB40->unk11C;
    node = (A2R2Node *)D_807FBB40->unk174;
    if (temp_v0 != NULL && (temp_v0->unk5C & 1)) {
        sp78 = temp_v0;
        sp7F = 1;
    } else {
        sp78 = D_807FBB4C;
    }
    sp80 = (A2R2Node *)sp78->unk174;
    if (D_807FC928 >= 2 && D_80750AB8 == 1) {
        sp74 = &((A2R2Node *)D_807FBB4C->unk174)->unk1F0;
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
        switch (func_80613448(D_807FBB40)) {
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
    if (func_8061CB50() != 0) {
        func_8061F0B0(sp80->unk104, 0xA, 0xA);
    }
    D_807FBB40->unk4->unk34 =
        D_807FBB40->unk4->unk34 * ((A2R2ActorF64 *)D_807FBB40)->unk160;
    D_807FBB40->unk4->unk3C = D_807FBB40->unk4->unk34;
    D_807FBB40->unk4->unk38 = D_807FBB40->unk4->unk38 * 1.04;
    D_807FBB40->unk4->unk38 = D_807FBB40->unk4->unk38 +
                              0.01 * (f64)func_80612794(((A2R2ActorS16 *)D_807FBB40)->unkEE);
    ((A2R2ActorS16 *)D_807FBB40)->unkEE += 0x1F4;
    D_807FBB40->unkE6 += 0x32;
    D_807FBB40->unk154++;
    if (D_807FBB40->unk168 == D_807FBB40->unk154) {
        animSetFinished(D_807FBB40, 0, 0);
    } else if (D_807FBB40->unk168 < D_807FBB40->unk154) {
        sp8E = 0x12C - (D_807FBB40->unk154 - D_807FBB40->unk168) * 0x28;
        if (animIsPlaying(D_807FBB40, 0, 0) == 0) {
            sp87 = 1;
            *sp74 &= 0xFDFFFFFF;
            func_8066EB40(sp78, (f32)node->unkC);
            actorGetOrSetNodeScale(sp78, func_8069E724(sp78->unk58), 0.0f);
            actorDespawn(D_807FBB40);
        }
    }
    lightSetFlags(1);
    sp48 = (f32)sp8E;
    lightAdd(D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84, 0.0f,
             0.0f, 0.0f, D_807FBB40->unk4->unk34 * sp48 * node->unk0, 0,
             node->unk10, node->unk11, node->unk12);
    if (D_8076A0A8 != 0x4C) {
        if (sp7F == 0 || D_807FBB40->unk15F != 0) {
            sp60 = 0x2E;
            if (func_80714608(0) != 0) {
                sp60 = 0xE;
            }
            sp88 = D_807FBB40->unk4->unk34 * sp48;
            sp88 = sp88 * sp88;
            for (i = 0; i < D_807FC928; i++) {
                sp50 = &D_807FC924[i];
                target = sp50->actor;
                if (sp7F == 0 ||
                    (i != sp80->unk1A4 && target->unk154 != 0x84)) {
                    if (func_8069E660(target, (f32)target->unk15E, sp88) !=
                        0) {
                        func_806EB0C0(sp60, D_807FBB40, i & 0xFF);
                    }
                }
            }
            if (D_807FBB40->unk15F != 0) {
                func_8066EB40(
                    D_807FBB40,
                    (f32)(2.0 * ((f64)(D_807FBB40->unk4->unk34 * sp48) *
                                 6.66666667)));
                actorGetOrSetNodeScale(
                    D_807FBB40, 1,
                    (f32)((f64)(D_807FBB40->unk4->unk34 * sp48) *
                          6.66666667));
            }
        } else if (sp87 == 0) {
            func_8066EB40((Actor *)D_807FBB40->unk11C,
                          (f32)(2.0 * ((f64)(D_807FBB40->unk4->unk34 * sp48) *
                                       6.66666667)));
            actorGetOrSetNodeScale(
                (Actor *)D_807FBB40->unk11C, func_8069E724(sp78->unk58),
                (f32)((f64)(D_807FBB40->unk4->unk34 * sp48) * 6.66666667));
            actorOrNodeFlags(sp78, func_8069E724(sp78->unk58), 3);
        }
    }
    func_806319C4(D_807FBB40, 0);
}
