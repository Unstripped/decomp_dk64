// func_80730408 (src/global/133A90.c): stage 4-5: pad2[4]->pad2[2] fixes frame to 0x288 (648) with the 133A90.c H1ActorB gaining ActorSub4 *unk4 at 4. Remaining: stack offset set differs only in 3 slots (target f64 temp@64, idx s32@72, f32 temp@208; mine idx@68, f64 temp@72, f32 temp@216) and idx v1 vs v0; 386 diff lines; decl adjacent swaps don't move it; permuter earlier best 1597 (stage 3 note kept in older draft).
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

typedef struct H1ActorState {
    /* 0x000 */ u8 pad0[0x130];
    /* 0x130 */ Actor *unk130;
    /* 0x134 */ u8 unk134;
    /* 0x135 */ u8 pad135[3];
    /* 0x138 */ f32 unk138;
    /* 0x13C */ f32 unk13C;
    /* 0x140 */ f32 unk140;
    /* 0x144 */ f32 unk144;
    /* 0x148 */ f32 unk148;
    /* 0x14C */ u8 pad14C[0x10];
    /* 0x15C */ u8 unk15C[0x40];
    /* 0x19C */ s16 unk19C;
    /* 0x19E */ s16 unk19E;
    /* 0x1A0 */ u8 pad1A0[4];
    /* 0x1A4 */ u8 unk1A4;
} H1ActorState;

typedef struct H1SlotEntry {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ u8 padC[8];
    /* 0x14 */ f32 unk14;
    /* 0x18 */ u8 pad18[0xC];
    /* 0x24 */ u32 *unk24;
    /* 0x28 */ u8 pad28[0x5C];
    /* 0x84 */ s16 unk84;
    /* 0x86 */ u8 pad86[0xA];
} H1SlotEntry; // size = 0x90

typedef struct H1ActorB {
    /* 0x000 */ u8 pad0[4];
    /* 0x004 */ ActorSub4 *unk4;
    /* 0x008 */ u8 pad8[4];
    /* 0x00C */ f32 unkC[4][4];
    /* 0x04C */ u8 pad4C[0xC];
    /* 0x058 */ s32 unk58;
    /* 0x05C */ u8 pad5C[8];
    /* 0x064 */ u32 unk64;
    /* 0x068 */ u8 pad68[2];
    /* 0x06A */ u16 unk6A;
    /* 0x06C */ u8 pad6C[0x10];
    /* 0x07C */ f32 unk7C;
    /* 0x080 */ f32 unk80;
    /* 0x084 */ f32 unk84;
    /* 0x088 */ u8 pad88[0x5E];
    /* 0x0E6 */ s16 unkE6;
    /* 0x0E8 */ s16 unkE8;
    /* 0x0EA */ u8 padEA[0x8A];
    /* 0x174 */ H1ActorState *unk174;
} H1ActorB;

extern H1SlotEntry *D_807F6000;
s32 hashTableLookup();

void func_80627B58(f32);
void func_80611A70(f32, f32, f32 *, f32 *);
f32 func_80611BB4(f32, f32);
void func_80730AEC(u8, f32, H1ProxNode *, f32 *, f32 *, f32 *);
void func_80730E18(Mtx *, Mtx *, f32, Mtx *);

