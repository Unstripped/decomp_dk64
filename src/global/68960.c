#include "common.h"
#include "actor.h"

typedef struct R1Small_68960_Entry {
    s16 unk0;
    s8 unk2;
    s8 pad3;
    s16 unk4;
} R1Small_68960_Entry;

extern R1Small_68960_Entry D_80748B70[];
extern s32 D_8076A0A8;
s32 func_8061CC00(void);

void func_80663C60(f32 *arg0, s16 arg1) {
    s16 limit = 6;
    f32 target;
    f32 val;
    s16 i;

    if (D_8076A0A8 == 0x57) {
        if (func_8061CC00()) {
            target = 2200.0f;
        } else {
            target = 900.0f;
        }
        val = *arg0;
        *arg0 = (target - val) * 0.03 + val;
    }

    for (i = 0; i < limit; i++) {
        if (D_8076A0A8 == D_80748B70[i].unk0 && (arg1 == D_80748B70[i].unk2 || D_80748B70[i].unk2 == -1)) {
            val = *arg0;
            *arg0 = (D_80748B70[i].unk4 - val) * 0.03 + val;
            return;
        }
    }
}

