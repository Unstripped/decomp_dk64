#include "common.h"
#include "audio_config.h"
#include "proto/global/13D170.h"



void n_alCSeqNew(ALCSeq *seq, ALCMidiHdr *base) {
    u32 i;
    u8 *track;
    s32 validTrack;

    seq->base = base;
    seq->validTracks = 0;
    seq->lastDeltaTicks = 0;
    seq->lastTicks = 0;
    seq->deltaFlag = 1;
    i = 0;
    do {
        seq->lastStatus[i] = 0;
        seq->curBUPtr[i] = NULL;
        seq->curBULen[i] = 0;
        track = (u8 *)seq->base->trackOffset[i];
        if (track != NULL) {
            validTrack = 1 << i;
            seq->validTracks |= validTrack;
            seq->curLoc[i] = (u8 *)base + (s32)track;
            seq->evtDeltaTicks[i] = __readVarLen(seq, i);
        } else {
            seq->curLoc[i] = NULL;
        }
    } while (++i < 16);
    seq->qnpt = 1.0f / seq->base->division;
}

void n_alCSeqNextEvent(ALCSeq *seq, ALEvent *event, s32 flag) {
    u32 i;
    u32 delta;
    u32 track;
    u32 lastDelta;

    delta = -1U;
    lastDelta = seq->lastDeltaTicks;
    i = 0;
    do {
        if ((seq->validTracks >> i) & 1) {
            if (seq->deltaFlag != 0) {
                seq->evtDeltaTicks[i] -= lastDelta;
            }
            if (seq->evtDeltaTicks[i] < delta) {
                delta = seq->evtDeltaTicks[i];
                track = i;
            }
        }
    } while (++i < 16);
    __n_alCSeqTrackEvent(seq, track, event, flag);
    event->msg.midi.ticks = delta;
    seq->lastTicks += delta;
    seq->lastDeltaTicks = delta;
    if (event->type != AL_TRACK_END) {
        seq->evtDeltaTicks[track] += __readVarLen(seq, track);
    }
    seq->deltaFlag = 1;
}

s32 __n_alCSeqTrackEvent(ALCSeq *seq, s32 track, ALEvent *event, s32 flag) {
    s32 loopOffset;
    u8 status;
    u8 loopStart;
    u8 loopCount;
    u8 *ptr;
    u8 metaType;
    s32 trackMask;

    status = __getTrackByte(seq, track);
    if (status == AL_MIDI_Meta) {
        metaType = __getTrackByte(seq, track);
        if (metaType == AL_MIDI_META_TEMPO) {
            event->type = AL_TEMPO_EVT;
            event->msg.tempo.status = status;
            event->msg.tempo.type = metaType;
            event->msg.tempo.byte1 = __getTrackByte(seq, track);
            event->msg.tempo.byte2 = __getTrackByte(seq, track);
            event->msg.tempo.byte3 = __getTrackByte(seq, track);
            seq->lastStatus[track] = 0;
        } else if (metaType == AL_MIDI_META_EOT) {
            trackMask = 1 << track;
            seq->validTracks ^= trackMask;
            if (seq->validTracks != 0) {
                event->type = AL_TRACK_END;
            } else {
                event->type = AL_SEQ_END_EVT;
            }
        } else if (metaType == AL_CMIDI_LOOPSTART_CODE) {
            status = __getTrackByte(seq, track);
            event->msg.midi.duration = status << 8;
            status = __getTrackByte(seq, track);
            event->msg.midi.duration += status;
            seq->lastStatus[track] = 0;
            event->type = AL_CSP_LOOPSTART;
        } else if (metaType == AL_CMIDI_LOOPEND_CODE) {
            ptr = seq->curLoc[track];
            loopStart = *ptr++;
            loopCount = *ptr;
            if ((loopCount == 0) || (flag == 0)) {
                *ptr = loopStart;
                seq->curLoc[track] = ptr + 5;
            } else {
                if (loopCount != 0xFF) {
                    *ptr = loopCount - 1;
                }
                ptr++;
                loopOffset = *ptr++ << 24;
                loopOffset += *ptr++ << 16;
                loopOffset += *ptr++ << 8;
                loopOffset += *ptr++;
                seq->curLoc[track] = ptr - loopOffset;
            }
            seq->lastStatus[track] = 0;
            event->type = AL_CSP_LOOPEND;
        }
    } else {
        event->type = AL_SEQ_MIDI_EVT;
        if (status & 0x80) {
            event->msg.midi.status = (status & AL_MIDI_StatusMask) | track;
            event->msg.midi.byte1 = __getTrackByte(seq, track);
            seq->lastStatus[track] = event->msg.midi.status;
        } else {
            event->msg.midi.status = seq->lastStatus[track];
            event->msg.midi.byte1 = status;
        }
        if (((event->msg.midi.status & AL_MIDI_StatusMask) != AL_MIDI_ProgramChange) &&
            ((event->msg.midi.status & AL_MIDI_StatusMask) != AL_MIDI_ChannelPressure)) {
            event->msg.midi.byte2 = __getTrackByte(seq, track);
            if ((event->msg.midi.status & AL_MIDI_StatusMask) == AL_MIDI_NoteOn) {
                event->msg.midi.duration = __readVarLen(seq, track);
            }
        } else {
            event->msg.midi.byte2 = 0;
        }
    }
    return 1;
}

