// jetpacBonusItemUpdate (src/jetpac/3480.c): stage 5: R13_sonnet_xhigh_5 (base 555ed2b6): no improvement, park unchanged (full=2 text=2 shape=2 n=314; only `li t5,2` stays in the unk1C-test block). Derived with an instrumented as1 (`.scratch/R13_sonnet_xhigh_5/x3/as1_dbg`: fprintf at the finder call 0x42a028 and at the new/old time compare, prints `FIND dst src idx` / `TIME dst src newD newS oldD oldS`; harness xb.py/dbg.py in that dir): (1) ring: the later code proves li is allocated AFTER J's `lw $12` and freed last (tail order [11,12,13] reproduces every later t3/t4/t5; an li allocated in the compare block would give li=$11 and rotate those); ugen cannot carry a ring temp across the J branch, so li lives in S in ugen's stream and ONLY as1 XBB can bring it into the compare block (no ugen/non-hoist route; hidden alloc/free pairs before the li cannot give arm=$11,J=$12,li=$13 either: FIFO appends frees at the tail). (2) li in J (record move 97->before bne/lw) is never hoisted: TIME dst=4 src=J newD=7 newS=5 oldD=7 oldS=5 -> sums equal -> rejected, because the real block scheduler (f_reschedule) counts the li as filling J's `li at -> bne` stall (J=5 with or without it); J would need a non-movable surplus filler. (3) li in any weight-7 block BEFORE J (guard region: record moves 97->60/61/80) IS hoisted into the compare block and gives full=0 n=314, so the route works exactly when the li sits in a J-class block; no C does that (value would cross the J branch in a ring register). (4) weight routine decoded (0x4295b0): per block in number order, over lower-numbered in-loop preds p, signed 32-bit: -3 if block postdominates p, else +1 if p has a successor outside the loop set, else +3; first value always taken when running min is the sentinel 1; stored as halfword; then copied to later blocks X with weight 0 where b dom X and X pdom b (so chains of pads copy, the -3 rule only hits joins). An unreachable Z block (alias/noop record after `b $65`, before `$33:`) has weight 1 and gives its successor 1-3=-2 -> 65534 (sorted last); deeper blocks wrap upward (65534+3 -> 1 -> 4 -> 7): S becomes 1, sorted BEFORE the compare block, so Z never helps. Window loop breaks at the first source with w(src)-w(dst) >= 6 even if not dominated; dominance and the 11-candidate counter come after. X (0x100003f0) is read once and never written (only reference). (5) every spelling of the J test (ternary with redundant else store, `if (!=) {} else {}`, switch) compiles to the same natural stream (uopt dordstore removes the redundant store); constant-variable forms (`c = 2` at several places, `| 0`, dead `if (c) {}`) are copy-propagated back to li in S; lim as a local before a guard becomes a coloured web (full=105). Pair search of alias/noop/label probes over records 38-69 of the FAKE-free stream (4720 specs) finds nothing below full=2 (label before bge). X=2 as1 on the FAKE-free body gives full=15 (other hoists change), so the original is not a global window difference. Conclusion: the target needs an XBB move with weight diff 6 (S -> compare block) at window 6 where the census has no diff>=6 move; no loop (target has no backward branch, jump-table entries all forward), no C-reachable CFG change (pads only add same-weight blocks, arm->J edge would remove the arm's `b`) reaches it. | Prior: stage 5: R12_sonnet_xhigh_2 (base 685f6570): NEW best count-exact park full=2 text=2 reloc=0 shape=2 n=314 (was full=7), natural body with NO ghost const/candidate fakes: local `t = arg0->unk34` compare + early return, `if (arg0 && arg0 && arg0) {}` ONCE inside the timer arm and 8x before the `unk1C == 1` test (Q0548 pad route; <=7 pads or 0 arm guard keep n=315). The pass-through weight-7 guard blocks push the arm's `addiu t3,v0,1` past as1's ~10-candidate XBB limit, so it is no longer hoisted above slt (beqz delay slot = addiu like the target) and the arm guard's label block stops as1 copy-forwarding so `sw t3,52(s0)` uses s0. ONLY remaining diff: target `li t5,2` is before slt in the compare block, ours stays in the unk1C test block before `bnel`. Derived this session: (1) ring proof: ugen allocates the li AFTER the arm addu ($11) and `lw $12`, so the target li is an as1 hoist (a ucode constant in the compare block gets $9/$11, not $13). (2) the li can only leave its own store block S (li and its sw in one block): an li put in the test block J cannot hoist (its def is live into S, and it fills J's delay slot), verified with record edits. (3) XBB window: with the timer arm and the unk1C test both real decisions, dominance forces J=w(cmp)+3 and S=w(cmp)+6, and the window test is w(src)-w(dst) < 6 (X static never written), so S is never a source for the compare block in ANY C-reachable CFG: dead guards only add same-weight pass-through blocks, a Z block (record between the arm `b` and `$32:`) wraps weights 65534, an extra skip edge to J breaks dst dominance of S. Only an inner loop (back edge making {compare,J,S} a loop: weights 1,2,3) lowers the diff, and the target has no back edge. (4) exact stream on the FAKE-free body: label before the compare `bge` + li moved right before that label = full=0 n=314 byte-identical (label alone = full 2, li moved without label = full 4); probes noop/alias/loc/live there do not give the label effect; single/pair record-edit search over records 40-64 (label/alias/noop) finds nothing below 2. Remaining untried: a C form producing a real label between the compare loads and `bge`, or an inner-loop CFG that vanishes. | Prior: stage 5: verified two competing near-miss states: stage-3 best draft full=4 text=4 reloc=0 shape=3 n=315 (target registers v0/t2/t5/t3, but addiu t3,v0,1 hoisted before slt into lw t2 load stall, leaving beqz delay slot nop, li t5,2 in B3, and sw using a0) versus stage-5 count-exact source park full=7 text=7 reloc=0 shape=2 n=314 (instructions and branch delay slots identical to target with li a1,2 before slt and sw using s0, but uopt colours 2 into a1 yielding 7 register-name swaps a0/v0/a1/t2). Under as1 -xbbdbg 31 trace on draft t.G, moving li t5,2 before bge with a label gives full=0 n=314 byte-identical match; label alone gives full=2 n=314 (delay slots filled, s0 restored, only li t5,2 at line 70 vs 54). In as1's sorted destination loop, BB4 (timer compare, weight 4) visits before BB6 (unk1C test, weight 7); BB7 (unk1C=2, weight 10) is outside BB4's source window (w7-w4 = 6 not < 6). When BB6 is visited, li t5,2 hoists into BB6, but BB4 cannot re-hoist. Tested block-scoped variables, load-order variants, and evaluation sequences; none bridged the register-colouring vs hoist gap. Exact park retained in 3480.c; fdiff OK. | Prior: stage 3 best draft: full=4 text=4 reloc=0 shape=3 n=315 (one instruction long, cannot park); existing stage-5 count-exact source park retained full=7 n=314. Natural full=5 shrinks to 4 by if ((arg0 && arg0) && arg0) {} after early timer return, restoring s0 store base. Original as1 proof retained: moving li t5,2 and a label before bge in t.G matches full=0; label alone gives full=2 on natural body. Tried 62 control-flow/nested-if/goto/while-for-do forms, 85 zero-trip loop forms, 105 constant-2 variable and zero-dependency forms, 114 compound comparisons/boolean temporaries, 189 state-transition loops/switch/reversed-arm forms, 61 duplicate branch joins, 60 ternary operand merges, 42 one-iteration loop rotations, 428 typed-dead-read variants, 4708 const-2 ghost variants; none improve full=4. as1 scan --rounds2 and uopt level5 trace completed. Permuter -j2 --seconds600: 59269 iterations; best valid adds arg0 triple ghost. Count-exact permuter full=5 candidates are invalid (moved color store past break or early return into switch), rejected. No improved count-exact park; original park retained, do not merge private source. Matcher12 Base 146bc6700cea148e81fdf5a7c2577afd85345194: 107 fresh type/name variants (signed/unsigned state views; enum state; s8/u8/s16/u16 next-state narrowing and arithmetic; void/byte/word/const player-pointer views; parameter reuse; named timer/limit/item/index/base; existing v/v1/v34 reuse) give no improvement. Target lw/sw and slt prove word-sized state/timer loads and signed timer comparison; narrow state arithmetic retains extension/mask instructions. void/byte/word/const player views fold identically; repurposing arg0 as player pointer grows to n319 full121 on natural body. Current full-TU best still full4 text4 reloc0 shape3 n315, frame0x38, s0+ra; early increment store uses a0 rather than target s0. Existing count-exact park remains full7 text7 reloc0 shape2 n314. No merge. As1Group (base d495328bf722a26c83c592a497693f5a487e9132): applying the matched clamp/join-before-bge pattern with explicit v=2/inner->unk144 arms retains extra work (full=28/text=28/shape=8 n=317 versus source park full=7 n=314). Rejected; natural stage-3 best and count-exact source park retained. Catalogue: .scratch/as1group/catalogue.md. XbbModel 2026-11-06 (base b0c5bc32): the li t5,2 placement is most likely an as1 XBB hoist. ugen's FIFO ring emits li $13 in B4 (after B2' $11 and B3 $12), and the decoded XBB path only hoists from blocks at most one control level below the destination (weight window < 6, constant 1 at as1 0x100003f0). B4 is two levels below B2, and an li in B3 fills B3's delay slot, so nothing moves. Record edits that make B3 postdominate B2 or delete B3's branch move the li into B2: two sufficient routes under the model. One candidate C shape puts the unk1C test at the timer test's weight with no visible extra edge; routes outside the decoded paths (flags, liveness, alias) are not excluded. None found (goto L; L: does not survive uopt). Full rules: quirks.py get ido-backend-record-pipeline (as1 XBB source selection).
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
            if (arg0 && arg0 && arg0) {} // FAKE: pads as1 XBB source window
            arg0->unk34 = t + 1;
            return;
        }
    }
    if (arg0 && arg0 && arg0) {} // FAKE: pads as1 XBB source window
    if (arg0 && arg0 && arg0) {} // FAKE: pads as1 XBB source window
    if (arg0 && arg0 && arg0) {} // FAKE: pads as1 XBB source window
    if (arg0 && arg0 && arg0) {} // FAKE: pads as1 XBB source window
    if (arg0 && arg0 && arg0) {} // FAKE: pads as1 XBB source window
    if (arg0 && arg0 && arg0) {} // FAKE: pads as1 XBB source window
    if (arg0 && arg0 && arg0) {} // FAKE: pads as1 XBB source window
    if (arg0 && arg0 && arg0) {} // FAKE: pads as1 XBB source window
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
