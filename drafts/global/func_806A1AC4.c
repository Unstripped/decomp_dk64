// func_806A1AC4 (src/global/A6280.c): stage 4: frame 0x58 vs 0x50 (one extra unused slot before cb at 0x44 vs 0x40); +2 instrs (sll/sra sign-extend of i at func_80714950 call); double conversion now cvt.d.w (speed = intExpr * 0.01); dz inlined; i s16; cb spilled
extern Actor *D_807FBB40;
extern Actor *D_807FBB4C;


extern s32 D_8076A064;
extern s32 D_8071FFA0;
extern ActorGlobalState D_807FBB70;

void func_80728950(s32);
void actorSetUniformScale(Actor *, f32);
s32 flagGet(s16, s32);
void func_80614EBC(Actor *, s32);
void currentActorAnimSetFrame(s32, s32);
void func_8070DA74(Actor *);
void func_8070D8C0(Actor *, s32, s32);
void func_8061CC40(Actor *, s32, s32);
void flagSet(s32, s32, s32);
s32 func_80611A44(void);
void func_8071498C(void *);
void func_80714950(s16);
void func_807149B8(s32);
void func_807149C8(s32, s32, s32, s32);
void func_80714998(s32);
void func_80714CC0(void *, f32, f32, f32, f32);
void func_8072881C(s32, void *);
void func_8071E864(void);

void func_80613C48(Actor *, s16, f32, f32);

void func_806A1AC4(void) {
    s16 i;
    void *cb;
    f32 dx;
    f32 speed;

    if (!(D_807FBB40->unk60 & 0x10)) {
        D_807FBB40->unk60 &= ~0x8000;
        func_80728950(0);
        actorSetUniformScale(D_807FBB40, 1.2f);
        D_807FBB40->unk60 |= 0x400;
        D_807FBB40->unk12A = 0x3E8;
        if (flagGet(0xFB, 0) != 0) {
            func_80613C48(D_807FBB40, 0x597, 0.0f, 0.0f);
            currentActorAnimSetFrame(0, 0);
            D_807FBB40->unk154 = 3;
        } else {
            func_80613C48(D_807FBB40, 0x598, 0.0f, 0.0f);
            func_80614D00(D_807FBB40, 0.0f, 0.0f);
            D_807FBB40->unk144 = 1;
            D_807FBB40->unk60 &= ~4;
        }
    }
    switch (D_807FBB40->unk154) {
    case 0:
        if (D_807FBB70.unk254 != 0 && D_807FBB70.unk258[0] == 1) {
            func_8070DA74(D_807FBB40);
            func_8070D8C0(D_807FBB40, 0x1F, 1);
            func_8061CC40(D_807FBB40, 0x12, 1);
            flagSet(0xFB, 1, 0);
            D_807FBB40->unk154 = 1;
        } else if (flagGet(0xFB, 0) == 0 && flagGet(0x21, 2) == 0) {
            dx = D_807FBB40->unk7C - D_807FBB4C->unk7C;
            if (dx * dx + (D_807FBB40->unk84 - D_807FBB4C->unk84) * (D_807FBB40->unk84 - D_807FBB4C->unk84) < 19600.0f) {
                func_8070D8C0(D_807FBB4C, 0x1F, 0);
                flagSet(0x21, 1, 2);
            }
        }
        break;
    case 1:
        if (D_807FBB70.unk254 != 0 && D_807FBB70.unk258[0] == 1) {
            func_80614EBC(D_807FBB40, 0x328);
            D_807FBB40->unk154 = 2;
            D_807FBB40->unk144 = 2;
            D_807FBB40->unk60 |= 4;
        }
        break;
    case 2:
        switch (D_807FBB40->unk155[0]) {
        case 0:
            if (!(D_8076A064 & 7)) {
                cb = (void *)func_8071E864;
                for (i = 0; i < 0xC; i++) {
                    speed = (((func_80611A44() >> 15) % 32767) % 171 + 0x96) * 0.01;
                    func_8071498C(cb);
                    func_80714950(i);
                    func_807149B8(1);
                    func_807149C8(0x8C, 0x8C, 0x8C, 0xFF);
                    func_80714998(5);
                    func_80714CC0(&D_8071FFA0, speed, D_807FBB40->unk7C, D_807FBB40->unk80 + 50.0f, D_807FBB40->unk84);
                }
            }
            break;
        case 2:
            currentActorAnimSetFrame(0, 0);
            D_807FBB40->unk155[0]++;
            break;
        case 4:
            currentActorAnimSetFrame(0, 2);
            D_807FBB40->unk155[0]++;
            break;
        case 6:
            currentActorAnimSetFrame(0, 0);
            D_807FBB40->unk154++;
            break;
        }
        break;
    case 3:
        func_8072881C(0, (u8 *)D_807FBB40 + 0xEC);
        break;
    }
    func_806319C4(D_807FBB40, 0);
}
