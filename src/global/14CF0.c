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
extern u8 gGfxBufferIndex;
extern u32 D_807F05A4;
extern u32 D_807F0984;
extern SchedGfxTask D_807F05A8[][2];
extern void *gFramebuffers[];
extern u8 D_805FB000[];
extern u8 D_805FB0D0[];
extern u8 D_8076AF20[];
extern u8 D_8076B320[];
extern u8 D_80767CD8[];
extern u8 D_80767CE8[];
extern OSMesgQueue D_807659E8;
extern u8 D_807F059C[];
extern OSMesgQueue gScheduler;

void schedSubmitGfxTask(void *glist, s32 numCommands, u8 taskIdx, u8 swapBuffers, s32 taskId, u8 writebackAll) {
    SchedGfxTask *msg;
    s32 size;

    if (D_80744460 != 0) {
        return;
    }
    msg = &D_807F05A8[taskIdx][gGfxBufferIndex];
    D_807F059C[taskIdx] = 1;
    msg->type = 1;
    msg->task_flags = 0;
    msg->ucode_boot = D_805FB000;
    msg->ucode_boot_size = D_805FB0D0 - D_805FB000;
    msg->ucode = D_807F0570[taskIdx];
    msg->ucode_data = D_807F0588[taskIdx];
    msg->ucode_size = 0x1000;
    msg->ucode_data_size = 0x800;
    msg->dram_stack = D_8076AF20;
    msg->dram_stack_size = 0x400;
    msg->output_buff = (void *)D_807F05A4;
    msg->output_buff_size = D_807F05A4 + D_807F0984;
    msg->data_ptr = glist;
    msg->data_size = numCommands * 8;
    msg->yield_data_ptr = D_8076B320;
    msg->yield_data_size = 0xC00;
    msg->next = NULL;
    msg->msgQ = &D_807659E8;
    msg->msg = (OSMesg)((taskIdx << 16) | taskId);
    msg->flags = 3;
    if (swapBuffers) {
        msg->flags |= 0x40;
    }
    msg->framebuffer = gFramebuffers[gGfxBufferIndex];
    msg->client = D_80767CD8;
    if (writebackAll) {
        osWritebackDCacheAll();
    } else {
        size = numCommands * 8;
        osWritebackDCache(msg, sizeof(SchedGfxTask));
        osWritebackDCache(glist, size);
        osWritebackDCache(D_80767CE8 + gGfxBufferIndex * 0x11B0, 0x11B0);
    }
    osSendMesg(&gScheduler, msg, 1);
}

extern s8 D_80746834;

void func_80610268(s32 targetTaskId) {
    void *receivedMsg;
    s32 receivedTaskId;

    do {
        D_80746834 = 8;
        osRecvMesg(&D_807659E8, &receivedMsg, 1);
        D_80746834 = 0;
        D_807F059C[(u32)receivedMsg >> 0x10] = 0;
        receivedTaskId = ((s32)receivedMsg & 0xFFFF) & 0xFFFF;
        receivedMsg = (void *)receivedTaskId;
    } while (receivedTaskId != targetTaskId);
}
