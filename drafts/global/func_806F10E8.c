// func_806F10E8 (src/global/F56F0.c): Stage 3 draft reconstructed from switch-table assembly; compiler switch lowering and structure ownership remain unmatched.
typedef struct F5AActorState {
    u8 pad0[0x58];
    s32 state;
    u8 pad5C[0x88];
    s16 unkE4;
    s16 unkE8;
} F5AActorState;

typedef struct F5AActorSub38 {
    u8 pad0[0x38];
    f32 unk38;
} F5AActorSub38;

void func_806F0C18(Actor *);
Actor *actorSpawn(s32, s32);
void func_8067B238(Actor *, Actor *, f32);
void func_80613194(Actor *, s32);
extern Actor *D_807FBB44;

void func_806F10E8(Actor *arg0) {
    switch (((F5AActorState *)arg0)->state) {
    case 2:
    case 0xC4:
        func_806F0C18(arg0);
        actorSpawn(0xEF, 0xA6);
        func_8067B238(D_807FBB44, arg0, ((F5AActorSub38 *)arg0->unk4)->unk38 * 1.25f);
        ((F5AActorState *)D_807FBB44)->unkE4 = ((F5AActorState *)arg0)->unkE4;
        ((F5AActorState *)D_807FBB44)->unkE8 = ((F5AActorState *)arg0)->unkE8;
        D_807FBB44->unk60 |= 0x40000000;
        break;
    case 3:
    case 0xC5:
        func_806F0C18(arg0);
        func_80613194(arg0, 2);
        break;
    case 4:
    case 0xC6:
        func_806F0C18(arg0);
        func_80613194(arg0, 7);
        break;
    case 5:
    case 0xC7:
        func_806F0C18(arg0);
        func_80613194(arg0, 10);
        break;
    case 6:
    case 0xC8:
        func_806F0C18(arg0);
        func_80613194(arg0, 13);
        break;
    }
}
