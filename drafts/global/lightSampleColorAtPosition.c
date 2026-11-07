// lightSampleColorAtPosition (src/global/5E2F0.c): stage 6 (PARKED in .scratch/R13_opus_9/5E2F0.c, fdiff OK; count-exact 441, frame 136): full=7 text=5 reloc=2 shape=7 (R13_opus_9, base 36a04bc3). Exact remaining diff (objdump): dy's caller-save reload lwc1 $f14,100(sp) is emitted in the call-return block (with dx/dz) instead of the join block after div.s $f6,$f16,$f12, and as1 then fills bc1f's delay slot with mov.s $f12,$f0 instead of lui v1,%hi(D_807F7EC8). Fixes this round: (1) frame: 7 words above dz (s32 pad2 after i); the 'three' variable is not needed ('/ 3' gives the same s1 constant); (2) nx/ny stores: dead guards survive uopt (cfe puts a loc before the label, so uoptinput's empty-if removal never fires; ugen deletes them) and copypropagate's find_replacements refuses a var under a Umpy whose other operand is an isop (no_nested_ops): 'if ((nx * entry->unk1C) + (ny * entry->unk1C) + dz) {}' in the dot<0 block keeps nx/ny live -> stores kept, Mmt len 52; dz must stay in it (without dz: 434 insns); (3) colour order: the dx/dist and dy/dist temps must colour after dist (adj 15, bit 104) and before (f32)arg3 (adj 15, bit 210), i.e. adjsave exactly 15 = (30 in B + 3 propagated loads x10)/4 (10..13 live units+reaching): 'if (nx + ny + nx + ny + nx + ny) {}' at the end of the unk0<=dot block (any late position works; 1 or 2 copies give adj 10/13.3). Pads: 18..55 'if (1) {}' all give full=7 (16 breaks, 57+ breaks). DY ANALYSIS (uoptreg2.c): after a call, every caller-saved range holding the same candidate in the call block and its successor gets an rlod in the successor, so the target's join-only reload means dy's coloured piece excludes the call-return and then blocks (a split). A split piece entered by a reload pays movcost*freq (compute_save needreglod penalty), so a 1-ref piece nets 0 and is '-ve save'; the target's join piece needs >=2 refs. A cost split needs totalsave <= best register cost (caller-saved 20 = save+restore of one call in the loop; callee firstUseCost), impossible with dy's 3 refs in the call block (30+). needsplit (regsleft==0) needs all 12 FP regs forbidden; only 11 are in use there. So the original differs structurally around dy; tried without effect: guards with dy/dx/dz/dist/dot/ny at every case-1/case-0 boundary, dy forms (two statements, temp float/int, duplicated assignment, guard before it), function-scope dx/dy shared with case 0 (neutral, still 7), dist==0 spellings, ny/nx order, as1probe scan (no single-record fix). | stage 3 (orchestrator, revisit 13): full=42 but 439 vs 441 instructions and frame 128 vs 136 (the target's nx/ny stores to 84/88(sp) are missing), so it stays a draft, not a park. Next: a non-forwarded same-block use of nx/ny that keeps their stores (Q0558) without killing the dx/dist copy; then replace the 20 if (1) {} node pads with natural structure (Q0559) | stage 6: full=42 text=40 reloc=2 shape=42 (439/441 lines). R13_opus_2 (base 555ed2b6): rebuilt from natural C + derived uopt rules. firstUseCost=curstaticno*0.25 must be >=20 (>=80 CFG nodes) so deltas take caller-saved f2/f14/f16 (20 x if (1) {} node padding); dot reused for factor with 'dot -= unk0; dot *= unk8;' (two statements give dot adj 40 >= cvt 40 so dot=f0, cvt=f2, and the target's in-place sub.s/mul.s into f0); decl order dz,dy,dx,nz,ny,nx after 7 top words gives target homes; nz computed before a goto/label block boundary so its dot use is a cross-block var (global copy-prop blocked by no_nested_ops: Umpy with ilod partner) -> uncoloured store+reload like target; nx,ny same-block substituted; dead 'if (nx + ny + dz) {}' in the dot<0 block makes dx/dist, dy/dist global CSEs (adj 15 after dist, before arg3f) -> f18/f20, arg3f reuses f20, r/g/b/0.0/300.0 = f22..f30; one-line r/g/b LAYOUT fixes preheader. 'max_range = (1.0f / unk24) / 3.0f; max_range -= range;' (two statements) fixes the whole case-0/post-loop ring (only sp offsets left there). LEFT: target stores nx/ny to homes 84/88 (live-out vars; missing -> frame 128 vs 136, all sp offsets -8); dy reload is in the join block in target (split range), mov.s dist placement; case-0 max_range/factor and post-loop ring names. Tried for the nx/ny stores (all fail): later dead uses `if (nx) {}`, `if (nx * entry->unk1C) {}` (still copy-propagated to dx/dist, var dead, store deleted), `(nx*unkC)+(ny*unk10)` guards (CSE with dot products, breaks f22-f30), local array n[3] or &nx (non-vreg: all three reloaded, full ~200), shared function-scope dx/dy/dz across cases (dz adj 26.7 -> f2). Source rule (uoptinput.c ~1660-1700): a same-block load is forwarded unless bigtree/treekilled/(count==1 && has_ilod); only a NON-forwarded load sets lval_av=false and keeps the store, so the target needs a non-forwarded use of nx/ny or a use reached on a path without the assignment. NEXT: a same-block nx/ny use after a kill of dx (dead `dx = ...` in B) keeps the store but also kills the INNEG copy that makes dx/dist global; dy-split (target reloads dy only at the join) needs dy totalsave <= its best cost; tools in .scratch/R13_opus_2 (chk.py colour checker vs target, reg.py per-region diff, greedy.py). | Prior: stage 4: full=94 text=85 reloc=6 shape=39; R12_sonnet_xhigh_4 (base 564cfef3) Q0548 XBB-window survey: as1probe keep on the park, patched as1 variants limit 0/1/2/3/5/10/100 (L100 built privately from as1patch by patching `li t4,10` at 0x42ace4 to 100, built with /usr/bin/make in .scratch/R12_sonnet_xhigh_4/as1L) and jr-live, plus as1probe scan. RESULT: pure uopt FP colouring (r/g/b $f22-$f26, 300.0 and 0.0f in $f30/$f28, delta spill slots), no as1 lever. Limit 0 = 100, 1 = 96 (hoists present), 2/3/5/10/100 and jrlive all full=94 text=85 reloc=6; scan: `insert 229:label` full=90 and noops at 215-219 full=91 only move the 300.0 `ldc1` constant, deletes at 248/250 full=81 delete constants; no guard applies. The target's `cvt.d.s $f2,$f12` in the `b` delay slot is fillable only because its dest is a different f-reg than ours (colouring-driven). | Prior: stage 4: full=94 text=85 reloc=6 shape=39; R11_lightSampleColorAtPosition: analyzed uopt candidate table via uopt_trace -l 6. In candidate table, g (cand 47, -16vreg) and b (cand 50, -20vreg) have higher priority and take $f22/$f24, leaving r (cand 44, -12vreg) to take $f28/$f30, whereas target assigns r=$f22, g=$f24, b=$f26, 0.0f=$f28, 300.0=$f30. Delta variables crossing sqrtf incur caller save costs (cost 20) and compete with color channels. Verified exact park form in 5E2F0.c with whole-file fdiff OK. | Prior: Matcher9 / prior: stage 4: full=94 text=85 reloc=6 shape=39; 404 actual instructions both (407 including trailing padding), normalized count 443 vs 441 includes relocation rows; frame 136 and callee-saved set exact. Tried dx/dy/dz inline field expressions and cached coordinate/subtraction expressions (all 7 subsets, with/without FAKEs), reuse delta locals for normalized axes, scalar/array/struct normal and delta vectors, nested/comma/inlined normalization, reuse dot as factor and staged range/diff subtraction, typed FP-zero tests, and scalar/array/struct r or rgb accumulators: no improvement. Inline field expressions across sqrtf recompute loads and grow code; coordinate-expression substitutions retain count but disturb frame/coloring. Array vectors retain stores but worsen allocation; structs compile like scalar locals. Prior 300.0/zero/r priority and missing normal stores remain unresolved.
void lightSampleColorAtPosition(f32 arg0, f32 arg1, f32 arg2, s16 arg3, u8 *arg4, u8 *arg5, u8 *arg6, s16 arg7) {
    LightTrigger *entry;
    f32 r;
    f32 g;
    f32 b;
    s32 i;
    s32 pad2;
    f32 pad;
    if (1) {}  // FAKE: node count
    if (1) {}  // FAKE: node count
    if (1) {}  // FAKE: node count
    if (1) {}  // FAKE: node count
    if (1) {}  // FAKE: node count
    if (1) {}  // FAKE: node count
    if (1) {}  // FAKE: node count
    if (1) {}  // FAKE: node count
    if (1) {}  // FAKE: node count
    if (1) {}  // FAKE: node count
    if (1) {}  // FAKE: node count
    if (1) {}  // FAKE: node count
    if (1) {}  // FAKE: node count
    if (1) {}  // FAKE: node count
    if (1) {}  // FAKE: node count
    if (1) {}  // FAKE: node count
    if (1) {}  // FAKE: node count
    if (1) {}  // FAKE: node count
    if (mapChunkIsInUse(arg7) == 0) {
        *arg4 = *arg5 = *arg6 = 0xFF;
        return;
    }
    if (D_807F7EC8 == 0) {
        *arg4 = (s32)(D_8076A0B4[arg7] * 255.0f);
        *arg5 = (s32)(D_8076A0B8[arg7] * 255.0f);
        *arg6 = (s32)(D_8076A0BC[arg7] * 255.0f);
        return;
    }
    r = D_8076A0B4[arg7]; g = D_8076A0B8[arg7]; b = D_8076A0BC[arg7];  // LAYOUT: one line changes as1 scheduling of the three loads

    for (i = 0; i < D_807F7EC8; i++) {
        entry = &D_807F7BC8[i];
        switch (entry->unk3E) {
        case 1: {
            f32 dz;
            f32 dy;
            f32 dx;
            f32 nz;
            f32 ny;
            f32 nx;
            f32 dist;
            f32 dot;
            dx = arg0 - (f32)(entry->unk38 / 3);
            dy = arg1 - (f32)(entry->unk3A / 3);
            dz = arg2 - (f32)(entry->unk3C / 3);
            dist = sqrtf((dz * dz) + ((dx * dx) + (dy * dy)));
            if (dist == 0.0f) {
                dist = 0.1f;
            }
            nz = dz / dist;
            goto lbl; lbl:  // FAKE: block boundary
            nx = dx / dist;
            ny = dy / dist;
            dot = (entry->unk14 * nz) + ((nx * entry->unkC) + (ny * entry->unk10));
            if (dot < 0.0f) {
                if ((nx * entry->unk1C) + (ny * entry->unk1C) + dz) {}  // FAKE: keeps the nx/ny stores (no copy-propagation under a multiply), dz live here
                dot = 0.0f;
            }
            if (entry->unk0 <= dot) {
                if (entry->unk4 <= dot) {
                    dot = 1.0f;
                } else {
                    dot -= entry->unk0;
                    dot *= entry->unk8;
                }
                if ((f64)dist > 300.0) {
                    if ((f64)dist > 1100.0) {
                        dot = 0.0f;
                    } else {
                        dot = (f64)dot * (1.0 - (((f64)dist - 300.0) / 800.0));
                    }
                }
                r += entry->unk2C * dot;
                g += entry->unk30 * dot;
                b += entry->unk34 * dot;
                if (nx + ny + nx + ny + nx + ny) {}  // FAKE: gives the dx/dist and dy/dist temps priority 15 (coloured after dist)
            }
            break;
        }
        case 0: {
            f32 dz;
            f32 dx;
            f32 dy;
            f32 dist;
            f32 diff_val;
            f32 range;
            f32 max_range;
            f32 factor;
            dz = (f32)(entry->unk3C / 3) - arg2;
            dx = (f32)(entry->unk38 / 3) - arg0;
            dy = (f32)(entry->unk3A / 3) - arg1;
            dist = sqrtf((dz * dz) + ((dx * dx) + (dy * dy)));
            diff_val = dist - (f32)arg3;
            if (dist <= (f32)arg3) {
                diff_val = 0.1f;
            }
            range = entry->unk28 / 3.0f;
            if (diff_val < range) {
                r += entry->unk2C;
                g += entry->unk30;
                b += entry->unk34;
            } else {
                diff_val -= range;
                max_range = (1.0f / entry->unk24) / 3.0f;
                max_range -= range;
                if (diff_val < max_range) {
                    factor = 1.0f - (diff_val / max_range);
                    r += entry->unk2C * factor;
                    g += entry->unk30 * factor;
                    b += entry->unk34 * factor;
                }
            }
            break;
        }
        }
    }
    if (r > 1.0f) {
        r = 1.0f;
    }
    if (g > 1.0f) {
        g = 1.0f;
    }
    if (b > 1.0f) {
        b = 1.0f;
    }
    *arg4 = (s32)(r * 255.0f);
    *arg5 = (s32)(g * 255.0f);
    *arg6 = (s32)(b * 255.0f);
}
