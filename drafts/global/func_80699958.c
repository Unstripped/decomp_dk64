// func_80699958 (src/global/9DD70.c): L699958 final: stage 5 parked NON_MATCHING, 836 vs 836 insns, frame 0x1A8 and all callee-saved match. Remaining diff (25ish lines): (1) top join: uopt hoists 'i = 0' (move s4,zero) into jal func_8069A750 delay slot and 'lui s0 (&D_807FBB70)' into blez delay slot (target keeps them after); only a dead read of uninitialised i blocks it (forbidden fake); (2) last loop: FP scratch temp pool rotated by one ( vs  etc, ~9 hunks) and add.s operand order spC0[i]+unk4[i]; (3) 843.0 reloc-only. Key wins: var_fa0 reused as sinApprox temp (fixes mul/add operand order, frame), (arg0<<4)-8 byte offset avoids arg0*16 CSE/spill, found u8, scan loops while(j<n&&!found){if(eq)found=1;else j++;}, temp>0 int zero, 0.5f in last loop, g/temp/val removed, i<arg0 in last loop, state->unk74[i]==g->unk7C[j] operand order.
#include "common.h"
#include "actor.h"

extern Actor *D_807FBB40;

typedef struct WaveNode {
    /* 0x00 */ u8 unk0;
    /* 0x01 */ u8 unk1;
    /* 0x02 */ u8 pad2[2];
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
} WaveNode;

typedef struct NodeListHead {
    /* 0x00 */ u8 pad0[0x24];
    /* 0x24 */ WaveNode *unk24;
} NodeListHead;

typedef struct ProximityEntry {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
} ProximityEntry;

typedef struct ProximityGlobals {
    /* 0x00 */ u8 pad0[0x39];
    /* 0x39 */ u8 unk39;
    /* 0x3A */ u8 pad3A[2];
    /* 0x3C */ ProximityEntry entries[4];
    /* 0x6C */ u8 pad6C[0x10];
    /* 0x7C */ void *unk7C[4];
} ProximityGlobals;

typedef struct WaveState {
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
} WaveState;

extern u8 D_807FBBEC;
extern ActorGlobalState D_807FBB70;
void func_80613C48(Actor *, s16, f32, f32);
void func_80614D00(Actor *, f32, f32);
Mtx *heapAlloc(s32);
void actorUpdateModelMatrix(Actor *, s32);
s32 func_8069A750(void);
void actorAddNodeForceSlot(f32, u8);
f32 sinApprox(f32);
void *memcpy(void *, const void *, unsigned int);

