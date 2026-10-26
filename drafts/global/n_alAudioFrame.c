// n_alAudioFrame (src/global/13E160.c): SynCore near-match: target frame is 0x40; output sample conditional differs.
s32 n_alAudioFrame(s32 cmdList, s32 *cmdLen, s32 outBuf, s32 outLen) {
    SynCorePlayer *player;
    s16 unused;
    s32 output;
    s32 original;
    s32 samples;
    s32 buffer;

    unused = 0;
    output = cmdList;
    buffer = outBuf;
    if (D_807563E4->head == NULL) {
        *cmdLen = 0;
        return cmdList;
    }
    D_807563E4->paramSamples = __n_nextSampleTime(&player);
    if ((D_807563E4->paramSamples - D_807563E4->curSamples) < outLen) {
        do {
            D_807563E4->paramSamples &= ~0xF;
            player->callTime += _n_timeToSamplesNoRound(player->handler(player));
            D_807563E4->paramSamples = __n_nextSampleTime(&player);
        } while ((D_807563E4->paramSamples - D_807563E4->curSamples) < outLen);
    }
    D_807563E4->paramSamples &= ~0xF;
    if (outLen > 0) {
        do {
            if (outLen > D_807563E4->maxOutSamples) {
                samples = D_807563E4->maxOutSamples;
            } else {
                samples = outLen;
            }
            original = output;
            D_807563E4->outBuffer = (void *)buffer;
            output = func_8073E800(D_807563E4->curSamples, original);
            outLen -= samples;
            buffer += samples * 4;
            D_807563E4->curSamples += samples;
        } while (outLen > 0);
    }
    *cmdLen = (output - cmdList) >> 3;
    _n_collectPVoices();
    return output;
}
