// jetpacBonusItemUpdate (src/jetpac/3480.c): OvlA (revisit 8): unchanged park full 7 (text 7, 314=314), stage 5. Re-derived: natural no-FAKE body (t = arg0->unk34 local, t < inner->unk144) is full 5 / 315 with ALL registers right; as1probe: only diffs = label record before the bge + the li t5,2 record in the compare block (both edited into t.G = exact 314). FAKE inner->unk144==2 gives both but uopt then colours hoisted li a1 / unk144 v0 / unk34 a0 (target v0, t2 ring, li t5 ring). 1300 dead const-2 tests never colour the li above t0; also tried: compare/arm forms x casts (1500), 6 local-temp forms x FAKE subsets, raw-offset unk144 reads, phantom 2nd param (+1 insn), #define inner (347), flagSet(s16,u8,u8) proto, 2 random dead-test hill-climbs from FAKE and natural bases (no gain). No C spelling found.
void flagSet(s32, s32, s32);
void jetpacSpawnBonusItem(JetpacPlayer *);
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
    if (inner->unk144 == 2) {} // FAKE: empty block boundary + const-2 web in the compare block (as1 delay slot / li hoist)
    if (arg0->unk34 < inner->unk144) {
        arg0->unk34 = arg0->unk34 + 1;
        return;
    }
    if (inner->unk4 && inner->unk4) {} // FAKE: steers uopt candidate priority
    if (arg0->unk1C == 1) {
        arg0->unk1C = 2;
    }
    if (inner->unk4) {} // FAKE: steers uopt candidate priority
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
        if (arg0->unk34 && arg0->unk34) {} // FAKE: raises the unk34 candidate priority (base address -> v1)
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
