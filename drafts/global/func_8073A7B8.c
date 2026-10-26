// func_8073A7B8 (src/global/13ECE0.c): stage 3: behavior and clamp branches match; frame/local-slot layout differs
#define VOICE_CLAMP_MIX(value) ((value) > 0x7F ? 0x7F : (value))

u8 func_8073A7B8(VoiceMapVoiceState *vs, VoiceMapCSPlayer *seqp) {
    s32 flags;
    s32 mix;

    flags = seqp->chanState[vs->channel].fxmix & 0x80;
    mix = (s32)((f32)((seqp->chanState[vs->channel].fxmix & 0x7F) + (s32)(seqp->unk7C * 127.0f)) * seqp->unk80);
    if (VOICE_CLAMP_MIX(mix) < 0) {
        return flags;
    }
    return VOICE_CLAMP_MIX(mix) | flags;
}