s32 alCSeqGetTicks(ALCSeq *seq) {
    return seq->lastTicks;
}

void alCSeqSetLoc(ALCSeq *seq, ALCSeqMarker *marker) {
    s32 i;

    seq->validTracks = marker->validTracks;
    seq->lastTicks = marker->lastTicks;
    seq->lastDeltaTicks = marker->lastDeltaTicks;
    i = 0;
    do {
        seq->curLoc[i] = marker->curLoc[i];
        seq->curBUPtr[i] = marker->curBUPtr[i];
        seq->curBULen[i] = marker->curBULen[i];
        seq->lastStatus[i] = marker->lastStatus[i];
        seq->evtDeltaTicks[i] = marker->evtDeltaTicks[i];
    } while (++i < 16);
}

void alCSeqGetLoc(ALCSeq *seq, ALCSeqMarker *marker) {
    s32 i;

    marker->validTracks = seq->validTracks;
    marker->lastTicks = seq->lastTicks;
    marker->lastDeltaTicks = seq->lastDeltaTicks;
    i = 0;
    do {
        marker->curLoc[i] = seq->curLoc[i];
        marker->curBUPtr[i] = seq->curBUPtr[i];
        marker->curBULen[i] = seq->curBULen[i];
        marker->lastStatus[i] = seq->lastStatus[i];
        marker->evtDeltaTicks[i] = seq->evtDeltaTicks[i];
    } while (++i < 16);
}

void n_alCSeqNewMarker(ALCSeq *seq, ALCSeqMarker *marker, u32 ticks) {
    ALEvent event;
    ALCSeq cseq;
    s32 i;

    n_alCSeqNew(&cseq, seq->base);
    do {
        marker->validTracks = cseq.validTracks;
        marker->lastTicks = cseq.lastTicks;
        marker->lastDeltaTicks = cseq.lastDeltaTicks;
        i = 0;
        do {
            marker->curLoc[i] = cseq.curLoc[i];
            marker->curBUPtr[i] = cseq.curBUPtr[i];
            marker->curBULen[i] = cseq.curBULen[i];
            marker->lastStatus[i] = cseq.lastStatus[i];
            marker->evtDeltaTicks[i] = cseq.evtDeltaTicks[i];
        } while (++i < 16);
        n_alCSeqNextEvent(&cseq, &event, 0);
        if (event.type == AL_SEQ_END_EVT) {
            break;
        }
    } while (cseq.lastTicks < ticks);
}

