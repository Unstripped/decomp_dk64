// schedHandleRetrace (src/global/131B0.c): stage 5-6: -1 in s2 reproduced with two `if (sp54 == -1) {}` dead stmts; text 51 vs expected, remaining D_80746858/D_80744510 hoist and temp regs; locals order sp54,i,s2,n,client,fb gives slots 0x54/0x48
extern s8 D_80744510;
extern s16 D_80746858;
extern u32 D_8074684C[];

void schedHandleRetrace(SchedStruct *sc) {
    s32 sp54;
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
            }
            if (D_80746858 == 0x3C) {
                if (D_8074684C) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                osViSetMode(&osViModeTable[D_8074684C[osTvType]]);
                osViSetSpecialFeatures(0x42);
                osViBlack(0);
                D_80744510 = 2;
            }
            D_80746858++;
        }
        osViSwapBuffer((void *)D_80744470[0]);
    }
    if (D_80746858 == -1) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
    if (D_807F04E0 != NULL) {
        if (D_8076A0B1 & 2) {
            if (D_80746858 == -1) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
            D_8076A0B1 ^= 2;
            osViBlack(0);
            if (D_80744470) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
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
        if (sp54 == -1) {}  // FAKE: steers uopt (hoists -1 into s2)
        if ((u32)sc->unk284 % ((u32 *)((TaskNode *)sp54)->unk50)[2] == 0) {
            schedAppendTask(sc, (TaskNode *)sp54);
        } else {
            osSendMesg(&sc->cmdQ, (OSMesg)sp54, 0);
        }
        if (sp54 == -1) {}  // FAKE: steers uopt (hoists -1 into s2)
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
