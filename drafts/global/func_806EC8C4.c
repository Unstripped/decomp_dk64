// func_806EC8C4 (src/global/EFDC0.c): EfN3: text-identical switch reconstruction; relocation remains against jtbl_8075D3A4.
typedef struct EfN3PlayerState {
    u8 pad0[0x1B0];
    struct EfN3Target *unk1B0;
    s32 unk1B4;
} EfN3PlayerState;

typedef struct EfN3Target {
    u8 pad0[0x54];
    s32 unk54;
    s32 unk58;
} EfN3Target;

typedef struct EfN3Actor {
    u8 pad0[0x154];
    u8 unk154;
    u8 unk155;
} EfN3Actor;

#define EFN3_P ((EfN3PlayerState *)D_807FD580)
#define EFN3_A48 ((EfN3Actor *)D_807FBB48)

extern Actor *D_807FBB90;

void func_806EC8C4(void) {
    EFN3_P->unk1B0 = (EfN3Target *)D_807FBB90;
    EFN3_P->unk1B4 = EFN3_P->unk1B0->unk54;
    switch ((u32)EFN3_P->unk1B0->unk58) {
    case 0x3D:
    case 0x3F:
    case 0x40:
    case 0x41:
    case 0x42:
    case 0x55:
    case 0x82:
        func_80614EBC(D_807FBB48, 0x1C8);
        break;
    default:
        func_80614E78(D_807FBB48, 0x2B);
        break;
    }
    EFN3_A48->unk154 = 0x47;
    EFN3_A48->unk155 = 0;
}
