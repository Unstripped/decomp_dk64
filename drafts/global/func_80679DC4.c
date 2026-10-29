// func_80679DC4 (src/global/7CA80.c): stage 5: 182 insns, frame 0x40, score 44 with dead statement, regalloc only (a2 vs a3, temp registers)
struct R2CEntry2F0;
extern struct R2CEntry2F0 *D_807FC924;

typedef struct KaN2_Entry2F0 {
    u8 pad0[0x2C0];
    u8 unk2C0;
    u8 pad2C1[0x2F0 - 0x2C1];
} KaN2_Entry2F0;

typedef struct KaN2_StructD580 {
    u8 pad0[0x1A4];
    u8 unk1A4;
    u8 pad1A5[0x1F0 - 0x1A5];
    u32 unk1F0;
    u8 pad1F4[0x200 - 0x1F4];
    u16 unk200;
} KaN2_StructD580;
extern KaN2_StructD580 *D_807FD580;

extern u8 D_807FBB85;
extern s32 D_80720E2C;
void func_80686CF8(Actor *);
s32 func_80714608(s32);
s32 func_806D0DE4(Actor *, Actor *, s32);
void func_807149FC(s32);
void func_807149B8(s32);
void func_8071498C(void *);
void func_80714C08(void *, s32, Actor *, s32, s32);
void effectPulseSpinUpdate(void);

void func_80679DC4(Actor *arg0, Actor *arg1, s32 arg2) {
    s32 sp3C;
    s32 var_a2;
    void *sp24;
    s32 temp_a3;
    s32 var_v0;

    temp_a3 = arg2 & 0xFF;
    D_807FBB85 = 1;
    if (arg0 == D_807FBB48) {
        var_a2 = 1;
        if (((KaN2_Entry2F0 *)D_807FC924)[D_807FD580->unk1A4].unk2C0 == 2 && arg1 != NULL && (arg1->unk5C & 2)) {
            return;
        }
        sp3C = 0x2E;
        if (temp_a3 != 0) {
            sp3C = 0x30;
        }
        if (arg1 != NULL && arg1->unk58 == 0x116) {
            func_80686CF8(arg0);
            switch (arg1->unk155[0]) {
            case 1:
                var_a2 = 0;
                D_807FD580->unk1F0 ^= 0x80;
                break;
            case 2:
                sp3C = 0x27;
                break;
            case 3:
                func_807149FC(0xF0);
                func_807149B8(1);
                sp24 = &effectPulseSpinUpdate;
                func_8071498C(&effectPulseSpinUpdate);
                func_80714C08(&D_80720E2C, 0x3ECCCCCD, arg0, 1, 2);
                func_807149FC(0xF0);
                func_807149B8(1);
                func_8071498C(sp24);
                func_80714C08(&D_80720E2C, 0x3EC28F5C, arg0, 5, 2);
                func_807149FC(0xF0);
                func_807149B8(1);
                func_8071498C(sp24);
                func_80714C08(&D_80720E2C, 0x3E99999A, arg0, 6, 2);
                var_a2 = 0;
                D_807FD580->unk1F0 |= 0x08000000;
                break;
            }
            D_807FD580->unk200 = 0xF0;
        } else if (arg1 != NULL && ((arg1->unk5C & 1) || (arg1->unk5C & 4) || (arg1->unk5C & 2))) {
            if (D_807FD580 == 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
            if (func_80714608(0) != 0) {
                if (func_806D0DE4(arg0, arg1, var_a2) != 0) {
                    sp3C = 0x31;
                } else {
                    var_v0 = 1;
                    if (arg1->unk5C & 4) {
                        var_v0 = 3;
                    }
                    if (arg1->unk154 != 0x28 && var_v0 < 3) {
                        sp3C = 0x2B;
                    } else {
                        sp3C = 0xE;
                    }
                }
            }
        }
        if (var_a2 != 0) {
            playerStateQueueCallback((s16)sp3C, (s32)arg1, D_807FC929);
        }
    }
}
