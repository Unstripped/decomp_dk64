// jetpacBonusItemUpdate (src/jetpac/3480.c): JetBoss (leftovers6): stage 5/6, count EXACT 314/314, deadsweep full=7 text=7 shape=2 (was 36, count 315). KEY1 per-case s32 locals (v case6, v1 case1+idx, v34 case3/4). KEY2 dead test 'if (inner->unk144 == 2) {}' right before the early compare creates the as1 block boundary => beqz/addiu delay + sw via s0 + li hoisted into stall slot. KEY3 '== 2U' on the later unk78C compare splits the later const-2 web. Hill-climb (dead tests anywhere) found 4 fakes (2 inner->unk4 tests, 1 case3/4 'arg0->unk34 && arg0->unk34'). Remaining 7 lines: B1 colours ours v0=unk144 cand, a0=unk34 cand, a1=const2; target v0=unk34, t2=unk144 (ring), t5=li 2, t3=addiu (v1=jetpacGame base is already right).
s32 jetpacCheckLedgeCollision(f32, f32, f32, f32, s32);
extern s32 D_8002F064;
extern f32 jetpacPlayer;
extern f32 D_8002F054;
extern s32 D_8002F06C;
extern s32 D_8002F070;
extern s32 D_8002F074;
extern s32 D_8002F078;
void flagSet(s32, s32, s32);
void jetpacPlaySound(s32);
void jetpacBonusItemUpdate(JetpacItem *arg0) {
    JetpacPlayer *inner = &jetpacGame.players[jetpacGame.active_player];
    s32 v;
    s32 v1;
    s32 v34;
    f32 *new_var;
    f32 *new_var2;

    if (inner->unkC == 0) {
        return;
    }
    if (inner->unk144 == 2) {} // FAKE
    if (arg0->unk34 < inner->unk144) {
        arg0->unk34 = arg0->unk34 + 1;
        return;
    }
    if (inner->unk4 && inner->unk4) {} // FAKE
    if (arg0->unk1C == 1) {
        arg0->unk1C = 2;
    }
    if (inner->unk4) {} // FAKE
    new_var = &jetpacPlayer;
    new_var2 = &D_8002F054;
    if (arg0->unk38 == 0) {
        if (arg0->unk14 > 0.0f) {
            f32 x = arg0->unk8;
            s32 hit = jetpacCheckLedgeCollision((f32)arg0->unk24 + x + arg0->unk10, (f32)arg0->unk28 + arg0->unkC + arg0->unk14,
                                                (f32)arg0->unk2C + x + arg0->unk10, (f32)arg0->unk30 + arg0->unkC + arg0->unk14, 0);
            if (hit >= 0) {
                arg0->unkC = jetpacGame.ledges[hit].unk4 - 16.0f;
                arg0->unk14 = 0.0f;
            } else {
                arg0->unkC = arg0->unkC + arg0->unk14;
            }
        }
        if (jetpacGame.unk78C == 2U && D_8002F064 == 3) {
            if (jetpacCheckAabbOverlapWrapped(arg0->unk8 + (f32)arg0->unk24, arg0->unkC + (f32)arg0->unk28, arg0->unk8 + (f32)arg0->unk2C, arg0->unkC + (f32)arg0->unk30,
                              (*new_var) + (f32)D_8002F06C, (*new_var2) + (f32)D_8002F070, (*new_var) + (f32)D_8002F074,
                              (*new_var2) + (f32)D_8002F078)) {
                if (arg0->unk40 == 6) {
                    flagSet(0x62, 1, 2);
                }
                inner->unk4 += arg0->unk3C;
                jetpacPlaySound(3);
                jetpacSpawnBonusItem(inner);
                return;
            }
        }
    }

    switch (arg0->unk40) {
    case 6:
        arg0->unk34++;
        v = arg0->unk34 - inner->unk144;
        if (v >= 0x97) {
            jetpacSpawnBonusItem(inner);
            return;
        }
        v = v % 24;
        if (v < 12) {
            arg0->color[2] = 0xFF;
            arg0->color[0] = 0;
            arg0->color[1] = 0;
        } else if (v < 24) {
            arg0->color[0] = 0xFF;
            arg0->color[1] = 0xFF;
            arg0->color[2] = 0;
        }
        break;
    case 1:
        arg0->unk34++;
        v1 = arg0->unk34 - inner->unk144;
        if (v1 >= 0x1C) {
            v1 -= 0x1C;
            arg0->unk34 = inner->unk144;
        }
        if (v1 < 0x1C) {
            v1 = v1 / 4 + 1;
            if (v1 & 1) {
                arg0->color[2] = 0xFF;
            } else {
                arg0->color[2] = 0;
            }
            if (v1 & 2) {
                arg0->color[0] = 0xFF;
            } else {
                arg0->color[0] = 0;
            }
            if (v1 & 4) {
                arg0->color[1] = 0xFF;
            } else {
                arg0->color[1] = 0;
            }
        }
        break;
    case 2:
        arg0->color[0] = 0xFF;
        arg0->color[1] = 0xFF;
        arg0->color[2] = 0;
        break;
    case 5:
        arg0->color[1] = 0xFF;
        arg0->color[0] = 0;
        arg0->color[2] = 0;
        break;
    case 3:
    case 4:
        arg0->unk34++;
    if (arg0->unk34 && arg0->unk34) {} // FAKE
        v34 = arg0->unk34 - inner->unk144;
        if (v34 >= 0x18) {
            v34 -= 0x18;
            arg0->unk34 = inner->unk144;
        }
        if (v34 < 12) {
            arg0->color[0] = 0;
            arg0->color[1] = 0;
            arg0->color[2] = 0;
        } else if (v34 < 24) {
            arg0->color[0] = 0;
            arg0->color[1] = 0xFF;
            arg0->color[2] = 0xFF;
        }
        break;
    }
}
