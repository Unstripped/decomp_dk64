// n_alFxNew (src/global/140600.c): stage 1 m2c reconstruction: exact allocations and control flow recovered; field-view types and statement shapes remain
typedef struct SynVoiceFxConfig SynVoiceFxConfig;
typedef struct SynVoiceFxState SynVoiceFxState;

typedef struct {
    s16 unk0;
    s16 unk2;
    u32 unk4;
    s16 coeff[16];
    s32 state;
} SynVoiceLPFilter;

void _init_lpfilter(SynVoiceLPFilter *);

/*
 * m2c stage-1 reconstruction: allocate a 0x30-byte FX state; choose a preset
 * stream from arg1/arg2 or D_80756458; allocate and zero delay storage; then
 * allocate one 0x28-byte descriptor per preset line.  Each descriptor consumes
 * five scalar fields, optionally allocates a 0x38-byte delay object plus two
 * 0x20-byte buffers, and optionally allocates/configures a 0x38-byte low-pass
 * filter with two 8-byte buffers and _init_lpfilter().  Exact field views and
 * source statement shapes remain to be recovered.
 */
void n_alFxNew(void **arg0, SynVoiceFxConfig *arg1, s16 arg2, ALHeap *arg3) {
    /* saved stage-1 sketch; see asm for exact typed allocation sequence */
}
