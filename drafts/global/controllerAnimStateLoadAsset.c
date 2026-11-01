// func_80612E90 (src/global/17B90.c): stage 4: exact frame 0x40 and saved regs s0-s2,ra; (u16)D_807FBB30 and (u16)D_807FBB32 matched entry lhu/blez/slti; remaining diff is loop pointer scheduling
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef short s16;
typedef int s32;
#define NULL ((void *)0)

typedef struct CtrlB_R2_StateEntry {
    u16 unk0;
    u16 unk2;
    void *unk4;
    u8 unk8;
} CtrlB_R2_StateEntry;

typedef struct CtrlB_R2_Asset {
    void *unk0;
    void **unk4;
    void *unk8;
    void *unkC;
    void *unk10;
    void *unk14;
    u8 pad18[8];
    u8 unk20;
    u8 unk21;
} CtrlB_R2_Asset;

extern CtrlB_R2_StateEntry D_807FB630[];
extern void *D_807FB634;
extern u16 D_807FBB30;
extern u16 D_807FBB32;
extern u8 D_80746B64[];

void animListInit(void *, void *);
void *assetLoad(s32, s32, s32, s32);
void controllerBuildSubcommandList(void *, void *, void *);
void renderReplaceSegment6Commands(void *, void *);
void controllerCommandRelocateAssets(void *, void *);
void func_806130A4(void *, void *);

void *func_80612E90(arg0, arg1, arg2)
void *arg0;
s32 arg1;
unsigned char arg2;
{
    s32 i;
    CtrlB_R2_StateEntry *entry;
    CtrlB_R2_Asset *asset;
    register s32 delta;

    i = 0;
    if ((s32)(u16)D_807FBB30 > 0) {
        entry = D_807FB630;
        do {
            i++;
            if (arg1 == entry->unk0 && entry->unk8 == arg2) {
                entry->unk2++;
                animListInit(arg0, entry->unk4);
                return entry->unk4;
            }
            entry++;
        } while (i < (u16)D_807FBB30);
    }

    if ((u16)D_807FBB32 >= 0x20) {
        return D_807FB634;
    }

    entry = &D_807FB630[i];
    asset = (CtrlB_R2_Asset *)assetLoad(5, arg1 - 1, 1, 1);
    entry->unk0 = arg1;
    D_807FBB30 = (u16)D_807FBB30 + 1;
    entry->unk8 = arg2;
    entry->unk2 = 1;
    entry->unk4 = asset;

    delta = ((u8 *)asset - (u8 *)asset->unk0) + 0x28;
    asset->unk0 = (u8 *)asset->unk0 + delta;
    asset->unk4 = (void **)((u8 *)asset->unk4 + delta);

    if (asset->unk21 > 0) {
        for (i = 0; i < asset->unk21; i++) {
            asset->unk4[i] = (u8 *)asset->unk4[i] + delta;
        }
    }

    if (asset->unk8 != NULL) {
        asset->unk8 = (u8 *)asset->unk8 + delta;
    } else {
        asset->unk8 = D_80746B64;
        asset->unk20 = 1;
    }

    asset->unkC = (u8 *)asset->unkC + delta;
    asset->unk10 = (u8 *)asset->unk10 + delta;

    controllerBuildSubcommandList(*asset->unk4, asset->unk4, &asset->unk14);
    renderReplaceSegment6Commands(*asset->unk4, asset->unk4);
    controllerCommandRelocateAssets(*asset->unk4, asset->unk4);
    animListInit(arg0, asset);

    if (arg2 & 1) {
        func_806130A4(*asset->unk4, asset->unk4);
    }

    return asset;
}
