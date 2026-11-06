// R11_jetpacBonusItemUpdate (base 9d6acd9dc66f1deacad36794631e27332c87412b): verified two competing near-miss states: stage-3 best draft full=4 text=4 reloc=0 shape=3 n=315 (target registers v0/t2/t5/t3, but addiu t3,v0,1 hoisted before slt into lw t2 load stall, leaving beqz delay slot nop, li t5,2 in B3, and sw using a0) versus stage-5 count-exact source park full=7 text=7 reloc=0 shape=2 n=314 (instructions and branch delay slots identical to target with li a1,2 before slt and sw using s0, but uopt colours 2 into a1 yielding 7 register-name swaps a0/v0/a1/t2). Under as1 -xbbdbg 31 trace on draft t.G, moving li t5,2 before bge with a label gives full=0 n=314 byte-identical match; label alone gives full=2 n=314 (delay slots filled, s0 restored, only li t5,2 at line 70 vs 54). In as1's sorted destination loop, BB4 (timer compare, weight 4) visits before BB6 (unk1C test, weight 7); BB7 (unk1C=2, weight 10) is outside BB4's source window (w7-w4 = 6 not < 6). When BB6 is visited, li t5,2 hoists into BB6, but BB4 cannot re-hoist. Tested block-scoped variables, load-order variants, and evaluation sequences; none bridged the register-colouring vs hoist gap. Exact park retained in 3480.c; fdiff OK.
// jetpacBonusItemUpdate (src/jetpac/3480.c): stage 3 best draft: full=4 text=4 reloc=0 shape=3 n=315 (one instruction long, cannot park); existing stage-5 count-exact source park retained full=7 n=314. Natural full=5 shrinks to 4 by if ((arg0 && arg0) && arg0) {} after early timer return, restoring s0 store base. Original as1 proof retained: moving li t5,2 and a label before bge in t.G matches full=0; label alone gives full=2 on natural body. Tried 62 control-flow/nested-if/goto/while-for-do forms, 85 zero-trip loop forms, 105 constant-2 variable and zero-dependency forms, 114 compound comparisons/boolean temporaries, 189 state-transition loops/switch/reversed-arm forms, 61 duplicate branch joins, 60 ternary operand merges, 42 one-iteration loop rotations, 428 typed-dead-read variants, 4708 const-2 ghost variants; none improve full=4. as1 scan --rounds2 and uopt level5 trace completed. Permuter -j2 --seconds600: 59269 iterations; best valid adds arg0 triple ghost. Count-exact permuter full=5 candidates are invalid (moved color store past break or early return into switch), rejected. No improved count-exact park; original park retained, do not merge private source. Matcher12 Base 146bc6700cea148e81fdf5a7c2577afd85345194: 107 fresh type/name variants (signed/unsigned state views; enum state; s8/u8/s16/u16 next-state narrowing and arithmetic; void/byte/word/const player-pointer views; parameter reuse; named timer/limit/item/index/base; existing v/v1/v34 reuse) give no improvement. Target lw/sw and slt prove word-sized state/timer loads and signed timer comparison; narrow state arithmetic retains extension/mask instructions. void/byte/word/const player views fold identically; repurposing arg0 as player pointer grows to n319 full121 on natural body. Current full-TU best still full4 text4 reloc0 shape3 n315, frame0x38, s0+ra; early increment store uses a0 rather than target s0. Existing count-exact park remains full7 text7 reloc0 shape2 n314. No merge.
// As1Group (base d495328bf722a26c83c592a497693f5a487e9132): applying the matched clamp/join-before-bge pattern with explicit v=2/inner->unk144 arms retains extra work (full=28/text=28/shape=8 n=317 versus source park full=7 n=314). Rejected; natural stage-3 best and count-exact source park retained. Catalogue: .scratch/as1group/catalogue.md.
// XbbModel 2026-11-06 (base b0c5bc32): the li t5,2 placement is most likely an as1 XBB hoist. ugen's FIFO ring emits li $13 in B4 (after B2' $11 and B3 $12), and the decoded XBB path only hoists from blocks at most one control level below the destination (weight window < 6, constant 1 at as1 0x100003f0). B4 is two levels below B2, and an li in B3 fills B3's delay slot, so nothing moves. Record edits that make B3 postdominate B2 or delete B3's branch move the li into B2: two sufficient routes under the model. One candidate C shape puts the unk1C test at the timer test's weight with no visible extra edge; routes outside the decoded paths (flags, liveness, alias) are not excluded. None found (goto L; L: does not survive uopt). Full rules: quirks.py get ido-backend-record-pipeline (as1 XBB source selection).
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
    {
        s32 t = arg0->unk34;
        if (t < inner->unk144) {
            arg0->unk34 = t + 1;
            return;
        }
    }
    if ((arg0 && arg0) && arg0) {} // FAKE: keeps the item pointer in s0 on the early-out path
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
