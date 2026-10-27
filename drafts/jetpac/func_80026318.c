// func_80026318 (src/jetpac/1460.c): Stage 6 (parked NON_MATCHING in J0a2/1460.c): same size (457 insns), frame 0x58, same regs; ~42 opcode diffs: target keeps arg0->unk30 in v0 reloaded at every path end (lw v0,0x30(s0) in delay slots) where C reloads once at the join; mtc1 zero hoist placement. Ledge fields must be read as (u8*)&D_8002EC30+idx*0x34+0x370/0x378 and D_8002EF84[idx*13] (extra &D_8002EC30 uses stop lda promotion so the prologue matches). Locals declared sp54,mx,my,vx,vy,a2,a1,px,sp34,sp30,idx give the frame slots.
typedef struct {
    f32 x;
    f32 y;
    f32 unk8;
    f32 unkC;
    u8 pad10[8];
    s32 unk18;
    s32 unk1C;
    s32 unk20;
    s32 unk24;
    s32 unk28;
    u8 pad2C[4];
    s32 unk30;
    s32 unk34;
    s32 unk38;
} J0a2Actor;

typedef struct {
    u8 pad0[4];
    f32 unk4;
    u8 pad8[0x18];
    s32 unk20;
    u8 pad24[4];
    s32 unk28;
    u8 pad2C[8];
} J0a2Ledge;

typedef struct {
    u8 pad0[0xC];
    s32 unkC;
} J0a2Player;

#define J0a2A ((J0a2Actor *)arg0)
#define J0a2Flags (*(u32 *)&D_8002EC30)
extern J0a2Ledge D_8002EF80[];
extern f32 D_8002EF84[];
extern s32 D_8002EF74;
void func_800260DC();
s32 jetpacCheckLedgeCollision(f32, f32, f32, f32, s32);
s32 func_80028E04(s32, s32, s32);
s32 func_80027330(f32);
void func_80024F9C(s32);

void func_80026318(JetpacActor *arg0) {
    J0a2Player *sp54;
    f32 mx;
    f32 my;
    f32 vx;
    f32 vy;
    s32 a2;
    s32 a1;
    f32 px;
    s32 sp34;
    s32 sp30;
    s32 idx;

    sp54 = (J0a2Player *)&D_8002EC30.sessions[D_8002EF74].data;
    sp34 = J0a2Flags & 0x200;
    sp30 = J0a2Flags & 0x100;
    a2 = J0a2Flags & 0x8000;
    a1 = J0a2Flags & 0x2030;
    if ((J0a2Flags & 0x4000) && J0a2A->unk38 >= 5) {
        func_800260DC(arg0, a1, a2);
        J0a2A->unk38 = 0;
    } else if (J0a2A->unk38 < 5) {
        J0a2A->unk38++;
    }
    if (a2 != 0 && (J0a2A->unk30 == 0 || a1 == 0)) {
        func_80025BB8(arg0, 1);
        J0a2A->unkC -= 0.2f;
    } else if (J0a2A->unk30 != 0) {
        if (a1 != 0) {
            J0a2A->unkC = 0.0f;
        } else {
            J0a2A->unkC += 0.2;
        }
    }
    if (sp34 != 0) {
        J0a2A->unk8 -= 0.33333334f;
        if (J0a2A->unk18 == 0 && J0a2A->unk8 <= 0.0f) {
            J0a2A->unk18 = 1;
            func_80025BB8(arg0, J0a2A->unk30);
        }
    } else if (sp30 != 0) {
        J0a2A->unk8 += 0.33333334f;
        if (J0a2A->unk18 != 0 && J0a2A->unk8 >= 0.0f) {
            J0a2A->unk18 = 0;
            func_80025BB8(arg0, J0a2A->unk30);
        }
    } else {
        vx = J0a2A->unk8;
        if (vx > 0.0f) {
            J0a2A->unk8 = vx - 0.16666667f;
        } else if (vx < 0.0f) {
            J0a2A->unk8 = vx + 0.16666667f;
        }
    }
    if (J0a2A->unk30 != 0) {
        mx = 2.0f;
        my = 2.0f;
    } else {
        mx = 1.0f;
        my = 0.0f;
    }
    vx = J0a2A->unk8;
    J0a2A->unk8 = (vx < -mx) ? -mx : ((mx < vx) ? mx : vx);
    vx = J0a2A->unkC;
    J0a2A->unkC = (vx < -my) ? -my : ((my < vx) ? my : vx);
    if (J0a2A->unk8 < 0.1 && J0a2A->unk8 > -0.1) {
        J0a2A->unk8 = 0.0f;
    }
    if (J0a2A->unkC < 0.1 && J0a2A->unkC > -0.1) {
        J0a2A->unkC = 0.0f;
    }
    vx = J0a2A->unk8;
    if (J0a2A->unk30 != 0) {
        idx = jetpacCheckLedgeCollision(J0a2A->unk1C + J0a2A->x + vx, J0a2A->unk20 + J0a2A->y + J0a2A->unkC,
                                        J0a2A->unk24 + J0a2A->x + vx, J0a2A->unk28 + J0a2A->y + J0a2A->unkC, 1);
        if (idx >= 0) {
            if ((f32)*(s32 *)((u8 *)&D_8002EC30 + idx * 0x34 + 0x378) <= J0a2A->unk20 + J0a2A->y) {
                J0a2A->unkC *= -0.4f;
                if ((J0a2A->unkC > 0.0f ? J0a2A->unkC : -J0a2A->unkC) <= 0.15f) {
                    J0a2A->unkC = 0.0f;
                }
            } else if (J0a2A->unk28 + J0a2A->y <= (f32)*(s32 *)((u8 *)&D_8002EC30 + idx * 0x34 + 0x370)) {
                J0a2A->unk34 = idx;
                J0a2A->unkC = 0.0f;
                func_80025BB8(arg0, 0);
                J0a2A->y = D_8002EF84[idx * 13] - 24.0f;
            } else {
                J0a2A->unk8 *= -0.5f;
            }
        }
    } else {
        idx = func_80028E04(J0a2A->unk34, (s32)(J0a2A->unk1C + J0a2A->x + vx), (s32)(J0a2A->unk24 + J0a2A->x + vx));
        switch (idx) {
        case -2:
        case 2:
            func_80025BB8(arg0, 1);
            J0a2A->unkC = -0.5f;
            break;
        case -1:
        case 1:
            if (J0a2A->unk18 == 0 && sp34 == 0) {
                J0a2A->unk8 = 1.0f;
            } else if (sp30 == 0) {
                J0a2A->unk8 = -1.0f;
            }
            break;
        }
    }
    J0a2A->x = J0a2A->x + J0a2A->unk8;
    if (J0a2A->x + J0a2A->unk24 > 256.0f) {
        J0a2A->x -= 256.0f;
    }
    if (J0a2A->x + J0a2A->unk1C < 0.0f) {
        J0a2A->x += 256.0f;
    }
    J0a2A->y = J0a2A->y + J0a2A->unkC;
    if (J0a2A->y < 18.0f) {
        J0a2A->y = 18.0f;
        J0a2A->unkC = 0.0f;
    }
    if (J0a2A->y > 168.0f) {
        J0a2A->y = 168.0f;
    }
    if (func_80027330(J0a2A->x) != 0 && sp54->unkC == 8 && J0a2A->y > 152.0f) {
        func_80024F9C(4);
    }
}
