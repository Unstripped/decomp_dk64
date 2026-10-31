// modelAnimEntryAdvance (src/global/54150.c): stage 6 (parked NON_MATCHING in src copy, plain TEXT OK; deadsweep score full=44): switch(unkF)/switch(unk10), += store+reload, q temps, int regs all match (FAKE dead if(arg0->unk11) + u32 cast). Left: float regs only (ours unk4=f12,out=f2,sum var=f0; target unk4=f2,out=f12,quotient var=f0, sum is an expression temp f4) + head schedule that follows. Candidate bit order explains it: unk4's load candidate colours AFTER out unless unk4 is first seen in a standalone statement. 2026-10-31 revisit3 tried (all <=44 or +1 insn): quotient-as-var forms (frac=(f32)(((f32)a+..)/300.0) makes ugen evaluate mul subtree first -> bgezl/ordering diff, score 65), t/out/frac var splits, u=arg0->unk4 local (u var f0 + mov.s f0,f2, best 31 but 1 insn too big), a/limit types u8/u16/u32/s32, limit/out spellings, decl-order permutations, 5 random hill-climbs (~4000 compiles) plateau 31-34, deadsweep rounds on 9 head variants
typedef struct ModelBAnim {
    u8 *unk0;
    f32 unk4;
    s16 unk8;
    s16 unkA;
    s16 unkC;
    u8 unkE;
    u8 unkF;
    u8 unk10;
    s8 unk11;
    u8 unk12;
    u8 unk13;
} ModelBAnim;

extern u32 D_80744478;

void modelAnimEntryAdvance(void *arg0raw) {
    ModelBAnim *arg0;
    u8 *node;
    u8 *p;
    u32 limit;
    u8 a;
    f32 frac;
    f32 out;
    s32 i;
    s32 q;

    arg0 = arg0raw;
    node = arg0->unk0;
    if (arg0->unk11) {} // FAKE: raises the arg0->unk11 candidate priority (v1 vs a1 swap)
    p = (u8 *)((u32)node + arg0->unk11); // FAKE: u32 cast flips the addu operand order (node, idx)
    a = p[1];
    frac = (f32)a;
    frac += (f32)(p[2] - a) * arg0->unk4;
    out = (f32)arg0->unkC * (f32)(frac / 300.0);
    if (D_80744478 < 4) {
        limit = D_80744478;
    } else {
        limit = 4;
    }
    if (arg0->unk12 & 1) {
        out = (f64)out * ((f64)limit * 0.5);
    }
    switch (arg0->unkF) {
    case 0:
        arg0->unk4 += out;
        i = arg0->unk4;
        arg0->unk11 += i;
        arg0->unk4 -= (f32)i;
        if (arg0->unk11 < *(u8 *)node - 1) {
            return;
        }
        arg0->unk8 += arg0->unk11 / (*(u8 *)node - 1);
        if (arg0->unk8 >= arg0->unkA && arg0->unkA != -1) {
            arg0->unk4 = 1.0f;
            arg0->unk11 = *(u8 *)node - 2;
            arg0->unkE = 0;
            if (arg0->unk10 == 1) {
                arg0->unkF = 1;
            }
        } else {
            switch (arg0->unk10) {
            case 0:
                arg0->unk11 = arg0->unk11 % (*(u8 *)node - 1);
                break;
            case 1:
                q = arg0->unk11 / (*(u8 *)node - 1);
                if (q != 0) {
                    arg0->unkF = 1;
                    arg0->unk11 = *(u8 *)node - 2;
                    arg0->unk4 = 1.0f;
                }
                break;
            }
        }
        break;
    case 1:
        arg0->unk4 -= out;
        if (arg0->unk4 < 0.0) {
            i = (s32)arg0->unk4 - 1;
            arg0->unk11 += i;
            arg0->unk4 -= (f32)i;
        }
        if (arg0->unk11 < 0) {
            arg0->unk8 += (-arg0->unk11) / *(u8 *)node + 1;
            if (arg0->unk8 >= arg0->unkA && arg0->unkA != -1) {
                if (arg0->unk10 == 1) {
                    arg0->unkF = 0;
                }
                arg0->unk4 = 0.0f;
                arg0->unk11 = 0;
                arg0->unkE = 0;
            } else {
                switch (arg0->unk10) {
                case 0:
                    arg0->unk11 = (-arg0->unk11) % (*(u8 *)node - 1);
                    if (arg0->unk11 != 0) {
                        arg0->unk11 = *(u8 *)node - arg0->unk11 - 1;
                    }
                    break;
                case 1:
                    q = (-arg0->unk11) / *(u8 *)node + 1;
                    if (q) {
                        arg0->unkF = 0;
                        arg0->unk11 = 0;
                        arg0->unk4 = 0.0f;
                    }
                    break;
                }
            }
        }
        break;
    }
}
