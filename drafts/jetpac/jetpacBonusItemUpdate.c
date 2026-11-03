// jetpacBonusItemUpdate (src/jetpac/3480.c): W3Mid: t1 form (s32 t = arg0->unk34 var, 'arg0->unk34 = t + 1', NO dead tests) gives full=5 text=5 but count 315 vs 314 (as1 hoists addiu into stall slot, beqzl+copy instead of beqz/addiu + li hoist): t/unk144 colours match target (v0 / ring t2). Any boundary dead test on unk144 makes unk144 a v0 cand (full 104+); 140 dead-test singles, 3 hill-climbs, d/t/td/dt local variants tried. Count-exact park stays full=7 in src.
void jetpacBonusItemUpdate(JetpacItem *arg0) {
    JetpacPlayer *inner = &jetpacGame.players[jetpacGame.active_player];
    s32 v;
    s32 v1;
    s32 v34;
    f32 *new_var;
    s32 t;
    s32 d;
    f32 *new_var2;

    if (inner->unkC == 0) {
        return;
    }
    t = arg0->unk34;
    if (t < inner->unk144) {
        arg0->unk34 = t + 1;
        return;
    }
    if (arg0->unk1C == 1) {
        arg0->unk1C = 2;
    }
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
