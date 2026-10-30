// frameTimingUpdate (src/global/3C10.c): stage 3 (callee-saved set differs: mine s0,s1,s2 frame 0x10 vs target s0 frame 8): structure matches (else-if flag, tail store dup per arm, volatile gScheduler+0x284 via lda-in-reg, volatile D_80767CC4 do-while spin, for-loop unrolled 4x). Cause: uopt const candidate 'lda D_8076AF00' is promoted to s2 (target keeps lui/addu/%lo per access) and max/min are 'constrained' (interference degree 22, k=22) so they colour first (v0/v1) instead of after AF10val/sched/&AF10 (a1/a2). uopt_trace -l 5: removing the flag var (permuter min<->flag merge, score 1240, not semantics-preserving) drops degree to 21/20 and gives target-like order. max/min init inside the if-arm also gives a1/a2 but li placement differs. Declaration order is irrelevant (brute-forced 80 perms: all 3161).
extern u32 D_80744478;
extern u8 D_80745290;
extern u32 D_8076A064;
extern u8 gScheduler[];
#define SCHED284 (*(volatile s32 *)(gScheduler + 0x284))

void frameTimingUpdate(void) {
    s32 max;
    s32 min;
    s32 sample;
    s32 flag;
    s32 n;
    s32 i;
    s32 idx;
    s32 v;
    u32 limit;

    max = 1;
    min = 20;
    if (D_8076AF14 != 0) {
        sample = SCHED284 - D_8076AF10;
        flag = 0;
        if (sample <= 0) {
            sample = 1;
        }
        i = 0;
        D_8076AF00[D_80745290] = sample;
        D_80745290++;
        if (D_80745290 == 8) {
            D_80745290 = 0;
        }
        if (D_80744478 >= 4) {
            n = 1;
        } else if (D_80744478 < sample) {
            n = 2;
        } else {
            n = 4;
        }
        idx = D_80745290;
        for (i = 0; i < n; i++) {
            idx--;
            if (idx < 0) {
                idx = 7;
            }
            v = D_8076AF00[idx];
            if (v >= max) {
                max = v;
            }
            if (min >= v) {
                min = v;
            }
        }
        if (D_80744478 < sample && D_80744478 < min) {
            flag = 1;
        } else if (sample < D_80744478 && max < D_80744478) {
            flag = 1;
        }
        if (flag != 0) {
            D_80744478 = sample;
        }
        if (D_8076A064 >= 0xB) {
            limit = D_8076AF10 + D_80744478;
            if (SCHED284 < limit) {
                do {
                } while (*(volatile s32 *)&D_80767CC4 < limit);
            }
        }
        D_8076AF10 = SCHED284;
    } else {
        D_80744478 = SCHED284 - D_8076AF10;
        D_8076AF10 = SCHED284;
    }
}
