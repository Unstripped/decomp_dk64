// func_8002B390 (src/arcade/0.c): stage 5, 12 diff lines (regalloc only): (1) D_8004A764 address ptr gets v0, target v1 (C71B ptr v1 matches); (2) tail 'if (t == 2)' emits bne t2,t0, target bne t0,t2. Everything else identical incl. frame/ring. Key forms: direct D_8004BCD0[arg0] (not ptr) so val CSE survives D_8004C71D store; ptr->unk1A ^= 1 (via ptr local) forces reload; !unk1B; val assigned after unk1B=0; permuter 300s no gain
extern u8 D_8003B180[];
extern u8 D_8003B3C8[];
extern u8 D_8003B610[];
extern u8 D_8003B858[];
extern u8 D_8003BAA0[];
extern u8 D_8003BCE8[];
extern u8 D_8003BF30[];
extern u8 D_8003C178[];
extern u8 D_8003C3C0[];
extern u8 D_8003C608[];
extern u8 D_8003C850[];
extern u8 D_8003CA98[];
extern u8 D_8003CCE0[];
extern u8 D_8003CF28[];
extern u8 D_8003D170[];
extern u8 D_8003D3B8[];
extern u8 D_8003D600[];
extern u8 D_8003D848[];
extern s32 D_8004A75C;

void func_8002B390(s32 arg0) {
    s32 val;
    ArcadeEntity *ptr = &D_8004BCD0[arg0];
    s32 b;
    s32 t;
    s32 s4;
    s32 s0;
    f32 fs0;
    f32 y;

    b = D_8004BCD0[arg0].unk1A & 2;
    D_8004BCD0[arg0].unk1A = b / 2 | b;
    D_8004BCD0[arg0].unk1B = 0;
    val = (s32)D_8004BCD0[arg0].unk10;
    if (D_8004BCD0[arg0].unk19 == 2) {
        if (D_8004C710 != 0) {
            if (D_8004C710 & 8) {
                switch (val & 3) {
                case 0:
                case 2:
                    D_8004BCD0[arg0].unk14 = D_8003C178;
                    break;
                case 1:
                    D_8004BCD0[arg0].unk14 = D_8003C608;
                    break;
                case 3:
                    D_8004BCD0[arg0].unk14 = D_8003CA98;
                    break;
                }
            } else {
                switch (val & 3) {
                case 0:
                case 2:
                    D_8004BCD0[arg0].unk14 = D_8003C3C0;
                    break;
                case 1:
                    D_8004BCD0[arg0].unk14 = D_8003C850;
                    break;
                case 3:
                    D_8004BCD0[arg0].unk14 = D_8003CCE0;
                    break;
                }
            }
        } else {
            switch (val & 3) {
            case 0:
            case 2:
                D_8004BCD0[arg0].unk14 = D_8003B180;
                break;
            case 1:
                D_8004BCD0[arg0].unk14 = D_8003B3C8;
                break;
            case 3:
                D_8004BCD0[arg0].unk14 = D_8003B610;
                break;
            }
        }
    } else if (D_8004BCD0[arg0].unk19 == 3) {
        D_8004BCD0[arg0].unk14 = D_8003CF28;
    } else if (D_8004BCD0[arg0].unk19 == 5) {
        y = D_8004BCD0[arg0].unk4;
        if ((f32)D_8004C6E8 - y < 1.0f || (y - (f32)D_8004C6E4 < 1.0f)) {
            D_8004BCD0[arg0].unk14 = D_8003BF30;
        } else if (y - (f32)D_8004C6E4 < 6.0f) {
            D_8004BCD0[arg0].unk14 = D_8003B858;
        } else if (y - (f32)D_8004C6E4 < 10.0f) {
            D_8004BCD0[arg0].unk14 = D_8003BCE8;
        } else if (y - (f32)D_8004C6E4 < 14.0f) {
            D_8004BCD0[arg0].unk14 = D_8003BAA0;
        } else {
            D_8004BCD0[arg0].unk14 = D_8003B858;
        }
        D_8004BCD0[arg0].unk1A = (s32)((f64)D_8004BCD0[arg0].unk10 / 4.5) & 1;
    } else if (D_8004BCD0[arg0].unk19 == 8) {
        if (D_8004BCD0[arg0].unk10 > 38.0f) {
            if (D_8004C71B == 0) {
                if (D_8004BCD0[arg0].unk10 > 48.0f) {
                    if (D_8004A75C < D_8004A748) {
                        arcadeCheckGameOver();
                        return;
                    }
                    if (D_8004A740 != 0) {
                        arcadeExit();
                        return;
                    }
                    func_80024D90();
                    return;
                }
                if (D_8004A764 == 0) {
                    D_8004A764 = 1;
                    for (s4 = 0x6C; s4 != 0xCC; s4 += 0x10) {
                        fs0 = s4;
                        for (s0 = 0xA6; s0 != 0xC6; s0 += 0x10) {
                            s32 index = func_800247F0();
                            D_8004BCD0[index] = D_8004A6B8;
                            D_8004BCD0[index].unk0 = fs0;
                            D_8004BCD0[index].unk4 = s0;
                        }
                    }
                }
            } else {
                D_8004C71B--;
                func_800257D8();
            }
        } else if (D_8004BCD0[arg0].unk10 > 20.0f) {
            D_8004BCD0[arg0].unk14 = D_8003D848;
        } else if (D_8004BCD0[arg0].unk10 > 8.0f) {
            D_8004C71D = 2;
            if ((s32)D_8004BCD0[arg0].unk10 & 1) {
                D_8004BCD0[arg0].unk14 = D_8003D3B8;
            } else {
                D_8004BCD0[arg0].unk14 = D_8003D600;
            }
            t = (s32)D_8004BCD0[arg0].unk10 & 3;
            if (t == 2) {
                ptr->unk1A ^= 1;
                t = (s32)D_8004BCD0[arg0].unk10 & 3;
            }
            if (t == 1) {
                D_8004BCD0[arg0].unk1B = !D_8004BCD0[arg0].unk1B;
            }
        }
    } else {
        D_8004BCD0[arg0].unk14 = D_8003D170;
    }
}
