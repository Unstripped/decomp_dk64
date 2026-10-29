// func_806794EC (src/global/7CA80.c): stage 5: frame 0x58, all 9 saved regs and 6 stack slots match, regalloc diff only (temp_a0 in v0 vs a0)

typedef struct KaL3_StructD580 {
    u8 pad0[0x6C];
    f32 unk6C;
    s16 unk70;
    u8 pad72[2];
    f32 unk74;
} KaL3_StructD580;
extern KaL3_StructD580 *D_807FD580;

extern u8 D_807FBC08[];
extern u8 D_807FBC14[];

void func_80675810(Actor *, ActorCallbackNode *);
void func_80679DC4(Actor *, Actor *, s32);
ActorCallbackNode *func_8067A09C(ActorCallbackNode *);
s32 actorCheckPointInAngleArc(Actor *, f32, f32);

typedef struct KaL3_SubF8 {
    u8 unk0[0xC];
    u8 unkC[0x24];
    s32 unk30;
    s32 unk34;
    s32 unk38;
    Actor *unk3C;
} KaL3_SubF8;

typedef struct KaL3_ActorGlobalState {
    u8 unk0;
    u8 unk1;
    u8 unk2;
    u8 pad3;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    s16 unk10;
    s16 unk12;
    u8 unk14;
    u8 unk15;
    u8 unk16;
    u8 unk17;
    u8 unk18;
    u8 unk19;
    u8 unk1A;
    u8 unk1B;
    u8 unk1C;
    u8 pad1D[3];
    Actor *unk20;
    u8 unk24;
    u8 unk25;
    u8 pad26[2];
    Actor *unk28;
    u8 unk2C;
    u8 pad2D[3];
    f32 unk30;
    s16 unk34;
    s16 unk36;
    u8 unk38;
    u8 unk39;
    u8 pad3A[2];
    f32 unk3C[4][3];
    s32 unk6C[4];
    Actor *unk7C[4];
    u8 unk8C[4];
    u8 unk90;
    u8 unk91;
    s16 unk92;
    s16 unk94;
    u8 pad96[0x32];
    s32 unkC8;
    Actor *unkCC;
    s32 unkD0;
    s32 unkD4;
    f32 unkD8;
    f32 unkDC;
    f32 unkE0;
    u8 unkE4;
    u8 unkE5;
    u8 padE6[2];
    f32 unkE8;
    Actor *unkEC;
    f32 unkF0;
    f32 unkF4;
    KaL3_SubF8 unkF8[4];
    s32 unk1F8;
    Actor *unk1FC;
    u8 unk200;
    u8 unk201;
    u8 unk202[2];
    s32 unk204[16];
    u8 unk244[16];
    u8 unk254;
    u8 pad255[3];
    s32 unk258[8];
    void *unk278[8];
} KaL3_ActorGlobalState;

#define GSTATE (*(KaL3_ActorGlobalState *)&D_807FBB70)


typedef struct KaL3_Payload10000 {
    s16 unk0;
    s16 unk2;
    u8 unk4[0xC];
    u8 unk10[0x24];
    s32 unk34;
    s32 unk38;
    s32 unk3C;
} KaL3_Payload10000;

typedef struct ActorPlayerState {
    u8 pad0[0x1A];
    u16 unk1A;
} ActorPlayerState;

