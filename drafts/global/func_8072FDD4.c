// func_8072FDD4 (src/global/133A90.c): float reg alloc only: 0.0 const f12/prev f2 vs target f2/f12; parked NON_MATCHING
typedef struct H1ProxSub {
    /* 0x00 */ u8 unk0;
    /* 0x01 */ u8 unk1;
    /* 0x02 */ u8 pad2[2];
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ s16 unk10;
    /* 0x12 */ s16 unk12;
    /* 0x14 */ s16 unk14;
    /* 0x16 */ s16 unk16;
    /* 0x18 */ u8 unk18;
    /* 0x19 */ u8 pad19[3];
} H1ProxSub; // size = 0x1C

typedef struct H1ProxNode {
    /* 0x00 */ Actor *unk0;
    /* 0x04 */ u8 unk4;
    /* 0x05 */ u8 unk5;
    /* 0x06 */ u8 unk6;
    /* 0x07 */ u8 unk7;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ u8 pad10[4];
    /* 0x14 */ f32 unk14;
    /* 0x18 */ u8 unk18;
    /* 0x19 */ u8 pad19[3];
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ f32 unk24;
    /* 0x28 */ f32 unk28;
    /* 0x2C */ f32 unk2C;
    /* 0x30 */ u8 unk30;
    /* 0x31 */ u8 unk31;
    /* 0x32 */ u8 pad32[2];
    /* 0x34 */ H1ProxSub *unk34;
    /* 0x38 */ struct H1ProxNode *next;
} H1ProxNode; // size = 0x3C

extern H1ProxNode *D_807FDCC0;

void func_8072FDD4(H1ProxNode *arg0, f32 arg1, u8 *arg2, f32 *arg3) {
    u8 i;
    f32 rem;
    f32 prev;
    H1ProxSub *sub;

    rem = arg1;
    i = 0;
    sub = arg0->unk34; do {
        prev = rem;
        rem -= sub[i++].unk4;
    } while (rem > 0.0 && i < arg0->unk7);
    i--;
    *arg2 = i;
    *arg3 = prev / arg0->unk34[i].unk4;
}
