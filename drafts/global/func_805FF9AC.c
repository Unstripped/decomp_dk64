// func_805FF9AC (src/global/3C10.c): TEXT-IDENTICAL (permuter score 0, fdiff 'code matches'); only .rodata differs: the 255.0 double (D_80756680, currently in 14C450.data.s) is a literal of this TU's .rodata (extern f64 gives f0+spill, literal hoists to $f20). Needs rodata carve of 3C10 (D_807565E0/D_80756630 tables + 255.0 before jump tables). Uses locals order cam,sp50,i,found,k,r,g,b,pad(unused slot word),obj; no slot var: D_8076A160[i] everywhere; 'k = 1; D_80750ACC = k; ... D_8076A160[i].unk0 = k' shares constant 1
typedef struct {
    s32 unk0;
    s32 unk4;
} MainLoopPair;

typedef struct {
    u8 pad0[0x58];
    s32 unk58;
} MainLoopView58;

extern MainLoopPair D_80744800[];

typedef struct {
    u8 pad0[0x24];
    u8 rgb[52][3];
} MainLoopSlotColors;

typedef struct {
    u8 pad0[0x1AC];
    MainLoopView58 *unk1AC;
    u8 pad1B0[0x1F0 - 0x1B0];
    s32 unk1F0;
} MainLoopObj;

typedef struct {
    u8 pad0[0x174];
    MainLoopObj *unk174;
} MainLoopHolder;

extern s8 D_80750ACC;
extern const f64 D_80756680;
extern s32 D_807F6C28;
extern s32 D_807FD56C;
extern s16 D_807FD570;
void func_805FFEF8(s32);
void func_806F5378();
void func_806115A8(u8 **);
void func_8063B8D8(u8 **, s32 *);
void modelSlotsPackRecords(u8 **, s32 *);
void lightGetColor(f32 *, f32 *, f32 *, s16);
void faultSetMessage(s32, s32, s32, s32);

void func_805FF9AC(s32 arg0, s32 arg1, s32 arg2, s16 arg3) {
    Struct807FBB4C *cam;
    s32 sp50;
    s32 i;
    s32 found;
    s32 k;
    f32 r;
    f32 g;
    f32 b;
    s32 pad;
    MainLoopObj *obj;

    found = 0;
    i = 0;
    while (i < 18 && !found) {
        if (D_8076A160[i].unk0 != 0 && D_8076A0A8 == D_8076A160[i].unk12) {
            found = 1;
        } else {
            i++;
        }
    }
    if (found) {
        func_805FFEF8(D_8076A0A8);
    } else {
        found = 0;
        i = 0;
        while (i < 18 && !found) {
            if (D_8076A160[i].unk0 == 0) {
                found = 1;
            } else {
                i++;
            }
        }
        if (!found) {
            faultSetMessage(0xA, 0, 0, 0);
        }
    }
    func_806F5378();
    func_8063B8D8((u8 **)&D_8076A160[i].unk18, &sp50);
    func_806115A8((u8 **)&D_8076A160[i].unk18);
    modelSlotsPackRecords((u8 **)&D_8076A160[i].unk20, (s32 *)&D_8076A160[i].unk1C);
    if (D_8076A160[i].unk20 != 0) {
        func_806115A8((u8 **)&D_8076A160[i].unk20);
    }
    D_8076A160[i].unk2 = arg3;
    if (arg3 & 1) {
        cam = D_807FBB4C;
        D_8076A160[i].unk4 = cam->unk7C;
        D_8076A160[i].unk8 = cam->unk80;
        D_8076A160[i].unkC = cam->unk84;
        D_8076A160[i].unk10 = cam->unkE6;
    }
    D_8076A160[i].unk12 = D_8076A0A8;
    if (arg3 & 2) {
        D_8076A160[i].unk14 = arg2;
    }
    for (k = 0; k < D_807F6C28; k++) {
        lightGetColor(&r, &g, &b, k);
        ((MainLoopSlotColors *)&D_8076A160[i])->rgb[k][0] = (u32)(r * 255.0);
        ((MainLoopSlotColors *)&D_8076A160[i])->rgb[k][1] = (u32)(g * 255.0);
        ((MainLoopSlotColors *)&D_8076A160[i])->rgb[k][2] = (u32)(b * 255.0);
    }
    k = 1;
    D_80750ACC = k;
    obj = ((MainLoopHolder *)D_807FBB4C)->unk174;
    D_807FD56C = obj->unk1F0;
    if (obj->unk1AC != NULL) {
        D_807FD570 = obj->unk1AC->unk58;
    } else {
        D_807FD570 = 0;
    }
    D_8076A160[i].unk0 = k;
    func_805FF378(arg0, arg1);
}
