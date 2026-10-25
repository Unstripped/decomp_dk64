// func_806F1048 (src/global/F56F0.c): Stage 3 behavioral draft from control-flow recovery; switch case scheduling remains unmatched.
typedef struct F5AActorExtra {
    u8 pad0[0x1F0];
    s32 flags;
} F5AActorExtra;

void func_80613214(void);
void func_806C8D20(Actor *);
extern Actor *D_807FBB40;

void func_806F1048(Actor *arg0) {
    F5AActorExtra *extra = arg0->unk174;

    switch (arg0->unk58) {
    case 4:
    case 0xC6:
        extra->flags &= ~0x100;
    case 3:
    case 5:
    case 6:
    case 0xC5:
    case 0xC7:
    case 0xC8:
        if (!(extra->flags & 0x40)) {
            func_80613214();
        }
        break;
    }
    func_806C8D20(D_807FBB40);
}
