// func_8065F1C0 (src/global/63EC0.c): near-miss: exact length and 0x78 frame, $s7/$s8 and $s1/$s2 induction pointer swaps
typedef struct R1B63810_Target {
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
} R1B63810_Target;

typedef struct R1B63810_Node {
    R1B63810_Target *target;
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
    struct R1B63810_Node *next;
} R1B63810_Node;

typedef struct R1B63810_Struct_AA0 {
    void (*func)(u8);
    u8 pad4[0x10];
    u8 unk14;
    u8 pad15[3];
} R1B63810_Struct_AA0;

extern R1B63810_Struct_AA0 D_80748A90[];
extern R1B63810_Struct_AA0 D_80748B68[];
extern R1B63810_Node *D_807F93C0;
extern s8 D_807F93C4;
extern s32 D_8076A0A8;

void *func_80610FE8(s32);
void func_80660D38(void *, void *);
void func_80660520(void *, void *);

void func_8065F1C0(void *arg0) {
    u8 pad[0x28];
    Table *entry = (Table *)D_80748A90;
    s32 i;
    Target *var_s6;
    Target *var_s2;
    Node **var_fp;
    u8 count;
    s32 sp4C;

    do {
        entry++;
        entry[-1].unk14 = 0;
    } while (entry < (Table *)D_80748B68);

    var_fp = &D_807F93C0;
    D_807F93C0 = NULL;
    count = *(u8 *)((u8 *)arg0 + *(s32 *)((u8 *)arg0 + 0x4C) + 3);
    D_807F93C4 = 0;

    if (count == 0) {
        return;
    }

    var_s6 = (Target *)((u8 *)arg0 + *(s32 *)((u8 *)arg0 + 0x4C) + 4);
    var_s2 = var_s6;
    sp4C = (s32)count;
    for (i = 0; i < sp4C; i++, var_s6++, var_s2++) {
        Node *node = func_80610FE8(sizeof(Node));
        s32 temp_s3;
        s32 temp_s4;
        s32 temp_s1;
        u8 temp_a0;
        Table *entry2;

        *var_fp = node;
        node->target = (Target *)var_s6;
        node->unk4 = 0.0f;
        node->unkC = 0.0f;
        node->unk8 = 0.0f;
        node->unk30 = 0;
        node->unk34 = 0;
        node->unk38 = 0;
        node->unk3C = 0;
        node->unk4A = 0;
        node->unk4B = 0;
        node->unk2C = var_s2->unk44;
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
        node->vtx[1] = func_80610FE8(temp_s1 << 3);

        temp_a0 = var_s2->unk66;
        entry2 = (Table *)&D_80748A90[temp_a0];
        if (entry2->unk14 == 0) {
            entry2->func(temp_a0);
            entry2->unk14 = 1;
        }
        node->next = NULL;
    }
}
