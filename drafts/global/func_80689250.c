// func_80689250 (src/global/8D3E0.c): Stage 4: frame 0x30, 4 insns diff on entry slot 0x1c vs 0x18
typedef struct KaE_R3D3B_Entry30 {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ s16 unk2;
    /* 0x04 */ char unk4[4];
    /* 0x08 */ s16 unk8;
    /* 0x0A */ char unkA[2];
    /* 0x0C */ s32 unkC;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ char unk14[0x1C];
} KaE_R3D3B_Entry30;
extern KaE_R3D3B_Entry30 D_8074E8B0[];

ActorListNode *func_80689250(s16 arg0, f32 arg1, f32 arg2, f32 arg3, s16 arg4, f32 arg5, void *arg6, u8 arg7, s32 arg8, s16 arg9) {
    ActorListNode *node;
    KaE_R3D3B_Entry30 *entry;
    s32 found;
    s32 i;

    found = 0;
    i = 0;
    do {
        if ((s16)(arg0 + 0x10) == D_8074E8B0[i].unk0) {
            found = 1;
        } else {
            i++;
        }
    } while (!found && i < 0x80);
    entry = &D_8074E8B0[i];

    node = func_80610FE8(sizeof(ActorListNode));
    node->unk00 = arg0;
    node->unk0C = arg3;
    node->unk18 = arg3;
    node->unk04 = arg1;
    node->unk10 = arg1;
    node->unk08 = arg2;
    node->unk14 = arg2;
    node->unk5A = arg9;
    node->unk1C = arg4;
    node->unk44 = 0;
    node->prev = NULL;
    node->unk48 = 0;
    node->unk20 = arg5;
    node->unk5C = entry->unkC;
    node->unk60 = entry->unk10;
    node->unk58 = entry->unk2;
    node->unk4A = func_806531B8(arg1, arg2, arg3, 0);
    node->unk4C = arg7;
    node->unk50 = arg8;
    node->unk54 = (f32)entry->unk8 * (f32)entry->unk8;

    for (i = 0; i < 8; i++) {
        ((f32 *)node->unk24)[i] = ((f32 *)arg6)[i];
    }

    node->next = D_807FC400;
    if (D_807FC400 != NULL) {
        D_807FC400->prev = node;
    }
    D_807FC400 = node;

    return node;
}
