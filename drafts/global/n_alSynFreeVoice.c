// n_alSynFreeVoice (src/global/13FED0.c): SynCore near-match: target size 0xE0, current 0xD4.
void n_alSynFreeVoice(ALVoice *voice) {
    void *unused;
    SynCoreParam *param;

    if (voice->pvoice != NULL) {
        if (((SynCorePVoice *)voice->pvoice)->envOffset != 0) {
            param = __n_allocParam();
            if (param == NULL) {
                return;
            }
            param->timestamp = D_807563E4->paramSamples + ((SynCorePVoice *)voice->pvoice)->envOffset;
            param->type = 0;
            param->value = (s32)voice->pvoice;
            n_alEnvmixerParam(voice->pvoice, 3, param);
        } else {
            _n_freePVoice((ALLink *)voice->pvoice);
        }
        voice->pvoice = NULL;
    }
}
