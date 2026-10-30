// func_80699958 (src/global/9DD70.c): stage 5 parked NON_MATCHING (best 801 vs 817 insns): control flow and prologue match target (frame 0x1A8, s0-s7+fp+ra, f20-f26; target also saves f28 and its sp128 is 32 floats at 0x128 vs my 26 at 0xD8, plus 8 extra scalar stack slots). Key wins: dropped the 'len' local and used the u8 arg0 directly (removes uopt spill, restores target prologue exactly), real prototypes for func_80613C48/func_80614D00 (missing ones caused double-arg promotion), fabsf replaced by if/else abs (IDO does not inline fabsf), scan loops use 'j < n && found == 0' early exit. Remaining: 233 target-only / 237 current-only asm-differ lines, mostly loop rotation and one float reg
#include "common.h"
#include "actor.h"

typedef struct L2Node {
    /* 0x00 */ u8 unk0;
    /* 0x01 */ u8 unk1;
    /* 0x02 */ u8 pad2[2];
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
} L2Node;

typedef struct L2Sub4 {
    /* 0x00 */ u8 pad0[0x24];
    /* 0x24 */ L2Node *unk24;
} L2Sub4;

typedef struct L2Entry {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
} L2Entry;

typedef struct L2Globals {
    /* 0x00 */ u8 pad0[0x39];
    /* 0x39 */ u8 unk39;
    /* 0x3A */ u8 pad3A[2];
    /* 0x3C */ L2Entry entries[4];
    /* 0x6C */ u8 pad6C[0x10];
    /* 0x7C */ void *unk7C[4];
} L2Globals;

typedef struct L2State {
    /* 0x000 */ s16 unk0;
    /* 0x002 */ u8 pad2[2];
    /* 0x004 */ f32 unk4[28];
    /* 0x074 */ void *unk74[4];
    /* 0x084 */ f32 unk84[4];
    /* 0x094 */ u8 unk94;
    /* 0x095 */ u8 pad95[3];
    /* 0x098 */ f32 unk98[4];
    /* 0x0A8 */ f32 unkA8[4];
    /* 0x0B8 */ u8 unkB8[4];
} L2State;

extern Actor *D_807FBB40;
extern u8 D_807FBBEC;
extern ActorGlobalState D_807FBB70;
void func_80613C48(Actor *, s16, f32, f32);
void func_80614D00(Actor *, f32, f32);
Mtx *heapAlloc(s32);
void actorUpdateModelMatrix(Actor *, s32);
s32 func_8069A750(void);
void func_8069A614(f32, u8);
f32 func_80612D1C(f32);
void *memcpy(void *, const void *, unsigned int);

