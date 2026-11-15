# mapChunksInitFromMapData (global, src/global/55B20.c)
## Sites
- 551532 and fc3dbd: dead ifs (kept).
## Attempts (2026-11-14)
- **551532:**

  | form | text |
  |---|---|
  | removal | 38 |
  | MapPortal * snapshot | 64 |
  | both dead tests removed, with the snapshot | 139 |

- **fc3dbd:**

  | form | text |
  |---|---|
  | removal | 76 |
  | for-loop fill | 79 |
  | real `if (gMapChunks != NULL)` guard | 7 (adds a branch the target lacks) |

