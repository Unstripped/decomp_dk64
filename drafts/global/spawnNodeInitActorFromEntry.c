// spawnNodeInitActorFromEntry (src/global/1295B0.c): Stage 5: 398/398 insns, frame 0x40 exact; fixed extra li a1,255 and reg swap by setting controllerLookupStateByHash to 1 arg, fixed move a1,zero to li a1,0 with f32 proto on actorUpdateFloorContactAndTilt; remaining diff is stack slot of entry/case6 v1 (0x20/0x28 vs 0x24)
typedef struct A4Act {
    /* 0x000 */ u8 pad0[4];
    /* 0x004 */ void *unk4;
    /* 0x008 */ u8 pad8[0x50];
    /* 0x058 */ s32 unk58;
    /* 0x05C */ u8 pad5C[4];
    /* 0x060 */ u32 unk60;
    /* 0x064 */ u8 pad64[4];
    /* 0x068 */ u16 unk68;
    /* 0x06A */ u16 unk6A;
    /* 0x06C */ u16 unk6C;
    /* 0x06E */ u8 pad6E[0xE];
    /* 0x07C */ f32 unk7C;
    /* 0x080 */ f32 unk80;
    /* 0x084 */ f32 unk84;
    /* 0x088 */ u8 pad88[0x1C];
    /* 0x0A4 */ f32 unkA4;
    /* 0x0A8 */ u8 padA8[0x1C];
    /* 0x0C4 */ f32 unkC4;
    /* 0x0C8 */ f32 unkC8;
    /* 0x0CC */ u8 padCC[0x12];
    /* 0x0DE */ s16 unkDE;
    /* 0x0E0 */ u8 padE0[6];
    /* 0x0E6 */ s16 unkE6;
    /* 0x0E8 */ u8 padE8[6];
    /* 0x0EE */ s16 unkEE;
    /* 0x0F0 */ u8 padF0[0x20];
    /* 0x110 */ u8 unk110;
    /* 0x111 */ u8 pad111[0x19];
    /* 0x12A */ s16 unk12A;
    /* 0x12C */ s16 unk12C;
    /* 0x12E */ u8 pad12E[2];
    /* 0x130 */ u8 unk130;
    /* 0x131 */ u8 unk131;
    /* 0x132 */ u8 pad132[0x12];
    /* 0x144 */ u8 unk144;
    /* 0x145 */ u8 pad145[0xF];
    /* 0x154 */ u8 unk154;
    /* 0x155 */ u8 unk155;
    /* 0x156 */ u8 pad156[0x14];
    /* 0x16A */ u8 unk16A;
    /* 0x16B */ u8 unk16B;
    /* 0x16C */ u8 unk16C;
    /* 0x16D */ u8 pad16D;
    /* 0x16E */ u8 unk16E;
    /* 0x16F */ u8 unk16F;
    /* 0x170 */ u8 pad170[4];
    /* 0x174 */ void *unk174;
    /* 0x178 */ u8 pad178[4];
    /* 0x17C */ s16 *unk17C;
} A4Act;

typedef struct A4Node {
    /* 0x00 */ u8 pad0[6];
    /* 0x06 */ s16 unk6;
    /* 0x08 */ u8 pad8[2];
    /* 0x0A */ u8 unkA;
    /* 0x0B */ u8 padB;
    /* 0x0C */ u8 unkC;
    /* 0x0D */ u8 unkD;
    /* 0x0E */ u8 padE;
    /* 0x0F */ u8 unkF;
    /* 0x10 */ u8 unk10;
    /* 0x11 */ u8 pad11[7];
    /* 0x18 */ A4Act *unk18;
    /* 0x1C */ u8 pad1C[0x10];
    /* 0x2C */ f32 unk2C;
    /* 0x30 */ f32 unk30;
    /* 0x34 */ f32 unk34;
    /* 0x38 */ f32 unk38;
    /* 0x3C */ u8 pad3C[4];
    /* 0x40 */ s16 unk40;
    /* 0x42 */ u8 unk42;
    /* 0x43 */ u8 unk43;
    /* 0x44 */ u8 unk44;
    /* 0x45 */ u8 pad45;
    /* 0x46 */ u16 unk46;
} A4Node;