void func_80699958(u8 arg0, u8 arg1) {
    f32 spC0[26];
    f32 sp128[26];
    f32 spBC;
    f32 var_fa0;
    L2State *state;
    L2Globals *g;
    s32 i;
    s32 j;
    s32 found;
    f64 temp;
    f32 dist;
    f32 val;

    state = (L2State *)D_807FBB40->unk174;
    if (!(D_807FBB40->unk60 & 0x10)) {
        ((L2Sub4 *)D_807FBB40->unk4)->unk24 = (L2Node *)heapAlloc((arg0 * 0x10) + 0x10);
        for (i = 0; i < arg0; i++) {
            ((L2Node *)((L2Sub4 *)D_807FBB40->unk4)->unk24)[i].unk0 = i;
            ((L2Node *)((L2Sub4 *)D_807FBB40->unk4)->unk24)[i].unk1 = (i == arg0 - 1) ? 0xFF : i + 1;
            ((L2Node *)((L2Sub4 *)D_807FBB40->unk4)->unk24)[i].unk4 = 0.0f;
            ((L2Node *)((L2Sub4 *)D_807FBB40->unk4)->unk24)[i].unkC = 0.0f;
            ((L2Node *)((L2Sub4 *)D_807FBB40->unk4)->unk24)[i].unk8 = 0.0f;
        }
        ((L2Node *)((L2Sub4 *)D_807FBB40->unk4)->unk24)[arg0].unk0 = 0xFF;
        for (i = 0; i < arg0; i++) {
            state->unk4[i] = 0.0f;
        }
        state->unk0 = -1;
        state->unk94 = 0;
        state->unkB8[1] = 0;
        state->unkB8[2] = 0;
        state->unkB8[3] = 0;
        state->unkB8[0] = 0;
    }
    if ((func_8069A750() != 0) && (state->unk0 == -1)) {
        state->unk0 = 10;
    }
    if (state->unk0 > 0) {
        state->unk0--;
    }
    if (state->unk0 == 0) {
        func_80613C48(D_807FBB40, 0x403, 0, 1.0f);
        func_80614D00(D_807FBB40, 4.0f, 1.0f);
        state->unk0 = -2;
    }
    for (i = 0; i < arg0; i++) {
        sp128[i] = 0.0f;
        spC0[i] = 0.0f;
    }
    g = (L2Globals *)&D_807FBB70;
    i = 0;
    if ((s32)D_807FBB70.unk39 > 0) {
        do {
            found = 0;
            for (j = 0; j < (s32)state->unk94 && found == 0; j++) {
                if (state->unk74[j] == g->unk7C[i]) {
                    found = 1;
                }
            }
            if (!found) {
                switch (arg1) {
                case 0:
                    func_8069A614(g->entries[i].unk8, arg1);
                    break;
                case 1:
                    func_8069A614(g->entries[i].unk0, arg1);
                    break;
                }
            }
            i++;
        } while (i < (s32)D_807FBB70.unk39);
        i = 0;
    }
    if ((s32)state->unk94 > 0) {
        do {
            found = 0;
            for (j = 0; j < (s32)D_807FBB70.unk39 && found == 0; j++) {
                if (g->unk7C[j] == state->unk74[i]) {
                    found = 1;
                }
            }
            if (!found) {
                func_8069A614(state->unk84[i], arg1);
            }
            i++;
        } while (i < (s32)state->unk94);
        i = 0;
    }
    memcpy(state->unk74, &D_807FBBEC, 0x10);
    state->unk94 = D_807FBB70.unk39;
    if ((s32)state->unk94 > 0) {
        do {
            switch (arg1) {
            case 0:
                state->unk84[i] = g->entries[i].unk8;
                break;
            case 1:
                state->unk84[i] = g->entries[i].unk8;
                break;
            }
            i++;
        } while (i < (s32)state->unk94);
        i = 0;
    }
    var_fa0 = spBC;
    if ((s32)D_807FBB70.unk39 > 0) {
        do {
            switch (arg1) {
            case 0:
                temp = (f64)g->entries[i].unk8 / 843.0;
                if (temp > 0.0) {
                    var_fa0 = (f32)temp;
                } else {
                    var_fa0 = (f32)-temp;
                }
                break;
            case 1:
                temp = (f64)g->entries[i].unk0 / 480.0;
                if (temp > 0.0) {
                    var_fa0 = (f32)temp;
                } else {
                    var_fa0 = (f32)-temp;
                }
                break;
            }
            i++;
            for (j = 0; j < arg0; j++) {
                if (var_fa0 < (f32)j) {
                    dist = (f32)j - var_fa0;
                } else {
                    dist = -((f32)j - var_fa0);
                }
                switch (arg1) {
                case 0:
                    val = (f32)(3.0 - (f64)dist);
                    if (val < 0.0f) {
                        val = 0.0f;
                    }
                    sp128[j] -= 45.0f * val;
                    break;
                case 1:
                    val = (f32)(7.0 - (f64)dist);
                    if (val < 0.0f) {
                        val = 0.0f;
                    }
                    sp128[j] -= 70.0f * val;
                    break;
                }
            }
        } while (i < (s32)D_807FBB70.unk39);
        spBC = var_fa0;
        i = 0;
    }
    for (i = 0; i < 4; i++) {
        j = 0;
        if (state->unkB8[i] != 0) {
            if (arg0 > 0) {
                do {
                    if (state->unk98[i] < (f32)j) {
                        dist = (f32)j - state->unk98[i];
                    } else {
                        dist = -((f32)j - state->unk98[i]);
                    }
                    val = (f32)(3.0 - (f64)dist);
                    if (val < 0.0f) {
                        val = 0.0f;
                    }
                    temp = (f64)state->unkB8[i];
                    spC0[j] = spC0[j] + (val * state->unkA8[i] * func_80612D1C((f32)(temp * 0.5)));
                    j++;
                } while (j != arg0);
            }
            state->unkA8[i] = (f32)((f64)state->unkA8[i] - ((f64)state->unkA8[i] / 20.0));
            if ((f64)state->unkA8[i] < 0.5) {
                state->unkB8[i] = 0;
            } else {
                state->unkB8[i]++;
            }
        }
    }
    i = 0;
    if (arg0 > 0) {
        do {
            if (state->unk4[i] < sp128[i]) {
                switch (arg1) {
                case 0:
                    state->unk4[i] = (f32)((f64)state->unk4[i] + ((f64)(sp128[i] - state->unk4[i]) * 0.25));
                    break;
                case 1:
                    state->unk4[i] = (f32)((f64)state->unk4[i] + ((f64)(sp128[i] - state->unk4[i]) / 15.0));
                    break;
                }
                if (sp128[i] < state->unk4[i]) {
                    state->unk4[i] = sp128[i];
                }
            }
            if (sp128[i] < state->unk4[i]) {
                switch (arg1) {
                case 0:
                    state->unk4[i] = (f32)((f64)state->unk4[i] - ((f64)(state->unk4[i] - sp128[i]) * 0.5));
                    break;
                case 1:
                    state->unk4[i] = (f32)((f64)state->unk4[i] - ((f64)(state->unk4[i] - sp128[i]) * 0.125));
                    break;
                }
                if (state->unk4[i] < sp128[i]) {
                    state->unk4[i] = sp128[i];
                }
            }
            ((L2Node *)((L2Sub4 *)D_807FBB40->unk4)->unk24)[i].unk8 = spC0[i] + state->unk4[i];
            i++;
        } while (i != arg0);
    }
    ((L2Node *)((L2Sub4 *)D_807FBB40->unk4)->unk24)[0].unk8 = 0.0f;
    ((L2Node *)((L2Sub4 *)D_807FBB40->unk4)->unk24)[arg0 - 1].unk8 = 0.0f;
    actorUpdateModelMatrix(D_807FBB40, 0);
}
