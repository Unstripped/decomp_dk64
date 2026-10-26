// func_806F6F28 (src/global/F9450.c): Stage 4: 0x2F0-stride flag propagation behavior; target frame 0x48 vs draft 0x50.
typedef struct F9N6_FlagBlock {
    u8 pad0[0x1F4];
    s32 flags;
} F9N6_FlagBlock;

typedef struct F9N6_PlayerRef {
    u8 pad0[0x154];
    u8 unk154;
    u8 pad155[0x1F];
    F9N6_FlagBlock *unk174;
} F9N6_PlayerRef;

typedef struct F9N6_PlayerBlock {
    u8 pad0[4];
    F9N6_PlayerRef *unk4;
    u8 pad8[0x2E8];
} F9N6_PlayerBlock;

extern s32 D_807FBB64;
extern u8 D_807FD738;
void func_806F603C(void);
void func_806F69A8(u8);
s32 flagGet(s32, s32);
s32 func_806F6E58(s16);

void func_806F6F28(void) {
    u8 sp45;
    s32 temp_lo;
    s32 temp_t7;
    s32 var_fp;
    s32 var_s0;
    F9N6_FlagBlock *temp_v0;

    var_fp = 0;
    sp45 = 0;
    if (D_807FBB64 & 0x10000) {
        func_806F603C();
    }
    if (flagGet(0x179, 0) != 0) {
        var_fp = 1;
    }
    if (func_806F6E58(D_8074E77C[0]) != 0) {
        sp45 = 1;
    }
    var_s0 = 0;
    if (D_807FC928 > 0) {
        do {
            temp_lo = var_s0 * 0x2F0;
            temp_v0 = ((F9N6_PlayerBlock *)D_807FC924)[var_s0].unk4->unk174;
            if (var_fp != 0) {
                temp_v0->flags |= 1;
            } else {
                temp_v0->flags &= -2;
            }
            if (sp45 != 0) {
                temp_v0->flags |= 2;
            } else {
                temp_v0->flags &= -3;
            }
            if ((((F9N6_PlayerBlock *)D_807FC924)[var_s0].unk4->unk154 != 0x36) && (D_807FD738 == 0)) {
                func_806F69A8(var_s0 & 0xFF);
            }
            temp_t7 = (var_s0 + 1) & 0xFF;
            var_s0 = temp_t7;
        } while (temp_t7 < D_807FC928);
    }
}
