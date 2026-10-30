// func_80610044 (src/global/14CF0.c): stage 5: matches frame 0x30, saves ra,s0, 0 reloc mismatches; 15 lines regalloc diff in task field store ordering
typedef struct RvD2_GfxTask {
    struct RvD2_GfxTask *next;
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
} RvD2_GfxTask;

extern s8 D_80744460;
extern u8 D_807444FC;
extern u32 D_807F05A4;
extern u32 D_807F0984;
extern RvD2_GfxTask D_807F05A8[][2];
extern void *D_80744470[];
extern u8 D_805FB000[];
extern u8 D_805FB0D0[];
extern u8 D_8076AF20[];
extern u8 D_8076B320[];
extern u8 D_80767CD8[];
extern u8 D_80767CE8[];
extern void *D_807F0570[];
extern void *D_807F0588[];
extern OSMesgQueue D_807659E8;
extern u8 D_807F059C[];
extern OSMesgQueue gScheduler;

void func_80610044(void *arg0, s32 arg1, u8 arg2, u8 arg3, s32 arg4, u8 arg5) {
    RvD2_GfxTask *msg;
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
    msg->yield_data_ptr = D_8076B320;
    msg->msgQ = &D_807659E8;
    msg->data_size = arg1 * 8;
    msg->yield_data_size = 0xC00;
    msg->data_ptr = arg0;
    msg->next = NULL;
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
        osWritebackDCache(msg, sizeof(RvD2_GfxTask));
        osWritebackDCache(arg0, size);
        osWritebackDCache(D_80767CE8 + D_807444FC * 0x11B0, 0x11B0);
    }
    osSendMesg(&gScheduler, msg, 1);
}
