// func_800286D0 (src/jetpac/3480.c): stage 5 unchanged: uopt_trace shows (y-(-8))/144 is its own candidate (udiv expr, f0) distinct from var t (colour f2), so t' lands in f2 and zero/one consts shift to f14/f16; target keeps one t in f0, zero f2, one f14. Tried clamp forms (ifs, split ternaries, int 0/1 consts, repeated expr), dummy if(!v){} uses (t,y,spd,i,item,0) before/after the clamp and at t = y + spd, permuter 200s: no gain.
extern s32 D_80770DF8[];
void func_80024E70(s32);
void func_80024F24(s32, f32);
void func_80024F64(s32);
void func_80024F9C(s32);
void func_800250A0(void);

void func_800286D0(void) {
    s32 i;
    JetpacItem *item;
    f32 spd;
    f32 y;
    f32 t;
    s32 pad;

    item = (JetpacItem *)((u8 *)&D_8002EC30 + D_8002EC30.unk344 * 0x194 + 0x30);

    y = item->unkC;
    t = (y - -8.0f) / 144.0f;
    t = (t < 0.0f) ? 0.0f : ((t > 1.0f) ? 1.0f : t);

    if (*(s32 *)((u8 *)&D_8002EC30 + 0x78C) == 1) {
        if (D_80770DF8[1] == 0) {
            func_80024E70(1);
        }
        func_80024F24(1, 1.0f - t * 0.059466f);
        y = item->unkC;
        if (y >= 136.0f) {
            for (i = 0; i < 3; i++) {
                item[i].unk8 = 168.0f;
                item[i].unkC = (f32)(i * 16) + 136.0f;
            }
            func_80024F64(1);
            func_80024F9C(2);
            return;
        }
        spd = 0.4f;
    } else if (*(s32 *)((u8 *)&D_8002EC30 + 0x78C) == 4) {
        if (D_80770DF8[0] == 0) {
            func_80024E70(0);
        }
        t = 1.0f - t;
        func_80024F24(0, t * 0.059466f + 1.0f);
        y = item->unkC;
        if (y < -8.0f) {
            func_80024F64(0);
            func_800250A0();
            return;
        }
        spd = -0.4f;
    }

    t = y + spd;
    for (i = 0; i < 3; i++) {
        item[i].unkC = t;
        t += 16.0f;
    }
}
