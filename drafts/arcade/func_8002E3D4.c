// func_8002E3D4 (src/arcade/0.c): Stage 5: text/relocs identical except (a) frame 0x30 vs 0x28 (user locals each reserve an 8-byte unit; 3 locals idx/t/count, target has 2; spills a1@0x1c,a2@0x24 already match) -- all selector/flag temps use one local t incl. `t = cond; if (t)` flag form (gets v1 right). Tried reuse of t as idx/count, types, declaration orders, permuter: none gives frame 0x28 with spills at 0x1c/0x24. 2-local variants put spills at 0x18/0x20.
extern u8 D_80032228[];
extern u8 D_80032470[];
extern u8 D_800326B8[];
extern u8 D_80032900[];

void func_8002E3D4(s32 arg0) {
    s32 idx;
    s32 t;
    s32 count;

    if (D_8004C71D == 0) {
        if (--D_8004BCD0[arg0].unk1C >= 0x15) {
            D_8004BCD0[arg0].unk1C = arcadeRand() & 0xF;
            t = D_8004BCD0[arg0].unk1D;
            D_8004BCD0[arg0].unk1D = t == 0;
        }
        t = D_8004BCD0[arg0].unk19;
        switch (t) {
        case 2:
            t = D_8004BCD0[arg0].unk1D;
            switch (t) {
            case 0:
                D_8004BCD0[arg0].unk14 = D_80032228;
                break;
            case 1:
                D_8004BCD0[arg0].unk14 = D_80032470;
                break;
            }
            count = arcadeMinFloat((u32)D_8004A76C, 5.0f);
            if (D_8004C722 == 4) {
                t = (f32)(0x64 - count * 0x14) == D_8004BCD0[arg0].unk10++;
                if (t) {
                    if (arcadeCountEntitiesByType(2) < count) {
                        D_8004BCD0[arg0].unk19 = 3;
                        D_8004BCD0[arg0].unk10 = 0.0f;
                    }
                }
            }
            break;
        case 3:
            t = D_8004BCD0[arg0].unk10++ > 40.0f;
            if (t) {
                D_8004BCD0[arg0].unk19 = 2;
                D_8004BCD0[arg0].unk10 = 0.0f;
                idx = func_80024828();
                D_8004BCD0[idx] = D_8004A3D8;
                D_8004BCD0[idx].unk19 = 3;
                D_8004BCD0[idx].unkC = -1.0f;
                if (D_8004C722 == 1) {
                    D_8004BCD0[idx].unk8 = 0.4f;
                } else {
                    if (D_8004BCD0[D_8004C71F].unk0 < 160.0f) {
                        D_8004BCD0[idx].unk8 = -0.5f;
                    } else {
                        D_8004BCD0[idx].unk8 = 0.5f;
                    }
                    D_8004BCD0[idx].unk1A = 0;
                    D_8004BCD0[idx].unk0 = 160.0f;
                    D_8004BCD0[idx].unk4 = 135.0f;
                }
            }
            t = D_8004BCD0[arg0].unk1D;
            switch (t) {
            case 0:
                D_8004BCD0[arg0].unk14 = D_800326B8;
                return;
            case 1:
                D_8004BCD0[arg0].unk14 = D_80032900;
                break;
            }
            break;
        }
    }
}
