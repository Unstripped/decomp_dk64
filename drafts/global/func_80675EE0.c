// func_80675EE0 (src/global/7A510.c): from .scratch/Beh7984B/func_80675EE0_best.c
typedef struct Beh7984B_ActorSub4_Sub0 {
    u8 pad0[4];
    f32 unk4;
    u8 pad8[8];
    s16 unk10;
} Beh7984B_ActorSub4_Sub0;

typedef struct Beh7984B_ActorSub4 {
    Beh7984B_ActorSub4_Sub0 *unk0;
} Beh7984B_ActorSub4;

typedef struct Beh7984B_ActorSub174 {
    u8 pad0[0x11E];
    s16 unk11E;
} Beh7984B_ActorSub174;

typedef struct Beh7984B_ActorEE0 {
    u8 pad0[4];
    Beh7984B_ActorSub4 *unk4;
    u8 pad8[0x5C];
    s32 unk64;
    u8 pad68[0xCA];
    s16 unk132;
    s16 unk134;
    s16 unk136;
    u8 pad138[0x3C];
    Beh7984B_ActorSub174 *unk174;
} Beh7984B_ActorEE0;

typedef struct Beh7984B_80748FE8 {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    s16 unk6;
    u8 unk8;
    u8 unk9;
    u8 unkA;
    u8 unkB;
} Beh7984B_80748FE8;

extern Beh7984B_80748FE8 D_80748FE8[];
void func_8067605C(Actor *, u8);

void func_80675EE0(Beh7984B_ActorEE0 *arg0) {
    s16 targetType;
    s16 targetVal;
    s32 a2;
    s32 a3;
    s32 a1;
    Beh7984B_80748FE8 *entry;
    Beh7984B_ActorSub174 *sub174;
    u8 pad;
    u8 valid;

    a1 = 0;
    a2 = 0;
    targetType = arg0->unk4->unk0->unk10;
    sub174 = arg0->unk174;
    targetVal = (s32)arg0->unk4->unk0->unk4;
    a3 = 0;
    valid = 1;

    if (targetType == -1) {
        arg0->unk132 = 0;
        return;
    }

    if (sub174->unk11E != -1) {
        a2 = sub174->unk11E;
        a3 = 1;
    }

    do {
        entry = &D_80748FE8[a2];
        if (entry->unk0 == -1) {
            a1 = 1;
        } else if (targetType == entry->unk0) {
            if ((targetVal >= entry->unk2) && (targetVal <= entry->unk4)) {
                arg0->unk132 = entry->unk6;
                arg0->unk136 = entry->unk8;
                if (entry->unkA & 1) {
                    arg0->unk64 |= 0x80;
                } else {
                    arg0->unk64 &= ~0x80;
                }
                func_8067605C((Actor *)arg0, entry->unk9);
                if (valid) {
                    sub174->unk11E = a2;
                } else {
                    sub174->unk11E = -1;
                }
                return;
            }
            valid = 0;
        }

        if (a3) {
            a2 = 0;
            a3 = 0;
            a1 = 0;
        } else {
            a2++;
        }
    } while (!a1);

    arg0->unk132 = 0;
    arg0->unk136 = 0;
}
