// func_8002D778 (src/race/7BD0.c): stage 5: same frame/callee-saved set (sp 0x30, s0), switch/loop structure identical; remaining 22 diff lines are only $t renumbering: case 3 target stores the unmasked sum (sh t8) and uses li t6 (mine sh t9 / li t8), case 4 unk1C CSE temp is v1 in target (v0 in mine; (u32) trick fixes it in cases 0-2 but not case 4), lui at,%hi(D_80030110) hoisted one slot earlier in target. found: (u64)(t->unk1C + 1), (u32)t->unk1C + 1 / - 1 in case 1/0, f32 scale declared before pa, list0 = t->unk20 copy before i = 0.
typedef struct RaceFActorView {
    char pad0[4];
    RaceSub4 *unk4;
    char pad8[0x60 - 8];
    u32 unk60;
    char pad64[0xE4 - 0x64];
    s16 unkE4;
    char padE6[2];
    s16 unkE8;
    char padEA[0x128 - 0xEA];
    s16 unk128;
} RaceFActorView;
void func_80609140(s16, s32, f32, f32, s32, s32);
void func_8002F950(RaceUnknown174 *);
void func_8002CBEC(void);

void func_8002D778(void) {
    void renderCallbacksRegister(void *, RaceUnknownActor *, s32);
    RaceUnknown174 *t;
    u16 sound;
    u8 i;
    RaceStruct3 *s;
    f32 scale;
    RaceFActorView *pa;
    s32 k;
    u16 cnt;
    RacePair *list;
    RacePair *list0;

    t = D_807FBB40->unk174;
    if (!(D_807FBB40->unk60 & 0x10)) {
        t->unk1C = 0x1E;
    }
    switch (D_807FBB40->unk154) {
    case 0:
        if (t->unk1C != 0) {
            t->unk1C = (u32)t->unk1C - 1;
        } else {
            func_8002D224(1);
        }
        break;
    case 1:
        if (t->unk1C < 0x5B) {
            if (t->unk1C % 30 == 0) {
                sound = 0x75;
                if (t->unk1C == 0x5A) {
                    func_8002D224(2);
                    sound = 0x74;
                    func_8002D4A0();
                }
                func_80609140(sound, 0x7FFF, 64.0f, 1.0, 0, 0x80);
            }
            t->unk1C = (u32)t->unk1C + 1;
        }
        break;
    case 2:
        if (t->unk1C < 0x78) {
            t->unk1C = (u32)t->unk1C + 1;
        }
        func_8002D524();
        break;
    case 3:
        if (D_8076A0A8 == 0xE || D_8076A0A8 == 0x52) {
            func_8002D224(4);
            t->unk1C = 0x32;
        } else {
            cnt = (u64)(t->unk1C + 1);
            t->unk1C = cnt;
            if (cnt >= 0x78) {
                if (t->unk25 == 1) {
                    func_8002D224(4);
                    t->unk1C = 0x32;
                } else {
                    func_8002D224(6);
                }
            }
        }
        break;
    case 4:
        if (t->unk1C != 0) {
            t->unk1C = t->unk1C - 1;
        } else {
            list0 = t->unk20;
            i = 0;
            list = list0;
            if (t->unk1E > 0) {
                do {
                    s = list[i].unk4;
                    if (s->unk27 == 0) {
                        pa = (RaceFActorView *)D_807FC924[s->unk28].unk4;
                        scale = 1.0f;
                        pa->unk128 = 0xFF;
                        pa->unk60 |= 0x8000;
                        if (D_8076A0A8 == 0xB9) {
                            scale = 0.3f;
                        }
                        for (k = 0; k < 3; k++) {
                            (&pa->unk4->unk34)[k] = scale * 0.15;
                        }
                        pa->unkE8 = 0;
                        pa->unkE4 = 0;
                    }
                    i++;
                } while (i < t->unk1E);
            }
            func_8002D224(5);
        }
        break;
    }
    func_8002F950(t);
    if (func_807142D8() == 0) {
        if (D_807FBB40->unk154 > 0 && D_807FBB40->unk154 < 5) {
            renderCallbacksRegister((void *)func_8002CBEC, D_807FBB40, 3);
        }
    }
}
