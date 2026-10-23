// func_8066B0F8 (src/global/6AD90.c): 88-byte frame matches target; s32 pad sets 0x50/0x4c slots; direct array access for D_807FA8A0

#include "common.h"

typedef struct {
    void *unk0;
    void *unk4;
    u8 unk8;
} R1D_StructA8A0;

void func_8060B140(u32, void *, s32 *, s32, s32, s32, s32);
void *func_80610FE8(s32);
void func_8066AEE4(void *, void *);
void func_8066B4AC(s32, u32, void *);
void func_8066B4D4(s32, u32, u32 *, s32 *);
void *func_8066B5C8(s32, u32);
void func_8066B5F4(void);
void func_8066B8C8(void *, s32, u32);
void func_80732354(s32, s32, s32, s32);
void *heapAllocFromPool(s32, s32);

extern u8 D_80748E18[];
extern OSMesgQueue D_807656D0;
extern s32 D_807F9678;
extern s8 D_807F967C;
extern s32 D_807F9680;
extern OSIoMesg D_807F9688[];
extern R1D_StructA8A0 D_807FA8A0[];
extern s32 *D_807FB1A0[];

void *func_8066B0F8(s32 arg0, u32 arg1, u8 arg2, s32 arg3) {
    s32 pad;
    u32 sp50;
    s32 sp4C;
    s32 var_a1;
    void *buffer;
    u8 *temp_t0;

    buffer = (void *)(arg3 & 0xFF);
    func_8066B5F4();
    if (buffer == NULL) {
        if ((arg1 >= 0x80000000U) && (arg1 < 0xA0000000U)) {
            func_8066B8C8((void *)arg1, arg0, 0);
            D_807F967C = 0;
            D_807F9678 = 0;
            return (void *)arg1;
        }
        buffer = func_8066B5C8(arg0, arg1);
        if (buffer != NULL) {
            func_8066B8C8(buffer, arg0, arg1);
            D_807F967C = 0;
            D_807F9678 = 0;
            return buffer;
        }
    }
    func_8066B4D4(arg0, arg1, &sp50, &sp4C);
    if (sp4C == 0) {
        D_807F967C = 0;
        D_807F9678 = 0;
        return NULL;
    }
    temp_t0 = &D_80748E18[arg0];
    var_a1 = sp4C;
    if (*temp_t0 != 0) {
        var_a1 = D_807FB1A0[arg0][arg1];
    }
    if (D_807F9678 == 0) {
        buffer = func_80610FE8(var_a1);
    } else {
        buffer = heapAllocFromPool(D_807F9678, var_a1);
    }
    if (arg2 != 0) {
        if (*temp_t0 != 0) {
            void *temp_v0_2 = func_80610FE8(sp4C);
            func_8060B140(sp50, temp_v0_2, &sp4C, 0, 0, 0, 0);
            func_8066AEE4(temp_v0_2, buffer);
        } else {
            func_8060B140(sp50, buffer, &sp4C, 0, 0, 0, 0);
        }
    } else {
        if (D_807F9680 == 0xC0) {
            func_80732354(6, 0, 0, 0);
        }
        D_807FA8A0[D_807F9680].unk8 = *temp_t0;
        if (*temp_t0 != 0) {
            D_807FA8A0[D_807F9680].unk0 = func_80610FE8(sp4C);
            D_807FA8A0[D_807F9680].unk4 = buffer;
        } else {
            D_807FA8A0[D_807F9680].unk4 = buffer;
            D_807FA8A0[D_807F9680].unk0 = buffer;
        }
        osInvalDCache(D_807FA8A0[D_807F9680].unk0, sp4C);
        osPiStartDma(&D_807F9688[D_807F9680], 0, 0, sp50, D_807FA8A0[D_807F9680].unk0, (u32) sp4C, &D_807656D0);
        D_807F9680 += 1;
    }
    func_8066B4AC(arg0, arg1, buffer);
    func_8066B8C8(buffer, arg0, arg1);
    D_807F967C = 0;
    D_807F9678 = 0;
    return buffer;
}
