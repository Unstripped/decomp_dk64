// n_alAuxBusPull (src/global/1445A0.c): stage 6: TEXT OK; reversed comparison operand order matches temporary register allocation
AuxAcmd *n_alAuxBusPull(void *arg0, AuxAcmd *arg1, s32 arg2, s32 *arg3) {
    AuxAcmd *ptr;
    AuxBus *bus;
    AuxPVoice **pvoices;
    s32 i;
    s32 count;
    u32 max;
    u32 ratio;

    ptr = arg1;
    bus = D_807563E4->buses + arg2;
    pvoices = bus->pvoices;
    count = 0;
    max = 1;
    {
        AuxAcmd *cmd;

        cmd = ptr++;
        cmd->w0 = 0x020007C0;
        cmd->w1 = 0x2E0;
    }
    *arg3 = 0;
    for (i = 0; i < bus->count; i++) {
        if ((pvoices[i]->env != NULL) && (pvoices[i]->env->time == arg2) && (pvoices[i]->env->resample != NULL) && (pvoices[i]->env->resample->pitch >= 0x40)) {
            ptr = n_alEnvmixerPull(pvoices[i], arg0, ptr);
            (*arg3)++;
            count++;
            if (pvoices[i]->env->resample->pitch > max) {
                max = pvoices[i]->env->resample->pitch;
            }
        }
    }
    if (count != 0) {
        max -= 0x3E;
        if (max >= 7) {
            ratio = (u32)(26755.0f / sqrtf((f32)max));
        } else {
            ratio = (u32)(65536.0f / (f32)max);
        }
        {
            AuxAcmd *cmd;

            cmd = ptr++;
            cmd->w0 = 0x4E0;
            cmd->w1 = ((ratio & 0xFFFF) << 16) | (max & 0xFFFF);
        }
        {
            AuxAcmd *cmd;

            cmd = ptr++;
            cmd->w0 = 0x650;
            cmd->w1 = ((ratio & 0xFFFF) << 16) | (max & 0xFFFF);
        }
    }
    for (i = 0; i < bus->count; i++) {
        if (((pvoices[i]->env != NULL) && (pvoices[i]->env->time == arg2) &&
             ((pvoices[i]->env->resample == NULL) || (pvoices[i]->env->resample->pitch < 0x40))) ||
            ((pvoices[i]->env == NULL) && (arg2 == 0))) {
            AuxAcmd *oldPtr;

            oldPtr = ptr;
            ptr = n_alEnvmixerPull(pvoices[i], arg0, ptr);
            if (ptr != oldPtr) {
                (*arg3)++;
            }
        }
    }
    return ptr;
}
