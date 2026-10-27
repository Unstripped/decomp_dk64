// func_80029118 (src/critter/5110.c): stage 6, score 20 (park in src now = draft). Last pair: case 0xFE 'lui v0,%hi(D_80029FA4); lhu a2' is v0, target v1. Mechanism (cc -S, .scratch/C0c6/S.sh): the lui reg is NOT a ring temp: as1 reuses the ORIGINAL destination of the lhu ('lhu $2,D_80029FA4; move $6,$2' -> lhu a2 + lui $2). So the value web must be coloured $3 (reg 2) not $2: value web (cand 147) is coloured first with reg 1 and tmp (merged webs bb2+bb81, 'and $3,$2,65535') takes reg 2 (that is what fixed the first read). To get v1 for both the single merged web needs reg 1 blocked in bb2 and the 0xFE join block by a higher-priority candidate; found none. Tried 96 combos (tmp u16/s16/s32/u32, arg D_80029FA4/tmp/(u16)tmp/(s32)tmp, store order, if(!tmp){} / if(tmp&&tmp){} dummies), tmp2 copies, z=0 first, tmp=0 after: none < 20. Merging first read into same web as arg gives v0 in both (40).
typedef struct Struct_807FBB40_174 {
    s16 unk0;
    u8 unk2;
    u8 pad3;
    s16 unk4;
    u8 unk5;
} Struct_807FBB40_174;

typedef struct Struct_807FBB40 {
    char pad0[0x60];
    s32 unk60;
    char pad64[0x11C - 0x64];
    struct Struct_807FBB40 *unk11C;
    char pad120[0x154 - 0x120];
    u8 unk154;
    char pad155[0x174 - 0x155];
    Struct_807FBB40_174 *unk174;
} Struct_807FBB40;

s32 critterBitwiseNot(s32 arg0);

extern s8 D_80029FA0;
extern u16 D_80029FA4;
extern s8 D_80029FA8;
extern u8 D_807444EC;
extern u8 D_807655F0[];
extern s32 D_8076A0A8;
extern u8 D_807ECE00[];
extern Struct_807FBB40 *D_807FBB40;
extern u16 D_807FCC44;
extern u8 D_807FCC40[];

void camStartPath(s32, s32, s32);
void func_806F8A8C(s32, s32, s32);
s32 camIsPathPaused(void);
void func_8070D8C0(void *, s32, s32);
void func_806A2A10(s32, s32, s32);
void camResumePath(void);
void actorSetStateTwo(void *);
void sfxAllocateChannel(s32, f32);
void flagSet(s16, s32, s32);
s32 func_806FDB8C(s32, char *, s32, f32, f32, f32);
void func_80609140(s32, s32, f32, f32, s32, s32);
void func_805FF800(s32 *, s32 *);
void func_805FF628(s32, s32);
void renderCallbacksRegister(void *, void *, s32);
Gfx *func_800296DC(Gfx *, Struct_807FBB40 *);

