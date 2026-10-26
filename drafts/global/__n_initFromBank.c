// __n_initFromBank (src/global/13ECE0.c): stage 3: local-slot layout and loop form adjusted; compile check blocked by Docker EOF
void __n_initFromBank(VoiceMapCSPlayer *seqp, ALBank *bank) {
    s32 chan;
    ALInstrument *inst;

    inst = NULL;
    if (inst == NULL) {
        chan = 0;
        do {
            inst = bank->instArray[chan];
        } while (inst == NULL && ++chan);
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
