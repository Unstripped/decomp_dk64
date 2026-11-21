#include "common.h"
#include "render.h"
#include "sched.h"
#include "proto/global/14CF0.h"

extern u8 D_80741F40[];
extern u8 D_807432D0[];
extern u8 D_80760840[];
extern u8 D_80760C60[];
extern void *gGfxTaskUcodeText[];
extern void *gGfxTaskUcodeData[];

void schedInitGfxUcodes(void) {
    gGfxTaskUcodeText[0] = D_807432D0;
    gGfxTaskUcodeData[0] = D_80760C60;
    gGfxTaskUcodeText[1] = D_80741F40;
    gGfxTaskUcodeData[1] = D_80760840;
    gGfxTaskUcodeText[2] = D_80741F40;
    gGfxTaskUcodeData[2] = D_80760840;
    gGfxTaskUcodeText[3] = D_80741F40;
    gGfxTaskUcodeData[3] = D_80760840;
}

extern s8 gMainThreadHalted;
extern u8 gGfxBufferIndex;
extern TaskNode gGfxTaskNodes[][2];
extern void *gFramebuffers[];
extern u8 D_805FB000[];
extern u8 D_805FB0D0[];
extern u64 D_8076AF20[];
extern u64 D_8076B320[];
extern SchedClient gGfxSchedClient;
extern FrameMatrices gFrameMatrices[];
extern OSMesgQueue gGfxDoneQueue;
extern u8 gGfxTaskPending[];
extern SchedStruct gScheduler;

void schedSubmitGfxTask(void *glist, s32 numCommands, u8 taskIdx, u8 swapBuffers, s32 taskId, u8 writebackAll) {
    TaskNode *task;
    s32 pad;

    if (gMainThreadHalted != 0) {
        return;
    }
    task = &gGfxTaskNodes[taskIdx][gGfxBufferIndex];
    gGfxTaskPending[taskIdx] = 1;
    task->task.t.type = M_GFXTASK;
    task->task.t.flags = 0;
    task->task.t.ucode_boot = (u64 *)D_805FB000;
    task->task.t.ucode_boot_size = D_805FB0D0 - D_805FB000;
    task->task.t.ucode = gGfxTaskUcodeText[taskIdx];
    task->task.t.ucode_data = gGfxTaskUcodeData[taskIdx];
    task->task.t.ucode_size = SP_UCODE_SIZE;
    task->task.t.ucode_data_size = SP_UCODE_DATA_SIZE;
    task->task.t.dram_stack = D_8076AF20;
    task->task.t.dram_stack_size = SP_DRAM_STACK_SIZE8;
    task->task.t.output_buff = (u64 *)gRdpOutputBuffer;
    task->task.t.output_buff_size = (u64 *)(gRdpOutputBuffer + gRdpOutputBufferSize);
    task->task.t.data_ptr = glist;
    task->task.t.data_size = numCommands * 8;
    task->task.t.yield_data_ptr = D_8076B320;
    task->task.t.yield_data_size = 0xC00;
    task->next = NULL;
    task->msgQ = &gGfxDoneQueue;
    task->msg = (OSMesg)((taskIdx << 16) | taskId);
    task->flags = 3;
    if (swapBuffers) {
        task->flags |= 0x40;
    }
    task->framebuffer = gFramebuffers[gGfxBufferIndex];
    task->client = &gGfxSchedClient;
    if (writebackAll) {
        osWritebackDCacheAll();
    } else {
        osWritebackDCache(task, sizeof(TaskNode));
        osWritebackDCache(glist, numCommands * 8);
        osWritebackDCache(&gFrameMatrices[gGfxBufferIndex], sizeof(FrameMatrices));
    }
    osSendMesg(&gScheduler.interruptQ, task, OS_MESG_BLOCK);
}

extern s8 gWaitPointId;

void schedWaitGfxTask(s32 targetTaskId) {
    OSMesg receivedMsg;

    do {
        gWaitPointId = 8;
        osRecvMesg(&gGfxDoneQueue, &receivedMsg, OS_MESG_BLOCK);
        gWaitPointId = 0;
        gGfxTaskPending[(u32)receivedMsg >> 16] = 0;
        receivedMsg = (OSMesg)((u32)receivedMsg & 0xFFFF);
    } while ((s32)receivedMsg != targetTaskId);
}
