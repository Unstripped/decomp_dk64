// n_alResamplePull (src/global/145950.c): stage 4: target-aligned frame and slots; unverified because Docker image is unavailable after container storage failure
SynAllocAcmd *n_alResamplePull(SynAllocResample *filter, s16 *outp, s32 arg2, SynAllocAcmd *p) {
    SynAllocAcmd *result = p;
    s32 unused;
    f32 ratio;

    result = n_alSavePull(filter, outp, p);
    if ((filter->pitch != 0) && (filter->pitch < 0x40)) {
        SynAllocAcmd *cmd;

        if (filter->pitch >= 6) {
            ratio = 26755.0f / sqrtf((f32)filter->pitch + 1.0f);
        } else {
            ratio = 65536.0f / ((f32)filter->pitch + 1.0f);
        }
        if (ratio < 7723.0f) {
            ratio = 7723.0f;
        }
        cmd = result++;
        cmd->w0 = *outp & 0xFFFF;
        cmd->w1 = (((u32)ratio & 0xFFFF) << 16) | (u16)(filter->pitch + 1);
    }
    if (filter->count > 0) {
        if (filter->flags != 0) {
            func_8073BE54(&filter->samples, 22050.0f);
        }
        {
            SynAllocAcmd *cmd;

            cmd = result++;
            cmd->w0 = 0x0B000020;
            cmd->w1 = osVirtualToPhysical(&filter->state);
        }
        if (filter->flags == 2) {
            filter->flags = 0;
        }
        {
            SynAllocAcmd *cmd;

            cmd = result++;
            cmd->w0 = 0x0E000000 | ((filter->flags & 0xFF) << 16) | (*outp & 0xFFFF);
            cmd->w1 = (osVirtualToPhysical(filter->input) & 0xFFFFFF) & 0xFFFFFF;
        }
        filter->flags = 0;
    }
    return result;
}
