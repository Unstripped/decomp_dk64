// func_8060A7C0 (src/global/F4C0.c): stage 4: behaviour recovered; 32-byte text deficit from register allocation and address formation
typedef struct { s16 unk0; u8 unk2; u8 unk3; s16 unk4; } SmallAActionEntry;
typedef struct { u8 unk0[0x5C]; u16 unk5C; } SmallAPlayerState;
typedef struct { u8 unk0[0x1A4]; u8 unk1A4; } SmallAContext;
typedef struct { u8 unk0[0x2C0]; u8 unk2C0; } SmallARaceInfo;
extern SmallAActionEntry D_80746340[];
extern s16 D_80745BDE[];
extern s32 D_8076A0A8;
extern SmallAPlayerState *D_807FBB40;
extern s32 D_807FC924;
extern SmallAContext *D_807FD580;
s16 func_8060A7C0(s16 arg0, void *arg1, s32 arg2) {
    s32 var_v0 = 0;
    s32 var_v1 = 0;
    SmallAActionEntry *var_a1 = D_80746340;
    do {
        if ((arg0 == var_a1->unk0) && ((arg2 & 0xFF) == var_a1->unk2)) var_v1 = 1;
        else { var_v0++; var_a1++; }
    } while ((var_v0 < 0xE) && (var_v1 == 0));
    if (var_v1 != 0) {
        if ((D_807FBB40->unk5C & 1) && (((SmallARaceInfo *)(D_807FC924 + D_807FD580->unk1A4 * 0x2F0))->unk2C0 == 2)) return 0x97;
        if (*((u16 *)((u8 *)arg1 + 0x6A)) & 4) return 0xA;
        if (D_80746340[var_v0].unk4 == 0) return D_80745BDE[D_8076A0A8];
        return D_80746340[var_v0].unk4;
    }
    return arg0;
}
