// slotQueueAddValue (src/global/FCCD0.c): Text R5: stage 4, frame 0x50 = target, 159 insns = target, 7 diff lines (deadsweep score; HEAD park was 46, old draft 48): ONLY spill-slot offsets differ (ours t2 spill 28(sp), a2 32(sp); target t2 36, a2 32). Levers: deadsweep 'if (D_8076A0AB && D_8076A0AB) {}' after slotQueueGetAddress and at end of the != 0xA/0xC block (48->12), then spelling grid: lhu 0xA before 0x26 (->10), '((SlotQueueStatSlot *)temp_v0)[arg0].unk0' reads (fixes addu a2,t0,t2 order), terms 'sp48 + 0xA + (idx*2)' (->7); func_805FEF10 takes s32 *. Left: cfe hidden s16 temp (nested flagSet(flagGridIndex()) result, home -42 = word 0x24) forces uopt spills to 0x20 (a2, coloured first, adjsave 1.33) / 0x1C (t2 cand 29, adjsave 0.25); target has t2 at 0x24 then a2 at 0x20 (t2 allocated first, no cfe temp above) with 8 free bytes below. Reusing a local for the call result drops frame to 0x48 (33 diff); named idx/slot locals are copy-propagated away (spill still 0x1C); s16/u8 packing of sp28/pb, declaration order/type/pad hill-climb (13k), dead-test hill-climb (56k): no change.
typedef struct SlotQueueStatSlot {
    u16 *unk0;
    u8 pad4[0x28];
    u8 unk2C;
    u8 unk2D;
    u8 pad2E[2];
} SlotQueueStatSlot;

extern u8 gPlayerCharacterId;
extern s32 func_805FEF10(s32 *);
extern void func_80687C48(void);
extern void flagSet(s16, s32, s32);
extern s16 flagGridIndex(s32, s32, u8, s32);
extern void sfxAllocateChannel(s32, f32);

void slotQueueAddValue(arg0, arg1, arg2)
s32 arg0;
u8 arg1;
s16 arg2;
{
    u8 *pa;
    u8 *sp48;
    s16 *pb;
    s32 temp_v0;
    s32 sp3C;
    s32 temp_a3;
    s32 temp_v0_2;
    u16 *temp_v1;
    SlotQueueStatSlot *temp_a0;
    s32 sp28;

    pa = &arg1;  // FAKE: keeps arg1 memory-resident (plain lbu per use)
    sp28 = arg1;
    temp_v0_2 = func_806C8DE0(arg1);
    sp48 = (u8 *)D_807FC950 + (arg1 * 0x306 + temp_v0_2 * 0x5E);
    temp_v0 = slotQueueGetAddress(arg1);
    if (D_8076A0AB && D_8076A0AB) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
    temp_a0 = (SlotQueueStatSlot *)temp_v0 + arg0;
    if (((temp_a0->unk2D == 0) || (arg2 >= 0)) && (temp_a0->unk2C == 0)) {
        if ((arg0 != 0xA) && (arg0 != 0xC)) {
            temp_v1 = temp_a0->unk0;
            if ((*temp_v1 + arg2) < 0) {
                *temp_v1 = 0;
            } else {
                temp_v1 = ((SlotQueueStatSlot *)temp_v0)[arg0].unk0;
                *temp_v1 += arg2;
                temp_v0_2 = slotQueueGetMaxValue(arg0, sp28);
                temp_v1 = ((SlotQueueStatSlot *)temp_v0)[arg0].unk0;
                if (temp_v0_2 < *temp_v1) {
                    *temp_v1 = temp_v0_2;
                }
                if (((arg0 * 0x30) == 0x180) && (func_805FEF10(&sp3C) != 0)) {
                    flagSet(sp3C, 1, 0);
                }
                if ((arg2 > 0) && ((arg0 * 0x30) == 0)) {
                    temp_v0_2 = func_805FF030(D_8076A0AB, 1);
                    temp_a3 = *(u16 *)(sp48 + 0xA + (temp_v0_2 * 2)) + *(u16 *)(sp48 + 0x26 + (temp_v0_2 * 2));
                    if ((temp_a3 >= 0x4B) && ((temp_a3 - arg2) < 0x4B)) {
                        flagSet(flagGridIndex(0x225, temp_v0_2, (&gPlayerCharacterId)[arg1], temp_a3), 1, 0);
                        func_80687C48();
                    }
                    if ((temp_a3 == 0x64) && ((temp_a3 - arg2) < 0x64)) {
                        sfxAllocateChannel(0xAC, 1.0f);
                    }
                }
            }
            if (D_8076A0AB && D_8076A0AB) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
        }
        if ((arg0 * 0x30) == 0x180) {
            func_806F8278(arg1);
        }
    }