void func_806794EC(Actor *arg0) {
    s16 pad[2];
    s32 sp50;
    f32 sp4C;
    f32 sp48;
    f32 sp44;
    s32 sp40;
    s16 sp3E;
    s8 var_s7;
    u8 temp_v0_2;
    u8 temp_v1_2;
    u8 temp_v1_3;
    ActorPayloadA7EC *temp_s0;
    KaL3_SubF8 *temp_s0_2;
    KaL3_Payload10000 *temp_s0_3;
    ActorCallbackNode *temp_v0;
    f32 *temp_v0_10;
    ActorPayloadABC0 *temp_v0_11;
    ActorPlayerState *temp_v0_3;
    ActorPayloadAAB8 *temp_v0_4;
    ActorPayloadA69C *temp_v0_5;
    ActorPayloadA70C *temp_v0_6;
    f32 *temp_v0_7;
    ActorPayloadAAB8 *temp_v0_8;
    ActorSub140 *temp_v0_9;
    Actor *temp_v1;
    ActorCallbackNode *var_s2;

    var_s7 = -1;
    func_8067AC38();
    temp_v0 = func_8067A09C(arg0->unk13C);
    arg0->unk13C = temp_v0;
    var_s2 = temp_v0;
    sp50 = arg0->unk138;
    if (temp_v0 != NULL) {
        do {
            s32 temp_a0 = (s32)var_s2->callback;
            if (temp_a0 & sp50) {
                switch (temp_a0) {
                case 0x8000:
                    func_80675810(arg0, var_s2);
                    if (((GSTATE.unk200 == 9) || (GSTATE.unk200 == 0xA)) && (arg0->unk5C & 1)) {
                        func_80679DC4(arg0, GSTATE.unk1FC, (GSTATE.unk200 == 0xA) & 0xFF);
                    }
                    break;
                case 0x2:
                    temp_v0_2 = var_s2->unk4;
                    switch (temp_v0_2) {
                    case 0:
                        GSTATE.unk16 = 1;
                        if (arg0 == D_807FBB48) {
                            playerStateQueueCallback(0x10, NULL, D_807FC929);
                        }
                        break;
                    case 1:
                        GSTATE.unk17 = 1;
                        if (arg0 == D_807FBB48) {
                            playerStateQueueCallback(0xE, var_s2->unk8, D_807FC929);
                        }
                        break;
                    case 2:
                        GSTATE.unk18 = 1;
                        if (arg0 == D_807FBB48) {
                            playerStateQueueCallback(0x12, NULL, D_807FC929);
                        }
                        break;
                    case 3:
                        GSTATE.unk19 = 1;
                        if (arg0 == D_807FBB48) {
                            playerStateQueueCallback(0x13, NULL, D_807FC929);
                        }
                        break;
                    case 6:
                        GSTATE.unk1B = 1;
                        if (arg0 == D_807FBB48) {
                            playerStateQueueCallback(0x36, var_s2->unk8, D_807FC929);
                        }
                        break;
                    case 4:
                    case 5:
                        if (arg0 == D_807FBB48) {
                            if (temp_v0_2 == 4) {
                                playerStateQueueCallback(0x2B, var_s2->unk8, D_807FC929);
                            } else {
                                playerStateQueueCallback(0x32, var_s2->unk8, D_807FC929);
                            }
                            temp_v1 = (Actor *)var_s2->unk8;
                            if ((temp_v1 != NULL) && (temp_v1->unk5C & 2)) {
                                temp_v0_3 = (ActorPlayerState *)temp_v1->unk174;
                                temp_v0_3->unk1A = (u16)(temp_v0_3->unk1A | 0x100);
                            }
                        }
                        break;
                    }
                    break;
                case 0x8:
                    func_80679DC4(arg0, (Actor *)var_s2->unk8, 0);
                    break;
                case 0x4:
                    func_80679DC4(arg0, (Actor *)var_s2->unk8, 1 & 0xFF);
                    break;
                case 0x800:
                    arg0->unk144 = (u8)var_s2->unk4;
                    GSTATE.unk90 = 1;
                    break;
                case 0x400:
                    temp_v0_4 = (ActorPayloadAAB8 *)var_s2->unk10;
                    D_807FD580->unk70 = temp_v0_4->unk0;
                    D_807FD580->unk74 = temp_v0_4->unk4;
                    D_807FD580->unk6C = (f32)temp_v0_4->unk8;
                    GSTATE.unk1A = 1;
                    if (arg0 == D_807FBB48) {
                        playerStateQueueCallback(0x17, var_s2->unk8, D_807FC929);
                    }
                    break;
                case 0x10:
                    temp_v0_5 = (ActorPayloadA69C *)var_s2->unk10;
                    temp_v1_2 = temp_v0_5->unk8;
                    if (var_s7 < (s32)temp_v1_2) {
                        sp4C = temp_v0_5->unk0;
                        sp40 = temp_a0;
                        var_s7 = (s8)temp_v1_2;
                        sp44 = temp_v0_5->unk4;
                        *(u8 *)&sp3E = temp_v0_5->unk9;
                    }
                    break;
                case 0x20:
                    temp_v0_6 = (ActorPayloadA70C *)var_s2->unk10;
                    temp_v1_3 = temp_v0_6->unkC;
                    if (var_s7 < (s32)temp_v1_3) {
                        sp4C = temp_v0_6->unk0;
                        var_s7 = (s8)temp_v1_3;
                        sp48 = temp_v0_6->unk4;
                        sp40 = temp_a0;
                        sp44 = temp_v0_6->unk8;
                        *(u8 *)&sp3E = temp_v0_6->unkD;
                    }
                    break;
                case 0x100000:
                    temp_v0_7 = (f32 *)var_s2->unk10;
                    GSTATE.unkD8 = temp_v0_7[0];
                    GSTATE.unkDC = temp_v0_7[1];
                    GSTATE.unkE4 = 1;
                    GSTATE.unkE0 = temp_v0_7[2];
                    GSTATE.unkEC = (Actor *)var_s2->unk8;
                    break;
                case 0x1000:
                    GSTATE.unk1C = 1;
                    GSTATE.unk20 = (Actor *)var_s2->unk8;
                    break;
                case 0x4000:
                    temp_v0_8 = (ActorPayloadAAB8 *)var_s2->unk10;
                    GSTATE.unk2C = 1;
                    GSTATE.unk30 = temp_v0_8->unk4;
                    GSTATE.unk34 = temp_v0_8->unk8;
                    GSTATE.unk36 = temp_v0_8->unk0;
                    break;
                case 0x2000:
                    if (var_s2->unk4 != 0) {
                        GSTATE.unk24 = 1;
                    } else {
                        GSTATE.unk25 = 1;
                    }
                    GSTATE.unk28 = (Actor *)var_s2->unk8;
                    break;
                case 0x80:
                    arg0->unk60 = (s32)(arg0->unk60 | 8);
                    if (arg0 == D_807FBB48) {
                        playerStateQueueCallback(0x16, var_s2->unk8, D_807FC929);
                    }
                    break;
                case 0x40:
                    if (var_s2->unk4 != 0) {
                        arg0->unk60 = (s32)(arg0->unk60 | 4);
                    } else {
                        arg0->unk60 = (s32)(arg0->unk60 & ~4);
                    }
                    break;
                case 0x1:
                    temp_s0 = (ActorPayloadA7EC *)var_s2->unk10;
                    if (actorTableContains(var_s2->unk8) != 0 && GSTATE.unk39 != 4) {
                        GSTATE.unk3C[GSTATE.unk39][0] = temp_s0->unk0;
                        GSTATE.unk3C[GSTATE.unk39][1] = temp_s0->unk4;
                        GSTATE.unk3C[GSTATE.unk39][2] = temp_s0->unk8;
                        GSTATE.unk6C[GSTATE.unk39] = temp_s0->unkC;
                        GSTATE.unk7C[GSTATE.unk39] = (Actor *)var_s2->unk8;
                        GSTATE.unk8C[GSTATE.unk39] = temp_s0->unk10;
                        GSTATE.unk39++;
                        func_80678F9C(arg0, var_s2->unk8);
                    }
                    break;
                case 0x20000:
                    temp_s0_2 = (KaL3_SubF8 *)var_s2->unk10;
                    if (GSTATE.unk1F8 != 4) {
                        memcpy(&GSTATE.unkF8[GSTATE.unk1F8], temp_s0_2, 0xC);
                        memcpy(GSTATE.unkF8[GSTATE.unk1F8].unkC, temp_s0_2->unkC, 0x24);
                        GSTATE.unkF8[GSTATE.unk1F8].unk30 = temp_s0_2->unk30;
                        GSTATE.unkF8[GSTATE.unk1F8].unk34 = temp_s0_2->unk34;
                        GSTATE.unkF8[GSTATE.unk1F8].unk38 = temp_s0_2->unk38;
                        GSTATE.unkF8[GSTATE.unk1F8].unk3C = (Actor *)var_s2->unk8;
                        GSTATE.unk1F8++;
                    }
                    break;
                case 0x10000:
                    temp_s0_3 = (KaL3_Payload10000 *)var_s2->unk10;
                    GSTATE.unk91 = 1;
                    GSTATE.unk92 = temp_s0_3->unk0;
                    GSTATE.unk94 = temp_s0_3->unk2;
                    memcpy(D_807FBC08, temp_s0_3->unk4, 0xC);
                    memcpy(D_807FBC14, temp_s0_3->unk10, 0x24);
                    GSTATE.unkC8 = temp_s0_3->unk34;
                    GSTATE.unkCC = (Actor *)var_s2->unk8;
                    GSTATE.unkD0 = temp_s0_3->unk38;
                    GSTATE.unkD4 = temp_s0_3->unk3C;
                    break;
                case 0x40000:
                    temp_s0 = var_s2->unk10;
                    temp_v0_9 = arg0->unk140;
                    if (temp_v0_9 != NULL) {
                        temp_v0_9->unk68 = *(s32 *)temp_s0;
                    }
                    break;
                case 0x80000:
                    GSTATE.unk38 = 1;
                    break;
                case 0x200000:
                    temp_v0_10 = (f32 *)var_s2->unk10;
                    GSTATE.unkF0 = temp_v0_10[0];
                    GSTATE.unkF4 = temp_v0_10[1];
                    break;
                case 0x400000:
                    GSTATE.unkE8 = (f32)(u32)var_s2->unk4;
                    GSTATE.unkE5 = 1;
                    break;
                case 0x1000000:
                    if (GSTATE.unk254 < 8) {
                        GSTATE.unk258[GSTATE.unk254] = var_s2->unk4;
                        GSTATE.unk278[GSTATE.unk254] = var_s2->unk10;
                        GSTATE.unk254++;
                    }
                    break;
                case 0x800000:
                    temp_v0_11 = (ActorPayloadABC0 *)var_s2->unk10;
                    GSTATE.unk4 = temp_v0_11->unk0;
                    GSTATE.unk8 = temp_v0_11->unk4;
                    GSTATE.unkC = temp_v0_11->unk8;
                    GSTATE.unk10 = temp_v0_11->unkC;
                    GSTATE.unk12 = temp_v0_11->unkE;
                    GSTATE.unk2 = 1;
                    GSTATE.unk14 = var_s2->unk4;
                    break;
                case 0x2000000:
                    GSTATE.unk0 = 1;
                    GSTATE.unk1 = var_s2->unk4;
                    break;
                }
            }
            var_s2 = var_s2->next;
        } while (var_s2 != NULL);
    }
    if ((var_s7 != -1) && ((*(u8 *)&sp3E == 1) || (actorCheckPointInAngleArc(arg0, sp4C, sp44) != 0))) {
        switch (sp40) {
        case 16:
            arg0->unk7C = sp4C;
            arg0->unk84 = sp44;
            return;
        case 32:
            arg0->unk7C = sp4C;
            arg0->unk80 = sp48;
            arg0->unk84 = sp44;
            break;
        }
    }
}
