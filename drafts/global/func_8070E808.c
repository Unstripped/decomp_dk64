// func_8070E808 (src/global/112080.c): stage 4: target instruction stream exactly matches, except an extra 8-byte local frame slot
extern void *func_8070D754(void *);
extern void func_8070E548(Actor *, u16, u8);
extern void timerQueueAdd(void *, s32, s32, s32, s32);
extern void func_8061DA84(void);

typedef struct R112cE808State {
    u8 pad0[0x54];
    u8 unk54;
} R112cE808State;

typedef struct R112cE808Item {
    u16 unk0;
    u8 unk2;
    u8 pad3;
    void *unk4;
} R112cE808Item;

typedef struct R112cE808Node {
    u8 pad0[8];
    R112cE808Item *unk8;
} R112cE808Node;

typedef struct R112cE808Arg1 {
    u8 pad0[0x60];
    s32 unk60;
} R112cE808Arg1;

void func_8070E808(Actor *arg0, void *arg1) {
    R112cE808State *sp24;
    R112cE808Node *sp20;
    R112cE808Item *temp_a0;
    R112cE808Node *temp_v0;

    sp24 = arg0->unk174;
    temp_v0 = func_8070D754(arg1);
    if (temp_v0->unk8 == NULL) {
        ((R112cE808Arg1 *) arg1)->unk60 &= 0xFDFFFFFF;
        if (sp24->unk54 & 1) {
            timerQueueAdd(func_8061DA84, 0x1E, 0, 0, 0);
        }
        arg0->unk154 = 4;
        return;
    }
    sp20 = temp_v0;
    func_8070E548(arg0, temp_v0->unk8->unk0, temp_v0->unk8->unk2);
    temp_a0 = temp_v0->unk8;
    temp_v0->unk8 = temp_a0->unk4;
    heapFreeDeferred(temp_a0);
}