typedef struct A4Entry {
    /* 0x00 */ u8 pad0[4];
    /* 0x04 */ s16 unk4;
    /* 0x06 */ u8 pad6[2];
    /* 0x08 */ u32 unk8;
    /* 0x0C */ u8 padC[2];
    /* 0x0E */ u8 unkE;
    /* 0x0F */ u8 unkF;
    /* 0x10 */ u8 unk10;
    /* 0x11 */ u8 unk11;
    /* 0x12 */ u8 unk12;
    /* 0x13 */ u8 unk13;
    /* 0x14 */ u8 unk14;
    /* 0x15 */ u8 unk15;
    /* 0x16 */ u8 unk16;
    /* 0x17 */ u8 unk17;
} A4Entry;

typedef struct A4Player {
    /* 0x000 */ u8 pad0[4];
    /* 0x004 */ void *unk4;
    /* 0x008 */ u8 pad8[0x2E8];
} A4Player;

typedef struct A4St174 {
    /* 0x00 */ A4Node *unk0;
    /* 0x04 */ void *unk4;
    /* 0x08 */ s16 unk8;
    /* 0x0A */ u8 padA[6];
    /* 0x10 */ s16 unk10;
    /* 0x12 */ s16 unk12;
    /* 0x14 */ s16 unk14;
    /* 0x16 */ u8 pad16[8];
    /* 0x1E */ u8 unk1E;
    /* 0x1F */ u8 unk1F;
    /* 0x20 */ u8 pad20;
    /* 0x21 */ u8 unk21;
    /* 0x22 */ u8 unk22;
    /* 0x23 */ u8 unk23;
    /* 0x24 */ u8 pad24;
    /* 0x25 */ u8 unk25;
    /* 0x26 */ u8 pad26[0xE];
    /* 0x34 */ u8 unk34;
    /* 0x35 */ u8 unk35;
    /* 0x36 */ u8 pad36;
    /* 0x37 */ u8 unk37;
} A4St174;

extern f32 D_807502E8;
extern s16 D_807502E0;
extern s16 D_8075570C[];
extern s32 D_807FBB68;
extern u8 gPlayerCount;
extern u8 D_80755698[];
extern s32 gCurrentMap;
void actorScriptStart(void *, s32);
s16 controllerLookupStateByHash(void *);
void actorUpdateFloorContactAndTilt(void *, f32);
void behaviourSetAnimIds(s16, s16, s16, s16);
void actorSetTargetSpeed(void *, u8);
s32 randomNonNegative(void);
#define A4P4 ((A4Player *)gPlayerSlots)

