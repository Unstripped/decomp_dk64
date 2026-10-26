// __n_lookupSoundQuick (src/global/13ECE0.c): stage 4: reconstructed target search-direction condition and local layout; Docker unavailable for compile verification
ALSound *__n_lookupSoundQuick(VoiceMapCSPlayer *seqp, u8 key, u8 velocity, u8 chan) {
    ALInstrument *inst;
    s32 min;
    s32 max;
    s32 mid;
    ALSound *sound;

    inst = seqp->chanState[chan].instrument;
    min = 1;
    max = inst->soundCount;
    while (max >= min) {
        mid = (min + max) / 2;
        sound = ((VoiceMapInstrument *)inst)->soundArray[mid];
        if ((key < sound->keyMap->keyMin) || (sound->keyMap->keyMax < key)
            || (velocity < sound->keyMap->velocityMin) || (sound->keyMap->velocityMax < velocity)) {
            if ((key < sound->keyMap->keyMin)
                || ((velocity < sound->keyMap->velocityMin) && (key <= sound->keyMap->keyMax))) {
                max = mid - 1;
            } else {
                min = mid + 1;
            }
        } else {
            return sound;
        }
    }
    return NULL;
}
