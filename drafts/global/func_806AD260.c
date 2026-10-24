// func_806AD260 (src/global/B1F60.c): M2 stage 4-5: structure matches (blocks, jump tables, K&R s16/u8/u16 params, first block incl. sll/sra a3 entry via 'actor = D_807FBB40' local inside the if, 3-arg func_8072D714, AB74 proto (s32,f32,f32,u16,f32)). Remaining diff regalloc/frame only: switch-operand temp D_807FBB40->unk154 lands in s0 (frame 0x28) where target keeps it in a0 with v0 = switch copy re-defined after each call (frame 0x20); pointer in a0 vs a2. Tried local state/sw vars, ANSI vs K&R, u8 first arg of AB74 (spills), permuter 240s no gain.
extern Actor *D_807FBB40;
void func_806AD260();

typedef struct {
    u8 pad0[0xC0];
    f32 unkC0;
} M2_ActorC0;

typedef struct {
    u8 pad0[0x28];
    s16 unk28;
    s16 unk2A;
} M2_View98;

extern ActorGlobalState D_807FBB70;
void func_8072D714(s32, s32, Actor *);
void func_8072AB74(s32, f32, f32, u16, f32);
void sfxSpawnTableNodes(Actor *);
void func_8072DC7C(s32);
void func_8072B7CC(s32);
void func_8072D13C(s32, s32);
void func_8072C918(s32, s32, s32);

void func_806AD260(arg0, arg1, arg2)
s16 arg0;
u8 arg1;
u16 arg2;
{
    Actor *actor;

    if (arg0 != 0 && (D_807FBB70.unk200 == 9 || D_807FBB70.unk15 != 0)) {
        actor = D_807FBB40;
        if (actor->unk154 != 0x37) {
            ((M2_ActorC0 *)actor)->unkC0 = 200.0f;
            func_8072D714(D_807FBB70.unk1FC, arg0, actor);
        }
    }
    switch (D_807FBB40->unk154) {
        case 1:
        case 0x10:
        case 0x15:
        case 0x23:
            func_8072AB74(D_807FBB40->unk154, D_807FDC94->unk7C, D_807FDC94->unk84, (D_807FBB40->unk6A & 1) ? arg2 : (arg2 | 2), 0.0f);
            break;
        case 2:
        case 3:
        case 7:
        case 0x35:
            func_8072AB74(D_807FBB40->unk154, (f32)D_807FDC90->unkA, (f32)D_807FDC90->unkE, arg2, 0.0f);
            break;
        case 0x37:
            switch (D_807FBB40->unk155[0]) {
                case 0:
                    func_8072AB74(0x37, 0.0f, 0.0f, (arg2 | 0x4200) & 0xFFFF, 0.0f);
                    break;
                case 1:
                    sfxSpawnTableNodes(D_807FBB40);
                    if (arg1 != 0) {
                        D_807FBB40->unk155[0] = 2;
                        break;
                    }
                    ((M2_ActorC0 *)D_807FBB40)->unkC0 = 100.0f;
                    D_807FBB40->unk155[0]++;
                case 2:
                    func_8072AB74(0x37, 0.0f, 0.0f, (arg2 | 0x4200) & 0xFFFF, 0.0f);
                    break;
                case 3:
                    func_8072DC7C(0xA);
                    break;
                case 4:
                    D_807FBB40->unk154 = 0x40;
                    break;
            }
            break;
        default:
            func_8072B7CC(((M2_View98 *)D_807FDC98)->unk28);
            break;
    }
    switch (D_807FBB40->unk154) {
        case 2:
        case 3:
            func_8072D13C(D_807FBB40->unk154, 1);
        default:
            func_8072C918(0x4C90, ((M2_View98 *)D_807FDC98)->unk28, ((M2_View98 *)D_807FDC98)->unk2A);
        case 0x37:
        case 0x40:
            break;
    }
}
