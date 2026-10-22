// func_80685F60 (src/global/89250.c): from .scratch/Beh8923A/func_80685F60_best.c
typedef struct Beh8923A_Player_Data {
    u8 pad0[0x2C0];
    u8 unk2C0;
    u8 pad2C1[0x2F0 - 0x2C1];
} Beh8923A_Player_Data;

typedef struct Beh8923A_ActorUnk118 {
    u8 pad0[0x10];
    u16 unk10;
} Beh8923A_ActorUnk118;

typedef struct Beh8923A_Actor {
    void *unk0;
    ActorSub4 *unk4;
    u8 pad8[0x50];
    s32 unk58;
    u16 unk5C;
    u8 pad5E[2];
    u32 unk60;
    u32 unk64;
    u16 unk68;
    u16 unk6A;
    u16 unk6C;
    u8 pad6E[0xE];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
    u8 pad88[0x18];
    f32 unkA0;
    f32 unkA4;
    u8 padA8[0x4];
    f32 unkAC;
    u8 padB0[8];
    f32 unkB8;
    f32 unkBC;
    f32 unkC0;
    u8 padC4[0x54];
    Beh8923A_ActorUnk118 *unk118;
    u8 pad11C[0x42];
    u8 unk15E;
} Beh8923A_Actor;

extern Beh8923A_Player_Data *D_807FC924;
extern u8 D_807FC929;
extern s16 D_80753A08[];
extern s16 D_80753A18[];
extern u32 D_8076A064;

#define ACTOR ((Beh8923A_Actor *)arg0)
void func_80685F60(Actor *arg0) {
    f32 var_fv0;
    register u8 var_v1;

    var_v1 = 0;
    if (ACTOR->unk0 != NULL && ACTOR->unk4 != NULL) {
        if (ACTOR->unk5C == 1) {
            if (D_807FC924[D_807FC929].unk2C0 == 1) {
                var_fv0 = D_80753A08[ACTOR->unk58];
            } else {
                var_fv0 = D_80753A18[ACTOR->unk58];
            }
        } else {
            var_fv0 = (f32)(u32)ACTOR->unk15E;
        }
        if ((ACTOR->unkAC - var_fv0) <= ACTOR->unk80) {
            if (!(D_8076A064 & 3)) {
                if ((f64)ACTOR->unkB8 != 0.0) {
                    var_v1 = 1;
                }
                if (ACTOR->unk118 != NULL && ACTOR->unk118->unk10 != 0) {
                    var_v1 = 1;
                }
            }
            if (var_v1 != 0) {
                func_80714950(1);
            } else if (((f64)ACTOR->unkB8 == 0.0) && ((D_8076A064 % 24 == 0) || ((f64)ACTOR->unkBC != 0.0))) {
                var_v1 = 1;
            }
            if (var_v1 != 0) {
                func_80685E78(arg0);
            }
        }
    }
}
#undef ACTOR
