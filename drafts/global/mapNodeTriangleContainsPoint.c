// mapNodeTriangleContainsPoint (src/global/55B20.c): stage 5 (MapB): natural f64 locals (cx,cz,c,dz,oz,ox,dx declared in a hill-climbed order + lead0 pad; mx/mz named mid sums; stale ox/oz/dx/dz read in the unexecuted default path like the target) + 7 dead-statement fakes found by a random hill-climb (cz==0.0, dz>0.0, arg1*2.0 ...). Same frame 0xC8 + callee-saved set; remaining ~75 diff lines are f64/int register rotation (target arg1->f14/arg2->f20, fs1..fs4 order px/pz/cx/cz, int load temps). Earlier 4-diff basin existed with named mx/mz (frame 0xD0, a different fake set read uninitialised locals - rejected). Parked NON_MATCHING in 55B20.c
s32 mapNodeTriangleContainsPoint(void *arg0, f32 arg1, f32 arg2) {
    f64 lead0;
    f64 cz;
    f64 cx;
    f64 c;
    f64 dz;
    f64 oz;
    f64 ox;
    f64 dx;
    f64 mx;
    f64 mz;
    u16 flag;
    s32 i;

    mx = (((MapCollisionNode *)arg0)->unk4 + ((MapCollisionNode *)arg0)->unk2) * 0.5;
    mz = (((MapCollisionNode *)arg0)->unk10 + ((MapCollisionNode *)arg0)->unkE) * 0.5;
    cx = (((MapCollisionNode *)arg0)->unk0 + mx) * 0.5;
    cz = (((MapCollisionNode *)arg0)->unkC + mz) * 0.5;
    flag = 0;
    i = 0;
    if (cz == 0.0) {} // FAKE: steers f64 coloring / int temp order (hill-climb)
    do {
        switch (i) {
        case 0:
            ox = ((MapCollisionNode *)arg0)->unk0;
            dx = ((MapCollisionNode *)arg0)->unk2 - ((MapCollisionNode *)arg0)->unk0;
            dz = ((MapCollisionNode *)arg0)->unkE - ((MapCollisionNode *)arg0)->unkC;
            oz = ((MapCollisionNode *)arg0)->unkC;
            if (dz > 0.0) {} // FAKE: steers f64 coloring / int temp order (hill-climb)
            break;
        case 1:
            oz = ((MapCollisionNode *)arg0)->unkC;
            ox = ((MapCollisionNode *)arg0)->unk0;
            dx = ((MapCollisionNode *)arg0)->unk4 - ((MapCollisionNode *)arg0)->unk0;
            dz = ((MapCollisionNode *)arg0)->unk10 - ((MapCollisionNode *)arg0)->unkC;
            if (arg1 * 2.0) {} // FAKE: steers f64 coloring / int temp order (hill-climb)
            break;
        case 2:
            dx = ((MapCollisionNode *)arg0)->unk4 - ((MapCollisionNode *)arg0)->unk2;
            ox = ((MapCollisionNode *)arg0)->unk2;
            dz = ((MapCollisionNode *)arg0)->unk10 - ((MapCollisionNode *)arg0)->unkE;
            oz = ((MapCollisionNode *)arg0)->unkE;
            if (i) {} // FAKE: steers f64 coloring / int temp order (hill-climb)
            break;
        }
        c = (cx - ox) * dz - (cz - oz) * dx;
        if (!i) {} // FAKE: steers f64 coloring / int temp order (hill-climb)
        i++;
        if (oz == 0) {} // FAKE: steers f64 coloring / int temp order (hill-climb)
        if (((arg2 - oz) * dx <= (arg1 - ox) * dz ? 1 : -1) != (c >= 0.0 ? 1 : -1)) {
            flag = 1;
        }
    } while (i != 3);
    if (arg1 > 0.0) {} // FAKE: steers f64 coloring / int temp order (hill-climb)
    return (flag == 0) & 0xFF;
}
