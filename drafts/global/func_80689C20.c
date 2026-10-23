// func_80689C20 (src/global/8D3E0.c): 0x18 frame matches; inner loop matched; register allocation difference on item/target
typedef struct ActorListRecord {
    /* 0x00 */ f32 unk00;
    /* 0x04 */ f32 unk04;
    /* 0x08 */ f32 unk08;
    /* 0x0C */ f32 unk0C;
    /* 0x10 */ char unk10[0x20];
    /* 0x30 */ s16 unk30;
    /* 0x32 */ s16 unk32;
    /* 0x34 */ s16 unk34;
    /* 0x36 */ char pad36[2];
} ActorListRecord;

s32 func_80689C20(s32 *arg0, s16 *arg1, u8 arg2, f32 arg3, f32 arg4, f32 arg5) {
    s32 total = *arg0;
    u8 count = arg2;
    s32 bestIndex = -1;
    f32 minDistance = 9999999.0f;
    s32 i;
    s16 *ptr;
    s16 *end;
    f32 dx, dy, dz, dist;

    for (i = 0; i < total; i++) {
        if (count > 0) {
            s32 j = 0;
            ActorListRecord *item = (ActorListRecord *)((u8 *)arg0 + (i * 0x38) + 4);
            s16 target = item->unk32 + 0x10;
            if (count & 1) {
                if (arg1[0] == target) {
                    dx = item->unk00 - arg3;
                    dy = item->unk04 - arg4;
                    dz = item->unk08 - arg5;
                    dist = (dz * dz) + ((dx * dx) + (dy * dy));
                    if (dist < minDistance) {
                        minDistance = dist;
                        bestIndex = item->unk34;
                    }
                }
                j = 1;
                if (count == 1) {
                    continue;
                }
            }
            ptr = &arg1[j];
            end = &arg1[count];
            do {
                if (*ptr == target) {
                    dx = item->unk00 - arg3;
                    dy = item->unk04 - arg4;
                    dz = item->unk08 - arg5;
                    dist = (dz * dz) + ((dx * dx) + (dy * dy));
                    if (dist < minDistance) {
                        minDistance = dist;
                        bestIndex = item->unk34;
                    }
                }
                if (*(ptr + 1) == target) {
                    dx = item->unk00 - arg3;
                    dy = item->unk04 - arg4;
                    dz = item->unk08 - arg5;
                    dist = (dz * dz) + ((dx * dx) + (dy * dy));
                    if (dist < minDistance) {
                        minDistance = dist;
                        bestIndex = item->unk34;
                    }
                }
                ptr += 2;
            } while (ptr != end);
        }
    }
    return bestIndex;
}
