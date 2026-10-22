// func_8067680C (src/global/7AF60.c): matches in C; land together with func_80676D00 (its C jump table drops the 4-byte late_rodata pad before 80676D00's floats)
typedef struct Beh7AF4_Sub0 {
    u8 pad[0x1C];
    s16 unk1C;
} Beh7AF4_Sub0;

typedef struct Beh7AF4_Actor {
    Beh7AF4_Sub0* unk0;
    ActorSub4* unk4;
    u8 pad[0x80 - 8];
    f32 unk80;
} Beh7AF4_Actor;

extern u8 D_807FBBA9;

s32 func_8067680C(arg0, arg1, arg2)
Actor* arg0;
Actor* arg1;
s32 arg2;
{
    f32 x;
    f32 y;
    f32 diff;
    f32 threshold;
    u32 type;

    if (arg1->unk5C & 1) {
        u8* beh = arg1->unk174;
        if (*(s32*)(beh + 0x1F0) & 0x01000000) {
            return 1;
        }
    }

    if (!func_8067641C((s32)arg0, (s32)arg1, arg2)) {
        return 0;
    }

    x = ((Beh7AF4_Actor*)arg0)->unk4->unk38 * (f32)((Beh7AF4_Actor*)arg0)->unk0->unk1C;
    y = ((Beh7AF4_Actor*)arg0)->unk80 + x;
    if (arg1->unk80 < y) {
        diff = y - arg1->unk80;
    } else {
        diff = -(y - arg1->unk80);
    }
    type = arg0->unk58;
    switch (type) {
        case 0x13:
        case 0x1A:
        case 0x55:
        case 0x85:
        case 0x95:
            threshold = 8.0f;
            break;
        case 0x3F:
        case 0x40:
        case 0x41:
        case 0x42:
        case 0x43:
            threshold = 14.0f;
            break;
        case 0x3D:
        case 0x82:
            threshold = 25.0f;
            break;
        default:
            threshold = 0.0f;
            break;
    }

    if (threshold < diff) {
        return 0;
    }

    if (D_807FBBA9 != 0) {
        return 0;
    }

    if (!(arg0->unk68 & 1)) {
        return 0;
    }
    return 1;
}
