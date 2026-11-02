// func_8071F1D0 (src/global/11BC10.c): W3SchedB R5: still stage 6, 4 lines. as1probe (p1 stream, .scratch/W3SchedB/fx_move.py): moving the ucode record of the PRE reload 'lw v1,900(s0)' to ANY earlier position than the global sb (anywhere after the heapAlloc result store is irrelevant to as1) gives full=0, so the target ucode order is lw<sb and as1 never swaps them; moving sb after lw gives 2. So uopt must emit the reload before the global store: the sb must not kill the ilod in the original (or the then-block is split so the reload lands before sb). Tried this round without gain: all no-local/inline-field variants, raw-offset casts of the field for compare/store/post-read (cfe folds to the same expr), field types s32/u32/void*/u8*/f32*/TimedMotionState* (all 4; u16 6), top-assign + explicit reload form (lw lands before sb but spill goes to the jal delay slot as in R4). || PREVIOUS: func_8071F1D0 (src/global/11BC10.c): MiscA R4 2026-11-01: still stage 6, 4 lines (negu after swc1 4(v0), lw v1,900(s0) before sb). New proof/negatives: IDO micro-tests (static/extern/array/struct-field globals, int*-field reload) show a store to ANY global kills the isop ilod and uopt's PRE reload is ALWAYS emitted at the END of the then block (after later pure arithmetic too), so an isop reload can never precede the global sb; only an EXPLICIT reload statement before sb gives lw<sb (form X: else{var_v1=arg0->unk384} + then-block var_v1=arg0->unk384 before D store -> 'lw a1,900(s0); b L; sb' in slot) but then var_v1 is an isvar (coloured a1, compare load separate in v0, spill 'sw a1,36(sp)' at the join not at defs: 25 lines; f1_a top-assign form 14 lines). Searched (all >=4): 2928-form grid (A/B locals x explicit/dead reload x cond x post-use x FAKE toggles) best 6; 212 sibling-style orders (arg0->unk384=heapAlloc; var=arg0->unk384 readback; dir/U0/U4/U8/SB permutations) best 15; dead self-assign '.loc' statements (x=x; on dir/var_v1/temp/arg0/arg1, singles+pairs, all points) none; dir type s8/s16/s32/u8/u32/f32 x 6 negate spellings none; 400s hill-climb (statement moves + spelling alts + dead ifs, 17.7k evals) none. as1 never hoists the lw above the sb (micro-test) so the ucode order must have lw first. || PREVIOUS: R3a: stage 6, still 4 lines (negu before swc1 f6,4(v0) vs after; 'lw v1,900(s0)' lands after sb vs before). New: uopt ALWAYS sinks the post-if reload of arg0->unk384 to the END of the then block (after the global sb, which kills it), so as1 keeps sb<lw. Form that gets lw BEFORE sb with v1/a0/negu all right: 'var_v1 = arg0->unk384; if (var_v1 == NULL) {..temp->unk8 = (f32)dir; var_v1 = arg0->unk384; if (var_v1 && var_v1 && var_v1) {} /*FAKE*/ D_8075567C = -(dir&0xFF);}' + dead if(D_8075567C) in else + NO post-if assign (ucode: lw $3 before sb, no PRE reload) -- first 28 insns then match, but the join loses the spill-at-head (sw v1,36(sp) lands after jal, first reload is v1 not t8): 14 lines. Statement permutation grid (720) of A/U0/U4/U8/SB/FAKE and 3 pre/post/cond grids: none beat 4. Untried: a form that puts a spill store at the join head WITHOUT a post-if load (store of var_v1 into a non-promoted home?).
extern s8 D_8075567C;

void func_8071F1D0(TimedEffectActorView *arg0, s8 *arg1) {
    TimedMotionState *var_v1;
    TimedMotionState *temp;
    s32 dir;

    if (arg0->unk384 == NULL) {
        temp = heapAlloc(0xC);
        dir = D_8075567C;
        arg0->unk384 = temp;
        temp->unk0 = arg0->unk340;
        temp->unk4 = arg0->unk348;
        temp->unk8 = (f32)dir;
        if (arg0->unk384 && arg0->unk384 && arg0->unk384) {}  // FAKE: dead uses steer dir/var_v1 colouring
        D_8075567C = -(dir & 0xFF);
    }
    var_v1 = (TimedMotionState *)arg0->unk384;
    arg0->unk340 = (func_80612794(*(s16 *)((u8 *)arg0 + 0x35E)) * 14.0f) + var_v1->unk0;
    arg0->unk348 = (func_80612790(*(s16 *)((u8 *)arg0 + 0x35E)) * 14.0f) + var_v1->unk4;
    arg0->unk344 = arg0->unk344 + 0.5f;
    if (arg0->unk36D >= 5) {
        if (D_8075567C) {}  // FAKE: dead read steers dir into $a0
        arg0->unk36D = arg0->unk36D - 4;
    } else {
        *arg1 = 1;
    }
    arg0->unk35C = arg0->unk35C + (s32)((f64)var_v1->unk8 * 200.0);
}
