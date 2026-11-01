#include "common.h"

extern u8 D_80741F40[];
extern u8 D_807432D0[];
extern u8 D_80760840[];
extern u8 D_80760C60[];
extern void *D_807F0570[];
extern void *D_807F0588[];

void func_8060FFF0(void) {
    D_807F0570[0] = D_807432D0;
    D_807F0588[0] = D_80760C60;
    D_807F0570[1] = D_80741F40;
    D_807F0588[1] = D_80760840;
    D_807F0570[2] = D_80741F40;
    D_807F0588[2] = D_80760840;
    D_807F0570[3] = D_80741F40;
    D_807F0588[3] = D_80760840;
}

typedef struct SchedGfxTask {
    struct SchedGfxTask *next;
    u32 state;
    u32 flags;
    void *framebuffer;
    u32 type;
    u32 task_flags;
    void *ucode_boot;
    u32 ucode_boot_size;
    void *ucode;
    u32 ucode_size;
    void *ucode_data;
    u32 ucode_data_size;
    void *dram_stack;
    u32 dram_stack_size;
    void *output_buff;
    u32 output_buff_size;
    void *data_ptr;
    u32 data_size;
    void *yield_data_ptr;
    u32 yield_data_size;
    void *client;
    OSMesgQueue *msgQ;
    OSMesg msg;
    u32 pad5C;
} SchedGfxTask;

extern s8 D_80744460;
extern u8 D_807444FC;
extern u32 D_807F05A4;
extern u32 D_807F0984;
extern SchedGfxTask D_807F05A8[][2];
extern void *D_80744470[];
extern u8 D_805FB000[];
extern u8 D_805FB0D0[];
extern u8 D_8076AF20[];
extern u8 D_8076B320[];
extern u8 D_80767CD8[];
extern u8 D_80767CE8[];
extern OSMesgQueue D_807659E8;
extern u8 D_807F059C[];
extern OSMesgQueue gScheduler;

void schedSubmitGfxTask(void *arg0, s32 arg1, u8 arg2, u8 arg3, s32 arg4, u8 arg5) {
    SchedGfxTask *msg;
    s32 size;

    if (D_80744460 != 0) {
        return;
    }
    msg = &D_807F05A8[arg2][D_807444FC];
    D_807F059C[arg2] = 1;
    msg->type = 1;
    msg->task_flags = 0;
    msg->ucode_boot = D_805FB000;
    msg->ucode_boot_size = D_805FB0D0 - D_805FB000;
    msg->ucode = D_807F0570[arg2];
    msg->ucode_data = D_807F0588[arg2];
    msg->ucode_size = 0x1000;
    msg->ucode_data_size = 0x800;
    msg->dram_stack = D_8076AF20;
    msg->dram_stack_size = 0x400;
    msg->output_buff = (void *)D_807F05A4;
    msg->output_buff_size = D_807F05A4 + D_807F0984;
    msg->data_ptr = arg0;
    msg->data_size = arg1 * 8;
    msg->yield_data_ptr = D_8076B320;
    msg->yield_data_size = 0xC00;
    msg->next = NULL;
    msg->msgQ = &D_807659E8;
    msg->msg = (OSMesg)((arg2 << 16) | arg4);
    msg->flags = 3;
    if (arg3) {
        msg->flags |= 0x40;
    }
    msg->framebuffer = D_80744470[D_807444FC];
    msg->client = D_80767CD8;
    if (arg5) {
        osWritebackDCacheAll();
    } else {
        size = arg1 * 8;
        osWritebackDCache(msg, sizeof(SchedGfxTask));
        osWritebackDCache(arg0, size);
        osWritebackDCache(D_80767CE8 + D_807444FC * 0x11B0, 0x11B0);
    }
    osSendMesg(&gScheduler, msg, 1);
}

extern s8 D_80746834;

void func_80610268(s32 arg0) {
    void *sp34;
    s32 temp_t8;

    do {
        D_80746834 = 8;
        osRecvMesg(&D_807659E8, &sp34, 1);
        D_80746834 = 0;
        D_807F059C[(u32)sp34 >> 0x10] = 0;
        temp_t8 = ((s32)sp34 & 0xFFFF) & 0xFFFF;
        sp34 = (void *)temp_t8;
    } while (temp_t8 != arg0);
}
