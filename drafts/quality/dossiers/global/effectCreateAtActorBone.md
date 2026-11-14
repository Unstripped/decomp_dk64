# effectCreateAtActorBone (global, src/global/119370.c)
## Sites
global:80714C08:other:9f69ab (`u16 ownerHidden` temp): REMOVED.
- The function had no return statement.
- With `return effectCreate(...)`, the call's v0 is the function result, and the reloaded actor pointer takes v1. The plain `!(actor->flags & 0x200)` test then matches.
## Attempts
- rounds 5/17/32 (opus:low, opus): plain test without return (5 lines off); permutes only swap the temp for dead ifs.
- 2026-11-14 HackeffectCreateAtActorBone (opus), variants.py try (lines off):

  | variant | lines off |
  |---|---|
  | return + plain test | 0 |
  | plain test, no return | 5 |
  | Actor *a snapshot | 5 |
  | nested ifs | 5 |
  | == 0 test | 5 |
  | return + u16 temp | 13 |
  | s32 temp | 13 |
  | pending-flag test first | 16 |

  Parameter retyped Actor *: the owner stand-in and 8 caller stand-ins fdiff OK.
## Untried ideas
none (fixed).
## Evidence
fdiff 0, objdump raw words equal (standin_119370.c).
