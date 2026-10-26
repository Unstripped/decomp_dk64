// func_80610044 (src/global/14CF0.c): from .scratch/SmallC/func_80610044_best.c
typedef struct { u32 unk0[24]; } SmallCMsg;
extern s8 D_80744460;
extern u8 D_807444FC;
extern u8 D_807F059C[];
extern void *D_807F0570[];
extern void *D_807F0588[];
extern s32 D_807F05A4;
extern s32 D_807F0984;
extern u8 D_807F05A8[];
extern u8 D_80744470[];
extern u8 D_805FB000[];
extern u8 D_805FB0D0[];
extern u8 D_8076AF20[];
extern u8 D_8076B320[];
extern OSMesgQueue D_807659E8;
extern u8 D_80767CD8[];
extern u8 D_80767CE8[];
extern OSMesgQueue gScheduler;
void func_80610044(void *arg0, s32 arg1, s32 arg2, u8 arg3, s32 arg4, u8 arg5) {
    SmallCMsg *msg;
    s32 size;
    arg2 &= 0xFF;
    if (D_80744460 != 0) return;
    msg = (SmallCMsg *)(D_807F05A8 + arg2 * 0xC0 + D_807444FC * 0x60);
    D_807F059C[arg2] = 1;
    msg->unk0[4] = 1; msg->unk0[5] = 0; msg->unk0[6] = (u32)D_805FB000;
    msg->unk0[7] = D_805FB0D0 - D_805FB000;
    msg->unk0[8] = (u32)D_807F0570[arg2]; msg->unk0[9] = 0x1000; msg->unk0[10] = (u32)D_807F0588[arg2];
    msg->unk0[11] = 0x800; msg->unk0[12] = (u32)D_8076AF20; msg->unk0[13] = 0x400;
    msg->unk0[14] = D_807F05A4; msg->unk0[15] = D_807F05A4 + D_807F0984; msg->unk0[16] = (u32)arg0;
    msg->unk0[17] = arg1 * 8; msg->unk0[18] = (u32)D_8076B320; msg->unk0[19] = 0xC00; msg->unk0[0] = 0;
    msg->unk0[21] = (u32)&D_807659E8; msg->unk0[22] = (arg2 << 16) | arg4; msg->unk0[2] = arg3 ? 0x43 : 3;
    msg->unk0[20] = (u32)D_80767CD8; msg->unk0[3] = *(u32 *)(D_80744470 + D_807444FC * 4);
    if (arg5) osWritebackDCacheAll(); else { size = arg1 * 8; osWritebackDCache(msg, 0x60); osWritebackDCache(arg0, size); osWritebackDCache(D_80767CE8 + D_807444FC * 0x11B0, 0x11B0); }
    osSendMesg(&gScheduler, msg, 1);
}