void func_80730408(H1ActorB *arg0, H1ActorState *arg1, H1ProxNode *arg2, u8 arg3, f32 arg4) {
    f32 one;
    f32 pad1[20];
    f32 p2[3];
    f32 p1[3];
    f32 p0[3];
    f32 a;
    f32 b;
    s16 slot;
    s8 idx2;
    s32 w2;
    f32 m1[4][4];
    f32 m2[4][4];
    s32 gapw;
    f32 m3[4][4];
    f32 ox;
    f32 oy;
    f32 oz;
    f32 yaw;
    f32 pad2[2];
    Mtx mA;
    s32 idx;
    f32 savedScale;
    Mtx mB;
    Mtx mC;

    func_80627B58(0.5f);
    a = arg4 - 0.1;
    idx = (s8)arg3;
    if (a < 0.0) {
        a = a + 1.0;
        idx = (s8)(arg3 - 1);
        if (idx < 0) {
            a = 0.0f;
            idx = 0;
        }
    }
    func_80730AEC(idx, a, arg2, &p0[0], &p0[1], &p0[2]);
    one = 1.0f;
    b = arg4 + 0.1;
    idx2 = arg3;
    if (b > 1.0) {
        b = b - 1.0;
        if ((s8)(arg3 + 1) == arg2->unk7) {
            idx2 = arg2->unk7 - 1;
            b = 1.0f;
        }
    }
    func_80730AEC(idx2, b, arg2, &p1[0], &p1[1], &p1[2]);
    func_80730AEC(arg3, arg4, arg2, &p2[0], &p2[1], &p2[2]);
    savedScale = arg1->unk148;
    arg1->unk148 = one;
    arg0->unk7C = (p2[0] - arg1->unk13C) * arg1->unk148 + arg1->unk13C;
    arg0->unk80 = (p2[1] - arg1->unk140) * arg1->unk148 + arg1->unk140;
    arg0->unk84 = (p2[2] - arg1->unk144) * arg1->unk148 + arg1->unk144;
    func_80611A70(p0[0], p0[2], &p1[0], &p1[2]);
    yaw = func_80611BB4(p1[0] - p0[0], p1[2] - p0[2]) * 57.29577637f + 180.0f;
    guTranslateF(m1, 0.0f, arg1->unk148 * -80.0f, 0.0f);
    guScaleF(m2, arg0->unk4->unk34, arg0->unk4->unk38, arg0->unk4->unk3C);
    guMtxCatF(m1, m2, m1);
    guRotateF(m2, arg0->unkE6 / 4095.0 * 360.0, 0.0f, one, 0.0f);
    guMtxCatF(m1, m2, m1);
    guRotateF(m2, -90.0f, one, 0.0f, 0.0f);
    guMtxCatF(m1, m2, m1);
    guAlignF(m2, yaw, p1[0] - p0[0], p1[1] - p0[1], p1[2] - p0[2]);
    guMtxCatF(m1, m2, m1);
    guRotateF(m3, arg0->unkE6 / 4095.0 * 360.0, 0.0f, one, 0.0f);
    guMtxXFMF(m3, 0.0f, 0.0f, -((arg2->unk34[arg3].unk8 + (arg2->unk34[arg3].unkC - arg2->unk34[arg3].unk8) * arg4)) * arg1->unk148, &ox, &oy, &oz);
    guTranslateF(m2, ox, oy, oz);
    guMtxCatF(m1, m2, m1);
    guMtxCatF(m1, m2, m1);
    guTranslateF(m2, arg0->unk7C, arg0->unk80, arg0->unk84);
    guMtxCatF(m1, m2, arg0->unkC);
    arg1->unk148 = savedScale;
    if (savedScale < 1.0) {
        guMtxF2L((f32 (*)[4])arg1->unk15C, &mB);
        guMtxF2L(arg0->unkC, &mC);
        func_80730E18(&mB, &mC, 1.0 - arg1->unk148, &mA);
        guMtxL2F(arg0->unkC, &mA);
    }
    arg1->unk148 = arg1->unk148 + 0.1;
    if (arg1->unk148 > 1.0) {
        arg1->unk148 = one;
    }
    arg1->unk19C = (s16)((arg2->unk34[arg3].unk12 - arg2->unk34[arg3].unk10) * arg4 + arg2->unk34[arg3].unk10);
    arg1->unk19E = (s16)((arg2->unk34[arg3].unk16 - arg2->unk34[arg3].unk14) * arg4 + arg2->unk34[arg3].unk14);
    switch (arg2->unk4) {
    case 1:
    case 2:
        slot = hashTableLookup(arg2->unk0);
        arg1->unk19C = ((s32)(D_807F6000[slot].unk14 * 4096.0f / 360.0f) + arg1->unk19C) & 0xFFF;
        arg1->unk19E = ((s32)(D_807F6000[slot].unk14 * 4096.0f / 360.0f) + arg1->unk19E) & 0xFFF;
        break;
    case 0:
        arg1->unk19C = (arg1->unk19C + arg2->unk0->unkE6) & 0xFFF;
        arg1->unk19E = (arg1->unk19E + arg2->unk0->unkE6) & 0xFFF;
        break;
    }
}