void func_80699958(u8 arg0, u8 arg1) {
    f32 sp128[32];
    f32 spC0[26];
    f32 var_fa0;
    WaveState *state;
    s32 i;
    s32 j;
    u8 found;
    f32 dist;

    state = (WaveState *)D_807FBB40->unk174;
    if (!(D_807FBB40->unk60 & 0x10)) {
        ((NodeListHead *)D_807FBB40->unk4)->unk24 = (WaveNode *)heapAlloc((arg0 + 1) * 0x10);
        for (i = 0; i < arg0; i++) {
            ((WaveNode *)((NodeListHead *)D_807FBB40->unk4)->unk24)[i].unk0 = i;
            if (i != arg0 - 1) {
                ((WaveNode *)((NodeListHead *)D_807FBB40->unk4)->unk24)[i].unk1 = i + 1;
            } else {
                ((WaveNode *)((NodeListHead *)D_807FBB40->unk4)->unk24)[i].unk1 = 0xFF;
            }
            ((WaveNode *)((NodeListHead *)D_807FBB40->unk4)->unk24)[i].unk4 = 0.0f;
            ((WaveNode *)((NodeListHead *)D_807FBB40->unk4)->unk24)[i].unkC = 0.0f;
            ((WaveNode *)((NodeListHead *)D_807FBB40->unk4)->unk24)[i].unk8 = 0.0f;
        }
        ((WaveNode *)((NodeListHead *)D_807FBB40->unk4)->unk24)[arg0].unk0 = 0xFF;
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
    i = 0;
    if ((s32)D_807FBB70.unk39 > 0) {
        do {
            found = 0;
            j = 0;
            while (j < (s32)state->unk94 && found == 0) {
                if (state->unk74[j] == ((ProximityGlobals *)&D_807FBB70)->unk7C[i]) {
                    found = 1;
                } else {
                    j++;
                }
            }
            if (!found) {
                switch (arg1) {
                case 0:
                    actorAddNodeForceSlot(((ProximityGlobals *)&D_807FBB70)->entries[i].unk8, arg1);
                    break;
                case 1:
                    actorAddNodeForceSlot(((ProximityGlobals *)&D_807FBB70)->entries[i].unk0, arg1);
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
            j = 0;
            while (j < (s32)D_807FBB70.unk39 && found == 0) {
                if (state->unk74[i] == ((ProximityGlobals *)&D_807FBB70)->unk7C[j]) {
                    found = 1;
                } else {
                    j++;
                }
            }
            if (!found) {
                actorAddNodeForceSlot(state->unk84[i], arg1);
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
                state->unk84[i] = ((ProximityGlobals *)&D_807FBB70)->entries[i].unk8;
                break;
            case 1:
                state->unk84[i] = ((ProximityGlobals *)&D_807FBB70)->entries[i].unk8;
                break;
            }
            i++;
        } while (i < (s32)state->unk94);
        i = 0;
    }
    if ((s32)D_807FBB70.unk39 > 0) {
        do {
            switch (arg1) {
            case 0:
                if ((f64)((ProximityGlobals *)&D_807FBB70)->entries[i].unk8 / 843.0 > 0) {
                    var_fa0 = (f32)((f64)((ProximityGlobals *)&D_807FBB70)->entries[i].unk8 / 843.0);
                } else {
                    var_fa0 = (f32)-((f64)((ProximityGlobals *)&D_807FBB70)->entries[i].unk8 / 843.0);
                }
                break;
            case 1:
                if ((f64)((ProximityGlobals *)&D_807FBB70)->entries[i].unk0 / 480.0 > 0) {
                    var_fa0 = (f32)((f64)((ProximityGlobals *)&D_807FBB70)->entries[i].unk0 / 480.0);
                } else {
                    var_fa0 = (f32)-((f64)((ProximityGlobals *)&D_807FBB70)->entries[i].unk0 / 480.0);
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
                    dist = (f32)(3.0 - (f64)dist);
                    if (dist < 0.0) {
                        dist = 0.0f;
                    }
                    sp128[j] -= 45.0f * dist;
                    break;
                case 1:
                    dist = (f32)(7.0 - (f64)dist);
                    if (dist < 0.0) {
                        dist = 0.0f;
                    }
                    sp128[j] -= 70.0f * dist;
                    break;
                }
            }
        } while (i < (s32)D_807FBB70.unk39);
        i = 0;
    }
    for (i = 0; i < 4; i++) {
        if (state->unkB8[i] != 0) {
            for (j = 0; j < arg0; j++) {
                if (state->unk98[i] < (f32)j) {
                    dist = (f32)j - state->unk98[i];
                } else {
                    dist = -((f32)j - state->unk98[i]);
                }
                dist = (f32)(3.0 - (f64)dist);
                if (dist < 0.0) {
                    dist = 0.0f;
                }
                var_fa0 = sinApprox((f32)((f64)state->unkB8[i] * 0.5));
                spC0[j] = ((dist * state->unkA8[i]) * var_fa0) + spC0[j];

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
                    state->unk4[i] = (f32)((f64)state->unk4[i] - ((f64)(state->unk4[i] - sp128[i]) * 0.5f));
                    break;
                case 1:
                    state->unk4[i] = (f32)((f64)state->unk4[i] - ((f64)(state->unk4[i] - sp128[i]) * 0.125));
                    break;
                }
                if (state->unk4[i] < sp128[i]) {
                    state->unk4[i] = sp128[i];
                }
            }
            ((WaveNode *)((NodeListHead *)D_807FBB40->unk4)->unk24)[i].unk8 = spC0[i] + state->unk4[i];
            i++;
        } while (i < arg0);
    }
    ((WaveNode *)((NodeListHead *)D_807FBB40->unk4)->unk24)[0].unk8 = 0.0f;
    *(f32 *)((u8 *)((NodeListHead *)D_807FBB40->unk4)->unk24 + (arg0 << 4) - 8) = 0.0f;  // FAKE: byte-offset form stops the CSE of arg0 * 16 across the calls
    actorUpdateModelMatrix(D_807FBB40, 0);
}