void __n_alCSeqNextDelta(ALCSeq *seq, ALCSeqMarker *markers, u32 count, u32 firstMarker) {
    ALEvent event;
    ALCSeq cseq;
    s32 i;
    s32 markerCount;
    ALCSeqMarker marker;
    s32 pad;
    n_alCSeqNew(&cseq, seq->base);
    for (markerCount = 0; markerCount < count; markerCount++) {
        markers[markerCount].lastTicks = 0;
    }
    do {
        marker.validTracks = cseq.validTracks;
        marker.lastTicks = cseq.lastTicks;
        marker.lastDeltaTicks = cseq.lastDeltaTicks;
        i = 0;
        do {
            marker.curLoc[i] = cseq.curLoc[i];
            marker.curBUPtr[i] = cseq.curBUPtr[i];
            marker.curBULen[i] = cseq.curBULen[i];
            marker.lastStatus[i] = cseq.lastStatus[i];
            marker.evtDeltaTicks[i] = cseq.evtDeltaTicks[i];
        } while (++i < 16);
        n_alCSeqNextEvent(&cseq, &event, 0);
        if ((event.type == AL_CSP_LOOPSTART) &&
            ((u32)((s32)event.msg.midi.duration >> 8) >= firstMarker) &&
            ((u32)((s32)event.msg.midi.duration >> 8) < firstMarker + count)) {
            if (markers[((s32)event.msg.midi.duration >> 8) - firstMarker].lastTicks == 0) {
                markers[((s32)event.msg.midi.duration >> 8) - firstMarker] = marker;
                if (--markerCount <= 0) {
                    return;
                }
            }
        }
    } while (event.type != AL_SEQ_END_EVT);
}

u8 __getTrackByte(ALCSeq *seq, s32 track) {
    u8 result;
    u8 byte3;
    u8 byte2;
    u8 byte1;
    u8 byte4;
    s32 offset;

    if (seq->curBULen[track] != 0) {
        result = *seq->curBUPtr[track];
        seq->curBUPtr[track]++;
        seq->curBULen[track]--;
    } else {
        result = *seq->curLoc[track];
        seq->curLoc[track]++;
        if (result == AL_CMIDI_BLOCK_CODE) {
            byte4 = *seq->curLoc[track];
            seq->curLoc[track]++;
            if (byte4 != AL_CMIDI_BLOCK_CODE) {
                byte2 = byte4;
                byte3 = *seq->curLoc[track];
                seq->curLoc[track]++;
                byte1 = *seq->curLoc[track];
                seq->curLoc[track]++;
                offset = byte2;
                offset <<= 8;
                offset += byte3;
                seq->curBUPtr[track] = seq->curLoc[track] - offset - 4;
                seq->curBULen[track] = byte1;
                result = *seq->curBUPtr[track];
                seq->curBUPtr[track]++;
                seq->curBULen[track]--;
            }
        }
    }
    return result;
}

s32 __readVarLen(ALCSeq *seq, s32 track) {
    s32 value;
    s32 byte;

    value = __getTrackByte(seq, track);
    if (value & 0x80) {
        value &= 0x7F;
        do {
            byte = __getTrackByte(seq, track);
            value = (value << 7) + (byte & 0x7F);
        } while (byte & 0x80);
    }
    return value;
}

extern ALGlobals *n_globals;
extern ALSynth *n_syn;
void n_alSynNew(AudioInitArgs *config);
void n_alSynDelete(void);

void n_alInit(ALGlobals *glob, AudioInitArgs *config) {
    if (n_globals == NULL) {
        n_globals = glob;
        if (n_syn == NULL) {
            n_syn = (ALSynth *)n_globals;
            n_alSynNew(config);
        }
    }
}

void n_alClose(ALGlobals *glob) {
    if (n_globals != NULL) {
        n_alSynDelete();
        n_globals = NULL;
        n_syn = NULL;
    }
}
