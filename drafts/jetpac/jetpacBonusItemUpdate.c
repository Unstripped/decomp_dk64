// jetpacBonusItemUpdate (src/jetpac/3480.c): UNPARKED 2026-11-02: park was 289 insns vs target 288 (count-inexact parks stay drafts); stage 5 park: 36 text diff: li t5,2 placement and sw via a0 vs s0 at unk34+1 early return (+4 bytes / 1 insn), v0/v1 swap in switch cases 1/3/4 (target v0=inner->unk144 expression, v1=v; idx reuses v1). Tested flagSet narrow prototype (s16, u8, u8), item copy to local, dead tests with constant 2. Jet (leftovers5 w2): 30 spellings of the early-return unk34 increment and unk1C=2 test (no change), idx removed/merged into v, declaration orders, u8/u16/s16 idx and v types (idx u8/u16 -> 30 but 2 insns longer), 17k-compile dead-test/self-assign hill-climb (best 33 only via an extra dead load: not kept).
void jetpacBonusItemUpdate(JetpacItem *arg0) {
    JetpacPlayer *inner = &jetpacGame.players[jetpacGame.active_player];
    s32 v;
    s32 idx;
    f32 *new_var;
    f32 *new_var2;

    if (inner->unkC == 0) {
        return;
    }
    if (arg0->unk34 < inner->unk144) {
        arg0->unk34 = arg0->unk34 + 1;
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
        if (jetpacGame.unk78C == 2 && D_8002F064 == 3) {
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
        v = arg0->unk34 - inner->unk144;
        if (v >= 0x1C) {
            v -= 0x1C;
            arg0->unk34 = inner->unk144;
        }
        if (v < 0x1C) {
            idx = v / 4 + 1;
            if (idx & 1) {
                arg0->color[2] = 0xFF;
            } else {
                arg0->color[2] = 0;
            }
            if (idx & 2) {
                arg0->color[0] = 0xFF;
            } else {
                arg0->color[0] = 0;
            }
            if (idx & 4) {
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
        v = arg0->unk34 - inner->unk144;
        if (v >= 0x18) {
            v -= 0x18;
            arg0->unk34 = inner->unk144;
        }
        if (v < 12) {
            arg0->color[0] = 0;
            arg0->color[1] = 0;
            arg0->color[2] = 0;
        } else if (v < 24) {
            arg0->color[0] = 0;
            arg0->color[1] = 0xFF;
            arg0->color[2] = 0xFF;
        }
        break;
    }
}
