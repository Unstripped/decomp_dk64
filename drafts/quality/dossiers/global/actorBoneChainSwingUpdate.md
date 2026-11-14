# actorBoneChainSwingUpdate (global, src/global/9CE20.c)

## Sites

global:80698120:dead-if:5f92e4 dead-if: preserves constant and global-base coloring around the queue loop; without it IDO hoists `li a1,0x50` and moves the `gActorGlobalState` base from `a1` to `a2`.

global:80698120:dead-if:04e08b dead-if: preserves the prologue `gCurrentActor` load in `t2` and the following `t2..t4` temporary ring.

## Attempts

2026-11-14 Rev20A HackactorBoneChainSwingUpdate openai-codex/gpt-5.6-sol: removed 5f92e4 alone; uopt trace plus the stock 119-body variants scan found no match (best baseline full mismatch 149).

2026-11-14 Rev20A HackactorBoneChainSwingUpdate openai-codex/gpt-5.6-sol: removed 04e08b alone; stock variants found no match; 7,583 as1 schedule edits improved 44 candidates but none matched (baseline full 274, best 266).

2026-11-14 Rev20A HackactorBoneChainSwingUpdate openai-codex/gpt-5.6-sol: tried a named `ActorGlobalState *` in both available pad declaration slots. It restores code before the queue but loads the count into `t9` at 0x30c and adds `move a0,a1` at 0x310.

2026-11-14 Rev20A HackactorBoneChainSwingUpdate openai-codex/gpt-5.6-sol: removed both sites together, tried a named repeated `Actor *`, and tried initializing `dir` through a default switch case. Coupled removal changes text from 3920 to 3824 bytes; the actor pointer grows it to 3984; the default keeps 3920 but increases mismatches. Restored both original tagged sites.

## Untried ideas

None among the brief's ordinary-C routes. The optional 900-second permuter was not repeated because the supplied history already records a no-hit run with both sites removed.

## Evidence

Target queue code loads `gActorGlobalState.volumeTriggerQueueCount` into `a0` at 0x30c, initializes `i` in `v1` at 0x310, forms the indexed queue address through `t2` at 0x31c, loads the element through `v0` at 0x320, loads 0x50 into `t4` at 0x334, stores it to `data->unk16` at 0x340, and reloads the queue count at 0x344.

With 5f92e4 removed, 0x50 is held in a register and the global base changes `a1 -> a2`. With 04e08b removed, the prologue `gCurrentActor` `lui` changes `t2 -> t3`. The final private copy has whole-object fdiff 0.
