#include "common.h"
#include "proto/global/1371D0.h"

void alSeqFileNew(ALSeqFile *f, u8 *base) {
    s32 offset = (s32)base;
    s32 i;

    for (i = 0; i < f->seqCount; i++) {
        f->seqArray[i].offset = f->seqArray[i].offset + offset;
    }
}


void alBnkfNew(ALBankFile *file, u8 *table) {
    s32 offset = (s32)file;
    s32 tbl = (s32)table;
    s32 i;

    if (file->revision != 0x4231) {
        return;
    }
    for (i = 0; i < file->bankCount; i++) {
        file->bankArray[i] = (ALBank *)((s32)file->bankArray[i] + offset);
        if (file->bankArray[i]) {
            _bnkfPatchBank(file->bankArray[i], offset, tbl);
        }
    }
}

void _bnkfPatchBank(ALBank *bank, s32 offset, s32 table) {
    s32 i;

    if (bank->flags) {
        return;
    }
    bank->flags = 1;
    if (bank->percussion) {
        bank->percussion = (ALInstrument *)((s32)bank->percussion + offset);
        _bnkfPatchInst(bank->percussion, offset, table);
    }
    for (i = 0; i < bank->instCount; i++) {
        bank->instArray[i] = (ALInstrument *)((s32)bank->instArray[i] + offset);
        if (bank->instArray[i]) {
            _bnkfPatchInst(bank->instArray[i], offset, table);
        }
    }
}

void _bnkfPatchInst(ALInstrument *inst, s32 offset, s32 table) {
    s32 i;

    if (inst->flags) {
        return;
    }
    inst->flags = 1;
    for (i = 0; i < inst->soundCount; i++) {
        inst->soundArray[i] = (ALSound *)((s32)inst->soundArray[i] + offset);
        _bnkfPatchSound(inst->soundArray[i], offset, table);
    }
}

void _bnkfPatchSound(ALSound *s, s32 offset, s32 table) {
    if (s->flags) {
        return;
    }
    s->flags = 1;
    s->envelope = (ALEnvelope *)((s32)s->envelope + offset);
    s->keyMap = (ALKeyMap *)((s32)s->keyMap + offset);
    s->wavetable = (ALWaveTable *)((s32)s->wavetable + offset);
    _bnkfPatchWaveTable(s->wavetable, offset, table);
}

void _bnkfPatchWaveTable(ALWaveTable *w, s32 offset, s32 table) {
    if (w->flags) {
        return;
    }
    w->flags = 1;
    w->base = (u8 *)((s32)w->base + table);
    if (w->type == AL_ADPCM_WAVE) {
        w->waveInfo.adpcmWave.book = (ALADPCMBook *)((s32)w->waveInfo.adpcmWave.book + offset);
        if (w->waveInfo.adpcmWave.loop) {
            w->waveInfo.adpcmWave.loop = (ALADPCMloop *)((s32)w->waveInfo.adpcmWave.loop + offset);
        }
    } else if (w->type == AL_RAW16_WAVE) {
        if (w->waveInfo.rawWave.loop) {
            w->waveInfo.rawWave.loop = (ALRawLoop *)((s32)w->waveInfo.rawWave.loop + offset);
        }
    }
}
