// func_807245F0 (src/global/1292F0.c): stage 6: 2 insns differ (frame 0x78, regs, schedule, relocs, rodata all match): 'subu t2,t7,t6; addiu t3,t2,2048' vs target 'subu t0,t7,t6; addiu t3,t0,2048'. Analysis 2026-10-31 (cc -S ugen order: mfc1 $12, sll, sra, li 4096 $15, subu $24, sll, sra $8, and $9, and $10, addu $11, and $12): as1 names a collapsed cast chain after its LAST op (ours $10=t2); the target ends at the sra ($8=t0) while the 2 and-ops still consume $9/$10 (use-propagated, not renamed). The cast/mask chain shape does not decide it: 1700+ cast/mask/wrapper/local/type/mod/shift variants (s16/u16/&0xFFFF/(s32)/+0/|0/^0/*1 at every level, intermediate s16/s32/u16 locals, % 0x1000U, u16/s16 store casts) all stay at 2 lines; statement swap of unk10/unkE (19); deadsweep rounds (no gain); permuter 240s+480s (min 10). cc -S -> as1 text round trip does not reproduce the build (prologue differs), so the as1 input cannot be probed by hand.
typedef struct PathFollowState {
    u8 pad0[4];
    s32 unk4;
    f32 unk8;
    u8 unkC;
    u8 padD;
    s16 unkE;
    s16 unk10;
    s16 unk12;
} PathFollowState;

typedef struct PathFollowOwner {
    u8 pad0[0x7C];
    s32 unk7C;
    s32 unk80;
    s32 unk84;
    u8 pad88[0x28];
    s8 unkB0;
    u8 padB1[0x67];
    PathFollowState *unk118;
} PathFollowOwner;

s32 pathExists(u8);
void pathFindClosestPoint(s32, s32, s32, s32, s32 *, f32 *);
void pathRefineClosestPoint(s32, s32, s32, s32, s32 *, f32 *);
void pathSplineSample(s32, s32, f32, f32 *, f32 *, f32 *);
f32 mathAngleBetweenPointsDeg(s32, s32, s32, s32);
s16 pathEntryCount(s32);

void func_807245F0(PathFollowOwner *arg0, u8 arg1) {
    s32 fresh;
    PathFollowState *s;
    s32 idx;
    f32 frac;
    f32 x0;
    f32 y0;
    f32 z0;
    f32 x1;
    f32 y1;
    f32 z1;
    f32 ang;
    s32 cnt;
    u8 sp47;

    sp47 = 0;
    fresh = 0;
    if (arg0->unk118 == NULL) {
        arg0->unk118 = heapAlloc(0x14);
        s = arg0->unk118;
        if (arg0->unkB0 != -1 && pathExists(arg0->unkB0) != 0) {
            s->unk12 = arg0->unkB0;
        } else {
            s->unk12 = -1;
        }
        s->unkC = 0;
        fresh = 1;
    } else {
        s = arg0->unk118;
    }
    if (arg1 != 0 || s->unkC == 0) {
        if (s->unk12 == -1) {
            s->unkC = 1;
            s->unk10 = 0;
            s->unkE = 0;
            return;
        }
        if (fresh != 0) {
            pathFindClosestPoint(s->unk12, arg0->unk7C, arg0->unk80, arg0->unk84, &s->unk4, &s->unk8);
        } else {
            pathRefineClosestPoint(s->unk12, arg0->unk7C, arg0->unk80, arg0->unk84, &s->unk4, &s->unk8);
        }
        frac = s->unk8;
        idx = s->unk4;
        pathSplineSample(s->unk12, idx, frac, &x0, &y0, &z0);
        frac = frac + 0.4;
        if (frac >= 1.0) {
            idx += 1;
            frac = frac - 1.0;
        }
        pathSplineSample(s->unk12, idx, frac, &x1, &y1, &z1);
        ang = mathAngleBetweenPointsDeg((s32)x0, (s32)z0, (s32)x1, (s32)z1);
        s->unkE = (((((s16)(0x1000 - (s16)(s32)(ang * 2048.0 / 3.14159274101257324)) & 0xFFFF) & 0xFFFF) + 0x800) & 0xFFF);
        s->unk10 = 0x23;
        cnt = pathEntryCount(s->unk12) - 1;
        if (s->unk4 >= cnt) {
            if (cnt == s->unk4) {
                sp47 = 1;
                s->unk10 = 0;
            } else {
                sp47 = 1;
                s->unk10 = 0;
            }
        }
        if (sp47 != 0 && arg1 == 0) {
            s->unkC = 1;
        }
    }
}
