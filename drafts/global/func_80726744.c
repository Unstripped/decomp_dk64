// func_80726744 (src/global/1295B0.c): stage 5: instruction stream identical modulo regs/spill slots (norm diff 50 lines of 400; same size 21072, frame 0x40, both jump tables ok). Diffs: (1) func_8072B79C arg conversions: target = three parallel sll/sra from a3 + raw a3 as 4th arg, mine chains them (sra t1 reused); entry->unk4 expression args give parallel convs but raw arg lands in a0 not a3. (2) spill slots: target v1@0x20 ang@0x34(sh) t0@0x3c, mine v1@0x30 ang@0x2c t0@0x34 (ang is a named local here, target spill is a temp). (3) rodata literals relocate via .rodata (late_rodata) and jtbl_8075F6D0 via .rodata+0x50: reloc-only. Needs C1 types moved above func_80726744 (C1SpawnEntry/C1ActorView/C1Node extended, C1PlayerView, D_8076A0A8, D_80755698). permuter setup fails (late_rodata_alignment directive in .s).
typedef struct C1St174 {
    /* 0x00 */ C1Node *unk0;
    /* 0x04 */ C1ActorView *unk4;
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
} C1St174;

extern f32 D_807502E8;
extern s16 D_807502E0;
extern s16 D_8075570C[];
extern s32 D_807FBB68;
extern u8 D_807FC928;
void func_80614EBC(void *, s32);
s16 func_80613448(void *, s32);
void func_80665564(void *, s32);
void func_8072B79C(s16, s16, s16, s16);
void func_807266E8(void *, void *);
void func_8072B324(void *, u8);
s32 func_80611A44(void);

void func_80726744(void *arg0, void *arg1) {
    C1ActorView *act;
    C1Node *node;
    C1St174 *st;
    C1SpawnEntry *entry;
    u8 type;
    s16 ang;
    s32 v;

    act = arg0;
    node = arg1;
    st = act->unk174;
    type = D_80755698[node->unk44];
    node->unk42 = 5;
    node->unk18 = act;
    node->unk30 = 1.0f;
    entry = &D_8075EB80[node->unk44];
    node->unk2C = 0.01f;
    if (entry->unk17 != 0) {
        node->unk38 = 1.0 / entry->unk17;
    } else {
        node->unk38 = 0.0f;
    }
    ang = entry->unk4;
    if (ang != 0) {
        func_80614EBC(act, ang);
    }
    D_807FDC98 = (Struct807FDC98 *)node;
    func_8072B79C((s32)ang, (s32)ang, (s32)ang, ang);
    if (act->unk4 != 0) {
        func_807248B0((Actor *)act, ((node->unkF * 5) / 255.0) * 0.15);
    }
    func_807266E8(act, node);
    act->unkDE = 0x400;
    act->unkC4 = D_807502E8;
    act->unkC8 = D_807502E0;
    act->unk12C = node->unk40;
    if (entry->unkE == 0) {
        act->unk12A = 0x7D0;
    }
    func_8072B324(act, node->unkC);
    st->unk0 = node;
    act->unkEE = act->unkE6;
    st->unk25 = 0;
    st->unk34 = 0xFF;
    st->unk8 = act->unkE6;
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
    st->unk22 = entry->unkF;
    st->unk23 = entry->unkF;
    st->unk1E = entry->unk10;
    st->unk1F = entry->unk11;
    st->unk21 = entry->unk12;
    st->unk35 = entry->unk13;
    st->unk37 = entry->unk16;
    act->unk155 = 0;
    act->unk154 = node->unk10;
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
            if (act->unk58 == 0xFE) {
                *act->unk17C = D_8075570C[node->unkA];
            } else {
                *act->unk17C = func_80613448(act, 0xFF);
            }
            break;
    }
    act->unk16A = 0xFF;
    act->unk16B = 0xFF;
    act->unk16C = 0xFF;
    switch (D_8076A0A8) {
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
    if (D_807FC928 >= 2) {
        st->unk4 = C1PLAYERS[(func_80611A44() >> 0xF) % D_807FC928].unk4;
    } else {
        st->unk4 = (C1ActorView *)D_807FBB4C;
    }
    node->unk34 = 0.75f;
    act->unkA4 = node->unk6;
    if (type != 8) {
        func_80665564(act, 0);
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
        C1ACT40->unk6A |= 4;
        C1ACT40->unk6C |= 4;
    }
}
