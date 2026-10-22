// func_80689C20 (src/global/8D3E0.c): search items for matching IDs with distance to 3D point; 2-way unrolled inner loop
s32 func_80689C20(s32 *arg0, s16 *arg1, u8 arg2, f32 arg3, f32 arg4, f32 arg5) {
    s32 total = *arg0;
    u8 count = arg2;
    s32 bestIndex = -1;
    f32 minDistance = 9999999.0f;
    s32 i;
    R2D3B_OutputStruct *item = (R2D3B_OutputStruct *)(arg0 + 1);

    for (i = 0; i < total; i++, item++) {
        s32 j = 0;
        if (count > 0) {
            s32 target = item->unk32 + 0x10;
            if (count & 1) {
                if (arg1[0] == target) {
                    f32 dx = item->unk0 - arg3;
                    f32 dy = item->unk4 - arg4;
                    f32 dz = item->unk8 - arg5;
                    f32 dist = (dz * dz) + ((dx * dx) + (dy * dy));
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
            {
                s16 *ptr = arg1 + j;
                s16 *end = arg1 + count;
                do {
                    if (*ptr == target) {
                        f32 dx = item->unk0 - arg3;
                        f32 dy = item->unk4 - arg4;
                        f32 dz = item->unk8 - arg5;
                        f32 dist = (dz * dz) + ((dx * dx) + (dy * dy));
                        if (dist < minDistance) {
                            minDistance = dist;
                            bestIndex = item->unk34;
                        }
                    }
                    if (*(ptr + 1) == target) {
                        f32 dx = item->unk0 - arg3;
                        f32 dy = item->unk4 - arg4;
                        f32 dz = item->unk8 - arg5;
                        f32 dist = (dz * dz) + ((dx * dx) + (dy * dy));
                        if (dist < minDistance) {
                            minDistance = dist;
                            bestIndex = item->unk34;
                        }
                    }
                    ptr += 2;
                } while (ptr != end);
            }
        }
    }
    return bestIndex;
}
