# Deferred header request (from .scratch/Clean478F0/header-request.md, round 3, not applied)
Base commit of the requesting copy: f67a7134b05924f05bac808f1d151821aac0086c

include/cutscene.h (CsState): split the third unk44 element into the two bytes the code accesses
(478F0.c csCmdLightPulse writes byte 0x49 via a local CsLightView cast; csCmdStepSequenceProgress /
csCmdBeatSyncAnimation / csCmdAnimProgressFromHubItems read/write byte 0x48 via (u8 *)cs + 0x48).
No size/offset change; unk44[2] is never indexed (only [0],[1] used in 42630.c / 478F0.c).

```diff
-    /* 0x44 */ s16 unk44[3];
+    /* 0x44 */ s16 unk44[2];
+    /* 0x48 */ u8 unk48;
+    /* 0x49 */ u8 unk49;
     /* 0x4A */ u8 pad4A;
```

## Orchestrator notes
the split is byte-preserving (s16 unk44[3] at 0x44 → s16 unk44[2]; u8 unk48; u8 unk49); 478F0 reads `(u8)cs->unk44[2]` five times (those become `cs->unk49`); 42630 indexes `cs->unk44[cmd->c]` (csCmdExec) and `->unk44[cmd->b]` (csCondEval) with variable indices that must be range-checked before splitting.
