// func_80613358 (src/global/17B90.c): stage 4; typed candidate has correct code size/control flow. Remaining temporary-register allocation around the two word comparisons.
typedef struct { u32 unk0; u32 unk4; } P17c3Command;
typedef struct { P17c3Command *unk0; } P17c3CommandArray;
typedef struct { u8 pad0[4]; P17c3CommandArray *unk4; } P17c3CommandStorage;
typedef struct { P17c3CommandStorage *unk0; u8 pad4[0x5C]; u32 unk60; } P17c3CommandOwner;

void func_80613358(P17c3CommandOwner *arg0, s32 arg1, P17c3Command *arg2) {
    P17c3Command *temp_a0;
    if (!(arg0->unk60 & 0x10)) {
        temp_a0 = arg0->unk0->unk4->unk0 + arg1;
        if ((temp_a0->unk0 != arg2->unk0) || (temp_a0->unk4 != arg2->unk4)) {
            memcpy(temp_a0, arg2, 8);
        }
    }
}
