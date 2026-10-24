// func_806A18A8 (src/global/A6280.c): stage 6: 1 instruction pair off. 212 instrs identical except: the 'unk64 != 0x233' exit emits 'beq t7,at,<join>' + nop where ROM has 'beql t7,at,<else-if test>' + 'c.le.s f0,f2'. Everything else (frame 0x48, s0, both c.le.s delay-slot dups, one mtc1 of 50.0f in f2, b join) matches. Tried: plain else, else{if}, separate ifs (gets beql->else-test but rematerialises 50.0f and no f2 reuse), negated test, local limit var, literal-first, explicit byte offset, do{...}while(0) and block wraps around the inner if/body; permuter 240s found nothing better than base. Emits an 8-byte jr ra;nop pad at 0x806A1ABC: add 'static void stub_806A1ABC(void) {}' after the function
typedef struct M6ActorView {
    u8 pad0[0x178];
    void *unk178;
} M6ActorView;

typedef struct M6Sub178 {
    u8 unk0;
    u8 unk1;
} M6Sub178;

typedef struct M6Sub11C {
    u8 pad0[0xB8];
    f32 unkB8;
} M6Sub11C;

typedef struct M6Sub4 {
    u8 pad0[0x64];
    u16 unk64;
} M6Sub4;

void func_806319C4(Actor *, s32);
void func_80724CA4(s32, s32);
void func_8067B238(Actor *, void *, f32);
void actorUpdatePulseIntensity(s32);
void func_80614EBC(Actor *, s32);
void func_80614D00(void *, f32, f32);
void func_8065D254(void *, s32, s32, s32, s32, s32, s32, s32, s32, s32, f32);

void func_806A18A8(void) {
    M6Sub178 *sp44;
    M6Sub11C *sp40;

    sp44 = ((M6ActorView *)D_807FBB40)->unk178;
    sp40 = (M6Sub11C *)D_807FBB40->unk11C;
    if (!(D_807FBB40->unk60 & 0x10)) {
        func_80724CA4(2, 2);
    }
    func_8067B238(D_807FBB40, sp40, 0.15f);
    if (D_807FBB40->unk154 != 0) {
        actorUpdatePulseIntensity(1);
        if (sp44->unk1 == 0) {
            D_807FBB40->unk154 = 0;
        }
    }
    if (0.0f != sp40->unkB8) {
        if (sp40->unkB8 > 50.0f) {
            if (((M6Sub4 *)D_807FBB40->unk4)->unk64 != 0x233) {
                func_80614EBC(D_807FBB40, 0x233);
            }
        } else if (50.0f >= sp40->unkB8) {
            if (((M6Sub4 *)D_807FBB40->unk4)->unk64 != 0x232) {
                func_80614EBC(D_807FBB40, 0x232);
            }
        }
        func_80614D00(D_807FBB40, sp40->unkB8 * 0.01, 4.0f);
    } else {
        if (((M6Sub4 *)D_807FBB40->unk4)->unk64 != 0x234) {
            func_80614EBC(D_807FBB40, 0x234);
        }
    }
    func_8065D254(D_807FBB40, 0x3C8, 0x40, 0x40, 0xA, 0xA, 1, 0x12C, 0xC8, 0, 1.0f);
    func_806319C4(D_807FBB40, 0);
}