void func_80029118(void) {
    s32 pad88;
    u16 tmp;
    Struct_807FBB40_174 *temp_s0;
    s32 *var_s0;
    void (*temp_v1)(void *, s32);
    s32 temp_t3;
    s32 sp74;
    s32 sp70;
    s32 sp58[6];
    s32 pad54;
    s32 sp50;
    s32 pad40[4];
    s32 sp3C;
    s32 sp38;
    temp_s0 = D_807FBB40->unk174;
    if (!(D_807FBB40->unk60 & 0x10)) {
        D_80029FA8 = 0;
        camStartPath(0, 0, 1);
        tmp = *(u16 *)&D_807FCC40[4];
        D_80029FA4 = tmp;
        D_807FCC44 = 0;
        func_806F8A8C(4, 0, 0);
        switch (D_8076A0A8) {
        case 0xB1:
            temp_s0->unk4 = 0x3C;
            D_80029FA0 = 1;
            break;
        case 0xB6:
            temp_s0->unk4 = 0x3C;
            D_80029FA0 = 1;
            break;
        case 0xB4:
            temp_s0->unk4 = 0x3C;
            D_80029FA0 = 5;
            break;
        case 0xB5:
            temp_s0->unk4 = 0x3C;
            D_80029FA0 = 5;
            break;
        }
        D_807FBB40->unk154 = 0;
    }

    switch (D_807FBB40->unk154) {
    case 0x0:
        if ((D_807444EC == 1) && (camIsPathPaused() != 0)) {
            switch (D_8076A0A8) {
            case 0xB1:
                sp74 = 0;
                break;
            case 0xB6:
                sp74 = 1;
                break;
            case 0xB4:
                sp74 = 2;
                break;
            case 0xB5:
                sp74 = 3;
                break;
            }
            func_8070D8C0(D_807FBB40, 0x19, *(u8 *)((char *)&sp74 + 3));
            D_807FBB40->unk154 = 1;
            func_806A2A10(0xDC, 0x2A, ((u8 *)temp_s0)[5]);
        }
        break;
    case 0x1:
        if (!(D_807FBB40->unk60 & 0x02000000)) {
            camResumePath();
            D_807FBB40->unk154 = 2;
            actorSetStateTwo(D_807FBB40->unk11C);
            sfxAllocateChannel(8, 1.0f);
        }
        break;
    case 0x2:
        var_s0 = sp58;
        if ((s32)var_s0 & 7) {
            do {
                var_s0 = (s32 *)((char *)var_s0 + 4);
            } while ((s32)var_s0 & 7);
        }
        temp_v1 = (void (*)(void *, s32))critterBitwiseNot(~(s32)osWritebackDCache);
        if (D_80029FA0 <= 0) {
            D_807FBB40->unk154 = 3;
        }
        temp_v1(var_s0, 0x10);
        sp50 = critterBitwiseNot(-0xDC1);
        ((void (*)(void *, s32, s32, s32, void *, s32, void *))critterBitwiseNot(~(s32)osPiStartDma))(&D_807ECE00, 0, 0, sp50, var_s0, 0x10, &D_807655F0);
        if (D_807FBB40->unk11C->unk154 == 5) {
            D_807FBB40->unk154 = 0xFF;
        }
        ((void (*)(void *, s32, s32))critterBitwiseNot(~(s32)osRecvMesg))(&D_807655F0, 0, 1);
        ((void (*)(void *, s32))critterBitwiseNot(~(s32)osInvalDCache))(var_s0, 0x10);
        var_s0[0] += var_s0[1];
        if (var_s0[0] != 0x0A78F00E) {
            flagSet((D_8076A0A8 == 0xB6) ? 0x184 : 0x183, 0, 0);
        }
        break;
    case 0x3:
        D_807FBB40->unk11C->unk154 = 1;
        temp_s0->unk2 = func_806FDB8C(1, "WELL DONE!", 2, 160.0f, 100.0f, 0.0f);
        func_80609140(0x143, 0x7FFF, 63.0f, 1.0f, 0, 0);
        temp_s0->unk0 = 0x78;
        D_807FBB40->unk154 = 0xFE;
        D_80029FA8 = 1;
        break;
    case 0xFE:
        if (temp_s0->unk0 > 0) {
            temp_s0->unk0--;
            if (temp_s0->unk0 == 0) {
                if (D_80029FA8 != 0) {
                    if (D_8076A0A8 == 0xB4) {
                        D_80029FA4 = 0x14;
                    }
                    switch (D_8076A0A8) {
                    case 0xB1:
                        sp70 = 0x182;
                        break;
                    case 0xB6:
                        sp70 = 0x183;
                        break;
                    case 0xB4:
                        sp70 = 0x184;
                        break;
                    case 0xB5:
                        sp70 = 0x185;
                        break;
                    }
                    flagSet(sp70, 1, 0);
                }
                tmp = D_80029FA4;
                D_807FCC44 = tmp;
                func_806F8A8C(4, 0, D_80029FA4);
                func_805FF800(&sp3C, &sp38);
                func_805FF628(sp3C, 0);
            }
        }
        break;
    case 0xFF:
        D_80029FA8 = 0;
        if (sp70 && sp70) {
        }
        temp_s0->unk2 = func_806FDB8C(1, "TIME OUT!", 2, 160.0f, 100.0f, 0.0f);
        temp_s0->unk0 = 0x78;
        D_807FBB40->unk154 = 0xFE;
        break;
    }
    renderCallbacksRegister(&func_800296DC, D_807FBB40, 3);
}
