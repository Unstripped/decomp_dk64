// func_8070DB9C (src/global/112080.c): Stage 6: instruction sequence and size match; u8 flags remains allocated in v1 rather than target v0.
typedef struct M112bFreeEntry { void *unk0; void *unk4; } M112bFreeEntry;
typedef struct M112bRecord { u8 flags; u8 pad1[3]; void *unk4; M112bFreeEntry *unk8; void *unkC; } M112bRecord;
extern void heapFreeDeferred(void *);
extern void func_8070DB7C(M112bFreeEntry *);
void func_8070DB9C(M112bRecord *arg0) {
    s32 i;
    u8 flags;
    void *temp;
    temp = arg0->unk4;
    if (temp != NULL) { heapFreeDeferred(temp); }
    flags = arg0->flags;
    i = 0;
    if (flags & 1) {
        do { func_8070DB7C(&arg0->unk8[i]); i++; } while (i != 1);
        heapFreeDeferred(arg0->unk8);
        return;
    }
    if (flags & 2) { heapFreeDeferred(arg0->unk8->unk4); heapFreeDeferred(arg0->unk8); }
}
