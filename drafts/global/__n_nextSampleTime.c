// __n_nextSampleTime (src/global/13E160.c): SynCore near-match: target stack frame is 0x10; current is 0x10 but body differs.
s32 __n_nextSampleTime(SynCorePlayer **player) {
    s32 unused;
    s32 time;
    SynCorePlayer *current;

    time = 0x7FFFFFFF;
    *player = NULL;
    if ((current = D_807563E4->head) != NULL) {
        do {
            if ((current->callTime - D_807563E4->curSamples) < time) {
                *player = current;
                time = current->callTime - D_807563E4->curSamples;
            }
        } while ((current = current->next) != NULL);
    }
    return (*player)->callTime;
}
