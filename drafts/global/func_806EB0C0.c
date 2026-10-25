// func_806EB0C0 (src/global/EFDC0.c): Stage 4 behavior reconstruction: branch and register allocation remain; explicit offset and signed priority.
s32 func_806EB0C0(s16 priority, void *actor, s32 player) {
    s32 playerByte;
    s32 offset;
    s32 priorityCopy;
    EfAQueuedCall *entry;

    priorityCopy = priority;
    playerByte = player & 0xFF;
    offset = playerByte * 0x2F0;
    entry = (EfAQueuedCall *)((u8 *)D_807FC924 + offset);
    if (entry->unk29C < priorityCopy) {
        entry->unk29C = priorityCopy;
        ((EfAQueuedCall *)((u8 *)D_807FC924 + offset))->unk2A0 = actor;
        ((EfAQueuedCall *)((u8 *)D_807FC924 + offset))->unk2A8 = D_807FD6F0.unk0;
        ((EfAQueuedCall *)((u8 *)D_807FC924 + offset))->unk2AC = D_807FD6F0.unk4;
        ((EfAQueuedCall *)((u8 *)D_807FC924 + offset))->unk2B0 = D_807FD6F0.unk8;
        if (actor != NULL) {
            ((EfAQueuedCall *)((u8 *)D_807FC924 + offset))->unk2A4 = ((EfAActor *)actor)->unk54;
        }
        return 1;
    }
    return 0;
}
