// n_alSynNew (src/global/13E160.c): SynCore near-match: target size 0x604, current 0x614.
void n_alSynNew(SynCoreConfig *config) {
    s32 i;
    s32 padI;
    s32 j;
    ALLink *pvoice;
    s32 padPVoice;
    SynCorePVoice *pvoices;
    ALHeap *heap;
    SynCoreParam *params;
    SynCoreParam *param;

    heap = config->heap;
    D_807563E4->head = NULL;
    D_807563E4->numPVoices = config->maxPVoices;
    D_807563E4->curSamples = 0;
    D_807563E4->paramSamples = 0;
    D_807563E4->outputRate = config->outputRate;
    D_807563E4->maxOutSamples = 0xB8;
    D_807563E4->dma = config->dma;
    D_807563E4->outBuffer = NULL;
    D_807563E4->unk4C = 1;
    if (config->maxFXBusses >= 3) D_807563E4->maxAuxBusses = 2;
    else if (config->maxFXBusses <= 0) D_807563E4->maxAuxBusses = 1;
    else D_807563E4->maxAuxBusses = config->maxFXBusses;
    D_807563E4->auxBuses = alHeapDBAlloc(NULL, 0, heap, D_807563E4->maxAuxBusses, 0x48);
    i = 0;
    if (D_807563E4->maxAuxBusses > 0) do {
        D_807563E4->auxBuses[i].count = 0;
        D_807563E4->auxBuses[i].maxPVoices = config->maxPVoices;
        D_807563E4->auxBuses[i].pvoices = alHeapDBAlloc(NULL, 0, heap, config->maxPVoices, 4);
        if (config->fxType[i] != 0) D_807563E4->auxBuses[i].effect = func_8073D160(i, config, heap);
        else D_807563E4->auxBuses[i].effect = NULL;
        D_807563E4->auxBuses[i].filter = alHeapDBAlloc(NULL, 0, heap, 1, 0x38);
        *(s16 *)((u8 *)D_807563E4->auxBuses[i].filter + 2) = 0;
        *(void **)((u8 *)D_807563E4->auxBuses[i].filter + 0x2C) = alHeapDBAlloc(NULL, 0, heap, 1, 8);
        *(void **)((u8 *)D_807563E4->auxBuses[i].filter + 0x30) = alHeapDBAlloc(NULL, 0, heap, 1, 8);
        i++;
    } while (i < D_807563E4->maxAuxBusses);
    D_807563E4->mainBus = alHeapDBAlloc(NULL, 0, heap, 1, 0x14);
    *(void **)((u8 *)D_807563E4->mainBus + 4) = n_alFxPull;
    D_807563E4->pFreeList.next = NULL;
    D_807563E4->pFreeList.prev = NULL;
    D_807563E4->pAllocList.next = NULL;
    D_807563E4->pAllocList.prev = NULL;
    D_807563E4->pLameList.next = NULL;
    D_807563E4->pLameList.prev = NULL;
    pvoices = alHeapDBAlloc(NULL, 0, heap, config->maxPVoices, 0xC0);
    i = 0;
    if (config->maxPVoices > 0) do {
        pvoice = (ALLink *)&pvoices[i];
        alLink(pvoice, &D_807563E4->pFreeList);
        *(s32 *)((u8 *)pvoice + 8) = 0;
        alN_PVoiceNew(pvoice, D_807563E4->dma, heap);
        j = 0;
        if (D_807563E4->maxAuxBusses > 0) do {
            D_807563E4->auxBuses[j].pvoices[D_807563E4->auxBuses[j].count] = pvoice;
            D_807563E4->auxBuses[j].count++;
            j++;
        } while (j < D_807563E4->maxAuxBusses);
        i++;
    } while (i < config->maxPVoices);
    params = alHeapDBAlloc(NULL, 0, heap, config->maxUpdates, 0x24);
    D_807563E4->paramFreeList = NULL;
    i = 0;
    if (config->maxUpdates > 0) do {
        param = (SynCoreParam *)&((u8 *)params)[i * 0x24];
        param->next = (ALLink *)D_807563E4->paramFreeList;
        D_807563E4->paramFreeList = param;
        i++;
    } while (i < config->maxUpdates);
    D_807563E4->paramPool = heap;
}
