// schedHandleRetrace (src/global/131B0.c): TEXT-IDENTICAL, reloc only (D_807F04F8+4 vs D_807F04FC for the u64 osGetTime store); sp54 as TaskNode* (not s32) fixed the schedAppendTask a1 reuse; 5 FAKE dead stmts keep s0..s3 + non-PRE'd D_80746858 loads; paste + ROM gate

extern s8 D_80744510;
extern s16 D_80746858;
extern u32 D_8074684C[];

void schedHandleRetrace(SchedStruct *sc) {
    TaskNode *sp54;
    s32 i;
    s32 s2;
    s32 n;
    TaskNode *client;
    TaskNode *fb;

    sc->unk284++;
    sc->unk280++;
    D_807F04F8 = osGetTime();
    if (D_80744510 != 0) {
        if (D_80744510 == 1) {
            if (D_80746858 == 0) {
                osViBlack(1);
                if (D_80744510 && D_80744510) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
            }
            if (D_80746858 == 0x3C) {
                osViSetMode(&osViModeTable[D_8074684C[osTvType]]);
                osViSetSpecialFeatures(0x42);
                osViBlack(0);
                D_80744510 = 2;
                if (D_80744470 && D_80744470) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
            }
            D_80746858++;
        }
        osViSwapBuffer((void *)D_80744470[0]);
    }
    if (D_807F04E0 != NULL) {
        if (D_8076A0B1 & 2) {
            D_8076A0B1 ^= 2;
            osViBlack(0);
        }
        osViSwapBuffer(D_807F04E0->framebuffer);
        D_80746824 = D_80746820;
        D_80746820 = sc->unk284 + 1;
        osDpSetStatus(8);
        if (D_807F04E0->msgQ != NULL) {
            func_8060FAA4(D_807F04E0->msgQ, D_807F04E0->msg, 0);
        }
        D_807F04E0 = NULL;
    } else {
        fb = osViGetCurrentFramebuffer();
        if (osViGetNextFramebuffer() == (void *)fb) {
            if (osDpGetStatus() & 2) {
                sc->unk288 = osGetTime();
                osDpSetStatus(4);
            }
        }
    }
    n = sc->cmdQ.validCount;
    for (i = 0; i < n; i++) {
        osRecvMesg(&sc->cmdQ, (OSMesg *)&sp54, 0);
        if (sp54 == (TaskNode *)-1) {}  // FAKE: steers uopt (hoists -1 into s2)
        if ((u32)sc->unk284 % ((u32 *)sp54->unk50)[2] == 0) {
            schedAppendTask(sc, sp54);
        } else {
            osSendMesg(&sc->cmdQ, (OSMesg)sp54, 0);
            if (D_80746858 == 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
        }
        if (sp54 == (TaskNode *)-1) {}  // FAKE: steers uopt (hoists -1 into s2)
    }
    if (sc->audioListHead != NULL) {
        if ((sc->unk284 & 1) == 0) {
            osSetTimer(&D_807F0540, 0x445C0, 0, ((OSMesgQueue **)sc->audioListHead->unk50)[1], (OSMesg)5);
        }
    }
    for (client = sc->clientList; client != NULL; client = client->next) {
        if ((s32)client->framebuffer == 3) {
            osSendMesg((OSMesgQueue *)client->state, (OSMesg)0x29A, 0);
        }
    }
}
