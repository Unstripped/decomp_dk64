// func_8065F1C0 (src/global/63EC0.c): stage 5: frame 0x78 exact (pad[0x14], s32 count as loop limit gives bne + sw 0x4c); remaining ~13 lines: s7/s8 swap (var_fp vs const 1), lui/addiu order D_80748B68 before A90 in first loop, lui v1 D_8076A0A8/li hoist vs z/unk4D stores order. Wins: 2nd vtx alloc arg as temp_s1 * 8 (first << 3) stops CSE move s1,a0; unk2C store right after target store
typedef struct EffAF1C0Sub {
    u8 pad0[0xC];
    f32 unkC;
    f32 unk10;
    u8 pad14[0x30];
    s16 unk44;
    s16 unk46;
    s16 unk48;
    s16 unk4A;
    s16 unk4C;
    s16 unk4E;
    s16 unk50[11];
    u8 unk66;
    u8 unk67;
    u8 unk68;
    u8 pad69[3];
} EffAF1C0Sub;

typedef struct EffAF1C0Node {
    EffAF1C0Sub *target;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 x;
    f32 y;
    f32 z;
    void *dl[2];
    void *vtx[2];
    s16 unk2C;
    u8 pad2E[2];
    s32 unk30;
    s32 unk34;
    s32 unk38;
    s32 unk3C;
    s16 unk40;
    s16 unk42;
    s16 unk44;
    s16 unk46;
    s16 unk48;
    u8 unk4A;
    u8 unk4B;
    u8 unk4C;
    u8 unk4D;
    u8 pad4E[2];
    struct EffAF1C0Node *next;
} EffAF1C0Node;

typedef struct EffAF1C0Entry {
    void (*func)(u8);
    u8 pad4[0x10];
    u8 unk14;
    u8 pad15[3];
} EffAF1C0Entry;

extern s32 D_80748B68;
extern s32 D_8076A0A8;

void *func_80610FE8(s32);
void func_80660D38(void *, void *);
void func_80660520(void *, void *);

void func_8065F1C0(u8 *arg0) {
    u8 pad[0x14];
    EffAF1C0Entry *entry = (EffAF1C0Entry *)D_80748A90;
    s32 i;
    EffAF1C0Sub *var_s6;
    EffAF1C0Sub *var_s2;
    EffAF1C0Node **var_fp;
    s32 count;

    do {
        entry++;
        entry[-1].unk14 = 0;
    } while (entry < (EffAF1C0Entry *)&D_80748B68);

    var_fp = (EffAF1C0Node **)&D_807F93C0;
    D_807F93C0 = NULL;
    count = *(u8 *)(arg0 + *(s32 *)(arg0 + 0x4C) + 3);
    D_807F93C4 = 0;

    if (count == 0) {
        return;
    }

    var_s6 = (EffAF1C0Sub *)(arg0 + *(s32 *)(arg0 + 0x4C) + 4);
    var_s2 = var_s6;
    for (i = 0; i < count; i++, var_s6++, var_s2++) {
        EffAF1C0Node *node = func_80610FE8(0x54);
        s32 temp_s3;
        s32 temp_s4;
        s32 temp_s1;
        u8 temp_a0;
        EffAF1C0Entry *entry2;

        *var_fp = node;
        node->target = var_s6;
        node->unk2C = var_s2->unk44;
        node->unk4 = 0.0f;
        node->unkC = 0.0f;
        node->unk8 = 0.0f;
        node->unk30 = 0;
        node->unk34 = 0;
        node->unk38 = 0;
        node->unk3C = 0;
        node->unk4A = 0;
        node->unk4B = 0;
        node->x = var_s2->unkC;
        node->z = 0.0f;
        node->unk4D = 0;
        node->y = var_s2->unk10;
        var_fp = &node->next;

        if (((D_8076A0A8 == 0x53) || (D_8076A0A8 == 0xC5)) && (i == 0)) {
            node->unk4D = 1;
        }

        temp_s3 = ((s32)(var_s2->unk4A - var_s2->unk46) / var_s2->unk44) + 1;
        temp_s4 = ((s32)(var_s2->unk4C - var_s2->unk48) / var_s2->unk44) + 1;
        node->unk48 = (temp_s3 + 1) * (temp_s4 + 1);

        node->dl[0] = func_80610FE8(node->unk48 * 0x10);
        func_80660D38(node->dl[0], node);
        func_80660520(node->dl[0], node);

        node->dl[1] = func_80610FE8(node->unk48 * 0x10);
        func_80660D38(node->dl[1], node);
        func_80660520(node->dl[1], node);

        temp_s1 = (temp_s3 * temp_s4) + (((temp_s3 / 16) + 1) * temp_s4 * 2);
        temp_s1 += 0xC8;
        node->vtx[0] = func_80610FE8(temp_s1 << 3);
        node->vtx[1] = func_80610FE8(temp_s1 * 8);

        temp_a0 = var_s2->unk66;
        entry2 = (EffAF1C0Entry *)D_80748A90 + temp_a0;
        if (entry2->unk14 == 0) {
            entry2->func(temp_a0);
            entry2->unk14 = 1;
        }
        node->next = NULL;
    }
}
