// __n_initFromBank (src/global/13ECE0.c): stage 3: all setup and loop body match; remaining diff is two boolean-normalization instructions in bank selection loop
void __n_initFromBank(VoiceMapCSPlayer *seqp, ALBank *bank) {
    s32 chan;
    ALInstrument *inst;

    inst = NULL;
    if ((chan = 0, inst == NULL)) {
        do {
            inst = bank->instArray[chan];
        } while ((inst == NULL) & ++chan);
    }
    for (chan = 0; chan < seqp->maxChannels; chan++) {
        __n_resetPerfChanState(seqp, chan);
        __n_setInstChanState(seqp, inst, chan);
    }
    if (bank->percussion != NULL) {
        __n_resetPerfChanState(seqp, chan);
        __n_setInstChanState(seqp, bank->percussion, 9);
    }
}