void spawnNodeInitActorFromEntry(void *arg0, void *arg1) {
    A4St174 *st;
    A4Node *node;
    s16 padA;
    s16 ang;
    A4Act *act;
    u8 type;
    s32 v;
    A4Entry *entry;
act = arg0;
    node = arg1;
    st = act->unk174;
    type = D_80755698[node->unk44];
    node->unk42 = 5;
    node->unk18 = act;
    node->unk30 = 1.0f;
    entry = (A4Entry *)&D_8075EB80[node->unk44];
    node->unk2C = 0.01f;
    if (entry->unk17 != 0) {
        node->unk38 = 1.0 / entry->unk17;
    } else {
        node->unk38 = 0.0f;
    }
    ang = entry->unk4;
    if (ang != 0) {
        actorScriptStart(act, ang);
    }
    D_807FDC98 = (Struct807FDC98 *)node;
    behaviourSetAnimIds(ang + 0, ang | 0, ang * 1, ang);
    if (act->unk4 != 0) {
        actorSetUniformScale((Actor *)act, ((node->unkF * 5) / 255.0) * 0.15);
    }
    actorSetPositionFromPoint((Actor *)act, (void *)node);
    act->unkDE = 0x400;
    act->unkC4 = D_807502E8;
    act->unkC8 = D_807502E0;
    act->unk12C = node->unk40;
    if (entry->unkE == 0) {
        act->unk12A = 0x7D0;
    }
    actorSetTargetSpeed(act, node->unkC);
    st->unk0 = node;
    v = act->unkE6;
    act->unkEE = v;
    st->unk25 = 0;
    st->unk34 = 0xFF;
    st->unk8 = v;
    st->unk10 = act->unk7C;
    st->unk12 = act->unk80;
    st->unk14 = act->unk84;
    act->unk144 = 0x24;
    act->unk60 &= 0xFFFEFFFF;
    act->unk60 |= 0x20000;
    act->unk60 |= entry->unk8;
    if (act->unk4 != 0) {
        act->unk68 |= 0xC0;
    }
    act->unk16E = entry->unk14;
    act->unk16F = entry->unk15;
    v = entry->unkF;
    st->unk22 = v;
    st->unk23 = v;
    st->unk1E = entry->unk10;
    st->unk1F = entry->unk11;
    st->unk21 = entry->unk12;
    st->unk35 = entry->unk13;
    st->unk37 = entry->unk16;
    act->unk154 = node->unk10;
    act->unk155 = 0;
    switch (type) {
        case 0:
        case 2:
        case 3:
            node->unk46 |= 0x4000;
        case 1:
            node->unk46 |= 8;
            break;
        case 10:
            node->unk46 |= 0x80;
            break;
        case 6:
            entry = (A4Entry *)act->unk17C;
            if (act->unk58 == 0xFE) {
                *(s16 *)entry = D_8075570C[node->unkA];
            } else {
                *(s16 *)entry = controllerLookupStateByHash(act);
            }
            break;
    }
    act->unk16A = 0xFF;
    act->unk16B = 0xFF;
    act->unk16C = 0xFF;
    switch (gCurrentMap) {
        case 0x4E:
        case 0x4F:
        case 0x83:
            v = node->unkD + (node->unk43 * 0xA);
            if (v >= 0x100) {
                node->unkD = 0xFF;
            } else {
                node->unkD = v;
            }
            break;
        case 0x53:
        case 0xC5:
            if (type == 6) {
        case 0x4C:
                act->unk130 = 0x3C;
                act->unk131 = 0x3C;
                act->unk154 = 0;
                act->unk155 = 0;
                act->unk144 = 1;
                act->unk60 |= 0x10000000;
        case 0x6:
        case 0xE:
        case 0x1B:
        case 0x1C:
        case 0x27:
        case 0x37:
        case 0x52:
        case 0x6A:
        case 0x98:
        case 0x99:
        case 0xAC:
        case 0xB9:
        case 0xD0:
                node->unk46 |= 0x20;
        case 0x3:
        case 0x43:
        case 0x44:
        case 0x4A:
        case 0xD1:
                act->unk60 |= 0x800000;
            }
            break;
        case 0x45:
            act->unk60 |= 0x800000;
        case 0x42:
        case 0x68:
        case 0x7C:
        case 0x88:
        case 0x89:
        case 0xA5:
            if (node->unk10 != 4) {
                st->unk37 = 7;
            }
            break;
        case 0xD4:
            act->unk12A = 0x7D0;
        case 0xD3:
            node->unk46 |= 4;
            break;
        case 0x50:
            act->unk60 &= 0xFEFFFFFF;
            break;
    }
    if (gPlayerCount >= 2) {
        st->unk4 = A4P4[(randomNonNegative() >> 0xF) % gPlayerCount].unk4;
    } else {
        st->unk4 = (void *)D_807FBB4C;
    }
    node->unk34 = 0.75f;
    act->unkA4 = node->unk6;
    if (type != 8) {
        actorUpdateFloorContactAndTilt(act, 0.0f);
        if (D_807FBB68 & 2) {
            act->unk110 = 0;
        } else if ((type == 4) || (act->unk58 == 0xF8)) {
            node->unk46 |= 0x800;
            act->unk110 = 0;
        } else if (act->unk110 == 1) {
            node->unk46 |= 0x200;
        }
    }
    if (type == 5) {
        ((A4Act *)D_807FBB40)->unk6A |= 4;
        ((A4Act *)D_807FBB40)->unk6C |= 4;
    }
}
