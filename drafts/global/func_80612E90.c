// func_80612E90 (src/global/17B90.c): stage 2: reconstructed entire function logic, asset loading, pointer relocation across split tail func_80613044 and downstream calls
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef short s16;
typedef int s32;
#define NULL ((void *)0)

typedef struct RvD2_StateEntry {
    u16 unk0;
    u16 unk2;
    void *unk4;
    u8 unk8;
} RvD2_StateEntry;

typedef struct RvD2_Asset {
    void *unk0;
    void **unk4;
    void *unk8;
    void *unkC;
    void *unk10;
    void *unk14;
    u8 pad18[8];
    u8 unk20;
    u8 unk21;
} RvD2_Asset;

extern RvD2_StateEntry D_807FB630[];
extern void *D_807FB634;
extern u16 D_807FBB30;
extern u16 D_807FBB32;
extern u8 D_80746B64[];

void animListInit(void *, void *);
void *assetLoad(s32, s32, s32, s32);
void func_8061324C(void *, void *, void *);
void renderReplaceSegment6Commands(void *, void *);
void func_806133C8(void *, void *);
void func_806130A4(void *, void *);

void *func_80612E90(void *arg0, s32 arg1, s32 arg2) {
    RvD2_StateEntry *entry;
    RvD2_Asset *asset;
    s32 delta;
    s32 i;
    s32 flag;

    flag = arg2 & 0xFF;
    i = 0;
    if ((s16)D_807FBB30 > 0) {
        entry = D_807FB630;
        do {
            i++;
            if (arg1 == entry->unk0 && flag == entry->unk8) {
                entry->unk2++;
                animListInit(arg0, entry->unk4);
                return entry->unk4;
            }
            entry++;
        } while (i < (s16)D_807FBB30);
    }

    if (D_807FBB32 >= 0x20) {
        return D_807FB634;
    }

    entry = &D_807FB630[i];
    asset = assetLoad(5, arg1 - 1, 1, 1);
    entry->unk0 = arg1;
    D_807FBB30++;
    entry->unk8 = flag;
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

    func_8061324C(*asset->unk4, asset->unk4, &asset->unk14);
    renderReplaceSegment6Commands(*asset->unk4, asset->unk4);
    func_806133C8(*asset->unk4, asset->unk4);
    animListInit(arg0, asset);

    if (flag & 1) {
        func_806130A4(*asset->unk4, asset->unk4);
    }

    return asset;
}
