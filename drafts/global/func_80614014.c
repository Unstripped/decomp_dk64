// func_80614014 (src/global/17B90.c): stage 3: semantic starter compiles; target homes all three arguments in a 0x30 frame and branch-likely forwards arg1, while draft uses a 0x20 frame; field-store order needs tuning.
typedef struct { f32 unk0; u16 unk4; u8 pad6[0xC]; u8 unk12; } P17LResource;
typedef struct { void *unk0; u8 pad4[0xC]; } P17LSlot;
typedef struct { void *unk0; P17LSlot *unk4; } P17LAnim;
typedef struct { void *unk0; P17LAnim *unk4; } P17LController;
void func_80613944(P17LController *, void *);
P17LResource *func_80614130(u16);
void func_80614644(P17LController *, P17LSlot *, s32);
void func_80614014(P17LController *arg0, u16 arg1, s32 arg2, u8 arg3) {
    P17LSlot *slot;
    P17LResource *resource;
    slot = arg0->unk4->unk4;
    if (slot->unk0 != NULL) func_80613944(arg0, slot);
    resource = func_80614130(arg1);
    if (resource != NULL) {
        slot->unk0 = resource;
        *(s16 *)((u8 *)slot + 0x10) = arg1;
        *(f32 *)((u8 *)slot + 0x14) = 0.0f;
        *(u16 *)((u8 *)slot + 0x1C) = resource->unk4;
        *(f32 *)((u8 *)slot + 0x34) = 0.0f;
        *(f32 *)((u8 *)slot + 0x18) = (f32)(resource->unk12 - 1);
        *(f32 *)((u8 *)slot + 0x24) = resource->unk0;
        *(f32 *)((u8 *)slot + 0x2C) = resource->unk0;
        *(f32 *)((u8 *)slot + 0x30) = 0.0f;
        *(f32 *)((u8 *)slot + 0x28) = resource->unk0;
        *(s16 *)((u8 *)arg0->unk4 + 0x28) = 0;
        *(s16 *)((u8 *)arg0->unk4 + 0x2C) = 0xFF;
        *(s16 *)((u8 *)arg0->unk4 + 0x2E) = arg3;
    } else {
        slot->unk0 = NULL;
        *(s16 *)((u8 *)slot + 0x10) = -1;
        *(u16 *)((u8 *)slot + 0x1C) = 0;
        *(f32 *)((u8 *)slot + 0x14) = 0.0f;
        *(f32 *)((u8 *)slot + 0x34) = 0.0f;
        *(f32 *)((u8 *)slot + 0x24) = 0.0f;
        *(f32 *)((u8 *)slot + 0x2C) = 0.0f;
        *(f32 *)((u8 *)slot + 0x28) = 0.0f;
        *(f32 *)((u8 *)slot + 0x30) = 0.0f;
        *(f32 *)((u8 *)slot + 0x18) = 0.0f;
    }
    func_80614644(arg0, slot, arg2);
}
