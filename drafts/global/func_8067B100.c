// func_8067B100 (src/global/7CA80.c): stage 5: 56 insns, frame 0, regalloc only (/ swap, / swap)
typedef struct KaA2_Actor174 {
    u8 pad0[0x1A4];
    u8 unk1A4;
} KaA2_Actor174;

typedef struct KaA2_Player {
    u8 pad0[4];
    Actor *actor;
    u8 pad8[0x294 - 0x8];
    s32 unk294;
    u16 *unk298;
    u8 pad29C[0x2C1 - 0x29C];
    u8 unk2C1;
    u8 pad2C2[0x2F0 - 0x2C2];
} KaA2_Player;

typedef struct KaA2_Sub950 {
    u8 pad[0x5E];
} KaA2_Sub950;

typedef struct KaA2_Array950 {
    KaA2_Sub950 sub[8];
    u8 pad[0x306 - 8 * 0x5E];
} KaA2_Array950;

typedef struct KaA2_5C414 {
    s32 unk0;
    u8 pad4[12];
} KaA2_5C414;

extern void *D_807FD580;
extern u8 D_8074E77C[];
extern KaA2_Array950 D_807FC950[];
extern void *D_807FD568;
extern s32 D_807ECDEC;
extern u16 D_807ECDF0;
extern KaA2_5C414 D_8075C414[];
extern s16 D_807FD584;

void func_8067B100(Actor *arg0) {
    s32 temp_v1;
    u8 temp_v0;
    KaA2_Player *player;

    D_807FD580 = arg0->unk174;
    D_807FC929 = ((KaA2_Actor174 *)D_807FD580)->unk1A4;
    temp_v1 = D_807FC929;
    temp_v0 = D_8074E77C[temp_v1];
    player = (KaA2_Player *)&D_807FC924[temp_v1];
    D_807FBB48 = player->actor;
    D_807FD568 = &D_807FC950[temp_v1].sub[temp_v0];
    D_807ECDEC = player->unk294;
    D_807ECDF0 = *player->unk298;
    D_807FD584 = D_8075C414[temp_v0].unk0;
    player->unk2C1 = 0;
}
