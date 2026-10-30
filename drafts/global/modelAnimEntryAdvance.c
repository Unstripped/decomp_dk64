// modelAnimEntryAdvance (src/global/54150.c): stage 6 (parked NON_MATCHING in src copy, fdiff plain TEXT OK): switch(unkF)/switch(unk10), += store+reload, else-first inverted branches, q temps match layout + all integer regs (v1/a1 colouring fixed by FAKE dead if(arg0->unk11) before p + u32 cast for addu order). Left: float regs (ours unk4=f12,out=f2; target unk4=f2,out=f12; frac is a temp f4 in target but var f0 here) and head schedule (ldc1 300.0 hoisted before lh 0xC, li 4 before sltiu) which follows from the float colouring; deadsweep (locals+fields), permuter 1500s: no gain
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
