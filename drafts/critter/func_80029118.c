// func_80029118 (src/critter/5110.c): stage 6 improved (fdiff score 890 -> 40; only remaining diff: the two global-address temps lui/lhu are v0 in ours, v1 in target at D_807FCC44 read (0x48) and D_80029FA4 read (case 0xFE)). Fix found: read D_807FCC44 through an alias symbol (extern u8 D_807FCC40[]; tmp = *(u16 *)&D_807FCC40[4]) into a u16 local so the address is no longer shared with the zero store (separate lui at); reloc-only difference (D_807FCC40+4 vs D_807FCC44). Frame needs 's32 pad88; u16 tmp;' instead of pad88[2]. Tried for v1: dropping/adding sp70 uses, alias read at 0x508, decl order: no effect.
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
                D_807FCC44 = D_80029FA4;
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
