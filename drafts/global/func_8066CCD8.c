// func_8066CCD8 (src/global/70FD0.c): Closest diff: frame 0x18 matched, 0x90 struct, minor delay slot / regalloc on a0
typedef struct M70A_Struct_C904 {
    u8 pad0[0x10];
    s32 unk10;
    u8 unk14;
    u8 unk15;
    u8 pad16[2];
    void *unk18;
    u8 pad1C[4];
} M70A_Struct_C904;
typedef struct M70A_SubStruct_48 {
    u8 pad0[8];
    s32 unk8;
    u8 padC[0x18];
    u8 unk24;
    u8 pad25[3];
} M70A_SubStruct_48;
typedef struct M70A_Struct_CCD8 {
    u8 pad0[0x28];
    M70A_Struct_C904 unk28;
    M70A_SubStruct_48 unk48;
    u8 pad70[0x20];
} M70A_Struct_CCD8;

extern s32 D_80747D70;
extern s16 D_80748E40;
extern s32 D_8076A064;
extern M70A_Struct_CCD8 *D_807F6000;
void func_806348B4(M70A_SubStruct_48 *);

void func_8066CCD8(void) {
    M70A_Struct_CCD8 *entry;
    void *a0;
    s32 count = D_80747D70;

    if (count != 0) {
        D_80748E40++;
        if (D_80748E40 >= count) {
            D_80748E40 = 0;
        }
        entry = &D_807F6000[D_80748E40];
        a0 = &entry->unk28;
        if ((((M70A_Struct_C904 *)a0)->unk15 & 1) && ((u32)(D_8076A064 - ((M70A_Struct_C904 *)a0)->unk10) >= 0x1F)) {
            func_8066C904(a0);
            entry = &D_807F6000[D_80748E40];
        }
        a0 = &entry->unk48;
        if ((((M70A_SubStruct_48 *)a0)->unk24 & 1) && ((u32)(D_8076A064 - ((M70A_SubStruct_48 *)a0)->unk8) >= 0x1F)) {
            func_806348B4(a0);
        }
    }
}
