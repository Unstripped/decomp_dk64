#include "common.h"
#include "actor.h"

void *func_80610FE8(s32);

typedef struct {
    u8 unk0[0x118];
    void *unk118;
} AnimationOwner;

void heapFree(void *);

#ifdef NON_MATCHING
typedef struct Fx127BPathState {
    u8 pad0[4];
    s32 unk4;
    f32 unk8;
    u8 unkC;
    u8 padD;
    s16 unkE;
    s16 unk10;
    s16 unk12;
} Fx127BPathState;

typedef struct Fx127BPathOwner {
    u8 pad0[0x7C];
    s32 unk7C;
    s32 unk80;
    s32 unk84;
    u8 pad88[0x28];
    s8 unkB0;
    u8 padB1[0x67];
    Fx127BPathState *unk118;
} Fx127BPathOwner;

s32 pathExists(u8);
void func_80723F88(s32, s32, s32, s32, s32 *, f32 *);
void func_80724154(s32, s32, s32, s32, s32 *, f32 *);
void func_80723CCC(s32, s32, f32, f32 *, f32 *, f32 *);
f32 mathAngleBetweenPointsDeg(s32, s32, s32, s32);
s16 pathEntryCount(s32);

void func_807245F0(Fx127BPathOwner *arg0, u8 arg1) {
    s32 fresh;
    Fx127BPathState *s;
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
        arg0->unk118 = func_80610FE8(0x14);
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
            func_80723F88(s->unk12, arg0->unk7C, arg0->unk80, arg0->unk84, &s->unk4, &s->unk8);
        } else {
            func_80724154(s->unk12, arg0->unk7C, arg0->unk80, arg0->unk84, &s->unk4, &s->unk8);
        }
        frac = s->unk8;
        idx = s->unk4;
        func_80723CCC(s->unk12, idx, frac, &x0, &y0, &z0);
        frac = frac + 0.4;
        if (frac >= 1.0) {
            idx += 1;
            frac = frac - 1.0;
        }
        func_80723CCC(s->unk12, idx, frac, &x1, &y1, &z1);
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
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/1292F0/func_807245F0.s")
#endif

void animationOwnerFreeBuffer(AnimationOwner *arg0) {
    void *temp_a1;

    temp_a1 = arg0->unk118;
    if (temp_a1 != 0) {
        heapFree(temp_a1);
        arg0->unk118 = NULL;
    }
}

